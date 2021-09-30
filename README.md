# NeoPixel control over serial using Python

I really wanted to brighten up more my room and to illuminate my monitor so I started this fun little project.

It let's you control NeoPixel Leds using a Python3 GUI that communicates with an arduino through one of the serial ports of your pc.
You can choose between static colors i.e. red, green, blue or white, or animations like the rgbLoop or the rainbowCycle.
I also provided 3 entries that can be used to set a custom RGB color, just search up a color code on Google and enter it in the GUI.

You can also add your own colors or animations by simpling adding some code to the .ino and .py/.pyw files following the built in colors/animations coding.

Both codes are completly commented so if you have any doubt or are just curios on how everything works, just check the code.

The communication protocol is based on sending commands over serial. A command is defined by 2 "markers", one starting character and an ending one. A simple command is [red]:
the arduino function reads the first character, and if it's the stating marker "CMD_START" then starts to read the real command until it reads the ending marker "CMD_END", in this case the "red" command, that sets the leds to a full red. All the commands are equal in struct, but the name, exept the [setRgb] command: this one actually has 3 valus coming in with him and those are the Red, Green and Blue codes used for the custom color.

For the arduino part you can use whatever board you like, I only had problems with the arduino pro micro that wouldn't let me use the FastLed library. The number of Leds used is, by default, set to 25 and the digital output pin is set to 2, so before uploading the file remembrer to change these values, if you need to. Remember also to attach a 100 Ohm resistor between the digital pin and the input of the first NeoPixel led.

For the python GUI I'm using Python 3.9.6 with pySerial and Tkinter. It's really important to install pySerial and not serial because it won't work, so use "pip install pySerial" to install it. Tkinter should be already installed so no problem with that. The GUI is fully customizable and it's pretty easy to do so, just follow the code you see for the other buttons. You can use both files to control the leds, but the .pyw one won't open the terminal like the .py would normally do, so it looks cleaner. There's also an icon you can use if you want to create a desktop shortcut and don't want to use the default icon.

I really hope this project can be usefull to you and if you have any question or suggestion just message me!
