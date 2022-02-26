from model.Point import *
from view.Settings import *
from view.CanvasLine import *
from view.CanvasSegment import *


class CanvasPolygon:
    def __init__(self, points, bdColor=Settings.COLOR_LINE,
               bgColor=Settings.COLOR_LINE, actbdColor=Settings.COLOR_LINE, actbgColor=Settings.COLOR_LINE,
               width=2, showComments=True):
        self.points = points

        self.bdColor = bdColor
        self.bgColor = bgColor
        self.actbdColor = actbdColor
        self.actbgColor = actbgColor
        self.width = width

        self.p = None

        self.ShowComments = showComments

    def show(self, field):
        if self.points == []:
            return

        try:
            CanvasPoints = [field.coordinateShift(point) for point in self.points if point.p]
        except:
            CanvasPoints = [(point.x, point.y) for point in self.points if point.p]
            print("Вы не переводите координаты полигона в координаты канвы, могут быть ошибки")

        if CanvasPoints:
            self.p = field.create_polygon(CanvasPoints, outline=self.bdColor, fill=self.bgColor, width=self.width,
                                          activefill=self.actbgColor, activeoutline=self.actbdColor)

    def hide(self, field):
        if self.p:
            field.delete(self.p)
        self.p = None

    def reShow(self, field):
        self.hide(field)
        self.show(field)

    def addPoint(self, field, newPoint):
        self.points.append(newPoint)
        self.reShow(field)

    def delPoint(self, field, delPoint):
        for i, point in enumerate(self.points):
            if Point.isPointsEqual(point, delPoint):
                self.points.pop(i)

        self.reShow(field)


class CanvasPolLine:
    def __init__(self, points, color=Settings.COLOR_LINE, width=2, showComments=True):
        self.points = points

        self.colorLine = color
        self.colorPoints = color
        self.width = width

        self.lines = []
        self.updateLines()

        self.showComments = showComments

    def show(self, field):
        for p in self.points:
            p.show(field)

        for l in self.lines:
            l.show(field)

    def hide(self, field):
        for p in self.points:
            p.hide(field)

        for l in self.lines:
            l.hide(field)

        self.lines.clear()

    def addPoint(self, field, newPoint):
        if len(self.points) > 0:
            self.lines.append(CanvasSegment(self.points[-1], newPoint, self.colorLine))

        self.points.append(newPoint)
        self.reShow(field)

    def reShow(self, field):
        self.hide(field)
        self.updateLines()
        self.show(field)

    def delPoint(self, field, delPoint):
        wasDel = False
        for i, point in enumerate(self.points):
            if Point.isPointsEqual(point, delPoint):
                point.hide(field)
                self.points.pop(i)
                wasDel = True

        self.reShow(field)
        return wasDel

    def updateLines(self):
        self.lines.clear()
        for i in range(len(self.points) - 1):
            self.lines.append(CanvasSegment(self.points[i], self.points[i + 1], self.colorLine))

    def isPointOn(self, field, X, Y):
        for p in self.points:
            if p.isClick(field, X, Y):
                return True
        return False

    def PointOnWithPoint(self, field, X, Y):
        for p in self.points:
            if p.isClick(field, X, Y):
                return p
        return None

    def updateShowFlag(self, newFlag):
        self.showComments = newFlag
        for p in self.points:
            p.ShowComments = self.showComments

    def changeColor(self, newColorPoint, newColorLine):
        self.colorLine = newColorLine
        self.colorPoints = newColorPoint

        for point in self.points:
            point.color = self.colorPoints

    def rotatePol(self, pointCenter, alpha):
        for point in self.points:
            point.rotate(pointCenter, alpha)
        self.updateLines()

    def shiftPol(self, xShift, yShift):
        for point in self.points:
            point.shift(xShift, yShift)
        self.updateLines()

    def scalePol(self, k):
        for point in self.points:
            point.scale(k)
        self.updateLines()
