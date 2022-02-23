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


def addPointKey(canva, XYform):
    x, y = XYform.getXY()
    if not Tools.isInt(x) or not Tools.isInt(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    canva.canva.showPoint(int(x), int(y))
    XYform.clear()

    canva.canva.save()


def delPointKey(canva, XYform):
    x, y = XYform.getXY()
    print(x, y)
    if not Tools.isInt(x) or not Tools.isInt(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    delPoint = CanvasPoint(int(x), int(y))
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
    if filename and filename[-4::] == '.txt':
        coords = controll.controllModel.inputPointsTXT(filename)
        if Tools.isInt(coords):
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
    else:
        showinfo('Ошибка открытия файла', 'Неверно указано название файла')
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


def plug():
    print('plug')

def mainView():
    root = RootWithVersions()
    root.geometry('850x650')
    root['bg'] = Settings.COLOR_MAIN_BG

    root.iconphoto(True, PhotoImage(file=r'C:\projects\Сomputational algorithms\lab_01_new_version\shared\rootIcon.png'))
    root.title('У меня лапки')

    menu = menuFrame(root)
    root.config(menu=menu.create())

    c = WrapCanva(root, bg='white', highlightthickness=0)
    root.setSaveObjs(c)
    b = WrapButton(root, txt='🗑', command=lambda: clearCanva(c))
    bcn = WrapButton(root, txt='🚀', command=lambda: go(c))
    binput = WrapButton(root, txt='📂', command=lambda: inputPointsFromFile(c))
    boutput = WrapButton(root, txt='📋', command=lambda: savePointsToFile(c))
    breturn = WrapButton(root, txt='⏎', command=lambda: root.loadVersion())

    act = ActionsField(root, c)
    act.show(posx=105, posy=300)


    c.show(Settings.X_CANVA, Settings.Y_CANVA, Settings.REL_X_CANVA, Settings.REL_Y_CANVA)
    breturn.show(posx=Settings.X_CANVA, posy=Settings.Y_START_BUTTONS)
    binput.show(posx=Settings.X_CANVA + 1 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    boutput.show(posx=Settings.X_CANVA + 2 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    b.show(posx=Settings.X_CANVA + 3 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    bcn.show(posx=Settings.X_CANVA + 4 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)

    addXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Add point', Settings.WIDTH_INPUT,
                       lambda: addPointKey(c, addXYForm), '  Add  ')
    delXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Del point', Settings.WIDTH_INPUT,
                       lambda: delPointKey(c, delXYForm), '  Del  ')

    addXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT)
    delXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT + Settings.STEP_INPUT)

    root.mainloop()