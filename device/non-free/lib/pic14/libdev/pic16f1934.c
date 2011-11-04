/* Register definitions for pic16f1934.
 * This file was automatically generated by:
 *   inc2h.pl V4850
 *   Copyright (c) 2002, Kevin L. Pauba, All Rights Reserved
 */
#include <pic16f1934.h>

__sfr  __at (INDF0_ADDR)                   INDF0;
__sfr  __at (INDF1_ADDR)                   INDF1;
__sfr  __at (PCL_ADDR)                     PCL;
__sfr  __at (STATUS_ADDR)                  STATUS;
__sfr  __at (FSR0L_ADDR)                   FSR0L;
__sfr  __at (FSR0_ADDR)                    FSR0;
__sfr  __at (FSR0H_ADDR)                   FSR0H;
__sfr  __at (FSR1L_ADDR)                   FSR1L;
__sfr  __at (FSR1_ADDR)                    FSR1;
__sfr  __at (FSR1H_ADDR)                   FSR1H;
__sfr  __at (BSR_ADDR)                     BSR;
__sfr  __at (WREG_ADDR)                    WREG;
__sfr  __at (PCLATH_ADDR)                  PCLATH;
__sfr  __at (INTCON_ADDR)                  INTCON;
__sfr  __at (PORTA_ADDR)                   PORTA;
__sfr  __at (PORTB_ADDR)                   PORTB;
__sfr  __at (PORTC_ADDR)                   PORTC;
__sfr  __at (PORTD_ADDR)                   PORTD;
__sfr  __at (PORTE_ADDR)                   PORTE;
__sfr  __at (PIR1_ADDR)                    PIR1;
__sfr  __at (PIR2_ADDR)                    PIR2;
__sfr  __at (PIR3_ADDR)                    PIR3;
__sfr  __at (TMR0_ADDR)                    TMR0;
__sfr  __at (TMR1L_ADDR)                   TMR1L;
__sfr  __at (TMR1_ADDR)                    TMR1;
__sfr  __at (TMR1H_ADDR)                   TMR1H;
__sfr  __at (T1CON_ADDR)                   T1CON;
__sfr  __at (T1GCON_ADDR)                  T1GCON;
__sfr  __at (TMR2_ADDR)                    TMR2;
__sfr  __at (PR2_ADDR)                     PR2;
__sfr  __at (T2CON_ADDR)                   T2CON;
__sfr  __at (CPSCON0_ADDR)                 CPSCON0;
__sfr  __at (CPSCON1_ADDR)                 CPSCON1;
__sfr  __at (TRISA_ADDR)                   TRISA;
__sfr  __at (TRISB_ADDR)                   TRISB;
__sfr  __at (TRISC_ADDR)                   TRISC;
__sfr  __at (TRISD_ADDR)                   TRISD;
__sfr  __at (TRISE_ADDR)                   TRISE;
__sfr  __at (PIE1_ADDR)                    PIE1;
__sfr  __at (PIE2_ADDR)                    PIE2;
__sfr  __at (PIE3_ADDR)                    PIE3;
__sfr  __at (OPTION_REG_ADDR)              OPTION_REG;
__sfr  __at (PCON_ADDR)                    PCON;
__sfr  __at (WDTCON_ADDR)                  WDTCON;
__sfr  __at (OSCTUNE_ADDR)                 OSCTUNE;
__sfr  __at (OSCCON_ADDR)                  OSCCON;
__sfr  __at (OSCCONL_ADDR)                 OSCCONL;
__sfr  __at (OSCCONH_ADDR)                 OSCCONH;
__sfr  __at (OSCSTAT_ADDR)                 OSCSTAT;
__sfr  __at (ADRESL_ADDR)                  ADRESL;
__sfr  __at (ADRES_ADDR)                   ADRES;
__sfr  __at (ADRESH_ADDR)                  ADRESH;
__sfr  __at (ADCON0_ADDR)                  ADCON0;
__sfr  __at (ADCON1_ADDR)                  ADCON1;
__sfr  __at (LATA_ADDR)                    LATA;
__sfr  __at (LATB_ADDR)                    LATB;
__sfr  __at (LATC_ADDR)                    LATC;
__sfr  __at (LATD_ADDR)                    LATD;
__sfr  __at (LATE_ADDR)                    LATE;
__sfr  __at (CM1CON0_ADDR)                 CM1CON0;
__sfr  __at (CM1CON1_ADDR)                 CM1CON1;
__sfr  __at (CM2CON0_ADDR)                 CM2CON0;
__sfr  __at (CM2CON1_ADDR)                 CM2CON1;
__sfr  __at (CMOUT_ADDR)                   CMOUT;
__sfr  __at (BORCON_ADDR)                  BORCON;
__sfr  __at (FVRCON_ADDR)                  FVRCON;
__sfr  __at (DACCON0_ADDR)                 DACCON0;
__sfr  __at (DACCON1_ADDR)                 DACCON1;
__sfr  __at (SRCON0_ADDR)                  SRCON0;
__sfr  __at (SRCON1_ADDR)                  SRCON1;
__sfr  __at (APFCON_ADDR)                  APFCON;
__sfr  __at (ANSELA_ADDR)                  ANSELA;
__sfr  __at (ANSELB_ADDR)                  ANSELB;
__sfr  __at (ANSELD_ADDR)                  ANSELD;
__sfr  __at (ANSELE_ADDR)                  ANSELE;
__sfr  __at (EEADRL_ADDR)                  EEADRL;
__sfr  __at (EEADR_ADDR)                   EEADR;
__sfr  __at (EEADRH_ADDR)                  EEADRH;
__sfr  __at (EEDATL_ADDR)                  EEDATL;
__sfr  __at (EEDAT_ADDR)                   EEDAT;
__sfr  __at (EEDATH_ADDR)                  EEDATH;
__sfr  __at (EECON1_ADDR)                  EECON1;
__sfr  __at (EECON2_ADDR)                  EECON2;
__sfr  __at (RCREG_ADDR)                   RCREG;
__sfr  __at (TXREG_ADDR)                   TXREG;
__sfr  __at (SPBRGL_ADDR)                  SPBRGL;
__sfr  __at (SPBRG_ADDR)                   SPBRG;
__sfr  __at (SPBRGH_ADDR)                  SPBRGH;
__sfr  __at (RCSTA_ADDR)                   RCSTA;
__sfr  __at (TXSTA_ADDR)                   TXSTA;
__sfr  __at (BAUDCON_ADDR)                 BAUDCON;
__sfr  __at (WPUB_ADDR)                    WPUB;
__sfr  __at (WPUE_ADDR)                    WPUE;
__sfr  __at (SSPBUF_ADDR)                  SSPBUF;
__sfr  __at (SSPADD_ADDR)                  SSPADD;
__sfr  __at (SSPMSK_ADDR)                  SSPMSK;
__sfr  __at (SSPSTAT_ADDR)                 SSPSTAT;
__sfr  __at (SSPCON1_ADDR)                 SSPCON1;
__sfr  __at (SSPCON_ADDR)                  SSPCON;
__sfr  __at (SSPCON2_ADDR)                 SSPCON2;
__sfr  __at (SSPCON3_ADDR)                 SSPCON3;
__sfr  __at (CCPR1L_ADDR)                  CCPR1L;
__sfr  __at (CCPR1H_ADDR)                  CCPR1H;
__sfr  __at (CCP1CON_ADDR)                 CCP1CON;
__sfr  __at (PWM1CON_ADDR)                 PWM1CON;
__sfr  __at (CCP1AS_ADDR)                  CCP1AS;
__sfr  __at (ECCP1AS_ADDR)                 ECCP1AS;
__sfr  __at (PSTR1CON_ADDR)                PSTR1CON;
__sfr  __at (CCPR2L_ADDR)                  CCPR2L;
__sfr  __at (CCPR2H_ADDR)                  CCPR2H;
__sfr  __at (CCP2CON_ADDR)                 CCP2CON;
__sfr  __at (PWM2CON_ADDR)                 PWM2CON;
__sfr  __at (CCP2AS_ADDR)                  CCP2AS;
__sfr  __at (ECCP2AS_ADDR)                 ECCP2AS;
__sfr  __at (PSTR2CON_ADDR)                PSTR2CON;
__sfr  __at (CCPTMRS0_ADDR)                CCPTMRS0;
__sfr  __at (CCPTMRS1_ADDR)                CCPTMRS1;
__sfr  __at (CCPR3L_ADDR)                  CCPR3L;
__sfr  __at (CCPR3H_ADDR)                  CCPR3H;
__sfr  __at (CCP3CON_ADDR)                 CCP3CON;
__sfr  __at (PWM3CON_ADDR)                 PWM3CON;
__sfr  __at (CCP3AS_ADDR)                  CCP3AS;
__sfr  __at (ECCP3AS_ADDR)                 ECCP3AS;
__sfr  __at (PSTR3CON_ADDR)                PSTR3CON;
__sfr  __at (CCPR4L_ADDR)                  CCPR4L;
__sfr  __at (CCPR4H_ADDR)                  CCPR4H;
__sfr  __at (CCP4CON_ADDR)                 CCP4CON;
__sfr  __at (CCPR5L_ADDR)                  CCPR5L;
__sfr  __at (CCPR5H_ADDR)                  CCPR5H;
__sfr  __at (CCP5CON_ADDR)                 CCP5CON;
__sfr  __at (IOCBP_ADDR)                   IOCBP;
__sfr  __at (IOCBN_ADDR)                   IOCBN;
__sfr  __at (IOCBF_ADDR)                   IOCBF;
__sfr  __at (TMR4_ADDR)                    TMR4;
__sfr  __at (PR4_ADDR)                     PR4;
__sfr  __at (T4CON_ADDR)                   T4CON;
__sfr  __at (TMR6_ADDR)                    TMR6;
__sfr  __at (PR6_ADDR)                     PR6;
__sfr  __at (T6CON_ADDR)                   T6CON;
__sfr  __at (LCDCON_ADDR)                  LCDCON;
__sfr  __at (LCDPS_ADDR)                   LCDPS;
__sfr  __at (LCDREF_ADDR)                  LCDREF;
__sfr  __at (LCDCST_ADDR)                  LCDCST;
__sfr  __at (LCDRL_ADDR)                   LCDRL;
__sfr  __at (LCDSE0_ADDR)                  LCDSE0;
__sfr  __at (LCDSE1_ADDR)                  LCDSE1;
__sfr  __at (LCDSE2_ADDR)                  LCDSE2;
__sfr  __at (LCDDATA0_ADDR)                LCDDATA0;
__sfr  __at (LCDDATA1_ADDR)                LCDDATA1;
__sfr  __at (LCDDATA2_ADDR)                LCDDATA2;
__sfr  __at (LCDDATA3_ADDR)                LCDDATA3;
__sfr  __at (LCDDATA4_ADDR)                LCDDATA4;
__sfr  __at (LCDDATA5_ADDR)                LCDDATA5;
__sfr  __at (LCDDATA6_ADDR)                LCDDATA6;
__sfr  __at (LCDDATA7_ADDR)                LCDDATA7;
__sfr  __at (LCDDATA8_ADDR)                LCDDATA8;
__sfr  __at (LCDDATA9_ADDR)                LCDDATA9;
__sfr  __at (LCDDATA10_ADDR)               LCDDATA10;
__sfr  __at (LCDDATA11_ADDR)               LCDDATA11;
__sfr  __at (STATUS_SHAD_ADDR)             STATUS_SHAD;
__sfr  __at (WREG_SHAD_ADDR)               WREG_SHAD;
__sfr  __at (BSR_SHAD_ADDR)                BSR_SHAD;
__sfr  __at (PCLATH_SHAD_ADDR)             PCLATH_SHAD;
__sfr  __at (FSR0L_SHAD_ADDR)              FSR0L_SHAD;
__sfr  __at (FSR0H_SHAD_ADDR)              FSR0H_SHAD;
__sfr  __at (FSR1L_SHAD_ADDR)              FSR1L_SHAD;
__sfr  __at (FSR1H_SHAD_ADDR)              FSR1H_SHAD;
__sfr  __at (STKPTR_ADDR)                  STKPTR;
__sfr  __at (TOSL_ADDR)                    TOSL;
__sfr  __at (TOSH_ADDR)                    TOSH;

// 
// bitfield definitions
// 
volatile __ADCON0_bits_t __at(ADCON0_ADDR) ADCON0_bits;
volatile __ADCON1_bits_t __at(ADCON1_ADDR) ADCON1_bits;
volatile __ANSELA_bits_t __at(ANSELA_ADDR) ANSELA_bits;
volatile __ANSELB_bits_t __at(ANSELB_ADDR) ANSELB_bits;
volatile __ANSELD_bits_t __at(ANSELD_ADDR) ANSELD_bits;
volatile __ANSELE_bits_t __at(ANSELE_ADDR) ANSELE_bits;
volatile __APFCON_bits_t __at(APFCON_ADDR) APFCON_bits;
volatile __BAUDCON_bits_t __at(BAUDCON_ADDR) BAUDCON_bits;
volatile __BORCON_bits_t __at(BORCON_ADDR) BORCON_bits;
volatile __BSR_bits_t __at(BSR_ADDR) BSR_bits;
volatile __CCP1AS_bits_t __at(CCP1AS_ADDR) CCP1AS_bits;
volatile __CCP1CON_bits_t __at(CCP1CON_ADDR) CCP1CON_bits;
volatile __CCP2AS_bits_t __at(CCP2AS_ADDR) CCP2AS_bits;
volatile __CCP2CON_bits_t __at(CCP2CON_ADDR) CCP2CON_bits;
volatile __CCP3AS_bits_t __at(CCP3AS_ADDR) CCP3AS_bits;
volatile __CCP3CON_bits_t __at(CCP3CON_ADDR) CCP3CON_bits;
volatile __CCP4CON_bits_t __at(CCP4CON_ADDR) CCP4CON_bits;
volatile __CCP5CON_bits_t __at(CCP5CON_ADDR) CCP5CON_bits;
volatile __CCPTMRS0_bits_t __at(CCPTMRS0_ADDR) CCPTMRS0_bits;
volatile __CCPTMRS1_bits_t __at(CCPTMRS1_ADDR) CCPTMRS1_bits;
volatile __CM1CON0_bits_t __at(CM1CON0_ADDR) CM1CON0_bits;
volatile __CM1CON1_bits_t __at(CM1CON1_ADDR) CM1CON1_bits;
volatile __CM2CON0_bits_t __at(CM2CON0_ADDR) CM2CON0_bits;
volatile __CM2CON1_bits_t __at(CM2CON1_ADDR) CM2CON1_bits;
volatile __CMOUT_bits_t __at(CMOUT_ADDR) CMOUT_bits;
volatile __CPSCON0_bits_t __at(CPSCON0_ADDR) CPSCON0_bits;
volatile __CPSCON1_bits_t __at(CPSCON1_ADDR) CPSCON1_bits;
volatile __DACCON0_bits_t __at(DACCON0_ADDR) DACCON0_bits;
volatile __DACCON1_bits_t __at(DACCON1_ADDR) DACCON1_bits;
volatile __ECCP1AS_bits_t __at(ECCP1AS_ADDR) ECCP1AS_bits;
volatile __ECCP2AS_bits_t __at(ECCP2AS_ADDR) ECCP2AS_bits;
volatile __ECCP3AS_bits_t __at(ECCP3AS_ADDR) ECCP3AS_bits;
volatile __EECON1_bits_t __at(EECON1_ADDR) EECON1_bits;
volatile __FVRCON_bits_t __at(FVRCON_ADDR) FVRCON_bits;
volatile __INTCON_bits_t __at(INTCON_ADDR) INTCON_bits;
volatile __IOCBF_bits_t __at(IOCBF_ADDR) IOCBF_bits;
volatile __IOCBN_bits_t __at(IOCBN_ADDR) IOCBN_bits;
volatile __IOCBP_bits_t __at(IOCBP_ADDR) IOCBP_bits;
volatile __LATA_bits_t __at(LATA_ADDR) LATA_bits;
volatile __LATB_bits_t __at(LATB_ADDR) LATB_bits;
volatile __LATC_bits_t __at(LATC_ADDR) LATC_bits;
volatile __LATD_bits_t __at(LATD_ADDR) LATD_bits;
volatile __LATE_bits_t __at(LATE_ADDR) LATE_bits;
volatile __LCDCON_bits_t __at(LCDCON_ADDR) LCDCON_bits;
volatile __LCDCST_bits_t __at(LCDCST_ADDR) LCDCST_bits;
volatile __LCDDATA0_bits_t __at(LCDDATA0_ADDR) LCDDATA0_bits;
volatile __LCDDATA1_bits_t __at(LCDDATA1_ADDR) LCDDATA1_bits;
volatile __LCDDATA10_bits_t __at(LCDDATA10_ADDR) LCDDATA10_bits;
volatile __LCDDATA11_bits_t __at(LCDDATA11_ADDR) LCDDATA11_bits;
volatile __LCDDATA2_bits_t __at(LCDDATA2_ADDR) LCDDATA2_bits;
volatile __LCDDATA3_bits_t __at(LCDDATA3_ADDR) LCDDATA3_bits;
volatile __LCDDATA4_bits_t __at(LCDDATA4_ADDR) LCDDATA4_bits;
volatile __LCDDATA5_bits_t __at(LCDDATA5_ADDR) LCDDATA5_bits;
volatile __LCDDATA6_bits_t __at(LCDDATA6_ADDR) LCDDATA6_bits;
volatile __LCDDATA7_bits_t __at(LCDDATA7_ADDR) LCDDATA7_bits;
volatile __LCDDATA8_bits_t __at(LCDDATA8_ADDR) LCDDATA8_bits;
volatile __LCDDATA9_bits_t __at(LCDDATA9_ADDR) LCDDATA9_bits;
volatile __LCDPS_bits_t __at(LCDPS_ADDR) LCDPS_bits;
volatile __LCDREF_bits_t __at(LCDREF_ADDR) LCDREF_bits;
volatile __LCDRL_bits_t __at(LCDRL_ADDR) LCDRL_bits;
volatile __LCDSE0_bits_t __at(LCDSE0_ADDR) LCDSE0_bits;
volatile __LCDSE1_bits_t __at(LCDSE1_ADDR) LCDSE1_bits;
volatile __LCDSE2_bits_t __at(LCDSE2_ADDR) LCDSE2_bits;
volatile __OPTION_REG_bits_t __at(OPTION_REG_ADDR) OPTION_REG_bits;
volatile __OSCCON_bits_t __at(OSCCON_ADDR) OSCCON_bits;
volatile __OSCSTAT_bits_t __at(OSCSTAT_ADDR) OSCSTAT_bits;
volatile __OSCTUNE_bits_t __at(OSCTUNE_ADDR) OSCTUNE_bits;
volatile __PCON_bits_t __at(PCON_ADDR) PCON_bits;
volatile __PIE1_bits_t __at(PIE1_ADDR) PIE1_bits;
volatile __PIE2_bits_t __at(PIE2_ADDR) PIE2_bits;
volatile __PIE3_bits_t __at(PIE3_ADDR) PIE3_bits;
volatile __PIR1_bits_t __at(PIR1_ADDR) PIR1_bits;
volatile __PIR2_bits_t __at(PIR2_ADDR) PIR2_bits;
volatile __PIR3_bits_t __at(PIR3_ADDR) PIR3_bits;
volatile __PORTA_bits_t __at(PORTA_ADDR) PORTA_bits;
volatile __PORTB_bits_t __at(PORTB_ADDR) PORTB_bits;
volatile __PORTC_bits_t __at(PORTC_ADDR) PORTC_bits;
volatile __PORTD_bits_t __at(PORTD_ADDR) PORTD_bits;
volatile __PORTE_bits_t __at(PORTE_ADDR) PORTE_bits;
volatile __PSTR1CON_bits_t __at(PSTR1CON_ADDR) PSTR1CON_bits;
volatile __PSTR2CON_bits_t __at(PSTR2CON_ADDR) PSTR2CON_bits;
volatile __PSTR3CON_bits_t __at(PSTR3CON_ADDR) PSTR3CON_bits;
volatile __PWM1CON_bits_t __at(PWM1CON_ADDR) PWM1CON_bits;
volatile __PWM2CON_bits_t __at(PWM2CON_ADDR) PWM2CON_bits;
volatile __PWM3CON_bits_t __at(PWM3CON_ADDR) PWM3CON_bits;
volatile __RCSTA_bits_t __at(RCSTA_ADDR) RCSTA_bits;
volatile __SRCON0_bits_t __at(SRCON0_ADDR) SRCON0_bits;
volatile __SRCON1_bits_t __at(SRCON1_ADDR) SRCON1_bits;
volatile __SSPCON_bits_t __at(SSPCON_ADDR) SSPCON_bits;
volatile __SSPCON1_bits_t __at(SSPCON1_ADDR) SSPCON1_bits;
volatile __SSPCON2_bits_t __at(SSPCON2_ADDR) SSPCON2_bits;
volatile __SSPCON3_bits_t __at(SSPCON3_ADDR) SSPCON3_bits;
volatile __SSPSTAT_bits_t __at(SSPSTAT_ADDR) SSPSTAT_bits;
volatile __STATUS_bits_t __at(STATUS_ADDR) STATUS_bits;
volatile __STATUS_SHAD_bits_t __at(STATUS_SHAD_ADDR) STATUS_SHAD_bits;
volatile __T1CON_bits_t __at(T1CON_ADDR) T1CON_bits;
volatile __T1GCON_bits_t __at(T1GCON_ADDR) T1GCON_bits;
volatile __T2CON_bits_t __at(T2CON_ADDR) T2CON_bits;
volatile __T4CON_bits_t __at(T4CON_ADDR) T4CON_bits;
volatile __T6CON_bits_t __at(T6CON_ADDR) T6CON_bits;
volatile __TRISA_bits_t __at(TRISA_ADDR) TRISA_bits;
volatile __TRISB_bits_t __at(TRISB_ADDR) TRISB_bits;
volatile __TRISC_bits_t __at(TRISC_ADDR) TRISC_bits;
volatile __TRISD_bits_t __at(TRISD_ADDR) TRISD_bits;
volatile __TRISE_bits_t __at(TRISE_ADDR) TRISE_bits;
volatile __TXSTA_bits_t __at(TXSTA_ADDR) TXSTA_bits;
volatile __WDTCON_bits_t __at(WDTCON_ADDR) WDTCON_bits;
volatile __WPUB_bits_t __at(WPUB_ADDR) WPUB_bits;
volatile __WPUE_bits_t __at(WPUE_ADDR) WPUE_bits;
