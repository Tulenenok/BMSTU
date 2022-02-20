from model.Point import Point


class CanvasPoint(Point):
    def __init__(self, x, y, color):
        super().__init__(x, y)
        self.color = color
