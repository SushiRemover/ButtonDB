// Arduino Button Library
// https://github.com/SushiRemover/ButtonDB

#ifndef BUTTON_DB_H_INCLUDED
#define BUTTON_DB_H_INCLUDED

#include <Arduino.h>

class Button {
public:

  // Button(pin, dbTime, puEnable, invert) instantiates a button object.
  //
  // Required parameter:
  // pin      The Arduino pin the button is connected to
  //
  // Optional parameters:
  // dbTime   Debounce time in milliseconds (default 25ms)
  // invert   true to interpret a low logic level as pressed (default true)
  Button(uint8_t pin, uint32_t dbTime = 20, bool invert = true, bool iPullUp = true)
    : m_pin(pin), m_dbTime(dbTime), m_invert(invert), m_pullup(iPullUp) {}

// initialize the Button
  void begin();

  // Does debouncing, captures and maintains times, previous state, etc.
  // Call this function frequently to ensure the sketch is responsive to user input.
  void update();

  // Returns true if the button state was pressed at the last call to update().
  // Does not cause the button to be updated.
  bool isPressed() const { return m_state; }

  // Returns true if the button state was released at the last call to update().
  // Does not cause the button to be updated.
  bool isReleased() const { return !m_state; }

  // This function checks the button state to see if it changed
  // between the last two updateds and returns true or false accordingly.
  // This function does not cause the button to be updated.
  bool wasPressed() const { return m_state && m_changed; }

  // This function checks the button state to see if it changed
  // between the last two updateds and returns true or false accordingly.
  // This function does not cause the button to be updated.
  bool wasReleased() const { return !m_state && m_changed; }

  // Returns true if the button state at the last call to update() was pressed,
  // and has been in that state for at least the given number of milliseconds.
  // This function does not cause the button to be updated.
  bool pressedFor(uint32_t ms) const { return m_state && m_time - m_lastChange >= ms; }

  // Returns true if the button state at the last call to update() was released,
  // and has been in that state for at least the given number of milliseconds.
  // This function does not cause the button to be updated.
  bool releasedFor(uint32_t ms) const { return !m_state && m_time - m_lastChange >= ms; }

private:
  uint8_t m_pin;                  // arduino pin number connected to button
  uint32_t m_dbTime;              // debounce time (ms)
  bool m_pullup;                  // internal pullup resistor enabled
  bool m_invert;                  // if true, interpret logic low as pressed, else interpret logic high as pressed
  bool m_state = false;           // current button state, true=pressed
  bool m_lastState = false;       // previous button state
  bool m_changed = false;         // state changed since last update
  uint32_t m_time = 0;            // time of current state (ms from millis)
  uint32_t m_lastChange = 0;      // time of last state change (ms)
};

#endif
