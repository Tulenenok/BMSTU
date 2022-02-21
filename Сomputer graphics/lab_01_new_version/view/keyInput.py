from tkinter import *
from model.Tools import Tools


class XYForm:
    def __init__(self, root, color, text, widthEntry, command, btnText, padx=5, pady=10, width=10,
                 font=('Arial', 11, 'bold'), fg="#f1e4de"):
        self.f = LabelFrame(root, bg=color, text=text, padx=padx, pady=pady, width=width, font=font, fg=fg)
        self.xEntry = Entry(self.f, width=widthEntry)
        self.yEntry = Entry(self.f, width=widthEntry)
        self.btn = Button(self.f, text=btnText, command=command)

        self.btn.bind("<Enter>", self.onEnter)
        self.btn.bind("<Leave>", self.onLeave)

    def onEnter(self, btn):
        btn.widget['background'] = '#deebf1'

    def onLeave(self, btn):
        btn.widget['background'] = 'SystemButtonFace'

    def show(self, color, posx=10, poxy=10):
        self.f.propagate(0)

        Label(self.f, text="X: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=0)
        Label(self.f, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=1)
        Label(self.f, text="Y: ", bg=color, font=('Arial', 10, 'bold'), fg="#f1e4de").grid(row=2)

        self.xEntry.grid(row=0, column=1, sticky=W)
        self.yEntry.grid(row=2, column=1, sticky=W)

        Label(self.f, text=" ", bg=color, font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=3)
        self.btn.grid(row=4, column=1, sticky="es")

        # self.f.pack(side=packSide, anchor=packAnchor)
        self.f.place(x=posx, y=poxy)

    def clear(self):
        self.xEntry.delete(0, END)
        self.yEntry.delete(0, END)

class pointAddDel():
    def __init__(self, window, row, column, color, addFunc, delFunc, widthInput=18):
        self.window = window
        self.f = Frame(width=row, height=column, bg=color)
        self.f.propagate(0)

        self.addXYForm = XYForm(self.f, color, 'Add point', widthInput, self.__addPointFunc, '  Add  ')
        self.delXYForm = XYForm(self.f, color, 'Del point', widthInput, self.__addPointFunc, '  Del  ')

        self.addXYForm.show(color, LEFT, 'n')
        self.delXYForm.show(color, RIGHT, 'ne')

    def create(self):
        return self.f

    def __addPointFunc(self):
        inputX = self.addXYForm.xEntry.get()
        inputY = self.addXYForm.yEntry.get()

        if Tools.isInt(inputX) and Tools.isInt(inputY):
            window.allFrames[OBJ_TEXT_POINTS].insert(END, f'({inputX}; {inputY})  ')
            window.allFrames[OBJ_FIELD].createPoint(int(inputX), int(inputY))

            self.addXYForm.xEntry.delete(0, END)
            self.addXYForm.yEntry.delete(0, END)
        else:
            showinfo('Error', 'Координаты точки введены неверно')

    def __delPointFunc(self):
        inputX = self.__xDel.get()
        inputY = self.__yDel.get()
        if Check.isInt(inputX) and Check.isInt(inputY):
            if not window.allFrames[OBJ_FIELD].delPoint(int(inputX), int(inputY)):
                showinfo('Error', 'Точка с такими координатами на поле отсутствует')
            else:
                self.__xDel.delete(0, END)

                self.__yDel.delete(0, END)
        else:
            showinfo('Error', 'Координаты точки введены неверно')

    def startingSettings(self):
        self.addXYForm.clear()
        self.delXYForm.clear()