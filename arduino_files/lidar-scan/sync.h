#ifndef _SYNC_H_
#define _SYNC_H_

class Sync
{
    int motorStepCnt;       
    int stepsPerRevolution;       
    int motorPos; // motor's position
    int lastMotorPos;


    public:
        Sync(int stepsPerRevolution); //start motor 0 degrees
        ~Sync();

        //getter and setter
        int get_motorPos();
        void set_motorPos(int p);
        int get_lastMotorPos();
        void set_lastMotorPos(int a);

        //methods

};

#endif // SYNC_H
