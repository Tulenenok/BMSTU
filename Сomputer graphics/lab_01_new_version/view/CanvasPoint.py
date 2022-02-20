from model.Point import Point


class CanvasPoint(Point):
    def __init__(self, x, y, color, fontText=('Arial', 8, 'bold'), colorText='black'):
        super().__init__(x, y)
        self.color = color

        self.fontText = fontText
        self.colorText = colorText

        self.p, self.t = None, None

    def show(self, field, showText=True):
        try:                                       # Такого метода у канвы может не оказаться
            x, y = field.coordinateShift(self)
        except:
            x, y = self.x, self.y
            print("Вы не переводите координаты точки в координаты канвы, могут быть ошибки")

        self.p = field.canva.create_oval(x - 4, y - 4, x + 4, y + 4, fill=self.color, outline=self.color)
        if showText:
            self.t = field.canva.create_text(x + 7, y - 7, text=f'{self.x}, {self.y}', font=self.fontText,
                                       fill=self.colorText)

    def hide(self, field):
        if self.p:
            field.canva.delete(self.p)
        if self.t:
            field.canva.delete(self.t)
        self.p, self.t = None, None

    def changeColor(self, canva, newColor):
        self.color = newColor
        self.hide(canva)
        self.show(canva)

    def reShow(self, canva):
        self.hide(canva)
        self.show(canva)
