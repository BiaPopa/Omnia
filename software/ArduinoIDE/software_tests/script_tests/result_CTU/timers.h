#ifndef __timers_h__
#define __timers_h__

#include <Arduino.h>

class TON {
	public:
		bool IN = false;
		bool Q = false;
		unsigned long PT = 0;
		unsigned long _start = 0;

		void update() {
			if (IN) {
			if (_start == 0) _start = millis();
			if (millis() - _start >= PT) Q = true;
			} else {
			_start = 0;
			Q = false;
			}
		}
};

class TOF {
	public:
		bool IN = false;
		bool Q = false;
		unsigned long PT = 0;
		unsigned long _stop = 0;

		void update() {
			if (IN) {
			Q = true;
			_stop = millis();
			} else {
			if (millis() - _stop >= PT) Q = false;
			}
		}
};

class TP {
	public:
	  bool IN = false;
	  bool Q = false;
	  unsigned long PT = 1000;
	  unsigned long startTime = 0;
	  bool triggered = false;
  
	  void update() {
		if (IN && !triggered) {
		  Q = true;
		  startTime = millis();
		  triggered = true;
		}
  
		if (triggered && millis() - startTime >= PT) {
		  Q = false;
		}

		if (!IN) {
		  triggered = false;
		}
	  }
  };

#endif
