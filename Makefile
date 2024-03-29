BUILD = ./build
PORT = /dev/ttyUSB0

BLUEPORT = /dev/blueled

.PHONY: combined.hex bootloader.hex application.hex

all: combined.hex
	cd $(BUILD)
	avrdude -v -c avrisp -patmega328p -P$(PORT) -b115200 -D -Uflash:w:$(BUILD)/combined.hex:i -e -u -U lock:w:0x3f:m -U efuse:w:0xFD:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m -U lock:w:0x2f:m

combined.hex: application.hex bootloader.hex
	@cat $(BUILD)/application.hex | awk '/^:00000001FF/ == 0' > $@
	@cat $(BUILD)/bootloader.hex >> $@
	mv $@ $(BUILD)

bootloader.hex: $(BUILD)
	git -C optiboot checkout master .
	git -C optiboot apply ../001-start-app-if-PD2-is-low.patch
	make -C optiboot/optiboot/bootloaders/optiboot atmega328
	cp optiboot/optiboot/bootloaders/optiboot/optiboot_atmega328.hex $(BUILD)/bootloader.hex

application.hex: $(BUILD)
	pio run -e wireless
	cp .pio/build/wireless/firmware.hex $(BUILD)/application.hex

analysis:
	cppcheck --enable=all src/*

sniff:
	interceptty $(BLUEPORT) /tmp/blueledish

$(BUILD):
	mkdir $(BUILD)
