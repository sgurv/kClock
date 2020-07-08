/* 
 * File:   main.h
 * Author: sandeep
 *
 * Created on September 1, 2019, 11:36 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define     BTN_DEBOUNCE_MIN    5
#define     BTN_DEBOUNCE_MAX    100
#define     BTN_MAX             200
    
#define     MODE_TIMEOUT_INTERVAL   8
    
#define     SEG_A   (1 << 7)
#define     SEG_B   (1 << 6)
#define     SEG_C   (1 << 5)
#define     SEG_D   (1 << 4)
#define     SEG_E   (1 << 3)
#define     SEG_F   (1 << 2)
#define     SEG_G   (1 << 1)
#define     SEG_DOT (1 << 0)

#define     CHAR_0  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define     CHAR_1  (SEG_B | SEG_C)
#define     CHAR_2  (SEG_A | SEG_B | SEG_D | SEG_E | SEG_G)
#define     CHAR_3  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)
#define     CHAR_4  (SEG_B | SEG_C | SEG_F | SEG_G)
#define     CHAR_5  (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)
#define     CHAR_6  (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     CHAR_7  (SEG_A | SEG_B | SEG_C)
#define     CHAR_8  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     CHAR_9  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)

#define     CHAR_SPC 0x00
#define     CHAR_A  (SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define     CHAR_B  (SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     CHAR_C  (SEG_A | SEG_D | SEG_E | SEG_F)
#define     CHAR_D  (SEG_B | SEG_C | SEG_D | SEG_E | SEG_G)
#define     CHAR_E  (SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)
#define     CHAR_F  (SEG_A | SEG_E | SEG_F | SEG_G)
#define     CHAR_G  (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F)
#define     CHAR_H  (SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define     CHAR_I  (SEG_B | SEG_C)
#define     CHAR_J  (SEG_B | SEG_C | SEG_D | SEG_E)
#define     CHAR_K  (SEG_E | SEG_F | SEG_G)    
#define     CHAR_L  (SEG_D | SEG_E | SEG_F)    

#define     CHAR_T  (SEG_D | SEG_E | SEG_F | SEG_G)
    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

