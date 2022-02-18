from model import tools
import numexpr as ne
from view import graph
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


def printResultTable(table, name, flag='Newton'):
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


def dividedDifferenceHermiteTwo(x1, y1, yDerivative1, x2, y2, yDerivative2):
    if x1 == x2:
        return yDerivative1
    else:
        return (y1 - y2) / (x1 - x2)


def dividedDifferenceHermiteThree(x1, y1, yDerivative1, x2, y2, yDerivative2, x3, y3, yDerivative3):
    return (dividedDifferenceHermiteTwo(x1, y1, yDerivative1, x2, y2, yDerivative2) -
            dividedDifferenceHermiteTwo(x1, y1, yDerivative1, x3, y3, yDerivative3)) / (x1 - x3)


def HermitePolynomial(tableHermite):
    tableHermite.pop(2)                     # удалили столбец с производной
    return NewtonPolynomial(tableHermite)


def interpolationHermite(table, x, degree, printComments=False):
    nearestEntries = findNearestEntries(table, x, degree // 2)

    if nearestEntries == tools.NOT_ENOUGH_DATA:

        return tools.NOT_ENOUGH_DATA

    # теперь эту таблицу нужно раздвоить
    i = 0
    while len(nearestEntries) != degree + 1:
        nearestEntries.insert(i, nearestEntries[i])
        i += 2

    tableHermite = [[i[0] for i in nearestEntries], [i[1] for i in nearestEntries], [i[2] for i in nearestEntries], []]

    # добавили строку y(xi, xj)
    for i in range(len(tableHermite[-2]) - 1):
        tableHermite[-1].append(dividedDifferenceHermiteTwo(tableHermite[0][i], tableHermite[1][i], tableHermite[2][i],
                                                             tableHermite[0][i + 1], tableHermite[1][i + 1], tableHermite[2][i + 1]))

    # работаем дальше также, как в Ньютоне
    j = 2
    while len(tableHermite[-1]) != 1:
        tableHermite.append([(tableHermite[-1][i] - tableHermite[-1][i + 1]) /
                            (tableHermite[0][i] - tableHermite[0][i + j]) for i in range(len(tableHermite[-1]) - 1)])
        j += 1

    polStr = HermitePolynomial(tableHermite.copy())
    pol = ne.evaluate(polStr)

    if printComments:
        printResultTable(tableHermite, "HERMITE TABLE", 'Hermite')
        print('H(x) =', polStr)
        print('-------------------------------------')
        print('H(%2.3f) = %2.5f' % (x, ne.evaluate(polStr)))
        print('-------------------------------------')

    return tableHermite, polStr, pol


def allNewtonInter(table, x, startDegree=1, endDgree=5, printOwnGraph=False, pltGraph=plt):
    resX = []
    allDegree = []

    if printOwnGraph:
        pltGraph.figure(figsize=[10, 10])
        pltGraph.suptitle('NewtonPolinom', fontsize=15, fontweight='bold')
        pltGraph.grid(True)

    pltGraph.grid(True)
    pltGraph.title.set_text('Newton')
    graph.showGraphUsePoints([table[i][0] for i in range(len(table))], [table[i][1] for i in range(len(table))], pltGraph,
                             f'start points', 'mo')

    for degree in range(startDegree, endDgree + 1):
        t, p, val = interpolationNewton(table, x, degree, printComments=False)
        resX.append(val)
        graph.showGraphUsePol(t, p, pltGraph, f'degree = {degree}', "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)]))

        randColor = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
        pltGraph.plot(x, val, marker='o', label='%d: (%1.3f, %1.3f)' % (degree, x, val), color=randColor)
        allDegree.append(degree)

    pltGraph.legend(loc=0)
    if printOwnGraph:
        pltGraph.legend(loc=0)
        pltGraph.savefig('Newton.svg')
        pltGraph.show()

    return allDegree, resX


def allHermiteInter(table, x, minCountNodes=1, maxCountNodes=3, printOwnGraph=False, pltGraph=plt):
    res = []
    allDegree = []

    if printOwnGraph:
        pltGraph.figure(figsize=[10, 10])
        pltGraph.suptitle('HermitePolinom', fontsize=15, fontweight='bold')

    pltGraph.grid(True)
    pltGraph.title.set_text('Hermite')
    graph.showGraphUsePoints([table[i][0] for i in range(len(table))], [table[i][1] for i in range(len(table))], pltGraph,
                             f'start points', 'mo')

    for degree in range(minCountNodes, maxCountNodes + 1):
        t, p, val = interpolationHermite(table, x, degree * 2 - 1, printComments=False)
        res.append(val)
        if degree != 1:
            randColor = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
            graph.showGraphUsePol(t, p, pltGraph, f'count = {degree}', randColor)

        randColor = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
        pltGraph.plot(x, val, marker='o', label='%d: (%1.3f, %1.3f)' % (degree, x, val), color=randColor)
        allDegree.append(degree * 2 - 1)

    pltGraph.legend(loc=0)
    if printOwnGraph:
        pltGraph.savefig('Hermite.svg')
        pltGraph.show()

    return allDegree, res



#
# table = [[0], [0.25], [0.3], [0.5], [0.75], [1]]
# print(findNearestEntries(table, 0.26, 0))
