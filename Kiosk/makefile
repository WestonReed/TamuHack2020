CPP = g++
CPPFLAGS = -g -Wall -pedantic
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
LDLIBS = -lnfc -lusb -lcurl -lncurses
VERSION = --std=c++2a
BINARY = kiosk


all: $(BINARY)

%.o: %.cpp %.h
	$(CPP) $(CPPFLAGS) $(VERSION) $(LDLIBS) -c $< -o $@

$(BINARY): driver.cpp nfc.cpp
	$(CPP) $(CPPFLAGS) $(VERSION) -o $(BINARY) driver.cpp nfc.cpp $(LDLIBS) $(CFLAGS)

clean:
	rm -rf *.o $(BINARY)
