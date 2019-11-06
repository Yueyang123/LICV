CC = arm-linux-gcc
INC = -I./include
 
TARGET=./bin/main
 
SRC=$(wildcard ./src/*.c)
 
OBJ=$(patsubst %.c, %.o, $(SRC))
 
$(TARGET): $(OBJ)
	$(CC)  -o $@ $^ -lm
 
$(OBJ):%.o: %.c
	$(CC)  $(INC) -o $@ -c $<
 
clean:
	rm -f ./src/*.o
	rm -f $(TARGET)
