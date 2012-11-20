#include "StringURLResolver.h"

namespace std
{
	//Default Constructor
	StringURLResolver::StringURLResolver()
	{
	}

	//Generate the prefix of a url based off the the given url.
	string StringURLResolver::GeneratePrefix(string _url)
	{
		if(boost::algorithm::starts_with(_url, "http://"))
		{
			  LinkedList<string> tokenList;
			  string str = _url;
			  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
			  boost::char_separator<char> sep("/");
			  tokenizer tokens(str, sep);

			  for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
			  {
				  string stringToAdd = *tok_iter;
				  tokenList.Insert(stringToAdd, NULL);
			  }
			  return "http://" + tokenList.Get(tokenList.GetSize()-2) + "/";
		}
		else if(boost::algorithm::starts_with(_url, "file:///"))
			return "file:///";
		else
			return NULL;
	}

	//Tokenize a given string and insert it into a LinkedList reference.
	void StringURLResolver::tokenizeString(string _fragment, LinkedList<string> & _tokenList)
	{
		string str = _fragment;
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> sep("/");
		tokenizer tokens(str, sep);

		//Count the number of directories to swipe off, and populate the linked list with tokens
		for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
		{
			string stringToAdd = *tok_iter;
			_tokenList.Insert(stringToAdd, NULL);
		}
	}


	//If the URLs start with periods, resolve them together and return the result.
	string StringURLResolver::calculateDotFragment(string _fragment, string _relativeURL)
	{
		//Prep the fragment to add the relativeURL onto it.
		int lastSlashPos = _fragment.rfind('/');
		_fragment.erase(lastSlashPos+1,_fragment.length());

		int numDoubleDots = 0;
		LinkedList<string> tokenList;
		string str = _relativeURL;
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> sep("/");
		tokenizer tokens(str, sep);

		//Count the number of directories to swipe off, and populate the linked list with tokens
		for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
		{
			if(*tok_iter == "..")
				numDoubleDots++;
			else if(*tok_iter != ".." && *tok_iter != ".")
			{
				string stringToAdd = *tok_iter;
				tokenList.Insert(stringToAdd, NULL);
			}
		}

		string returnFragment = "";
		for(int i = (tokenList.GetSize()-1); i >= 0; i--)
		{
			if(i >= 1)
				returnFragment += tokenList.Get(i) + "/";
			else
				returnFragment += tokenList.Get(i);
		}
		LinkedList<string> tokenHolder;
		tokenizeString(_fragment, tokenHolder);

		//If there are too many directories to remove, return normal returnFrag
		if(numDoubleDots >= tokenHolder.GetSize())
			return returnFragment;
		else //Or, we can just take off the right amount
		{
			//cout << "num double dots " << numDoubleDots << endl;
			string baseURLFragment = "";
			for( int j = tokenHolder.GetSize()-1; j >= numDoubleDots; j-- )
			{
				//cout << "adding " << tokenHolder.Get(j) << endl;
				baseURLFragment += (tokenHolder.Get(j) + "/");
			}
			return baseURLFragment + returnFragment;
		}
	}

	//Calculate the fragment part of a URL based on a fragment and the relative URL.
	string StringURLResolver::calculateFragment(string _fragment, string _relativeURL)
	{
		if(_relativeURL[0] == '#') //If the URL starts witih a #
			return _fragment;
		else if(_relativeURL[0] == '/') //If the URL starts witih a /
			return _relativeURL.erase(0,1);
		else if(_relativeURL[0] == '.') //If the URL starts witih a .
			return calculateDotFragment(_fragment, _relativeURL);
		else //relative url starts with a letter
		{
			int lastSlashPos = _fragment.rfind('/');
			_fragment.erase(lastSlashPos+1,_fragment.length());
			return _fragment + _relativeURL;
		}
	}

	//Primary function of class. Resolves a URL relative to the base URL.
	URL StringURLResolver::resolveURL(URL _baseURL, URL _relativeURL)
	{
		//Check to see if the relative URL is empty. In such case,
		//return the _baseURL.
		if(_relativeURL.getURL() == "")
			return _baseURL;

		//Initialize strings to be used.
		string theURL = _baseURL.getURL();
		string laterRel = _relativeURL.getURL();
		string urlPrefix = GeneratePrefix(theURL);

		//This is the "rest of the url" after the prefix has been taken away.
		theURL.erase(0, urlPrefix.length());

		//If the URL doesn't end in a file name add an ending slash.
		if(theURL.find(".") < 0)
			if(theURL[theURL.length()-1] != '/')
				theURL += "/";

		//Create the fragment to add on to the net_loc. ToLower() it, and return.
		string fragment = calculateFragment(theURL, _relativeURL.getURL());
		boost::algorithm::to_lower(urlPrefix);
		string finishedURL =  urlPrefix + fragment;

		return URL(finishedURL);
	}

	bool StringURLResolver::Test(ostream &os)
	{
		bool success;
		cout << "---------------TESTING StringURLResolver.cpp-----------------" << endl;

		StringURLResolver resolver;

		TEST(resolver.resolveURL(URL("file:///news/financial/index.html"),
				URL("/images/nasdaq.jpg")).getURL() == "file:///images/nasdaq.jpg");
		TEST(resolver.resolveURL(URL("http://www.cnn.com/news/financial/index.html"),
				URL("/images/nasdaq.jpg")).getURL() == "http://www.cnn.com/images/nasdaq.jpg");

		TEST(resolver.resolveURL(URL("file:///www.cnn.com/news/financial/index.html"),
				URL("./images/nasdaq.jpg")).getURL() == "file:///www.cnn.com/news/financial/images/nasdaq.jpg");
		TEST(resolver.resolveURL(URL("http://www.cnn.com/news/financial/index.html"),
				URL("./images/nasdaq.jpg")).getURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");

		TEST(resolver.resolveURL(URL("file:///www.cnn.com/news/financial/index.html"),
				URL("../images/nasdaq.jpg")).getURL() == "file:///www.cnn.com/news/images/nasdaq.jpg");
		TEST(resolver.resolveURL(URL("http://www.cnn.com/news/financial/index.html"),
				URL("../images/nasdaq.jpg")).getURL() == "http://www.cnn.com/news/images/nasdaq.jpg");

		TEST(resolver.resolveURL(URL("file:///news/index.html"),
				URL("#HEADLINES")).getURL() == "file:///news/index.html#HEADLINES");
		TEST(resolver.resolveURL(URL("http://www.cnn.com/news/index.html"),
				URL("#HEADLINES")).getURL() == "http://www.cnn.com/news/index.html#HEADLINES");

		TEST(resolver.resolveURL(URL("file:///news/financial/index.html"),
				URL("images/nasdaq.jpg")).getURL() == "file:///news/financial/images/nasdaq.jpg");

		TEST(resolver.resolveURL(URL("http://www.cnn.com/news/financial/index.html"),
				URL("images/nasdaq.jpg")).getURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");

		TEST(resolver.resolveURL(
				URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFour.htm"),
					URL("title.html")).getURL() ==
							"http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/title.html");

		TEST(resolver.resolveURL(
				URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec="),
					URL("scale.php?sec=tortoise")).getURL() ==
							"http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=tortoise");

		TEST(resolver.resolveURL(URL("http://students.cs.byu.edu/"
				"~cs240ta/crawler_tests/crawler/testFive.html"),
					URL("scale.php?sec=")).getURL() == "http://students.cs.byu.edu/"
						"~cs240ta/crawler_tests/crawler/scale.php?sec=");

		//cout <<  resolver.resolveURL(URL("http://students.cs.byu.edu/
//			~cs240ta/crawler_tests/crawler/testFive.html"), URL("scale.php?sec=")).getURL() << endl;
		//cout <<  resolver.resolveURL(URL("http://students.cs.byu.edu/
//				~cs240ta/crawler_tests/crawler/testTwo.html"), URL("#hook")).getURL() << endl;
		//cout <<  resolver.resolveURL(URL("http://students.cs.byu.edu/
//				~cs240ta/crawler_tests/crawler/testTwo.html#hook"), URL("#hook")).getURL() << endl;

		return success;
	}
}
/* namespace std */
