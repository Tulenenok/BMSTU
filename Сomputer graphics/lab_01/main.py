
import tkinter as tk

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        group_1 = tk.LabelFrame(self, padx=15, pady=10,
                                text="Add point")
        group_1.pack(padx=10, pady=5)

        tk.Label(group_1, text="X: ").grid(row=0)
        tk.Label(group_1, text="Y: ").grid(row=1)
        tk.Entry(group_1).grid(row=0, column=1, sticky=tk.W)
        tk.Entry(group_1).grid(row=1, column=1, sticky=tk.W)

        self.buttonAdd = tk.Button(self, text="  Add  ")
        self.buttonAdd.pack(padx=10, pady=10, side=tk.RIGHT)

if __name__ == "__main__":
    app = App()
    app.mainloop()