import json
from flask import Flask
from flask import request
from enum import Enum

class State(Enum):
    AUTO = "AUTO"
    MANUAL = "MANUAL"
    ALARM = "ALARM"
    
state = State.AUTO
app = Flask(__name__)
  

def getStateDict():
    return {"state":state.value}

@app.route("/")
def hello_world():
    return "<p>Hello, Worldioooooooo!</p>"


@app.route("/sensorState")
def sendState():
    tmp = request.args.get('tmp')
    lux = request.args.get('lum')
    useValue(lux, tmp)
    return state.value


@app.route("/resetAlarm")
def reset():
    global state
    state = State.AUTO
    return "reset"


def useValue(lux, temp):
    global state
    if(temp == "5"):
        state = State.ALARM
        sendAlarmMessage()


def sendAlarmMessage():
    print("ALLARMEEEEEE ROSSOOOO")
