from sympy import *

FILE_WITH_TABLE = '../data\\data.txt'
FILE_WITH_SINGLE_TABLE = '../data\\single_data.txt'
FILE_WITH_DOUBLE_TABLE = '../data\\double_data.txt'

MODE_EXIT = '0'
MODE_INPUT_FROM_FILE = '1'
MODE_INTERPOLATION = '2'
MODE_PRINT_TABLE = '3'

NOT_ENOUGH_DATA = 10


def inputTableFromFile(filename=FILE_WITH_TABLE):
    table = []
    with open(filename, 'r') as fin:
        s = fin.readline()
        while s:
            table.append(list(map(float, s.split())))
            s = fin.readline()

    return table


# Находит индексы в массиве, из которых нужно будет вытащить count + 1 значение
# j не включается
def findNearestInd(array, x, count):
    if count >= len(array):
        return NOT_ENOUGH_DATA

    i = 0
    while i < len(array) and array[i] < x:
        i += 1

    if i < count // 2 + 1:
        start, end = 0, count + 1
    elif i > len(array) - count:
        start, end = len(array) - count - 1, len(array)
    else:
        start = i - count // 2 - 1 if x != array[i] or count % 2 == 1 else i - count // 2
        end = i + count // 2 + 1 if count % 2 == 1 or x == array[i] else i + count // 2

    return start, end


def findDerivative(mathExpression):
    """ Найти производную от выражения """

    x = Symbol('x')
    y = eval(mathExpression)
    return str(y.diff(x))


def printResultTable(table, name, flag='Newton'):
    """ Рисует какие-то вспомогательные таблицы """

    print(name)
    print('-------------------------------------')
    for i in range(len(table)):
        if i == 0:
            print(f'X:', end=' ')
        elif i == 1:
            print(f'Y:', end=' ')
        elif i == 2 and flag == 'Hermite':
            print(f"Y':", end=' ')
        else:
            print(f'{i}:', end=' ')
        for j in range(len(table[i])):
            print('%+2.3f' % table[i][j], end=' ')
        print()
    print('-------------------------------------')