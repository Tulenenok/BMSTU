from tkinter import *
from tkinter.messagebox import *
from model.Tools import Tools
from view.Settings import Settings
from view.Btn import WrapButton


class XYForm:
    def __init__(self, root, color, text, widthEntry, command, btnText, padx=5, pady=10, width=10,
                 font=('Arial', 11, 'bold'), fg="#f1e4de"):
        self.f = LabelFrame(root, bg=color, text=text, padx=padx, pady=pady, width=width, font=font, fg=fg)
        self.xEntry = Entry(self.f, width=widthEntry)
        self.yEntry = Entry(self.f, width=widthEntry)
        self.btn = Button(self.f, text=btnText, command=command)

        self.btn.bind("<Enter>", self.onEnter)
        self.btn.bind("<Leave>", self.onLeave)

        self.xEntry.bind("<Return>", lambda event: self.yEntry.focus_set())
        self.yEntry.bind("<Return>", lambda event: command())

        self.xEntry.bind("<Down>", lambda event: self.yEntry.focus_set())
        self.yEntry.bind("<Up>", lambda event: self.xEntry.focus_set())

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
        self.xEntry.focus_set()

    def getXY(self):
        return self.xEntry.get(), self.yEntry.get()



class Zoom:
    def __init__(self, root, canva):
        self.z = Toplevel(root)

        self.xStart = Entry(self.z, width=18)
        self.yStart = Entry(self.z, width=18)
        self.xEnd = Entry(self.z, width=18)
        self.yEnd = Entry(self.z, width=18)

        self.btn = WrapButton(self.z, txt='change', padx=10, pady=3, command=lambda: self.changeCoords(canva), font=('Arial', 10, 'bold'))

        self.bindSetting(canva)

    def show(self):
        self.z.geometry('180x195')
        self.z.title('New limits')
        self.z['bg'] = Settings.COLOR_MAIN_BG
        self.z.resizable(0, 0)
        headLabel = Label(self.z, text='Input new limits for grid', bg=Settings.COLOR_MAIN_BG,
                          fg=Settings.COLOR_BTN, font=('Arial', 10, 'bold'))

        XSL = Label(self.z, text='Xmin: ', bg=Settings.COLOR_MAIN_BG, fg=Settings.COLOR_BTN, font=('Arial', 8, 'bold'))
        XEL = Label(self.z, text='Xmax: ', bg=Settings.COLOR_MAIN_BG, fg=Settings.COLOR_BTN, font=('Arial', 8, 'bold'))
        YSL = Label(self.z, text='Ymin: ', bg=Settings.COLOR_MAIN_BG, fg=Settings.COLOR_BTN, font=('Arial', 8, 'bold'))
        YEL = Label(self.z, text='Ymax: ', bg=Settings.COLOR_MAIN_BG, fg=Settings.COLOR_BTN, font=('Arial', 8, 'bold'))

        headLabel.place(x=10, y=10)

        xstart, ystart, xstep, ystep = 10, 15, 42, 25

        XSL.place(x=xstart, y=ystart + ystep)
        self.xStart.place(x=xstart + xstep, y=ystart + ystep)

        XEL.place(x=xstart, y=ystart + 2 * ystep)
        self.xEnd.place(x=xstart + xstep, y=ystart + 2 * ystep)

        YSL.place(x=xstart, y=ystart + 3 * ystep)
        self.yStart.place(x=xstart + xstep, y=ystart + 3 * ystep)

        YEL.place(x=xstart, y=ystart + 4 * ystep)
        self.yEnd.place(x=xstart + xstep, y=ystart + 4 * ystep)

        self.btn.show(posx=52, posy=ystart + 5.3 * ystep)

        self.xStart.focus_set()

    def bindSetting(self, canva):
        self.xStart.bind("<Return>", lambda event: self.xEnd.focus_set())
        self.xEnd.bind("<Return>", lambda event: self.yStart.focus_set())
        self.yStart.bind("<Return>", lambda event: self.yEnd.focus_set())
        self.yEnd.bind("<Return>", lambda event: self.changeCoords(canva))

        self.xStart.bind("<Down>", lambda event: self.xEnd.focus_set())
        self.xEnd.bind("<Up>", lambda event: self.xStart.focus_set())
        self.xEnd.bind("<Down>", lambda event: self.yStart.focus_set())
        self.yStart.bind("<Up>", lambda event: self.xEnd.focus_set())
        self.yStart.bind("<Down>", lambda event: self.yEnd.focus_set())
        self.yEnd.bind("<Up>", lambda event: self.yStart.focus_set())

    def plug(self):
        print('plug')

    def changeCoords(self, canva):
        xMin = self.xStart.get()
        yMin = self.yStart.get()
        xMax = self.xEnd.get()
        yMax = self.yEnd.get()

        xMin = canva.canva.XStart if xMin == '' else xMin
        yMin = canva.canva.YStart if yMin == '' else yMin
        xMax = canva.canva.XEnd if xMax == '' else xMax
        yMax = canva.canva.YEnd if yMax == '' else yMax

        if not Tools.isInt(xMin):
            showinfo('Error', 'Неверно введена xMin')
            return

        if not Tools.isInt(yMin):
            showinfo('Error', 'Неверно введена yMin')
            return

        if not Tools.isInt(xMax):
            showinfo('Error', 'Неверно введена xMax')
            return

        if not Tools.isInt(yMax):
            showinfo('Error', 'Неверно введена yMax')
            return

        xMin, xMax, yMin, yMax = int(xMin), int(xMax), int(yMin), int(yMax)
        if xMin >= xMax:
            showinfo('Error', 'Ввод неверный (xMin >= xMax)')
            return

        if yMin >= yMax:
            showinfo('Error', 'Ввод неверный (yMin >= yMax)')
            return

        if abs(xMin - xMax) <= Settings.MIN_LEN_COORDS:
            showinfo('Warning', f'Невозможно расчертить координатную сетку для оси X при xMax - xMin <= {Settings.MIN_LEN_COORDS}')
            return

        if abs(yMin - yMax) <= Settings.MIN_LEN_COORDS:
            showinfo('Warning', f'Невозможно расчертить координатную сетку для оси Y при yMax - yMin <= {Settings.MIN_LEN_COORDS}')
            return

        canva.canva.changeLimits(xMin, xMax, yMin, yMax)
        print('Change coords --> correct')

        showinfo('Успешно', 'Координаты были успешно изменены.\n\nНовые пределы:\n'
                            f'Xmin = {xMin}\n'
                            f'Xmax = {xMax}\n'
                            f'Ymin = {yMin}\n'
                            f'Ymax = {yMax}\n'
                            f'\n'
                            f'Примечание: те координаты, поля для которых остались незаполненными, сохранили свои значения')

        self.z.destroy()
        # self.clearAll()
        # self.xStart.focus_set()

    def clearAll(self):
        self.xStart.delete(0, END)
        self.xEnd.delete(0, END)
        self.yStart.delete(0, END)
        self.yEnd.delete(0, END)

