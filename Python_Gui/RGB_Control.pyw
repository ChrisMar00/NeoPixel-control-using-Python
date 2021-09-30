import serial
from tkinter import *

# Change them based on your arduino configuration
port = "COM3"
baudRate = "9600"

# Set ser as serial port COM3 at 9600 baud rate
ser = serial.Serial(port, baudRate)

# Creating a GUI with tkinter
window = Tk()
window.title("RGB Monitor")
window.geometry("575x430")
photo = PhotoImage(file="icon.png")
window.iconphoto(False, photo)
window.configure(bg="black")


# Button functions
def red():
    ser.write("[red]".encode())


def green():
    ser.write("[green]".encode())


def blue():
    ser.write("[blue]".encode())


def white():
    ser.write("[white]".encode())

def neonPurple():
    ser.write("[neonPurple]".encode())

def rgbLoop():
    ser.write("[rgbLoop]".encode())


def strobe():
    ser.write("[strobe]".encode())


def sparkle():
    ser.write("[sparkle]".encode())


def rainbowCycle():
    ser.write("[rainbowCycle]".encode())


def twinkleRandom():
    ser.write("[twinkleRandom]".encode())


def theaterChaseRainbow():
    ser.write("[theaterChaseRainbow]".encode())


def meteorRain():
    ser.write("[meteorRain]".encode())


def off():
    ser.write("[turnOff]".encode())


def setRgb():
    r = entry_RED.get()
    g = entry_GREEN.get()
    b = entry_BLUE.get()
    x = "[setRgb," + r + "," + g + "," + b + ",]"
    ser.write(x.encode())


# Labels / Buttons / Entries
btn_OFF = Button(window, text="OFF", width=15, height=4, command=off, fg="white", bg="black")
btn_RED = Button(window, text="RED", width=15, height=4, command=red, fg="red", bg="black")
btn_GREEN = Button(window, text="GREEN", width=15, height=4, command=green, fg="green", bg="black")
btn_BLUE = Button(window, text="BLUE", width=15, height=4, command=blue, fg="blue", bg="black")
btn_WHITE = Button(window, text="WHITE", width=15, height=4, command=white, fg="white", bg="black")
btn_RGBLoop = Button(window, text="RGBLOOP", width=15, height=4, command=rgbLoop, fg="white", bg="black")
btn_Strobe = Button(window, text="STROBE", width=15, height=4, command=strobe, fg="white", bg="black")
btn_Sparkle = Button(window, text="SPARKLE", width=15, height=4, command=sparkle, fg="white", bg="black")
btn_RainbowCycle = Button(window, text="RAINBOWCYCLE", width=15, height=4, command=rainbowCycle, fg="white", bg="black")
btn_TwinkleRandom = Button(window, text="TWINKLERANDOM", width=15, height=4, command=twinkleRandom, fg="white", bg="black")
btn_TheaterChaseRainbow = Button(window, text="THEATERCHASE\nRAINBOW", width=15, height=4, command=theaterChaseRainbow, fg="white", bg="black")
btn_MeteorRain = Button(window, text="METEOR\nRAIN", width=15, height=4, command=meteorRain, fg="white", bg="black")
btn_NeonPurple = Button(window, text="NEON\nPURPLE", width=15, height=4, command=neonPurple, fg="white", bg="black")
btn_SetRGB = Button(window, text="Set RGB", width=15, height=4, command=setRgb, fg="white", bg="black")


lb_RED = Label(window, bg="black", fg="red", text="RED: ", width=15, height=4)
lb_GREEN = Label(window, bg="black", fg="green", text="GREEN: ", width=15, height=4)
lb_BLUE = Label(window, bg="black", fg="blue", text="BLUE: ", width=15, height=4)

entry_RED = Entry(window, width=15, fg="red")
entry_GREEN = Entry(window, width=15, fg="green")
entry_BLUE = Entry(window, width=15, fg="blue")

# Insert widgets in the window
btn_OFF.grid(row=0, column=0)
btn_RED.grid(row=1, column=0)

btn_GREEN.grid(row=0, column=1)
btn_BLUE.grid(row=1, column=1)

btn_WHITE.grid(row=0, column=2)
btn_RGBLoop.grid(row=1, column=2)

btn_Strobe.grid(row=0, column=3)
btn_Sparkle.grid(row=1, column=3)

btn_RainbowCycle.grid(row=0, column=4)
btn_TwinkleRandom.grid(row=1, column=4)

btn_TheaterChaseRainbow.grid(row=2, column=0)
btn_MeteorRain.grid(row=2, column=1)

btn_NeonPurple.grid(row=2, column=2)

lb_RED.grid(row=3, column=0)
entry_RED.grid(row=3, column=1)
btn_SetRGB.grid(row=3, column=2)

lb_GREEN.grid(row=4, column=0)
entry_GREEN.grid(row=4, column=1)

lb_BLUE.grid(row=5, column=0)
entry_BLUE.grid(row=5, column=1)

# Gets a feedback from arduino serial and turns off the leds
if ser.readline() == b'Ready to receive!\r\n':
    off()

window.mainloop()
