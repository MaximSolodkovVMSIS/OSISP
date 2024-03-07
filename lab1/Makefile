CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Wno-deprecated-declarations

TARGET = lab1
SOURCE = 1lab.c 

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
