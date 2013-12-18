#include "UTFramework.h"
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class User {
  private:
  int livesSaved;
  bool hasHid;
  bool hasRan; 
  
  public:
  User();
  void change_livesSaved();
  void change_hasHid();
  void begin (); 
  void hide_mode(); 
  void run (); 
  void fight (); 
  void law_enfor(); 
  void end (); 
};

int main();
	
	
	




