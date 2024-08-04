import tkinter as tk
# from tkinter import ttk
import ttkbootstrap as ttk


def convert():
    mile_input = entry_int.get()
    km_output = mile_input * 1.61
    output_string.set(km_output)

# Main Window
window = ttk.Window(themename = 'journal')
window.title('Title')
window.geometry('400x200')
title_label = ttk.Label(master = window, text = 'Example title', font = 'Calibri 24 bold')
title_label.pack()


# Input Field + Button
input_frame = ttk.Frame(master = window)
entry_int = tk.IntVar() # Init's the variable as a tk int
entry = ttk.Entry(
    master = input_frame, 
    textvariable = entry_int) # Stores to entryInt
button = ttk.Button(master = input_frame, text = 'Convert', command = convert)
entry.pack(side = 'left', padx = 10)
button.pack(side = 'left')
input_frame.pack(pady = 10)


# Output
output_string = tk.StringVar()
output_label = ttk.Label(
    master = window, 
    text = 'Output', 
    font = 'Calibri 24', 
    textvariable = output_string)
output_label.pack(pady = 5)




window.mainloop()