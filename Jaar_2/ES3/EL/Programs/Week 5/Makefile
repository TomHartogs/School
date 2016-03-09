CXX = arm-linux-g++
CFLAGS = -O2 -Wall -Werror MessageQueue.cpp
LDFLAGS = -lusb-1.0 -lrt
SOURCES = ControllerReadDaemon.cpp Controller.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ControllerReadDaemon

.PHONY: all clean install

all: $(TARGET)

$(TARGET) : $(OBJECTS) 
	$(CXX) -o $@  $^ $(LDFLAGS) $(CFLAGS)

install: $(TARGET)
	scp $(TARGET) root@192.168.0.50:/home/School
	clear
	ssh root@192.168.0.50 -t "/home/School/$(TARGET)"
clean:
	@rm -rf $(TARGET) $(OBJECTS)
