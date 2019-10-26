#ifndef _SYNC_H_
#define _SYNC_H_

#include <stdlib.h>/* srand, rand */

class Sync
{
    int motorStepCnt;       
    int stepsPerRevolution;
    int outputStepsPerRevolution; // steps on inputGear for a complete cycle in outputGear
    float motorPos; // motor's position
    float lastMotorPos;
    float anglePerStep;
    float gearRatio;    
    
    public:
        // inputGear is the one connected to motor; outputGear is the passive one.
        Sync(int stepsPerRevolution, int inputGearTeeth, int outputGearTeeth); //start motor 0 degrees
        ~Sync();

        //getter and setter
        int get_outputStepsPerRevolution();
        float get_motorPos();
        void set_motorPos(float p);
        float get_lastMotorPos();
        void set_lastMotorPos(float a);
        float get_laserPos();
        void set_laserPos(float p);
        
        //methods
        float fakeLaser();
        float fakeMotor(int pos);
        float fakeLaserAngle(int pos);
};

#endif // SYNC_H
