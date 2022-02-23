from model.Point import Point
from view.Settings import Settings


class CanvasPoint(Point):
    def __init__(self, x, y, color=Settings.COLOR_NEW_POINT, fontText=('Arial', 8, 'bold'), colorText='black', showComments=True):
        super().__init__(x, y)
        self.color = color

        self.fontText = fontText
        self.colorText = colorText

        self.p, self.t = None, None

        self.ShowComments = showComments

    def show(self, field):
        try:                                       # Такого метода у канвы может не оказаться
            x, y = field.coordinateShift(self)
        except:
            x, y = self.x, self.y
            print("Вы не переводите координаты точки в координаты канвы, могут быть ошибки")

        self.p = field.create_oval(x - 4, y - 4, x + 4, y + 4, fill=self.color, outline=self.color)
        if self.ShowComments:
            self.t = field.create_text(x + 12, y - 12, text=f'{int(self.x)}, {int(self.y)}', font=self.fontText,
                                       fill=self.colorText)

    def hide(self, field):
        if self.p:
            field.delete(self.p)
        if self.t:
            field.delete(self.t)
        self.p, self.t = None, None

    def changeColor(self, canva, newColor):
        self.color = newColor
        self.reShow(canva)

    def reShow(self, canva):
        self.hide(canva)
        self.show(canva)

    def isClick(self, field, XEvent, YEvent):
        try:                                       # Такого метода у канвы может не оказаться
            x, y = field.coordinateShift(self)
        except:
            x, y = self.x, self.y
            print("Вы не переводите координаты точки в координаты канвы, могут быть ошибки")

        if x - 4 <= XEvent <= x + 4 and y - 4 <= YEvent <= y + 4:
            return True

        return False