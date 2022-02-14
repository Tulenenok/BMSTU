from tkinter import *
from tkinter.messagebox import *
from drawErrors import Check
from drawControll import controll

class Window:
    def __init__(self, name, size, color):
        self.__name = name
        self.__size = size
        self.__color = color
        self.create()

    def create(self):
        self.__window = Tk()
        self.__window.title(self.__name)
        self.__window.geometry(self.__size)
        self.__window['bg'] = self.__color
        self.__window.resizable(width=False, height=False)                 # размеры окна не меняются

    def addFrame(self, row, column, frame, columnspan=1, rowspan=1, sticky='NWSE'):
        frame.grid(row=row, column=column, columnspan=columnspan, rowspan=rowspan, sticky=sticky)

    def addMenu(self):
        self.__window.config(menu=menu.create())

    def showWindow(self):
        self.__window.mainloop()

    def closeWindow(self):
        self.__window.destroy()

class menuFrame:
    def __init__(self, window):
        self.__menu = Menu()
        self.__window = window

    def __makeDropDown(self, dictLabels):
        newItem = Menu(self.__menu, tearoff=0)
        for item in dictLabels:
            newItem.add_command(label=item, command=dictLabels[item])
        return newItem

    def create(self):
        self.__menu.add_cascade(label='Menu', menu=self.__makeDropDown({'Информация о программе': self.__info_programm,
                                                                        'Информация об авторе': self.__info_author,
                                                                        'Выход': self.__window.closeWindow
                                                                        }))
        return self.__menu

    def __info_author(self):
        showinfo('Info', 'Автор: Гурова Наталия ИУ7-44Б')

    def __info_programm(self):
        showinfo('Info', 'Программа была создана 13.02.22 \n\n'
                         'Задание: множество точек на плоскости разбить на два подмножества прямой,'
                         'проходящей через две различные точки так, чтобы количества точек, '
                         'лежащих по разные стороны прямой, проходящей через эти две точки, '
                         'различались наименьшим образом. Каждое из полученных множеств поместить внутрь '
                         'окружности минимального радиуса. Найти суммарную площадь, покрытую данными окружностями.')

class auxiliaryFrames:
    @staticmethod
    def create(row, column, color):
        entry = Frame(width=row, height=column, bg=color)
        return entry

    @staticmethod
    def createLabel(row, column, text, color, backgroundColor, font):
        f = Frame(width=row, height=column, bg=backgroundColor)
        label = Label(f, text=text, fg=color, bg=backgroundColor, font=font)
        label.grid(column=0, row=0, sticky='w')
        return f


class pointAddDel():
    def __init__(self, row, column, color):
        self.__f = Frame(width=row, height=column, bg=color)
        self.__f.propagate(0)
        self.__widthInput = 18
        self.__showAdd(color)
        self.__showDel(color)


    def __showAdd(self, color):
        add = LabelFrame(self.__f, padx=5, pady=10, width=10,
                         text="Add point",  font=('Arial', 11, 'bold'), bg=color, fg="#f1e4de")

        add.propagate(0)

        self.__xAdd = Label(add, text="X: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=0)
        Label(add, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=1)
        self.__yAdd = Label(add, text="Y: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=2)
        Entry(add, width=self.__widthInput).grid(row=0, column=1, sticky=W)
        Entry(add, width=self.__widthInput).grid(row=2, column=1, sticky=W)

        Label(add, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=3)
        self.buttonAdd = Button(add, text="  Add  ")
        self.buttonAdd.grid(row=4, column=1, sticky="es")

        add.pack(side=LEFT, anchor="n")

    def __showDel(self, color):
        delF = LabelFrame(self.__f, padx=5, pady=10,
                         text="Del point", font=('Arial', 11, 'bold'), bg=color, fg="#f1e4de")

        self.__xDel = Label(delF, text="X: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=0)
        Label(delF, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=1)

        self.__yDel = Label(delF, text="Y: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=2)
        Entry(delF, width=self.__widthInput).grid(row=0, column=1, sticky=W)
        Entry(delF,  width=self.__widthInput ).grid(row=2, column=1, sticky=W)

        Label(delF, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=3)
        self.buttonAdd = Button(delF, text="  Del  ")
        self.buttonAdd.grid(row=4, column=1, sticky="es")

        delF.pack(side=RIGHT, anchor="ne")

    def create(self):
        return self.__f

class TextArea:
    def __init__(self, width, height, bg, fg):
        self.__frame = Frame()
        self.__text = Text(self.__frame, width=width, height=height, bg=bg, fg=fg, wrap=WORD,
                           font=('Verdana', 10), insertbackground="black", state=DISABLED)
        self.__text.grid(row=0, column=0)

    def create(self):
        return self.__frame

    def insert(self, position, str):
        self.__text.configure(state=NORMAL)
        self.__text.insert(position, str)
        self.__text.configure(state=DISABLED)

    def get(self):
        return self.__text.get("1.0", "end-1c")

    def delete_all(self):
        self.__text.delete('1.0', 'end')
        self.__text.update()

    def delete(self):
        self.__text.delete('end-2c')
        self.__text.update()

    def update(self):
        coordPoints = self.__takePoints()
        field.delTriangle()
        if coordPoints == None:
            showinfo('Info', 'Точки введены некорректно. Проверьте, что количество координат четно '
                             'и что нет лишних символов.')
            return

        # Поставили на поле точки, которых не хватало
        for i in coordPoints:
            if i not in field.coordsForCanvas:
                field.createPoint(i[0], i[1])

        # Удаляем с поля точки, которых нет в форме
        i = 0
        while i < len(field.coordsForCanvas):
            if field.coordsForCanvas[i] not in coordPoints:
                field.delPoint(field.points[i])

                field.coordsForCanvas.pop(i)
                field.points.pop(i)
            else:
                i += 1

    def __takePoints(self):
        text = self.get()
        for i in text:
            if i not in '0123456789.;() ':
                return None
        points = self.parser(text)
        if len(points) % 2 == 1:
            return None
        points = [(points[i], points[i + 1]) for i in range(0, len(points), 2)]
        return points

    # Он считает, что строка валидна, то есть лишних символов в ней нет!
    def parser(self, text):
        list = text.split(' ')
        points = []
        for i in list:
            i = i.split(';')
            for j in i:
                j = j.split('(')
                for k in j:
                    k = k.split(')')
                    for l in k:
                        if Check.isFloat(l):
                            points.append(float(l))
        return points

    def calculate(self):
        self.update()
        field.delTriangle()
        print(field.coordsForCanvas)
        minPoints = controll(field.coordsForCanvas)
        if minPoints == None:
            showinfo('Info', 'Треугольник не найден. Проверьте, сколько у вас уникальных точек. '
                             'Проверьте, что точки не лежат на одной прямой.')
            return
        field.drawTriangle(minPoints, "#f4d75e")

class Field:
    def __init__(self, width, height, bg, koefGrid=25, gridColor='grey'):
        self.__width = width
        self.__heigh = height
        self.__step = width // koefGrid
        self.__gridColor = gridColor

        self.__lenX = 500                        # размеры окна
        self.__lenY = 450
        self.__startGridY = 25                   # координаната, на которой рисуется ось Y
        self.__startGridX = self.__lenX - 70     # координаната, на которой рисуется ось X

        self.__frame = Frame(bg=bg)
        self.__c = Canvas(self.__frame, width=self.__lenX, height=self.__lenY, bg=bg)
        self.__c.grid(row=0, column=0, sticky='S')

        self.coordsForCanvas = []
        self.coordsForPeople = []
        self.points = []

        self.lines = []

        self.__showCoordText = 1

        self.__c.bind('<1>', lambda event: self.__click(event))
        self.__c.bind("<Motion>", lambda event: self.__showCoords(event))
        self.__ownGrid()

    def __ownGrid(self):
        # вертикальная сетка |
        for i in range(self.__startGridY, self.__lenX, self.__step):
            self.__c.create_line(i, self.__startGridX, i, 0, fill=self.__gridColor, width=2, dash=(2, 2))

        # горизонтальная сетка --
        for i in range(self.__startGridX, 0, -self.__step):
            self.__c.create_line(self.__startGridY, i, self.__lenY + 50, i, fill=self.__gridColor, width=2, dash=(2, 2))

        # вертикальная (ось y) (не зависят от масштаба)
        self.__c.create_line(self.__startGridY, 0, self.__startGridY, self.__lenX, fill='black', width=2, arrow=FIRST)
        # горизонтальная (ось x)
        self.__c.create_line(0, self.__startGridX, self.__lenX, self.__startGridX, fill='black', width=2, arrow=LAST)

        # рисуем черточки на оси y (зависят от масштаба)           # причем как зависят не понятно
        j = 0
        for i in range(self.__width - 6 * self.__step, -2 * self.__step, -self.__step):
            self.__c.create_line(self.__startGridY - 4, i + 50, self.__startGridY + 4, i + 50,
                                 fill='black', width=2)

            if j != 0:
                self.__c.create_text(self.__startGridY - 13, i + 50, text=str(j), font=('Arial', 8, 'bold'), justify=CENTER, fill='black')
            j += self.__step

        # рисуем черточки на оси x
        j = 0
        for i in range(self.__startGridY, self.__lenY + self.__step, self.__step):
            self.__c.create_line(i, self.__startGridX - 5, i, self.__startGridX + 5,
                                 fill='black', width=2)

            if j != 0:
                self.__c.create_text(i, self.__startGridX + 12, text=str(j), font=('Arial', 8, 'bold'), justify=CENTER, fill='black')
            j += self.__step

        # рисуем ноль
        self.__c.create_text(self.__startGridY - 10, self.__startGridX + 10, text=0, font=('Arial', 8, 'bold'), justify=CENTER, fill='black')

    def create(self):
        return self.__frame

    def __click(self, event):
        x = event.x - self.__startGridY
        y = self.__startGridX - event.y
        if x < 0 or y < 0:
            return

        point = self.__c.create_oval(event.x - 4, event.y - 4, event.x + 4, event.y + 4,
                             fill='#8eb2ac', outline='#8eb2ac')

        input.insert(END, f'({x}; {y})  ')
        self.points.append(point)
        self.coordsForCanvas.append((event.x, event.y))
        self.coordsForPeople.append((x, y))

    def __showCoords(self, event):
        if self.__showCoordText != 1:
            self.__c.itemconfigure(self.__showCoordText, state='hidden')

        x = event.x - self.__startGridY
        y = self.__startGridX - event.y
        self.__showCoordText = self.__c.create_text(event.x + 10, event.y - 10, text=str(x) + ", " + str(y),
                                                    font=('Arial', 8, 'bold'), justify=CENTER, fill='black')

    def createPoint(self, x, y):
        point = self.__c.create_oval(x - 4, y - 4, x + 4, y + 4,
                             fill='#8eb2ac', outline='#8eb2ac')
        self.points.append(point)

        self.coordsForCanvas.append((x, y))

    def delPoint(self, point):
        self.__c.delete(point)

    def drawTriangle(self, listPoints, color):
        l1 = self.__c.create_line(listPoints[0][0], listPoints[0][1], listPoints[1][0], listPoints[1][1],
                                  fill=color, width=3)
        l2 = self.__c.create_line(listPoints[0][0], listPoints[0][1], listPoints[2][0], listPoints[2][1],
                                  fill=color, width=3)
        l3 = self.__c.create_line(listPoints[1][0], listPoints[1][1],
                                  listPoints[2][0], listPoints[2][1],
                                  fill=color, width=3)
        self.lines.append(l1)
        self.lines.append(l2)
        self.lines.append(l3)

    def delTriangle(self):
        for i in self.lines:
            self.__c.delete(i)
        self.lines = []

class SpecialBtns:
    def __init__(self, txt, bg, fg, padx, pady, font=('Consolas, 14')):
        self.__txt = txt
        self.__bg = bg
        self.__fg = fg
        self.__padx = padx
        self.__pady = pady
        self.__font = font
        self.__frame = Frame(bg='#7c7b89')

    def __btn(self, text, command, row, column, sticky='NWSE'):
        btn = Button(self.__frame, text=text, padx=self.__padx, pady=self.__pady, font=self.__font,
                          bg=self.__bg, fg=self.__fg,
                          command=command)
        btn.grid(row=row, column=column, sticky=sticky)

    def create(self):
        self.__btn('add point', self.__txt.calculate, 0, 0)
        self.__btn('del point', self.__txt.calculate, 0, 1)
        self.__btn('clear all', self.__txt.delete_all, 0, 2)
        self.__btn('calculate', self.__txt.calculate, 0, 3)
        return self.__frame

window = Window('Lab 01', '900x580', '#7c7b89')
menu = menuFrame(window)
input = TextArea(38, 10, "#f1e4de", "black")
field = Field(500, 450, "white")
specBtn = SpecialBtns(input, "#f1e4de", "black", 15, 5)
addDel = pointAddDel(100, 350, '#7c7b89')

window.addMenu()
window.addFrame(row=0, column=0, frame=auxiliaryFrames.create(10, 20, '#7c7b89'), columnspan=5)
window.addFrame(row=0, column=0, frame=auxiliaryFrames.create(20, 10, '#7c7b89'), rowspan=5)

#window.addFrame(row=1, column=1, frame=auxiliaryFrames.create(100, 350, '#7c7b89'))            # говно-заглушка надо фиксить
window.addFrame(row=1, column=1, frame=addDel.create())            # попытка не пытка

window.addFrame(row=2, column=1, frame=auxiliaryFrames.createLabel(10, 10, "Previously entered points", '#f1e4de', '#7c7b89', font=('Arial', 10, 'bold')), columnspan=2)

window.addFrame(row=3, column=1, frame=input.create())

window.addFrame(row=1, column=2, frame=auxiliaryFrames.create(32, 50, '#7c7b89'), rowspan=5)
window.addFrame(row=1, column=3, frame=field.create(), rowspan=5, sticky='S')

window.addFrame(row=1, column=3, frame=specBtn.create(), sticky='NW')
window.showWindow()


