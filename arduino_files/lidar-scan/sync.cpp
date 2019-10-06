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

void Sync::calculate_speed(int p_position, int p_interval){

  int degreesTraveled;
  if ( p_position > get_lastMotorPos() ){
      
      degreesTraveled = p_position - get_lastMotorPos(); 
  }
  else{
      
      degreesTraveled = p_position - get_lastMotorPos() + 360;
  }

  set_lastMotorPos(p_position);
  float secsPerDeg = ( p_interval / 1000.0/*milliseconds*/ ) / degreesTraveled;
  set_secondsPerDegree(( 0.9 * get_secondsPerDegree() ) + ( 0.1 * secsPerDeg ));
}

void Sync::position_motor(){

    float m = (360.0/stepsPerRevolution)*motorStepCnt;
    
    this->motorPos = m;
}

//----------------------------------------getters and setters ---------------------------------

float Sync::get_motorPos(){
    
    return this->motorPos;
}

void Sync::set_motorPos(float p){
    
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

float Sync::get_lastMotorPos(){
    
    return this->lastMotorPos;
}

void Sync::set_lastMotorPos(float angle){

    this->lastMotorPos = angle;
}

float Sync::get_secondsPerDegree(){
    
    return this->secondsPerDegree;
}

void Sync::set_secondsPerDegree(float tx){

    this->secondsPerDegree = tx;
}