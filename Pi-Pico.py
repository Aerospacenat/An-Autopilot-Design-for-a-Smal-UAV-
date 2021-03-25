from machine import Pin
import utime, _thread, machine
import os
from rp2 import PIO, StateMachine, asm_pio
#print sys info
print(os.uname())
led_onboard = machine.Pin(25, machine.Pin.OUT)
led_onboard.value(0)     # onboard LED OFF for 0.5 sec
utime.sleep(0.5)
led_onboard.value(1)
uart = machine.UART(0, baudrate=9600)
ser = machine.UART(1, baudrate=9600)
print(uart)
print(ser)

baton = _thread.allocate_lock()

rcvChar = b""

trigger = Pin(3, Pin.OUT) #left 
echo = Pin(2, Pin.IN)

trigger2 = Pin(7, Pin.OUT) #right 
echo2 = Pin(6, Pin.IN)

trigger4 = Pin(9, Pin.OUT) #down
echo4 = Pin(8, Pin.IN)


def decode(coord):
    #Converts DDDMM.MMMMM > DD deg MM.MMMMM min
    x = coord.split(".")
    head = x[0]
    tail = x[1]
    deg = head[0:-2]
    min = head[-2:]
    return deg + " deg " + min + "." + tail + " min"

def ultrasonic(ntrigger, necho ):
    
   ntrigger.low()
   utime.sleep_us(2)
   ntrigger.high()
   utime.sleep_us(5)
   ntrigger.low()
   
   while necho.value() == 0:
       signaloff = utime.ticks_us()
   while necho.value() == 1:
       signalon = utime.ticks_us()
   timepassed = signalon - signaloff
   distance = (timepassed * 0.0343) / 2
   
   utime.sleep(0.1)  
   ntrigger.low()
   utime.sleep_us(2)
   ntrigger.high()
   utime.sleep_us(5)
   ntrigger.low()
   
   while necho.value() == 0:
       signaloff2 = utime.ticks_us()
   while necho.value() == 1:
       signalon2 = utime.ticks_us()
   timepassed2 = signalon2 - signaloff2
   distance2 = (timepassed2 * 0.0343) / 2
   newdist =  (distance + distance2) / 2
   if newdist > 120:
       newdist = 120
   elif newdist <= 100:
       if ntrigger == trigger:
           uart.write("LO")
           uart.write("\n")
           print("The distance left from object is ",newdist,"cm message sent")
       if ntrigger == trigger2:
           uart.write("RO")
           uart.write("\n")
           print("The distance right from object is ",newdist,"cm message sent")
       
   if newdist >= 20:
       if ntrigger == trigger4:
           uart.write("D20")
           uart.write("\n")
           print("Sent TO Height")
   if newdist <= 13:
       if ntrigger == trigger4:
           uart.write("D12")
           uart.write("\n")
           print("Sent Landed")
           
def gps():
       #baton.acquire()
       rcvChar = ser.readline()
       gps_data = rcvChar.decode("ASCII")
       data = gps_data
       if (data[0:6] == "$GPRMC"):
           sdata = data.split(",")
           if (sdata[2] == 'V'):
               print("no satellite data available")   
           print ("---Parsing GPRMC---")
           time = sdata[1][0:2] + ":" + sdata[1][2:4] + ":" + sdata[1][4:6]
           lat = decode(sdata[3]) #latitude
           dirLat = sdata[4]      #latitude direction N/S
           lon = decode(sdata[5]) #longitute
           dirLon = sdata[6]      #longitude direction E/W
           speed = sdata[7]       #Speed in knots
           trCourse = sdata[8]    #True course
           date = sdata[9][0:2] + "/" + sdata[9][2:4] + "/" + sdata[9][4:6]#date
           print ("time : %s, latitude : %s(%s), longitude : %s(%s), speed : %s, True Course : %s, Date : %s" %  (time,lat,dirLat,lon,dirLon,speed,trCourse,date))
       #baton.acquire()
        
#_thread.start_new_thread(gps(), ())  

while True:
    ultrasonic(trigger, echo)
    utime.sleep(1)
    ultrasonic(trigger2, echo2)
    utime.sleep(1)
    ultrasonic(trigger4, echo4)
    utime.sleep(1)
    gps()
    utime.sleep(2)
