// Arduino Button Library
// https://github.com/SushiRemover/ButtonDB
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "ButtonDb.h"

// initialize the Button
void Button::begin() {
  pinMode(m_pin, m_pullup ? INPUT_PULLUP : INPUT);
  m_state = digitalRead(m_pin);
  if (m_invert) m_state = !m_state;
  m_time = millis();
  m_lastState = m_state;
  m_changed = false;
  m_lastChange = m_time;
}

// updates Button and runs debouncing logic
void Button::update() {
  uint32_t ms = millis();
  bool pinVal = digitalRead(m_pin);
  if (m_invert) pinVal = !pinVal;
  if (ms - m_lastChange < m_dbTime) {
    m_changed = false;
  } else {
    m_lastState = m_state;
    m_state = pinVal;
    m_changed = (m_state != m_lastState);
    if (m_changed) m_lastChange = ms;
  }
  m_time = ms;
}
