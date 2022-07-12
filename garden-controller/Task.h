#ifndef __TASK__
#define __TASK__

class Task {
  long myPeriod;
  long timeElapsed;
  bool active;
  
public:
  virtual void init(long period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;


  bool updateAndCheckTime(long basePeriod){
     
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool isActive(){
    return active;
  }

  void setActive(bool active){
    this->active = active;
  }
  
};

#endif
