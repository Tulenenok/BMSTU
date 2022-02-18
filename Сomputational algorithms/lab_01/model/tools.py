# FILE_WITH_TABLE = 'data\\data.txt'
FILE_WITH_TABLE = 'data\\new.txt'

MODE_EXIT = '0'
MODE_INPUT_FROM_FILE = '1'
MODE_INPUT_FROM_STDIN = '2'
MODE_INTERPOLATION = '3'
MODE_FIND_ROOTS = '4'
MODE_PRINT_TABLE = '5'

NOT_ENOUGH_DATA = 10


def inputTableFromFile(filename=FILE_WITH_TABLE):
    table = []
    with open(filename, 'r') as fin:
        s = fin.readline()
        while s:
            table.append(list(map(float, s.split(" "))))
            s = fin.readline()

    return table