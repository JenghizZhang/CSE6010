CC=gcc

TARGET=output

.PHONY: all run clean

all: $(TARGET)

$(TARGET): constructGraph.c constructGraph.h dijkstra.c dijkstra.h wordchains.c
	$(CC) -o $(TARGET) *.c

run:
	./$(TARGET) $(ARGS)

swap:
	./$(TARGET) $(ARGS) -swap

clean:
	rm -f $(TARGET)
