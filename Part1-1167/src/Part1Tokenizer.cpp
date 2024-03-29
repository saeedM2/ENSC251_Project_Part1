//============================================================================
//
//% Student Name 1: Saeed Molaie
//% Student 1 #:301189698
//% Student 1 userid (email): smolaie@sfu.ca
//
//% Student Name 2: Gabe Teeger
//% Student 2 #: 301261001
//% Student 2 userid (email): gteeger@sfu.ca
//
// Helpers: Mohammad Akbari (TA)
//
//
// Name        : Part1Tokenizer.cpp
// Description : Course Project Part 1 (Tokenizer)
//============================================================================

//#include "Part1Tokenizer.h"
// at least some of the following will eventually go in a file "Part1Tokenizer.h":
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>        // needed for std::size_t
#include <algorithm>

using namespace std;

//function declaration
bool Check_for_operator(char element);
int Check_for_punctuation(char element);
int Special_check(string element, int index);
string Extract_special_operator(string element, int *index, int output);
string String_inside_Quotation(string input, int *index);
vector<string> Exponent(vector<string> v1);
vector<string> Remove_Any_RemainingSpaces(vector<string> v1);
vector<string> Operator_with_three_char(vector<string> v1);
string UnwantedString3(string input);
string unterminated_strings(string input, string *RemoveThis);
string Remove_All_BackSlash_White_space(string input);


//Global variables
bool squote(string input);
const char *quote = "'";
const char *space = " ";

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
	string combine;
	string special_string;
	string RemoveThis;
	string RemoveThis2;
	vector<string> v1;//v1 is a vector holding valid tokens
	vector<string> answer;
	int sizeOfString = 0;
	int sizeofV1 = 0;
	int boolean = 0;
	int squotetest = 0;

	//Save in Auxiliary variable input
	while (getline(code, combine))
	{
		std::size_t found = combine.find_first_not_of(*space);
		if (combine[found] == '#') //ignore line if # starts the string
		{
			continue;
		}
		input += combine;
	}
	squotetest = squote(input); //tests whether an unterminated single quote exists in the input

	if (squotetest == 1) //if an unterminated single quote exists
	{
		input = UnwantedString3(input);//removes the part of the string in between a single quote and the semicolon, including
		for (unsigned int K = 0; K< input.length(); K++)
		{
			if (input[K] == '\'')
			{
				input.at(K) = '`';//Detect flag `
				RemoveThis2 = '`';//remove flag `
				cout << endl;
				cout << "Warning: You have an unterminated Single Quote String!!" << endl;
				cout << endl;
			}
			if (input[K] == '\r')
			{
				input.erase(input.begin() + K);
			}
			if (input[K] == '\n')
			{
				input.erase(input.begin() + K);
			}
		}
	}
	//remove white space: \n, \t, \r
	input = Remove_All_BackSlash_White_space(input);
	//remove unterminated string
	input = unterminated_strings(input, &RemoveThis);
	//get size of string stream
	sizeOfString = input.length();

	for (int i = 0; i<sizeOfString; i++)
	{
		token = token + input[i];
		if (token[0] == ' ') //if the first element in token is a space
		{
			token = "";
		}
		else if (input[i] == ' ' && Special_check(input, i) == -1)
		{
			token.pop_back();
			v1.push_back(token);
			token = "";
		}
		else if (input[i] == *quote && squotetest == 1)
		{
			token.pop_back();
		}
		else if (input[i] == '"')
		{
			token = String_inside_Quotation(input, &i);
			v1.push_back(token);
			token = "";
		}
		else if (Check_for_operator(input[i]) == 1 && input[i - 1] == ' ' && Special_check(input, i) == -1)
		{
			if(input[i] !='.')
			{
				v1.push_back(token);
				token = "";
			}
			else if(input[i] =='.' && isdigit(input[i-1]) != 1 && isdigit(input[i+1]) != 1)
			{
				v1.push_back(token);
				token = "";
			}
		}
		else if (Check_for_operator(input[i]) == 1 && input[i + 1] != ' ' && Special_check(input, i) == -1)
		{
			if(input[i] !='.')
			{
				if (token.length() > 1)
				{
					token.pop_back();
					v1.push_back(token);
					token = "";
				}
				token = input[i];
				v1.push_back(token);
				token = "";
			}
			else if(input[i] =='.' && isdigit(input[i-1]) != 1 && isdigit(input[i+1]) != 1)
			{
				if (token.length() > 1)
				{
					token.pop_back();
					v1.push_back(token);
					token = "";
				}
				token = input[i];
				v1.push_back(token);
				token = "";
			}
		}
		else if ((boolean = Special_check(input, i)) > 1)
		{

			if(Check_for_punctuation(input[i-2]) == 1)
			{
				if(token.length() > 1 && token[1] !=' ')
				{
					token.pop_back();
					v1.push_back(token);
					token=input[i];
					v1.push_back(token);
					token="";
				}
			}
			if(input[i - 1]  != ' ')
			{
				special_string = Extract_special_operator(input, &i, boolean);
				if(Check_for_operator(token[0]) != 1)
				{
					if(token !="")
					{
						v1.push_back(token);
					}
				}
				v1.push_back(special_string);
				token = "";
			}
		}
		else if (Check_for_punctuation(input[i]) == 1 && input[i - 1] == ' ')
		{
			v1.push_back(token);
			token = "";
		}
		else if (Check_for_punctuation(input[i]) == 1 && input[i - 1] != ' ')
		{
			if (input[i - 1] != '"' && token != ";")
			{
				token.pop_back();
				if(Check_for_punctuation(input[i-1]) != 1)
				{
					if(token !="")
					{
						v1.push_back(token);
					}
				}
				else if(Check_for_punctuation(input[i-1]) == 1)
				{
					v1.push_back(token);
				}
				token = "";
			}
			if(Check_for_punctuation(input[i-1]) != 1 )
			{
				if(token.length()>1)
				{
					token.pop_back();
				}
				token = input[i];
				v1.push_back(token);
				token = "";
			}
			else if(Check_for_punctuation(input[i-1]) == 1)
			{
				token = input[i];
				v1.push_back(token);
				if(token !=";")
				{
					v1.erase(v1.begin()+i-2);
				}
				//v1.erase(v1.begin()+i-2);//remove extra space
				token = "";
			}
		}
	}
	for (unsigned int L = 0; L <v1.size(); L++)
	{
		if (v1[L] == RemoveThis)
		{
			v1.at(L) = "";
		}
		if (v1[L] == RemoveThis2)
		{
			v1.at(L) = "";
		}
	}
	//Some additional operations on v1 to clean up the vector output
	sizeofV1 = v1.size();
	v1=Exponent(v1);
	v1=Remove_Any_RemainingSpaces(v1);
	v1=Operator_with_three_char(v1);

	sizeofV1 = v1.size();
	for (int i = 0; i< sizeofV1; i++)
	{
		answer.push_back(v1[i]);
	}
	v1.clear();
	return answer;
}

//Checks whether various single operators exist. If one exists, 1 is returned, otherwise 0 is returned by the function
bool Check_for_operator(char element)
{
	int boolean = 0;
	int sizeOfarray = 0;
	char operators[] = { '=', '+', '-', '*', '/', '~', '&', '^', '%', '|', '?' ,'>','<',',','.'};
	//measure size
	sizeOfarray = sizeof(operators);
	for (int i = 0; i<sizeOfarray; i++)
	{
		if (operators[i] == element)
		{
			boolean = 1;
		}
	}
	return boolean;
}

//Checks whether various punctuation marks exist. If one exists, 1 is returned, otherwise a zero is returned by the function
int Check_for_punctuation(char element)
{
	int boolean = 0;
	int sizeOfarray = 0;
	char punctuation[] = { '(', ')', ':', ';', '*','{','}','[',']' };//* is multiplication or indirection operator depending on context
	//measure size
	sizeOfarray = sizeof(punctuation);
	for (int i = 0; i<sizeOfarray; i++)
	{
		if (punctuation[i] == element)
		{
			boolean = 1;
		}
	}
	return boolean;
}

//returns a token that is put into the output vector when there is a double quote present
string String_inside_Quotation(string input, int *index)
{
	int counter = 0;
	string token = "";
	unsigned sizeOfString = input.length();
	for (unsigned int i = *index; i < sizeOfString; i++)
	{
		if (input[i] == '"')
		{
			counter++;
		}
		if (counter == 1)
		{
			token = token + input[i];
		}
		else if (counter == 2)
		{
			token = token + input[i];
			*index = i;
			break;
		}
	}
	return token;
}

//ensures that operators with 2 characters are treated as a single token (examples: ++, -+, etc.)
string Extract_special_operator(string element, int *index, int output)
{
	int i = *index;
	int count4SmallestIndex=0;
	int index2 = 0;
	int sizeOfarrayChar = 0;
	char special_operator_char[] = { '=', '+', '-', '*', '/', '~', '&', '^', '%', '<', '>', '|' ,'!','?'};//* is multiplication or indirection operator depending on context
	string special_string = "";
	vector<int> smallestIndex;
	//measure size
	sizeOfarrayChar = sizeof(special_operator_char);
	while(count4SmallestIndex < sizeOfarrayChar)
	{
		for (int u = count4SmallestIndex; u<sizeOfarrayChar; u++)
		{
			index2 = element.find_first_of(special_operator_char[u], i);
			if (index2 != -1)
			{
				smallestIndex.push_back(index2);
				break;
			}
		}
		count4SmallestIndex++;
	}
	index2=*min_element(smallestIndex.begin(),smallestIndex.end());
	i = index2;
	if (output == 2)
	{
		special_string = special_string + element[i];
		special_string = special_string + element[i + 1];
		i = index2 + 1;
	}
	else if (output == -1)
	{
		cout << "error" << endl;
	}
	*index = i;
	return special_string;
}

//checks for operators that are consecutive more than once (==,+-...etc)
int Special_check(string element, int index)
{
	int special_operator_falg = 0;
	int output = 0;
	int count = 0;
	int sizeOfarray = 0;
	int sizeOfelement = 0;
	int i = index;
	char special_operator_char[] = { '=', '+', '-', '*', '/', '~', '&', '^', '%', '<', '>', '|','!' ,'?', };//'*' is multiplication or indirection operator depending on context

	//measure size of array and string
	sizeOfarray = sizeof(special_operator_char);
	sizeOfelement = element.length();

	while ((i < sizeOfelement) && (i - index) < 3)
	{
		for (int j = 0; j<sizeOfarray; j++)
		{
			if (element[i] == special_operator_char[j])
			{
				special_operator_falg++;
			}
			else if (element[i] != special_operator_char[j])
			{
				count++;
				if (count >= sizeOfarray && special_operator_falg == 1)
				{
					special_operator_falg = 0;
				}
			}
			if (special_operator_falg == 2)
			{
				output = 2;
			}
			else if (special_operator_falg == 0)
			{
				output = -1;
			}
		}
		count = 0;
		i++;
	}
	return output;
}

//Takes a string that was found to contain an unterminated single quote. This function deletes everything in between the single quote and the semicolon
//This function also deletes the unterminated single quote.
string UnwantedString3(string input)
{
	std::size_t foundfirst = input.find_first_of(*quote);
	std::size_t foundfirstsc = input.find_first_of(';');
	input.replace(input.begin() + (foundfirst + 1), input.begin() + foundfirstsc, "");
	return input;
}

//Checks whether a single quote is closed by another single quote.
//If a second quote closes the first quote, zero is returned and if not a one is returned.
bool squote(string input)
{
	size_t sizeOfstring = 0;
	sizeOfstring = input.length();
	std::size_t foundfirst = input.find_first_of(*quote);
	std::size_t foundlast = input.find_last_of(*quote);

	if (foundfirst == foundlast && foundfirst<sizeOfstring)
	{
		return 1;
	}
	else{
		return 0;
	}
}

//ensures that an exponential number is treated properly as one string and is not incorrectly separated.
//exponential parts of numbers are preceded by an e
vector<string> Exponent(vector<string> v1)
{
	int sizeVector = v1.size();
	int sizeIndexVector = 0;
	int flag = 0;
	int flag_for_change_v1_size = 0;
	vector<int> indexVector;
	string Check;
	string string;
	for (int i = 0; i<sizeVector; i++)
	{
		string = v1[i];
		if (isdigit(string[0]) == 1)
		{

			if (string.back() == 'e' || string.back() == 'E')
			{
				indexVector.push_back(i);
				flag = 1;
			}
		}
	}
	if (flag == 1)
	{
		sizeIndexVector = indexVector.size();
		for (int j = 0; j<sizeIndexVector; j++)
		{
			if (flag_for_change_v1_size == 1)
			{
				for( int j=0; j < sizeIndexVector; j++)
				{
					indexVector.at(j) = indexVector[j] - 2;
				}
			}
			else if (flag_for_change_v1_size == 2)
			{
				indexVector.at(j) = indexVector[j] - 1;
			}
			Check = v1[indexVector[j] + 1];
			if (Check[0] == '+' || Check[0] == '-')
			{
				v1.at(indexVector[j]) = v1[indexVector[j]] + v1[indexVector[j] + 1] + v1[indexVector[j] + 2];
				v1.erase(v1.begin() + indexVector[j] + 1);
				v1.erase(v1.begin() + indexVector[j] + 1);
				flag_for_change_v1_size = 1;
			}
			else if (Check[0] != '+' && Check[0] != '-')
			{
				v1.at(indexVector[j]) = v1[indexVector[j] + 1];
				v1.erase(v1.begin() + indexVector[j] + 1);
				flag_for_change_v1_size = 2;
			}
		}
	}
	return v1;
}

//removes any unwanted whitespace in each string
vector<string> Remove_Any_RemainingSpaces(vector<string> v1)
{
	string token;
	int sizeVector = v1.size();
	int sizeToken =0;
	for(int i=0; i<sizeVector; i++)
	{
		token=v1[i];
		sizeToken=token.length();
		if(token[sizeToken-1] ==' ')
		{
			token.pop_back();
			v1.at(i)=token;
		}
	}
	return v1;
}

//removes everything after an unterminated double quote
string unterminated_strings(string input, string *RemoveThis)
{
	int sizeOfInput = 0;
	int count = 0;
	int index2 = 0;
	int index1 = 0;
	vector<int> index;

	sizeOfInput = input.length();

	for (int i = 0; i< sizeOfInput; i++)
	{
		if (input[i] == '"')
		{
			count++;
			index.push_back(i);
		}
	}
	if (count % 2 == 1)
	{
		index2 = input.find_first_of(';', index[0]);
		input.insert(index2 + 1, 1, '"');
		*RemoveThis = input.substr(index[0], index2);
		index1 = (*RemoveThis).find_first_of('"');
		index2 = (*RemoveThis).find_last_of('"');
		(*RemoveThis) = (*RemoveThis).substr(index1, index2 + 1);
		cout << endl;
		cout << "Warning: You have an unterminated Double Quote String!!" << endl;
		cout << endl;
	}
	return input;
}

//removes all unwanted white space created by various 'escape sequences' (example \t, \n, etc.)
string Remove_All_BackSlash_White_space(string input)
{
	for (unsigned int K = 0; K< input.length(); K++)
	{
		if (input[K] == '\r')
		{
			input.erase(input.begin() + K);
		}
		if (input[K] == '\n')
		{
			input.erase(input.begin() + K);
		}
		if (input[K] == '\t')
		{
			input.erase(input.begin() + K);
		}
		if (input[K] == '\v')
		{
			input.erase(input.begin() + K);
		}
		if (input[K] == '\f')
		{
			input.erase(input.begin() + K);
		}
		if (input[K] == '\b')
		{
			input.erase(input.begin() + K);
		}
	}
	return input;
}

//ensures that operators with 3 characters are treated correctly and not separated (example: <<=,>>=...etc)
vector<string> Operator_with_three_char(vector<string> v1)
{
	string token;
	int pos1=0;
	int pos2=0;
	int index=0;
	int sizeOfvector_v1=0;
	//element.find_first_of(special_operator_char[u], i);
	sizeOfvector_v1 = v1.size();

	for(int i=0; i < sizeOfvector_v1; i++)
	{
		token=v1[i];
		pos1=token.find_first_of('<');
		pos2=token.find_first_of('>');

		if(pos1 >-1 || pos2 >-1)
		{
			if(pos1 > -1)
			{
				if(v1[i+1] =="=")
				{
					index=i;
					token=v1[i]+v1[i+1];
					v1.erase(v1.begin()+index+1);
					v1.at(i)=token;
					break;
				}
			}
			else if(pos2 > -1)
			{
				if(v1[i+1] =="=")
				{
					index=i;
					token=v1[i]+v1[i+1];
					v1.erase(v1.begin()+index+1);
					v1.at(i)=token;
					break;
				}
			}
		}
	}
	return v1;
}
