from Tkinter import *
import os
import subprocess as sp

def mainMenu(frame) :
	global messageLabel
	label    = ["Add","Delete","Search","Display All Records","Check Eligibility"]
	function = [add,delete,search,display,eligibility]
	messageLabel = Label(frame,text=message)
	messageLabel.pack(side=TOP)
	for i in range(len(label)) :
		Button(frame,text=label[i],command=function[i]).pack()
	displayFrame(Frame(root),frame)

def entry(frame) :
	entryList = []
	for i in range(4) :
		e = Entry(frame)
		e.pack()
		entryList.append(e)
	return entryList
	
#Add Function
def add() :
	global entryList
	frame = Frame(root)
	entryList = entry(frame)
	Button(frame,text="Save",command=save_add).pack(side=LEFT)
	Button(frame,text="Back",command=goMainMenu).pack(side=RIGHT)
	displayFrame(currentFrame,frame)

def save_add() :
	global messageLabel
	record = []
	for i in range(len(entryList)) :
		record.append(entryList[i].get())
	os.system("g++ add.cpp")
	try :
		sp.check_output("./a.out "+record[0]+" "+record[1]+" "+record[2]+" "+record[3],shell=True)
		messageLabel['text'] = "Record Added"
	except :
		messageLabel['text'] = "Error in File"
	displayFrame(currentFrame,mainFrame)

#Search Function
def search() :
	global entryList
	frame = Frame(root)
	entryList = Entry(frame)
	entryList.pack()
	Button(frame,text="Search",command=search_entry).pack(side=LEFT)
	Button(frame,text="Back",command=goMainMenu).pack(side=RIGHT)
	displayFrame(currentFrame,frame)

def search_entry() :
	os.system("g++ search.cpp")
	try :
		sp.check_output("./a.out "+entryList.get(),shell=True)
		messageLabel['text'] = "Record Found"
		display = ""
		with open("displayOutput","r") as fobj :
			display = fobj.read()
		fobj.close();
		frame = Frame(root)
		Label(frame,text=display).pack(side=TOP)
		Button(frame,text="Back",command=goMainMenu).pack(side=BOTTOM)
		displayFrame(currentFrame,frame)
			
	except :
		messageLabel['text'] = "Record Not Found"
		displayFrame(currentFrame,mainFrame)

#Display
def display() :
	os.system("g++ display.cpp")
	try :
		sp.check_output("./a.out ",shell=True)
		display = ""
		with open("displayOutput","r") as fobj :
			display = fobj.read()
		fobj.close();
		frame = Frame(root)
		Label(frame,text=display).pack(side=TOP)
		Button(frame,text="Back",command=goMainMenu).pack(side=BOTTOM)
		displayFrame(currentFrame,frame)
			
	except :
		messageLabel['text'] = "Record Not Found"
		displayFrame(currentFrame,mainFrame)

#Display
def eligibility() :
	global entryList
	frame = Frame(root)
	entryList = Entry(frame)
	entryList.pack()
	Button(frame,text="Check",command=check_eligible).pack(side=LEFT)
	Button(frame,text="Back",command=goMainMenu).pack(side=RIGHT)
	displayFrame(currentFrame,frame)
	

def check_eligible() :
	os.system("g++ eligibility.cpp")
	try :
		sp.check_output("./a.out "+entryList.get(),shell=True)
		display = ""
		with open("displayOutput","r") as fobj :
			display = fobj.read()
		fobj.close();
		frame = Frame(root)
		Label(frame,text=display).pack(side=TOP)
		Button(frame,text="Back",command=goMainMenu).pack(side=BOTTOM)
		displayFrame(currentFrame,frame)
			
	except :
		messageLabel['text'] = "Record Not Found"
		displayFrame(currentFrame,mainFrame)
#Delete Function
def delete() :
	global entryList
	frame = Frame(root)
	entryList = Entry(frame)
	entryList.pack()
	Button(frame,text="Delete",command=save_delete).pack(side=LEFT)
	Button(frame,text="Back",command=goMainMenu).pack(side=RIGHT)
	displayFrame(currentFrame,frame)

def save_delete() :
	os.system("g++ del.cpp")
	try :
		sp.check_output("./a.out "+entryList.get(),shell=True)
		messageLabel['text'] = "Record Deleted"
	except :
		messageLabel['text'] = "Record Not Found"
	displayFrame(currentFrame,mainFrame)

def displayFrame(oldFrame,newFrame):
	global currentFrame
	oldFrame.pack_forget()
	newFrame.pack()
	currentFrame = newFrame

def goMainMenu() :
	global messageLabel
	messageLabel['text'] = " Placement Eligibility App"
	displayFrame(currentFrame,mainFrame)

message = "Placement Eligibility App"
root = Tk(className="i-Placement Eligibility App")
width,height = 500,500
currentFrame = Frame(root)
root.geometry(str(width)+"x"+str(height))
mainFrame = Frame(root)
mainMenu(mainFrame)
root.mainloop()
