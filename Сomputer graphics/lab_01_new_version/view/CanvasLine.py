from model.Line import Line
from view.CanvasPoint import CanvasPoint


class CanvasLine(Line):
    def __init__(self, pointA, pointB, color, width=2, dash=(0, 0)):
        super().__init__(pointA, pointB)
        self.color = color
        self.width = width
        self.dash = dash

        self.l = None

    def show(self, canva, showText=True):
        try:                                                   # Такого метода у канвы может не оказаться
            xStart, yStart = canva.coordinateShift(self.start)
        except:
            xStart, yStart = self.start.x, self.start.y
            print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

        if self.start.x == self.end.x and self.start.y == self.end.y:
            print("Нельзя строить линию по одной точке")
            return

        # Если линия вертикальная, то нужно поменять y от начала координатной сетки до конца
        elif self.start.x == self.end.x:
            self.l = canva.field.create_line(xStart, 0, xStart, canva.heightField,
                                             fill=self.color, width=self.width, dash=self.dash)

        # Если линия горизонтальная, то нужно поменять x от начала координатной сетки до конца
        elif self.start.y == self.end.y:
            self.l = canva.field.create_line(0, yStart, canva.widthField, yStart,
                                             fill=self.color, width=self.width, dash=self.dash)

        # Линия наклонная, надо посчитать для нее координаты от самого левого края, до самого правого
        else:
            xS, yS = 0, self.findYByX(0)
            xE, yE = canva.widthField, self.findYByX(canva.widthField)
            try:
                xS, yS = canva.coordinateShift(CanvasPoint(xS, yS, self.color))
                xE, yE = canva.coordinateShift(CanvasPoint(xE, yE, self.color))
            except:
                print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

            self.l = canva.field.create_line(xS, yS, xE, yE, fill=self.color, width=self.width, dash=self.dash)

    def hide(self, canva):
        canva.delete(self.l)
        self.l = None