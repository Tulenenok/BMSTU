from model.Line import Line


class CanvasSegment(Line):
    def __init__(self, pointA, pointB, color='black', width=2, dash=None, arrow=None):
        super().__init__(pointA, pointB)
        self.color = color
        self.width = width
        self.dash = dash
        self.arrow = arrow

        self.l = None

        self.ShowComments = True

    def show(self, field):
        try:                                                    # Такого метода у канвы может не оказаться
            xStart, yStart = field.coordinateShift(self.start)  # Точки перевели в понятие канвы
            xEnd, yEnd = field.coordinateShift(self.end)
        except:
            xStart, yStart = self.start.x, self.start.y
            xEnd, yEnd = self.end.x, self.end.y
            print("Вы не переводите координаты точек в координаты канвы, могут быть ошибки")

        xS, yS, xE, yE = xStart, yStart, xEnd, yEnd
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