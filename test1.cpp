#include "program1.h"
#include <iostream>

using namespace std;

/* You may use this file to test your program.
	This file will not be submitted, as a different test1.cpp will be used. */
int main(int argv, char **argc) {
	LoadGrammar("test.txt");
	char * testStats = GetStats();
	char * testFirst = GetFirstSets();

	cout << "Returned From GetStats:\n";
	cout << testStats << "\n";

	cout << "Returned from GetFirstSets:\n"; 
	cout << testFirst << "\n";

	delete[] testStats;
	delete[] testFirst;

	return 0;
}