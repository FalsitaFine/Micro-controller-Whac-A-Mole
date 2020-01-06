# Micro-controller-Whac-A-Mole
A Whac-A-Mole Game on Micro controller and its corresponding API

It is an sample project shows how a PIC24 controller can drive the iLED device.

Intro:

It contains two libraries: one is for 8 x 8 LED matrix, and the other is for a buzzer.
The matrix library has three layers, means to send a single bit to the matrix, control each pixel of the matrix, and control multiple pixels to print out something together.
The buzzer library has only one function: make a voice with given frequency.
Hardware description:
The keypad and LCD screen is all the same with the devices used in the previous labs.(LAB 3 and 5).
The 8 x 8 Matrix is the most important device in this project. It is formed by 64 iLEDs, each iLED(pixel) is controled by a 24-bit signal.(8 bit red, 8 bit green and 8 bit blue). Unlike single LED, we need to send 64 signals to the matrix in order to control all these 8 x 8 pixels, the first pixel will take its signal, and then send the rest 63 signals to the rest pixels, and etc.
The buzzer is a simple device, it has two pins, one connect to the ground and another connect to an output pin of the PIC, when there are voltage difference(should be within 3 ~ 28V) between these two pins, it will make some voice. By giving signals in different frequence, we can make different voices.

 
Full documentation:
See Document.txt
