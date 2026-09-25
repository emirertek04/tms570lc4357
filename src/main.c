#include "tms570lc4357.h"
#include "system.h"
#include "gio.h"

/* LAUNCHXL2-570LC43 için Doğru LED Pinleri */
#define LED_PORT    GIO_PORT_B
#define LED2_PIN    6U   /* Kart üzerindeki D4 / LED2 */
#define LED3_PIN    7U   /* Kart üzerindeki D5 / LED3 */

static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__ volatile("nop");
    }
}

int main(void) {
    /* 1. GIO Modülünü Resetten Çıkar */
    *((volatile unsigned int *)0xFFF7BC00) = 1U;

    /* 2. GIOB_6 (LED2) ve GIOB_7 (LED3) Pinlerini Çıkış (Output) Yap */
    *((volatile unsigned int *)0xFFF7BC54) = (1U << 6) | (1U << 7);

    /* 3. KESİN TEST: Birini HIGH, diğerini LOW yap */
    /* Eğer devre Active-High ise LED2 (GIOB_6) yanar. */
    *((volatile unsigned int *)0xFFF7BC60) = (1U << 6); // GIOB_6 DSET (Lojik 1)
    
    /* Eğer devre Active-Low ise LED3 (GIOB_7) yanar. */
    *((volatile unsigned int *)0xFFF7BC64) = (1U << 7); // GIOB_7 DCLR (Lojik 0)

    /* Sabit bekle */
    while (1) {
    }

    return 0;
}

