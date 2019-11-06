CC = arm-linux-gcc
INC = -I./include
 
TARGET=./bin/main
 
SRC=$(wildcard ./src/*.c)
 
OBJ=$(patsubst %.c, %.o, $(SRC))
 
$(TARGET): $(OBJ)
	$(CC)  -o $@ $^ -lm -std=c99
 
$(OBJ):%.o: %.c
	$(CC)  $(INC) -o $@ -c $< -std=c99
 
clean:
	rm -f ./src/*.o
	rm -f $(TARGET)
