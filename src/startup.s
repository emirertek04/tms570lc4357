 .syntax unified

    .cpu cortex-r5

    .arm


    .section .vectors, "ax"

    .global _vectors

    .type _vectors, %function

_vectors:

    b _reset

    b _undef_handler

    b _svc_handler

    b _prefetch_abort_handler

    b _data_abort_handler

    b .

    b _irq_handler

    b _fiq_handler


    .section .text

    .global _reset

    .type _reset, %function

_reset:

    /* Tüm kesmeleri maskele (IRQ ve FIQ kapat) */

    cpsid if


    /* ---------------------------------------------------------

     * 1. RAM ECC Donanımsal Başlatma (MINITGCR / MSINENA)

     * SYS1 Base: 0xFFFFFF00

     * --------------------------------------------------------- */

    ldr r0, =0xFFFFFF5C

    mov r1, #0xA

    str r1, [r0]             /* MINITGCR = 0xA */


    ldr r0, =0xFFFFFF60

    mov r1, #0x1

    str r1, [r0]             /* MSINENA = 0x1 */


    ldr r0, =0xFFFFFF68

_wait_ram_init:

    ldr r1, [r0]

    tst r1, #0x100           /* MSTCGSTAT[8] set mi? */

    beq _wait_ram_init


    ldr r0, =0xFFFFFF5C

    mov r1, #0x5

    str r1, [r0]             /* MINITGCR = 0x5 */


    /* ---------------------------------------------------------

     * 2. Stack Pointer Ataması

     * --------------------------------------------------------- */

    cps #0x13

    ldr sp, =_stack_top


    cps #0x1F

    ldr sp, =_stack_top


    /* ---------------------------------------------------------

     * 3. .data Segmentini Flash'tan RAM'e Kopyala

     * --------------------------------------------------------- */

    ldr r0, =_sdata

    ldr r1, =_edata

    ldr r2, =_sidata

1:

    cmp r0, r1

    ldrlt r3, [r2], #4

    strlt r3, [r0], #4

    blt 1b


    /* ---------------------------------------------------------

     * 4. .bss Segmentini Sıfırla

     * --------------------------------------------------------- */

    ldr r0, =__bss_start__

    ldr r1, =__bss_end__

    mov r2, #0

2:

    cmp r0, r1

    strlt r2, [r0], #4

    blt 2b


    /* ---------------------------------------------------------

     * 5. main'e Sıçra

     * --------------------------------------------------------- */

    bl main


_deadloop:

    b _deadloop


_undef_handler:

_svc_handler:

_prefetch_abort_handler:

_data_abort_handler:

_irq_handler:

_fiq_handler:

    b . 