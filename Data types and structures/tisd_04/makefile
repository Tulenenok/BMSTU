CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -pedantic
COV := 




app.exe : main.o libr.o
	$(CC) -o $@ $^ $(COV)

unit_tests.exe : libr.o check_libr.o check_main.o
	$(CC) -o $@ $^ -lcheck

check_main.o : unit_tests/check_main.c libr.h
	$(CC) -Iinc $(CFLAGS) -c $<

check_libr.o : unit_tests/check_libr.c libr.h
	$(CC) -Iinc $(CFLAGS) -c $<

main.o : main.c libr.h
	$(CC) -Iinc $(CFLAGS) -c $<
	
libr.o : libr.c libr.h	
	$(CC) -Iinc $(CFLAGS) -c $<




.PHONY : clean func unit release debug

clean :
	rm -rf ./*.out ./*.exe ./*.o ./*.pch ./*.gch ./*.gcda ./*.gcov ./*.gcno ./*.h.gcov

func :
	make debug && sh make_func.sh

unit : 
	make clean && make unit_tests.exe && ./unit_tests.exe




debug : CFLAGS += --coverage -g3
debug : COV += --coverage
debug : app.exe

release : CFLAGS += -g0 -DNDEBUG
release : app.exe
