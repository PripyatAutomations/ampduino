all: world
PLATFORM = esp8266
#PLATFORM = esp32
ESP_CC := gcc
ESP_LD := gcc
ESP_CFLAGS := -Wall -pedantic
ESP_LDFLAGS :=

bin := esp-serial.elf
objs += main.o

world: ${bin}

clean:
	${RM} ${bin} ${objs}

distclean: clean

firmware-install:

esp-serial.elf: ${objs}
	${ESP_LD} ${ESP_LDFLAGS} -o $@ $^

%.o:%.c
	${ESP_CC} ${ESP_CFLAGS} -o $@ -c $<
