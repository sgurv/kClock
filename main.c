/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1939
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"
/*
                         Main application
 */

const uint8_t displayNum[] = {CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5,
                            CHAR_6, CHAR_7, CHAR_8, CHAR_9};

uint8_t displayBuff[4]; // 4 digits
uint8_t flag_time_display_update;

uint8_t rtcData[9];

uint8_t flag_button_press_count[4];
uint8_t button_press_count[4];

uint8_t mode;
uint8_t mode_timeout_count; // timeout to mode normal in seconds

enum mode{
    MODE_NORMAL,
    MODE_SET_HOUR,
    MODE_SET_MINUTE
};

void secondISR(void);
void displayRefreshISR(void);
void initRTC(void);
void updateRTC(uint8_t bcdHour, uint8_t bcdMinute);
static uint8_t bcdHourIncr(uint8_t hr);
static uint8_t bcdHourDecr(uint8_t hr);
static uint8_t bcdMinuteIncr(uint8_t mn);
static uint8_t bcdMinuteDecr(uint8_t mn);

void initRTC(void){
    __delay_ms(30);
    //i2c_write1ByteRegister(0x68,0x00,0x00);
    //i2c_writeNBytes(0x68,rtcData,1);
    //i2c_readNBytes(0x68,rtcData,sizeof(rtcData));
    i2c_readDataBlock(0x68,0x00,rtcData,sizeof(rtcData));
    if((rtcData[0] & 0x80) == 0x80){
        // need to start
        rtcData[0] = 0x00; // start register address
        rtcData[1] = 0x00; // start second
        rtcData[2] = 0x00; // BCD minute
        rtcData[3] = 0x00; // hour in 24hr format
        rtcData[4] = 0x01; // day 1-7
        rtcData[5] = 0x01; // 1-31
        rtcData[6] = 0x01; // month 1-12
        rtcData[7] = 0x19; // year 00-99
        rtcData[8] = 0x10; // control 1Hz SQWE output

        i2c_writeNBytes(0x68,rtcData,sizeof(rtcData));
    }
}

void updateRTC(uint8_t bcdHour, uint8_t bcdMinute){
    rtcData[0] = 0x00; // start register address
    rtcData[1] = 0x00; // start second
    rtcData[2] = bcdMinute & 0x7F; // BCD minute
    rtcData[3] = bcdHour & 0x3F; // hour in 24hr format
    i2c_writeNBytes(0x68,rtcData,4);
}
/*
static uint8_t byteToBcd2(uint8_t Value)
{
	uint8_t bcdhigh = 0U;

	while(Value >= 10U)
	{
		bcdhigh++;
		Value -= 10U;
	}

	return  ((uint8_t)(bcdhigh << 4U) | Value);
}
*/

static uint8_t bcdHourIncr(uint8_t hr){
    
    if(hr == 0x09) return 0x10;
    if(hr == 0x19) return 0x20;
    if(hr == 0x23) return 0x00;
    return (hr + 1);
}

static uint8_t bcdHourDecr(uint8_t hr){
    if(hr == 0x00) return 0x23;
    if(hr == 0x10) return 0x09;
    if(hr == 0x20) return 0x19;
    return (hr - 1);
}

static uint8_t bcdMinuteIncr(uint8_t mn){
    
    if(mn == 0x09) return 0x10;
    if(mn == 0x19) return 0x20;
    if(mn == 0x29) return 0x30;
    if(mn == 0x39) return 0x40;
    if(mn == 0x49) return 0x50;
    if(mn == 0x59) return 0x00;
    return (mn + 1);
}

static uint8_t bcdMinuteDecr(uint8_t mn){
    if(mn == 0x00) return 0x59;
    if(mn == 0x10) return 0x09;
    if(mn == 0x20) return 0x19;
    if(mn == 0x30) return 0x29;
    if(mn == 0x40) return 0x39;
    if(mn == 0x50) return 0x49;
    return (mn - 1);
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    //Turn Off all digit
    DIGIT_1_SetLow();
    DIGIT_2_SetLow();
    DIGIT_3_SetLow();
    DIGIT_4_SetLow();
    
    mode = MODE_NORMAL;
    
    IOCBF4_SetInterruptHandler(&secondISR);
    TMR0_SetInterruptHandler(&displayRefreshISR);
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    initRTC();
    
    while (1)
    {
        // Add your application code
        
        // Key scan
        
        if(SW_1_GetValue() == false){
            flag_button_press_count[0] = 1;
        } else if(SW_2_GetValue() == false){
            flag_button_press_count[1] = 1;
        } else if(SW_3_GetValue() == false){
            flag_button_press_count[2] = 1;
        } else if(SW_4_GetValue() == false){
            flag_button_press_count[3] = 1;
        } else { // no key pressed
            if(flag_button_press_count[0] == 1){ // previously pressed
                if(button_press_count[0] > BTN_DEBOUNCE_MIN  && button_press_count[0] < BTN_DEBOUNCE_MAX){
                    if(mode == MODE_NORMAL){
                        mode = MODE_SET_HOUR;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_HOUR){
                        mode = MODE_SET_MINUTE;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else { // back to normal
                        mode = MODE_NORMAL;
                    }
                    
                }
                button_press_count[0] = 0;
                flag_button_press_count[0] = 0;
            }
            
            if(flag_button_press_count[1] == 1){
                if(button_press_count[1] > BTN_DEBOUNCE_MIN  && button_press_count[1] < BTN_DEBOUNCE_MAX){
                    // incr
                    if(mode == MODE_SET_HOUR){
                        rtcData[2] = bcdHourIncr(rtcData[2]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MINUTE){
                        rtcData[1] = bcdMinuteIncr(rtcData[1]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    }
                    
                }
                button_press_count[1] = 0;
                flag_button_press_count[1] = 0;
            }
            
            if(flag_button_press_count[2] == 1){
                if(button_press_count[2] > BTN_DEBOUNCE_MIN  && button_press_count[2] < BTN_DEBOUNCE_MAX){
                    // decr
                    if(mode == MODE_SET_HOUR){
                        rtcData[2] = bcdHourDecr(rtcData[2]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MINUTE){
                        rtcData[1] = bcdMinuteDecr(rtcData[1]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    }
                }
                button_press_count[2] = 0;
                flag_button_press_count[2] = 0;
            }
            
            if(flag_button_press_count[3] == 1){
                if(button_press_count[3] > BTN_DEBOUNCE_MIN  && button_press_count[3] < BTN_DEBOUNCE_MAX){
                    updateRTC(rtcData[2],rtcData[1]);
                    
                    mode = MODE_NORMAL;
                    flag_time_display_update = 1;
                }
                button_press_count[3] = 0;
                flag_button_press_count[3] = 0;
            }
        }
        
        if(mode == MODE_NORMAL){
            if(flag_time_display_update == 1){
                i2c_readDataBlock(0x68,0x00,rtcData,sizeof(rtcData));

                displayBuff[0] = displayNum[((rtcData[2] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[2]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[1] >> 4) & 0x0F)];
                displayBuff[3] = displayNum[(rtcData[1]& 0x0F)];
                
                flag_time_display_update = 0;
            }
        } else {
            if(flag_time_display_update == 1){
                LED_COLON_SetHigh();
                displayBuff[0] = displayNum[((rtcData[2] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[2]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[1] >> 4) & 0x0F)];
                displayBuff[3] = displayNum[(rtcData[1]& 0x0F)];
                if(mode == MODE_SET_HOUR){
                    displayBuff[1] |= SEG_DOT;
                } else if(mode == MODE_SET_MINUTE){
                    displayBuff[3] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        }
    }
}

void secondISR(void){
    
    if(mode == MODE_NORMAL){
        LED_COLON_Toggle();
        flag_time_display_update = 1;
    }
    
    if(mode_timeout_count) {
        mode_timeout_count--;
        if(mode_timeout_count == 0){
            mode = MODE_NORMAL;
        }
    }
}

void displayRefreshISR(void){
    static uint8_t i;
    i &= 0x03;
    LATD = displayBuff[i];
    switch(i){
        case 0:
            DIGIT_4_SetLow();
            DIGIT_1_SetHigh();
            break;
        case 1:
            DIGIT_1_SetLow();
            DIGIT_2_SetHigh();
            break;
        case 2:
            DIGIT_2_SetLow();
            DIGIT_3_SetHigh();
            break;
        case 3:
            DIGIT_3_SetLow();
            DIGIT_4_SetHigh();
            break;
    }
    
    i++;
    
    //key debounce count
    if(flag_button_press_count[0] != 0){
		if(button_press_count[0] < BTN_MAX) button_press_count[0]++;
	}
    if(flag_button_press_count[1] != 0){
		if(button_press_count[1] < BTN_MAX) button_press_count[1]++;
	}
    if(flag_button_press_count[2] != 0){
		if(button_press_count[2] < BTN_MAX) button_press_count[2]++;
	}
    if(flag_button_press_count[3] != 0){
		if(button_press_count[3] < BTN_MAX) button_press_count[3]++;
	}

}
/**
 End of File
*/