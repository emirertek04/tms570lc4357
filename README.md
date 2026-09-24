tms570lc4357-baremetal/
├── include/
│   ├── tms570lc4357.h       # Register base adresleri ve struct tanımları
│   ├── system.h             # SYS (Saat / Güç / PLL) prototipleri
│   └── gio.h                # GIO sürücü prototipleri
├── src/
│   ├── startup.s            # Vektör tablosu, stack pointer ve C runtime init
│   ├── system.c             # PLL ve clock routing (RCC muadili)
│   ├── gio.c                # GIO register konfigürasyonları
│   └── main.c               # Uygulama döngüsü
├── linker/
│   └── tms570lc4357.ld      # Flash ve SRAM bellek yerleşimi (Flash: 0x00000000, RAM: 0x08000000)
├── Makefile                 # arm-none-eabi-gcc derleme akışı
└── README.md
