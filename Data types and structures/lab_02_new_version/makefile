CC := gcc
CFLAGS := -std=c99

O_FILES := modes.o flats.o tools.o

app.exe : $(O_FILES) main.o
	$(CC) -o $@ $^ $(CFLAGS)
	
main.o : main.c src/modes.c src/flats.c
	$(CC) $(CFLAGS) -c $<
	
flats.o : src/flats.c inc/flats.h
	$(CC) $(CFLAGS) -c $<
	
modes.o : src/modes.c src/flats.c inc/flats.h inc/modes.h
	$(CC) $(CFLAGS) -c $<

tools.o : src/tools.c
	$(CC) $(CFLAGS) -c $<
	
.PHONY : clean debug release

clean :
	rm -f *.o *.exe *.d *.gcno *.gcov *.gcda
	cd src && rm -f *.o *.exe *.d *.gcno *gcov *gcda

release : CFLAGS += -DNDEBUG -g0
release : app.exe

debug : CFLAGS += -g3 --coverage
debug : app.exe
	