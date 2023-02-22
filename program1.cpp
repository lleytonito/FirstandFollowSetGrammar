#include "program1.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

vector<string> nonterminals;
vector<string> terminals;
vector<string> rules;
vector<string> tokens;
vector<int> statNonT;
vector<int> statT;
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

	for (string i; getline(inFile, i, delim); rules.push_back(i)) {
		if (i == "\n") {
			break;
		}
	}

	int charCount = 0;
	int totalCharCount = 0;
	int tokenCount = 0;
	char firstChar;
	string firstToken;
	for (int i = 0; i < rules.size(); i++) {
		firstChar = rules[i].at(0);
		if (isspace(firstChar)) {
			rules[i].erase(0,1);
		}
		for(int j = 0; j < rules[i].length(); j++) {
			char itr = rules[i].at(j);
			charCount++;
			if(isspace(itr)) {
				token = rules[i].substr(totalCharCount, charCount-1);
				tokens.push_back(token);
				totalCharCount += charCount;
				charCount = 0;
			}
		}


		
		if (!isalpha(tokens[tokenCount][0])) {
			cout << "INVALID FIRSTLETTERID" << endl;
			exit(0);
		}

		for(int k=1; k < tokens[tokenCount].length(); k++) {
			if(! isalpha(tokens[tokenCount][k])) {
				if(! isdigit(tokens[tokenCount][k])) {
					grammar = false;
					cout << "INVALID LETTERS/DIGITS ONLY FIRST ID" << endl;
					exit(0);
				}
			}
		}
		tokenCount++;

		if(tokens[tokenCount] != "->") {
			cout <<  "INVALID ARROW" << endl;
			exit(0);
		}
		tokenCount++;

		for(tokenCount; tokenCount< tokens.size(); tokenCount++) {
			if (!isalpha(tokens[tokenCount][0])) {
			cout << "INVALID FIRSTLETTERID" << endl;
			exit(0);
			}

			for(int k=1; k < tokens[tokenCount].length(); k++) {
				if(! isalpha(tokens[tokenCount][k])) {
					if(! isdigit(tokens[tokenCount][k])) {
						grammar = false;
						cout << "INVALID LETTERS/DIGITS ONLY FIRST ID" << endl;
						exit(0);
					}
				}
		}
		}

		
		totalCharCount = 0;
		charCount = 0;
		tokenCount = tokens.size();

	}

	//store terminals in a vector<string>
	bool nonT = false;
	for(int i = 0; i < tokens.size(); i++) {
		//if token is not an arrow, then check token to see if it is a non terminal
		if(tokens[i] != "->") {
			for (int j = 0; j < nonterminals.size(); j++) {
				if(tokens[i] == nonterminals[j]) {
					nonT = true;
				}
			}
			//if token is not a nonterminal or an arrow, it must be a terminal
			if(!nonT) {
				terminals.push_back(tokens[i]);
			}
		}

		//reset nonterminal boolean
		nonT = false;
	}

	//algorithm designed to sort terminals in ascii order
	for (int j = 0; j < terminals.size(); j++) {
		for(int i = 0; i < terminals.size(); i++) {
			if (int(terminals[i][0]) > int(terminals[i+1][0])) {
				swap(terminals[i],terminals[i+1]);
			}
			else if (int(terminals[i][0]) == int(terminals[i+1][0])) {
				if (int(terminals[i][1]) > int(terminals[i+1][1])) {
					swap(terminals[i],terminals[i+1]);
				}
			}
		}
	}

	//set grammar to true if all cases pass
	grammar = true;
}

// Returns a string with some statistics for the grammar.
void GetStats() {
	//if loadGrammar returns false, return ""
	if (grammar == false) {
		exit(0);
	}

	//statNonT holds number of rules nonterminals appear in
	

	//set statNonT to a zero for every nonterminal
	for (int i = 0; i < nonterminals.size(); i++) {
		statNonT.push_back(0);
	}

	//for all tokens, check for nonterminal
	for(int j = 0; j < tokens.size(); j++) {
		//if token is an arrow, the token before it must be a nonterminal
		if (tokens[j] == "->") {
			//find the correct nonterminal and add one to the position of its counter
			for (int i = 0; i < nonterminals.size(); i++) {
				if (nonterminals[i] == tokens[j-1]) {
					statNonT[i]++;
				}
			}
		}
		
	}


	for(int i = 0; i < statNonT.size(); i++) {
		cout << nonterminals[i] << " - ";
		cout << statNonT[i] << " ";
		
	}

	for (int i = 0; i < terminals.size(); i++) {
		statT.push_back(0);
	}

	//for all tokens, if the token is a terminal, add one to the corresponding value in statT
	for(int i = 0; i < tokens.size(); i++) {
		for (int j = 0; j < terminals.size(); j++) {
			if(terminals[j] == tokens[i]) {
				statT[j]++;
			}
		}
	}


	for(int i = 0; i < statT.size(); i++) {
		cout << terminals[i] << " - ";
		cout << statT[i] << " ";
		
	}

}

// Returns the first sets of all nonterminals.
char* GetFirstSets() {
	for (int i = 0; i < nonterminals.size(); i++) {
		for (int j = 0; j < statNonT[i]; j++) {
			
		}
	}
	
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
