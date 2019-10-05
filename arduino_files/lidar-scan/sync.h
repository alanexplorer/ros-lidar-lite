#ifndef _SYNC_H_
#define _SYNC_H_

class Sync
{
    float angle_min;       //- [deg]    Minimum angle of the servo
    float angle_max;       //- [deg]    Maximum angle of the servo
    int n_steps;           //- [ ]      number of measurements in the min-max range
    float time_min_max;    //- [s]      time for the servo to move from min to max
    float delta;
    float speed;
    float sleep;

    public:
        Sync(); //start motor 0 degrees
        ~Sync();

        //getter and setter
        float get_angle_min();
        void set_angle_min(float angle);
        float get_angle_max();
        void set_angle_max(float angle);
        int get_n_steps();
        void set_n_steps(int n);
        float get_time_min_max();
        void set_time_min_max(float t);
        float get_delta();
        void set_delta(float d);
        float get_speed();
        void set_speed(float s);
        float get_sleep();
        void set_sleep(float s);

        //methods
        void delta_angle(float angle_max, float angle_min, int n_steps); //Calculate the angle step
        void servo_speed(float angle_max, float angle_min, float time);  //speed servo
        void min_time_pause(float delta, float speed);
};

#endif // SYNC_H