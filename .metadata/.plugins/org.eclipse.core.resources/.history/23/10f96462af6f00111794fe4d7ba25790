#include "StopWords.h"
#include <stdlib.h>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;

//Constructor. Populates stopWords and prepares sorting numbers.
StopWords::StopWords(string _fileName)
{
	numStopWords = GetNumStopWords(_fileName);
	InitializeStopWords(_fileName);
}

StopWords::~StopWords()
{
	delete[] stopWords;
}

void StopWords::InitializeStopWords(string _fileName)
{
	    stopWords = new string[numStopWords];

		ifstream infile;
		infile.open(_fileName.c_str());

		int loop_counter = 0;
		while(!infile.eof()) // To get you all the lines.
		{
			string STRING;
			getline(infile,STRING); // Saves the line in STRING.

			stopWords[loop_counter] = STRING;

			loop_counter++;
		}
		infile.close();
}

int StopWords::GetNumStopWords(string _fileName)
{
	  ifstream myfile;
	  myfile.open(_fileName.c_str());

	  int loop_count_for_line_number = 0;
	  if (myfile.is_open())
	  {
		while(myfile.good())
		{
		  char my_string[2048];
		  myfile.getline(my_string, sizeof(my_string));
		  loop_count_for_line_number++;
		}
		myfile.close();
	  }
	  else
		  cout << "Unable to open file";

	  return loop_count_for_line_number;
}

int CompareStrings (const void * a, const void * b)
{
	  if ( *(string*)a >  *(string*)b ) return 1;
	  if ( *(string*)a == *(string*)b ) return 0;
	  if ( *(string*)a <  *(string*)b ) return -1;
}

bool StopWords::IsStopWord(string _possibleStopWord)
{
	string * pItem;

	pItem = (string*) bsearch(&_possibleStopWord, stopWords, numStopWords, sizeof (string), CompareStrings);

	return (pItem != NULL);
}

bool StopWords::Test(ostream &os)
{
	bool success = true;
	os << "---------Testing StopWords.cpp----------" << endl;

	StopWords words("stopwords.txt");

	//Should contain
	TEST(words.IsStopWord("a"));
	TEST(words.IsStopWord("their"));
	TEST(words.IsStopWord("languages"));
	TEST(words.IsStopWord("sharp"));
	TEST(words.IsStopWord("z"));

	//Should NOT contain
	TEST(!words.IsStopWord("asdfasdf"));
	TEST(!words.IsStopWord(""));

	return success;
}
