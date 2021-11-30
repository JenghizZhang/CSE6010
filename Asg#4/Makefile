CC=gcc

TARGET=integral

.PHONY: all run clean

all: $(TARGET)

$(TARGET): integral.c
	$(CC) -o $(TARGET) -fopenmp integral.c -lm

run:
	time ./$(TARGET)

clean:
	rm -f $(TARGET)
