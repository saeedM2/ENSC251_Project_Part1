//============================================================================
//
//% Student Name 1: student1
//% Student 1 #: 123456781
//% Student 1 userid (email): stu1 (stu1@sfu.ca)
//
//% Student Name 2: student2
//% Student 2 #: 123456782
//% Student 2 userid (email): stu2 (stu2@sfu.ca)
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put ‘none’ if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "<userid1>_<userid2>" (eg. stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1.cpp
// Description : Course Project Part 1 (Tokenizer)
//============================================================================

//#include "Part1Tokenizer.h"
// at least some of the following will eventually go in a file "Part1Tokenizer.h":
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int Check_for_operator(char element);
int Check_for_punctuation(char element);
vector<string> tokenizeCodeStrip(istream& code); // declaration


// end of eventual contents of file "Part1Tokenizer.h"
// Accepts a stream and returns a vector of tokens with any remaining preprocessing directives stripped out
// Input: a stream
// Output: a vector of tokens

vector<string> tokenizeCodeStrip(istream& code)
{
	//initialize and/or Declare
	string input;
	string token;
	vector<string> v1;
	int sizeOfString = 0;

	//Save in Auxiliary variable input
	getline(code, input);

	//measure size
	sizeOfString=input.length();
	cout<<input<<endl;
	//Compare String against white space, operator, punctuation, directives
	for(int i=0; i<sizeOfString; i++)
	{

		token=token+input[i];

		if(token[0] ==' ')
		{
			token="";
		}
		else if(input[i] == ' ')
		{
			token.pop_back();
			v1.push_back(token);
			token="";
		}
		else if(Check_for_operator(input[i]) ==1 && input[i-1] ==' ')
		{
			//cout<<token<<endl;
			v1.push_back(token);
			token="";
		}
		else if(Check_for_operator(input[i])==1 && input[i+1] !=' ')
		{
			token.pop_back();
			v1.push_back(token);
			token=input[i];
			v1.push_back(token);
			token="";
		}
		else if(input[i] == ';' && input[i-1] ==' ')
		{
			v1.push_back(token);
			token="";
		}
		else if(input[i] == ';' && input[i-1] !=' ')
		{
			token.pop_back();
			v1.push_back(token);
			token=";";
			v1.push_back(token);
			token="";
		}
	}


	cout<<v1[0]<<endl;
	cout<<v1[1]<<endl;
	cout<<v1[2]<<endl;
	cout<<v1[3]<<endl;
	cout<<v1[4]<<endl;
	cout<<v1[5]<<endl;






	// *** Fill in implementation ***
	vector<string> answer = {v1[0], v1[1] ,v1[2], v1[3], v1[4], v1[5]};
	v1.clear();
	return answer;
}


int Check_for_operator(char element)
{

	int boolean=0;
	int sizeOfarray=0;
	char operators[] ={'=','+','-','*','/','~','&','^','%'};

	//measure size
	sizeOfarray=sizeof(operators);
	for(int i=0; i<sizeOfarray; i++)
	{
		if(operators[i] == element)
		{
			boolean=1;
		}
	}

	return boolean;
	}




