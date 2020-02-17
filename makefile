OBJ := $(patsubst %.c, %.o, $(wildcard *.c))
mp3_tag_reader_editor : $(OBJ)
	gcc -Wall -o $@ $^
clean:
	rm *.o *.exe
