import tools
import interpolationAlgorithms


def menu():
    print("Menu:\n"
          "    0 - EXIT\n"
          "    1 - input table from file\n"
          "    2 - input table from stdin\n"
          "    3 - perform interpolation\n"
          "    4 - print table with data")
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
            interpolationAlgorithms.allNewtonInter(table, 0.6, 1, 4)

        mode = menu()




