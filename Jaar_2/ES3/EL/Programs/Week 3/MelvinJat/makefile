CC = arm-linux-gcc
CFLAGS = -O2 -Wall -Werror
LDFLAGS = -lusb-1.0
SOURCES = xpadtest.c 
TARGET = xboxcontroller

.PHONY: all clean

all: $(TARGET)

install: $(TARGET)
	scp $(TARGET) root@192.168.0.50:/home/School
	clear
	ssh root@192.168.0.50 -t /home/School/$(TARGET)

$(TARGET) : $(SOURCES) 
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS)
clean:
	@rm -rf $(TARGET) 
