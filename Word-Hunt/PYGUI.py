import tkinter as tk
import ttkbootstrap as ttk
from tkinter import *
#from PIL import ImageTk,Image
from tkinter import filedialog
import os
import platform
import threading

INPUTWIDTH = 4
INPUTHEIGHT = 4
filename = ""

def getWordList():
    global filename
    # Returns name + location of file
    filename = filedialog.askopenfilename(
                                            initialdir="./WordLists", 
                                            title="Select A Word List", 
                                            filetypes=(("text files", "*.txt"), ("any files", "*.*")))
    return filename

def displayWordList():
    filename = getWordList()
    wordListFile = open(filename, 'r')
    allWords = wordListFile.read()
    text_box.insert(END, allWords)
    wordListFile.close()

def runSolver():
    # Create a thread to run the program and return the answer
    thread1 = threading.Thread(executeCProg)
    thread1.start()

def executeCProg(filename, input):
    #print("Executing C Program")
    version = platform.platform()
    print(version)
    if "Windows" in version:
        os.system(".\\WordHunt.exe " + filename + " " + input)
    else:
        if "/mnt/" in filename:
            filename = filename.replace("/mnt/c/", "C:/")
        print(filename)
        os.system("./WordHunt.exe " + filename + " " + input)
    # subprocess.run(["./WordHunt.exe", filename, input])
    #print('Done')
    displayAnswers()
    
def validate(P):
    if len(P) == 0:
        # empty Entry is ok
        return True
    elif len(P) == 1 and P.isalpha():
        # Entry with 1 character is ok
        return True
    else:
        # Anything else, reject it
        return False    
    
def enterLetterGrid():
    for i in range(INPUTWIDTH):
        for j in range(INPUTHEIGHT):
            vcmd = (inputGridFrame.register(validate), '%P')
            entry = ttk.Entry(inputGridFrame, validate="key", validatecommand=vcmd, width = 1)
            entry.insert(0, ' ')
            entry.grid(row = i, column = j)
            entries.append(entry)
            
def generateAnswers(filename, input):
    for entry in entries:
        input += entry.get()
    #print(input)
    executeCProg(filename, input)
    
    
def displayAnswers():
    #print("Displaying Answers")
    answerFile = open("genAnswers.txt", 'r')
    answers = answerFile.read()
    answerText.delete(1.0, END)
    answerText.insert(END, answers)
    answerFile.close()
    

input = " "

root = ttk.Window(themename = 'journal')
root.title('Word Hunt Solver')
root.geometry('900x700')
rootLabel = ttk.Label(master = root, text = 'Word Hunt Solver', font = 'Calibri 24 bold')
rootLabel.pack()
# Sets up the frames for the word list, input, and answers.
listFrame = ttk.Frame(master = root)     # Left 
inputFrame = ttk.Frame(master = root)    # Middle
answerFrame = ttk.Frame(master = root)   # Right
listFrame.pack(side = "left", fill = "both", expand = True)
inputFrame.pack(side = "left", fill = "both", expand = True)
answerFrame.pack(side = "left", fill = "both", expand = True)

wordListFile = None # Contains the absolute path of the wordlist.txt
filename = None

#####                                   #####
##### Frame that contains the word List #####
#####                                   #####

listLabel = ttk.Label(master = listFrame, text = 'Word List')
listLabel.pack()
text_box = Text(listFrame, width = 40, height = 50)
text_box.pack(pady = 10)
displayWordList()
# threadWordList = threading.Thread(target = displayWordList)

#####                                   #####
#####  Frame that contains the Input    #####
#####                                   #####

inputTopFrame = ttk.Frame(master = inputFrame)
inputGridFrame = ttk.Frame(master = inputFrame)
inputBottomFrame = ttk.Frame(master = inputFrame)
inputTopFrame.pack(fill = "both", expand = True)
inputGridFrame.pack(fill = "both", expand = True)
inputBottomFrame.pack(fill = "both", expand = True)

inputLabel = ttk.Label(master = inputTopFrame, text = 'INPUTS')
inputLabel.pack()
entries = []
inputLabel = ttk.Label(master = inputBottomFrame, text = 'BUTTON')
inputLabel.pack()
enterLetterGrid()
inputButton = ttk.Button(master = inputBottomFrame, text = 'Generate Answers', command = lambda:  generateAnswers(filename, input))
inputButton.pack()

#####                                       #####
#####   Frame that contains the Answers     #####
#####                                       #####

answerLabel = ttk.Label(master = answerFrame, text = 'Answers')
answerText = Text(answerFrame, width = 40, height = 50)

answerLabel.pack()
answerText.pack(pady = 10)

# Getting the Word List


#Output = ttk.Label(master = root, text = wordListFile, font = 'Calibri 24 bold')
#Output.pack()



root.mainloop()