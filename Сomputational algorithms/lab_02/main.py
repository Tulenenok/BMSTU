from model.TripleTable import *


def menu():
    print("Menu:\n"
          "    0 - EXIT\n"
          "    1 - input table from file\n"
          "    2 - perform interpolation\n"
          "    3 - print table with data")
    return input("Input command: ")


if __name__ == '__main__':
    mode = menu()
    table = TripleTable()
    while mode != tools.MODE_EXIT:
        if mode == tools.MODE_INPUT_FROM_FILE:
            try:
                filename = input(r"Input filename with data or 1 if you want to use data\t.txt): ")
                table.inputFromTXTFile(filename if filename != '1' else r'data\t.txt')
                print("INPUT DATA ---> SUCCESS")
            except FileNotFoundError:
                print('Error with filename')
            except ValueError:
                print('Error with data in file')

        elif mode == tools.MODE_PRINT_TABLE:
            table.print()

        elif mode == tools.MODE_INTERPOLATION:
            try:
                x = float(input('Input x [float]: '))
                y = float(input('Input y [float]: '))
                z = float(input('Input z [float]: '))
                nx = int(input('Input x degree (nx) [int]: '))
                ny = int(input('Input y degree (ny) [int]: '))
                nz = int(input('Input z degree (nz) [int]: '))
            except:
                print('Invalid input')
                mode = menu()
                continue
            res = table.tripleNewtonInter(x, y, z, nz, ny, nz, True)
            print('Res =', res)

        mode = menu()




