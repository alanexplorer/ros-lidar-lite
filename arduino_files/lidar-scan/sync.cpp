#include "sync.h"

Sync::Sync(int stepsPerRevolution){

    this->stepsPerRevolution = stepsPerRevolution;
    this->motorStepCnt = 0;
    this->lastMotorPos = -1;
    this->motorPos = 0;
}

Sync::~Sync(){

    this->stepsPerRevolution = 0;
    this->motorStepCnt = 0;
    this->lastMotorPos = 0;

}

//----------------------------------------getters and setters ---------------------------------

float Sync::get_motorPos(){
    
    return this->motorPos;
}

void Sync::set_motorPos(float p){
    
    this->motorPos = p;
}

float Sync::get_lastMotorPos(){
    
    return this->lastMotorPos;
}

void Sync::set_lastMotorPos(float angle){

    this->lastMotorPos = angle;
}
