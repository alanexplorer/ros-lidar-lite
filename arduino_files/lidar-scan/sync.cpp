#include "sync.h"

Sync::Sync(int stepsPerRevolution, int inputGearTeeth, int outputGearTeeth){

    this->stepsPerRevolution = stepsPerRevolution;
    this->motorStepCnt = 0;
    this->motorPos = 0;

    this->anglePerStep = 360.0/stepsPerRevolution;
    
    this->gearRatio = (float)inputGearTeeth / (float)outputGearTeeth;
    this->outputStepsPerRevolution = (int)( this->stepsPerRevolution * 1.0 / this->gearRatio  );
}

Sync::~Sync(){
    this->stepsPerRevolution = 0;
    this->outputStepsPerRevolution = 0;
    this->motorStepCnt = 0;
}

//----------------------------------------getters and setters ---------------------------------

float Sync::get_laserAngle() {
  return this->anglePerStep * this->motorPos * this->gearRatio;
}

void Sync::set_laserAngle(float s) {
  this->laserAngle = this->anglePerStep * s * this->gearRatio;
}

float Sync::get_motorPos(){
    
    return this->motorPos;
}

void Sync::set_motorPos(float p){
    
    this->motorPos = p;
    this->set_laserAngle( p );
}

int Sync::get_outputStepsPerRevolution(){
    return this->outputStepsPerRevolution;
}

float Sync::fakeLaser() {
  float random = ((float) rand()) / (float) RAND_MAX;
  float r = random * 50;
  return r;
}

float Sync::fakeMotor(int pos) {
  float r = this->anglePerStep * pos;
  return r;
}

float Sync::fakeLaserAngle(int pos) {
  return this->anglePerStep * pos * this->gearRatio;
}
