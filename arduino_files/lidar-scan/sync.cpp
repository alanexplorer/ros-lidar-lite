#include "sync.h"

Sync::Sync(int stepsPerRevolution){

    this->stepsPerRevolution = stepsPerRevolution;
    this->motorStepCnt = 0;
    this->lastMotorPos = -1;
    this->secondsPerDegree = 0;

}

Sync::~Sync(){

    this->stepsPerRevolution = 0;
    this->motorStepCnt = 0;
    this->lastMotorPos = 0;
    this->secondsPerDegree = 0;

}

void Sync::calculate_speed(){

  int degreesTraveled;
  
  if ( this->motorPos > get_lastMotorPos() ){
      
      degreesTraveled = this->motorPos - get_lastMotorPos(); 
  }
  else{
      
      degreesTraveled = this->motorPos - get_lastMotorPos() + 360;
  }

  set_lastMotorPos(this->motorPos);
  float secsPerDeg = ( this->dT / 1000.0/*milliseconds*/ ) / degreesTraveled;
  set_secondsPerDegree(( 0.9 * get_secondsPerDegree() ) + ( 0.1 * secsPerDeg ));
}

void Sync::position_motor(){

    float m = (360.0/stepsPerRevolution)*motorStepCnt;
    
    this->motorPos = m;
}

void Sync::stepAdd(){

    if(++this->motorStepCnt > this->stepsPerRevolution){
      
      this->motorStepCnt = 0;
    }
}

//----------------------------------------getters and setters ---------------------------------

int Sync::get_motorPos(){
    
    return this->motorPos;
}

void Sync::set_motorPos(int p){
    
    this->motorPos = p;
}

long Sync::get_dT(){
    
    return this->dT;
}

void Sync::set_dT(long tNew, long tOld){
    
    long t;
    t = tNew - tOld;
    this->dT = t;
}

int Sync::get_lastMotorPos(){
    
    return this->lastMotorPos;
}

void Sync::set_lastMotorPos(int a){

    this->lastMotorPos = a;
}

float Sync::get_secondsPerDegree(){
    
    return this->secondsPerDegree;
}

void Sync::set_secondsPerDegree(float tx){

    this->secondsPerDegree = tx;
}
