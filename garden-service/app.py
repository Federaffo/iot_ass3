#%%
import json
from mimetypes import init
from this import d
from tkinter.tix import Tree
from turtle import delay
from flask import Flask
from flask import request, jsonify, Response
from enum import Enum
from numpy import tri, true_divide
import serial
from datetime import date, datetime,timedelta
import time, threading
from flask_cors import CORS
from threading import Thread



class State(Enum):
    AUTO = 0
    MANUAL = 1
    ALARM = 2
    
state = State.AUTO
app = Flask(__name__)
CORS(app)

ir_X = 10
ir_Y = 10

lastStart = datetime.now() - timedelta(days=1)

class sender():
    def __init__(self, rate, port) -> None:        
        self.ser = serial.Serial() 
        self.ser.baudrate = rate 
        self.ser.port = port
        self.ser.open()


    def send(self,msg):
        #self.ser.open()
        print("sending")
        a = str(msg) + "-"  
        a = a.lower()
        self.ser.write(str.encode(a))
        #self.ser.close()  

    def read(self):
        return self.ser.readline()
        

class myGarden():
    def __init__(self) -> None:
        self.dict = {'l1':True,'l2':True,'l3':1,'l4':4,'i':False,'is':1,'state':0,'lux':0,'tmp':0}
        self.canIrr = True

    def setIrr(self, ir):
        self.dict["i"] = ir

    def setAllOff(self):
        self.setLedOff()
        self.dict["i"] = False

    def setLedOff(self):
        self.dict["l1"] = False
        self.dict["l2"] = False
        self.dict["l3"] = 0
        self.dict["l4"] = 0

    def stopIrr(self):
        self.setIrr(False)
        self.canIrr = False
        threading.Timer(ir_Y, self.nowCanIrr).start()

    def nowCanIrr(self):
        self.canIrr = True

    def startIrr(self):
        self.setIrr(True)
        threading.Timer(ir_X, self.stopIrr).start()

    def sync(self,temp,lux):
        global state

        self.dict["lux"]=lux
        self.dict["tmp"]=temp

        if state == State.AUTO:
            if(temp == 5):
                self.setAllOff()
                state = State.ALARM
                self.dict["state"] = State.ALARM.value
                return

            if lux < 2 and self.dict["i"] == False and self.canIrr:
                self.startIrr()


            if lux < 5 :
                self.dict["l1"] = True
                self.dict["l2"] = True
                self.dict["l3"] = 5-lux
                self.dict["l4"] = 5-lux
            else:
                self.setLedOff()

    def getGarden(self):
        return self.dict

    def changeState(self,i):
        self.dict["state"]=i
        state=i
        self.setAllOff()
    
    def changeAll(self,myJson):
        self.dict = myJson


def readFromArduino():
    while True :
        data=s.read().decode("utf-8")
        print(data)
        if "exitAlarm" in data :
            garden.setAllOff()
            state = 0
            garden.dict["state"] = 0
        elif "restoreAuto" in data:
            garden.setAllOff()
            state = 0
            garden.dict["state"] = 0
        elif "manualControl" in data:
            garden.setAllOff()
            state = 1
            garden.dict["state"] = 1
        else:
            a = json.loads(data)
            garden.changeAll(a)


def getStateDict():
    return {"state":state.value}

@app.route("/")
def hello_world():

    return "OK"


@app.route("/sensorState")
def sendState():
    tmp =int(request.args.get('tmp'))
    lux = int(request.args.get('lum'))
    garden.sync(tmp,lux)
    s.send(garden.getGarden())
    #useValue(lux, tmp)
    #return json.dumps(garden.getGarden(), indent=4)
    return str(garden.getGarden()["state"])

@app.route("/resetAlarm")
def reset():
    global state
    state = State.AUTO
    return "reset"
    
@app.route("/send")
def send():
    s.send(garden.getGarden())
    #s.send("ciao")
    threading.Timer(5.0, send).start()

    return "OK"

@app.route("/dashboard",methods=["GET","POST"])
def sendWeb():

    return garden.getGarden()

    

if __name__ == "__main__":
    threading.Thread(target=lambda: app.run(host="0.0.0.0", port=80, debug=True, use_reloader=False)).start()
    garden = myGarden()
    s = sender(9600, "COM6")
    threading.Timer(3.0, send).start()
    t=Thread(target=readFromArduino,args=[])
    t.start()


# %%
