from model.Line import Line
from view.CanvasPoint import CanvasPoint

from tkinter import *


class CanvasLine(Line):
    def __init__(self, pointA, pointB, color='black', width=2, dash=None, arrow=None):
        super().__init__(pointA, pointB)
        self.color = color
        self.width = width
        self.dash = dash
        self.arrow = arrow

        self.l = None

    def show(self, field, showText=True):
        try:                                                    # Такого метода у канвы может не оказаться
            xStart, yStart = field.coordinateShift(self.start)  # Точки перевели в понятие канвы
            xEnd, yEnd = field.coordinateShift(self.end)
        except:
            xStart, yStart = self.start.x, self.start.y
            xEnd, yEnd = self.end.x, self.end.y
            print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

        xS, yS, xE, yE = 0, 0, 0, 0      # Точки на канве, по которым будем рисовать
        if self.start.x == self.end.x and self.start.y == self.end.y:
            print("Нельзя строить линию по одной точке")
            return

        # Если линия вертикальная, то нужно поменять y от начала координатной сетки до конца
        elif self.start.x == self.end.x:
            xS, yS, xE, yE = xStart, 0, xStart, field.height

        # Если линия горизонтальная, то нужно поменять x от начала координатной сетки до конца
        elif self.start.y == self.end.y:
            xS, yS, xE, yE = 0, yStart, field.width, yStart

        # Линия наклонная, надо посчитать для нее координаты от самого левого края, до самого правого
        else:
            helpLine = Line(CanvasPoint(xStart, yStart), CanvasPoint(xEnd, yEnd))   # Прямая с коэффициентами канвы
            xS, yS = 0, helpLine.findYByX(0)
            xE, yE = field.width, helpLine.findYByX(field.width)

        if self.dash and self.arrow:
            self.l = field.create_line(xS, yS, xE, yE, fill=self.color, width=self.width, dash=self.dash, arrow=self.arrow)
        elif self.dash:
            self.l = field.create_line(xS, yS, xE, yE, fill=self.color, width=self.width, dash=self.dash)
        elif self.arrow:
            self.l = field.create_line(xS, yS, xE, yE, fill=self.color, width=self.width, arrow=self.arrow)
        else:
            self.l = field.create_line(xS, yS, xE, yE, fill=self.color, width=self.width)

    def hide(self, field):
        field.delete(self.l)
        self.l = None

    def reShow(self, field):
        self.hide(field)
        self.show(field)