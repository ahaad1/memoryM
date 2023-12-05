CC     = g++
CFLAGS = -Wall -g
RM     = rm -f

default: all

all: myprogram

myprogram: 03_2_02main.cpp
	$(CC) -fsanitize=address -fdiagnostics-color=always $(CFLAGS) -o 03_2_02main 03_2_02main.cpp 
	./03_2_02main  
	$(RM) 03_2_02main 
	$(CC) -o 03_2_02main 03_2_02main.cpp 
	valgrind --leak-check=full --show-leak-kinds=all ./03_2_02main
