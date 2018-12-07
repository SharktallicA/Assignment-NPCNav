#pragma once
/*
	C++ general utility functions and helper classes
	Khalid Ali 2018
	http://khalidali.co.uk/
*/

#include <iostream>
#include <sstream>
#include <random>
#include <windows.h>
#include <conio.h>

using namespace std;

//Enumeration of possible foreground and background colours that the C++ console can be set to
enum Colour
{
	BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GREY, LIGHT_BLUE,
	LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
};

//Encapulation of two Colour enumerations for data transportation
class cvec
{
public:
	Colour fore, back;

	cvec(void) {}
	cvec(Colour nFore, Colour nBack) { fore = nFore; back = nBack; }

	bool operator==(cvec& o) const
	{
		if ((fore == o.fore) && (back == o.back)) return true;
		else return false;
	}
	bool operator!=(cvec& o) const
	{
		if ((fore != o.fore) || (back != o.back)) return true;
		else return false;
	}
};

//2-dimensional vector 
class vec2
{
public:
	int x, y;

	vec2(void) {}
	vec2(int nX, int nY) { x = nX; y = nY; }

	bool operator==(vec2& o) const
	{
		if ((x == o.x) && (y == o.y)) return true;
		else return false;
	}
	bool operator!=(vec2& o) const
	{
		if ((x != o.x) || (y != o.y)) return true;
		else return false;
	}
};

//3-dimensional vector 
class vec3
{
public:
	int x, y, z;

	vec3(void) {}
	vec3(int nX, int nY, int nZ) { x = nX; y = nY; z = nZ; }
	vec3(const vec2& o) : x(o.x), y(o.y), z(0) {}

	bool operator==(vec3& o) const
	{
		if ((x == o.x) && (y == o.y) && (z == o.z)) return true;
		else return false;
	}
	bool operator!=(vec3& o) const
	{
		if ((x != o.x) || (y != o.y) || (z == o.z)) return true;
		else return false;
	}
};

//Class of static methods that provide utility functions for C++ console applications
class Utility
{
private:
	Utility() {}; //prevents class from being constructed

public:
	//Requests yes (true)/no (false) boolean input from the user
	static bool getYesNo(void)
	{
		string input = "";
		bool isYes = true;

		cin >> input;
		while (input != "Y" && input != "Yes" && input != "YES" && input != "yes" && input != "N" && input != "No" && input != "NO" && input != "no" && input != "y" && input != "n")
		{
			cout << "ERROR: you can only enter 'Yes', 'No' or a similar variation.\nTry again: ";
			cin >> input;
		}

		if (input == "Y" || input == "Yes" || input == "YES" || input == "yes" || input == "y")
			isYes = true;
		else if (input == "N" || input == "No" || input == "NO" || input == "no" || input == "n")
			isYes = false;
		return isYes;
	}
	//Requests yes (true)/no (false) boolean input from the user with a given input notice message
	static bool getYesNo(string message)
	{
		string input = "";
		bool isYes = true;

		cout << message;
		cin >> input;
		cin.ignore();
		while (input != "Y" && input != "Yes" && input != "YES" && input != "yes" && input != "N" && input != "No" && input != "NO" && input != "no" && input != "y" && input != "n")
		{
			cout << "ERROR: you can only enter 'Yes', 'No' or a similar variation.\nTry again: ";
			cin >> input;
		}

		if (input == "Y" || input == "Yes" || input == "YES" || input == "yes" || input == "y")
			isYes = true;
		else if (input == "N" || input == "No" || input == "NO" || input == "no" || input == "n")
			isYes = false;
		return isYes;
	}

	//Safely requests any string input from the user
	static string getString(void)
	{
		string input = "";
		getline(cin, input);
		return input;
	}
	//Safely requests any string input from the user with a given input notice message
	static string getString(string message)
	{
		cout << message;
		string input = "";
		getline(cin, input);
		return input;
	}

	//Safely requests integer input from the user
	static int getInteger(void)
	{
		string input = "";
		int parseResult = -1024;

		cin >> input;
		cin.ignore();
		stringstream strStream(input);
		strStream >> parseResult;
		return parseResult;
	}
	//Safely requests integer input from the user with a given input notice message
	static int getInteger(string message, int min, int max)
	{
		string input = "";
		int parseResult = -1024;

		cout << message;
		cin >> input;
		cin.ignore();
		stringstream strStream(input);
		strStream >> parseResult;
		while (parseResult < min || parseResult > max)
		{
			cout << "ERROR: you can only enter a whole number between " << min << " and " << max << ".\nTry again: ";
			cin >> input;
			cin.ignore();
			stringstream strStream(input);
			strStream >> parseResult;
		}
		return parseResult;
	}

	//Generates a random integer using 32-Bit Mersenne Twister 19937
	static int generateNumber32(int min, int max)
	{
		int intResult;
		random_device randGenerator;
		mt19937 mersenne(randGenerator());
		uniform_int_distribution<int> distInt(min, max);
		intResult = distInt(mersenne);
		return intResult;
	}
	//Generates a random integer using 64-Bit Mersenne Twister 19937
	static int generateNumber64(int min, int max)
	{
		int intResult;
		random_device randGenerator;
		mt19937_64 mersenne(randGenerator());
		uniform_int_distribution<int> distInt(min, max);
		intResult = distInt(mersenne);
		return intResult;
	}
	//Generates a random double using 32-Bit Mersenne Twister 19937
	static double generateNumber32(double min, double max)
	{
		double dblResult;
		random_device randGenerator;
		mt19937 mersenne(randGenerator());
		uniform_real_distribution<double> distInt(min, max);
		dblResult = distInt(mersenne);
		return dblResult;
	}
	//Generates a random double using 64-Bit Mersenne Twister 19937
	static double generateNumber64(double min, double max)
	{
		double dblResult;
		random_device randGenerator;
		mt19937_64 mersenne(randGenerator());
		uniform_real_distribution<double> distInt(min, max);
		dblResult = distInt(mersenne);
		return dblResult;
	}

	//Clears the screen
	static void clearScreen(void)
	{
		system("cls");
	}

	//Waits for user input - good replacement for system("pause")
	static char pause(string message = "Press any key to continue...")
	{
		cout << message;
		char in = _getch();
		cout << endl;
		return in;
	}

	//Sets the C++ console window's title
	static void setWindowTitle(string title)
	{
		SetConsoleTitle(title.c_str());
	}

	//Sets the C++ console window's size
	static void setWindowSize(unsigned int width, unsigned int height)
	{
		HWND console = GetConsoleWindow();
		RECT rectWindow;

		GetWindowRect(console, &rectWindow);
		MoveWindow(console, rectWindow.left, rectWindow.top, width, height, TRUE);
	}

	//Resets the C++ console window's colours to default
	static void resetColour(void)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int colour = BLACK * 16 + DEFAULT;

		SetConsoleTextAttribute(handle, colour);
	}

	//Sets the C++ console window's colours | Possible: BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
	static void setColour(Colour fore = WHITE, Colour back = BLACK)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int colour = back * 16 + fore;

		SetConsoleTextAttribute(handle, colour);
	}
	//Sets the C++ console window's colours | Possible: BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE
	static void setColour(cvec colours = cvec(WHITE, BLACK))
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int colour = colours.back * 16 + colours.fore;

		SetConsoleTextAttribute(handle, colour);
	}

	//Moves the C++ console window's cursor
	static void moveCursor(vec2 nPos)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD point = { nPos.x, nPos.y };
		SetConsoleCursorPosition(handle, point);
	}
	//Moves the C++ console window's cursor
	static void moveCursor(SHORT x, SHORT y)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD point = { x, y };
		SetConsoleCursorPosition(handle, point);
	}

	//Makes the program sleep
	static void sleep(int mSecs)
	{
		Sleep(mSecs);
	}
};