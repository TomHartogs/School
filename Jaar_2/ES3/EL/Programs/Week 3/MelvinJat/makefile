CC = arm-linux-gcc
CFLAGS = -O2 -Wall -Werror
LDFLAGS = -lusb-1.0
SOURCES = xpadtest.c 
TARGET = xboxcontroller

.PHONY: all clean

all: $(TARGET)

install: $(TARGET)
	scp $(TARGET) root@10.0.0.42:/root

$(TARGET) : $(SOURCES) 
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS)
clean:
	@rm -rf $(TARGET) 
