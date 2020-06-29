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

    if "COM4" in p.device:
        port = p.device
        break
    

arduino = Serial(port, baudrate=115200) 

while 1:
    if (arduino.read() != ""):
        break

OpenHardwareMonitor = WMI(namespace="root\\OpenHardwareMonitor")

while 1:
    cpu_temp = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/amdcpu/0/temperature/0")[0].Value)
    gpu_temp = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/nvidiagpu/0/temperature/0")[0].Value)    
    cpu_usage = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/amdcpu/0/load/0")[0].Value) 
    gpu_usage = int(OpenHardwareMonitor.Sensor(["Value"], Identifier="/nvidiagpu/0/load/0")[0].Value) 
    stat = ("99", str(gpu_usage))[gpu_usage < 100].zfill(2) + str(gpu_temp).zfill(2) + ("99", str(cpu_usage))[cpu_usage < 100].zfill(2) + str(cpu_temp).zfill(2)
    arduino.write(str.encode(stat))
    sleep(1)

arduino.close()
