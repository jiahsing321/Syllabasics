#include "ClassesInitialization.h"
#include<bits/stdc++.h>
#include<stdio.h>
#include<ctype.h>
using namespace std;
/*
 **************************************************************************
 *																		 *
 *																		 *
 *	Database Manager Initialization 									 *
 *																		 *
 *																		 *
 **************************************************************************
 */
User DbManager::getUser(string userID)
{
	int i;
	for(i = 0; i < 50; i++)
	{
		if(users[i].getID() == userID)
			return users[i];
	}

	return users[i - 1];

}

User DbManager::createUser()
{


	bool flag = false;
	string username, pass;
	ofstream outFile;

while(!flag)
	{
		cout << "please enter Username: ";
		cin >> username;

		if(users[userCount].validateID(username, userCount))
		{

			users[userCount].setID(username);
			cout << "Please enter the password: ";
			cin >> pass;

			if(users[userCount].validatePass(pass))
			{
				users[userCount].setPassword(pass);
				cout << "The Password has been set and account has been created" << endl;
				flag = true;

				//open the outputfile and write in the text file
				outFile.open("users.txt", ios::app);
				outFile <<endl << username << " " << pass << endl;
				outFile.close();
			}
			else
			{
				cout << "something happened" << endl;
			}
		}
		else
		{
			//Stops and re loops when username is not right
			cout << "Please re-input data..." << endl;
			flag = false;

		}

	}

	userCount += 1;
	return users[userCount - 1];


}



/*
 **************************************************************************
 *																		 *
 *																		 *
 *	User Object Initialization											 *
 *																		 *
 *																		 *
 **************************************************************************
 */

bool User::validateID(string ID, int count)
{
	bool Flag_Length, Flag_duplicate;
	int x = ID.length();

	//Declaring character Array
	char char_array[x + 1];

	//Copying contents of the string to char array
	strcpy(char_array, ID.c_str());




	//create a copy of the database to compare
	ifstream inFile;
	User temp[50];
	string line;
	inFile.open("users.txt");

	if(!inFile)
	{
		cout << "Could not open user text file" << endl;
	}
	else
	{
		int i = 0;;
		while(!inFile.eof())
		{

			//reads username from file and initializes the username in database
			getline(inFile, line, ' ');
			temp[i].setID(line);

			//reads Password from file and initializes the password in database
			getline(inFile, line, ' ');
			temp[i].setPassword(line);

			//iterate counter
			++i;

		}
	}

	inFile.close();



	//Check if Username is at least 3 characters long or less than 32 characters long
	if(x > 2 && x < 33  )
	{
		Flag_Length = true;
	}
	else
	{
		Flag_Length = false;
		cout << "Username has to be between 3-32 characters long" << endl;
	}


	//Check if the Username is not taken
	for(int i = 0; i < count; i ++)
	{
		if (temp[i].getID() == ID)
		{
			cout << "This username is taken" << endl;
		}
		else
		{
			Flag_duplicate = true;
		}

	}

	if(Flag_Length && Flag_duplicate)
	{
		return true;
	}
	else
	{
		return false;
	}


}

bool User::validatePass(string pass)
{
	bool hasUpper = false;
	bool hasSpecial = false;
	bool flag_length = false;
	int size = pass.length(); //Number of characters in password

	//Declaring character Array
	char char_array[size + 1];

	//Copying contents of the string to char array
	strcpy(char_array, pass.c_str());

	if (size > 7 && size < 33)
		flag_length = true;
	else
		cout << "Password length should be between 8-32 characters long " << endl;

	for(int count = 0; count < size; count++)
	{
		if(isupper(char_array[count]))
			hasUpper = true;

		//check if there is a special character
		if(char_array[count] == '!')
		{
			hasSpecial = true;
		}
		else if (char_array[count] == '@')
		{
			hasSpecial = true;
		}
		else if (char_array[count] == '#')
		{
			hasSpecial = true;
		}
		else if(char_array[count] == '$')
		{
			hasSpecial = true;
		}
		else if(char_array[count] == '%')
		{
			hasSpecial = true;
		}
		else if(char_array[count] == '^')
		{
			hasSpecial = true;
		}
		else if(char_array[count] == '&')
		{
			hasSpecial = true;
		}
		else if(char_array[count] == '*')
		{
			hasSpecial = true;
		}


	}

	if (flag_length == true  && hasUpper == true && hasSpecial == true)
		return true;
	else
		return false;
}

bool User::authenticate(string pass)
{
	if (pwd == pass)
		return true;
	else
		return false;
}

void User::setID(string id)
{
	uid = id;
}

void User::setPassword(string pass)
{
	pwd = pass;
}

string User::getID()
{
	return uid;
}

string User::getPwd()
{
	return pwd;
}



/*
 **************************************************************************
 *																		 *
 *																		 *
 *	Login Controller/GUI Initialization 								 *
 *																		 *
 *																		 *
 **************************************************************************
 */

User LoginController::login(string userId, string pass, DbManager Database)
{

	bool flag;
	//LoginController lControl;
	LoginGUI lGUI;
	int count = 0;
	string message;// Used for Login GUI
	string Uid, Pass;
	do
	{

		while (count < 50)
		{
			if (Database.users[count].getID() == userId)
				break;
			count++;
		}
		if (Database.users[count].authenticate(pass) == true)
		{

			cout << "Attempting to login... \n";
			//Attempting to get the user and initialize
			//currentU = test.login(Database.users[count].uid, Database.users[count].pwd);
			message = "Login Successful";

			lGUI.display(message);
			flag = true;
		}
		else
		{
			message = "Wrong Credentials";
			lGUI.display(message);
			cout << "Please re-enter the ID/Password again" << endl << "Username: ";
			cin >> userId;
			cout << "Password: ";
			cin >> pass;
		}

	} while (!flag);

	return Database.users[count];

}

void LoginGUI::display(string message)
{
	cout << message << endl;

}

/*
 **************************************************************************
 *																		 *
 *																		 *
 *	Account controller Initialization    								 *
 *																		 *
 *																		 *
 **************************************************************************
 */
/*
User AccountController::createAccount(string userID, string pass, GoogleAccount g)
{

}
 */



/*
 **************************************************************************
 *																		 *
 *																		 *
 *	Schedule Object Initialization 										 *
 *																		 *
 *																		 *
 **************************************************************************
 */
void Schedule::setclassID(string class_id)
{
	classID = class_id;
}

void Schedule::setcourseID(string course_id)
{
	courseID = course_id;
}

void Schedule::setcourseName(string course_name)
{
	courseName = course_name;
}

string Schedule::getclassID()
{
	return classID;
}

string Schedule::getcourseID()
{
	return courseID;
}

string Schedule::getcourseName()
{
	return courseName;
}






