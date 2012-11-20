#ifndef STOPWORDS_H_
#define STOPWORDS_H_

#include <string>
#include <iostream>
#include <UnitTest.h>

using namespace std;

//This is a wrapper class to store the StopWords and includes
//some helper methods to aid in the general functioning of
//using StopWords.
class StopWords
{
	public:
		~StopWords();
		//Takes a fileName to read in the entire stopwords file,
		StopWords(string _fileName);

		//Checks to see if a certain string is a stopword.
		bool IsStopWord(string _possibleStopWord);

		//int CompareStrings (const void * a, const void * b);
		static bool Test(ostream &os);
	private:
		void InitializeStopWords(string _fileName);
		int GetNumStopWords(string _fileName);

		//The array of strings that the stopwords will be stored in.
		string * stopWords;
		int numStopWords;
};

#endif /* STOPWORDS_H_ */
