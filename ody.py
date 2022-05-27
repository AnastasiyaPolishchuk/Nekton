from tkinter import *
import time
import mech
import serial

tk = Tk()
tk.title("Odyssey pilot hub")
tk.resizable(0, 0)
tk.wm_attributes('-topmost', 1)
canvas = Canvas(tk, width=400, height=200, highlightthickness=0)
canvas.pack()
tk.update()


stop = 1

class Data:
    def get_data(self):
        self.canvas.itemconfig(self.id1, text=self.temp)
        self.canvas.itemconfig(self.id3, text=self.depth)
        self.canvas.itemconfig(self.id5, text=self.angle1)
        self.canvas.itemconfig(self.id7, text=self.angle2)
        self.canvas.itemconfig(self.id9, text=self.light_stat)
        self.canvas.itemconfig(self.id11, text=mech.mot[0])
        self.canvas.itemconfig(self.id12, text=mech.mot[2])
        self.canvas.itemconfig(self.id13, text=mech.mot[1])
        self.canvas.itemconfig(self.id14, text=mech.mot[3])
        self.canvas.itemconfig(self.id15, text=mech.mot[4])



    def light_state(self, event):
        if self.light_stat == 1:
            self.light_stat = 0
            ser.write(str("10,0;").encode('utf-8'))

        else:
            self.light_stat = 1
            ser.write(str("10,1;").encode('utf-8'))

        mech.light(mech.makeMsg(10, 2, self.light_stat))

    def sideAct1(self, event):
        mech.sideAction(1)
    def sideAct2(self, event):
        mech.sideAction(2)
    def sideAct3(self, event):
        mech.sideAction(3)
    def sideAct4(self, event):
        mech.sideAction(4)
    def sideAct5(self, event):
        mech.sideAction(5)

    def __init__(self, canvas, color):
        self.canvas = canvas
        self.temp = 0
        self.depth = 3.65
        self.angle1 = 90
        self.angle2 = 44
        self.light_stat = 0
        self.id0 = canvas.create_text(40, 10, text="temp: ", font=('Courier', 15), fill=color)
        self.id1 = canvas.create_text(105, 10, text=self.temp, font=('Courier', 15), fill=color)
        self.id2 = canvas.create_text(45, 30, text="depth: ", font=('Courier', 15), fill=color)
        self.id3 = canvas.create_text(120, 30, text=self.depth, font=('Courier', 15), fill=color)
        self.id4 = canvas.create_text(50, 50, text="angle1: ", font=('Courier', 15), fill=color)
        self.id5 = canvas.create_text(110, 50, text=self.angle1, font=('Courier', 15), fill=color)
        self.id6 = canvas.create_text(50, 70, text="angle2: ", font=('Courier', 15), fill=color)
        self.id7 = canvas.create_text(110, 70, text=self.angle2, font=('Courier', 15), fill=color)
        self.id8 = canvas.create_text(45, 90, text="light: ", font=('Courier', 15), fill=color)
        self.id9 = canvas.create_text(110, 90, text=self.light_stat, font=('Courier', 15), fill=color)
        self.id10 = canvas.create_text(65, 110, text="mot speed:", font=('Courier', 15), fill=color)
        self.id11 = canvas.create_text(150, 110, text=mech.mot[0], font=('Courier', 15), fill=color)
        self.id12 = canvas.create_text(170, 150, text=mech.mot[1], font=('Courier', 15), fill=color)
        self.id13 = canvas.create_text(190, 110, text=mech.mot[2], font=('Courier', 15), fill=color)
        self.id14 = canvas.create_text(130, 150, text=mech.mot[3], font=('Courier', 15), fill=color)
        self.id15 = canvas.create_text(210, 150, text=mech.mot[4], font=('Courier', 15), fill=color)


        self.canvas.bind_all('<KeyPress-l>', self.light_state)

        #add more side actions (like drop smth)
        self.canvas.bind_all('<KeyPress-1>', self.sideAct1)
        self.canvas.bind_all('<KeyPress-2>', self.sideAct2)
        self.canvas.bind_all('<KeyPress-3>', self.sideAct3)
        self.canvas.bind_all('<KeyPress-4>', self.sideAct4)
        self.canvas.bind_all('<KeyPress-5>', self.sideAct5)



class Move:
    def move_forward(self, event):
        mech.motWrite(4, 100)
        mech.motWrite(5, 100)
        print('forw')
        ser.write(str("11,0,0,0,100,100;").encode('utf-8'))

    def move_backward(self, event):
        mech.motWrite(4, -100)
        mech.motWrite(5, -100)
        print('back')
        ser.write(str("11,0,0,0,-100,-100;").encode('utf-8'))

    def turn_right(self, event):
        mech.motWrite(4, -100)
        mech.motWrite(5, 100)
        print('right')
        ser.write(str("11,0,0,0,-100,100;").encode('utf-8'))
    def turn_left(self, event):
        mech.motWrite(4, 100)
        mech.motWrite(5, -100) 
        print('left')
        ser.write(str("11,0,0,0,100,-100;").encode('utf-8'))
    def move_up(self, event):
        mech.motWrite(1, 100)
        mech.motWrite(2, 100)
        mech.motWrite(3, 100)
        ser.write(str("11,100,100,100,0,0;").encode('utf-8'))
        print('up')
    def move_down(self, event):
        mech.motWrite(1, -100)
        mech.motWrite(2, -100)
        mech.motWrite(3, -100)
        print('down')
        ser.write(str("11,-100,-100,-100,0,0;").encode('utf-8'))
    def rotate_right(self, event): #right side up
        mech.motWrite(1, -50)
        mech.motWrite(2, 50)
        print('rot_right')
        ser.write(str("11,-50,50,0,0,0;").encode('utf-8'))
    def rotate_left(self, event):
        mech.motWrite(1, 50)
        mech.motWrite(2, -50)
        print('rot_left')
        ser.write(str("11,50,-50,0,0,0;").encode('utf-8'))
    def cam_up(self, event):
        mech.motWrite(1, 50)
        mech.motWrite(2, 50)
        mech.motWrite(3, -100)
        ser.write(str("11,50,50,-100,0,0;").encode('utf-8'))
        print('nos up')
    def cam_down(self, event):
        mech.motWrite(1, -50)
        mech.motWrite(2, -50)
        mech.motWrite(3, 100)
        print('nos down')
        ser.write(str("11,-50,-50,100,0,0;").encode('utf-8'))




    def stop(self, event):
        global stop
        print('stop')
        stop = 0



    def draw(self):
        print('ok')
    def __init__(self, canvas, color):
        self.canvas =canvas
        self.id = canvas.create_rectangle(0, 0, 0, 0, fill='green')

        self.canvas.bind_all('<KeyPress-0>', self.stop)

        self.canvas.bind_all('<KeyPress-w>', self.move_forward)
        self.canvas.bind_all('<KeyPress-s>', self.move_backward)

        self.canvas.bind_all('<KeyPress-Up>', self.cam_up)
        self.canvas.bind_all('<KeyPress-Down>', self.cam_down)

        self.canvas.bind_all('<KeyPress-d>', self.turn_right)
        self.canvas.bind_all('<KeyPress-a>', self.turn_left)

        self.canvas.bind_all('<KeyPress-space>', self.move_up)
        self.canvas.bind_all('<KeyPress-c>', self.move_down)

        self.canvas.bind_all('<KeyPress-Right>', self.rotate_right)
        self.canvas.bind_all('<KeyPress-Left>', self.rotate_left)

data = Data(canvas, 'black')
move = Move(canvas, 'green')

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()

while stop:
    tk.update_idletasks()
    tk.update()

    data.get_data()

    mech.motTime()

    time.sleep(0.1)
    
    ser.write(str("11,0,0,0,0,0;").encode('utf-8'))
