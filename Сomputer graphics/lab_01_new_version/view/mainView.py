from tkinter import *
from tkinter.messagebox import *

from view.CanvasField import WrapCanva
from view.Btn import WrapButton
from view.menu import menuFrame
from view.keyInput import XYForm
from view.CanvasField import WrapCanva
from view.CanvasPoint import CanvasPoint
from view.Settings import Settings

from model.SetPoints import SetPoints
from model.Tools import Tools

import controll.cn


def go(field):
    points = SetPoints(field.getPoints())

    field.canva.clearResult()

    rc = controll.cn.findLine(points)
    if rc == Tools.EXIT_FAILURE:
        return

    b, e, more, equal, less = rc
    b.print()
    e.print()
    field.canva.showLine(b, e)

    minCircleFirst = controll.cn.minCircle(more)
    minCircleSecond = controll.cn.minCircle(less)

    if minCircleFirst.r != 0:
        field.canva.showCircle(minCircleFirst.center, minCircleFirst.r, Settings.COLOR_POINT_FIRST_SET)

    if minCircleSecond.r != 0:
        field.canva.showCircle(minCircleSecond.center, minCircleSecond.r, Settings.COLOR_POINT_SECOND_SET)

    field.canva.changeColorPoints(more, Settings.COLOR_POINT_FIRST_SET)
    field.canva.changeColorPoints(equal, Settings.COLOR_LINE)
    field.canva.changeColorPoints(less, Settings.COLOR_POINT_SECOND_SET)


def addPointKey(canva, XYform):
    x, y = XYform.getXY()
    if not Tools.isInt(x) or not Tools.isInt(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    canva.canva.showPoint(int(x), int(y))
    XYform.clear()


def delPointKey(canva, XYform):
    x, y = XYform.getXY()
    print(x, y)
    if not Tools.isInt(x) or not Tools.isInt(y):
        showinfo('Error', 'Неверно введены координаты точки (должны быть целые числа)')
        return

    delPoint = CanvasPoint(int(x), int(y))
    for point in canva.getPoints():
        if point.isPointsEqual(delPoint, point):
            point.hide(canva.canva)
            XYform.clear()


def mainView():
    root = Tk()
    root.geometry('850x650')
    root['bg'] = Settings.COLOR_MAIN_BG

    menu = menuFrame(root)
    root.config(menu=menu.create())

    c = WrapCanva(root, bg='white', highlightthickness=0)
    b = WrapButton(root, txt='🗑', command=c.clear)
    bcn = WrapButton(root, txt='🚀', command=lambda: go(c))

    c.show(Settings.X_CANVA, Settings.Y_CANVA, Settings.REL_X_CANVA, Settings.REL_Y_CANVA)
    b.show(posx=Settings.X_CANVA, posy=Settings.Y_START_BUTTONS)
    bcn.show(posx=Settings.X_CANVA + Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)

    addXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Add point', Settings.WIDTH_INPUT,
                       lambda: addPointKey(c, addXYForm), '  Add  ')
    delXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Del point', Settings.WIDTH_INPUT,
                       lambda: delPointKey(c, delXYForm), '  Del  ')

    addXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT)
    delXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT + Settings.STEP_INPUT)

    root.mainloop()