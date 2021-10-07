/**
 * Homie Node for VL53L0x.
 *
 */
#include "LoxRanger.hpp"

LoxRanger::LoxRanger(const char *id, const char *name, const char *cType, const unsigned long durationInSeconds, const int gpioPin)
    : HomieNode(id, name, cType),
      _pinGPIO(gpioPin),
      _ulCycleTime((durationInSeconds * 1000))
{
  printCaption();
}

/**
 *
 */
bool LoxRanger::isReady()
{
  return vbEnabled;
}

/**
 *
 */
void LoxRanger::setRunDuration(const int seconds) {
  if (seconds != 0) {
    _ulCycleTime = (unsigned long)(seconds * 1000);
  }
}

/**
 *
 */
void LoxRanger::startRanging() {
  vbEnabled = true;
}

/**
 *
 */
void LoxRanger::stopRanging() {
  vbEnabled = false;
  vTaskDelay(300);
  lox.stopContinuous();
  vTaskDelay(300);
}

/**
 *
 */
void LoxRanger::printCaption() {
  Homie.getLogger() << cCaption << endl;
}

/**
 * Handles the received MQTT messages from Homie.
 * - no settable properties
 */
bool LoxRanger::handleInput(const HomieRange& range, const String& property, const String& value) {

  printCaption();
  Homie.getLogger() << cIndent << "〽 handleInput -> property '" << property << "' value=" << value << endl;

  return false;
}

/**
 *
 */
void LoxRanger::loop()
{
  ulTimebase = millis();
  ulElapsedTime = ulTimebase - ulCycleTimebase;
  vbRangeDuration = ((ulTimebase - ulLastTimebase) >= ulRangingDuration);
  vbRangeCycle = (ulElapsedTime >= _ulCycleTime);

  if (vbEnabled) {

      if (vbLastRangeCycle && vbRangeCycle)
      {
        vbLastRangeCycle = !vbLastRangeCycle;

        lox.startContinuous((uint32_t)ulRangingDuration);
        Homie.getLogger() << "〽 Start continuous ranging @ " << ulRangingDuration << " ms accepted." << endl;
      }

    if (vbRangeDuration && vbRangeCycle)
    {
      if (!digitalRead(_pinGPIO))
      {
		  uint32_t rangeMM = lox.readRangeContinuousMillimeters();
        char buf[32];
        snprintf(buf, sizeof(buf), cRangeFormat, rangeMM);
        setProperty(cRangeID).send(buf);

        Homie.getLogger() << "〽 range: " << rangeMM << endl;

        ulLastTimebase = ulTimebase;
      }
    }

    if (ulElapsedTime >= (_ulCycleTime * 2))
    {
      lox.stopContinuous();
      ulCycleTimebase  = ulTimebase;
      vbLastRangeCycle = !vbLastRangeCycle;
      Homie.getLogger() << "〽 Stopping continuous ranging accepted." << endl;
    }
  }
}

/**
 *
 */
void LoxRanger::onReadyToOperate() {
  Homie.getLogger() << "〽 "<< "Node: " << getName() << " Ready to operate." << endl;

  vbEnabled = true;
}

/**
 *
 */
void LoxRanger::setup() {
  printCaption();

  pinMode(_pinGPIO, INPUT_PULLUP);

  vbEnabled = false;

  lox.setTimeout(500);
  if (!lox.init())
  {
    vTaskDelay(1000);
    while (!lox.init())
    {
      Homie.getLogger() << "• Failed to detect and initialize VL53L0x sensor!" << endl;
      vTaskDelay(1000);
    }
  }

  // lower the return signal rate limit (default is 0.25 MCPS)
  if (lox.setSignalRateLimit(0.2)) {
      Homie.getLogger() << "〽 0.2mcps rate limit (medium) accepted." << endl;
  }

  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  if (lox.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 16)) {
      Homie.getLogger() << "〽 16 pclks pulse period accepted." << endl;
  }

  if (lox.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 12)) {
      Homie.getLogger() << "〽 12 pclks final pulse period accepted." << endl;
  }

  if (lox.setMeasurementTimingBudget(200000)) {
      Homie.getLogger() << "〽 200us timing budget accepted." << endl;

      ulCycleTimebase = millis(); // - _ulCycleTime; // need a startup delay
      ulLastTimebase = millis();
  }

  advertise(cRangeID)
          .setName("distance in mm")
          .setDatatype("integer")
          .setFormat(cRangeFormat)
          .setRetained(false)
          .setUnit("mm");

  advertise(cStatusID)
      .setName("range operating status")
      .setDatatype("string")
      .setFormat(cStatusFormat)
      .setRetained(false)
      .setUnit("#");

  advertise(cSignalID)
      .setName("peak signal count rate")
      .setDatatype("float")
      .setFormat(cSignalFormat)
      .setRetained(false)
      .setUnit("mcps");

  advertise(cAmbientID)
      .setName("ambient light count rate")
      .setDatatype("float")
      .setFormat(cAmbientFormat)
      .setRetained(false)
      .setUnit("mcps");
}
