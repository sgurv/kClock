/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1939
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DIGIT_4 aliases
#define DIGIT_4_TRIS                 TRISAbits.TRISA3
#define DIGIT_4_LAT                  LATAbits.LATA3
#define DIGIT_4_PORT                 PORTAbits.RA3
#define DIGIT_4_ANS                  ANSELAbits.ANSA3
#define DIGIT_4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define DIGIT_4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define DIGIT_4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define DIGIT_4_GetValue()           PORTAbits.RA3
#define DIGIT_4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define DIGIT_4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define DIGIT_4_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define DIGIT_4_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set DIGIT_3 aliases
#define DIGIT_3_TRIS                 TRISAbits.TRISA4
#define DIGIT_3_LAT                  LATAbits.LATA4
#define DIGIT_3_PORT                 PORTAbits.RA4
#define DIGIT_3_ANS                  ANSELAbits.ANSA4
#define DIGIT_3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define DIGIT_3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define DIGIT_3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define DIGIT_3_GetValue()           PORTAbits.RA4
#define DIGIT_3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define DIGIT_3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define DIGIT_3_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define DIGIT_3_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set LED_COLON aliases
#define LED_COLON_TRIS                 TRISAbits.TRISA7
#define LED_COLON_LAT                  LATAbits.LATA7
#define LED_COLON_PORT                 PORTAbits.RA7
#define LED_COLON_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_COLON_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_COLON_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_COLON_GetValue()           PORTAbits.RA7
#define LED_COLON_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_COLON_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set SW_1 aliases
#define SW_1_TRIS                 TRISBbits.TRISB0
#define SW_1_LAT                  LATBbits.LATB0
#define SW_1_PORT                 PORTBbits.RB0
#define SW_1_WPU                  WPUBbits.WPUB0
#define SW_1_ANS                  ANSELBbits.ANSB0
#define SW_1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define SW_1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define SW_1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define SW_1_GetValue()           PORTBbits.RB0
#define SW_1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define SW_1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define SW_1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define SW_1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define SW_1_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define SW_1_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set SW_2 aliases
#define SW_2_TRIS                 TRISBbits.TRISB1
#define SW_2_LAT                  LATBbits.LATB1
#define SW_2_PORT                 PORTBbits.RB1
#define SW_2_WPU                  WPUBbits.WPUB1
#define SW_2_ANS                  ANSELBbits.ANSB1
#define SW_2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SW_2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SW_2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SW_2_GetValue()           PORTBbits.RB1
#define SW_2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SW_2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SW_2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SW_2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SW_2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define SW_2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set SW_3 aliases
#define SW_3_TRIS                 TRISBbits.TRISB2
#define SW_3_LAT                  LATBbits.LATB2
#define SW_3_PORT                 PORTBbits.RB2
#define SW_3_WPU                  WPUBbits.WPUB2
#define SW_3_ANS                  ANSELBbits.ANSB2
#define SW_3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SW_3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SW_3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SW_3_GetValue()           PORTBbits.RB2
#define SW_3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SW_3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SW_3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SW_3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SW_3_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define SW_3_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set SW_4 aliases
#define SW_4_TRIS                 TRISBbits.TRISB3
#define SW_4_LAT                  LATBbits.LATB3
#define SW_4_PORT                 PORTBbits.RB3
#define SW_4_WPU                  WPUBbits.WPUB3
#define SW_4_ANS                  ANSELBbits.ANSB3
#define SW_4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define SW_4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define SW_4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define SW_4_GetValue()           PORTBbits.RB3
#define SW_4_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define SW_4_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define SW_4_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define SW_4_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define SW_4_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define SW_4_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set PULSE_IN aliases
#define PULSE_IN_TRIS                 TRISBbits.TRISB4
#define PULSE_IN_LAT                  LATBbits.LATB4
#define PULSE_IN_PORT                 PORTBbits.RB4
#define PULSE_IN_WPU                  WPUBbits.WPUB4
#define PULSE_IN_ANS                  ANSELBbits.ANSB4
#define PULSE_IN_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PULSE_IN_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PULSE_IN_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PULSE_IN_GetValue()           PORTBbits.RB4
#define PULSE_IN_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PULSE_IN_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PULSE_IN_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PULSE_IN_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PULSE_IN_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define PULSE_IN_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set DIGIT_2 aliases
#define DIGIT_2_TRIS                 TRISCbits.TRISC1
#define DIGIT_2_LAT                  LATCbits.LATC1
#define DIGIT_2_PORT                 PORTCbits.RC1
#define DIGIT_2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define DIGIT_2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define DIGIT_2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define DIGIT_2_GetValue()           PORTCbits.RC1
#define DIGIT_2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define DIGIT_2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS                 TRISCbits.TRISC3
#define SCL_LAT                  LATCbits.LATC3
#define SCL_PORT                 PORTCbits.RC3
#define SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL_GetValue()           PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISCbits.TRISC4
#define SDA_LAT                  LATCbits.LATC4
#define SDA_PORT                 PORTCbits.RC4
#define SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA_GetValue()           PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set SEG_DOT aliases
#define SEG_DOT_TRIS                 TRISDbits.TRISD0
#define SEG_DOT_LAT                  LATDbits.LATD0
#define SEG_DOT_PORT                 PORTDbits.RD0
#define SEG_DOT_ANS                  ANSELDbits.ANSD0
#define SEG_DOT_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define SEG_DOT_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define SEG_DOT_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define SEG_DOT_GetValue()           PORTDbits.RD0
#define SEG_DOT_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define SEG_DOT_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define SEG_DOT_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define SEG_DOT_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set SEG_G aliases
#define SEG_G_TRIS                 TRISDbits.TRISD1
#define SEG_G_LAT                  LATDbits.LATD1
#define SEG_G_PORT                 PORTDbits.RD1
#define SEG_G_ANS                  ANSELDbits.ANSD1
#define SEG_G_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define SEG_G_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define SEG_G_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define SEG_G_GetValue()           PORTDbits.RD1
#define SEG_G_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define SEG_G_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define SEG_G_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define SEG_G_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set SEG_F aliases
#define SEG_F_TRIS                 TRISDbits.TRISD2
#define SEG_F_LAT                  LATDbits.LATD2
#define SEG_F_PORT                 PORTDbits.RD2
#define SEG_F_ANS                  ANSELDbits.ANSD2
#define SEG_F_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define SEG_F_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define SEG_F_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define SEG_F_GetValue()           PORTDbits.RD2
#define SEG_F_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define SEG_F_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define SEG_F_SetAnalogMode()      do { ANSELDbits.ANSD2 = 1; } while(0)
#define SEG_F_SetDigitalMode()     do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set SEG_E aliases
#define SEG_E_TRIS                 TRISDbits.TRISD3
#define SEG_E_LAT                  LATDbits.LATD3
#define SEG_E_PORT                 PORTDbits.RD3
#define SEG_E_ANS                  ANSELDbits.ANSD3
#define SEG_E_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define SEG_E_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define SEG_E_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define SEG_E_GetValue()           PORTDbits.RD3
#define SEG_E_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define SEG_E_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define SEG_E_SetAnalogMode()      do { ANSELDbits.ANSD3 = 1; } while(0)
#define SEG_E_SetDigitalMode()     do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set SEG_D aliases
#define SEG_D_TRIS                 TRISDbits.TRISD4
#define SEG_D_LAT                  LATDbits.LATD4
#define SEG_D_PORT                 PORTDbits.RD4
#define SEG_D_ANS                  ANSELDbits.ANSD4
#define SEG_D_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define SEG_D_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define SEG_D_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define SEG_D_GetValue()           PORTDbits.RD4
#define SEG_D_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define SEG_D_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define SEG_D_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define SEG_D_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set SEG_C aliases
#define SEG_C_TRIS                 TRISDbits.TRISD5
#define SEG_C_LAT                  LATDbits.LATD5
#define SEG_C_PORT                 PORTDbits.RD5
#define SEG_C_ANS                  ANSELDbits.ANSD5
#define SEG_C_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define SEG_C_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define SEG_C_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define SEG_C_GetValue()           PORTDbits.RD5
#define SEG_C_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define SEG_C_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define SEG_C_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define SEG_C_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set SEG_B aliases
#define SEG_B_TRIS                 TRISDbits.TRISD6
#define SEG_B_LAT                  LATDbits.LATD6
#define SEG_B_PORT                 PORTDbits.RD6
#define SEG_B_ANS                  ANSELDbits.ANSD6
#define SEG_B_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define SEG_B_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define SEG_B_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define SEG_B_GetValue()           PORTDbits.RD6
#define SEG_B_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define SEG_B_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define SEG_B_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define SEG_B_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set SEG_A aliases
#define SEG_A_TRIS                 TRISDbits.TRISD7
#define SEG_A_LAT                  LATDbits.LATD7
#define SEG_A_PORT                 PORTDbits.RD7
#define SEG_A_ANS                  ANSELDbits.ANSD7
#define SEG_A_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define SEG_A_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define SEG_A_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define SEG_A_GetValue()           PORTDbits.RD7
#define SEG_A_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define SEG_A_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define SEG_A_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define SEG_A_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set DIGIT_1 aliases
#define DIGIT_1_TRIS                 TRISEbits.TRISE1
#define DIGIT_1_LAT                  LATEbits.LATE1
#define DIGIT_1_PORT                 PORTEbits.RE1
#define DIGIT_1_ANS                  ANSELEbits.ANSE1
#define DIGIT_1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define DIGIT_1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define DIGIT_1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define DIGIT_1_GetValue()           PORTEbits.RE1
#define DIGIT_1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define DIGIT_1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define DIGIT_1_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define DIGIT_1_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF4 pin functionality
 * @Example
    IOCBF4_ISR();
 */
void IOCBF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_InterruptHandler);

*/
extern void (*IOCBF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);

*/
void IOCBF4_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/