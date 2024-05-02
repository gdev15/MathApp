#include <iostream>
#include <random> //Random number generation
#include <cstdlib> //added for clearing console text

using namespace std;


class Question {
	public:
		int firstValue;
		int secondValue;
		char operation;

		Question() {}

		Question(int firstValue, int secondValue) :
			firstValue(firstValue), secondValue(secondValue) {}

		void print(char operation) {
			cout << firstValue << " " << operation << " ";
			cout << secondValue << " = ";
		}

		int addValues() {
			return firstValue + secondValue;
		}

		int multiplyValues() {
			return firstValue * secondValue;
		}

};

int generateProblem(char gameMode) {


	random_device rd; //Seed for the random number
	mt19937 gen(rd()); // Generator engine
	uniform_int_distribution<> dis(0, 10); // Define the range [0, 9]

	int firstValue, secondValue;

	bool isFirstSelected = false;
	bool isSecondSelected = false;

	//Generates 2 random numbers
	for (int i = 0; i < 2; i++) {
		int random_num = dis(gen);

		if (!isFirstSelected) {
			firstValue = random_num;
			isFirstSelected = true;
		}

		if (!isSecondSelected && isFirstSelected) {
			secondValue = random_num;
		}
	}

	Question problem = Question(firstValue, secondValue);

	if (gameMode == '+') {
		problem.print(gameMode);
		 return problem.addValues();
	}
	if (gameMode == 'X') {
		problem.print(gameMode);
		return problem.multiplyValues();
	}
}

//Function for menu screen
void welcomeScreen() {
		cout << R"(

	   _____          __  .__         _____                 
	  /     \ _____ _/  |_|  |__     /  _  \ ______ ______  
	 /  \ /  \\__  \\   __\  |  \   /  /_\  \\____ \\____ \ 
	/    Y    \/ __ \|  | |   Y  \ /    |    \  |_> >  |_> >
	\____|__  (____  /__| |___|  / \____|__  /   __/|   __/ 
			\/     \/          \/          \/|__|   |__|    


	)" << '\n';
}

int main() {

	bool isPlaying = true;
	bool isGameModeSelected = false;

	bool isAddition = false;
	bool isMultiplication = false;

	int usersChoice;

	//Game Loop
	while (isPlaying) {
		//Main Menu
		//Checks to see if the user has selected a game mode to play
		if (!isGameModeSelected) {
			welcomeScreen();

			cout << "Select from the following options: " << endl;
			cout << "1) Practice Addition" << endl;
			cout << "2) Practice Multiplication" << endl;
			cout << "3) Exit/Close App" << endl;

			//Wait for users choice
			if (!(cin >> usersChoice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore wrong input
				system("cls");
				cout << "Invalid input. Please enter a number." << endl;

				continue; //Skip the rest of the loop and prompt again
			}
			cout << endl;
			//Switch statement to evaluate the users input
			switch (usersChoice) {

			case 1: 
				isAddition = true;
				isGameModeSelected = true;
				break;

			case 2:
				isMultiplication = true;
				isGameModeSelected = true;
				break;

			//Closes app
			case 3: cout << "Have a nice day!";
				isPlaying = false;
				continue;

			default: cout << "Invalid Choice. Please make a valid selection.";
				break;

			}
		}

		//Data types used to store the game mode value
		char gameMode;
		string problemType;
		if (isAddition) {
			problemType = "Addition";
			gameMode = '+';
		}
		if (isMultiplication) {
			problemType = "Multiplication";
			gameMode = 'X';
		}
		
		
		cout << endl << "1) Generate " << problemType << " Problem " << endl;
		cout << "2) Back to the Main Menu" << endl;
		cout << "3) Exit/Close App" << endl;

		//Wait for users choice
		if (!(cin >> usersChoice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore wrong input
			cout << "Invalid input. Please enter a valid option." << endl;
			continue; //Skip the rest of the loop and prompt again
		}
		cout << endl;

		//Clears console text
		system("cls");

		switch (usersChoice) {
			//Variables to store the users input and the correct answer for grading 
			int usersAnswer;
			int correctAnswer;
			//Case for the user to generate a problem to answer
			case 1: 
				cout << "Please type in the correct answer. " << endl;
				correctAnswer = generateProblem(gameMode);

				//Wait for a valid input if it's not an integer this loop repeats
				//Runs until it encounters a break statement
				while(true) {
					cin >> usersAnswer;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input, you must enter an integer." << endl;
					}
					else {
						break;
					}
				}
			
				if (usersAnswer == correctAnswer) {
					cout << "Correct!" << endl;
				}
				else
					cout << "The correct answer is: " << correctAnswer << endl;
				break;

				//Reset bool values back to the initial state
			case 2: 
					isAddition = false;
					isMultiplication = false;
					isGameModeSelected = false;
				break;
				//Ends application
			case 3: 
				cout << "Have a nice day!";
				isPlaying = false;
				continue;
				//Prompts the user to make a valid selection
			default: cout << "Invalid selection. Please select a valid option. ";
				break;
		}

	}

	return 0;
}
