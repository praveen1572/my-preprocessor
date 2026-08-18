CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic

TARGET = my_Preprocessor.exe
OBJS = main.o comments.o includes.o macros.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c preprocessor.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET) *.i