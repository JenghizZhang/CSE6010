CC=gcc

TARGET=voting

.PHONY: all default detail clean

all: $(TARGET)

$(TARGET): voting.c methodPair1.c methodPair2.c header.h
	$(CC) voting.c methodPair1.c methodPair2.c -o $(TARGET) -g

default:
	./$(TARGET)

detail:
	./$(TARGET) d

clean:
	rm -f $(TARGET)
