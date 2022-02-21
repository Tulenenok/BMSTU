from model.Circle import Circle
from view.CanvasPoint import CanvasPoint

from tkinter import *

""" РАБОТАЕТ, НО НЕ ВСЕГДА, НУЖНЫ ПРОВЕРКИ """
# Тест с проваленными точками
# (-59, 31) (-72, -57) (-46, -42) (-19, 40) (42, 49) (40, -29)

class CanvasCircle(Circle):
    def __init__(self, center, r, color, width=2, activefill=None):
        super().__init__(center, r)
        self.color = color
        self.width = width
        self.activefill = activefill if activefill else color

        self.c = None
        self.t = None
        self.pointCenter = CanvasPoint(self.center.x, self.center.y, color='black')
        self.arrowRadius = None

    def show(self, canva, showText=True):
        try:
            x, y = canva.coordinateShift(self.center)
            xl, xr = canva.XShiftPC(self.center.x - self.r), canva.XShiftPC(self.center.x + self.r)
            yl, yr = canva.YShiftPC(self.center.y - self.r), canva.YShiftPC(self.center.y + self.r)
        except:
            x, y = self.center.x, self.center.y
            xl, xr, yl, yr = self.center.x - self.r, self.center.x + self.r, self.center.y - self.r, self.center.y + self.r
            print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

        self.c = canva.create_oval(xl, yl, xr, yr,
                                   outline=self.color, width=self.width, activefill=self.activefill)
        if showText:
            self.pointCenter.show(canva)
            self.arrowRadius = canva.create_line(x, y, xr, y, fill='black', width=2, arrow=LAST)
            self.t = canva.create_text((xr - x) / 2 + x, y + 10, text=str(int(int(self.r))), font=('Arial', 8, 'bold'),
                                       justify=CENTER, fill='black')

    def hide(self, canva):
        if self.c:
            canva.delete(self.c)
        if self.t:
            canva.delete(self.t)
        if self.arrowRadius:
            canva.delete(self.arrowRadius)
        self.pointCenter.hide(canva)

        self.c, self.t, self.arrowRadius = None, None, None

    def reShow(self, canva):
        self.hide(canva)
        self.show(canva)