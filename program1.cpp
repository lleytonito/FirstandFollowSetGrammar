#include "program1.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

vector<string> nonterminals;
vector<string> rules;
bool grammar = false;

// Loads the grammar.
void LoadGrammar(char *grammarFileName) {
	ifstream inFile;
	string token;
	string temp;
	
	const char delim = '@';
	
	inFile.open(grammarFileName);
	if( !inFile )
	{
		cerr << "Unable to open file: " << grammarFileName << endl;
		exit(0);
	}
	getline(inFile, token, delim);
	istringstream s(token);
	
	for (string i; getline(s, i, ' '); nonterminals.push_back(i));

	for(int i = 0; i < nonterminals.size(); i++) {
		temp = nonterminals[i];
		if(!isalpha(temp[0])) {
			grammar = false;
			cout << "INVALID" << endl;
			exit(0);
		}
		for(int i=1; i < temp.length(); i++) {
			if(! isalpha(temp[i])) {
				if(! isdigit(temp[i])) {
					grammar = false;
					exit(0);
				}
			}
		}
	}
	while(getline(inFile, token, delim)) {
		if (token == "\n") {
			break;
		}

		istringstream line(token);
	
		for (string i; getline(line, i, ' '); rules.push_back(i));
		
		temp = rules[0];
		if (temp[0] == '\n') {
			rules[0].erase(0,1);
			temp = rules[0];
		}

		if(! isalpha(temp[0])) {
			grammar = false;
			cout << "INVALID FIRSTLETTERID" << endl;
			exit(0);
		}

		for(int i=1; i < temp.length(); i++) {
			if(! isalpha(temp[i])) {
				if(! isdigit(temp[i])) {
					grammar = false;
					cout << "INVALID LETTERS/DIGITS ONLY FIRST ID" << endl;
					exit(0);
				}
			}
		}

		if(rules[1] != "->") {
			grammar = false;
			cout << "INVALID ARROW" << endl;
			exit(0);
		}

		for(int i = 2; i < rules.size(); i++) {
			temp = rules[i];
			if(!isalpha(temp[0])) {
				grammar = false;
				cout << "INVALID FIRST NONLETTER" << endl;
				exit(0);
			}
			for(int i=1; i < temp.length(); i++) {
				if(! isalpha(temp[i])) {
					if(! isdigit(temp[i])) {
						grammar = false;
						cout << "INVALID LETTERS/DIGITS ONLY" << endl;
						exit(0);
					}
				}
			}
		}	
		cout << token << endl;
	}
	grammar == true;
}

// Returns a string with some statistics for the grammar.
char* GetStats() {
	if (grammar == false) {
	return "";
	exit(0);
	}
	
}

// Returns the first sets of all nonterminals.
char* GetFirstSets() {
	return "";
}

// Returns the first set of the specified nonterminal.
char* GetFirstSet(char *nonTerminal) {
	return "";
}

// Returns the follow sets of all nonterminals.
char* GetFollowSets() {
	return "";
}

// Returns the follow set of the specified nonterminal.
char* GetFollowSet(char *nonTerminal) {
	return "";
}
