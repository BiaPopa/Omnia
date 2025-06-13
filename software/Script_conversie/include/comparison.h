#ifndef __comparison_h__
#define __comparison_h__

#include <Arduino.h>

template <typename T>
class GT {
    public:
        T IN1 = 0; 
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 > IN2);
        }
};

template <typename T>
class GE {
    public:
        T IN1 = 0;
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 >= IN2);
        }
};

template <typename T>
class EQ {
    public:
        T IN1 = 0; 
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 == IN2);
        }
};

template <typename T>
class LT {
    public:
        T IN1 = 0; 
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 < IN2);
        }
};

template <typename T>
class LE {
    public:
        T IN1 = 0; 
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 <= IN2);
        }
};

template <typename T>
class NE {
    public:
        T IN1 = 0; 
        T IN2 = 0;
        bool OUT = false; 

        void update() {
            OUT = (IN1 != IN2);
        }
};

#endif 