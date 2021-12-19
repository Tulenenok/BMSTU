CC = gcc
INC = ./inc/
OUT = ./out/
SRC = ./src/
UNIT = ./unit_tests/
CFLAGS = -I../inc/ -Wall -Werror -Wextra -pedantic -Wvla -Wfloat-equal -Wfloat-conversion -std=c99
LFLAGS =
MKOUT = mkdir -p out

release : CFLAGS += -DNDEBUG -g0
release : app.exe

debug : CFLAGS += -g3 -fprofile-arcs -ftest-coverage
debug : LFLAGS += -lgcov --coverage
debug : app.exe

SRCS = $(wildcard $(SRC)*.c)
UNITS = $(wildcard $(UNIT)*.c)

OBJS = $(patsubst $(SRC)%.c,$(OUT)%.o,$(SRCS))

app.exe: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

unit_tests.exe: $(patsubst $(UNIT)%.c,$(OUT)%.o,$(UNITS)) $(filter-out $(OUT)main.o,$(OBJS))
	$(CC) $^ -o $@ -lgcov --coverage -lcheck

$(OUT)%.o : $(SRC)%.c
	$(MKOUT) && cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)%.o : $(UNIT)%.c
	$(MKOUT) && cd out && $(CC) $(CFLAGS) -c ../$<

include $(wildcard *.d)

.PHONY : clean debug release func unit
clean :
	$(RM) $(OUT)*.o *.exe $(OUT)*.gcno $(OUT)*.gcda $(OUT)*.gcov $(OUT)*.txt
	
unit : unit_tests.exe
	make clean && make unit_tests.exe && ./unit_tests.exe
	
func :
	make debug && cd ./func_tests && ./all_test.sh && cd .. && gcov main.c
