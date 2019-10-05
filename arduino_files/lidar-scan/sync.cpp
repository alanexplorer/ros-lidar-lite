#include "sync.h"

Sync::Sync(){

}

Sync::~Sync(){

}

void Sync::delta_angle(float angle_max, float angle_min, int n_steps){

    float d;

    d = (angle_max - angle_min)/(n_steps - 1);

    set_delta(d);

}

void Sync::servo_speed(float angle_max, float angle_min, float time){

    float t;

    t = (angle_max - angle_min)/time;

    set_speed(t);
}

void Sync::min_time_pause(float delta, float speed){

    float s;

    s = get_delta()/get_speed();

    set_sleep(s);
}

float Sync::get_angle_min(){

    return this->angle_min;
}

void Sync::set_angle_min(float angle){

    this->angle_min = angle;
}

float Sync::get_angle_max(){

    return this->angle_max;
}

void Sync::set_angle_max(float angle){

    this->angle_max = angle;
}

int Sync::get_n_steps(){
    
    return this->n_steps;
}

void Sync::set_n_steps(int n){
    
    this->n_steps = n;
}

float Sync::get_time_min_max(){
    
    return this->time_min_max;
}

void Sync::set_time_min_max(float t){

    this->time_min_max = t;

}

float Sync::get_delta(){

    return this->delta;
}

void Sync::set_delta(float d){

    this->delta = d;
}

float Sync::get_speed(){

    return this->speed;
}

void Sync::set_speed(float s){

    this->speed = s;
}

float Sync::get_sleep(){

    return this->sleep;
}

void Sync::set_sleep(float s){

    this->sleep = s;
}