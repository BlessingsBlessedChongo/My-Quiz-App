#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

//structure for quiz questions
struct Question {
	string query;
	string options[4];
	int correctOption;
};
//Function to swap two Question structures 
void swap(Question& a, Question& b) {
	Question temp = a;
	a = b;
	b = temp;
}
//custom shuffle function
void shuffle(Question questions[], int numQuestions) {
	srand(time(0));
	for (int i = numQuestions - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(questions[i], questions[j]);
	}
}
//function to display quiz questions and check answers
void conductQuiz(Question questions[], int numQuestions) {
	int score = 0;
	for (int i = 0; i < numQuestions; i++) {
		cout << "\nQuestion " << i + 1 << ":" << questions[i].query << endl;
		for (int j = 0; j < 4; j++) {
			cout << j + 1 << "." << questions[i].options[j] << endl;
		}
		int answer;
		cout << "Enter your answer(1-4):";
		cin >> answer;
		if (answer == questions[i].correctOption) {
			cout << "Correct!" << endl;
			score++;
		}
		else {
			cout << "Incorrect. The correct answer is " << questions[i].correctOption << "." << questions[i].options[questions[i].correctOption - 1] << endl;
		}
	}cout << "\nQuiz finished. Your final score is " << score << "/" << numQuestions << endl;

}
//Function to add new questions tothe quiz
void addQuestion(Question questions[], int& numQuestions) {
	cout << "Enter new question: ";
	cin.ignore();
	getline(cin, questions[numQuestions].query);
	cout << "Enter option 1: ";
	getline(cin, questions[numQuestions].options[0]);
	cout << "Enter option 2: ";
	getline(cin, questions[numQuestions].options[1]);
	cout << "Enter option 3: ";
	getline(cin, questions[numQuestions].options[2]);
	cout << "Enter option 4: ";
	getline(cin, questions[numQuestions].options[3]);
	cout << "Enter correct option (1-4): ";
	cin >> questions[numQuestions].correctOption;
	numQuestions++;
}
//Function to save questions to file
void saveQuestions(Question questions[], int numQuestions) {
	ofstream outFile("quiz_questions.txt");
	if (outFile.is_open()) {
		for (int i = 0; i < numQuestions; i++) {
			outFile << questions[i].query << endl;
			for (int j = 0; j < 4; j++) {
				outFile << questions[i].options[j] << endl;
			}
			outFile << questions[i].correctOption << endl;
		}
		outFile.close();
		cout << "Questions saved to quiz_questions.txt" << endl;
	}
}
//function to load questions from file#
void loadQuestions(Question questions[], int& numQuestions) {
	ifstream inFile("quiz_questions.txt");
	if (inFile.is_open()) {
		numQuestions = 0;
		while (!inFile.eof()) {
			getline(inFile, questions[numQuestions].query);
			for (int j = 0; j < 4; j++) {
				getline(inFile, questions[numQuestions].options[j]);
			}
			inFile >> questions[numQuestions].correctOption;
			inFile.ignore(); //ignore newline character
			numQuestions++;
		}
		inFile.close();
		cout << "Questions loaded from quiz_questions.txt" << endl;
	}
	else {
		cout << "Unable to load questions" << endl;
	}
}
//Function to display menu
void displayMenu() {
	cout << "\nQuiz Program Menu" << endl;
	cout << "----------------------" << endl;
	cout << "1. Take Quiz" << endl;
	cout << "2. Add Question" << endl;
	cout << "3.Save Questions" << endl;
	cout << "4. Load Questions" << endl;
	cout << "5.Exit" << endl;
	cout << "Enter your choice: ";
}
int main() {
	const int MAX_QUESTIONS = 100;
	Question questions[MAX_QUESTIONS];
	int numQuestions = 5;

	//initialize questions
	questions[0] = { "What is the capital of France?",{"Berlin","Paris","London","Rome"},2 };
	questions[1] = { "Which planet is largest in our solar system?",{"Earth","Saturn","Jupiter","Uranus"},3 };
	questions[2] = { "Who painted the Mona Lisa?",{"Leonardo da Vinci","Michelangelo","Raphael","Caravaggio"},1 };
	questions[3] = { "What is the chemical symbol for gold?",{"Ag","Au","Hg","Pb"},2 };
	questions[4] = { "Which language is spoken in china?",{"Spanish","Mandarin","English","French"},2 };

	int choice;
	do {
		displayMenu();
		cin >> choice;
		switch (choice) {
		case 1:
			shuffle(questions, numQuestions);
			conductQuiz(questions,numQuestions);
			break;
		case 2:
			addQuestion(questions, numQuestions);
			break;
		case 3:
			saveQuestions(questions, numQuestions);
			break;
		case 4:
			loadQuestions(questions, numQuestions);
			break;
		case 5:
			cout << "Exiting program. Goodbye!" << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 5);
	system("PAUSE");
	return 0;
}