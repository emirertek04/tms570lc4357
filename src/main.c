#include "tms570lc4357.h"
#include "system.h"
#include "gio.h"

#define LED_PORT    GIO_PORT_B
#define LED_PIN     1U

static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__ volatile("nop");
    }
}

int main(void) {
    system_init();

    gio_init();
    gio_set_direction(LED_PORT, LED_PIN, GIO_DIR_OUTPUT);

    while (1) {
        gio_toggle_pin(LED_PORT, LED_PIN);
        delay(3000000);
    }

    return 0;
}