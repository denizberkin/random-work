#include <iostream>
#include <Windows.h>
#include <ctime>
#include "race.h"

using namespace std;

Race::Race(){
	srand(time(0));
	while (true)
	{
		cout << "BANG !!!!!\nAND THEY'RE OFF !!!!!" << endl;
		int endCondition = race(&harePos, &tortoisePos);
		if (endCondition == 0) {
			break;
		}
	}
}

void Race::moveTortoise (int *tortoisePos){
	int caseNum = rand() % 10 + 1;

	if (caseNum <= 5 && caseNum >= 1) {
		*tortoisePos += 3;
	}
	else if (caseNum == 6 || caseNum == 5) {
		*tortoisePos -= 6;
	}
	else
	{
		*tortoisePos += 1;
	}

	*tortoisePos = (*tortoisePos < 1) ? 1 : *tortoisePos;
	*tortoisePos = (*tortoisePos > 70) ? 70 : *tortoisePos;
}


void Race::moveHare (int *harePos){
	int caseNum = rand() % 10 + 1;

	if (caseNum == 1 || caseNum == 2)
		*harePos += 9;
	else if (caseNum == 3)
		*harePos -= 12;
	else if (caseNum >= 4 && caseNum <= 6)
		*harePos += 1;

	*harePos = (*harePos < 1) ? 1 : *harePos;
	*harePos = (*harePos > 70) ? 70 : *harePos;
}


int Race::race(int *harePos, int *tortoisePos) {
	moveTortoise(tortoisePos);
	moveHare(harePos);

	for (int i = 0; i < 71; i++)
	{
		if (*harePos == *tortoisePos && *harePos == i) {
			cout << "OUCH!!!";
		}
		else if (i == *harePos) {
			cout << "H";
		}
		else if (i == *tortoisePos) {
			cout << "T";
		}
		else{ cout << " "; }
	}

	cout << "\n";

	Sleep(1000);

	if ((*harePos & *tortoisePos) == 70) {
		cout << "Its a tie." << endl;
		return 1;
	}
	else if (*harePos == 70) {
		cout << "Hare wins. Yuch." << endl;
		return 0;
	}
	else if (*tortoisePos == 70) {
		cout << "TORTOISE WINS!!! YAY!!!" << endl;
		return 0;
	}
	else {
		race(harePos, tortoisePos);
	}
}
