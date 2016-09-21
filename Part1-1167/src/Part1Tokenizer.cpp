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
int Special_check(string element,int index);
string Check_for_special_operator(string element,int *index, int boolean, int *size_sub_string);
string String_inside_Quotation(string input, int *index);

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
	string temp;
	string special_string;
	vector<string> v1;
	vector<string> answer;
	int sizeOfString = 0;
	int sizeofV1=0;
	int boolean=0;
	int size_sub_string=0;

	//Save in Auxiliary variable input
	getline(code, input);
	cout<<input<<endl;
	//measure size
	sizeOfString=input.length();
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
		else if(input[i] == '"')
		{
			token=String_inside_Quotation(input, &i);
			v1.push_back(token);
			token="";
		}
		else if(Check_for_operator(input[i])==1 && input[i-1] ==' ' && Special_check(input,i) == -1)
		{
			//cout<<token<<endl;
			v1.push_back(token);
			token="";

		}
		else if(Check_for_operator(input[i])==1 && input[i+1] !=' ' && Special_check(input,i) == -1)
		{
			if(token.length() > 1)
			{
				token.pop_back();
				v1.push_back(token);
			}
			token=input[i];

			v1.push_back(token);
			token="";
		}
		else if((boolean=Special_check(input,i)) > 1)
		{
			//token.pop_back();
			cout<<token<<endl;
			special_string=Check_for_special_operator(input, &i, boolean, &size_sub_string);
			v1.push_back(special_string);
			v1.push_back(token);
			token="";

			//v1.erase(v1.begin() + 0);

		}
		else if(Check_for_punctuation(input[i]) ==1 && input[i-1] ==' ')
		{
			v1.push_back(token);
			token="";
		}
		else if(Check_for_punctuation(input[i]) ==1 && input[i-1] !=' ')
		{
			if(input[i-1] !='"')
			{
				token.pop_back();
				v1.push_back(token);
			}
			token=input[i];
			v1.push_back(token);
			token="";
		}
	}

	//stream out to be tested by TestPart1
	//v1.erase( v1.begin() + 0);
	sizeofV1=v1.size();
	for(int i=0; i< sizeofV1 ; i++)
	{
		//cout<<v1[i]<<endl;
		answer.push_back(v1[i]);
	}
	v1.clear();
	return answer;
}
int Check_for_operator(char element)
{
	int boolean=0;
	int sizeOfarray=0;
	char operators[] ={'=','+','-','*','/','~','&','^','%','|','?'};
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
string Check_for_special_operator(string element,int *index, int boolean, int *size_sub_string)
{
	int i=*index;
	int count=0;
	int sizeOfarrayChar=0;
	int sizeOfelement=0;
	int sizeOfarrayString=0;
	char special_operator_char[]={'=','+','-','*','/','~','&','^','%', '<','>', '|'};//* is multiplication or indirection operator depending on context
	string special_operator_string[] = {"++","--","+=", "-=","*=","==","/=",">>=","<<=","&=","^=","|="};
	string special_string="";
	//measure size
	sizeOfarrayChar=sizeof(special_operator_char);
	sizeOfelement=element.length();
	sizeOfarrayString=sizeof(special_operator_string)/sizeof(special_operator_string[0]);

	if(boolean == 2)
	{
		special_string=special_string+element[i];
		special_string=special_string+element[i+1];
		i=*index+1;
	}
	else if(boolean == 3)
	{
		special_string=special_string+element[i];
		special_string=special_string+element[i+1];
		special_string=special_string+element[i+2];

		for(int j=0; j < sizeOfarrayString; j++)
		{
			if( special_string != special_operator_string[j] )
			{
				count++;
				*size_sub_string=3;
				i=*index;
			}
		}
		if(count == sizeOfarrayString)
		{
			special_string.pop_back();
			i=*index+2;
		}
	}
	*index=i;
	return special_string;
}
int Check_for_punctuation(char element)
{
	int boolean=0;
	int sizeOfarray=0;
	char punctuation[] ={'(', ')',':',';','*'};//* is multiplication or indirection operator depending on context
	//measure size
	sizeOfarray=sizeof(punctuation);
	for(int i=0; i<sizeOfarray; i++)
	{
		if(punctuation[i] == element)
		{
			boolean=1;
		}
	}
		return boolean;
}
string String_inside_Quotation(string input, int *index)
{
	int counter=0;
	string token="";
	unsigned sizeOfString=input.length();
	for(unsigned int i=*index; i < sizeOfString; i++)
	{
		if(input[i]=='"')
		{
			counter++;
		}
		if(counter==1)
		{
			token=token+input[i];
		}
		else if(counter==2)
		{
			token=token+input[i];
			*index=i;
			return token;
			break;
		}
	}
}
int Special_check(string element,int index)
{

	int special_operator_falg=0;
	int boolean=0;
	int count=0;
	int count_index=0;
	int sizeOfarray=0;
	int sizeOfelement=0;
	int i=index;
	int difference_check=index;
	char special_operator_char[] ={'=','+','-','*','/','~','&','^','%', '<','>', '|'};//* is multiplication or indirection operator depending on context

	sizeOfarray=sizeof(special_operator_char);
	sizeOfelement=element.length();

	while((i < sizeOfelement) && (i-index) < 3)
	{
		for(int j=0; j<sizeOfarray; j++)
		{
				//cout<<i-index<<endl;
				if(element[i] == special_operator_char[j])//need to fix this to include guard against =+, +-, =& and etc.Because these pass but shoudent
				{
					special_operator_falg++;
				}
				else if (element[i] != special_operator_char[j] )
				{
					count++;
					if(count >= sizeOfarray && special_operator_falg==1)
					{
						 special_operator_falg=0;
					}
				}
				if(special_operator_falg == 2)
				{
					boolean=2;
				}
				else if(special_operator_falg == 3)
				{
					boolean=3;
				}
				else if(special_operator_falg==0)
				{
					boolean=-1;
				}
		}
		count=0;
		i++;
	}
	return boolean;
}
