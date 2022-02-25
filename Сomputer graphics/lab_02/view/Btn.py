from tkinter import *
from view.Settings import Settings


class WrapButton:
    def __init__(self, window, txt, command=None, fg='black', padx=15, pady=5, bg=Settings.COLOR_BTN,
                 bgHover=Settings.COLOR_HOVER_BTN, font=('Consolas, 14'), bd=2, name='btn', flagPos='no'):
        self.btn = Button(window, text=txt, padx=padx, pady=pady, font=font, bg=bg, fg=fg, command=command if command else self.plug, bd=bd)
        self.bg = bg
        self.bgHover = bgHover
        self.window = window

        self.btn.bind("<Enter>", self.onEnter)
        self.btn.bind("<Leave>", self.onLeave)
        self.btn.bind("<Motion>", self.motion)

        self.name = name
        self.menu = None

        self.coordX = None
        self.coordY = None
        self.t = None

        self.Pos = flagPos

    def onEnter(self, event):
        event.widget['background'] = self.bgHover

    def onLeave(self, event):
        event.widget['background'] = self.bg
        if self.t:
            self.t.destroy()

    def motion(self, event):
        if self.t:
            self.t.destroy()
        self.t = Label(self.window, text=self.name, bg=Settings.COLOR_HOVER_BTN,
                          fg='black', font=('Arial', 8, 'bold'), bd=1, relief="ridge")
        if self.Pos == 'up':
            self.t.place(x=event.x / 5, y=event.y / 6)

    def show(self, posx=0, posy=0):
        self.coordY = posy
        self.coordX = posx
        self.btn.place(x=posx, y=posy)

    def plug(self):
        print('plug')