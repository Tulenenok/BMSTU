from controll.controllView import *

from view.RootWithVersions import *
from view.menu import *
from view.CanvasField import *
from view.ActionsField import *
from view.keyInput import *


def main():
    root = RootWithVersions()
    root.geometry('850x650')
    root['bg'] = Settings.COLOR_MAIN_BG

    root.iconphoto(True, PhotoImage(file=r'shared/rootIcon2.png'))
    root.title('Лось - это призвание (посвящается Оленеву)')

    c = WrapCanva(root, Canva=PolygonField, highlightthickness=0)
    menu = menuFrame(root)
    root.config(menu=menu.create(c, inputPointsFromFile, savePointsToFile, clearCanva, root.loadVersion))
    root.setSaveObjs(c)

    act = ActionsField(root, c)
    act.show(posx=105, posy=300)

    c.show(Settings.X_CANVA, Settings.Y_CANVA, Settings.REL_X_CANVA, Settings.REL_Y_CANVA)

    # image = ImageTk.PhotoImage(file=r"C:\projects\Сomputer graphics\lab_02\data\lica.jpg", size=0.5)
    # c.canva.create_image(0, 0, image=image, anchor=NW)

    root.bind("<Control-s>", lambda event: savePointsToFile(c), '+')

    upBtns = UpButtons(root, c)
    upBtns.show()

    addXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Add point', Settings.WIDTH_INPUT,
                       lambda: addPointKey(c, addXYForm), '  Add  ')
    delXYForm = XYForm(root, Settings.COLOR_MAIN_BG, 'Del point', Settings.WIDTH_INPUT,
                       lambda: delPointKey(c, delXYForm), '  Del  ')

    addXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT)
    delXYForm.show(Settings.COLOR_MAIN_BG, Settings.X_INPUT, Settings.Y_INPUT + Settings.STEP_INPUT)

    root.mainloop()


if __name__ == "__main__":
    main()


# from tkinter import *
# from PIL import ImageTk
# from view.CanvasField import *
#
# root = Tk()
# root.geometry('850x650')
# root['bg'] = 'yellow'
# f = WrapCanva(root, width=200, height=200, highlightthickness=0)
# f.show(Settings.X_CANVA, Settings.Y_CANVA, Settings.REL_X_CANVA, Settings.REL_Y_CANVA)
# image = ImageTk.PhotoImage(file = r"C:\projects\Сomputer graphics\lab_02\shared\rootIcon.png")
# f.canva.create_line(10, 10, 100, 100)
# f.canva.create_image(10, 10, image = image, anchor = NW)
# f = Frame(root, width=200, height=200)
# canvas = CartesianField(root, f, width=200, height=200, bg='blue')
# canvas.place(x=0, y=0, relwidth=1)
#
# image = ImageTk.PhotoImage(file = r"C:\projects\Сomputer graphics\lab_02\shared\rootIcon.png")
# canvas.create_image(10, 10, image = image, anchor = NW)
# canvas.create_line(10, 10, 100, 100)
# f.place(x=0, y=0, relwidth=0.7)

# mainloop()