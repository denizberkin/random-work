#include <stdio.h>
#include "race.h"

using namespace std;


int main() {
	// Race race_starter;
	char str1[] = "Hello";
	char str2[] = "World";
	str1 = str2;
	printf("%s %s", str1, str2)

	return 0;
}
