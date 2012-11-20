#include <URLQueue.h>
#include <URL.h>

using namespace std;

URLQueue::URLQueue(URL * _startURL, BST<Page> * _PageHistory):PageHistory(_PageHistory)
{
	scope = generateScope(_startURL->getURL());
	urlList.Insert(*_startURL, NULL);
}

URLQueue::~URLQueue()
{
}

bool URLQueue::enqueue(URL _url)
{
	string urlToAdd = _url.getURL();
	if (urlToAdd.find("#") != string::npos)
	{
		int pos = urlToAdd.find("#");
		urlToAdd.erase(pos, urlToAdd.size()-1);
	}

	Page tempPage(urlToAdd);

	if(isInScope(urlToAdd) && isHTML(urlToAdd) && PageHistory->Find(tempPage) == NULL)
	{
		urlList.Insert(_url, NULL);
		return true;
	}

	return false;
}

bool URLQueue::isHTML(URL _url)
{
	int lastSlashPos = _url.getURL().rfind("/");
	string urlToCheck = _url.getURL();

	urlToCheck = urlToCheck.erase(0, lastSlashPos);

	if(urlToCheck[urlToCheck.length() - 1] == '/')
		return true;
	if(urlToCheck[urlToCheck.length() - 1] != '/' && urlToCheck.find(".") == string::npos)
		return true;
	if(urlToCheck.find(".") >= 0)
	{
		int periodPos = urlToCheck.find(".");
		urlToCheck = urlToCheck.erase(0, periodPos);

		if(boost::starts_with(urlToCheck, ".html") || boost::starts_with(urlToCheck, ".htm") ||
				boost::starts_with(urlToCheck, ".shtml") || boost::starts_with(urlToCheck, ".cgi") ||
					boost::starts_with(urlToCheck, ".jsp") || boost::starts_with(urlToCheck, ".asp") ||
						boost::starts_with(urlToCheck, ".aspx") || boost::starts_with(urlToCheck, ".php") ||
							boost::starts_with(urlToCheck, ".pl") || boost::starts_with(urlToCheck, ".cfm"))
			return true;
	}
	return false;
}

string URLQueue::generateScope(string _startURL)
{
	int lastSlashPos = _startURL.rfind("/");
	return _startURL.erase(lastSlashPos+1, _startURL.length());
}

bool URLQueue::isInScope(URL _incomingUrl)
{
	return boost::starts_with(_incomingUrl.getURL(), scope);
}

URL URLQueue::dequeue()
{
	LLNode<URL> * node = urlList.GetLast();
	URL urlToReturn = node->GetValue();
	urlList.Remove(node);
	return urlToReturn;
}

bool URLQueue::isEmpty()
{
	return urlList.IsEmpty();
}

int URLQueue::getSize()
{
	return urlList.GetSize();
}

string URLQueue::getScope()
{
	return scope;
}

bool URLQueue::Test(ostream &os)
{
	bool success = false;

	cout << "---------------TESTING URLQueue.cpp-----------------" << endl;

	BST<Page> * pageHistory = new BST<Page>;
	URL * startURL = new URL("http://www.google.com/cs240/index.html");

	URLQueue uq(startURL,pageHistory);

	os << "The Scope Is " << uq.getScope() << endl;
	TEST(uq.getScope() == "http://www.google.com/cs240/");

	TEST(!uq.isInScope(URL("http://www.google.com/")));
	TEST(uq.isInScope(URL("http://www.google.com/cs240/hello/index.html")));
	TEST(!uq.isInScope(URL("http://www.google.com/index.html")));

	TEST(!uq.isInScope(URL("Http://cs-OnLine.Cs.byu.edu/cs240/")));

	TEST(uq.isHTML(URL("http://www.google.com/test/index.html")));
	TEST(uq.isHTML(URL("http://www.google.com/test/")));
	TEST(uq.isHTML(URL("http://www.google.com/test")));

	TEST(uq.isHTML(URL("http://www.espn.com/football/")));
	TEST(uq.isHTML(URL("http://www.espn.com/football/scores")));
	TEST(uq.isHTML(URL("http://www.espn.com/football/scores/index.html")));

	TEST(!uq.isHTML(URL("http://www.espn.com/football/scores/index.xml")));
	TEST(uq.isHTML(URL("http://www.espn.com/")));
	TEST(!uq.isHTML(URL("http://www.espn.com/testing.AWL")));

	//NEW QUEUE
	BST<Page> * pageHistory2 = new BST<Page>;
	URL * startURL2 = new
			URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFour.htm");
	URLQueue uq2(startURL2, pageHistory2);

	TEST(uq2.isInScope(URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/title.html")));
	TEST(uq2.isHTML(URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/title.html")));

	delete pageHistory2;
	delete pageHistory;
	delete startURL;
	delete startURL2;
	return success;
}


