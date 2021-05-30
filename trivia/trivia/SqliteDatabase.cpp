#include "SqliteDatabase.h"

int usersCallback(void* data, int argc, char** argv, char** azColName);
int statsCallback(void* data, int argc, char** argv, char** azColName);
int questionsCallback(void* data, int argc, char** argv, char** azColName);

//Constructor
SqliteDatabase::SqliteDatabase()
{
	string err = "no error";
	bool doesFileExist = !_access(DB_FILE_NAME, 0);
	int res = sqlite3_open(DB_FILE_NAME, &_db);
	if (res != SQLITE_OK)
	{
		_db = nullptr;
		err = "Failed to open DB. Error code: " + to_string(res) + ENDL;
		throw(exception(err.c_str()));
	}

	if (!doesFileExist)
	{
		err = "Error, DB file didn't exist. Created empty one\n\n";
		throw(exception(err.c_str()));
	}
}

//Destructor
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
	_db = nullptr;
}

/*
Adds a new user to the sqlite database
Input: username, password, email
Output: none
*/
void SqliteDatabase::addNewUser(string username, string password, string email)
{
	char** errMsg = nullptr;
	int res;

	string statement = "INSERT INTO users VALUES (\"" +username+ "\", \"" +password+ "\", \"" +email+ "\");";
	res = sqlite3_exec(_db, statement.c_str(), nullptr, nullptr, errMsg);
	if (res == SQLITE_CONSTRAINT)
	{
		cerr << "username already taken or something is null" << endl;
	}
	else
		checkResult(res, "insert user");
}

/*
Function checks if user exists in the database
Input: username
Output: doesExist
*/
bool SqliteDatabase::doesUserExist(string username)
{
	char** errMsg = nullptr;
	int res;
	list<User> users;

	//Get the user
	string statement = "SELECT * FROM users WHERE username=\"" + username + "\";";
	res = sqlite3_exec(_db, statement.c_str(), usersCallback, &users, errMsg);
	checkResult(res, "check user's existance");

	if (users.empty())
		return false;

	users.clear();
	return true;
}

/*
Function checks if the password match this username's password
Input: username, password
Output: doesMatch
*/
bool SqliteDatabase::doesPasswordMatch(string username, string password)
{
	char** errMsg = nullptr;
	int res;
	list<User> users;
	bool doesMatch = false;

	//Get the user
	string statement = "SELECT * FROM users WHERE username=\"" + username + "\";";
	res = sqlite3_exec(_db, statement.c_str(), usersCallback, &users, errMsg);
	checkResult(res, "check if password matches");

	if (!users.empty())
	{
		doesMatch = users.front().password == password; //becomes true if passwords match
		users.clear();
	}

	return doesMatch;
}

//Returns the number of questions
list<Question> SqliteDatabase::getQuestions(int numOfQuestions)
{
	char** errMsg = nullptr;
	int res;
	list<Question> questions;
	list<Question> randomizedQuestions;
	int questionsCount = 0;
	int randomNum;

	//Get the user's statistics
	string statement = "SELECT * FROM questions;";
	res = sqlite3_exec(_db, statement.c_str(), statsCallback, &questions, errMsg);
	checkResult(res, "getQuestions");

	//Make sure to not go over the max number of questions
	if (numOfQuestions > MAX_QUESTIONS)
		numOfQuestions = MAX_QUESTIONS;

	//Make helper array and initialize its values to 0
	int* selectedQuestions = new int[MAX_QUESTIONS];
	for (int i = 0; i < MAX_QUESTIONS; i++)
		selectedQuestions[i] = 0;
	
	if (!questions.empty())
	{
		//Randomize questions
		while (questionsCount < numOfQuestions)
		{
			randomNum = rand() % MAX_QUESTIONS + 1; //Choose random question
			auto question = questions.begin();
			advance(question, randomNum-1);

			//If the question hasn't been selected yet then select it
			if (selectedQuestions[randomNum-1] == 0)
			{
				selectedQuestions[randomNum-1] = 1;
				randomizedQuestions.push_back(*question);
			}
		}
	}
	else
		cerr << "questions are somehow empty" << endl;

	return randomizedQuestions;
}

//returns the average time per answer of a user
float SqliteDatabase::getPlayerAverageAnswerTime(string username)
{
	Stats* stats = getStatsOfUser(username);

	if (stats != nullptr)
	{
		float avrgTime = stats->totalAnswerTime / stats->totalAnswers;
		delete stats;

		return avrgTime;
	}

	return USER_NOT_FOUND;
}

//Returns number of correct answers of user
int SqliteDatabase::getNumOfCorrectAnswers(string username)
{
	Stats* stats = getStatsOfUser(username);

	if (stats != nullptr)
	{
		int rightAnswers = stats->rightAnswers;
		delete stats;

		return rightAnswers;
	}

	return USER_NOT_FOUND;
}

//Returns number of total answers of user
int SqliteDatabase::getNumOfTotalAnswers(string username)
{
	Stats* stats = getStatsOfUser(username);

	if (stats != nullptr)
	{
		int totalAnswers = stats->totalAnswers;
		delete stats;

		return totalAnswers;
	}

	return USER_NOT_FOUND;
}

//Returns the number of games the user played
int SqliteDatabase::getNumOfPlayerGames(string username)
{
	Stats* stats = getStatsOfUser(username);

	if (stats != nullptr)
	{
		int gamesPlayed = stats->gamesPlayed;
		delete stats;

		return gamesPlayed;
	}

	return USER_NOT_FOUND;
}

///////////////////////////////////////////////////////////////////////
////////////////////////// Helper functions ///////////////////////////
/////////////////////////////////////////////////////////////////////// 

//Function checks the result after executing an sql statement
void SqliteDatabase::checkResult(int res, string subject)
{
	if (res != SQLITE_OK)
	{
		if (subject == "" || nullptr)
			subject = "something";
		cerr << "Error at \"" << subject << "\", err code: " << res << endl;
	}
}

Stats* SqliteDatabase::getStatsOfUser(string username)
{
	char** errMsg = nullptr;
	int res;
	list<Stats> stats;

	//Get the user's statistics
	string statement = "SELECT * FROM statistics WHERE username=\"" + username + "\";";
	res = sqlite3_exec(_db, statement.c_str(), statsCallback, &stats, errMsg);
	checkResult(res, "get stats of user");

	if (!stats.empty())
	{
		return &stats.front();
	}

	return nullptr;
}

//callback function for users
int usersCallback(void* data, int argc, char** argv, char** azColName)
{
	User user;
	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "username") {
			user.username = argv[i];
		}
		else if (string(azColName[i]) == "password") {
			user.password = argv[i];
		}
		else if (string(azColName[i]) == "email") {
			user.email = argv[i];
		}
	}
	((list<User>*)data)->push_back(user);
	return 0;
}

//Callback for stats
int statsCallback(void* data, int argc, char** argv, char** azColName)
{
	Stats stat { "", 0, 0, 0, 0, 0 };
	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "username") {
			stat.username = argv[i];
		}
		else if (string(azColName[i]) == "gamesPlayed") {
			stat.gamesPlayed = stoi(argv[i]);
		}
		else if (string(azColName[i]) == "totalAnswers") {
			stat.totalAnswers = stoi(argv[i]);
		}
		else if (string(azColName[i]) == "rightAnswers") {
			stat.rightAnswers = stoi(argv[i]);
		}
		else if (string(azColName[i]) == "totalAnswerTime") {
			stat.totalAnswerTime = stof(argv[i]);
		}
		else if (string(azColName[i]) == "bestScore") {
			stat.bestScore = stoi(argv[i]);
		}
	}
	((list<Stats>*)data)->push_back(stat);
	return 0;
}

//Callback for questions
int questionsCallback(void* data, int argc, char** argv, char** azColName)
{
	Question question { 0, "", "", "", "", "" };
	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "id") {
			question.id = stoi(argv[i]);
		}
		else if (string(azColName[i]) == "question") {
			question.question = argv[i];
		}
		else if (string(azColName[i]) == "rightAnswer") {
			question.rightAnswer = argv[i];
		}
		else if (string(azColName[i]) == "WrongAnswer1") {
			question.wrongAnswers[0] = argv[i];
		}
		else if (string(azColName[i]) == "WrongAnswer2") {
			question.wrongAnswers[1] = argv[i];
		}
		else if (string(azColName[i]) == "WrongAnswer3") {
			question.wrongAnswers[2] = argv[i];
		}
	}
	((list<Question>*)data)->push_back(question);
	return 0;
}