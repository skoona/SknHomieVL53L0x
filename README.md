# SknHomieVL53L1x

<a href="https://homieiot.github.io/">
  <img src="https://homieiot.github.io/img/works-with-homie.png" alt="works with MQTT Homie">
</a>

HomieNode V3 featuring:
- VL53L1x Time of Flight Sensor capturing distance reading every 280 milliseconds once triggered.
- Runs in continuous capture mode once triggered for the seconds indicated as  duration, set in the config.

### Homie Config

```
{
  "name": "Time of Flight Ranger",
  "device_id": "TOFRanger",
  "device_stats_interval": 900,  
  "wifi": {
    "ssid": "<wifi-host>",
    "password": "<wifi-password>"
  },
  "mqtt": {
    "host": "<mqtt-hostname-or-ip>",
    "port": 1883,
	"base_topic": "sknSensors/",
    "auth": true,
    "username": "<mqtt-username>",
    "password": "<mqtt-password>"
  },
  "ota": {
    "enabled": true
  },
  "settings": {
      "duration": 20
    }
}
```


### Home MQTT Log
```
09:19:12.400 > 💡 Firmware Time of Flight Ranger (1.0.0)
09:19:12.400 > 🔌 Booting into normal mode 🔌
09:19:12.684 > {} Stored configuration
09:19:12.687 >   • Hardware device ID: 240ac4594254
09:19:12.690 >   • Device ID: TOFRanger
09:19:12.693 >   • Name: Time of Flight Ranger
09:19:12.696 >   • Device Stats Interval: 300 sec
09:19:12.699 >   • Wi-Fi: 
09:19:12.700 >     ◦ SSID: SFNSS1-24G
09:19:12.702 >     ◦ Password not shown
09:19:12.705 >   • MQTT: 
09:19:12.706 >     ◦ Host: openhab.skoona.net
09:19:12.709 >     ◦ Port: 1883
09:19:12.711 >     ◦ Base topic: sknSensors/
09:19:12.714 >     ◦ Auth? yes
09:19:12.715 >     ◦ Username: openhabian
09:19:12.718 >     ◦ Password not shown
09:19:12.720 >   • OTA: 
09:19:12.721 >     ◦ Enabled? yes
09:19:12.723 >   • Custom settings: 
09:19:12.726 >     ◦ duration: 15 (set)
09:19:12.728 > • Ranging Module:
09:19:12.735 > 〽 Medium distance mode accepted.
09:19:12.738 > 〽 200us timing budget accepted.
09:19:12.741 > ↕ Attempting to connect to Wi-Fi...
09:19:15.809 > ✔ Wi-Fi connected, IP: 10.100.1.244
09:19:15.813 > Triggering WIFI_CONNECTED event...
09:19:15.816 > ↕ Attempting to connect to MQTT...
09:19:15.845 > Sending initial information...
09:19:15.903 > ✔ MQTT ready
09:19:15.904 > Triggering MQTT_READY event...
09:19:15.907 > 〽 Node: TOF Ranger Ready to operate.
09:19:15.911 > Calling setup function...
09:19:15.913 > 〽 Sending statistics...
09:19:15.915 >   • Interval: 305s (300s including 5s grace time)
09:19:15.920 >   • Wi-Fi signal quality: 100%
09:19:15.923 >   • Uptime: 4s
09:19:18.852 > 📢 Calling broadcast handler...
09:19:18.855 > Received broadcast level alert: OH3 Offline
09:19:18.859 > 📢 Calling broadcast handler...
09:19:18.862 > Received broadcast level LWT: HomieMonitor Offline!
09:19:32.734 > 〽 Start continuous ranging @ 280 ms accepted.
09:19:32.982 > 〽 range: 350 mm         status: range valid     signal: 41.19 MCPS      ambient: 0.11 MCPS
09:19:33.256 > 〽 range: 359 mm         status: range valid     signal: 20.73 MCPS      ambient: 0.06 MCPS
09:19:33.542 > 〽 range: 357 mm         status: range valid     signal: 19.83 MCPS      ambient: 0.05 MCPS
09:19:33.804 > 〽 range: 358 mm         status: range valid     signal: 19.87 MCPS      ambient: 0.05 MCPS
09:19:34.091 > 〽 range: 357 mm         status: range valid     signal: 19.80 MCPS      ambient: 0.05 MCPS
09:19:34.360 > 〽 range: 357 mm         status: range valid     signal: 19.90 MCPS      ambient: 0.05 MCPS
09:19:34.656 > 〽 range: 359 mm         status: range valid     signal: 19.91 MCPS      ambient: 0.05 MCPS
09:19:34.908 > 〽 range: 359 mm         status: range valid     signal: 19.95 MCPS      ambient: 0.05 MCPS
09:19:35.194 > 〽 range: 358 mm         status: range valid     signal: 19.97 MCPS      ambient: 0.05 MCPS
09:19:35.476 > 〽 range: 356 mm         status: range valid     signal: 19.57 MCPS      ambient: 0.05 MCPS
09:19:35.756 > 〽 range: 359 mm         status: range valid     signal: 19.49 MCPS      ambient: 0.05 MCPS
09:19:36.059 > 〽 range: 358 mm         status: range valid     signal: 20.00 MCPS      ambient: 0.05 MCPS
09:19:36.320 > 〽 range: 357 mm         status: range valid     signal: 19.52 MCPS      ambient: 0.05 MCPS
09:19:36.603 > 〽 range: 358 mm         status: range valid     signal: 19.98 MCPS      ambient: 0.05 MCPS
09:19:36.898 > 〽 range: 357 mm         status: range valid     signal: 19.59 MCPS      ambient: 0.05 MCPS
09:19:37.160 > 〽 range: 358 mm         status: range valid     signal: 19.96 MCPS      ambient: 0.05 MCPS
09:19:37.450 > 〽 range: 358 mm         status: range valid     signal: 19.87 MCPS      ambient: 0.05 MCPS
09:19:37.724 > 〽 range: 357 mm         status: range valid     signal: 19.68 MCPS      ambient: 0.05 MCPS
09:19:37.995 > 〽 range: 358 mm         status: range valid     signal: 19.95 MCPS      ambient: 0.06 MCPS
09:19:38.281 > 〽 range: 358 mm         status: range valid     signal: 19.64 MCPS      ambient: 0.05 MCPS
09:19:38.563 > 〽 range: 358 mm         status: range valid     signal: 19.65 MCPS      ambient: 0.05 MCPS
09:19:38.851 > 〽 range: 359 mm         status: range valid     signal: 19.92 MCPS      ambient: 0.06 MCPS
09:19:39.128 > 〽 range: 357 mm         status: range valid     signal: 20.02 MCPS      ambient: 0.05 MCPS
09:19:39.400 > 〽 range: 358 mm         status: range valid     signal: 19.92 MCPS      ambient: 0.06 MCPS
09:19:39.675 > 〽 range: 358 mm         status: range valid     signal: 20.00 MCPS      ambient: 0.05 MCPS
09:19:39.983 > 〽 range: 357 mm         status: range valid     signal: 19.67 MCPS      ambient: 0.05 MCPS
09:19:40.252 > 〽 range: 358 mm         status: range valid     signal: 19.95 MCPS      ambient: 0.05 MCPS
09:19:40.533 > 〽 range: 357 mm         status: range valid     signal: 19.63 MCPS      ambient: 0.05 MCPS
09:19:40.799 > 〽 range: 359 mm         status: range valid     signal: 19.60 MCPS      ambient: 0.05 MCPS
09:19:41.075 > 〽 range: 358 mm         status: range valid     signal: 20.00 MCPS      ambient: 0.05 MCPS
09:19:41.372 > 〽 range: 275 mm         status: wrap target fail        signal: 43.54 MCPS      ambient: 0.05 MCPS
09:19:41.635 > 〽 range: 0 mm   status: range valid     signal: 299.45 MCPS     ambient: 0.05 MCPS
09:19:41.928 > 〽 range: 0 mm   status: range valid     signal: 262.31 MCPS     ambient: 0.02 MCPS

```
