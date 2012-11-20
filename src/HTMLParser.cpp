#include "HTMLParser.h"

using namespace std;

	HTMLParser::HTMLParser(WordList & _WordList, URLQueue & _PQ):
			MasterWordList(_WordList), MasterURLQueue(_PQ), urlToParse(""),
				inHTML(false),inHead(false),inBody(false),inTitle(false),
					inH(false),inScript(false), title(""), possibleDescription("")
	{
	}

	void HTMLParser::PreAddChecks(string url, URL urlToAdd,
		StringURLResolver Resolver, URL _urlToParse)
	{
	if (boost::starts_with(url, "http://")
			|| boost::starts_with(url, "file:///"))
	{
		StringURLResolver resolver;
		string prefix = resolver.GeneratePrefix(urlToAdd.getURL());
		boost::algorithm::to_lower(prefix);
		string urlToReturn = urlToAdd.getURL();
		urlToReturn.erase(0, prefix.size());
		urlToReturn = prefix + urlToReturn;
		MasterURLQueue.enqueue(URL(urlToReturn));
	}
	else
		MasterURLQueue.enqueue(Resolver.resolveURL(_urlToParse, urlToAdd));
}
Page * HTMLParser::Parse(URL _urlToParse)
	{
		try
		{
			urlToParse = _urlToParse;
			Page * pageToReturn = new Page(urlToParse);
			URLInputStream stream(urlToParse.getURL()); HTMLTokenizer Tokenizer(&stream);
			StringURLResolver Resolver;
			while(Tokenizer.HasNextToken())
			{
				HTMLToken current_tok = Tokenizer.GetNextToken();
				if(current_tok.GetType() == COMMENT) continue; //If comment, skip.
				if(current_tok.GetType() == TAG_START) //Marks flags for when we see an opening tag.
				{
					string tag_value = current_tok.GetValue();
					StringUtil::ToLower(tag_value);

					MarkStartFlags(tag_value);

					if(tag_value == "a") //Extract, resolve, and add links.
					{
						string url = current_tok.GetAttribute("HREF");
						URL urlToAdd(url);

						//Before adding a URL, do some checks, clean URL up, then add.
						PreAddChecks(url, urlToAdd, Resolver, _urlToParse);
					}
					if(tag_value[0] == 'h' && isdigit(tag_value[1]))
						inH = true;
				}
				MarkEndFlags(current_tok); //Check current token to see if we are in title or body
				if(current_tok.GetType() == TEXT) //If it's text, send it off for processing
					processBlockOfText(current_tok.GetValue(), pageToReturn);
			}
			if(!pageToReturn->hasDescription()) //Pre-return check, see if title has 100 chars. Add if not
				pageToReturn->SetDescription(BuildPossibleDescription());
			return pageToReturn;
		}
		catch (CS240Exception & e) //If the page could not be downloaded, catch error. Do nothing.
		{
			cout << e.GetMessage() << endl;
		}
		return NULL;
	}

	void HTMLParser::MarkStartFlags(string tag_value)
	{
		if(tag_value == "html") inHTML = true;
		if(tag_value == "head")	inHead = true;
		if(tag_value == "title")inTitle = true;
		if(tag_value == "body")	inBody = true;
		if(tag_value == "script") inScript = true;
	}

	void HTMLParser::MarkEndFlags(HTMLToken & current_tok)
	{
		//Marks flags for when we see the closing tag.
		if(current_tok.GetType() == TAG_END)
		{
			string tag_value = current_tok.GetValue();
			StringUtil::ToLower(tag_value);

			if(tag_value == "html")	inHTML = false;
			if(tag_value == "head") inHead = false;
			if(tag_value == "title") inTitle = false;
			if(tag_value == "body") inBody = false;
			if(tag_value == "script") inScript = false;
			if(tag_value[0] == 'h' && isdigit(tag_value[1]))
				inH = false;
		}
	}

	void HTMLParser::processBlockOfText(string _text, Page * pageToReturn)
	{
		//If the current page has no description, set the title to either title or first h.
		if(!pageToReturn->hasDescription())
		{
			if(inTitle)
				pageToReturn->SetDescription(_text);
			if(inH)
				pageToReturn->SetDescription(_text);
		}

		//If in body, or title, and not in script, clean and add text to wordlist
		if(inBody || inTitle)
			if(!inScript)
				cleanAndAddText(_text);
	}

	string HTMLParser::BuildPossibleDescription()
	{
		string description;
		int loopCount = 0;
		int charCount = 0;

		//While total characters in description is less than 100
		while(charCount < 100)
		{
			//If encountered char is not a space, increment character count.
			if(!isspace(possibleDescription[loopCount]))
				charCount++;

			//Add the character - no matter what it is.
			description += possibleDescription[loopCount];

			//Increment count to go onto next character in text.
			loopCount++;

			//If the number of view characters equals the size of the possDescription, stop
			//Because there are no more possible characters to be added.
			if(loopCount == possibleDescription.size())
				break;
		}

		return description;
	}

	void HTMLParser::cleanAndAddText(string _text)
	{
		//Make a new stringstream.
		stringstream ss (stringstream::in | stringstream::out);

		//Empty word to be later added to the wordlist.
		string word;

		//Send _text over to the possible description building
		possibleDescription += _text;

		//Clean text for addiition to the word list
		for(int i=0; i<_text.length(); i++)
		{
			//If it's not alphanumeric, -, or _ , make it a space.
			if(!isalnum(_text[i]) && _text[i] != '-' && _text[i] != '_')
				_text[i] = ' ';

			//Turn all found characters to lowerspace.
			_text[i] = tolower(_text[i]);
		}

		//Add the cleaned _text to the string stream
		ss << _text;

		//Initilaize word to the first value from ss. Then keep adding til stop.
		ss >> word;

		//While ss has tokens left.
		while(ss)
		{
			//If the found word starts with an alphabetical character, add the entire word.
			if(isalpha(word[0]))
				MasterWordList.addWord(word, urlToParse);

			//Get next token from stringstream.
			ss >> word;
		}
	}

	bool HTMLParser::Test(ostream &os)
	{
		cout << "---------------TESTING HTMLPARSER.cpp-----------------" << endl;

	/*	URLQueue * myPageQueue = new URLQueue();

		WordList * myWordList = new WordList();

		//Build the parser
		HTMLParser * parser = new HTMLParser(*myWordList, *myPageQueue);

		string testUrl = "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/title.html";
		URL * urlToTest = new URL(testUrl);
		Page * returned_page = parser->Parse(*urlToTest);

		cout << returned_page->GetDescription() << endl;

		cout << myPageQueue->getSize() << endl;

		cout << myWordList->getSize() << endl;*/

		return true;
	}
