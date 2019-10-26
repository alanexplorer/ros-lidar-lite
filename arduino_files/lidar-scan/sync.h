#ifndef _SYNC_H_
#define _SYNC_H_

#include <stdlib.h>/* srand, rand */

class Sync
{
    int motorStepCnt;       
    int stepsPerRevolution;
    int outputStepsPerRevolution; // steps on inputGear for a complete cycle in outputGear
    float motorPos; // motor's position
    float laserAngle; // outputGear angle
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
        float get_laserAngle();
        void set_laserAngle(float s); // receives step position s from inputGear
        
        //methods
        float fakeLaser();
        float fakeMotor(int pos);
        float fakeLaserAngle(int pos);
};

#endif // SYNC_H
