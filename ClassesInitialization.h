#ifndef CLASSESINITIALIZATION_H_
#define CLASSESINITIALIZATION_H_

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Schedule
{
private:
	string classID;
	string courseID;
	string courseName;


public:

	//Accessor and mutator functions
	void setclassID(string ID);
	string getclassID();
	void setcourseID(string ID);
	string getcourseID();
	void setcourseName(string name);
	string getcourseName();

	void addClass(string classID);
	void deleteClass(string classID);
};


class User
{
private:
	//Basic User information
	string uid;
	string pwd;
	//Creates and holds the classes and the schedules
	string classids[5];
	Schedule classes[5];

public:
	int classCount = 0;
	int UserCount;
	void setID(string id);
	void setPassword(string pass);
	string getID();
	string getPwd();
	bool validateID(string ID, int count); //Checks if the Username is valid
	bool validatePass(string pass); //Checks if the Password is valid
	bool authenticate(string pass);

	void setGoogleAccount(); // ???
	void createSchedule(string scheduleID);
	void getSchedule(string scheduleID);
};

class GoogleAccount
{
private:
	string username;
	string pass;

public:
	GoogleAccount(string user, string pwd){

		username = user;
		pass = pwd;
	}
	string setUsername();
	string setPass();
	string getUsername();
	string getpass();
};
class Classes
{

private:
	string professors;
	string books;
	string schedule;
	string importantDates;

public:
	void getData(int, string, string, string);
	void setSyllabus(string);
};

class Book
{
private:
	string name;
	string isbn;

public:
	void getPrices();
};

class Professor
{
private:
	string name;
	string officeHours;
	string roomNumber;

public:
	void getRating();
};

class AccountController
{
public:
	User createAccount(string userID, string pass, GoogleAccount g); //Complete for iteration 3
	User manageAccount(string userID);
	User deleteAccount(string userID);
	User checkClass(string classID);
	User retrieveClass(string classID);
};

class AccountManagementGUI
{
public:
	void display(string message);
};

class AccountGUI
{
public:
	void display(string message);
};


class LoginGUI
{
public:
	void display(string message);
};



class ScheduleController
{
public:
	void createSchedule(User userID, string scheduleID);
	void addClass(User userID, string scheduleID, string classID);
	void deleteClass(User userID, string scheduleID, string classID);
};

class ScheduleGUI
{
public:
	void display(string message);
};


class DbManager
{
private:
	string classid;
	string GAccount;
	string scheduleid;

	//Array to hold all the different users


public:
	Schedule diffClasses[50];  //Array to hold all the different classes
	int userCount; //Holds the amount of users created already
	int classesCount;
	User users[50];
	//Constructor
	DbManager() //Initializes all the users when the program starts from the users text file
	{

		userCount = 0;
		classesCount = 0;
		ifstream inFile;
		inFile.open("users.txt");

		//Fills up the Current users
		if(!inFile)
		{
			cout << "Could not open user text file" << endl;
		}
		else
		{
			int i = 0;
			while(!inFile.eof())
			{
				string line;


				//reads username from file and initializes the username in database
				getline(inFile, line, ' ');
				users[i].setID(line);

				//reads Password from file and initializes the password in database
				getline(inFile, line);
				users[i].setPassword(line);

				//Adds 1 to the user count for each iteration
				userCount += 1;
				++i;

			}
		}
		inFile.close();


		//Fills up the Current Classes
		inFile.open("classes_database.txt");
		if(!inFile)
		{
			cout << "Could not open the classes text file" << endl;
		}
		else
		{
			int j = 0;
			while(!inFile.eof())
			{
				string line;

				//reads classID from file and initializes the classID in database
				getline(inFile, line, ':');
				diffClasses[j].setclassID(line);

				//reads courseId from file and initializes the courseID in database
				getline(inFile, line, ':');
				diffClasses[j].setcourseID(line);

				//reads courseName from file and initializes the courseName in database
				getline(inFile, line, ':');
				diffClasses[j].setcourseName(line);

				//Adds 1 to the classes count for each iteration
				classesCount += 1;
				++j;

			}
		}

		inFile.close();
	}


	User getUser(string userID);
	User getClass(string classID);
	User addClass(string classID);
	User deleteUser(string userID);
	User createUser();
};

class UploadSyllabusController
{
private:
	string importantDates;

public:
	void uploadSyllabus(ifstream File);  // ???
};

class UploadSyllabusGUI
{
public:
	void display(string message);
};

class PurchaseBookController
{
public:
	void purchaseBook(int isbn);
};

class PurchaseBookGUI
{
	void display(string message);
};

class ExportController
{
	void exportToGoogle(Schedule);
};


class ExportGUI
{
	void display(string message);
};

class LoginController
{
public:
	User login(string userId, string pass, DbManager database); // "get user"
};



#endif /* CLASSESINITIALIZATION_H_ */
