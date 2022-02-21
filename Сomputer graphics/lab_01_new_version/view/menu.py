from tkinter import *
from tkinter.messagebox import *


class menuFrame:
    def __init__(self, window):
        self.__menu = Menu()
        self.__window = window

    def __makeDropDown(self, dictLabels):
        newItem = Menu(self.__menu, tearoff=0)
        for item in dictLabels:
            newItem.add_command(label=item, command=dictLabels[item])
        return newItem

    def create(self):
        self.__menu.add_cascade(label='Menu', menu=self.__makeDropDown({'Информация о программе': self.__info_programm,
                                                                        'Информация об авторе': self.__info_author,
                                                                        'Выход': self.__window.destroy
                                                                        }))
        return self.__menu

    def __info_author(self):
        showinfo('Info', 'Автор: Гурова Наталия ИУ7-44Б')

    def __info_programm(self):
        showinfo('Info', 'Программа была создана 13.02.22 \n\n'
                         'Задание: множество точек на плоскости разбить на два подмножества прямой,'
                         'проходящей через две различные точки так, чтобы количества точек, '
                         'лежащих по разные стороны прямой, проходящей через эти две точки, '
                         'различались наименьшим образом. Каждое из полученных множеств поместить внутрь '
                         'окружности минимального радиуса. Найти суммарную площадь, покрытую данными окружностями.')