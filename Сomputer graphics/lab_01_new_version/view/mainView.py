from tkinter import *
from view.CanvasField import CanvasField

window = Tk()
canva = CanvasField(window, 500, 450, 0, 1, 0, 1, 'black')
canva.create().pack()
window.mainloop()