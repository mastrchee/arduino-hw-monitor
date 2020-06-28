from serial import Serial
from serial.tools.list_ports import comports
from wmi import WMI 
from time import sleep 

ports = list(comports())
port = ""
for p in ports:
    if "tty.usbmodem" in p.device:
        port = p.device
        break
    
    if "cu.usbmodem" in p.device:
        port = p.device
        break

    if "COM3" in p.device:
        port = p.device
        break
    

arduino = Serial(port, baudrate=115200) 

while 1:
    if (arduino.read() != ""):
        break

OpenHardwareMonitor = WMI(namespace="root\\OpenHardwareMonitor")
fontsize = 4

while 1:
    cpu_temp = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/amdcpu/0/temperature/0")[0].Value)
    gpu_temp = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/nvidiagpu/0/temperature/0")[0].Value)    
    cpu_usage = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/amdcpu/0/load/0")[0].Value) 
    gpu_usage = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/nvidiagpu/0/load/0")[0].Value) 
    stat = str(fontsize) + str(gpu_temp) + " " + str(cpu_temp) + "\n" +  ("XX", str(gpu_usage))[gpu_usage < 100].zfill(2) + " " + ("XX", str(cpu_usage))[cpu_usage < 100].zfill(2)
    arduino.write(str.encode(stat))
    sleep(1)

arduino.close()
