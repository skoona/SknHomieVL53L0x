/**
 * Homie Node for VL53L1x.
 *
 */
#include "LoxRanger.hpp"

LoxRanger::LoxRanger(const char *id, const char *name, const char *cType, const unsigned long durationInSeconds, const int sdaPin, const int sclPin, const int gpioPin)
    : HomieNode(id, name, cType),
      _pinSDA(sdaPin),
      _pinSCL(sclPin),
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
        lox.read(false);
        char buf[32];
        snprintf(buf, sizeof(buf), cRangeFormat, lox.ranging_data.range_mm);
        setProperty(cRangeID).send(buf);

        snprintf(buf, sizeof(buf), cStatusFormat, lox.rangeStatusToString(lox.ranging_data.range_status));
        setProperty(cStatusID).send(buf);

        snprintf(buf, sizeof(buf), cSignalFormat, lox.ranging_data.peak_signal_count_rate_MCPS);
        setProperty(cSignalID).send(buf);

        snprintf(buf, sizeof(buf), cAmbientFormat, lox.ranging_data.ambient_count_rate_MCPS);
        setProperty(cAmbientID).send(buf);

        Homie.getLogger() << "〽 range: " << lox.ranging_data.range_mm 
                          << " mm \tstatus: " << lox.rangeStatusToString(lox.ranging_data.range_status) 
                          << "\tsignal: " << lox.ranging_data.peak_signal_count_rate_MCPS 
                          << " MCPS\tambient: " << lox.ranging_data.ambient_count_rate_MCPS 
                          << " MCPS" << endl;

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
  Homie.getLogger() << "〽 " << getName() << " Ready to operate." << endl;

  vbEnabled = true;
}

/**
 *
 */
void LoxRanger::setup() {
  printCaption();

  pinMode(_pinGPIO, INPUT_PULLUP);

  Wire.begin(_pinSDA, _pinSCL, 400000U);
  vbEnabled = false;

  lox.setTimeout(500);
  if (!lox.init())
  {
    vTaskDelay(1000);
    while (!lox.init())
    {
      Homie.getLogger() << "• Failed to detect and initialize sensor!" << endl;
      vTaskDelay(1000);
    }
  }

  if (lox.setDistanceMode(VL53L1X::Medium))
  {
    Homie.getLogger() << "〽 Medium distance mode accepted." << endl;
  }

  if (lox.setMeasurementTimingBudget(200000))
  {
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
