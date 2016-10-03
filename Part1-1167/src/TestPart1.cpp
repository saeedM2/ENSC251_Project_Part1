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
//
// Name        : TestPart1.cpp
// Description : Course Project Part 1 (Test cases)
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
	testTokenStrings("i++-j;",
			{"i","++","-","j",";"});
}



BOOST_AUTO_TEST_CASE( test6 )
{
	testTokenStrings("#define MY_DEFINE \n int i;",
										{"int","i",";"});
}
BOOST_AUTO_TEST_CASE( test7x )
{
    // the comment below shows what's in memory (but with extra whitespace
    //      to align things as much as possible) delimited by '[' and ']' and
    //      using ? to indicate control characters:
    //                 [#define MYDEFINE ? ?  str    =     "x"      "+"      ""     ; ]
 testTokenStrings(  "#define MYDEFINE \r\n str    =    \"x\"    \"+\"    \"\"    ; ",
            {  "str", "=", "\"x\"", "\"+\"", "\"\"", ";"});
}

// below demonstrates a bug in one of our libraries

/*
BOOST_AUTO_TEST_CASE( test7bug )
{
    // the comment below shows what's in memory (but with extra whitespace
    //      to align things as much as possible) delimited by '[' and ']' and
    //      using ? to indicate control characters:
    //                 [#define MYDEFINE ? ?  str    =     "\""        "+"      ""     ; ]
	testTokenStrings(  "#define MYDEFINE \r\n str    =    \"\\\"\"    \"+\"    \"\"    ; ",
										  {  "str", "=", "\"\\\"\"", "\"+\"", "\"\"", ";"});
}
*/



BOOST_AUTO_TEST_CASE( test8 )
{
	//std::stoi( str ) used to convert string to int type
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
	testTokenStrings("str = \"Hello World out there;  \n str++;",
			{"str","=","","str","++",";"});
}

BOOST_AUTO_TEST_CASE( test13 )
{
	testTokenStrings("i-=3;",
			{"i","-=","3",";"});
}

BOOST_AUTO_TEST_CASE( test14 )
{
	testTokenStrings("Register_X &= 0b00001111;",
			{"Register_X","&=","0b00001111",";"});
}

BOOST_AUTO_TEST_CASE( test15 )
{
	testTokenStrings("Register_X |= 0xFF;",
			{"Register_X","|=","0xFF",";"});
}

BOOST_AUTO_TEST_CASE( test16 )
{
	testTokenStrings("Address >>= 0x0C;",
			{"Address",">>=","0x0C",";"});
}

BOOST_AUTO_TEST_CASE( test17 )
{
	testTokenStrings("Address>>=0x0C;",
			{"Address",">>=","0x0C",";"});
}

BOOST_AUTO_TEST_CASE( test18 )
{

	testTokenStrings("sumFloat = 314159E-5 + 12345e-3 + 12345e-3 ;",
			{"sumFloat","=","314159E-5","+","12345e-3","+","12345e-3",";"});
}

BOOST_AUTO_TEST_CASE( test19 )
{
	testTokenStrings("Register_X&=0b00001111;",
			{"Register_X","&=","0b00001111",";"});
}

BOOST_AUTO_TEST_CASE( test20)
{
	testTokenStrings("*pointer=0;",
			{"*","pointer","=","0",";"});
}
BOOST_AUTO_TEST_CASE( test21 )
{
	testTokenStrings("Register_X =| 0xFF;",
			{"Register_X","=|","0xFF",";"});
}
BOOST_AUTO_TEST_CASE( test22 )
{
	testTokenStrings("if(x==2) { }",
			{"if","(","x","==","2",")","{","}"});
}
BOOST_AUTO_TEST_CASE( test23 )
{
	testTokenStrings("while(x != 2)",
			{"while","(","x","!=","2",")"});
}
BOOST_AUTO_TEST_CASE( test24 )
{
	testTokenStrings("char* str; str = \"!!!!!!.\";"
			,{"char", "*","str",";", "str","=","\"!!!!!!.\"",";"});
}
BOOST_AUTO_TEST_CASE( test25 )
{
	testTokenStrings("if(x==2) { }",
			{"if","(","x","==","2",")","{","}"});
}
BOOST_AUTO_TEST_CASE( test26 )
{
	testTokenStrings("index = 1.575E1;",
			{"index","=","1.575E1",";"});
}

BOOST_AUTO_TEST_CASE( test27)
{

	testTokenStrings("sumFloat=314159E-5+12345e-3+12345e-3 ",
			{"sumFloat","=","314159E-5","+","12345e-3","+","12345e-3"});
}

BOOST_AUTO_TEST_CASE( test28)
{

	testTokenStrings("cout << ( i > j ? i : j ) << \" is greater.\" << endl; ",
			{"cout","<<","(","i",">","j","?","i",":","j",")","<<","\" is greater.\"","<<","endl",";"});
}

BOOST_AUTO_TEST_CASE( test29)
{

	testTokenStrings("if(value ==2 || value ==3) { }",
			{"if","(","value","==","2","||","value","==","3",")","{","}"});
}
BOOST_AUTO_TEST_CASE( test30)
{

	testTokenStrings("cout<<(i>j?i:j)<<\" is greater.\"<<endl;",
			{"cout","<<","(","i",">","j","?","i",":","j",")","<<","\" is greater.\"","<<","endl",";"});
}
BOOST_AUTO_TEST_CASE( test31 )
{
	testTokenStrings("if(x==2){}",
			{"if","(","x","==","2",")","{","}"});
}
BOOST_AUTO_TEST_CASE( test32 )
{
	testTokenStrings("Address <<= 0x0C;",
			{"Address","<<=","0x0C",";"});
}
BOOST_AUTO_TEST_CASE( test33 )
{
	testTokenStrings("object.method(254);",
			{"object",".","method","(","254",")",";"});
}
BOOST_AUTO_TEST_CASE( test34 )
{
	testTokenStrings("int Special_check(string element,int index);",
			{"int","Special_check","(","string","element",",","int","index",")",";"});
}

