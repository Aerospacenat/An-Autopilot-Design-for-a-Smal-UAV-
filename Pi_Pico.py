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

trigger2 = Pin(6, Pin.OUT) #right 
echo2 = Pin(7, Pin.IN)

trigger4 = Pin(9, Pin.OUT) #backward
echo4 = Pin(8, Pin.IN)


def decode(coord):
    #Converts DDDMM.MMMMM > DD deg MM.MMMMM min
    x = coord.split(".")
    head = x[0]
    tail = x[1]
    deg = head[0:-2]
    min = head[-2:]
    return deg + " deg " + min + "." + tail + " min"

def ultraleft():
   trigger.low()
   utime.sleep_us(2)
   trigger.high()
   utime.sleep_us(5)
   trigger.low()
   while echo.value() == 0:
       signaloff = utime.ticks_us()
   while echo.value() == 1:
       signalon = utime.ticks_us()
   timepassed = signalon - signaloff
   Ldistance = (timepassed * 0.0343) / 2  
   utime.sleep(0.1)  
   trigger.low()
   utime.sleep_us(2)
   trigger.high()
   utime.sleep_us(5)
   trigger.low()
   while echo.value() == 0:
       signaloff = utime.ticks_us()
   while echo.value() == 1:
       signalon = utime.ticks_us()
   timepassed = signalon - signaloff
   Ldistance2 = (timepassed * 0.0343) / 2   
   newLdist =  (Ldistance + Ldistance2) / 2
   if newLdist > 120:
       newLdist = 120
   elif newLdist <= 100:
       print("Distance Left less than 100")
       return True
   print("The distance Left from object is ",newLdist,"cm")
   

def ultraright():
   trigger2.low()
   utime.sleep_us(2)
   trigger2.high()
   utime.sleep_us(5)
   trigger2.low()
   while echo2.value() == 0:
       signaloff2 = utime.ticks_us()
   while echo2.value() == 1:
       signalon2 = utime.ticks_us()
   timepassed2 = signalon2 - signaloff2
   Rdistance = (timepassed2 * 0.0343) / 2   
   utime.sleep(0.1)  
   trigger2.low()
   utime.sleep_us(2)
   trigger2.high()
   utime.sleep_us(5)
   trigger2.low()
   while echo2.value() == 0:
       signaloff2 = utime.ticks_us()
   while echo2.value() == 1:
       signalon2 = utime.ticks_us()
   timepassed2 = signalon2 - signaloff2
   Rdistance2 = (timepassed2 * 0.0343) / 2
   newRdist =  (Rdistance + Rdistance2) / 2
   if newRdist > 120:
       newRdist = 120
   elif newRdist <= 100:
       print("Distance Right less than 100")
       return True
   print("The distance Right from object is ",newRdist,"cm")
   
   
   
def ultradwn():
   trigger4.low()
   utime.sleep_us(2)
   trigger4.high()
   utime.sleep_us(5)
   trigger4.low()
   while echo4.value() == 0:
       signaloff4 = utime.ticks_us()
   while echo4.value() == 1:
       signalon4 = utime.ticks_us()
   timepassed4 = signalon4 - signaloff4
   Ddistance = (timepassed4 * 0.0343) / 2
   utime.sleep(0.1)   
   trigger4.low()
   utime.sleep_us(2)
   trigger4.high()
   utime.sleep_us(5)
   trigger4.low()
   while echo4.value() == 0:
       signaloff4 = utime.ticks_us()
   while echo4.value() == 1:
       signalon4 = utime.ticks_us()
   timepassed4 = signalon4 - signaloff4
   Ddistance2 = (timepassed4 * 0.0343) / 2
   newDdist =  (Ddistance + Ddistance2) / 2
   if newDdist > 120:
       newDdist = 120
   elif newDdist >20 :
       print("Distance Down is greater than 20")
       x = 1
       #uart.write("D20")
       #uart.write("\n")
       #print("Sent TO Height")
       return True
   elif newDdist <12 :
       print("Distance Down is less than 12")
       x = 2
       #uart.write("D12")
       #uart.write("\n")
       #print("Sent Landed")
       return True
   print("The distance Down from object is ",newDdist,"cm")
   

def gps():
    while True:
        baton.acquire()
        rcvChar = ser.readline()
        gps_data =rcvChar.decode("ASCII")
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
        baton.acquire()
_thread.start_new_thread(ultradwn, ())  

while True:
   x = 0
   baton.acquire()
   ultraleft()
   utime.sleep(0.1)
   ultraright()
   utime.sleep(0.1)
   ultradwn()
   utime.sleep(0.1)
   if ultraleft():
    uart.write("LO")
    uart.write("\n")
    print("Sent Left")
    utime.sleep(1)
   if ultraright():
    uart.write("RO")
    uart.write("\n")
    print("Sent Right")
    uart.sendbreak()
    utime.sleep(1)
   if ultradwn():
    if x == 1:
        uart.write("D20")
        uart.write("\n")
        print("Sent TO Height")
        utime.sleep(1)
    if x == 2:
        uart.write("D12")
        uart.write("\n")
        print("Sent Landed")
        utime.sleep(1)
    utime.sleep(1)
    baton.release()
    
       

