from prometheus_client import start_http_server, Summary
import random
import time
import serial
import logging
import datetime
from prometheus_client import Gauge, start_http_server
import sys, os, schedule
import requests

log = logging.getLogger('co2_sensor')

g_co2PPM = Gauge('co2_ppm',
           'co2 ppm measured by the co2_Sensor TG100')
g_co2MV = Gauge('co2_mV', 
        'co2 mV measured by the co2_Sensor TG100 ')
g_temp = Gauge('temperature',
        'temperature measured by the BME280')
g_press = Gauge('pressure',
        'pressure measured by the BME280')
g_humidity = Gauge('humidity',
        'humidity measured by the BME280')
g_pm1 = Gauge('pm1',
         'pm1.0 measured by the PMS7003m')
g_pm2 = Gauge('pm2',
         'pm2 measured by the PMS7003m')
g_pm10 = Gauge('pm10',
         'pm10 measured by the PMS7003m')
g_nh3 = Gauge('nh3',
        'nh3 measured by the Multichannel Gas Sensor')
g_co = Gauge('co',
        'co measured by the Multichannel Gas Sensor')
g_no2 = Gauge('no2',
        'no2 measured by the Multichannel Gas Sensor')
g_h2 = Gauge('h2',
        'h2 measured by the Multichannel Gas Sensor')
g_c2h5oh = Gauge('c2h5oh',
        'c2h5oh measured by the Multichannel Gas Sensor')
g_c3h8 = Gauge('c3h8',
        'c3h8 measured by the BMEMultichannel Gas Sensor280')
g_c4h10 = Gauge('c4h10',
        'c4h10 measured by the Multichannel Gas Sensor')
g_ch4 = Gauge('ch4',
        'ch4 measured by the Multichannel Gas Sensor')

def read_sensor(co2_mv, co2, temp, press, humidity, pm1, pm2, pm10, nh3, co, no2, h2, c2h5oh, c3h8, c4h10,ch4):
        g_co2PPM.set(co2)
        g_co2MV.set(co2_mv)
        # g_co2MV.labels('fahrenheit').set(co2_mv)
        g_temp.set(temp)
        g_press.set(press)
        g_humidity.set(humidity)
        g_pm1.set(pm1)
        g_pm2.set(pm2)
        g_pm10.set(pm10)
        g_nh3.set(nh3)
        g_co.set(co)
        g_no2.set(no2)
        g_h2.set(h2)
        g_c2h5oh.set(c2h5oh)
        g_c3h8.set(c3h8)
        g_c4h10.set(c4h10)
        g_ch4.set(ch4)
        #log.info("co2:{0:0.1f}*C".format(mv))

# Create a metric to track time spent and requests made.
REQUEST_TIME = Summary('request_processing_seconds', 'Time spent processing request')

# # Decorate function with metric.
# @REQUEST_TIME.time()
# def process_request(t):
#     """A dummy function that takes some time."""
#     time.sleep(t)

###for monitor on / off
monitor_0 = "vcgencmd display_power 0"
monitor_1 = "vcgencmd display_power 1"
def power_off():
    os.system(monitor_0)
def power_on():
    os.system(monitor_1)
#at.(time that want to on/off)
schedule.every().day.at("08:40").do(power_on)
schedule.every().day.at("18:40").do(power_off)

if __name__ == '__main__':
    # Start up the server to expose the metrics.
    start_http_server(8000)
    # Generate some requests.

    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1)
    ser.flush()
    now = datetime.datetime.now()
    print(now)
    while True:
        try:
            schedule.run_pending()
            if ser.in_waiting>0:
                line = ser.readline().decode('utf-8').rstrip()
                # print(line)
                co2_mv, co2, temp, press, humidity, pm1, pm2, pm10, nh3, co, no2, h2, c2h5oh, c3h8, c4h10, ch4 = line.split()
                

                read_sensor(co2_mv, co2, temp, press, humidity, pm1, pm2, pm10, nh3, co, no2, h2, c2h5oh, c3h8, c4h10, ch4)
                send_url = "http://ec2-52-78-39-147.ap-northeast-2.compute.amazonaws.com/api/v1/data/"
                send_data = {
                    
                    "temperature" : temp,
                    "pressure" : press,
                    "humidity" : humidity,
                    "co2_mv" : co2_mv,
                    "co2" : co2,
                    "pm1_0" : pm1,
                    "pm2_5" : pm2,
                    "pm10" : pm10,
                    "nh3" : nh3,
                    "co" : co,
                    "no2" : no2,
                    "h2" : h2,
                    "c2h5oh" : c2h5oh,
                    "c3h8" : c3h8,
                    "c4h10" : c4h10,
                    "ch4" : ch4
                    }
                res = requests.post(send_url, data=send_data)
                print(res)
                #print(send_data)

                #print(co2_mv, co2, temp, press, humidity, pm1, pm2, pm10, nh3, co, no2, h2, c2h5oh, c3h8, c4h10, ch4)
            #process_request(random.random())
            time.sleep(30)
        except:
            time.sleep(5)
            continue # 나중에 수정
            
