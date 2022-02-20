from tkinter import *

# a subclass of Canvas for dealing with resizing of windows
class ResizingCanvas(Canvas):
    def __init__(self, parent, **kwargs):
        Canvas.__init__(self, parent, **kwargs)
        self.bind("<Configure>", self.on_resize)

        self.height = self.winfo_reqheight()
        self.width = self.winfo_reqwidth()

    def on_resize(self, event):
        self.width = event.width
        self.height = event.height

        self.config(width=self.width, height=self.height)


class auxiliaryFrames:
    @staticmethod
    def create(row, column, color):
        entry = Frame(width=row, height=column, bg=color)
        return entry

def main():
    root = Tk()
    auxiliaryFrames.create(100, 20, 'black').place(x=20, y=20)

    myframe = Frame(root)
    myframe.place(x=250, y=200, relwidth=0.3, relheight=0.15)

    mycanvas = ResizingCanvas(myframe, width=850, height=400, bg="red", highlightthickness=0)
    myframe.bind('<Configure>', mycanvas.on_resize)

    mycanvas.place(x=0, y=0)

    root.mainloop()

if __name__ == "__main__":
    main()