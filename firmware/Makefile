
CC=avr-gcc
PROGRAMMER=usbtiny
CPU=attiny85

SOURCE=tree_blink.c
OBJECT=tree_blink.o
ELF=tree_blink.elf
HEX=tree_blink.hex

object: ${SOURCE}
	${CC} -mmcu=${CPU} -c ${SOURCE}

elf: object
	${CC} -mmcu=${CPU} -o ${ELF} ${OBJECT}

hex: elf
	avr-objcopy -j .text -j .data -O ihex ${ELF} ${HEX}

avrdude: hex
	avrdude -c ${PROGRAMMER} -p ${CPU} -U flash:w:${HEX}:i

readfuse:
	avrdude -c ${PROGRAMMER} -p ${CPU} -U lfuse:r:-:h 2> /dev/null
	avrdude -c ${PROGRAMMER} -p ${CPU} -U hfuse:r:-:h 2> /dev/null
	avrdude -c ${PROGRAMMER} -p ${CPU} -U efuse:r:-:h 2> /dev/null
