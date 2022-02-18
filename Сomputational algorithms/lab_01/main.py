from model import interpolationAlgorithms, tools
from prettytable import PrettyTable
import matplotlib.pyplot as plt


def Inter(table):
    try:
        x = float(input("Input x (float number): "))
        startDegree = int(input(f"Input start degree for Newton interpolation (int from 1 to {len(table) - 1}): "))
        endDegree = int(input(f"Input end degree for Newton interpolation (int from {startDegree} to {len(table) - 1}): "))

        startCount = int(input(f"Input start count nodes for Hermite interpolation: "))
        endCount = int(input(f"Input end count nodes for Hermite interpolation: "))
    except:
        print("Error input")
        return

    # x = 0.525
    # startDegree = 1
    # endDegree = 5
    # startCount = 1
    # endCount = 3

    fig = plt.figure(figsize=(15, 10))
    fig.suptitle('Interpolation', fontsize=15, fontweight='bold')

    ax1 = fig.add_subplot(121)
    degN, yN = interpolationAlgorithms.allNewtonInter(table, x, startDegree, endDegree, printOwnGraph=False, pltGraph=ax1)

    ax2 = fig.add_subplot(122)
    degH, yH = interpolationAlgorithms.allHermiteInter(table, x, startCount, endCount, printOwnGraph=False, pltGraph=ax2)

    resTable = PrettyTable()
    resTable.field_names = ["Degree", "Newton", "Hermite"]
    for i in range(min(degN[0], degH[0]), max(degN[-1], degH[-1]) + 1):
        if i in degN and i in degH:
            resTable.add_row([f"{i}", "%2.5f" % yN[degN.index(i)], "%2.5f" % yH[degH.index(i)]])
        elif i in degN:
            resTable.add_row([f"{i}", "%2.5f" % yN[degN.index(i)], '-'])
        elif i in degH:
            resTable.add_row([f"{i}", '-', "%2.5f" % yH[degH.index(i)]])

    print(resTable)

    plt.show()

def menu():
    print("Menu:\n"
          "    0 - EXIT\n"
          "    1 - input table from file\n"
          "    2 - input table from stdin\n"
          "    3 - perform interpolation\n"
          "    4 - find roots\n"
          "    5 - print table with data")
    return input("Input command: ")


if __name__ == '__main__':
    mode = menu()
    table = []
    while mode != tools.MODE_EXIT:
        if mode == tools.MODE_INPUT_FROM_FILE:
            try:
                filename = input("Input filename with data or 1 if you want to use data.txt): ")
                table = tools.inputTableFromFile(filename if filename != '1' else tools.FILE_WITH_TABLE)
                print("INPUT DATA ---> SUCCESS")
            except FileNotFoundError:
                print('Error with filename')
            except ValueError:
                print('Error with data in file')

        elif mode == tools.MODE_INPUT_FROM_STDIN:
            table = []
            try:
                countValues = int(input("Input number of rows in the table (count values): "))
                if countValues <= 0:
                    print('Error count')
                    continue
                print("    x   y   y'")
                for i in range(countValues):
                    table.append(list(map(float, input(f'{i}:  ').split(" "))))
                print("INPUT DATA ---> SUCCESS")
            except ValueError:
                print('Error input data')

        elif mode == tools.MODE_PRINT_TABLE:
            if len(table) == 0:
                print('No data input')
            else:

                print("+--------------------------------------------------+'")
                print("|       x        |       y        |        y'      |'")
                print("+--------------------------------------------------+'")
                for i in range(len(table)):
                    print('|      %+2.6f |      %+2.6f |      %+2.6f |' % (table[i][0], table[i][1], table[i][2]))
                print("+--------------------------------------------------+'")

        elif mode == tools.MODE_INTERPOLATION:
            # interpolationAlgorithms.allNewtonInter(table, 0.6, 5, 5, True)
            # interpolationAlgorithms.interpolationNewton(table, 0.6, 5, True)
            # interpolationAlgorithms.interpolationHermite(table, 0.6, 5, True)
            # interpolationAlgorithms.allHermiteInter(table, 0.525, 1, 3)
            Inter(table)

        elif mode == tools.MODE_FIND_ROOTS:
            interpolationAlgorithms.roots(table)

        mode = menu()




