#include "system.h"
#include "tms570lc4357.h"

/* 
 * IOMM Pin Multiplexing Ayarları
 * LaunchXL2-570LC43 üzerinde LED1 -> GIOB[1], LED2 -> GIOB[2] pinindedir.
 * Bu pinleri IOMM üzerinden aktif etmemiz gerekir.
 */
void pinmux_init(void) {
    /* 1. IOMM Kilidini Aç */
    IOMM->KICKER0 = 0x83E70B13U;
    IOMM->KICKER1 = 0x95A4F1E0U;

    /* 
     * GIOB[1] ve GIOB[2] pinlerini bağla.
     * PINMMR7: Bit 8-15 (GIOB[1]), Bit 16-23 (GIOB[2])
     * 1 << 8 ve 1 << 16 fonksiyonu GIO modülünü pinlere yönlendirir.
     */
    IOMM->PINMMR[7] &= ~((0xFFU << 8) | (0xFFU << 16));
    IOMM->PINMMR[7] |=  ((0x01U << 8) | (0x01U << 16));

    /* 2. IOMM Kilidini Kapat */
    IOMM->KICKER0 = 0x00000000U;
    IOMM->KICKER1 = 0x00000000U;
}

void system_init(void) {
    /* -------------------------------------------------------------
     * 1. FLASH WAIT STATES
     * 300 MHz için en az 3 wait-state ve adres pipeline (ASWSTEN) şarttır.
     * FRDCNTL: [11:8] = RWAIT (3), [0] = ASWSTEN (1) -> 0x00000301
     * ------------------------------------------------------------- */
    FLASH_WRAPPER->FRDCNTL = (3U << 8) | (1U << 0);

    /* -------------------------------------------------------------
     * 2. OSCILLATOR AKTİVASYONU
     * OSCIN (16 MHz) aç ve kararlı olmasını bekle
     * ------------------------------------------------------------- */
    SYS1->CSDISCLR = (1U << 0); // OSCIN enable (Bit 0)
    while ((SYS1->CSVSTAT & (1U << 0)) == 0U) {
        // Kararlı olana kadar bekle
    }

    /* -------------------------------------------------------------
     * 3. PLL1 YAPILANDIRMASI (Target: 300 MHz)
     * Formül: f_VCO = (f_OSC / NR) * NF
     *         f_PLL = f_VCO / (OD * R)
     * OSCIN = 16 MHz
     * NR = 6  (PLLCTL1[29:24] = 5)  -> 16 / 6 = 2.66 MHz
     * NF = 225 (PLLCTL1[15:8] = 224) -> 2.66 * 225 = 600 MHz VCO
     * OD = 2  (PLLCTL2[13:9] = 1)   -> 600 / 2 = 300 MHz PLL Output
     * R  = 1  (PLLCTL2[4:0] = 0)
     * ------------------------------------------------------------- */
    SYS1->PLLCTL1 = (5U << 24)        // NR = 6
                  | (0U << 16)        // Ref Clock Divider
                  | (224U << 8);      // NF = 225

    SYS1->PLLCTL2 = (0x0U << 24)      // FM Range
                  | (1U << 9)         // ODPLL = 2
                  | (0U << 0);        // R = 1

    /* PLL1'i aç */
    SYS1->CSDISCLR = (1U << 1);

    /* PLL'in kilitlenmesini (Slip / Lock) bekle */
    while ((SYS1->CSVSTAT & (1U << 1)) == 0U) {
        // PLL kilitlenene kadar bekle
    }

    /* -------------------------------------------------------------
     * 4. SAAT BÖLÜCÜLERİ (CLKCNTL)
     * HCLK = 150 MHz (GCLK / 2)
     * VCLK = 75 MHz  (VCLK ratio = 1 -> HCLK / 2)
     * ------------------------------------------------------------- */
    SYS1->CLKCNTL = (1U << 16)        // VCLK = HCLK / 2
                  | (1U << 24);       // VCLK2 = HCLK / 2

    /* -------------------------------------------------------------
     * 5. SAAT KAYNAĞI SEÇİMİ (GHVSRC)
     * GCLK, HCLK, VCLK kaynaklarını PLL1 (Kaynak 1) yap
     * ------------------------------------------------------------- */
    SYS1->GHVSRC = (1U << 24)         // HCLK  = PLL1
                 | (1U << 16)         // GCLK  = PLL1
                 | (1U << 0);         // VCLK  = PLL1

    /* Domain saatlerini serbest bırak */
    SYS1->CDDISCLR = (1U << 0) | (1U << 1) | (1U << 2);

    /* Pin multiplexing'i tamamla */
    pinmux_init();
}