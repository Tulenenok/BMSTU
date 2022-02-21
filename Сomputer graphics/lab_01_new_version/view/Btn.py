from tkinter import *
from view.Settings import Settings


class WrapButton:
    def __init__(self, window, txt, command=None, fg='black', padx=15, pady=5, bg=Settings.COLOR_BTN,
                 bgHover=Settings.COLOR_HOVER_BTN, font=('Consolas, 14')):
        self.btn = Button(window, text=txt, padx=padx, pady=pady, font=font, bg=bg, fg=fg, command=command if command else self.plug)
        self.bg = bg
        self.bgHover = bgHover

        self.btn.bind("<Enter>", self.onEnter)
        self.btn.bind("<Leave>", self.onLeave)

    def onEnter(self, btn):
        btn.widget['background'] = self.bgHover

    def onLeave(self, btn):
        btn.widget['background'] = self.bg

    def show(self, posx=0, posy=0):
        self.btn.place(x=posx, y=posy)

    def plug(self):
        print('plug')

    # def create(self):
    #     self.__btn('⏎', self.__window.downloadPreviousVersion, 0, 0, name='back')
    #     self.__btn('🗑', self.__window.allFrames[OBJ_FIELD].clearBtn, 0, 1, name='clear all')
    #     # Label(self.__frame, text=" ", bg='black', font=('Arial', 1, 'bold'), fg="#f1e4de").grid(row=0, column=2)
    #     # self.__btn('clear all', self.__txt.delete_all, 0, 2, name='отмена')
    #     self.__btn('🚀', self.__window.allFrames[OBJ_FIELD].findLineBetweenPoints, 0, 10, name='go')
    #     return self.__frame