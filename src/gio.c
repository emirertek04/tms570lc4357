#include "gio.h"
#include "tms570lc4357.h"

static GIO_PORT_TypeDef* get_port(gio_port_t port) {
    return (port == GIO_PORT_A) ? &(GIO->PORTA) : &(GIO->PORTB);
}

void gio_init(void) {
    /* GCR0 register bit 0 = 1: GIO modülünü reset durumundan çıkar */
    GIO->GCR0 = 1U;
}

void gio_set_direction(gio_port_t port, uint32_t pin, gio_dir_t dir) {
    GIO_PORT_TypeDef *p = get_port(port);
    if (dir == GIO_DIR_OUTPUT) {
        p->DIR |= (1U << pin);
    } else {
        p->DIR &= ~(1U << pin);
    }
}

void gio_write_pin(gio_port_t port, uint32_t pin, gio_state_t state) {
    GIO_PORT_TypeDef *p = get_port(port);
    if (state == GIO_PIN_SET) {
        p->DSET = (1U << pin);
    } else {
        p->DCLR = (1U << pin);
    }
}

void gio_toggle_pin(gio_port_t port, uint32_t pin) {
    GIO_PORT_TypeDef *p = get_port(port);
    if ((p->DOUT & (1U << pin)) != 0U) {
        p->DCLR = (1U << pin);
    } else {
        p->DSET = (1U << pin);
    }
}

gio_state_t gio_read_pin(gio_port_t port, uint32_t pin) {
    GIO_PORT_TypeDef *p = get_port(port);
    return ((p->DIN & (1U << pin)) != 0U) ? GIO_PIN_SET : GIO_PIN_RESET;
}