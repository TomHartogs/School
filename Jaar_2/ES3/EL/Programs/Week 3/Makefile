CXX = arm-linux-g++
CFLAGS = -O2 -Wall -Werror
LDFLAGS = -lusb-1.0
SOURCES = ControllerMain.cpp Controller.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = xbox360

.PHONY: all clean install

all: $(TARGET)

$(TARGET) : $(OBJECTS) 
	$(CXX) -o $@  $^ $(LDFLAGS) $(CFLAGS)

install: $(TARGET)
	scp $(TARGET) root@192.168.0.50:/home/School/

clean:
	@rm -rf $(TARGET) $(OBJECTS)
