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
// Original Version Copyright (c) 2016 Simon Fraser University
//============================================================================


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Course Project Part 1
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/join.hpp>

#include <sstream>

//#include "Part1Tokenizer.h"
// at least some of the following will eventually go in a file "Part1Tokenizer.h":
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost::algorithm;

vector<string> tokenizeCodeStrip(istream& code);
// end of eventual contents of file "Part1Tokenizer.h"

void testTokenStrings(string codeString, vector<string> desiredTokenVector)
{
	string newLineTab = " \n\t ";
	string newLine = " \n ";
	istringstream code(codeString);
	auto vectorToTest = tokenizeCodeStrip(code);
	string joinedVectorToTest = newLineTab + join(vectorToTest, " \n\t ") + newLine;
	string joinedDesiredTokenVector = newLineTab + join(desiredTokenVector, " \n\t ") + newLine;

	BOOST_CHECK_EQUAL(joinedVectorToTest, joinedDesiredTokenVector);

}


BOOST_AUTO_TEST_CASE( test1 )
{
	testTokenStrings("sum = a + 10 ;",
			{"sum","=","a","+","10",";"});
}

BOOST_AUTO_TEST_CASE( test2 )
{
	testTokenStrings("sum=a+10;",
			{"sum","=","a","+","10",";"});
}


BOOST_AUTO_TEST_CASE( test3 )
{
	testTokenStrings("char* str; str = \"string test.\";"
			,{"char", "*","str",";", "str","=","\"string test.\"",";"});
}


BOOST_AUTO_TEST_CASE( test4 )
{
	testTokenStrings(" str    =    \"  x  \"     \"  +  \"     \"  \"    ; ",
			         {"str", "=", "\"  x  \"",  "\"  +  \"",  "\"  \"", ";"});
}



BOOST_AUTO_TEST_CASE( test5 )
{
	testTokenStrings("i+==j;",
			{"i","++","+","j",";"});
}



BOOST_AUTO_TEST_CASE( test6 )
{
	testTokenStrings("#define MY_DEFINE \n int i;",
										{"int","i",";"});
}

BOOST_AUTO_TEST_CASE( test7 )
{
    // the comment below shows what's in memory (but with extra whitespace
    //      to align things as much as possible) delimited by '[' and ']' and
    //      using ? to indicate control characters:
    //                 [#define MYDEFINE ? ?  str    =     """       "+"      ""     ; ]
	testTokenStrings(  "#define MYDEFINE \r\n str    =    \"\"\"    \"+\"    \"\"    ; ",
										  {  "str", "=", "\"\"\"", "\"+\"", "\"\"", ";"});
}

// below demonstrates a bug in one of our libraries

BOOST_AUTO_TEST_CASE( test7bug )
{
    // the comment below shows what's in memory (but with extra whitespace
    //      to align things as much as possible) delimited by '[' and ']' and
    //      using ? to indicate control characters:
    //                 [#define MYDEFINE ? ?  str    =     "\""        "+"      ""     ; ]
	testTokenStrings(  "#define MYDEFINE \r\n str    =    \"\\\"\"    \"+\"    \"\"    ; ",
										  {  "str", "=", "\"\\\"\"", "\"+\"", "\"\"", ";"});
}


BOOST_AUTO_TEST_CASE( test8 )
{
	testTokenStrings("float pi; pi = 314159E-5;",
			{"float","pi",";","pi","=","314159E-5",";"});
}

BOOST_AUTO_TEST_CASE( test9 )
{
	testTokenStrings("sumFloat = 314159E-5 + 12345e-3;",
			{"sumFloat","=","314159E-5","+","12345e-3",";"});
}

BOOST_AUTO_TEST_CASE( test10 )
{
	testTokenStrings("newLineChar = '\\n';",
			{"newLineChar","=","'\\n'",";"});
}

// Below mentioned test case would generate error by C compiler.
// However, we should be able to get tokens for it.
BOOST_AUTO_TEST_CASE( test11 )
{
	testTokenStrings("fNameInitial = 'A ;",
			{"fNameInitial","=","",";"});
}

BOOST_AUTO_TEST_CASE( test12 )
{
	testTokenStrings("str = \"Hello World out there ; \n str++;",
			{"str","=","","str","++",";"});
}


