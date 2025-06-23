#ifndef __triggers_h__
#define __triggers_h__

#include <Arduino.h>

class R_TRIG {
	public:
		bool CLK = false;
		bool Q = false;
	private:
		bool prev = false;

	public:
		void update() {
			Q = (CLK && !prev);
			prev = CLK;
		}
};

class F_TRIG {
	public:
		bool CLK = false;
		bool Q = false;
	private:
		bool prev = false;

	public:
		void update() {
			Q = (!CLK && prev);
			prev = CLK;
		}
};

class SR {
	public:
		bool S = false;
		bool R = false;
		bool Q = false;
	
		void update() {
			if (S) {
				Q = true;
			} else if (R) {
				Q = false;
			}
		}
};

class RS {
	public:
		bool S = false;
		bool R = false;
		bool Q = false;
	
		void update() {
			if (R) {
				Q = false;
			} else if (S) {
				Q = true;
			}
		}
};  

class SEMA {
	public:
		bool CLAIM = false;
	  	bool RELEASE = false;
	  	bool BUSY = false;
	
	  	void update() {
			if (RELEASE) {
		  		BUSY = false;
			} else if (CLAIM && !BUSY) {
		  		BUSY = true;
			}
	  	}
};

#endif 
