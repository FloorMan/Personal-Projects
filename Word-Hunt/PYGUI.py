import tkinter as tk
import ttkbootstrap as ttk
from tkinter import *
#from PIL import ImageTk,Image
from tkinter import filedialog
import subprocess


def getWordList():
    # Returns name + location of file
    filename = filedialog.askopenfilename(
                                            initialdir="./WordLists", 
                                            title="Select A Word List", 
                                            filetypes=(("text files", "*.txt"), ("any files", "*.*")))
    return filename

def parseWordList():
    print("NOT IMPLEMENTED")

def buildTrie():
    print("NOT IMPLEMENTED")
    
def enterLetterGrid():
    print("NOT IMPLEMENTED")
    
def generateAnswers():
    print("NOT IMPLEMENTED")

def displayAnswers():
    print("NOT IMPLEMENTED")






root = Tk()
root.title('Word Hunt Solver')
wordListFile = None # Contains the absolute path of the wordlist.txt
filename = None

#####                                   #####
##### Frame that contains the word List #####
#####                                   #####

listFrame = ttk.Frame(master = root)
text_box = Text(listFrame, width = 40, height = 50)
text_box.pack()

filename = getWordList()
wordListFile = open(filename, 'r')
allWords = wordListFile.read()
text_box.insert(END, allWords)
wordListFile.close()

#####                                   #####
#####  Frame that contains the answers  #####
#####                                   #####
answerFrame = ttk.Frame(master = root)
subprocess.run(["./wordHunt.exe", filename])

#####                                       #####
#####  Frame that contains the Input Field  #####
#####                                       #####
inputFrame = ttk.Frame(master = root)


# Getting the Word List


#Output = ttk.Label(master = root, text = wordListFile, font = 'Calibri 24 bold')
#Output.pack()



root.mainloop()