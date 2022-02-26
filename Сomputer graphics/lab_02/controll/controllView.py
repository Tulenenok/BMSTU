from tkinter import *
from tkinter.messagebox import *
import tkinter.filedialog as fd

from view.Btn import WrapButton
from view.CanvasPoint import CanvasPoint
from view.Settings import Settings
from view.keyInput import *

from model.Tools import Tools

import controll.controllModel


def addPointKey(canva, XYform):
    x, y = XYform.getXY()
    if not Tools.isFloat(x) or not Tools.isFloat(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    canva.canva.showPoint(float(x), float(y))
    XYform.clear()

    canva.canva.update()
    canva.canva.save()


def delPointKey(canva, XYform):
    x, y = XYform.getXY()
    print(x, y)
    if not Tools.isFloat(x) or not Tools.isFloat(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    delPoint = CanvasPoint(float(x), float(y))
    flagWasPoint = canva.canva.delPoint(delPoint)

    if not flagWasPoint:
        showinfo('Warning', 'Точки с такими координатами не найдено')
        return

    XYform.clear()
    canva.canva.save()


def inputPointsFromFile(canva):
    filetypes = (("Текстовый файл", "*.txt"), ("Excel", "*.xlsx"))
    filename = fd.askopenfilename(title="Открыть файл", initialdir=Settings.DIR_INPUT_POINTS,
                                  filetypes=filetypes, multiple=False)
    if filename and filename[-4::] == '.txt':
        coords = controll.controllModel.inputPointsTXT(filename)
        if Tools.isFloat(coords):
            showinfo('Ошибка открытия файла' if coords == Tools.INVALID_FILENAME else 'Неверный формат данных',
                     'Неверно указано название файла' if coords == -1 else f'Произошла ошибка на {coords} строке. \n\n'
                              'Проверьте, что координаты точек введены в формате x ; y и что каждая точка введена '
                              'на новой строке')
            return

    elif filename and filename[-5::] == '.xlsx':
        coords = controll.controllModel.inputPointsXLSX(filename)
        if Tools.isInt(coords):
            if coords == Tools.INVALID_FILENAME:
                showinfo('Ошибка открытия файла', 'Неверно указано название файла')
            elif coords == Tools.INVALID_LISTNAME:
                showinfo('Ошибка названия листа', 'Не удалось найти лист с названием Points')
            elif coords == Tools.INVALID_HEAD:
                showinfo('Ошибка заголовка таблицы', 'Проверьте, что заголовок таблицы содержит названия X и Y')
            elif coords == Tools.INVALID_DATA:
                showinfo('Ошибка чтения данных', 'Проверьте, что количество х-сов совпадает с количеством y-ков')
            elif coords == Tools.INVALID_FORMAT_DATA:
                showinfo('Ошибка чтения данных', 'Формат данных неверный (ожидались вещественные числа)')
            else:
                showinfo('Error', 'Непонятная ошибка, но мы работаем над этим')
            return
    elif filename:
        showinfo('Ошибка открытия файла', 'Неверно указано название файла')
        return
    else:
        return

    if coords == [[]]:
        showinfo('Empty file', 'Выбранный файл не содержит данных, точки не обновлены.')
        return

    canva.canva.clear()
    for c in coords:
        for p in c:
            canva.canva.showPoint(p[0], p[1])
        canva.canva.startNewPolygon('sdfv')

    canva.canva.update()
    canva.canva.save()


def savePointsToFile(canva):
    new_file = fd.asksaveasfile(title="Сохранить файл", defaultextension=".txt",
                                filetypes=(("Текстовый файл", "*.txt"), ))
    if new_file:
        for pol in canva.getPointsForSave():
            for p in pol:
                new_file.write(p.likeStr() + '\n')
            new_file.write(Tools.SEPARATOR_POL + '\n')
        new_file.close()


def clearCanva(canva):
    canva.clear()
    canva.canva.save()

def scaleShiftRotate(root, canva):
    z = ZoomRotateShift(root, canva)
    z.show()


class UpButtons:
    def __init__(self, root, c):
        self.root = root
        self.canva = c
        self.f = Frame(self.root, width=500, height=60)
        self.f['bg'] = Settings.COLOR_MAIN_BG

        self.bClear = WrapButton(self.f, txt='🗑', command=lambda: clearCanva(self.canva), name='clear all')
        self.bInput = WrapButton(self.f, txt='📂', command=lambda: inputPointsFromFile(self.canva), name='take points from file')
        self.bSave = WrapButton(self.f, txt='📋', command=lambda: savePointsToFile(self.canva), name='save points')
        self.bReturn = WrapButton(self.f, txt='⏎', command=lambda: root.loadVersion(), name='cancel')
        self.bGo = WrapButton(self.f, txt='🚀', command=lambda: scaleShiftRotate(root, c), name='scale shift rotate')

    def show(self, posx=Settings.X_CANVA, posy=Settings.Y_INPUT + 9):
        startX, startY = 0, 0
        self.bReturn.show(posx=startX, posy=startY)
        self.bInput.show(posx=startX + 1 * Settings.BTN_STEP, posy=startY)
        self.bSave.show(posx=startX + 2 * Settings.BTN_STEP, posy=startY)
        self.bClear.show(posx=startX + 3 * Settings.BTN_STEP, posy=startY)
        self.bGo.show(posx=startX + 4 * Settings.BTN_STEP, posy=startY)

        self.f.place(x=posx, y=posy)