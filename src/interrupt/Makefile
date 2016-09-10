PROJ   = interrupt
CC     = msp430-gcc
MCU    = msp430g2231
TARGET = main

CFLAGS  = -Os -g -Wall -mmcu=$(MCU)
LDFLAGS = -g -mmcu=$(MCU)

OBJS = $(TARGET).o

all:$(OBJS)
	@echo linking: $(PROJ).elf
	$(CC) $(LDFLAGS) -o $(PROJ).elf $(OBJS)
	@echo "--== Size of firmware ==--"
	msp430-size $(PROJ).elf

%.o:%.c %.h
	@echo compiling file: $<
	$(CC) $(CFLAGS) -c $<

clean:
	@echo cleaning $<
	rm -rf $(PROJ).elf $(OBJS)

flash: all
	mspdebug rf2500 'erase' 'load $(PROJ).elf' 'exit'
