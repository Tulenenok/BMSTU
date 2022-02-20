from model.Circle import Circle
from view.CanvasPoint import CanvasPoint

from tkinter import *


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
        except:
            x, y = self.center.x, self.center.y
            print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

        self.c = canva.create_oval(x - self.r, y - self.r, x + self.r, y + self.r,
                                   outline=self.color, width=self.width, activefill=self.activefill)

        if showText:
            self.pointCenter.show(canva)
            self.arrowRadius = canva.create_line(x, y, x + self.r, y, fill='black', width=2, arrow=LAST)
            self.t = canva.create_text(x + self.r / 2, y - 10, text=str(int(self.r)), font=('Arial', 8, 'bold'),
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