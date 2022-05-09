from model.SingleTable import *
from view.graph import showPol
import model.tools as tools

from colorama import init, Fore


def menu():
    print(Fore.LIGHTMAGENTA_EX + "Menu:\n"
          "    0 - EXIT\n"
          "    1 - input table from file\n"
          "    2 - perform interpolation\n"
          "    3 - print table with data")
    return input(Fore.LIGHTMAGENTA_EX + "Input command: ")


if __name__ == '__main__':

    init(autoreset=True)

    mode = menu()
    table = SingleTable()
    while mode != tools.MODE_EXIT:
        if mode == tools.MODE_INPUT_FROM_FILE:
            try:
                filename = input(r"Input filename with data or 1 if you want to use data\data.txt): ")
                table.inputFromTXTFile(filename if filename != '1' else r'data\data.txt')
                print("INPUT DATA ---> SUCCESS\n")
            except FileNotFoundError:
                print(Fore.LIGHTRED_EX + 'Error with filename\n')
            except ValueError:
                print(Fore.LIGHTRED_EX + 'Error with data in file\n')

        elif mode == tools.MODE_PRINT_TABLE:
            table.print()

        elif mode == tools.MODE_INTERPOLATION:
            try:
                x = float(input('Input x [float]: '))
                # nx = int(input('Input x degree (nx) [int]: '))
                nx = 3
            except:
                print('Fore.LIGHTRED_EX + Invalid input')
                mode = menu()
                continue

            NewtonPol, NewtonValue = table.NewtonInter(x, nx, True)
            NewtonPolP0, NewtonValueP0 = table.NewtonInter(table.x[0], nx, True)
            NewtonPolPP, NewtonValuePP = table.NewtonInter(table.x[-1], nx, True)

            SplinePol_0_0, SplineValue_0_0 = table.SplineInter(x, nx, True, cStart=0, cEnd=0)
            SplinePol_P_0, SplineValue_P_0 = table.SplineInter(x, nx, True,
                                                               cStart=NewtonPolP0.findValueSecondDer(x=table.x[0]),
                                                               cEnd=0)
            SplinePol_P_P, SplineValue_P_P = table.SplineInter(x, nx, True,
                                                               cStart=NewtonPolP0.findValueSecondDer(x=table.x[0]),
                                                               cEnd=NewtonPolPP.findValueSecondDer(x=table.x[-1]))

            isXInData = table.checkingForAlreadySetPoint(x)

            if isXInData != -1:
                print(Fore.LIGHTCYAN_EX + '\nWARNING: the value of x is a given node of the table.')
                print(Fore.LIGHTCYAN_EX + 'Table value y(x) = %.3f' % table.y[isXInData])

            print(Fore.LIGHTYELLOW_EX + '\nRESULTS')
            print(Fore.LIGHTYELLOW_EX + 'Newton: %.3f' % NewtonValue)
            print(Fore.LIGHTYELLOW_EX + 'Spline')
            spTable = PrettyTable()
            spTable.title = 'φ''(x₀) = .., φ''(xₙ) = ..'
            spTable.field_names = ["0,0", "P''(x₀), 0", "P''(x₀), P''(xₙ)"]

            spTable.add_row([round(SplineValue_0_0, 3), round(SplineValue_P_0, 3), round(SplineValue_P_P, 3)])
            print(spTable, '\n')

            showPol(table, NewtonPol, SplinePol_0_0, SplinePol_P_0, SplinePol_P_P)

        else:
            print(Fore.LIGHTRED_EX + 'ERROR --> INVALID COMMAND')

        mode = menu()
