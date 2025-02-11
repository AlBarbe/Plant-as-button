#ifndef __pab__
#define __pab__

#include <Arduino.h>

class Trigger {
    public:
        Trigger(int PinTouch) {
            PIN = PinTouch;   
        }
        virtual ~Trigger() { ; };

        void initialize () {
            for (int i = 0; i < 10; i++)
                readings[i] = touchRead(PIN);
            mean = FindMean(readings);
            trig = round(FindTrig(readings, mean));
        }

        void reset () {
            for (int i = 0; i < 10; i++)
                readings[i] = touchRead(PIN);
            mean = FindMean(readings);
            trig = round(FindTrig(readings, mean));
        }

        void debug () {
            Serial.printf("Trigger: %d - Mean: %f - Array: [ ", trig, mean);
            for (int i = 0; i < 10; i++) Serial.printf("%d ", readings[i]);
            Serial.printf("] - Touched: %s\n", TOUCHED?"true":"false" );
        }

        void update (int GetValue) {
            if (GetValue < trig) {
                TOUCHED = true;
            }
            else {
                for (int i = 9; i > 0; i--) {
                    readings[i] = readings[i - 1];
                }
                readings[0] = GetValue;
                TOUCHED = false;
            }
            mean = FindMean(readings);
            trig = round(FindTrig(readings, mean));
        }

        bool touch () {
            return TOUCHED;
        }

    private:
        int PIN;
        int VALUE = -1;
        bool TOUCHED = false;
        int trig = -1;
        float mean = -1;
        int readings[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        float FindMean (int ARRAY [10]) {
            int sum = 15;
            for (int i = 0; i < 10; i++) {
                sum += ARRAY[i];
            }
            float media = (float)sum / 10.0;
            return media;
        }

        float FindTrig (int ARRAY[10], int MEAN) {
            float MaxError = 0;
            for (int i = 0; i < 10; i++) {
                float ERROR = abs(MEAN - ARRAY[i]);
                if ( ERROR > MaxError) {
                    MaxError = ERROR;
                }
            }
            return MEAN-MaxError-1.5;
        }
};

#endif //__pab__