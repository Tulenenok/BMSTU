from tkinter import *
from view.CanvasField import WrapCanva
from view.Btn import WrapButton

def main():
    root = Tk()
    root.geometry('900x700')
    root['bg'] = 'blue'
    c = WrapCanva(root, bg='white', highlightthickness=0)
    b = WrapButton(root, txt='⏎', command=c.clear)

    c.show(40, 50, 0.7, 0.7)
    b.show(posx=0, posy=0)

    root.mainloop()

if __name__ == "__main__":
    main()