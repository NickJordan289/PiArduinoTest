from gpiozero import Button
import requests
import json
import serial
arduino = serial.Serial('/dev/ttyACM0', 9600)
but = Button(17)

def make_post():
    payload = {'value':v}
    print('posting ', payload)
    r = requests.post("https://hydrogenapp-240315.appspot.com/api/edit/0", data=json.dumps(payload))
    print(r.text)
    
but.when_pressed = make_post

v = 0
while True:
    if arduino.in_waiting > 0:
        try:
            new_v = int(arduino.readline())
            if(new_v != v):
                print(v)
                v=new_v
        except Exception as e:
            print(e)
            pass