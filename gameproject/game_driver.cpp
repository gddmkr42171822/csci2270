#include "game.hpp"
using namespace Thilenius;
using namespace std;



void manual() {
  // to run the manual tester just run
  // ./fsm_driver --manual

  /* cout << "Manual Program Begin" << endl;
  char a = 'A';
  int a_as_int = (int) a;
  cout << a << " vs " << a_as_int << endl;
  cout << 'B' << " vs " << (int) 'B' << endl;
  cout << "Manual Program End" << endl;
  */
  main();
}

SUITE_BEGIN("Game")

TEST_BEGIN("Game Test")
{
  int i = 1;
  IsTrue("Sanity Check", i == 1, "I'm crazy");
  bool crazy = true;
  IsTrue(" Do you ", crazy == false, " like Colors");
 
}TEST_END

SUITE_END

 /*int main (int argc, char* argv[])
{	
  if (argc == 2 && argv[1] == string("--manual")) {
    manual();
  } else {
    UTFrameworkInit;
  }
}
 */
