#ifndef __selection_h__
#define __selection_h__

#include <Arduino.h>

template<typename T>
class SEL {
	public:
		bool G = false;
		T IN0 = T();
		T IN1 = T();
		T OUT = T();

		void update() {
			OUT = G ? IN1 : IN0;
		}
};

template<typename T>
class MAX {
	public:
		T IN1 = T();
		T IN2 = T();
		T OUT = T();

		void update() {
			OUT = (IN1 > IN2) ? IN1 : IN2;
		}
};

template<typename T>
class MIN {
	public:
		T IN1 = T();
		T IN2 = T();
		T OUT = T();

		void update() {
			OUT = (IN1 < IN2) ? IN1 : IN2;
		}
};

template<typename T>
class LIMIT {
	public:
		T MN = 0;
		T MX = 0;
		T IN = 0;
		T OUT = 0;

		void update() {
			if (IN < MN)
				OUT = MN;
			else if (IN > MX)
				OUT = MX;
			else
				OUT = IN;
		}
};

template<typename T>
class MUX {
	public:
		int K = 0;
		T IN0 = 0;
		T IN1 = 0;
		T OUT = 0;

		void update() {
			switch (K) {
				case 0:
					OUT = IN0;
					break;
				case 1:
					OUT = IN1;
					break;
				default:
					OUT = IN0; // fallback
			}
		}
};

#endif