from tkinter import *
from tkinter.messagebox import *
import tkinter.filedialog as fd

from view.Btn import WrapButton
from view.menu import menuFrame
from view.keyInput import XYForm, Zoom
from view.CanvasField import WrapCanva
from view.CanvasPoint import CanvasPoint
from view.Settings import Settings
from view.RootWithVersions import RootWithVersions
from view.ActionsField import ActionsField

from model.SetPoints import SetPoints
from model.Tools import Tools

import controll.controllModel


def go(field):
    points = SetPoints(field.getPoints())

    field.canva.clearResult()

    rc = controll.controllModel.findLine(points)
    if rc == Tools.EXIT_FAILURE:
        return

    b, e, more, equal, less = rc
    field.canva.showLine(b, e)

    minCircleFirst = controll.controllModel.minCircle(more)
    minCircleSecond = controll.controllModel.minCircle(less)

    if minCircleFirst.r != 0:
        field.canva.showCircle(minCircleFirst.center, minCircleFirst.r, Settings.COLOR_POINT_FIRST_SET)

    if minCircleSecond.r != 0:
        field.canva.showCircle(minCircleSecond.center, minCircleSecond.r, Settings.COLOR_POINT_SECOND_SET)

    field.canva.changeColorPoints(more, Settings.COLOR_POINT_FIRST_SET)
    field.canva.changeColorPoints(equal, Settings.COLOR_LINE)
    field.canva.changeColorPoints(less, Settings.COLOR_POINT_SECOND_SET)

    field.canva.save()

    result = "Center purple circle - %s, radius - %.3f. \n" \
             "Center red circle - %s, radius - %.3f. \n\n" \
             "Square purple circle - %.3f. \n" \
             "Square red circle - %.3f. \n\n" \
             f"Unification - %.3f" % (minCircleFirst.center.likeFormatStr(), minCircleFirst.r,
                                       minCircleSecond.center.likeFormatStr(), minCircleSecond.r,
                                       controll.controllModel.Square(minCircleFirst),
                                       controll.controllModel.Square(minCircleSecond),
                                       controll.controllModel.findArea(minCircleFirst.r, minCircleSecond.r, minCircleFirst.center, minCircleSecond.center))

    # showinfo("Result", f"Center purple circle - {minCircleFirst.center.likeStr()}, radius - {minCircleFirst.r}. \n"
    #                    f"Center red circle - {minCircleSecond.center.likeStr()}, radius - {minCircleSecond.r}. \n\n"
    #                    f"Square purple circle - {controll.controllModel.Square(minCircleFirst)}. \n"
    #                    f"Square red circle - {controll.controllModel.Square(minCircleSecond)}. \n\n"
    #                    f"Intersection - {controll.controllModel.findArea(minCircleFirst.r, minCircleSecond.r, minCircleFirst.center, minCircleSecond.center)}")

    showinfo("Result", result)


def addPointKey(canva, XYform):
    x, y = XYform.getXY()
    if not Tools.isFloat(x) or not Tools.isFloat(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    canva.canva.showPoint(float(x), float(y))
    XYform.clear()

    canva.canva.save()


def delPointKey(canva, XYform):
    x, y = XYform.getXY()
    print(x, y)
    if not Tools.isFloat(x) or not Tools.isFloat(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    delPoint = CanvasPoint(float(x), float(y))
    flagWasPoint = False
    for point in canva.getPoints():
        if point.isPointsEqual(delPoint, point):
            point.hide(canva.canva)
            XYform.clear()
            flagWasPoint = True

    if not flagWasPoint:
        showinfo('Warning', 'Точки с такими координатами не найдено')
        return

    canva.canva.save()


def inputPointsFromFile(canva):
    filetypes = (("Текстовый файл", "*.txt"), ("Excel", "*.xlsx"))
    filename = fd.askopenfilename(title="Открыть файл", initialdir=Settings.DIR_INPUT_POINTS,
                                  filetypes=filetypes, multiple=False)

    coords = []
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

    if coords == []:
        showinfo('Empty file', 'Выбранный файл не содержит данных, точки не обновлены.')
        return

    canva.canva.clear()
    for c in coords:
        canva.canva.showPoint(c[0], c[1])

    canva.canva.save()


def savePointsToFile(canva):
    new_file = fd.asksaveasfile(title="Сохранить файл", defaultextension=".txt",
                                filetypes=(("Текстовый файл", "*.txt"), ))
    if new_file:
        for point in canva.getPoints():
            new_file.write(point.likeStr() + '\n')
        new_file.close()


def clearCanva(canva):
    canva.clear()
    canva.canva.save()


class UpButtons:
    def __init__(self, root, c):
        self.root = root
        self.canva = c
        self.f = Frame(self.root, width=400, height=60)
        self.f['bg'] = Settings.COLOR_MAIN_BG

        self.bClear = WrapButton(self.f, txt='🗑', command=lambda: clearCanva(self.canva), name='clear all')
        self.bGo = WrapButton(self.f, txt='🚀', command=lambda: go(self.canva), name='make calc')
        self.bInput = WrapButton(self.f, txt='📂', command=lambda: inputPointsFromFile(self.canva), name='take points from file')
        self.bSave = WrapButton(self.f, txt='📋', command=lambda: savePointsToFile(self.canva), name='save points')
        self.bReturn = WrapButton(self.f, txt='⏎', command=lambda: root.loadVersion(), name='cancel')

    def show(self, posx=Settings.X_CANVA, posy=Settings.Y_INPUT + 9):
        startX, startY = 0, 0
        self.bReturn.show(posx=startX, posy=startY)
        self.bInput.show(posx=startX + 1 * Settings.BTN_STEP, posy=startY)
        self.bSave.show(posx=startX + 2 * Settings.BTN_STEP, posy=startY)
        self.bClear.show(posx=startX + 3 * Settings.BTN_STEP, posy=startY)
        self.bGo.show(posx=startX + 4 * Settings.BTN_STEP, posy=startY)

        self.f.place(x=posx, y=posy)