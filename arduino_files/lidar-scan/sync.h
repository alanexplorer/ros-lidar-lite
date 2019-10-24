#ifndef _SYNC_H_
#define _SYNC_H_

#include <stdlib.h>/* srand, rand */

class Sync
{
    int motorStepCnt;       
    int stepsPerRevolution;       
    float motorPos; // motor's position
    float lastMotorPos;
    float anglePerStep;


    public:
        Sync(int stepsPerRevolution); //start motor 0 degrees
        ~Sync();

        //getter and setter
        float get_motorPos();
        void set_motorPos(float p);
        float get_lastMotorPos();
        void set_lastMotorPos(float a);
    
        //methods

        float fakeLaser();
        float fakeMotor(int pos);
};

#endif // SYNC_H
