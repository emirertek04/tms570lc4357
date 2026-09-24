#ifndef GIO_H
#define GIO_H

#include <stdint.h>

typedef enum {
    GIO_PORT_A = 0,
    GIO_PORT_B = 1
} gio_port_t;

typedef enum {
    GIO_DIR_INPUT  = 0,
    GIO_DIR_OUTPUT = 1
} gio_dir_t;

typedef enum {
    GIO_PIN_RESET = 0,
    GIO_PIN_SET   = 1
} gio_state_t;

void        gio_init(void);
void        gio_set_direction(gio_port_t port, uint32_t pin, gio_dir_t dir);
void        gio_write_pin(gio_port_t port, uint32_t pin, gio_state_t state);
void        gio_toggle_pin(gio_port_t port, uint32_t pin);
gio_state_t gio_read_pin(gio_port_t port, uint32_t pin);

#endif