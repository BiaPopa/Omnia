#ifndef __bitwise_h__
#define __bitwise_h__

#include <Arduino.h>

class AND {
    public:
        bool IN1 = false;
        bool IN2 = false;
        bool OUT = false;
    
        void update() {
            OUT = IN1 & IN2;
        }
};
    
class OR {
    public:
        bool IN1 = false;
        bool IN2 = false;
        bool OUT = false;
    
        void update() {
            OUT = IN1 | IN2;
        }
};

class XOR {
    public:
        bool IN1 = false;
        bool IN2 = false;
        bool OUT = false;
    
        void update() {
            OUT = IN1 ^ IN2;
        }
};    

class NOT {
    public:
        bool IN = false;
        bool OUT = false;
    
        void update() {
            OUT = !IN;
        }
};    

#endif