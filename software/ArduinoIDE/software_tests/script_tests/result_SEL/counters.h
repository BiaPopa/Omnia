#ifndef __counters_h__
#define __counters_h__

#include <Arduino.h>

class CTU {
    public:
        bool CU = false;       
        bool R = false;        
        int PV = 0;            
        int CV = 0;            
        bool Q = false;      

        void update() {
            if (R) {
                CV = 0;
                Q = false;
            } else if (CU) {
                CV++;
                if (CV >= PV) {
                    Q = true;
                }
            }
        }
};

class CTD {
    public:
        bool CD = false;      
        bool LD = false;       
        int PV = 0;            
        int CV = 0;           
        bool Q = false;       
    
        void update() {
            if (LD) {
                CV = PV;
                Q = false;
            } else if (CD) {
                if (CV > 0)
                    CV--;
                Q = (CV <= 0);
            }
        }
};

class CTUD {
    public:
        bool CU = false;
        bool CD = false;
        bool R = false;
        bool LD = false;
        int PV = 0;
        int CV = 0;
    
        bool QU = false;
        bool QD = false;
        bool CU_T = false;
        bool CD_T = false;
    
    private:
       bool prev_CU = false;
       bool prev_CD = false;
    
    public:
        void update() {
            CU_T = (CU && !prev_CU);
            CD_T = (CD && !prev_CD);
            prev_CU = CU;
            prev_CD = CD;
    
            if (R) {
                CV = 0;
            } else if (LD) {
                CV = PV;
            } else {
                if (CU_T) 
                    CV++;
                if (CD_T && CV > 0) 
                    CV--;
            }
    
            QU = (CV >= PV);
            QD = (CV <= 0);
        }
};    

template<typename T>
class CTU_Generic {
    public:
        bool CU = false;
        bool R = false;
        T PV = 0;
        T CV = 0;
        bool Q = false;

        void update() {
            if (R) {
                CV = 0;
                Q = false;
            } else if (CU) {
                CV++;
                if (CV >= PV) {
                    Q = true;
                }
            }
        }
};

using CTU_DINT = CTU_Generic<int32_t>;
using CTU_LINT = CTU_Generic<int64_t>;
using CTU_UDINT = CTU_Generic<uint32_t>;
using CTU_ULINT = CTU_Generic<uint64_t>;

template<typename T>
class CTD_Generic {
    public:
        bool CD = false;
        bool LD = false;
        T PV = 0;
        T CV = 0;
        bool Q = false;

        void update() {
            if (LD) {
                CV = PV;
                Q = false;
            } else if (CD) {
                if (CV > 0)
                    CV--;
                Q = (CV <= 0);
            }
        }
};

using CTD_DINT = CTD_Generic<int32_t>;
using CTD_LINT = CTD_Generic<int64_t>;
using CTD_UDINT = CTD_Generic<uint32_t>;
using CTD_ULINT = CTD_Generic<uint64_t>;

template<typename T>
class CTUD_Generic {
    public:
        bool CU = false;
        bool CD = false;
        bool R = false;
        bool LD = false;
        T PV = 0;
        T CV = 0;

        bool QU = false;
        bool QD = false;
        bool CU_T = false;
        bool CD_T = false;

    private:
       bool prev_CU = false;
       bool prev_CD = false;

    public:
        void update() {
            CU_T = (CU && !prev_CU);
            CD_T = (CD && !prev_CD);
            prev_CU = CU;
            prev_CD = CD;

            if (R) {
                CV = 0;
            } else if (LD) {
                CV = PV;
            } else {
                if (CU_T) 
                    CV++;
                if (CD_T && CV > 0) 
                    CV--;
            }

            QU = (CV >= PV);
            QD = (CV <= 0);
        }
};

using CTUD_DINT = CTUD_Generic<int32_t>;
using CTUD_LINT = CTUD_Generic<int64_t>;
using CTUD_UDINT = CTUD_Generic<uint32_t>;
using CTUD_ULINT = CTUD_Generic<uint64_t>;

#endif