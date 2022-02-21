from tkinter import *
from view.CanvasField import WrapCanva
from view.Btn import WrapButton

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


def mainView():
    root = Tk()
    root.geometry('900x700')
    root['bg'] = Settings.COLOR_MAIN_BG
    c = WrapCanva(root, bg='white', highlightthickness=0)
    b = WrapButton(root, txt='⏎', command=c.clear)
    bcn = WrapButton(root, txt='go', command=lambda: go(c))

    c.show(40, 50, 0.7, 0.7)
    b.show(posx=0, posy=0)
    bcn.show(posx=70, posy=0)

    root.mainloop()