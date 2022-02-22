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