from tkinter import *
from tkinter.messagebox import *


class menuFrame:
    def __init__(self, window):
        self.menu = Menu()
        self.window = window
        self.name = '✔ Комментарии'
        self.gridName = '✔ Оси координат'
        self.settingMenu = None

        self.sp = 'Горячие клавиши:\n\n' \
                  '  - Cntrl-Space -- начать новую фигуру, замкнув старую\n' \
                  '  - Cntrl-Shift-Space -- начать новую, не замыкая старую\n' \
                  '  - Cntrl-plus -- масштабирование х2\n' \
                  '  - Cntrl-minus -- масштабирование х0.5\n' \
                  '  - Cntrl-p -- поворот по часовой стрелке на 15 градусов\n' \
                  '  - Cntrl-o -- поворот против часовой стрелки на 15 градусов'

    def __makeDropDown(self, dictLabels):
        newItem = Menu(self.menu, tearoff=0)
        for item in dictLabels:
            newItem.add_command(label=item, command=dictLabels[item])
        return newItem

    def create(self, field, funcInput, funcLoad, funcClean, funcReturn):
        self.field = field
        self.settingMenu = self.__makeDropDown({self.name: self.__showComment, self.gridName: self.__showGrid,
                                                'Изменить цвет': field.changeColorNewPol})

        self.menu.add_cascade(label='File', menu=self.__makeDropDown({'Открыть 📂': lambda: funcInput(field),
                                                                      'Сохранить 📋': lambda: funcLoad(field),
                                                                      'Отменить ⏎': lambda: funcReturn(),
                                                                      'Очистить 🗑': lambda: funcClean(field),
                                                                      }))
        self.menu.add_cascade(label='Setting', menu=self.settingMenu)
        self.menu.add_cascade(label='Info', menu=self.__makeDropDown({'Информация о программе': self.__info_programm,
                                                                      'Информация об авторе': self.__info_author,
                                                                      'Справка': lambda : showinfo('Info', self.sp)
                                                                      }))
        self.menu.add_cascade(label='Exit', menu=self.__makeDropDown({'Выход': self.window.destroy}))
        return self.menu

    def __showComment(self):
        self.field.radioShowComments()
        self.name = '✔ Комментарии' if self.name == '❌ Комментарии' else '❌ Комментарии'
        self.settingMenu.entryconfig(0, label=self.name)

    def __showGrid(self):
        self.field.canva.flagShowGrid(not self.field.canva.showArrows)
        self.gridName = '✔ Оси координат' if self.gridName == '❌ Оси координат' else '❌ Оси координат'
        self.settingMenu.entryconfig(1, label=self.gridName)


    def __info_author(self):
        showinfo('Info', 'Автор: Гурова Наталия ИУ7-44Б')

    def __info_programm(self):
        showinfo('Info', 'Программа не была создана 13.02.22, 14.02.22 и даже 28.02.22 \n\n'
                         'Задание: в час ночи нарисуйте лося. Просто нарисуйте')