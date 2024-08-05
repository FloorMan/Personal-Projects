from tkinter import * 

root = Tk()

f = Frame(root, bg = "orange", width = 500, height = 500)
f.pack(side=LEFT, expand = 1)

f3 = Frame(f, bg = "red", width = 500)
f3.pack(side=LEFT, expand = 1, pady = 50, padx = 50)

f2 = Frame(root, bg = "black", height=100, width = 100)
f2.pack(side=LEFT, fill = Y)

b = Button(f2, text = "test")
b.pack()

b = Button(f3, text = "1", bg = "red")
b.grid(row=1, column=3)
b2 = Button(f3, text = "2")
b2.grid(row=1, column=4)
b3 = Button(f3, text = "2")
b3.grid(row=2, column=0)

root.mainloop()