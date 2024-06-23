SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
mp3_tag_reader.exe: $(OBJ)
	gcc -o $@ $^
run: 
	make && ./mp3_tag_reader.exe 
clean:
	rm *.o *.exe

