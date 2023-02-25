#include "program1.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>

using namespace std;

//global variables
vector<string> nonterminals;
vector<string> terminals;
vector<string> rules;
vector<string> tokens;
vector<string> firstTrack;
vector<int> statNonT;
vector<int> statT;
bool grammar = false;
int nonTCounter;
char * blank = new char[0];

// Loads the grammar.
void LoadGrammar(char *grammarFileName) {

	//local variables
	ifstream inFile;
	string token;
	string temp;
	const char delim = '@';
	const char d1 = ' ';
	const char d2 = '\n';

	//open file
	inFile.open(grammarFileName);

	//error handling for file doesn't exist
	if( !inFile )
	{
		cerr << "Unable to open file: " << grammarFileName << endl;
		exit(0);
	}

	//put contents of file into string
	while (inFile) {
	getline(inFile, token, '\0');
	}
	istringstream s(token);

	//split string using any whitespace character
	for (string string1; getline(s, string1, d1); ) {
		istringstream s1(string1);
		for (string string2; getline(s1, string2, d2); tokens.push_back(string2));
	}

	//erase empty tokens
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].length() == 0) {
			tokens.erase(tokens.begin()+i);
		}
	}
	
	//get first line of nonterminals, and put in nonterminals vector
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "@@") {
			break;
		} 
		else if (tokens[i] == "@") {
			break;
		}
		else {
			nonterminals.push_back(tokens[i]);
		}
	}

	//erase all tokens in the first line
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[0] == "@") {
			tokens.erase(tokens.begin());
			break;
		}
		else {
			tokens.erase(tokens.begin());
		}	
	}

	//local variables for rules vector
	string rule;
	vector<string> temptokens;

	//temptokens is identical to tokens
	for (int i = 0; i < tokens.size(); i++) {
		temptokens.push_back(tokens[i]);
	}

	//while loop that loops until "@@" sign is reached, and erases each element of temptokens to place it into the rules vector, which is split by "@".
	while (1) {
		if (temptokens[0] == "@@") {
			break;
		} 
		else if (temptokens[0] == "@") {
			rules.push_back(rule);
			rule = "";
			temptokens.erase(temptokens.begin());
		}
		else {
			rule = rule + temptokens[0] + " ";
			temptokens.erase(temptokens.begin());
		}
	}




	//checker for validity of nonterminals
	for(int i = 0; i < nonterminals.size(); i++) {
		temp = nonterminals[i];
		if(!isalpha(temp[0])) {
			grammar = false;
			return;
		}
		for(int i=1; i < temp.length(); i++) {
			if(! isalpha(temp[i])) {
				if(! isdigit(temp[i])) {
					grammar = false;
					return;
				}
			}
		}
	}

	int tokenCount = 0;
	
	for (int i = 0; i < rules.size(); i++) {
		if (! isalpha(tokens[tokenCount][0])) {
			if (tokens[tokenCount] != "#") {
				cout << "Test" << endl;
				cout << tokens[tokenCount] << endl;
			grammar = false;
			return;
			}
		}
		for(int k=1; k < tokens[tokenCount].length(); k++) {
			if(! isalpha(tokens[tokenCount][k])) {
				if(! isdigit(tokens[tokenCount][k])) {
					grammar = false;
					cout << "INVALID LETTERS/DIGITS ONLY FIRST ID" << endl;
					return;
				}
			}
		}
		tokenCount++;

		if(tokens[tokenCount] != "->") {
			grammar = false;
			cout <<  "INVALID ARROW" << endl;
			return;
		}
		tokenCount++;

		for(tokenCount; tokenCount < tokens.size(); tokenCount++) {
			if (tokens[tokenCount] == "@") {
				tokenCount++;
				break;
			}
			if (tokens[tokenCount] == "@@") {
				tokens.erase(tokens.begin()+tokenCount, tokens.end());
				break;
			}

			if (!isalpha(tokens[tokenCount][0])) {
				if (tokens[tokenCount] != "#") {
					grammar = false;
					cout << "INVALID FIRSTLETTERID" << endl;
					cout << tokens[tokenCount] << endl;
					return;
				}
			}

			for(int k=1; k < tokens[tokenCount].length(); k++) {
				if(! isalpha(tokens[tokenCount][k])) {
					if(! isdigit(tokens[tokenCount][k])) {
						grammar = false;
						cout << "INVALID LETTERS/DIGITS ONLY FIRST ID" << endl;
						return;
					}
				}
			}
		}	
	}

		//erase "@" and "@@" as well as anything after "@@"
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "@") {
			tokens.erase(tokens.begin()+i);
		}
		if (tokens[i] == "@@") {
			tokens.erase(tokens.begin()+i, tokens.end());
		}
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
		for(int i = 0; i < terminals.size()-1; i++) {
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

	//erase duplicates from terminals vector
	auto duplicate = unique(terminals.begin(), terminals.end());
	terminals.erase(duplicate, terminals.end());



	//set grammar to true if all cases pass
	grammar = true;
}

// Returns a string with some statistics for the grammar.
char* GetStats() {
	//if loadGrammar returns false, return ""
	if (!grammar) {
		return blank;
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
	string output;
	for(int i = 0; i < statNonT.size(); i++) {
		
		output = output + nonterminals[i] + " - " + to_string(statNonT[i]) + ", ";
	}
	output.pop_back();
	output.pop_back();
	output.push_back('\n');


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
		output = output + terminals[i] + " - " + to_string(statT[i]) + ", ";
	}
	output.pop_back();
	output.pop_back();
	output.push_back('\n');

	char * cStats = new char[output.size() + 1];
	memcpy(cStats, output.c_str(), output.size()+1);
	return cStats;
}

// Returns the first sets of all nonterminals.
char* GetFirstSets() {

	if (!grammar) {
		return blank;
	}
	char* nonT;
	char* fSet;
	string fSets;
	nonTCounter = 0;
	
	int trackerCount = nonterminals.size()*terminals.size();
	for (int i = 0; i < trackerCount; i++) {
		firstTrack.push_back("N");
	}

	for(int i = 0; i < nonterminals.size(); i++) {
		nonT = new char[nonterminals[i].size() + 1];
		memcpy(nonT, nonterminals[i].c_str(), nonterminals[i].size()+1);
		fSet = GetFirstSet(nonT);
		fSets += fSet;
		nonTCounter++;
	}
	char * firstSetOutput = new char[fSets.size() + 1];
	memcpy(firstSetOutput, fSets.c_str(), fSets.size()+1);

	return firstSetOutput;
}

// Returns the first set of the specified nonterminal.
char* GetFirstSet(char *nonTerminal) {
	char * cOutput;
	string nT = nonTerminal;
	string sOutput = "FIRST(" + nT + ") = { ";


	for (int i = 0; i < tokens.size(); i++) {
		if (nT == tokens[i] && tokens[i+1] == "->") {
			for (int j = 0; j < terminals.size(); j++) {
				if(tokens[i+2] == terminals[j]) {
					if (tokens[i+2] == "#") {
						firstTrack[(nonTCounter*terminals.size())+j] = "E";
					} 
					else {
					firstTrack[(nonTCounter*terminals.size())+j] = "Y";
					}
				}
			}
		}
	}

	for (int i = 0; i < tokens.size(); i++) {
		if (nT == tokens[i] && tokens[i+1] == "->") {
			for (int j = 0; j < nonterminals.size(); j++) {
				if (tokens[i+2] == nonterminals[j]) {
					char * recNT = new char[nonterminals[j].size() + 1];
					memcpy(recNT, nonterminals[j].c_str(), nonterminals[j].size()+1);
					GetFirstSet(recNT);
					for (int k = 0; k < terminals.size(); k++) {
						if (firstTrack[(j*terminals.size())+k] == "Y") {
							firstTrack[(nonTCounter*terminals.size())+k] = "Y";
						}
						
					}
				}
			}
		}
	}

	for (int i = 0; i < terminals.size(); i++) {
		if(firstTrack[(nonTCounter*terminals.size())+i] == "Y") {
			sOutput = sOutput + terminals[i] + ", ";
		}
	}
	sOutput.pop_back();
	sOutput.pop_back();
	sOutput = sOutput + " }\n";
	cOutput = new char[sOutput.size() + 1];
	memcpy(cOutput, sOutput.c_str(), sOutput.size()+1);
	return cOutput;
}

// Returns the follow sets of all nonterminals.
char* GetFollowSets() {
	return "";
}

// Returns the follow set of the specified nonterminal.
char* GetFollowSet(char *nonTerminal) {
	return "";
}
