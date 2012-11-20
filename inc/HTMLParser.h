#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <string>
#include <iostream>
#include <sstream>
#include "WordList.h"
#include "UnitTest.h"
#include "LinkedList.h"
#include "HTMLTokenizer.h"
#include "Word.h"
#include "URL.h"
#include "Page.h"
#include "URLQueue.h"
#include <ctype.h>
#include "boost/regex.hpp"
#include "StringUtil.h"
#include <boost/algorithm/string/predicate.hpp>
#include "StringURLResolver.h"
#include "CS240Exception.h"

using namespace std;

//This class Parses all HTML of a document
class HTMLParser
{
	public:
	//COnstructor
	HTMLParser(WordList& _WordList, URLQueue& _PQ);

	//Mark end of flags
	void MarkEndFlags(HTMLToken& current_tok);

	//Mark start of flags
	void MarkStartFlags(string tag_value);

	//Parse a page
	Page* Parse(URL urlToParse);

	//Parse for words
	LinkedList<Word> ParseForWords();

	//Parse all links
	LinkedList<URL> ParseForLinks();

	//Pasre the description
	string ParseForDescription();

	//Process a block of text
	void processBlockOfText(string _text, Page* pageToReturn);

	//Clean and add text to the word list.
	void cleanAndAddText(string _text);

	//Testing functions
	static bool Test(ostream& os);

	//Make a possible description for this
	string BuildPossibleDescription();

	//Before adding word to list, do some checks.
	void PreAddChecks(string url, URL urlToAdd, StringURLResolver Resolver,
			URL _urlToParse);

private:
	URL urlToParse;
	WordList& MasterWordList;
	URLQueue& MasterURLQueue;
	bool inHTML;
	bool inHead;
	bool inBody;
	bool inTitle;
	bool inH;
	bool inScript;
	bool inA;
		string title;
		string possibleDescription;
};

#endif /* HTMLPARSER_H_ */
