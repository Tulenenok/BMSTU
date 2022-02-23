from tkinter import *
from tkinter.messagebox import *


class menuFrame:
    def __init__(self, window):
        self.menu = Menu()
        self.window = window

        self.name = '❌ Комментарии'
        self.settingMenu = self.__makeDropDown({self.name: self.__showComment})
        self.field = None

    def __makeDropDown(self, dictLabels):
        newItem = Menu(self.menu, tearoff=0)
        for item in dictLabels:
            newItem.add_command(label=item, command=dictLabels[item])
        return newItem

    def create(self, field, funcInput, funcLoad, funcClean, funcReturn, funcGo):
        self.field = field
        self.menu.add_cascade(label='File', menu=self.__makeDropDown({'Открыть 📂': lambda: funcInput(field),
                                                                      'Сохранить 📋': lambda: funcLoad(field),
                                                                      'Отменить ⏎': lambda: funcReturn(),
                                                                      'Очистить 🗑': lambda: funcClean(field),
                                                                      }))
        self.menu.add_cascade(label='Setting', menu=self.settingMenu)
        self.menu.add_cascade(label='Info', menu=self.__makeDropDown({'Информация о программе': self.__info_programm,
                                                                        'Информация об авторе': self.__info_author,
                                                                      }))
        self.menu.add_cascade(label='Exit', menu=self.__makeDropDown({'Выход': self.window.destroy}))
        return self.menu

    def __showComment(self):
        self.field.radioShowComments()
        self.name = '✔ Комментарии' if self.name == '❌ Комментарии' else '❌ Комментарии'
        self.settingMenu.entryconfig(1, label=self.name)

    def __info_author(self):
        showinfo('Info', 'Автор: Гурова Наталия ИУ7-44Б')

    def __info_programm(self):
        showinfo('Info', 'Программа была создана 13.02.22 \n\n'
                         'Задание: множество точек на плоскости разбить на два подмножества прямой,'
                         'проходящей через две различные точки так, чтобы количества точек, '
                         'лежащих по разные стороны прямой, проходящей через эти две точки, '
                         'различались наименьшим образом. Каждое из полученных множеств поместить внутрь '
                         'окружности минимального радиуса. Найти суммарную площадь, покрытую данными окружностями.')