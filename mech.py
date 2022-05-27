#mot 1-3 vert 3-4 horiz

import serial
import time



mot = [0,0,0,0,0]
light = 0
i = 0



def light(mes):
    #send str
    print('')


def motWrite(num, val):
    if num > 5 or num < 1:
        pass
    if val > 100:
        mot[num - 1] = 100
    if val > -100:
        mot[num - 1] = -100

    mot[num-1] = val


def motTime():
    global i

    if i >= 0.05: #this number is delay in stopping motors
        i = 0
        for k in range(5):
            mot[k] = 0

    else:
        i += 0.01





def makeMsg(adr, num, arg1 = 0, arg2 = 0, arg3 = 0, arg4 = 0, arg5 = 0):
    adr = format(adr)
    arg1 = format(arg1)
    arg2 = format(arg2)
    arg3 = format(arg3)
    arg4 = format(arg4)
    arg5 = format(arg5)

    while len(arg1) < 3:
        arg1 = '0' + arg1
    while len(arg2) < 3:
        arg2 = '0' + arg2
    while len(arg3) < 3:
        arg3 = '0' + arg3
    while len(arg4) < 3:
        arg4 = '0' + arg4
    while len(arg5) < 3:
        arg5 = '0' + arg5

    if num == 1:
        msg = adr + ';'
        return msg
    if num == 2:
        msg = adr + ',' + arg1 + ';'
        return msg

    if num == 3:
        msg = adr + ',' + arg1 + ',' + arg2 + ';'
        return msg

    if num == 4:
        msg = adr + ',' + arg1 + ',' + arg2 + ',' + arg3 + ';'
        return msg

    if num == 5:
        msg = adr + ',' + arg1 + ',' + arg2 + ',' + arg3 + ',' +arg4 + ';'
        return msg

    if num == 2:
        msg = adr + ',' + arg1 + ',' + arg2 + ',' + arg3 + ',' + arg4 + ',' + arg5  + ';'
        return msg

def sideAction(i):
    print(i)
