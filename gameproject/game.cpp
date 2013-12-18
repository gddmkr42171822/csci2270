#include "game.hpp"


using namespace std;

/*
 * Layne : Came up with the idea and wrote part of the story and the branches as well as hide mode and ending.
 * Jane : Wrote the part of the story and branches as well as law enforcement mode and ending
 * Steven : Coded run mode and put everything together	
 * Bob : Coded fight mode
 * Brook: Wrote and edited Introspection
 * Alix: Wrote Introspection and helped with law enforcement mode
 * Ian: Wrote and edited Introspection
 * 
 * 
 */


User::User() 
{
livesSaved = 0;
hasHid = false;	
}

void User::change_livesSaved()
{
	livesSaved = livesSaved + 1;
}

void User::change_hasHid()
{
	if ( hasHid == false)
	{
		hasHid = true;
	}
}

void User::begin ()
{
	  bool valid = false;
	  bool valid1 = false;
	  int choice;
	  string location; 
	  	
	  //cout << "Entering begin" << endl; 
	  srand((unsigned) time(NULL)); 
	  int loca_gen = rand() % 3;
	  switch(loca_gen)
	  {
		  case 0:
			location = "class";
			break; 
		  case 1:
			location = "the library";
			break;
		  case 2:
			location = "the dining hall";  
			break;
	  }
	  //cout << "Location is " << location << endl; 
	  
	  cout << "Active Shooter Preparedness Training: University Edition" << endl;  
	  cout << "\nYou are in " << location << " when you hear gunshots outside." <<endl;
	  
      cout << "Press 1 to run to find an exit." << endl;
      cout << "Press 2 to find a hiding spot." << endl;
	  cout << "Press 3 to freeze." << endl;
      cout << "Press 4 to approach the shooter." << endl;
      
      cin >> choice; 
      
      //cout << "Choice is " << choice << endl;
      
    while(!valid){
      switch(choice)
      {
		  case 1:
		  {
			run(); 
			valid = true; 
		    break;
		  }
		  case 2:
		  {
			hide_mode();
			valid = true; 
			break; 
		  }
		  case 3:
		  {
			cout << "\n\nThere's something you can do to help yourself and others!" << endl; 
			cout << "Choose again?" << endl; 
			cout << "Press key number 1 to run, 2 to hide, or 4 to approach." << endl;
			cin >> choice; 
		    break;
		  }
		  case 4:
		  {
			int approach; 
			cout << "\n\nAre you sure?" << endl; 
			cout << "You might give away your location and endanger yourself and others." << endl; 
			cout << "Do you still want to approach?" << endl; 
			cout << "Press 1 to approach." << endl; 
			cout << "Press 2 to go back and choose again." << endl; 
			cin >> approach;
		    while(!valid1)
		    { 
			  switch(approach)
			  {
				case 1:
				{
				  
				  livesSaved = 0; 
				  cout << "\n\nYou risked your life and put others in harm's way!" << endl; 
				  cout << "Game over" << endl << "Try again?" << endl; 
				  cout << "Press key number 1 to run, 2 to hide, or 3 to freeze." << endl;
				  cin >> choice; 
				  valid1 = true;
				  break;
			    }
				case 2:
				{
				  cout << "\n\nPress key number 1 to run, 2 to hide, or 3 to freeze." << endl;
				  cin >> choice; 
				  valid1 = true;
				  break;
			    }
				default:
				{
				  cout << "\n\nInvalid entry. Please choose 1 to run, 2 to hide, or 3 to freeze." << endl;
				  cin >> approach;
				  break;
			    }
			  }
		    }
		    break;
		  }
		  default:
		  {
		    cout << "\n\nInvalid entry. Press the number key 1 to run, 2 to hide, 3 to freeze, or 4 to approach.\n"; 
		    cin >> choice;
		    break;
		  }
	  } 
  }

}

void User::hide_mode ()
{
	bool valid1 = false; 
	bool valid2 = false; 
	bool valid3 = false; 
	bool valid4 = false; 
	bool valid5 = false; 
	
	change_hasHid(); 
	//cout << "hasHid? " << hasHid << endl; 
	
	int choice1; 
	int choice2; 
	int choice3; 
	int choice4; 
	int approach; 
	
	cout << "\n\nPress 1 to survey your environment or press 2 to quickly hide." << endl; 
	cin >> choice1; 
	
	while(!valid1)
	{
		switch(choice1)
		{
		  case 1:
		  {
			cout << "\nGreat! You saved lives by taking the time to turn off the lights and lock the doors!" << endl;
			change_livesSaved(); 
			valid1 = true; 
		    break;
		  }
		  case 2: 
		  {
			  cout << "\nOops! You forgot to turn off the lights and lock the doors!" << endl;
			  cout << "Remember to take the time to survey your environment" << endl; 
			  valid1 = true; 
			  break; 
		  }
		  default:
		  {
		    cout << "\n\nInvalid entry." << endl; 
		    cout << "Press 1 to survey your environment" << endl; 
		    cout << "Press 2 to quickly hide." << endl; 
		    cin >> choice1;
		    //break; 
		  }
		} 
	}
	
	cout << "\n\nPress 1 to hide with friends. " << endl; 
	cout << "Press 2 to hide alone." << endl; 
	cin >> choice2; 
	
	while(!valid2)
	{
		switch(choice2)
		{
		  case 1:
		  {
			cout << "\nOops!" << endl;  
			cout << "Next time, spread out if possible." << endl; 
			cout << "This can save lives!" << endl; 
			valid2 = true; 
		    break;
		  }
		  case 2: 
		  {
			  cout << "\nGreat!" << endl; 
			  cout << "You've saved lives by spreading out and hiding separately!" << endl; 
			  change_livesSaved(); 
			  valid2 = true; 
			  break; 
		  }
		  default:
		  {
		    cout << "\n\nInvalid entry." << endl; 
		    cout << "Press 1 to hide with friends." << endl; 
		    cout << "Press 2 to hide alone." << endl; 
		    cin >> choice2;
		    //break; 
		  }
		} 
	}	
	
	cout << "\n\nGreat, you've found a safe hiding place. " << endl; 
	cout << "Do you want to call a friend?" << endl;
	cout << "Press 1 to call a friend." << endl; 
	cout << "Press 2 to silence your phone." << endl;  
	cin >> choice3; 
	
	while(!valid3)
	{
		switch(choice3)
		{
		  case 1:
		  {
			cout << "\nOops!" << endl;  
			cout << "Next time, silence your phone a.s.a.p." << endl; 
			cout << "And remember to turn off the vibration!" << endl; 
			cout << "These sounds can signal your position and endanger lives." << endl; 
			cout << "Once silent, you may be able to safely text someone who can help." << endl; 
			valid3 = true; 
		    break;
		  }
		  case 2: 
		  {
			  cout << "\nGreat!" << endl; 
			  cout << "You've saved lives by silencing your phone" << endl; 
			  cout << "Remember to turn off the vibration!" << endl; 
			  cout << "These sounds can signal your position and endanger lives." << endl; 
			  cout << "Once silent, you may be able to safely text someone who can help." << endl; 
			  change_livesSaved(); 
			  valid3 = true; 
			  break; 
		  }
		  default:
		  {
		    cout << "\n\nInvalid entry." << endl; 
		    cout << "Press 1 to call a friend." << endl; 
		    cout << "Press 2 to silence your phone." << endl; 
		    cin >> choice3;
		    //break; 
		  }
		} 
	}	
	
	//cout << "\nRemember to survey your environment for possible weapons!" << endl; 
	//cout << "These are the objects you have at your disposal: " << endl; 
	// cout randgen weapons
	
	//Use hasRan bool to determine if run mode needed? Ask Commander best practice. 
	
	cout << "\n\nYou hear the shooter approaching your area." << endl; 
	cout << "Press 1 to run to find an exit." << endl; 
	cout << "Press 2 to stay hidden." << endl; 
	cout << "Press 3 to approach the shooter" << endl; 
	cin >> choice4; 
	
	while(!valid4)
	{
		switch(choice4)
		{
		  case 1:
		  {
			//send to run mode
			run();
			valid4 = true; 
		    break;
		  }
		  case 2: 
		  {
			  //send to fight mode
			  fight();
			  valid4 = true; 
			  break; 
		  }
		  case 3:
		  {
			cout << "\n\nAre you sure?" << endl; 
			cout << "You might give away your location and endanger yourself and others." << endl; 
			cout << "Do you still want to approach?\n" << endl; 
			cout << "\nPress 1 to approach." << endl; 
			cout << "Press 2 to go back and choose again." << endl; 
			cin >> approach;
		    while(!valid5)
		    { 
			  switch(approach)
			  {
				case 1:
				{
				  
				  livesSaved = 0; 
				  cout << "\n\nYou risked your life and put others in harm's way!" << endl; 
				  cout << "Game over" << endl << "Try again?" << endl; 
				  cout << "Press 1 to run and find an exit" << endl; 
				  cout << "Press 2 to stay hidden." << endl;
				  cin >> choice4; 
				  valid5 = true;
				  break;
			    }
				case 2:
				{
				  cout << "Press 1 to run and find an exit" << endl; 
				  cout << "Press 2 to stay hidden." << endl;
				  cin >> choice4;
				  valid5 = true;
				  break;
			    }
				default:
				{
				  cout << "\n\nInvalid entry." << endl; 
				  cout << "Press 1 to run and find an exit" << endl; 
				  cout << "Press 2 to stay hidden." << endl;
				  cin >> approach;
				  break;
			    }
			  }
		    }
		    break;
		  }
		  
		  default:
		  {
		    cout << "\n\nInvalid entry." << endl; 
		    cout << "Press 1 to run and find an exit" << endl; 
			cout << "Press 2 to stay hidden." << endl;
			cout << "Press 3 to approach the shooter." << endl; 
		    cin >> choice4;
		    //break; 
		  }
		} 
	}
}	
	
void User::run()

{	bool hall=false;
	bool door=false;

	srand((unsigned)time(NULL));
	int rand_number = rand() %2;
	
	if (rand_number == 0) {cout<<"You turn to find an exit and see a door that leads to a closet. Do you open it??\n1. Yes\n2. No\n\n"; door = true;}
	if (rand_number == 1) {cout<<"You turn to find an exit and see a hallway. Do you enter it?\n1. Yes\n2. No\n\n"; hall = true;}
	
	int x;
	cin>>x;
	if (x>2 || x<1) {cout<<"invalid answer\n"; run();}
	
	if (x==2) {run();}
	if (x==1 && door == true)  
		{
			srand((unsigned)time(NULL));
			int rand_locked = rand() %2;
				
				if (rand_locked == 0 && door == true) { cout<< "The door is locked! You decide to look for another exit.\n"; run(); }
				if (rand_locked == 1 && door == true) 
				{ 
					cout<< "The door is unlocked and leads to a closet.\n"; 
					hide_mode();
				}
		}
		
	if (x==1 && hall == true) 
			{ cout<< "You are running down the hall and are approached by a shooter!\n1. fight \n2. run\n";
	
				int xx;
				cin>>xx;
				if (xx == 1) {fight();}
				if (xx == 2) {run();}
			}
}

void User::fight()
{
	bool good_choice = false;
	while (good_choice == false)
	{
		int fight_choice;
		cout << "\nYou are approached by a shooter and have no chance to escape or hide!!\n" << endl;
		cout << "What do you want to do?\n";
		cout << "Type 1, then enter, to FREEZE\n";
		cout << "Type 2, then enter, to HESITATE\n";
		cout << "Type 3, then enter, to CHARGE\n";
		cin >> fight_choice;
		
		switch (fight_choice)
		{
			case 1:
			{
				cout << "\nThat was not a wise decision.\n";
				cout << "There is something you can do to help yourself and others!  Please try again!\n";
				break;
			}
			case 2:
			{
				cout << "\nGood choice! You saved lives by taking time to survey the environment and plan your attack!\n";
				change_livesSaved();
				while ( !good_choice)
				{
					int choice1 = 0;
					cout << "Do you want to...\n";
					cout << "Type 1, then enter, improvise a weapon?\n";
					cout << "Type 2, then enter, develop a plan to tackle?\n";
					cout << "Type 3, then enter, find a way to distract?\n";
					cin >> choice1;
					
					switch (choice1)
					{
						case 1:
						{
							int choice3 = 0;
							int randgen = rand() % 3;
							int scissors = 1;
							int pencil = 2;
							cout << "\nYou picked up a weapon.\n";
							if (randgen == scissors)
							cout << "It is some scissors.\n";
							else if (randgen == pencil)
							cout << "It is a pencil.\n";
							else
							cout << "It is a folding chair.\n";
							cout << "\nDo you want to use this to ...\n";
							cout << "Type 1, then enter, to throw?\n";
							cout << "Type 2, then enter, attack with?\n";
							cout << "Type 3, then enter, distract with?\n";
							cin >> choice3;
							
							cout << "\nCongratulations! You disabled the shooter, took the weapon, and held until the police arrived!\n";
									change_livesSaved();
									//call law_endforcement();
									cout << "\nEntering Law Enforcement mode... \n";
									law_enfor();
									good_choice = true;
									break;
						}
						case 2:
						{
							while ( !good_choice)
							{
								int choice2 = 0;
								cout << "\nType 1, then enter, to distract with threatening gestures while neighbor tackles.\n";
								cout << "Type 2, then enter, to throw something to distract while neighbor tackles.\n";
								cout << "Type 3, then enter, to go berserk.\n";
								cin >> choice2;
								
								if ( choice2 == 1 || choice2 == 2 || choice2 == 3)
								{
									cout << "\nCongratulations! You disabled the shooter, took the weapon, and held until the police arrived!\n";
									change_livesSaved();
									//call law_endforcement();
									cout << "Entering Law Enforcement mode... \n";
									law_enfor();
									good_choice = true;
								}
								else
								{
									cout << "Please try again.\n";
								}
								
							}
							break;
						}
						case 3:
						{
							while ( !good_choice)
							{
								int choice2 = 0;
								cout << "\nType 1, then enter, to distract with threatening gestures while neighbor tackles.\n";
								cout << "Type 2, then enter, to throw something to distract while neighbor tackles.\n";
								cout << "Type 3, then enter, to go berserk.\n";
								cin >> choice2;
								if ( choice2 == 1 || choice2 == 2 || choice2 == 3)
								{
									cout << "\nCongratulations! You disabled the shooter, took the weapon, and held until the police arrived!\n";
									change_livesSaved(); 
									law_enfor();
									good_choice = true;
								}
								else
								{
									cout << "Please try again.\n";
								}
							}
							break;
						}
						default:
						{
							cout << "Please try again.\n";
						}
					}
				}
				good_choice = true;
				break;
			}
			case 3:
			{
				cout << "\nThat was not a wise decision.\n";
				//add warnings
				cout << "While charging might work taking a second to survey your environment could save lives.  Please make another choice.\n";
				break;
			}
			default:
			{
				cout << "Please make your choice again.\n";
				break;
			}
		}
	}
	
}

void User::law_enfor()
{
	int play;
	int choice;
	int choice2;
	cout << "Congratulations!" << endl;
	cout << "You have now entered the BONUS round of Law Enforcement Protocol." << endl;
	cout << "Press 1 to play BONUS round." << endl;
	cin >> play;
	if (play != 1)
	{
		cout << "Invalid entry. Please enter 1." << endl;
		cin >> play;
	}
	if (play == 1)
	{
		cout << "\n\nFirst Question: " << endl;
		cout << "When law enforcement arrives, it is your own responsibility to: "<< endl;
		cout << "1. Point and scream the location of the shooter." << endl;
		cout << "2. Put down any items in your hands and remain calm in your area." << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "\n\nWhoops! Drawing attention to yourself can distract law enforcemnt from finding the shooter. It is important to remain calm and stay where you are." << endl;
			
		}
		if (choice == 2)
		{
			cout << "\n\nCorrect! It is the law enforcement's responsibility to focus on" << endl;
			cout << "finding and incapacitating the shooter. It is important to remain in your area" << endl;
			cout << "and follow instructions." << endl;
		}
		//if (choice != 1 || choice != 2)
		//{
			//cout << "Invalid entry. Please enter 1 or 2." << endl;
			//cin >> choice;
		//}
		while (choice == 1 || choice == 2)
		{
			cout << "\n\nNext question:" << endl;
			cout << "The most important indicator to law enforcement that you are not armed is: " << endl;
			cout << "1. Showing them that you are hurt or injured." << endl;
			cout << "2. Raising your hands high and spreading your fingers." << endl;
			cout << "3. Directing law enforcement officers to injured persons." << endl;
			cin >> choice2;
			
			if (choice2 == 1 || choice2 == 3)
			{
				cout << "\n\nWrong." << endl;
				cout << "\n\nThe police are trained to find/stop the shooter before they attend" << endl;
				cout << "to the victims so don't expect them to help you" << endl;
				cout << "until the shooter is disarmed and arrested." << endl;
				cout << "\nTo identify innocent people, law enforcement is trained to see hands," << endl; 
				cout << "so make sure you spread your fingers and show them your hands." << endl;
				cout << "\nAfter staying in your place with your hands visible," << endl;
				cout << "they will assist you and the other victims after they have stopped the shooter." << endl;
				cout << "The EMS will take care injured persons and the police will secure the area." << endl;
				cout << "\n\nMake sure you don't distract them so they can do their job!" << endl;
				cout << "\n\nYou have successfully completed the Active-Shooter Awareness learning module" << endl;
				cout << "based off of The Department Homeland's Security." << endl;
				break;
			}
			if (choice2 == 2)
			{
				cout << "\n\nCorrect! Law enforcement officials strickly declare that you put" << endl;
				cout << "your hands up and wait for them to take care of the shooter." << endl;
				cout << "Then they will assist you and the other victims." << endl;
				cout << "\nThe EMS will take care injured persons and the police will secure the area." << endl;
				cout << "\n\nMake sure you don't distract them so they can do their job!" << endl;
				cout << "\n\nYou have successfully completed the Active-Shooter Awareness learning module" << endl;
				cout << "based off of The Department of Homeland Security." << endl;
				break;
			}
		}
		
		end(); 
		
	}
}



void User::end()
{
	cout << "Congratulations! \nYou have completed the Active Shooter Preparedness training!" << endl; 
	if (livesSaved == 0)
		cout << "\nYou did not save any lives this time." << "\nPlay the game again to boost your skills." << endl; 
	
	else 
	{
	cout << "\nYou saved " << livesSaved << " lives!" << endl; 
	cout << "Play the game again to boost your skills and save more lives!" << endl; 
	}
	
	cout << "Remember: \nUse your best judgement, make a plan, and be prepared to change it." << "\nThink flexibility and train your instincts!" << endl; 
	cout << "\nFor more info and training, visit: " << "1) The Dept. of Homeland Secuity's training, \nhttp://emilms.fema.gov/IS907/index.htm" << endl; 
	cout << "\n2) The CU-Boulder Police Dept.'s training, \nhttp://police.colorado.edu/activeharmerresponse" << endl; 
	cout << "Thank you for keeping everyone safe!" << endl; 
}	

int main()
{
 
	User user; 
	
	user.begin (); 
	
}



