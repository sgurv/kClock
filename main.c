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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.3
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

#define RTC_DS3231

#if defined(RTC_DS3231)

#define     SECONDS     0x00
#define     MINUTES     0x01
#define     HOURS       0x02
#define     DAY         0x03
#define     DATE        0x04
#define     MONTH       0x05
#define     YEAR        0x06
#define     AL1_SECONDS 0x07
#define     AL1_MINUTES 0x08
#define     AL1_HOURS   0x09
#define     AL1_DAY_DATE    0x0A
#define     AL2_MINUTES     0x0B
#define     AL2_HOURS       0x0C
#define     AL2_DAY_DATE    0x0D
#define     CONTROL         0x0E
#define     CONTROL_STATUS  0x0F
#define     AGING_OFFSET    0x10
#define     MSB_TEMP        0x11
#define     LSB_TEMP        0x12

#else

#define     SECONDS     0x00
#define     MINUTES     0x01
#define     HOURS       0x02
#define     DAY         0x03
#define     DATE        0x04
#define     MONTH       0x05
#define     YEAR        0x06
#define     CONTROL     0x07
#define     RAM         0x08

#endif

const uint8_t displayNum[] = {CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5,
                            CHAR_6, CHAR_7, CHAR_8, CHAR_9};

uint8_t displayBuff[4]; // 4 digits
uint8_t flag_time_display_update;
uint8_t flag_dot_blink;

#if defined(RTC_DS3231)
uint8_t rtcData[20];
#else 
uint8_t rtcData[9];
#endif

uint16_t bcd_temp;
uint16_t filter_temp; // for storing temperature ADC after FIR

uint8_t flag_button_press_count[4];
uint8_t button_press_count[4];

volatile uint8_t mode;
volatile uint8_t mode_timeout_count; // timeout to mode normal in 1/2 seconds
volatile uint8_t mode_flash_count;

uint8_t flag_alarm1,flag_alarm2;
uint8_t display_mode,temp_display_mode;

uint8_t buzz_timeout;

enum mode{
    MODE_NORMAL,
    MODE_TEMPERATURE,
    MODE_DATE,
    MODE_SET_HOUR,
    MODE_SET_MINUTE,
    MODE_SET_MONTH,
    MODE_SET_DATE,
    MODE_SET_AL1_H,
    MODE_SET_AL1_M,
    MODE_SET_AL2_H,
    MODE_SET_AL2_M,
    MODE_SET_DISPLAY_MODE
};

enum display_mode{
    DISPLAY_MODE_TIME,
    DISPLAY_MODE_TIME_DATE_30S_3S,
    DISPLAY_MODE_TIME_TEMP_10S_3S,
    DISPLAY_MODE_TIME_TEMP_30S_3S,
    DISPLAY_MODE_TIME_TEMP_60S_5S,
    DISPLAY_MODE_END
};

void secondISR(void);
void displayRefreshISR(void);
void initRTC(void);
void updateRTC(uint8_t bcdHour, uint8_t bcdMinute);
void updateAlarm1(uint8_t bcdHour, uint8_t bcdMinute);
void updateAlarm2(uint8_t bcdHour, uint8_t bcdMinute);
void clearAlarmFlag(void);
void updateDay(uint8_t bcdDay);
void updateDate(uint8_t bcdDate);
void updateMonth(uint8_t bcdMonth);
void updateYear(uint8_t bcdYear);
static uint8_t bcdHourIncr(uint8_t hr);
static uint8_t bcdHourDecr(uint8_t hr);
static uint8_t bcdMinuteIncr(uint8_t mn);
static uint8_t bcdMinuteDecr(uint8_t mn);
static uint8_t bcdMonthIncr(uint8_t mo);
static uint8_t bcdMonthDecr(uint8_t mo);
static uint8_t bcdDateIncr(uint8_t dt);
static uint8_t bcdDateDecr(uint8_t dt);
uint16_t intToBCD(uint16_t binaryInput);
adc_result_t FIR_filter(adc_result_t sample);

void initRTC(void){
    __delay_ms(30);
    //i2c_write1ByteRegister(0x68,0x00,0x00);
    //i2c_writeNBytes(0x68,rtcData,1);
    //i2c_readNBytes(0x68,rtcData,sizeof(rtcData));
    i2c_readDataBlock(0x68,0x00,rtcData,sizeof(rtcData));
    
#if defined(RTC_DS3231)
    if((rtcData[CONTROL_STATUS] & 0x80) == 0x80){// if osc stopped
        rtcData[0] = 0x00; // start register address
        rtcData[SECONDS+1] = 0x00;
        rtcData[MINUTES+1] = 0x00;
        rtcData[HOURS+1] = 0x00;
        rtcData[DAY+1] = 0x01; //day 1-7
        rtcData[DATE+1] = 0x01; //date 1-31
        rtcData[MONTH+1] = 0x01; //month 1-12 + century
        rtcData[YEAR+1] = 0x20; //00-99
        rtcData[AL1_SECONDS+1] = 0x00;
        rtcData[AL1_MINUTES+1] = 0x00;
        rtcData[AL1_HOURS+1] = 0x00;
        rtcData[AL1_DAY_DATE+1] = 0x00;
        rtcData[AL2_MINUTES+1] = 0x00;
        rtcData[AL1_HOURS+1] = 0x00;
        rtcData[AL1_DAY_DATE+1] = 0x00;
        rtcData[CONTROL+1] = 0x00; //osc enabled, 1Hz Sqw wave no AL int
        rtcData[CONTROL_STATUS+1] = 0x00; //osc enabled 32KHz disabled
        
        i2c_writeNBytes(0x68,rtcData,sizeof(rtcData));
    } else if((rtcData[CONTROL] & 0x04) == 0x04){ //if SQW not enabled
        rtcData[0] = CONTROL; //start reg address
        rtcData[1] = 0x00; //osc enabled, 1Hz SQW enabled
        i2c_writeNBytes(0x68,rtcData,2);
    }
#else
    if((rtcData[0] & 0x80) == 0x80){ // if clock stopped
        // need to start
        rtcData[0] = 0x00; // start register address
        rtcData[1] = 0x00; // start second
        rtcData[2] = 0x00; // BCD minute
        rtcData[3] = 0x00; // hour in 24hr format
        rtcData[4] = 0x01; // day 1-7
        rtcData[5] = 0x01; // 1-31
        rtcData[6] = 0x01; // month 1-12
        rtcData[7] = 0x20; // year 00-99
        rtcData[8] = 0x10; // control 1Hz SQWE output

        i2c_writeNBytes(0x68,rtcData,sizeof(rtcData));
    }
#endif
}

void updateRTC(uint8_t bcdHour, uint8_t bcdMinute){
    rtcData[0] = 0x00; // start register address
    rtcData[1] = 0x00; // start second
    rtcData[2] = bcdMinute & 0x7F; // BCD minute
    rtcData[3] = bcdHour & 0x3F; // hour in 24hr format
    i2c_writeNBytes(0x68,rtcData,4);
}

void updateAlarm1(uint8_t bcdHour, uint8_t bcdMinute){
    rtcData[0] = AL1_MINUTES; // start register address
    rtcData[1] = bcdMinute; // BCD minute
    rtcData[2] = (bcdHour & 0xBF) ; // hour in 24hr format
    if((bcdMinute != 0) || (bcdHour != 0)){
        // enable alarm
        rtcData[1] |= 0x80;
        rtcData[2] |= 0x80;
    }
    i2c_writeNBytes(0x68,rtcData,3);
}

void updateAlarm2(uint8_t bcdHour, uint8_t bcdMinute){
    rtcData[0] = AL2_MINUTES; // start register address
    rtcData[1] = bcdMinute; // BCD minute
    rtcData[2] = bcdHour & 0xBF; // hour in 24hr format
    if((bcdMinute != 0) || (bcdHour != 0)){
        // enable alarm
        rtcData[1] |= 0x80;
        rtcData[2] |= 0x80;
    }
    i2c_writeNBytes(0x68,rtcData,3);
}

void clearAlarmFlag(void){
    uint8_t rData[2];
    rData[0] = CONTROL_STATUS; //address
    rData[1] = 0x00;
    i2c_writeNBytes(0x68,rData,2);
}

void updateDay(uint8_t bcdDay){
    rtcData[0] = DAY; // start register address
    rtcData[1] = bcdDay & 0x07; // BCD date 1 - 7
    i2c_writeNBytes(0x68,rtcData,2);
}

void updateDate(uint8_t bcdDate){
    rtcData[0] = DATE; // start register address
    rtcData[1] = bcdDate & 0x3F; // BCD date 1-31
    i2c_writeNBytes(0x68,rtcData,2);
}

void updateMonth(uint8_t bcdMonth){
    rtcData[0] = MONTH; // start register address
    rtcData[1] = bcdMonth & 0x9F; // BCD 1-12 + century
    i2c_writeNBytes(0x68,rtcData,2);
}

void updateYear(uint8_t bcdYear){
    if(bcdYear <= 0x99){ //0-99 BCD
        rtcData[0] = YEAR; // start register address
        rtcData[1] = bcdYear; // BCD minute
        i2c_writeNBytes(0x68,rtcData,2);
    }
}



static uint8_t bcdHourIncr(uint8_t hr){
    hr &= 0x7F;
    if(hr == 0x09) return 0x10;
    if(hr == 0x19) return 0x20;
    if(hr == 0x23) return 0x00;
    return (hr + 1);
}

static uint8_t bcdHourDecr(uint8_t hr){
    hr &= 0x7F;
    if(hr == 0x00) return 0x23;
    if(hr == 0x10) return 0x09;
    if(hr == 0x20) return 0x19;
    return (hr - 1);
}

static uint8_t bcdMinuteIncr(uint8_t mn){
    mn &= 0x7F;
    if(mn == 0x09) return 0x10;
    if(mn == 0x19) return 0x20;
    if(mn == 0x29) return 0x30;
    if(mn == 0x39) return 0x40;
    if(mn == 0x49) return 0x50;
    if(mn == 0x59) return 0x00;
    return (mn + 1);
}

static uint8_t bcdMinuteDecr(uint8_t mn){
    mn &= 0x7F;
    if(mn == 0x00) return 0x59;
    if(mn == 0x10) return 0x09;
    if(mn == 0x20) return 0x19;
    if(mn == 0x30) return 0x29;
    if(mn == 0x40) return 0x39;
    if(mn == 0x50) return 0x49;
    return (mn - 1);
}

static uint8_t bcdMonthIncr(uint8_t mo){
    
    if(mo == 0x09) return 0x10;
    if(mo == 0x12) return 0x01; // 1 - 12 month
    return (mo + 1);
}

static uint8_t bcdMonthDecr(uint8_t mo){
    if(mo <= 0x01) return 0x12;
    if(mo == 0x10) return 0x09;
    return (mo - 1);
}

static uint8_t bcdDateIncr(uint8_t dt){
    if(dt >= 0x31) return 0x01;
    if(dt == 0x09) return 0x10;
    if(dt == 0x19) return 0x20;
    if(dt == 0x29) return 0x30;
    return (dt + 1);
}

static uint8_t bcdDateDecr(uint8_t dt){
    if(dt <= 0x01) return 0x31;
    if(dt == 0x10) return 0x09;
    if(dt == 0x20) return 0x19;
    if(dt == 0x30) return 0x29;
    return (dt - 1);
}

uint16_t intToBCD(uint16_t binaryInput){
    uint16_t bcdResult = 0;
    uint16_t shift = 0;
    
    while (binaryInput > 0) {
      bcdResult |= (binaryInput % 10) << (shift++ << 2);
      binaryInput /= 10;
    }
    
    return bcdResult;
}

/*
adc_result_t FIR_filter(adc_result_t sample){
    static adc_result_t buffer[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    static adc_result_t oldest = 0;
    static uint32_t sum;

    sum -= buffer[oldest];
    sum += sample;
    buffer[oldest] = sample;
    oldest += 1;
    if (oldest >= 32) oldest = 0;

    return (sum >> 5); // divide by 32
}
*/

adc_result_t FIR_filter(adc_result_t sample){
    static adc_result_t buffer[8] = {0,0,0,0,0,0,0,0};
    static adc_result_t oldest = 0;
    static uint32_t sum;

    sum -= buffer[oldest];
    sum += sample;
    buffer[oldest] = sample;
    oldest += 1;
    if (oldest >= 8) oldest = 0;

    return (sum >> 3); // divide by 8
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
    flag_alarm1 = 0;
    flag_alarm2 = 0;
    
    //read display mode and other settings from EEPROM
    display_mode = DATAEE_ReadByte(0x01);
    
    if(display_mode >= DISPLAY_MODE_END){
        display_mode = DISPLAY_MODE_TIME;
    }
    
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
        CLRWDT();
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
                    } else if(mode == MODE_SET_MINUTE){
                        mode = MODE_SET_MONTH;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        mode_flash_count = MODE_FLASH_INTERVAL; //Flash for date
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MONTH){
                        mode = MODE_SET_DATE;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_DATE){
                        mode = MODE_SET_AL1_H;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        mode_flash_count = MODE_FLASH_INTERVAL; //Flash
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_H){
                        mode = MODE_SET_AL1_M;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_M){
                        mode = MODE_SET_AL2_H;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        mode_flash_count = MODE_FLASH_INTERVAL; //Flash
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_H){
                        mode = MODE_SET_AL2_M;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_M){
                        mode = MODE_SET_DISPLAY_MODE;
                        temp_display_mode = display_mode; //temp used for display mode setting
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
                        rtcData[HOURS] = bcdHourIncr(rtcData[HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MINUTE){
                        rtcData[MINUTES] = bcdMinuteIncr(rtcData[MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MONTH){
                        rtcData[MONTH] = bcdMonthIncr(rtcData[MONTH]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_DATE){
                        rtcData[DATE] = bcdDateIncr(rtcData[DATE]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_H){
                        rtcData[AL1_HOURS] = bcdHourIncr(rtcData[AL1_HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_M){
                        rtcData[AL1_MINUTES] = bcdMinuteIncr(rtcData[AL1_MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_H){
                        rtcData[AL2_HOURS] = bcdHourIncr(rtcData[AL2_HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_M){
                        rtcData[AL2_MINUTES] = bcdMinuteIncr(rtcData[AL2_MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_DISPLAY_MODE){
                        temp_display_mode++;
                        
                        if(temp_display_mode == DISPLAY_MODE_END){
                            temp_display_mode = 0;
                        }
                        
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    }
                    
                    mode_flash_count = 0; // cancel flash immediately if up/down pressed
                    
                }
                button_press_count[1] = 0;
                flag_button_press_count[1] = 0;
            }
            
            if(flag_button_press_count[2] == 1){
                if(button_press_count[2] > BTN_DEBOUNCE_MIN  && button_press_count[2] < BTN_DEBOUNCE_MAX){
                    // decr
                    if(mode == MODE_SET_HOUR){
                        rtcData[HOURS] = bcdHourDecr(rtcData[HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MINUTE){
                        rtcData[MINUTES] = bcdMinuteDecr(rtcData[MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_MONTH){
                        rtcData[MONTH] = bcdMonthDecr(rtcData[MONTH]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_DATE){
                        rtcData[DATE] = bcdDateDecr(rtcData[DATE]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_H){
                        rtcData[AL1_HOURS] = bcdHourDecr(rtcData[AL1_HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL1_M){
                        rtcData[AL1_MINUTES] = bcdMinuteDecr(rtcData[AL1_MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_H){
                        rtcData[AL2_HOURS] = bcdHourDecr(rtcData[AL2_HOURS]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_AL2_M){
                        rtcData[AL2_MINUTES] = bcdMinuteDecr(rtcData[AL2_MINUTES]);
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    } else if(mode == MODE_SET_DISPLAY_MODE){
                        if(temp_display_mode) temp_display_mode--;
                        mode_timeout_count = MODE_TIMEOUT_INTERVAL;
                        flag_time_display_update = 1;
                    }
                    
                    mode_flash_count = 0; // cancel flash immediately if up/down pressed
                }
                button_press_count[2] = 0;
                flag_button_press_count[2] = 0;
            }
            
            if(flag_button_press_count[3] == 1){
                if(button_press_count[3] > BTN_DEBOUNCE_MIN  && button_press_count[3] < BTN_DEBOUNCE_MAX){
                    
                    if((mode == MODE_SET_HOUR) || (mode == MODE_SET_MINUTE)){
                        updateRTC(rtcData[HOURS],rtcData[MINUTES]);
                    } else if(mode == MODE_SET_MONTH){
                        updateMonth(rtcData[MONTH]);
                    } else if (mode == MODE_SET_DATE){
                        updateDate(rtcData[DATE]);
                    } else if ((mode == MODE_SET_AL1_H) || (mode == MODE_SET_AL1_M)){
                        updateAlarm1(rtcData[AL1_HOURS], rtcData[AL1_MINUTES]);
                    } else if ((mode == MODE_SET_AL2_H) || (mode == MODE_SET_AL2_M)){
                        updateAlarm2(rtcData[AL2_HOURS], rtcData[AL2_MINUTES]);
                    } else if(mode == MODE_SET_DISPLAY_MODE){
                        //update display mode
                        display_mode = temp_display_mode;
                        DATAEE_WriteByte(0x01, temp_display_mode);
                    }
                    
                    mode = MODE_NORMAL;
                    flag_time_display_update = 1;
                }
                button_press_count[3] = 0;
                flag_button_press_count[3] = 0;
            }
        }
        
        if(mode == MODE_NORMAL){
            if(flag_time_display_update == 1){
                if(PULSE_IN_GetValue()) { // read on high pulse
#if defined(RTC_DS3231)
                    i2c_readDataBlock(0x68,0x00,rtcData,AGING_OFFSET); //Upto CONTROL_STATUS
                    //Check alarm
                    if((rtcData[CONTROL_STATUS] & 0x01) != 0) { 
                        flag_alarm1 = 1;
                    }
                    if((rtcData[CONTROL_STATUS] & 0x02) != 0) {
                        flag_alarm2 = 1;
                    }
                    
                    if((flag_alarm1 == 1) || (flag_alarm1 == 1)){
                        clearAlarmFlag(); //Clear Alarm flags in RTC if needed
                    }
#else
                    i2c_readDataBlock(0x68,0x00,rtcData,sizeof(rtcData));
#endif
                } 
                
                if((display_mode == DISPLAY_MODE_TIME_DATE_30S_3S) 
                        && ((rtcData[SECONDS] == 0x27) || (rtcData[SECONDS] == 0x57))){ //bcd sec 0-59;
                    //
                    mode_flash_count = 6; //3s
                    mode = MODE_DATE;
                } else if((display_mode == DISPLAY_MODE_TIME_TEMP_10S_3S) 
                        && ((rtcData[SECONDS] == 0x07) || (rtcData[SECONDS] == 0x17)
                        || (rtcData[SECONDS] == 0x27) || (rtcData[SECONDS] == 0x37)
                        || (rtcData[SECONDS] == 0x47) || (rtcData[SECONDS] == 0x57))){
                    //
                    mode_flash_count = 6; //3s
                    mode = MODE_TEMPERATURE;
                } else if((display_mode == DISPLAY_MODE_TIME_TEMP_30S_3S) 
                        && ((rtcData[SECONDS] == 0x27) || (rtcData[SECONDS] == 0x57))){
                    //
                    mode_flash_count = 6;
                    mode = MODE_TEMPERATURE;
                } else if((display_mode == DISPLAY_MODE_TIME_TEMP_60S_5S) && (rtcData[SECONDS] == 0x55)){
                    //
                    mode_flash_count = 10;
                    mode = MODE_TEMPERATURE;
                } else { //display_mode == DISPLAY_MODE_TIME // only time
                
                    displayBuff[0] = displayNum[((rtcData[HOURS] >> 4) & 0x03)];
                    displayBuff[1] = displayNum[(rtcData[HOURS]& 0x0F)];
                    displayBuff[2] = displayNum[((rtcData[MINUTES] >> 4) & 0x07)];
                    displayBuff[3] = displayNum[(rtcData[MINUTES]& 0x0F)];

                    flag_time_display_update = 0;
                }
            }
        } else if(mode == MODE_TEMPERATURE){
            if(flag_time_display_update == 1){
                if(mode_flash_count){
                    LED_COLON_SetLow();

                    bcd_temp = intToBCD(filter_temp); // read ADC

                    displayBuff[0] = displayNum[((bcd_temp >> 8) & 0x0F)];
                    displayBuff[1] = displayNum[((bcd_temp >> 4) & 0x0F)] | SEG_DOT;
                    displayBuff[2] = displayNum[(bcd_temp & 0x0F)];
                    displayBuff[3] = CHAR_C;

                    flag_time_display_update = 0;
                } else {
                    mode = MODE_NORMAL;
                }
            }
        } else if(mode == MODE_DATE){
            if(flag_time_display_update == 1){
                if(mode_flash_count){
                    LED_COLON_SetLow();
                    displayBuff[0] = displayNum[((rtcData[DATE] >> 4) & 0x03)]; //date
                    displayBuff[1] = displayNum[(rtcData[DATE]& 0x0F)];
                    displayBuff[2] = displayNum[((rtcData[MONTH] >> 4) & 0x01)]; //month
                    displayBuff[3] = displayNum[(rtcData[MONTH]& 0x0F)];

                    flag_time_display_update = 0;
                } else {
                    mode = MODE_NORMAL;
                }
            }
        } else if(mode == MODE_SET_HOUR){
            if(flag_time_display_update == 1){
                LED_COLON_SetHigh();
                displayBuff[0] = displayNum[((rtcData[HOURS] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[HOURS]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[MINUTES] >> 4) & 0x07)];
                displayBuff[3] = displayNum[(rtcData[MINUTES]& 0x0F)];
                if(flag_dot_blink){
                    displayBuff[1] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_MINUTE){
            if(flag_time_display_update == 1){
                LED_COLON_SetHigh();
                displayBuff[0] = displayNum[((rtcData[HOURS] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[HOURS]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[MINUTES] >> 4) & 0x07)];
                displayBuff[3] = displayNum[(rtcData[MINUTES]& 0x0F)];
                if(flag_dot_blink){
                    displayBuff[3] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_MONTH){ //month
            if(flag_time_display_update == 1){
                if(mode_flash_count){
                    //Flash DD MM
                    LED_COLON_SetLow();
                    displayBuff[0] = CHAR_D;
                    displayBuff[1] = CHAR_D;
                    displayBuff[2] = (SEG_A | SEG_B | SEG_E | SEG_F);
                    displayBuff[3] = (SEG_A | SEG_B | SEG_C | SEG_F);
                } else {
                    LED_COLON_SetLow();
                    displayBuff[0] = displayNum[((rtcData[DATE] >> 4) & 0x03)]; //date
                    displayBuff[1] = displayNum[(rtcData[DATE]& 0x0F)];
                    displayBuff[2] = displayNum[((rtcData[MONTH] >> 4) & 0x01)]; //month
                    displayBuff[3] = displayNum[(rtcData[MONTH]& 0x0F)];
                    if(flag_dot_blink){
                        displayBuff[3] |= SEG_DOT;
                    }
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_DATE){ //date
            if(flag_time_display_update == 1){
                LED_COLON_SetLow();
                displayBuff[0] = displayNum[((rtcData[DATE] >> 4) & 0x03)]; //date
                displayBuff[1] = displayNum[(rtcData[DATE]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[MONTH] >> 4) & 0x01)]; //month
                displayBuff[3] = displayNum[(rtcData[MONTH]& 0x0F)];
                if(flag_dot_blink){
                    displayBuff[1] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_AL1_H){
            if(flag_time_display_update == 1){
                if(mode_flash_count){
                    //Flash AL 1
                    LED_COLON_SetLow();
                    displayBuff[0] = CHAR_A;
                    displayBuff[1] = CHAR_L;
                    displayBuff[2] = CHAR_SPC;
                    displayBuff[3] = CHAR_1;
                } else {
                    LED_COLON_SetHigh();
                    displayBuff[0] = displayNum[((rtcData[AL1_HOURS] >> 4) & 0x03)];
                    displayBuff[1] = displayNum[(rtcData[AL1_HOURS]& 0x0F)];
                    displayBuff[2] = displayNum[((rtcData[AL1_MINUTES] >> 4) & 0x07)];
                    displayBuff[3] = displayNum[(rtcData[AL1_MINUTES]& 0x0F)];
                    if(flag_dot_blink){
                        displayBuff[1] |= SEG_DOT;
                    }
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_AL1_M){
            if(flag_time_display_update == 1){
                LED_COLON_SetHigh();
                displayBuff[0] = displayNum[((rtcData[AL1_HOURS] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[AL1_HOURS]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[AL1_MINUTES] >> 4) & 0x07)];
                displayBuff[3] = displayNum[(rtcData[AL1_MINUTES]& 0x0F)];
                if(flag_dot_blink){
                    displayBuff[3] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_AL2_H){
            if(flag_time_display_update == 1){
                if(mode_flash_count){
                    //Flash AL 2
                    LED_COLON_SetLow();
                    displayBuff[0] = CHAR_A;
                    displayBuff[1] = CHAR_L;
                    displayBuff[2] = CHAR_SPC;
                    displayBuff[3] = CHAR_2;
                } else {
                    LED_COLON_SetHigh();
                    displayBuff[0] = displayNum[((rtcData[AL2_HOURS] >> 4) & 0x03)];
                    displayBuff[1] = displayNum[(rtcData[AL2_HOURS]& 0x0F)];
                    displayBuff[2] = displayNum[((rtcData[AL2_MINUTES] >> 4) & 0x07)];
                    displayBuff[3] = displayNum[(rtcData[AL2_MINUTES]& 0x0F)];
                    if(flag_dot_blink){
                        displayBuff[1] |= SEG_DOT;
                    }
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_AL2_M){
            if(flag_time_display_update == 1){
                LED_COLON_SetHigh();
                displayBuff[0] = displayNum[((rtcData[AL2_HOURS] >> 4) & 0x03)];
                displayBuff[1] = displayNum[(rtcData[AL2_HOURS]& 0x0F)];
                displayBuff[2] = displayNum[((rtcData[AL2_MINUTES] >> 4) & 0x07)];
                displayBuff[3] = displayNum[(rtcData[AL2_MINUTES]& 0x0F)];
                if(flag_dot_blink){
                    displayBuff[3] |= SEG_DOT;
                }
                flag_time_display_update = 0;
            }
        } else if(mode == MODE_SET_DISPLAY_MODE){ //Display mode
            if(flag_time_display_update == 1){
                LED_COLON_SetLow();
                bcd_temp = (uint8_t) intToBCD((uint16_t)temp_display_mode); // display_mode to BCD
                displayBuff[0] = CHAR_D; //
                displayBuff[1] = 0x00;
                displayBuff[2] = displayNum[((bcd_temp >> 4) & 0x0F)];
                displayBuff[3] = displayNum[(bcd_temp& 0x0F)];
                
                flag_time_display_update = 0;
            }
        }
        
        //Alarm
        if(flag_alarm1){
            flag_alarm1 = 0;
            //buzz
            buzz_timeout = 30; //15 second
            BUZZ_SetHigh();
        }
        
        if(flag_alarm2){
            flag_alarm2 = 0;
            //buzz
            buzz_timeout = 30; //15 second
            BUZZ_SetHigh();
        }
        
        if(buzz_timeout == 0) {
            BUZZ_SetLow();
        }
        
        //TODO: UART thing
        
        //temperature thing
        if((display_mode == DISPLAY_MODE_TIME_TEMP_10S_3S) 
            || (display_mode == DISPLAY_MODE_TIME_TEMP_30S_3S)
            || (display_mode == DISPLAY_MODE_TIME_TEMP_60S_5S)){
            
            filter_temp = FIR_filter(ADC_GetConversion(channel_AN13));
        }
    }
}

void secondISR(void){
    
    if(mode == MODE_NORMAL){
        LED_COLON_Toggle();
    } else {
        if(flag_dot_blink) flag_dot_blink = 0;
        else flag_dot_blink = 1;
    }
    
    flag_time_display_update = 1;
    
    if(mode_timeout_count) {
        mode_timeout_count--;
        if(mode_timeout_count == 0){
            mode = MODE_NORMAL;
        }
    }
    
    if(mode_flash_count) mode_flash_count--;
    
    if(buzz_timeout) buzz_timeout--;
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