#%%
import serial


class sender():
    ser = serial.Serial() 
    def __init__(self) -> None:        
        self.ser.baudrate = 9600 
        self.ser.port = 'COM3'

    def send(self,msg):
        self.ser.open()
        print("sending")      
        self.ser.write(str.encode(msg))
        self.ser.close() 

s=sender()
s.send("ciao-")

# %%
