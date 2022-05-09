import math

import numexpr as ne
from model.tools import *

# *******************************************************
# Методы одномерной интерполяции на основе великих людей
# *******************************************************


class InterAlgorithms:
    @staticmethod
    def __NewtonPolynomial(tableNewton):
        """ Вспомогательная функция. Составляет полином Ньютона на основе высчитанной таблицы """

        pol = '%2.3f' % tableNewton[1][0]
        for k in range(2, len(tableNewton)):
            pol += ' + (%2.3f' % tableNewton[k][0]
            for i in range(k - 1):
                if tableNewton[0][i] == 0:
                    pol += ' * x'
                elif tableNewton[0][i] > 0:
                    pol += ' * (x - %2.3f)' % tableNewton[0][i]
                else:
                    pol += ' * (x + %2.3f)' % math.fabs(tableNewton[0][i])
            pol += ')'
        return pol


    @staticmethod
    def interpolationNewton(tableNewton, x, printComments=False):
        """ Функция проводит одномерную интерполяцию Ньютона для выбранного значения x """
        """ Table -- двумерный массив вида [[x][y]] """
        """ Возвращает таблицу значений полинома, строку-полином, итоговое значение y для введенного x"""

        j = 1
        while len(tableNewton[-1]) != 1:
            tableNewton.append([(tableNewton[-1][i] - tableNewton[-1][i + 1]) /
                                (tableNewton[0][i] - tableNewton[0][i + j]) for i in range(len(tableNewton[-1]) - 1)])
            j += 1

        polStr = InterAlgorithms.__NewtonPolynomial(tableNewton)
        pol = ne.evaluate(polStr)

        if printComments:
            printResultTable(tableNewton, "\nNEWTON TABLE")
            print('NEWTON POLYNOMIAL')
            print('P(x) =', polStr)
            print('-------------------------------------')
            print('NEWTON RESULT')
            print('P(%2.3f) = %2.5f' % (x, ne.evaluate(polStr)))
            print('-------------------------------------\n')

        return tableNewton, polStr, pol