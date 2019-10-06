#ifndef _SYNC_H_
#define _SYNC_H_

class Sync
{
    int motorStepCnt;       
    int stepsPerRevolution;       
    int motorPos; // motor's position
    int lastMotorPos;
    float dT; // diference betwen times millis()
    float secondsPerDegree;


    public:
        Sync(int stepsPerRevolution); //start motor 0 degrees
        ~Sync();

        //getter and setter
        int get_motorPos();
        void set_motorPos(int p);
        long get_dT();
        void set_dT(long tNew, long tOld);
        int get_lastMotorPos();
        void set_lastMotorPos(int a);
        float get_secondsPerDegree();
        void set_secondsPerDegree(float tx);


        //methods
    
        void calculate_speed();  //speed servo
        void position_motor(); //calc motor'position
};

#endif // SYNC_H