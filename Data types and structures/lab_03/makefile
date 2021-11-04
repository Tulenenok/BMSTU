CC := gcc
CFLAGS := -std=c99

O_FILES := index_matrix.o matrix.o modes.o node.o sparse_matrix.o take_time.o tools.o
SRC_FILES := index_matrix.c matrix.c modes.c node.c sparse_matrix.c take_time.c tools.c

app.exe : $(O_FILES) main.o
	$(CC) -o $@ $^ $(CFLAGS)
	
tools.o : src/tools.c
	$(CC) $(CFLAGS) -c $<
	
node.o : src/node.c
	$(CC) $(CFLAGS) -c $<
	
matrix.o : src/matrix.c
	$(CC) $(CFLAGS) -c $<
	
index_matrix.o : src/index_matrix.c
	$(CC) $(CFLAGS) -c $<
	
sparse_matrix.o : src/sparse_matrix.c src/node.c src/tools.c
	$(CC) $(CFLAGS) -c $<
	
take_time.o : src/take_time.c
	$(CC) $(CFLAGS) -c $<
	
modes.o : src/modes.c
	$(CC) $(CFLAGS) -c $<
	
main.o : main.c
	$(CC) $(CFLAGS) -c $<
	
.PHONY : clean debug release

clean :
	rm -f *.o *.exe *.d *.gcno *.gcov *.gcda
	cd src && rm -f *.o *.exe *.d *.gcno *gcov *gcda

release : CFLAGS += -DNDEBUG -g0
release : app.exe

debug : CFLAGS += -g3 --coverage
debug : app.exe
	