from tkinter import *
import serial
import time

czasDoZapisu = 10

arduino = serial.Serial('COM5', 9600, timeout=.1)
okno = Tk()

def zmien():
    arduino.write('s'.encode())

def zapisz():
    arduino.write('writeToSD'.encode())


okno.geometry("300x300")
okno.title("PyArdu")
b = Button(okno, text="Celsjusze", command=zmien)
b.configure(background='black', fg='white')

b.pack()

while True:
    data = arduino.readline()
    if data:
        data = data.decode()
        if (data == "Cel\r\n"):
            b["text"] = "Celsjusze"

        if (data == "Fahren\r\n"):
            b["text"] = "Fahrenheity"

    okno.update()
