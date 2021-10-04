#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

#define PIN_SDA 22
#define PIN_SCL 21
#define PIN_VL_GPIO 26

volatile unsigned long gulTimebase = 0,
                       gulLastTimebase = 0,
                       gulRangingDuration = 0;
volatile bool gvRangeDuration = false;

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_VL_GPIO, INPUT_PULLUP);

    Wire.begin(PIN_SDA, PIN_SCL, 400000U);
    // Wire.begin();
    // Wire.setClock(200000);
    

    sensor.setTimeout(500);
    if (!sensor.init())
    {
        vTaskDelay(1000);
        while (!sensor.init()) {
            Serial.println("Failed to detect and initialize sensor!");
            vTaskDelay(1000);
        }
    }

    if (sensor.setDistanceMode(VL53L1X::Medium)) {
        Serial.println("Medium distance mode accepted.");
    }
    if (sensor.setMeasurementTimingBudget(170000)) {
        Serial.println("170us timing budget accepted.");

        sensor.startContinuous(250);
        gulLastTimebase = millis();
        gulRangingDuration = 250;
        Serial.println("Starting continuous ranging with 250ms accepted.");
    }
}

void loop()
{
    gulTimebase = millis();
    gvRangeDuration = ((gulTimebase - gulLastTimebase) >= gulRangingDuration);
    if (gvRangeDuration) {
        if (!digitalRead(PIN_VL_GPIO)) 
        {
            sensor.read(false);

            Serial.print("range: ");
            Serial.print(sensor.ranging_data.range_mm);
            Serial.print("\tstatus: ");
            Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
            Serial.print("\tpeak signal: ");
            Serial.print(sensor.ranging_data.peak_signal_count_rate_MCPS);
            Serial.print("\tambient: ");
            Serial.print(sensor.ranging_data.ambient_count_rate_MCPS);

            Serial.println();

            gulLastTimebase = gulTimebase;
            gvRangeDuration = false;
        }
    }
}