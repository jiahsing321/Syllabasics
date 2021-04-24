#include<iostream>
#include<iomanip>
#include<string>
#include"ClassesInitialization.h"
using namespace std;

void startProgram();
void afterlogin(User user);
void Manageaccount(User user);
void ScheduleManagement(User user);
bool validateClassID(string class_id);

int main()
{
	startProgram();
	system("pause");
	return 0;
}

void startProgram()
{
	//Create the database first
	DbManager Database;
	LoginController lControl;
	string user, pass;
	bool end;
	do
	{
		int choice;
		cout << "1: Login" << endl;
		cout << "2: Create Account " << endl;
		cout << "Pick your option: ";
		cin >> choice;


		switch(choice)
		{
		case 1:
			cout << "Username: " << endl;
			cin >> user;

			cout << "Password: " << endl;
			cin >> pass;

			//Attempts to log in
			lControl.login(user, pass, Database);
			cout << endl << endl << "Welcome " << user << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			afterlogin(Database.getUser(user));
			end = true;
			break;

		case 2:
			Database.createUser(); //This will create and ask and validate all the create user items
			break;

		default:
			cout << "Invalid input please try again" << endl;
			break;
		}



	}while(!end);
}


void afterlogin(User user)
{
	int choice;
	char exit;
	bool flag = false, flag2 = false;
	while(!flag)
	{
		cout << "1: Account Management " << endl;
		cout << "2: Schedule Management " << endl;
		cout << "3: Retrieve Class info " << endl;
		cout << "4: Upload Syllabus " << endl;
		cout << "5: Log out " << endl;
		cout << "Please enter your choice: " << endl;

		cin >> choice;

		switch(choice)
		{
		case 1:
			Manageaccount(user);
			break;
		case 2:
			ScheduleManagement(user);
			break;

		case 3:
		{
			string classID;
			DbManager Temp;
			cout << "What class would you like to see... Please enter in the Class ID: ";
			cin >> classID;
			int spot; //Holds the spot where the class info is found
			for(int i = 0; i < Temp.classesCount; i ++)
			{
				if(Temp.diffClasses[i].getclassID() == classID )
					spot = i;
			}

			//Check if found, Class is found if spot != 0;
			if(spot != 0)
			{
				cout << endl << endl << endl << endl << endl;
				cout << "ClassID: " << Temp.diffClasses[spot].getclassID() << endl;
				cout << "CourseID: " << Temp.diffClasses[spot].getcourseID() << endl;
				cout << "Course Name: " << Temp.diffClasses[spot].getcourseName() << endl;
			}
			else
			{
				cout << "There was no class under that ClassID... Please Try Again" << endl;
			}

			break;
		}
		case 4:
		{
			cout << "coming soon" << endl;
			break;
		}
		case 5:
		{
			while(!flag2)
			{
				cout << "Are you sure you want to log out (y/n)?";
				cin >> exit;

				//Exits program if 'y' is entered
				if(exit == 'y' || exit == 'Y')
				{
					flag = true;
					flag2 = true;
				}
				else if(exit == 'n' || exit == 'N')
				{
					flag = false;
					flag2 = true;
				}
				else
				{
					cout << "Invalid input Please try again... " << endl;
					flag2 = false;
				}
			}
			break;
		}
		default:
			cout << "Invalid menu input... Please Try again... " << endl;
			break;

		}
	}
}


void Manageaccount(User user)
{
	bool flag = false;
	int x;
	cout << endl << endl << endl << endl;
	while(!flag)
	{
		cout << "Would you like to...." << endl;
		cout << "1: Change Password" << endl;
		cout << "2: Delete Account" << endl;

		cin >> x;

		switch(x)
		{
		case 1:
		{
			string pwd;
			cout << "Please enter your new password: ";
			cin >> pwd;
			user.setPassword(pwd);
			cout << "Password has been successfully changed..." << endl;
			//Start to delete password
			string deleteline;
			string line;

			ifstream inFile;
			inFile.open("users.txt");
			ofstream temp;
			temp.open("temp.txt");

			while (getline(inFile,line))
			{
				if (line.substr(0, line.find(' ')) != user.getID())
					temp << line << endl;
			}
			temp << user.getID() << " " << pwd << endl;
			temp.close();
			inFile.close();
			remove("users.txt");
			rename("temp.txt","users.txt");
			flag = true;
			break;
		}
		case 2:
		{	string userID;
		cout << "Please enter the userID of the Account you would like to delete: ";
		cin >> userID;

		//Start to delete
		string deleteline;
		string line;

		ifstream inFile;
		inFile.open("users.txt");
		ofstream temp;
		temp.open("temp.txt");

		while (getline(inFile,line))
		{
			if (line.substr(0, line.find(' ')) != userID)
				temp << line << endl;
		}

		temp.close();
		inFile.close();
		remove("users.txt");
		rename("temp.txt","users.txt");
		cout << "The Account has been removed... Goodbye...." << endl;
		flag = true;
		break;
		}
		default:
			cout << "Invalid menu input... Please try again..." << endl;
			break;

		}
	}
}

void ScheduleManagement(User user)
{
	int choice;
	string classID;
	bool flag = false;
	DbManager Dbtemp;
	while(!flag)
	{
		cout << "1: Show current classes " << endl;
		cout << "2: Add Class " << endl;
		cout << "3: Delete Class " << endl;
		cout << "Please enter your choice: " << endl;
		cin >> choice;

		switch(choice)
		{
		case 1:
			cout << "coming soon " << endl;
			break;
		case 2:
			/*
			cout << "Enter class ID: ";
			cin >> classID;
			if(validateClassID(classID))
			{
				for(int i = 0; i < 50; i++)
					if (Dbtemp.diffClasses[i].getclassID == classID)
					{
						user.classes[classCount] = Dbtemp.diffClasses[i];
						break;
					}
			}
			user.classCount++;
			*/
			break;
		case 3:
			break;
		default:
			cout << "Invalid menu input... Please Try again... " << endl;
			break;
		}
	}
}
bool validateClassID(string class_id)
{
    ifstream inFile;
    inFile.open("classes_database.txt");

    if(!inFile)
    {
        cout << "Could not open user text file" << endl;
    }
    else
    {
        string line;

        while (getline(inFile, line))
        {
            if (line.substr(0, line.find(':')) == class_id)
            {
                inFile.close();
                return true;
            }
        }
    }
    inFile.close();
    return false;
}
