from controll.cn import *


def main():
    root = RootWithVersions()
    root.geometry('850x650')
    root['bg'] = Settings.COLOR_MAIN_BG

    root.iconphoto(True, PhotoImage(file=r'../shared/rootIcon.png'))
    root.title('У меня лапки')

    menu = menuFrame(root)

    c = WrapCanva(root, bg='white', highlightthickness=0)
    root.config(menu=menu.create(c, inputPointsFromFile, savePointsToFile, clearCanva, root.loadVersion, go))
    root.setSaveObjs(c)

    # b = WrapButton(root, txt='🗑', command=lambda: clearCanva(c), name='clear all')
    # bcn = WrapButton(root, txt='🚀', command=lambda: go(c), name='make a calculation')
    # binput = WrapButton(root, txt='📂', command=lambda: inputPointsFromFile(c), name='take points from file')
    # boutput = WrapButton(root, txt='📋', command=lambda: savePointsToFile(c), name='save points')
    # breturn = WrapButton(root, txt='⏎', command=lambda: root.loadVersion(), name='cancel')

    act = ActionsField(root, c)
    act.show(posx=105, posy=300)

    c.show(Settings.X_CANVA, Settings.Y_CANVA, Settings.REL_X_CANVA, Settings.REL_Y_CANVA)
    # breturn.show(posx=Settings.X_CANVA, posy=Settings.Y_START_BUTTONS)
    # binput.show(posx=Settings.X_CANVA + 1 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    # boutput.show(posx=Settings.X_CANVA + 2 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    # b.show(posx=Settings.X_CANVA + 3 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)
    # bcn.show(posx=Settings.X_CANVA + 4 * Settings.BTN_STEP, posy=Settings.Y_START_BUTTONS)

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