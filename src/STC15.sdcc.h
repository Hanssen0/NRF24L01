#ifndef SRC_STC15_H_
#define SRC_STC15_H_

__sfr __at (0xE0) ACC;
__sfr __at (0xF0) B;
#define kAddressPSW 0xD0
__sfr __at (kAddressPSW) PSW;
__sbit __at (kAddressPSW^7) CY;
__sbit __at (kAddressPSW^6) AC;
__sbit __at (kAddressPSW^5) F0;
__sbit __at (kAddressPSW^4) RS1;
__sbit __at (kAddressPSW^3) RS0;
__sbit __at (kAddressPSW^2) OV;
__sbit __at (kAddressPSW^0) P;
__sfr __at (0x81) SP;
__sfr __at (0x82) DPL;
__sfr __at (0x83) DPH;

#define kAddressP0 0x80
__sfr __at (kAddressP0) P0;
__sbit __at (kAddressP0^0) P00;
__sbit __at (kAddressP0^1) P01;
__sbit __at (kAddressP0^2) P02;
__sbit __at (kAddressP0^3) P03;
__sbit __at (kAddressP0^4) P04;
__sbit __at (kAddressP0^5) P05;
__sbit __at (kAddressP0^6) P06;
__sbit __at (kAddressP0^7) P07;

#define kAddressP1 0x90
__sfr __at (kAddressP1) P1;
__sbit __at (kAddressP1^0) P10;
__sbit __at (kAddressP1^1) P11;
__sbit __at (kAddressP1^2) P12;
__sbit __at (kAddressP1^3) P13;
__sbit __at (kAddressP1^4) P14;
__sbit __at (kAddressP1^5) P15;
__sbit __at (kAddressP1^6) P16;
__sbit __at (kAddressP1^7) P17;

#define kAddressP2 0xA0
__sfr __at (kAddressP2) P2;
__sbit __at (kAddressP2^0) P20;
__sbit __at (kAddressP2^1) P21;
__sbit __at (kAddressP2^2) P22;
__sbit __at (kAddressP2^3) P23;
__sbit __at (kAddressP2^4) P24;
__sbit __at (kAddressP2^5) P25;
__sbit __at (kAddressP2^6) P26;
__sbit __at (kAddressP2^7) P27;

#define kAddressP3 0xB0
__sfr __at (kAddressP3) P3;
__sbit __at (kAddressP3^0) P30;
__sbit __at (kAddressP3^1) P31;
__sbit __at (kAddressP3^2) P32;
__sbit __at (kAddressP3^3) P33;
__sbit __at (kAddressP3^4) P34;
__sbit __at (kAddressP3^5) P35;
__sbit __at (kAddressP3^6) P36;
__sbit __at (kAddressP3^7) P37;

#define kAddressP4 0xC0
__sfr __at (kAddressP4) P4;
__sbit __at (kAddressP4^0) P40;
__sbit __at (kAddressP4^1) P41;
__sbit __at (kAddressP4^2) P42;
__sbit __at (kAddressP4^3) P43;
__sbit __at (kAddressP4^4) P44;
__sbit __at (kAddressP4^5) P45;
__sbit __at (kAddressP4^6) P46;
__sbit __at (kAddressP4^7) P47;

#define kAddressP5 0xC8
__sfr __at (kAddressP5) P5;
__sbit __at (kAddressP5^0) P50;
__sbit __at (kAddressP5^1) P51;
__sbit __at (kAddressP5^2) P52;
__sbit __at (kAddressP5^3) P53;
__sbit __at (kAddressP5^4) P54;
__sbit __at (kAddressP5^5) P55;
__sbit __at (kAddressP5^6) P56;
__sbit __at (kAddressP5^7) P57;

#define kAddressP6 0xE8
__sfr __at (kAddressP6) P6;
__sbit __at (kAddressP6^0) P60;
__sbit __at (kAddressP6^1) P61;
__sbit __at (kAddressP6^2) P62;
__sbit __at (kAddressP6^3) P63;
__sbit __at (kAddressP6^4) P64;
__sbit __at (kAddressP6^5) P65;
__sbit __at (kAddressP6^6) P66;
__sbit __at (kAddressP6^7) P67;

#define kAddressP7 0xF8
__sfr __at (kAddressP7) P7;
__sbit __at (kAddressP7^0) P70;
__sbit __at (kAddressP7^1) P71;
__sbit __at (kAddressP7^2) P72;
__sbit __at (kAddressP7^3) P73;
__sbit __at (kAddressP7^4) P74;
__sbit __at (kAddressP7^5) P75;
__sbit __at (kAddressP7^6) P76;
__sbit __at (kAddressP7^7) P77;

__sfr __at (0x94) P0M0;
__sfr __at (0x93) P0M1;
__sfr __at (0x92) P1M0;
__sfr __at (0x91) P1M1;
__sfr __at (0x96) P2M0;
__sfr __at (0x95) P2M1;
__sfr __at (0xB2) P3M0;
__sfr __at (0xB1) P3M1;
__sfr __at (0xB4) P4M0;
__sfr __at (0xB3) P4M1;
__sfr __at (0xCA) P5M0;
__sfr __at (0xC9) P5M1;
__sfr __at (0xCC) P6M0;
__sfr __at (0xCB) P6M1;
__sfr __at (0xE2) P7M0;
__sfr __at (0xE1) P7M1;

__sfr __at (0x87) PCON;
__sfr __at (0x8E) AUXR;
__sfr __at (0xA2) AUXR1;
__sfr __at (0xA2) P_SW1;
__sfr __at (0x97) CLK_DIV;
__sfr __at (0xA1) BUS_SPEED;
__sfr __at (0x9D) P1ASF;
__sfr __at (0xBA) P_SW2;

#define kAddressIE 0xA8
__sfr __at (kAddressIE) IE;
__sbit __at (kAddressIE^7) EA;
__sbit __at (kAddressIE^6) ELVD;
__sbit __at (kAddressIE^5) ADC2;
__sbit __at (kAddressIE^4) ES;
__sbit __at (kAddressIE^3) ET1;
__sbit __at (kAddressIE^2) EX1;
__sbit __at (kAddressIE^1) ET0;
__sbit __at (kAddressIE^0) EX0;
#define kAddressIP 0xB8
__sfr __at (kAddressIP) IP;
__sbit __at (kAddressIP^7) PPCA;
__sbit __at (kAddressIP^6) PLVD;
__sbit __at (kAddressIP^5) PADC;
__sbit __at (kAddressIP^4) PS;
__sbit __at (kAddressIP^3) PT1;
__sbit __at (kAddressIP^2) PX1;
__sbit __at (kAddressIP^1) PT0;
__sbit __at (kAddressIP^0) PX0;
__sfr __at (0xAF) IE2;
__sfr __at (0xB5) IP2;
__sfr __at (0x8F) INT_CLKO;

#define kAddressTCON 0x88
__sfr __at (kAddressTCON) TCON;
__sbit __at (kAddressTCON^7) TF1;
__sbit __at (kAddressTCON^6) TR1;
__sbit __at (kAddressTCON^5) TF0;
__sbit __at (kAddressTCON^4) TR0;
__sbit __at (kAddressTCON^3) IE1;
__sbit __at (kAddressTCON^2) IT1;
__sbit __at (kAddressTCON^1) IE0;
__sbit __at (kAddressTCON^0) IT0;
__sfr __at (0x89) TMOD;
__sfr __at (0x8A) TL0;
__sfr __at (0x8B) TL1;
__sfr __at (0x8C) TH0;
__sfr __at (0x8D) TH1;
__sfr __at (0xD1) T4T3M;
__sfr __at (0xD1) T3T4M;
__sfr __at (0xD2) T4H;
__sfr __at (0xD3) T4L;
__sfr __at (0xD4) T3H;
__sfr __at (0xD5) T3L;
__sfr __at (0xD6) T2H;
__sfr __at (0xD7) T2L;
__sfr __at (0xAA) WKTCL;
__sfr __at (0xAB) WKTCH;
__sfr __at (0xC1) WDT_CONTR;

#define kAddressSCON 0x98
__sfr __at (kAddressSCON) SCON;
__sbit __at (kAddressSCON^7) SM0;
__sbit __at (kAddressSCON^6) SM1;
__sbit __at (kAddressSCON^5) SM2;
__sbit __at (kAddressSCON^4) REN;
__sbit __at (kAddressSCON^3) TB8;
__sbit __at (kAddressSCON^2) RB8;
__sbit __at (kAddressSCON^1) TI;
__sbit __at (kAddressSCON^0) RI;
__sfr __at (0x99) SBUF;
__sfr __at (0x9A) S2CON;
__sfr __at (0x9B) S2BUF;
__sfr __at (0xAC) S3CON;
__sfr __at (0xAD) S3BUF;
__sfr __at (0x84) S4CON;
__sfr __at (0x85) S4BUF;
__sfr __at (0xA9) SADDR;
__sfr __at (0xB9) SADEN;

__sfr __at (0xBC) ADC_CONTR;
__sfr __at (0xBD) ADC_RES;
__sfr __at (0xBE) ADC_RESL;

__sfr __at (0xCD) SPSTAT;
__sfr __at (0xCE) SPCTL;
__sfr __at (0xCF) SPDAT;

__sfr __at (0xC2) IAP_DATA;
__sfr __at (0xC3) IAP_ADDRH;
__sfr __at (0xC4) IAP_ADDRL;
__sfr __at (0xC5) IAP_CMD;
__sfr __at (0xC6) IAP_TRIG;
__sfr __at (0xC7) IAP_CONTR;

#define kAddressCCON 0xD8
__sfr __at (kAddressCCON) CCON;
__sbit __at (kAddressCCON^7) CF;
__sbit __at (kAddressCCON^6) CR;
__sbit __at (kAddressCCON^2) CCF2;
__sbit __at (kAddressCCON^1) CCF1;
__sbit __at (kAddressCCON^0) CCF0;
__sfr __at (0xD9) CMOD;
__sfr __at (0xE9) CL;
__sfr __at (0xF9) CH;
__sfr __at (0xDA) CCAPM0;
__sfr __at (0xDB) CCAPM1;
__sfr __at (0xDC) CCAPM2;
__sfr __at (0xEA) CCAP0L;
__sfr __at (0xEB) CCAP1L;
__sfr __at (0xEC) CCAP2L;
__sfr __at (0xF2) PCA_PWM0;
__sfr __at (0xF3) PCA_PWM1;
__sfr __at (0xF4) PCA_PWM2;
__sfr __at (0xFA) CCAP0H;
__sfr __at (0xFB) CCAP1H;
__sfr __at (0xFC) CCAP2H;

__sfr __at (0xE6) CMPCR1;
__sfr __at (0xE7) CMPCR2;

__sfr __at (0xf1) PWMCFG;
__sfr __at (0xf5) PWMCR;
__sfr __at (0xf6) PWMIF;
__sfr __at (0xf7) PWMFDCR;

#define PWMC (*(unsigned int volatile xdata *)0xfff0)
#define PWMCH (*(unsigned char volatile xdata *)0xfff0)
#define PWMCL (*(unsigned char volatile xdata *)0xfff1)
#define PWMCKS (*(unsigned char volatile xdata *)0xfff2)
#define PWM2T1 (*(unsigned int volatile xdata *)0xff00)
#define PWM2T1H (*(unsigned char volatile xdata *)0xff00)
#define PWM2T1L (*(unsigned char volatile xdata *)0xff01)
#define PWM2T2 (*(unsigned int volatile xdata *)0xff02)
#define PWM2T2H (*(unsigned char volatile xdata *)0xff02)
#define PWM2T2L (*(unsigned char volatile xdata *)0xff03)
#define PWM2CR (*(unsigned char volatile xdata *)0xff04)
#define PWM3T1 (*(unsigned int volatile xdata *)0xff10)
#define PWM3T1H (*(unsigned char volatile xdata *)0xff10)
#define PWM3T1L (*(unsigned char volatile xdata *)0xff11)
#define PWM3T2 (*(unsigned int volatile xdata *)0xff12)
#define PWM3T2H (*(unsigned char volatile xdata *)0xff12)
#define PWM3T2L (*(unsigned char volatile xdata *)0xff13)
#define PWM3CR (*(unsigned char volatile xdata *)0xff14)
#define PWM4T1 (*(unsigned int volatile xdata *)0xff20)
#define PWM4T1H (*(unsigned char volatile xdata *)0xff20)
#define PWM4T1L (*(unsigned char volatile xdata *)0xff21)
#define PWM4T2 (*(unsigned int volatile xdata *)0xff22)
#define PWM4T2H (*(unsigned char volatile xdata *)0xff22)
#define PWM4T2L (*(unsigned char volatile xdata *)0xff23)
#define PWM4CR (*(unsigned char volatile xdata *)0xff24)
#define PWM5T1 (*(unsigned int volatile xdata *)0xff30)
#define PWM5T1H (*(unsigned char volatile xdata *)0xff30)
#define PWM5T1L (*(unsigned char volatile xdata *)0xff31)
#define PWM5T2 (*(unsigned int volatile xdata *)0xff32)
#define PWM5T2H (*(unsigned char volatile xdata *)0xff32)
#define PWM5T2L (*(unsigned char volatile xdata *)0xff33)
#define PWM5CR (*(unsigned char volatile xdata *)0xff34)
#define PWM6T1 (*(unsigned int volatile xdata *)0xff40)
#define PWM6T1H (*(unsigned char volatile xdata *)0xff40)
#define PWM6T1L (*(unsigned char volatile xdata *)0xff41)
#define PWM6T2 (*(unsigned int volatile xdata *)0xff42)
#define PWM6T2H (*(unsigned char volatile xdata *)0xff42)
#define PWM6T2L (*(unsigned char volatile xdata *)0xff43)
#define PWM6CR (*(unsigned char volatile xdata *)0xff44)
#define PWM7T1 (*(unsigned int volatile xdata *)0xff50)
#define PWM7T1H (*(unsigned char volatile xdata *)0xff50)
#define PWM7T1L (*(unsigned char volatile xdata *)0xff51)
#define PWM7T2 (*(unsigned int volatile xdata *)0xff52)
#define PWM7T2H (*(unsigned char volatile xdata *)0xff52)
#define PWM7T2L (*(unsigned char volatile xdata *)0xff53)
#define PWM7CR (*(unsigned char volatile xdata *)0xff54)

#endif  // SRC_STC15_H_
