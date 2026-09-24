#ifndef TMS570LC4357_H
#define TMS570LC4357_H

#include <stdint.h>

#define __IO volatile

/* ========================================================================= */
/* System Controller 1 (SYS1) - 0xFFFFFF00                                  */
/* ========================================================================= */
typedef struct {
    __IO uint32_t SYSPC1;      // 0x00
    __IO uint32_t SYSPC2;      // 0x04
    __IO uint32_t SYSPC3;      // 0x08
    __IO uint32_t SYSPC4;      // 0x0C
    __IO uint32_t SYSPC5;      // 0x10
    __IO uint32_t SYSPC6;      // 0x14
    __IO uint32_t SYSPC7;      // 0x18
    __IO uint32_t SYSPC8;      // 0x1C
    __IO uint32_t SYSPC9;      // 0x20
    uint32_t      RESERVED0[3];
    __IO uint32_t CSDIS;       // 0x30: Clock Source Disable
    __IO uint32_t CSDISSET;    // 0x34: Clock Source Disable Set
    __IO uint32_t CSDISCLR;    // 0x38: Clock Source Disable Clear
    __IO uint32_t CDDIS;       // 0x3C: Clock Domain Disable
    __IO uint32_t CDDISSET;    // 0x40
    __IO uint32_t CDDISCLR;    // 0x44
    __IO uint32_t GHVSRC;      // 0x48: GCLK, HCLK, VCLK Source
    __IO uint32_t VCLKASRC;    // 0x4C: VCLKA Source
    __IO uint32_t RCLKSRC;     // 0x50: RTI Clock Source
    __IO uint32_t CSVSTAT;     // 0x54: Clock Source Valid Status
    __IO uint32_t MSTGCR;      // 0x58: Memory Self-Test Global Control
    __IO uint32_t MINITGCR;    // 0x5C: Memory Hardware Initialization Control
    __IO uint32_t MSINENA;     // 0x60: Memory Hardware Initialization Enable
    uint32_t      RESERVED1[1];
    __IO uint32_t MSTCGSTAT;   // 0x68: Memory Self-Test Global Status
    uint32_t      RESERVED2[1];
    __IO uint32_t PLLCTL1;     // 0x70: PLL Control 1
    __IO uint32_t PLLCTL2;     // 0x74: PLL Control 2
    __IO uint32_t SYSPC10;     // 0x78
    __IO uint32_t DIEIDL;      // 0x7C
    __IO uint32_t DIEIDH;      // 0x80
    __IO uint32_t VRCTL;       // 0x84
    uint32_t      RESERVED3[1];
    __IO uint32_t CLKTEST;     // 0x8C
    __IO uint32_t DFTSTCEN;    // 0x90
    __IO uint32_t DFTSTCREG1;  // 0x94
    __IO uint32_t DFTSTCREG2;  // 0x98
    uint32_t      RESERVED4[1];
    __IO uint32_t GPREG1;      // 0xA0
    __IO uint32_t BMMCR1;      // 0xA4
    uint32_t      RESERVED5[1];
    __IO uint32_t BMMCR2;      // 0xAC
    __IO uint32_t CPURSTCR;    // 0xB0
    __IO uint32_t CLKCNTL;     // 0xD0: Clock Control (VCLK Dividers)
} SYS1_TypeDef;

#define SYS1 ((SYS1_TypeDef *)0xFFFFFF00U)

/* ========================================================================= */
/* System Controller 2 (SYS2) - 0xFFFFE100                                  */
/* ========================================================================= */
typedef struct {
    __IO uint32_t PLLCTL3;     // 0x00: PLL2 Control
    uint32_t      RESERVED0[7];
    __IO uint32_t STCCLKDIV;   // 0x20
    uint32_t      RESERVED1[6];
    __IO uint32_t CLK2CNTRL;   // 0x3C: VCLK3/VCLK4 divider
} SYS2_TypeDef;

#define SYS2 ((SYS2_TypeDef *)0xFFFFE100U)

/* ========================================================================= */
/* Flash Wrapper Core Registers - 0xFFF87000                                 */
/* ========================================================================= */
typedef struct {
    __IO uint32_t FRDCNTL;     // 0x00: Flash Read Control (Wait States)
    uint32_t      RESERVED0[63];
    __IO uint32_t FEDACCTRL1;  // 0x100: Flash ECC Control
} FLASH_TypeDef;

#define FLASH_WRAPPER ((FLASH_TypeDef *)0xFFF87000U)

/* ========================================================================= */
/* IOMM (Pin Multiplexing and Kicker) - 0xFFFFEA00                          */
/* ========================================================================= */
typedef struct {
    __IO uint32_t KICKER0;     // 0x00: Unlock Key 0 (0x83E70B13)
    __IO uint32_t KICKER1;     // 0x04: Unlock Key 1 (0x95A4F1E0)
    uint32_t      RESERVED0[14];
    __IO uint32_t PINMMR[32];  // 0x40 - 0xBC: Pin Mux Registers
} IOMM_TypeDef;

#define IOMM ((IOMM_TypeDef *)0xFFFFEA00U)

/* ========================================================================= */
/* GIO Controller - 0xFFF7BC00                                              */
/* ========================================================================= */
typedef struct {
    __IO uint32_t DIR;         // 0x00: Data Direction (0=In, 1=Out)
    __IO uint32_t DIN;         // 0x04: Data Input
    __IO uint32_t DOUT;        // 0x08: Data Output
    __IO uint32_t DSET;        // 0x0C: Bit Set
    __IO uint32_t DCLR;        // 0x10: Bit Clear
    __IO uint32_t PDR;         // 0x14: Open Drain
    __IO uint32_t PULDIS;      // 0x18: Pull-up/down Disable
    __IO uint32_t PSL;         // 0x1C: Pull Select (0=Down, 1=Up)
} GIO_PORT_TypeDef;

typedef struct {
    __IO uint32_t GCR0;        // 0x00: Global Control Register
    __IO uint32_t PWDN;        // 0x04: Power Down
    __IO uint32_t INTDET;      // 0x08
    __IO uint32_t POL;         // 0x0C
    __IO uint32_t ENASET;      // 0x10
    __IO uint32_t ENACLR;      // 0x14
    __IO uint32_t LVLSET;      // 0x18
    __IO uint32_t LVLCLR;      // 0x1C
    __IO uint32_t FLG;         // 0x20
    __IO uint32_t OFF1;        // 0x24
    __IO uint32_t OFF2;        // 0x28
    __IO uint32_t EMU1;        // 0x2C
    __IO uint32_t EMU2;        // 0x30
    GIO_PORT_TypeDef PORTA;    // 0x34 - 0x50
    GIO_PORT_TypeDef PORTB;    // 0x54 - 0x70
} GIO_TypeDef;

#define GIO ((GIO_TypeDef *)0xFFF7BC00U)

#endif