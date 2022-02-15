from tkinter import *
from tkinter.messagebox import *
from drawErrors import Check
from drawControll import controll
import model
from consts import *
import shutil
from idlelib.tooltip import Hovertip
from tools import CreateToolTip
import pickle

class Window:
    def __init__(self, name, size, color):
        self.__name = name
        self.__size = size
        self.__color = color
        self.allFrames = {}
        self.create()

        self.__prevVersionPP = FILE_PREVIOUS_VERSION_P_P
        self.__prevVersionP = FILE_PREVIOUS_VERSION_P
        self.__prevVersion = FILE_PREVIOUS_VERSION
        self.__curVersion = FILE_CURRENT_VERSION

        self.__startingSetting()

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

    def __startingSetting(self):
        with open(self.__prevVersionPP, 'w') as f:
            pass

        with open(self.__prevVersionP, 'w') as f:
            pass

        with open(self.__prevVersion, 'w') as f:
            pass

        with open(self.__curVersion, 'w') as f:
            pass

    def __saveShift(self):
        shutil.copyfile(self.__prevVersionP, self.__prevVersionPP)
        shutil.copyfile(self.__prevVersion, self.__prevVersionP)
        shutil.copyfile(self.__curVersion, self.__prevVersion)

    def saveCondition(self):
        self.__saveShift()

        with open(self.__curVersion, 'wb') as f:
            self.allFrames[OBJ_ADD_DEL_BTN].saveCondition(f)
            self.allFrames[OBJ_FIELD].saveCondition(f)

    def __downloadShift(self):
        shutil.copyfile(self.__prevVersion, self.__curVersion)
        shutil.copyfile(self.__prevVersionP, self.__prevVersion)
        shutil.copyfile(self.__prevVersionPP, self.__prevVersionP)

    def downloadPreviousVersion(self):
        with open(self.__prevVersion, 'rb') as f:
            try:
                self.allFrames[OBJ_ADD_DEL_BTN].downloadPreviousVersion(f)
                self.allFrames[OBJ_FIELD].downloadPreviousVersion(f)

            except:
                showinfo('Error', 'Возникли неожиданные затруднения. \n\n Если вы еще ничего не успели поменять, не пугайтесь, '
                                  'оно так и должно работать. \n\n'
                                  'А вот если успели... зовите фиксиков')
                return

        self.__downloadShift()

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
    def __init__(self, window, row, column, color):
        self.__maindWindow = window
        self.__f = Frame(width=row, height=column, bg=color)
        self.__f.propagate(0)
        self.__widthInput = 18

        self.__add = LabelFrame(self.__f, padx=5, pady=10, width=10, text="Add point", font=('Arial', 11, 'bold'),
                                bg=color, fg="#f1e4de")
        self.__xAdd = Entry(self.__add, width=self.__widthInput)
        self.__yAdd = Entry(self.__add, width=self.__widthInput)
        self.__buttonAdd = Button(self.__add, text="  Add  ", command=self.__addPointFunc)

        self.__del = LabelFrame(self.__f, padx=5, pady=10, text="Del point", font=('Arial', 11, 'bold'), bg=color, fg="#f1e4de")
        self.__xDel = Entry(self.__del, width=self.__widthInput)
        self.__yDel = Entry(self.__del, width=self.__widthInput)
        self.__buttonDel = Button(self.__del, text="  Del  ", command=self.__delPointFunc)

        self.__showAdd(color)
        self.__showDel(color)

    def __onEnter(self, btn):
        btn.widget['background'] = '#deebf1'

    def __onLeave(self, btn):
        btn.widget['background'] = 'SystemButtonFace'

    def __showAdd(self, color):
        self.__add.propagate(0)

        Label(self.__add, text="X: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=0)
        Label(self.__add, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=1)
        Label(self.__add, text="Y: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=2)

        self.__xAdd.grid(row=0, column=1, sticky=W)
        self.__yAdd.grid(row=2, column=1, sticky=W)

        Label(self.__add, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=3)
        self.__buttonAdd.grid(row=4, column=1, sticky="es")

        self.__add.pack(side=LEFT, anchor="n")

        self.__buttonAdd.bind("<Enter>", self.__onEnter)
        self.__buttonAdd.bind("<Leave>", self.__onLeave)

    def __showDel(self, color):
        self.__del.propagate(0)
        Label(self.__del, text="X: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=0)
        Label(self.__del, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=1)
        Label(self.__del, text="Y: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=2)

        self.__xDel.grid(row=0, column=1, sticky=W)
        self.__yDel.grid(row=2, column=1, sticky=W)

        Label(self.__del, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=3)
        self.__buttonDel.grid(row=4, column=1, sticky="es")

        self.__del.pack(side=RIGHT, anchor="ne")

        self.__buttonDel.bind("<Enter>", self.__onEnter)
        self.__buttonDel.bind("<Leave>", self.__onLeave)

    def create(self):
        return self.__f

    def __addPointFunc(self):
        inputX = self.__xAdd.get()
        inputY = self.__yAdd.get()
        if Check.isInt(inputX) and Check.isInt(inputY):
            window.allFrames[OBJ_TEXT_POINTS].insert(END, f'({inputX}; {inputY})  ')
            window.allFrames[OBJ_FIELD].createPoint(inputX, inputY)
            self.__xAdd.delete(0, END)
            self.__yAdd.delete(0, END)
        else:
            showinfo('Error', 'Координаты точки введены неверно')

    def __delPointFunc(self):
        inputX = self.__xDel.get()
        inputY = self.__yDel.get()
        if Check.isInt(inputX) and Check.isInt(inputY):
            if not window.allFrames[OBJ_FIELD].delPoint(inputX, inputY):
                showinfo('Error', 'Точка с такими координатами на поле отсутствует')
            else:
                self.__xDel.delete(0, END)
                self.__yDel.delete(0, END)
        else:
            showinfo('Error', 'Координаты точки введены неверно')

    def startingSettings(self):
        self.__xAdd.delete(0, END)
        self.__yAdd.delete(0, END)
        self.__xDel.delete(0, END)
        self.__yDel.delete(0, END)

    def saveCondition(self, file):
        pickle.dump(self.__xAdd.get(), file)
        pickle.dump(self.__yAdd.get(), file)
        pickle.dump(self.__xDel.get(), file)
        pickle.dump(self.__yDel.get(), file)

    def downloadPreviousVersion(self, file):
        x_add = pickle.load(file)
        y_add = pickle.load(file)
        x_del = pickle.load(file)
        y_del = pickle.load(file)

        self.startingSettings()

        self.__xAdd.insert(0, x_add)
        self.__yAdd.insert(0, y_add)
        self.__xDel.insert(0, x_del)
        self.__yDel.insert(0, y_del)

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

    def replaceText(self, newText):
        self.__text.configure(state=NORMAL)
        self.delete_all()
        self.insert(END, newText)
        self.__text.configure(state=DISABLED)

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

    def startingSettings(self):
        self.replaceText("")

class Field:
    def __init__(self, window, width, height, bg, koefGrid=25, gridColor='grey'):
        self.__window = window
        self.__width = width
        self.__heigh = height
        self.__step = width // koefGrid
        self.__gridColor = gridColor

        self.__lenX = 500                        # размеры окна
        self.__lenY = 450
        self.__startGridY = 25                   # координаната, на которой рисуется ось Y
        self.__startGridX = self.__lenX - 70     # координаната, на которой рисуется ось X

        self.__leftXCoord = 0
        self.__rightXCoord = self.__width

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

        textPoints.insert(END, f'({x}; {y})  ')
        self.points.append(point)
        self.coordsForCanvas.append((event.x, event.y))
        self.coordsForPeople.append((x, y))

        self.__window.saveCondition()

    def __showCoords(self, event):
        if self.__showCoordText != 1:
            self.__c.itemconfigure(self.__showCoordText, state='hidden')

        x = event.x - self.__startGridY
        y = self.__startGridX - event.y
        self.__showCoordText = self.__c.create_text(event.x + 10, event.y - 10, text=str(x) + ", " + str(y),
                                                    font=('Arial', 8, 'bold'), justify=CENTER, fill='black')

    def fillTextFrame(self):
        str = ""
        for p in self.coordsForPeople:
            str += f'({p[0]}; {p[1]})  '
        window.allFrames[OBJ_TEXT_POINTS].replaceText(str)

    def createPoint(self, x, y, color='#8eb2ac'):
        xOnCanvas, yOnCanvas = self.fromPeopleToCanvas((x, y))

        point = self.__c.create_oval(xOnCanvas - 4, yOnCanvas - 4, xOnCanvas + 4, yOnCanvas + 4,
                             fill=color, outline='#8eb2ac')
        self.points.append(point)

        self.coordsForCanvas.append((xOnCanvas, yOnCanvas))
        self.coordsForPeople.append((x, y))

    def delPoint(self, x, y):
        xOnCanvas = int(x) + self.__startGridY
        yOnCanvas = self.__startGridX - int(y)
        for i, point in enumerate(self.coordsForPeople):
            if (int(x), int(y)) == point or (x, y) == point:
                self.__c.delete((xOnCanvas, yOnCanvas))
                self.coordsForPeople.pop(i)
                self.coordsForCanvas.pop(i)
                self.__c.delete(self.points[i])
                self.points.pop(i)

                self.fillTextFrame()
                return 1
        return 0

    def clear(self):
        for i, line in enumerate(self.lines):
            self.__c.delete(line)
            self.lines.pop(i)

        while len(self.coordsForPeople) != 0:
            self.delPoint(self.coordsForPeople[0][0], self.coordsForPeople[0][1])

    def clearBtn(self):
        self.clear()
        self.__window.saveCondition()

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

    def update(self):
        self.clear()
        for point in self.coordsForPeople:
            self.createPoint(point[0], point[1])

    def startingSettings(self):
        self.clear()

    def saveCondition(self, file):
        pickle.dump(self.coordsForCanvas, file)
        pickle.dump(self.coordsForPeople, file)
        pickle.dump(self.points, file)

    def showAllPoints(self):
        self.points = []
        for point in self.coordsForCanvas:
            p = self.__c.create_oval(point[0] - 4, point[1] - 4, point[0] + 4, point[1] + 4,
                                     fill='#8eb2ac', outline='#8eb2ac')
            self.points.append(p)

    def downloadPreviousVersion(self, file):
        self.clear()
        self.coordsForCanvas = pickle.load(file)
        self.coordsForPeople = pickle.load(file)

        self.fillTextFrame()

        self.showAllPoints()

    def fromPeopleToCanvas(self, point):
        return int(point[0]) + self.__startGridY, self.__startGridX - int(point[1])

    def findLineBetweenPoints(self):
        rc = model.findLine(self.coordsForPeople)
        if rc == 0:
            showinfo("Error", 'Произошла ошибка \n\n Проверьте, что количество введенных точек больше 2')
            return

        startLine, endLine, rightSet, lineSet, leftSet = model.findLine(self.coordsForPeople)
        self.clear()

        for point in rightSet:
            self.createPoint(point[0], point[1], '#E40045')

        for point in leftSet:
            self.createPoint(point[0], point[1], '#530FAD')

        for point in lineSet:
            self.createPoint(point[0], point[1], '#CCF600')

        xStart, yStart = self.__leftXCoord, model.ByXFindYOnLine(self.__leftXCoord, startLine, endLine)
        xEnd, yEnd = self.__rightXCoord, model.ByXFindYOnLine(self.__rightXCoord, startLine, endLine)

        start, end = self.fromPeopleToCanvas((xStart, yStart)), self.fromPeopleToCanvas((xEnd, yEnd))
        self.lines.append(self.__c.create_line(start[0], start[1], end[0], end[1]))

class SpecialBtns:
    def __init__(self, window, txt, bg, fg, padx, pady, font=('Consolas, 14')):
        self.__window = window
        self.__txt = txt
        self.__bg = bg
        self.__fg = fg
        self.__padx = padx
        self.__pady = pady
        self.__font = font
        self.__frame = Frame(bg='#7c7b89')

    def __onEnter(self, btn):
        btn.widget['background'] = '#deebf1'

    def __onLeave(self, btn):
        btn.widget['background'] = self.__bg

    def __btn(self, text, command, row, column, sticky='NWSE', name='button'):
        btn = Button(self.__frame, text=text, padx=self.__padx, pady=self.__pady, font=self.__font,
                          bg=self.__bg, fg=self.__fg,
                          command=command)
        btn.bind("<Enter>", self.__onEnter)
        btn.bind("<Leave>", self.__onLeave)

        #CreateToolTip(btn, text=name, waittime=0)
        # Listbox.ToolTip(btn, ['tooltip', name])

        btn.grid(row=row, column=column, sticky=sticky)

    def create(self):
        self.__btn('⏎', self.__window.downloadPreviousVersion, 0, 0, name='back')
        self.__btn('🗑', self.__window.allFrames[OBJ_FIELD].clearBtn, 0, 1, name='clear all')
        # Label(self.__frame, text=" ", bg='black', font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=0, column=2)
        # self.__btn('clear all', self.__txt.delete_all, 0, 2, name='отмена')
        self.__btn('🚀', self.__window.allFrames[OBJ_FIELD].findLineBetweenPoints, 0, 10, name='go')
        return self.__frame

window = Window('Lab 01', '900x580', '#7c7b89')
menu = menuFrame(window)
textPoints = TextArea(38, 10, "#f1e4de", "black")
field = Field(window, 500, 450, "white")
specBtn = SpecialBtns(window, textPoints, "#f1e4de", "black", 15, 5)
addDel = pointAddDel(window, 100, 350, '#7c7b89')

window.allFrames = {OBJ_ADD_DEL_BTN : addDel, OBJ_TEXT_POINTS : textPoints, OBJ_FIELD : field, OBJ_SPC_BTN : specBtn}
window.saveCondition()

window.addMenu()
window.addFrame(row=0, column=0, frame=auxiliaryFrames.create(10, 20, '#7c7b89'), columnspan=5)
window.addFrame(row=0, column=0, frame=auxiliaryFrames.create(20, 10, '#7c7b89'), rowspan=5)

#window.addFrame(row=1, column=1, frame=auxiliaryFrames.create(100, 350, '#7c7b89'))            # говно-заглушка надо фиксить
window.addFrame(row=1, column=1, frame=addDel.create())                     # попытка не пытка

window.addFrame(row=2, column=1, frame=auxiliaryFrames.createLabel(10, 10, "Previously entered points", '#f1e4de', '#7c7b89', font=('Arial', 10, 'bold')), columnspan=2)

window.addFrame(row=3, column=1, frame=textPoints.create())

window.addFrame(row=1, column=2, frame=auxiliaryFrames.create(32, 50, '#7c7b89'), rowspan=5)
window.addFrame(row=1, column=3, frame=field.create(), rowspan=5, sticky='S')

window.addFrame(row=1, column=3, frame=specBtn.create(), sticky='NW')
window.showWindow()


