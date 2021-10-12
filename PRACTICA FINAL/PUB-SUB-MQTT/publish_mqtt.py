#mosquitto_pub -h localhost -p 1883 -t "casa/cocina/nevera" -m "{\"dato\":6}"
import paho.mqtt.client as mqtt
from random import randrange
import datetime
import serial, time

arduino = serial.Serial('COM5', 115200)

while True:

    rawString = arduino.readline()
    rawString_s = str(rawString)
    humedad = 0
    temper = 0
    bombillo = False
    ventilador = False
    var = ""
    #print("Serial Arduino: ",rawString)
    variables = rawString_s.split(" ")
    variables[0] == "b'"
    print(variables)
    if variables[0] == "b'":
        humedad = variables[1]
        temper = variables[2]
        if variables[3] == "1":
            bombillo = "ON"
        elif variables[3] == "0":
            bombillo = "OFF"
        if variables[4] == "1":
            ventilador = "ON"
        elif variables[4] == "0":
            ventilador = "OFF"
        

    #arduino.close()


        mqttBroker = "localhost"
        client = mqtt.Client("P1")
        client.connect(mqttBroker)


        hora= str(datetime.datetime.now())

        horaf = hora.split(".")
        
        if (variables[1] != "nan") and (variables[2] != "nan"):
            var = '{"hora":"'+str(horaf[0])+'","humedad":"'+str(humedad)+'","temperatura":"'+str(temper)+'","bombillo":"'+str(bombillo)+'","ventilador":"'+str(ventilador)+'"}'
            client.publish("casa/habitacion", var)
            print("Just published " + var )
        