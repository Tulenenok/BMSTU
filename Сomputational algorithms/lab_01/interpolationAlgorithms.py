import tools
import numexpr as ne
import graph
import matplotlib.pyplot as plt
import random


def findNearestEntries(table, x, countEntries):
    ansTable = []
    if countEntries >= len(table):
        return tools.NOT_ENOUGH_DATA

    table.sort(key=lambda i: i[0])

    i = 0
    while i < len(table) and table[i][0] < x:
        i += 1

    if i < countEntries // 2 + 1:
        for j in range(countEntries + 1):
            ansTable.append(table[j])
    elif i > len(table) - countEntries:
        for j in range(len(table) - countEntries - 1, len(table)):
            ansTable.append(table[j])
    else:
        for j in range(i - countEntries // 2 - 1 if x != table[i][0] or countEntries % 2 == 1 else i - countEntries // 2,
                       i + countEntries // 2 + 1 if countEntries % 2 == 1 or x == table[i][0] else i + countEntries // 2):
            ansTable.append(table[j])

    return ansTable


def printResultTable(table, name):
    print(name)
    print('-------------------------------------')
    for i in range(len(table)):
        if i == 0:
            print(f'X:', end=' ')
        elif i == 1:
            print(f'Y:', end=' ')
        else:
            print(f'{i}:', end=' ')
        for j in range(len(table[i])):
            print('%+2.3f' % table[i][j], end=' ')
        print()
    print('-------------------------------------')


def NewtonPolynomial(tableNewton):
    pol = '%2.3f' % tableNewton[1][0]
    for k in range(2, len(tableNewton)):
        pol += ' + (%2.3f' % tableNewton[k][0]
        for i in range(k - 1):
            if tableNewton[0][i] == 0:
                pol += ' * x'
            elif tableNewton[0][i] > 0:
                pol += ' * (x - %2.3f)' % tableNewton[0][i]
            else:
                pol += ' * (x + %2.3f)' % tableNewton[0][i]
        pol += ')'
    return pol


def interpolationNewton(table, x, degree, printComments=False):
    nearestEntries = findNearestEntries(table, x, degree)

    if nearestEntries == tools.NOT_ENOUGH_DATA:
        return tools.NOT_ENOUGH_DATA

    tableNewton = [[i[0] for i in nearestEntries], [i[1] for i in nearestEntries]]
    j = 1
    while len(tableNewton[-1]) != 1:
        tableNewton.append([(tableNewton[-1][i] - tableNewton[-1][i + 1]) /
                            (tableNewton[0][i] - tableNewton[0][i + j]) for i in range(len(tableNewton[-1]) - 1)])
        j += 1

    polStr = NewtonPolynomial(tableNewton)
    pol = ne.evaluate(polStr)

    if printComments:
        printResultTable(tableNewton, "NEWTON TABLE")
        print('P(x) =', polStr)
        print('-------------------------------------')
        print('P(%2.3f) = %2.5f' % (x, ne.evaluate(polStr)))
        print('-------------------------------------')

    return tableNewton, polStr, pol


def allNewtonInter(table, x, startDegree, endDgree):
    res = []

    plt.figure(figsize=[10, 10])
    plt.suptitle('NewtonPolinom', fontsize=15, fontweight='bold')
    plt.grid(True)
    graph.showGraphUsePoints([table[i][0] for i in range(len(table))], [table[i][1] for i in range(len(table))], plt,
                             f'start points', 'mo')

    for degree in range(startDegree, endDgree + 1):
        t, p, val = interpolationNewton(table, x, degree, printComments=False)
        res.append(val)
        graph.showGraphUsePol(t, p, plt, f'degree = {degree}', "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)]))

    plt.legend(loc=0)
    plt.savefig('Newton.svg')
    plt.show()

    return res

# table = [[0], [0.25], [0.3], [0.5], [0.75], [1]]
# print(findNearestEntries(table, -0.1, 5))
