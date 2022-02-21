from tkinter import *
from view.CanvasField import WrapCanva
from view.Btn import WrapButton
from view.menu import menuFrame
from view.keyInput import XYForm

from model.SetPoints import SetPoints
import controll.cn
from view.CanvasField import WrapCanva
from view.Settings import Settings
from model.Tools import Tools


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
    print('add')


def delPointKey():
    print('del')


def mainView():
    root = Tk()
    root.geometry('850x650')
    root['bg'] = Settings.COLOR_MAIN_BG

    menu = menuFrame(root)
    root.config(menu=menu.create())

    c = WrapCanva(root, bg='white', highlightthickness=0)
    b = WrapButton(root, txt='🗑', command=c.clear)
    bcn = WrapButton(root, txt='🚀', command=lambda: go(c))

    c.show(200, 85, 0.7, 0.8)
    b.show(posx=200, posy=19)
    bcn.show(posx=270, posy=19)

    addXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Add point', 18, lambda: addPointKey(c, addXYForm), '  Add  ')
    delXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Del point', 18, delPointKey, '  Del  ')

    addXYForm.show(Settings.COLOR_MAIN_BG, 20, 10)
    delXYForm.show(Settings.COLOR_MAIN_BG, 20, 150)

    root.mainloop()