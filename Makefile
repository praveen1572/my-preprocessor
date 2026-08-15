CC = cc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
TARGET = my_Preprocessor
OBJS = main.o comments.o includes.o macros.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c preprocessor.h
	$(CC) $(CFLAGS) -c main.c

comments.o: comments.c preprocessor.h
	$(CC) $(CFLAGS) -c comments.c

includes.o: includes.c preprocessor.h
	$(CC) $(CFLAGS) -c includes.c

macros.o: macros.c preprocessor.h
	$(CC) $(CFLAGS) -c macros.c

clean:
	rm -f $(OBJS) $(TARGET) *.i
