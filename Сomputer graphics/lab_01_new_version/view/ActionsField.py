from tkinter import *
from view.Btn import WrapButton
from view.keyInput import Zoom
from view.Settings import Settings
from controll.cn import *


class ActionsField:
    def __init__(self, root, canva, bg=Settings.COLOR_MAIN_BG):
        self.root = root
        self.f = Frame(root, width=180, height=200, bg=bg)
        self.canva = canva

        self.bzoom = WrapButton(self.f, txt='🔎', padx=10, pady=8, command=lambda: self.zoom(), bd=0, name='Zoom')

        self.bleft = WrapButton(self.f, txt='⬅', padx=10, pady=8, command=lambda: self.arrowMoveAcrossField(self.canva, 'X', 'left'), bd=0, name='Left')
        self.bright = WrapButton(self.f, txt='➡', padx=10, pady=8, command=lambda: self.arrowMoveAcrossField(self.canva, 'X', 'right'), bd=0, name='Right')
        self.bup = WrapButton(self.f, txt='⬆', padx=14, pady=8, command=lambda: self.arrowMoveAcrossField(self.canva, 'Y', 'up'), bd=0, name='Up')
        self.bdown = WrapButton(self.f, txt='⬇', padx=14, pady=8, command=lambda: self.arrowMoveAcrossField(self.canva, 'Y', 'down'), bd=0, name='Down')

    def zoom(self):
        z = Zoom(self.root, self.canva)
        z.show()

    # Принимает axis как ось (т.е. 'X' или 'Y'), side как сторону, в которую перемещать
    # side = 'left' или 'right' для X, 'up' или 'down' для Y
    def arrowMoveAcrossField(self, canva, axis, side):
        canva.canva.arrowMoveAcrossField(axis, side)


    def show(self, posx, posy, anchor=CENTER):
        self.bleft.show(posx=1, posy=52)
        self.bzoom.show(posx=57, posy=52)
        self.bright.show(posx=2 * 57 - 1, posy=52)

        self.bup.show(posx=57, posy=-1)
        self.bdown.show(posx=57, posy=105)

        self.f.place(x=posx, rely=0.85, anchor=anchor)






