
all:
	srec_cat firmware.hex -I optiboot.hex -I -o combined.hex -I
	avrdude -v -c avrisp -patmega328p -P/dev/ttyACM0 -b19200 -D -Uflash:w:combined.hex:i -e -u -U lock:w:0x3f:m -U efuse:w:0xFD:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m -U lock:w:0x2f:m
