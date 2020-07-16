OUTPUT_PATH = ./build/
SRC_PATH = ./src/
tx: $(SRC_PATH)main.sdcc.c $(SRC_PATH)STC15.sdcc.h $(OUTPUT_PATH)Timer.sdcc.rel $(OUTPUT_PATH)Wireless.sdcc.rel $(OUTPUT_PATH)aes.sdcc.rel $(OUTPUT_PATH)Logger.sdcc.rel $(OUTPUT_PATH)UART.sdcc.rel $(OUTPUT_PATH)Transmit.sdcc.rel
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) $(SRC_PATH)main.sdcc.c $(OUTPUT_PATH)aes.sdcc.rel $(OUTPUT_PATH)Logger.sdcc.rel $(OUTPUT_PATH)UART.sdcc.rel $(OUTPUT_PATH)Wireless.sdcc.rel $(OUTPUT_PATH)Transmit.sdcc.rel $(OUTPUT_PATH)Timer.sdcc.rel
rx: $(SRC_PATH)main_rx.sdcc.c $(SRC_PATH)STC15.sdcc.h $(OUTPUT_PATH)Timer.sdcc.rel $(OUTPUT_PATH)Wireless.sdcc.rel $(OUTPUT_PATH)aes.sdcc.rel $(OUTPUT_PATH)Logger.sdcc.rel $(OUTPUT_PATH)UART.sdcc.rel $(OUTPUT_PATH)Transmit.sdcc.rel
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) $(SRC_PATH)main_rx.sdcc.c $(OUTPUT_PATH)aes.sdcc.rel $(OUTPUT_PATH)Logger.sdcc.rel $(OUTPUT_PATH)UART.sdcc.rel $(OUTPUT_PATH)Wireless.sdcc.rel $(OUTPUT_PATH)Transmit.sdcc.rel $(OUTPUT_PATH)Timer.sdcc.rel
$(OUTPUT_PATH)Transmit.sdcc.rel: $(SRC_PATH)Transmit.sdcc.h $(SRC_PATH)Transmit.sdcc.c
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)Transmit.sdcc.c

$(OUTPUT_PATH)aes.sdcc.rel: $(SRC_PATH)aes.sdcc.h $(SRC_PATH)aes.sdcc.c
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)aes.sdcc.c

$(OUTPUT_PATH)Logger.sdcc.rel: $(SRC_PATH)Logger.sdcc.h $(SRC_PATH)Logger.sdcc.c $(OUTPUT_PATH)UART.sdcc.rel
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)Logger.sdcc.c

$(OUTPUT_PATH)UART.sdcc.rel: $(SRC_PATH)UART.sdcc.h $(SRC_PATH)STC15.sdcc.h $(SRC_PATH)UART.sdcc.c
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)UART.sdcc.c

$(OUTPUT_PATH)Wireless.sdcc.rel: $(SRC_PATH)Wireless.sdcc.h $(SRC_PATH)STC15.sdcc.h $(OUTPUT_PATH)Timer.sdcc.rel $(SRC_PATH)Wireless.sdcc.c
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)Wireless.sdcc.c

$(OUTPUT_PATH)Timer.sdcc.rel: $(SRC_PATH)Timer.sdcc.h $(SRC_PATH)Timer.sdcc.c
	mkdir -p $(OUTPUT_PATH)
	sdcc --std-sdcc99 --stack-auto -o $(OUTPUT_PATH) -c $(SRC_PATH)Timer.sdcc.c

flash:
	sudo stcgal $(OUTPUT_PATH)main.sdcc.ihx
flash_rx:
	sudo stcgal $(OUTPUT_PATH)main_rx.sdcc.ihx
flash_trim:
	sudo stcgal -t 20000 $(OUTPUT_PATH)main.sdcc.ihx
flash_rx_trim:
	sudo stcgal -t 20000 $(OUTPUT_PATH)main_rx.sdcc.ihx
