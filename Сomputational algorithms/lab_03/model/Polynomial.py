import math
import model.tools as tools

# *****************************
# Полиномы, которые многочлены
# *****************************


class Polynomial:
    def __init__(self, degree=None, strRepresentation=None, variables=None):
        """ Создание --> Polynomial(degree=2, strRepresentation='2 + 5 * x + 10 * x^2', variables=['x']) """

        self.degree = degree                                     # Степень полинома
        self.strRepresentation = strRepresentation               # Строка вида 'a + bx + ..' для закидывания в eval
        self.variables = variables                               # Массив вида ['x', 'y', 'z'] (функция f(x, y, z) = ..)


    def print(self, name=None):
        """ Вывод полинома в виде выражения --> P(x) = 2 + 5 * x + 10 * x^2 """

        if not self.variables:
            print('ERROR ---> вы не определили переменные в полиноме')
            return

        if not self.strRepresentation:
            print('ERROR ---> вы не определили строку, которая задавала бы полином')
            return

        if name:
            print(name)

        temp = ''
        for i in range(len(self.variables)):
            temp += self.variables[i]
            temp += ', ' if i != len(self.variables) - 1 else ''
        print('P(' + temp + ') = ' + self.strRepresentation)


    def findValue(self, **vars):
        """ Посчитать значение полинома для конкретной точки """
        """ vars --> {x: 1, y: 2, z: 3 ...} """
        """ Не проверяет, что словарь составлен правильно """

        return eval(self.strRepresentation, vars)


    def findArrayValues(self, axisLabels, **axisValues):
        """ Посчитать значение полинома для набора точек """
        """ axis --> названия колонок ['x', 'y' ...] """
        """ axisValues --> {'x': [1, 2, 3, 4], 'y': [1, 1, 1, 1] ...} """
        """ Не проверяет, что словарь и названия осей составлены правильно """

        countPoints = len(axisValues[axisLabels[0]])
        results = []
        for i in range(countPoints):
            temp = ''
            for j, ax in enumerate(axisLabels):
                temp += ax + f'={axisValues[axisLabels[j]][i]}, '
            command = 'self.findValue(' + temp + ')'
            results.append(eval(command))

        return results


    def updateUseStr(self, str):
        """ Установить новою формулу для полинома используя строку """
        self.strRepresentation = str


    def updateUseData(self, coeff, diff):
        """ Строит текстовое представление полинома """
        """ coef --> коэффициенты a + b(  ) + c(  ) + ... """
        """ diff --> значения, которые вычитаются из x в скобочках . + .(x - diff[i]) + . """
        """ [1, 2, 3], [6, 7] --> P(x) = 1 + (2 * (x - 6)) + (3 * (x - 6) * (x - 7))"""

        if len(coeff) == 0:
            return ''

        pol = '%2.3f' % coeff[0]
        for k in range(2, len(coeff) + 1):
            pol += ' + (%2.3f' % coeff[k - 1]
            for i in range(k - 1):
                if diff[i] == 0:
                    pol += ' * x'
                elif diff[i] > 0:
                    pol += ' * (x - %2.3f)' % diff[i]
                else:
                    pol += ' * (x + %2.3f)' % math.fabs(diff[i])
            pol += ')'

        self.updateUseStr(pol)

    def findValueFirstDer(self, **vars):
        firstDer = tools.findDerivative(self.strRepresentation)
        return eval(firstDer, vars)

    def findValueSecondDer(self, **vars):
        print('strRep = ', self.strRepresentation)
        firstDer = tools.findDerivative(self.strRepresentation)
        print('firstDer = ', firstDer)
        secondDer = tools.findDerivative(firstDer)
        print('secondDer = ', secondDer)
        return eval(secondDer, vars)