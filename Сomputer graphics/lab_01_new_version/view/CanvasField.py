import math
import pickle

from view.CanvasPoint import CanvasPoint
from view.CanvasLine import CanvasLine
from view.CanvasCircle import CanvasCircle
from view.Settings import Settings

from model.Tools import Tools

from tkinter import *


# пример создания  ResizingCanvas(myFrame, width=850, height=400, bg="red", highlightthickness=0)
class ResizingCanvas(Canvas):
    def __init__(self, parent, **kwargs):
        Canvas.__init__(self, parent, **kwargs)
        self.bind("<Configure>", self.resize)

        self.bind('<1>', lambda event: self.click(event))
        self.bind("<Motion>", lambda event: self.showCoords(event))
        self.bind("<Leave>", lambda event: self.hideCoords(event))

        self.height = self.winfo_reqheight()
        self.width = self.winfo_reqwidth()

    def resize(self, event):
        self.width = event.width
        self.height = event.height

        self.config(width=self.width, height=self.height)

    def click(self, event):
        print('click')

    def showCoords(self, event):
        print('showCoords')

    def hideCoords(self, event):
        print('delCoods')


class CoordGrid(ResizingCanvas):
    def __init__(self, window, XStart=-100, XEnd=100, YStart=-100, YEnd=100, gridCoef=10, **kwargs):
        super(CoordGrid, self).__init__(window, **kwargs)
        self.XStart, self.XEnd, self.YStart, self.YEnd = XStart, XEnd, YStart, YEnd

        self.XLine, self.YLine = None, None
        self.gridLines = []
        self.gridDashes = []
        self.gridText = []

        self.gridCoefX = gridCoef
        self.gridCoefY = gridCoef

    def changeLimits(self, XStart, XEnd, YStart, YEnd):
        if self.controllCoef(XStart, XEnd, YStart, YEnd):
            return Tools.EXIT_FAILURE

        self.XStart, self.XEnd, self.YStart, self.YEnd = XStart, XEnd, YStart, YEnd
        self.update()

    def coordinateShift(self, canvasPoint):
        return self.XShiftPC(canvasPoint.x), self.YShiftPC(canvasPoint.y)

    # Перевод координаты X из представления человека в представление канвы
    def XShiftPC(self, x):
        return 0 + (x - self.XStart) * self.width / abs(self.XEnd - self.XStart)

    # Перевод координаты Y из представления человека в представление канвы
    def YShiftPC(self, y):
        return self.height - (y - self.YStart) * self.height / abs(self.YEnd - self.YStart)

    # Перевод координаты X из представления канвы в представление человека
    def XShiftCP(self, x):
        return self.XStart + x * abs(self.XEnd - self.XStart) / self.width

    # Перевод координаты Y из представления канвы в представление человека
    def YShiftCP(self, y):
        return self.YEnd - y * abs(self.YEnd - self.YStart) / self.height

    # Перевод длины отрезка из представления человека в представление канвы
    def XLineShiftPC(self, lenLine):
        return lenLine * self.width / abs(self.XEnd - self.YStart)

    def arrowsShow(self):
        self.XLine = self.create_line(0, self.height / 2, self.width, self.height / 2, fill='black', width=2, arrow=LAST)
        self.YLine = self.create_line(self.width / 2, self.height, self.width / 2, 0, fill='black', width=2, arrow=LAST)

    def arrowsHide(self):
        if self.XLine:
            self.delete(self.XLine)
        if self.YLine:
            self.delete(self.YLine)
        self.XLine, self.YLine = None, None

    def arrowsUpdate(self):
        self.arrowsHide()
        self.arrowsShow()

    def gridShow(self):
        # вертикальная сетка (рисуем линии параллельные оси Y)
        step = self.width / 2 / self.gridCoefX
        i = 0
        while i < self.width - step:
            i += step
            if math.fabs(i - self.width / 2) < 1:
                continue

            self.gridLines.append(self.create_line(i, self.height, i, 0, fill='grey', width=2, dash=(2, 2)))
            self.gridDashes.append(self.create_line(i, self.height / 2 - 4, i, self.height / 2 + 4, fill='black', width=2))
            self.gridText.append(self.create_text(i, self.height / 2 - 12, text=str(int(self.XShiftCP(i))), font=('Arial', 8, 'bold'), justify=CENTER, fill='black'))

        # горизонтальная сетка (рисуем линии параллельные оси X)
        step = self.height / 2 / self.gridCoefY
        i = 0
        while i < self.height - step:
            i += step
            if math.fabs(i - self.height / 2) < 1:
                continue
            self.gridLines.append(self.create_line(0, i, self.width, i, fill='grey', width=2, dash=(2, 2)))
            self.gridDashes.append(self.create_line(self.width / 2 - 4, i, self.width / 2 + 4, i, fill='black', width=2))
            self.gridText.append(self.create_text(self.width / 2 + 12, i, text=str(int(self.YShiftCP(i))),
                                                        font=('Arial', 8, 'bold'), justify=CENTER, fill='black'))

        # Подпись осей координат
        self.gridText.append(self.create_text(self.width / 2 + 12, 12, text='Y',
                                                    font=('Arial', 10, 'bold'), justify=CENTER, fill='black'))
        self.gridText.append(self.create_text(self.width - 12, self.height / 2 + 12, text='X',
                                                    font=('Arial', 10, 'bold'), justify=CENTER, fill='black'))

    def gridHide(self):
        for line in self.gridLines:
            self.delete(line)

        for dash in self.gridDashes:
            self.delete(dash)

        for text in self.gridText:
            self.delete(text)

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
        self.update()

    def zoomPlus(self, XStart, XEnd, YStart, YEnd):
        stepX = abs(XStart - XEnd) / 2 / self.gridCoefX
        while stepX < 1:
            self.gridCoefX -= 1
            stepX = abs(XStart - XEnd) / 2 / self.gridCoefX

        stepY = abs(YStart - YEnd) / 2 / self.gridCoefY
        while stepY < 1:
            self.gridCoefY -= 1
            stepY = abs(YStart - YEnd) / 2 / self.gridCoefY

    def zoomMinus(self, XStart, XEnd, YStart, YEnd):
        stepX = abs(XStart - XEnd) / 2 / self.gridCoefX
        while stepX >= 2 and self.gridCoefX < 10:
            self.gridCoefX += 1
            stepX = abs(XStart - XEnd) / 2 / self.gridCoefX

        stepY = abs(YStart - YEnd) / 2 / self.gridCoefY
        while stepY >= 2 and self.gridCoefY < 10:
            self.gridCoefY += 1
            stepY = abs(YStart - YEnd) / 2 / self.gridCoefY

    def controllCoef(self, XStart, XEnd, YStart, YEnd):
        if abs(XEnd - XStart) <= Settings.MIN_LEN_COORDS:
            print('Слишком маленький масштаб сетки для X')
            return Tools.EXIT_FAILURE

        if abs(YEnd - YStart) <= Settings.MIN_LEN_COORDS:
            print('Слишком маленький масштаб сетки для Y')
            return Tools.EXIT_FAILURE

        self.zoomPlus(XStart, XEnd, YStart, YEnd)
        self.zoomMinus(XStart, XEnd, YStart, YEnd)

        return Tools.EXIT_SUCCESS



class CartesianField(CoordGrid):
    def __init__(self, rootFrame, root, colorPoints=Settings.COLOR_NEW_POINT,
                 XStart=-100, XEnd=100, YStart=-100, YEnd=100, gridCoef=10, **kwargs):
        super(CartesianField, self).__init__(rootFrame, XStart, XEnd, YStart, YEnd, gridCoef, **kwargs)
        self.root = root

        self.points = []
        self.lines = []
        self.circles = []

        self.t = None

        self.colorPoints = colorPoints

    def showCoords(self, event):
        if self.t:
            self.delete(self.t)

        self.t = self.create_text(event.x + 10, event.y - 10,
                                  text=str(int(self.XShiftCP(event.x))) + ", " + str(int(self.YShiftCP(event.y))),
                                  font=('Arial', 8, 'bold'), justify=CENTER, fill='black')

    def hideCoords(self, event):
        if self.t:
            self.delete(self.t)

    def click(self, event):
        newPoint = CanvasPoint(int(self.XShiftCP(event.x)), int(self.YShiftCP(event.y)), self.colorPoints)
        newPoint.show(self)
        self.points.append(newPoint)

        self.save()

    def clear(self):
        for point in self.points:
            point.hide(self)
        self.points.clear()
        self.clearResult()

    def clearResult(self):
        for line in self.lines:
            line.hide(self)
        for circle in self.circles:
            circle.hide(self)

        self.lines.clear()
        self.circles.clear()

    def changeColorPoints(self, points, newColor=Settings.COLOR_POINT_FIRST_SET):
        for p in points.getAll():
            p.changeColor(self, newColor)

    def showPoint(self, x, y, color=Settings.COLOR_NEW_POINT):
        point = CanvasPoint(int(x), int(y))
        self.points.append(point)
        point.show(self)

    def showLine(self, start, end, color=Settings.COLOR_LINE):
        line = CanvasLine(start, end, color)
        self.lines.append(line)
        line.show(self)

    def showCircle(self, center, r, color, width=2, activefill=None):
        circle = CanvasCircle(center, r, color, width, activefill)
        self.circles.append(circle)
        circle.show(self)

    def update(self):
        super().update()

        for point in self.points:
            point.reShow(self)

        for line in self.lines:
            line.reShow(self)

        for circle in self.circles:
            circle.reShow(self)

    def save(self):
        try:
            self.root.saveVersion()
        except:
            print('Вы не используете сохранение')


class WrapCanva:
    def __init__(self, window, Canva=CartesianField, **kwargs):
        self.window = window

        self.frame = Frame(window)
        self.canva = Canva(self.frame, self.window, **kwargs)
        self.frame.bind('<Configure>', self.resize)
        self.canva.place(x=0, y=0)

    def resize(self, event):
        self.canva.resize(event)

    def show(self, x, y, relwidth, relheight):
        self.frame.place(x=x, y=y, relwidth=relwidth, relheight=relheight)

    def clear(self):
        self.canva.clear()

    def getPoints(self):
        return self.canva.points

    def saveVersion(self, f):
        pickle.dump(self.canva.points, f)
        pickle.dump(self.canva.lines, f)
        pickle.dump(self.canva.circles, f)

    def loadVersion(self, f):
        try:
            points = pickle.load(f)
            lines = pickle.load(f)
            circles = pickle.load(f)
        except:
            print('Ошибка загрузки данных')
            return Tools.EXIT_FAILURE

        self.canva.clear()
        self.canva.points = points
        self.canva.lines = lines
        self.canva.circles = circles

        self.canva.update()

        return Tools.EXIT_SUCCESS
