// Aneesh Akella
// ana0039
// project4_Akella_ana0039.cpp
//  use g++ to compile ./a.out to run
// No help used

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

int totalPoints;

struct triviaNode {

    string question;
    string answer;
    int points;
    triviaNode* next;

};

class linkedList {

public:
    triviaNode* left, * right;
    triviaNode* index;
    int listSize;
    linkedList() {

        triviaNode* t1 = new triviaNode();
        triviaNode* t2 = new triviaNode();
        triviaNode* t3 = new triviaNode();
        t1->question = "How long was the shortest war on record? (Hint: how many minutes)";
        t1->answer = "38";
        t1->points = 100;
        t2->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
        t2->answer = "Bank of Italy";
        t2->points = 50;
        t3->question = " What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
        t3->answer = "Wii Sports";
        t3->points = 20;
        t1->next = t2;
        t2->next = t3;
        t3->next = NULL;
        left = t1;
        right = t3;
        listSize = 3;
        index = NULL;

    }

    void addNode(string questionIn, string answerIn, int pointsIn) {
        triviaNode* temp = new triviaNode();
        temp->question = questionIn;
        temp->answer = answerIn;
        temp->points = pointsIn;
        right->next = temp;
        right = temp;
        listSize++;

    }

    triviaNode* getNext() {
        if (index == NULL) {
            index = left;
        }
        else {
            index = index->next;
        }
        return index;
    }

};

int askQuestion(linkedList& inputList, int numofQuestions);
void testAskQuestion(void);


//#define UNIT_TESTING 

#ifdef UNIT_TESTING

int main() {
    testAskQuestion();
}

#else

int main() {
    int pointValue;
    string questionInput;
    string answerInput;
    string next;
    linkedList mainList;
    cout << "\n*** Welcome to Aneesh's trivia quiz game ***\n";
    bool finished = false;
    while (!finished) {
        cout << "Enter a question: ";
        getline(cin, questionInput);
        cout << "Enter an answer: ";
        getline(cin, answerInput);
        cout << "Enter award points: ";
        cin >> pointValue;
        mainList.addNode(questionInput, answerInput, pointValue);
        cout << "Continue? (Yes/No): ";
        cin >> next;
        cin.ignore();
        if (next == "No" || next == "no") {
            finished = true;
        }
    }
    for (int i = 0; i < mainList.listSize; i++) {
        askQuestion(mainList, 1);
    }
    cout << "\n\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
}
#endif

int askQuestion(linkedList& questionList, int numberOfQuestions) {
    string answerInput;
    string correctAnswer;
    if (numberOfQuestions < 1) {
        cout << "\nWarning: The number of trivia to be asked must equal or be larger than 1.\n";
        return 0;
    }

    if (numberOfQuestions > questionList.listSize) {
        cout << "\nWarning: There are only " << questionList.listSize << " trivia in the list.\n";
        return 0;
    }

    for (int i = 0; i < numberOfQuestions; i++) {
        triviaNode* node = questionList.getNext();
        cout << "\nQuestion: " << node->question;
        cout << "\nAnswer: ";
        getline(cin, answerInput);
        correctAnswer = node->answer;

        if (answerInput != correctAnswer) {
            cout << "Your answer is wrong. The correct answer is " << node->answer << endl;
        }

        else {
            cout << "Your answer is correct! You will receive " << node->points << " points." << endl;
            totalPoints += node->points;
        }
        cout << "Your total points: " << totalPoints << endl;
    }
    return 1;
}


void testAskQuestion(void) {

    linkedList case1;
    linkedList case2;
    linkedList case3;
    linkedList case4;
    cout << "*** This is a debug version ***";
    cout << "\nUnit Test Case 1: Ask no question. The program should give a warning message.";
    askQuestion(case1, 0);
    cout << "\nCase 1 Passed\n";
    cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.";
    askQuestion(case1, 1);
    cout << "\nCase 2.1 passed\n";
    totalPoints = 0;
    cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.";
    assert(1 == askQuestion(case2, 1));
    cout << "\nCase 2.2 passed\n";
    totalPoints = 0;
    cout << "\nUnit Test Case 3: Ask all the questions of the last trivia in the linked list.";
    assert(1 == askQuestion(case3, 3));
    cout << "\nCase 3 passed\n";
    cout << "\nUnit Test Case 4: Ask 5 questions in the linked list.";
    assert(0 == askQuestion(case4, 5));
    cout << "\nCase 4 passed\n";
    cout << "\n*** End of the Debugging Version ***\n\n";
    totalPoints = 0;
}
