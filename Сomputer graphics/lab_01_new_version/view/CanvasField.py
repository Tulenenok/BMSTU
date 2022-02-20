import math

from view.CanvasPoint import CanvasPoint
from view.CanvasLine import CanvasLine

from tkinter import *


# пример создания  ResizingCanvas(myFrame, width=850, height=400, bg="red", highlightthickness=0)
class ResizingCanvas(Canvas):
    def __init__(self, parent, **kwargs):
        Canvas.__init__(self, parent, **kwargs)
        self.bind("<Configure>", self.on_resize)

        """                             ПРИВЕТ, КОСТЫЛЬ, ДАВНО НЕ ВИДЕЛИСЬ                         """
        # self.bind('<1>', lambda event: self.click(event))
        # self.bind("<Motion>", lambda event: self.showCoords(event))

        self.height = self.winfo_reqheight()
        self.width = self.winfo_reqwidth()

    def on_resize(self, event):
        self.width = event.width
        self.height = event.height

        self.config(width=self.width, height=self.height)

    """                              КОД НЕ РАБОТАЕТ, НО ВЫ ДЕРЖИТЕСЬ                              """
    def createMotion(self, motion, func):
        self.bind(motion, lambda event: func(event))

    # def click(self, event):
    #     print('click')
    #
    # def showCoords(self, event):
    #     print('showCoords')


class ResizingFrame:
    def __init__(self, window, bg):
        self.window = window

        self.frame = Frame(window)
        self.canva = ResizingCanvas(self.frame, bg=bg, highlightthickness=0)
        self.frame.bind('<Configure>', self.resize)
        self.canva.place(x=0, y=0)

        self.frame.bind('<1>', lambda event: self.click(event))
        self.frame.bind("<Motion>", lambda event: self.showCoords(event))

    def resize(self, event):
        self.canva.on_resize(event)

    def show(self, x, y, relwidth, relheight):
        self.frame.place(x=x, y=y, relwidth=relwidth, relheight=relheight)


class CoordGrid(ResizingFrame):
    def __init__(self, window, bg, XStart=-100, XEnd=100, YStart=-100, YEnd=100, gridCoef=10):
        super(CoordGrid, self).__init__(window, bg)
        self.XStart, self.XEnd, self.YStart, self.YEnd = XStart, XEnd, YStart, YEnd

        self.XLine, self.YLine = None, None
        self.gridLines = []
        self.gridDashes = []
        self.gridText = []

        self.gridCoef = gridCoef

    def changeLimits(self, XStart, XEnd, YStart, YEnd):
        self.XStart, self.XEnd, self.YStart, self.YEnd = XStart, XEnd, YStart, YEnd
        self.update()

    def coordinateShift(self, canvasPoint):
        return self.XShiftPC(canvasPoint.x), self.YShiftPC(canvasPoint.y)

    # Перевод координаты X из представления человека в представление канвы
    def XShiftPC(self, x):
        return abs(x - self.XStart) * self.canva.width / abs(self.XEnd - self.XStart)

    # Перевод координаты Y из представления человека в представление канвы
    def YShiftPC(self, y):
        return self.canva.height - abs(y - self.YStart) * self.canva.height / abs(self.YEnd - self.YStart)

    # Перевод координаты X из представления канвы в представление человека
    def XShiftCP(self, x):
        return self.XStart + x * abs(self.XEnd - self.XStart) / self.canva.width

    # Перевод координаты Y из представления канвы в представление человека
    def YShiftCP(self, y):
        return self.YEnd - y * abs(self.YEnd - self.YStart) / self.canva.height

    def arrowsShow(self):
        self.XLine = self.canva.create_line(0, self.canva.height / 2, self.canva.width, self.canva.height / 2,
                                            fill='black', width=2, arrow=LAST)

        self.YLine = self.canva.create_line(self.canva.width / 2, self.canva.height, self.canva.width / 2, 0,
                                            fill='black', width=2, arrow=LAST)

    def arrowsHide(self):
        if self.XLine:
            self.canva.delete(self.XLine)
        if self.YLine:
            self.canva.delete(self.YLine)
        self.XLine, self.YLine = None, None

    def arrowsUpdate(self):
        self.arrowsHide()
        self.arrowsShow()

    def gridShow(self):
        # вертикальная сетка (рисуем линии параллельные оси Y)
        step = self.canva.width / 2 / self.gridCoef
        i = 0
        while i < self.canva.width - step:
            i += step
            if math.fabs(i - self.canva.width / 2) < 1:
                continue

            self.gridLines.append(self.canva.create_line(i, self.canva.height, i, 0, fill='grey', width=2, dash=(2, 2)))
            self.gridDashes.append(self.canva.create_line(i, self.canva.height / 2 - 4, i, self.canva.height / 2 + 4, fill='black', width=2))
            self.gridText.append(self.canva.create_text(i, self.canva.height / 2 - 12, text=str(int(self.XShiftCP(i))), font=('Arial', 8, 'bold'), justify=CENTER, fill='black'))

        # горизонтальная сетка (рисуем линии параллельные оси X)
        step = self.canva.height / 2 / self.gridCoef
        i = 0
        while i < self.canva.height - step:
            i += step
            if math.fabs(i - self.canva.height / 2) < 1:
                continue
            self.gridLines.append(self.canva.create_line(0, i, self.canva.width, i, fill='grey', width=2, dash=(2, 2)))
            self.gridDashes.append(self.canva.create_line(self.canva.width / 2 - 4, i, self.canva.width / 2 + 4, i, fill='black', width=2))
            self.gridText.append(self.canva.create_text(self.canva.width / 2 + 12, i, text=str(int(self.YShiftCP(i))),
                                                        font=('Arial', 8, 'bold'), justify=CENTER, fill='black'))

        # Подпись координат
        self.gridText.append(self.canva.create_text(self.canva.width / 2 + 12, 12, text='Y',
                                                    font=('Arial', 10, 'bold'), justify=CENTER, fill='black'))
        self.gridText.append(self.canva.create_text(self.canva.width - 12, self.canva.height / 2 + 12, text='X',
                                                    font=('Arial', 10, 'bold'), justify=CENTER, fill='black'))

    def gridHide(self):
        for line in self.gridLines:
            self.canva.delete(line)

        for dash in self.gridDashes:
            self.canva.delete(dash)

        for text in self.gridText:
            self.canva.delete(text)

        self.gridLines.clear()
        self.gridDashes.clear()

    def gridUpdate(self):
        self.gridHide()
        self.gridShow()

    def update(self):
        self.arrowsUpdate()
        self.gridUpdate()

    def resize(self, event):
        super().resize(event)
        self.arrowsUpdate()
        self.gridUpdate()


class CartesianField(CoordGrid):
    def __init__(self, window, bg, colorPoints='red', XStart=-100, XEnd=100, YStart=-100, YEnd=100, gridCoef=10):
        super(CartesianField, self).__init__(window, bg, XStart, XEnd, YStart, YEnd, gridCoef)

        self.points = []
        self.lines = []
        self.circles = []

        self.colorPoints = colorPoints

        self.canva.createMotion('<1>', self.click)
        self.canva.createMotion('<Motion>', self.showCoords)

    def showCoords(self, event):
        self.canva.create_text(event.x + 10, event.y - 10, text=str(10) + ", " + str(10),
                             font=('Arial', 8, 'bold'), justify=CENTER, fill='black')

    def click(self, event):
        newPoint = CanvasPoint(self.XShiftCP(event.x), self.YShiftCP(event.y), self.colorPoints)
        newPoint.show(self)
        self.points.append(newPoint)


def main():
    root = Tk()
    root.geometry('900x700')
    root['bg'] = 'blue'
    c = CoordGrid(root, 'white')

    c.show(10, 10, 0.7, 0.7)

    root.mainloop()

if __name__ == "__main__":
    main()
