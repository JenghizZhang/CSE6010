CC=gcc

TARGET=gates

.PHONY: all insertion heap quick clean

all: $(TARGET)

$(TARGET): gates.c common.h
	$(CC) gates.c -o $(TARGET) -g

insertion:
	./$(TARGET) i

heap:
	./$(TARGET) h

quick:
	./$(TARGET) q

clean:
	rm -f $(TARGET)
