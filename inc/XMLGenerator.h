#ifndef XMLGENERATOR_H_
#define XMLGENERATOR_H_
#include <string>
#include "WordList.h"
#include "BST.h"

using namespace std;

//This class will be used to generate an XML document to the specified file.
class XMLGenerator
{
	public:
		//Destructor
		~XMLGenerator();

		//Constructor.
		XMLGenerator(string _startURL, WordList & _MasterWordList,
				BST<Page> & _PageHistory, string _outputFile, string _stopWordFile);

		//Submethod of print page, prints file
		void printFile();

		//Submethod of printFile, prints words.
		void printWords(ofstream & output);

		//Prints pages.
		void printPages(ofstream & output);

	private:
		//URL to print in output.
		string startURL;

		//Reference to the master wordlist
		WordList & MasterWordList;

		//Refererence to the visited pages.
		BST<Page> & PageHistory;

		//File to output to
		string outputFile;

		//Array of words to exclude on output
		string stopWordFile;
};

#endif  /* XMLGENERATOR_H_ */

