# SknHomieVL53L0x

<a href="https://homieiot.github.io/">
  <img src="https://homieiot.github.io/img/works-with-homie.png" alt="works with MQTT Homie">
</a>

HomieNode V3 featuring:
- VL53L0x Time of Flight Sensor capturing distance reading every 280 milliseconds once triggered.
- Runs in continuous capture mode once triggered for the seconds indicated as  duration, set in the config.

### Homie Config: data/homie/config.json

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


### Homie Serial Runtime Log
```
10:33:21.494 > 💡 Firmware Time of Flight Ranger (1.0.0)
10:33:21.499 > 🔌 Booting into normal mode 🔌
10:33:22.216 > {} Stored configuration
10:33:22.219 >   • Hardware device ID: ac67b22b9164
10:33:22.223 >   • Device ID: TOFRanger
10:33:22.225 >   • Name: Time of Flight Ranger
10:33:22.228 >   • Device Stats Interval: 300 sec
10:33:22.232 >   • Wi-Fi: 
10:33:22.233 >     ◦ SSID: SFNSS1-24G
10:33:22.235 >     ◦ Password not shown
10:33:22.238 >   • MQTT: 
10:33:22.239 >     ◦ Host: openhab.skoona.net
10:33:22.242 >     ◦ Port: 1883
10:33:22.244 >     ◦ Base topic: sknSensors/
10:33:22.246 >     ◦ Auth? yes
10:33:22.248 >     ◦ Username: openhabian
10:33:22.251 >     ◦ Password not shown
10:33:22.253 >   • OTA: 
10:33:22.254 >     ◦ Enabled? yes
10:33:22.256 >   • Custom settings: 
10:33:22.258 >     ◦ duration: 15 (set)
10:33:22.261 > • VL53L0x Ranging Module:
10:33:22.331 > 〽 0.2mcps rate limit (medium) accepted.
10:33:22.339 > 〽 16 pclks pulse period accepted.
10:33:22.347 > 〽 12 pclks final pulse period accepted.
10:33:22.352 > 〽 200us timing budget accepted.
10:33:22.355 > ↕ Attempting to connect to Wi-Fi...
10:33:25.346 > ✔ Wi-Fi connected, IP: 10.100.1.202
10:33:25.350 > Triggering WIFI_CONNECTED event...
10:33:25.353 > ↕ Attempting to connect to MQTT...
10:33:25.397 > Sending initial information...
10:33:25.433 > ✔ MQTT ready
10:33:25.434 > Triggering MQTT_READY event...
10:33:25.437 > 〽 Node: TOF Ranger Ready to operate.
10:33:25.442 > Calling setup function...
10:33:25.443 > 〽 Sending statistics...
10:33:25.445 >   • Interval: 305s (300s including 5s grace time)
10:33:25.450 >   • Wi-Fi signal quality: 100%
10:33:25.453 >   • Uptime: 4s
10:33:25.455 > 📢 Calling broadcast handler...
10:33:25.458 > Received broadcast level alert: OH3 Offline
10:33:25.462 > 📢 Calling broadcast handler...
10:33:25.464 > Received broadcast level LWT: HomieMonitor Offline!
10:33:42.351 > 〽 Start continuous ranging @ 280 ms accepted.
10:33:42.553 > 〽 range: 263
10:33:42.831 > 〽 range: 264
10:33:43.112 > 〽 range: 262
10:33:43.391 > 〽 range: 264
10:33:43.670 > 〽 range: 264
10:33:43.950 > 〽 range: 262
10:33:44.231 > 〽 range: 264
10:33:44.508 > 〽 range: 262
10:33:44.788 > 〽 range: 263
10:33:45.068 > 〽 range: 264
10:33:45.348 > 〽 range: 263
10:33:45.628 > 〽 range: 262
10:33:45.908 > 〽 range: 262
10:33:46.188 > 〽 range: 264
10:33:46.468 > 〽 range: 262
10:33:46.748 > 〽 range: 263
10:33:47.028 > 〽 range: 263
10:33:47.310 > 〽 range: 262
10:33:47.591 > 〽 range: 263
10:33:47.871 > 〽 range: 263
10:33:48.151 > 〽 range: 264

...

10:33:59.351 > 〽 range: 262
10:33:59.631 > 〽 range: 262
10:33:59.911 > 〽 range: 262
10:34:00.191 > 〽 range: 262
10:34:00.471 > 〽 range: 262
10:34:00.751 > 〽 range: 262
10:34:01.031 > 〽 range: 263
10:34:01.309 > 〽 range: 262
10:34:01.589 > 〽 range: 262
10:34:01.870 > 〽 range: 262
10:34:02.151 > 〽 range: 263
10:34:02.349 > 〽 Stopping continuous ranging accepted.
10:34:22.350 > 〽 Start continuous ranging @ 280 ms accepted.
10:34:22.356 > 〽 range: 44
10:34:22.633 > 〽 range: 262
10:34:22.913 > 〽 range: 262
10:34:23.193 > 〽 range: 262
10:34:23.473 > 〽 range: 260
10:34:23.753 > 〽 range: 260
10:34:24.032 > 〽 range: 262

```
