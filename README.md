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
TO BE ADD LATER

```