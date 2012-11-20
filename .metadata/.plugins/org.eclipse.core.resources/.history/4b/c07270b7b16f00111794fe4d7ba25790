#include "WebCrawler.h"

//Constructor. Initializes startURL, outputFile, and stopWordFile.
WebCrawler::WebCrawler(string _startURL)
{
	startURL = URL(_startURL);
}

WebCrawler::~WebCrawler()
{
	cout << "________________WEBCRAWLER DESTRUCTOR______________" << endl;
}

//This is the main driver method of the program. It will take user input,
//crawl a URL within it's scope, and output XML to a user-specified file.
void WebCrawler::crawl()
{
	//Creates a new URLQueue on the stack, and initializes it's first URL as the startURL
	URLQueue MasterURLQueue(&startURL, &PageHistory);

	while(!MasterURLQueue.isEmpty())
	{
		URL urlToParse = MasterURLQueue.dequeue();


		string urlToAdd = urlToParse.getURL();
		if (urlToAdd.find("#") != string::npos)
		{
			int pos = urlToAdd.find("#");
			urlToAdd.erase(pos, urlToAdd.size()-1);
		}

		Page tempPage(urlToAdd);

		if(PageHistory.Find(tempPage) == NULL)
		{
			HTMLParser parser(MasterWordList, MasterURLQueue);
			Page * returnedPage = parser.Parse(urlToParse);
			if(returnedPage != NULL)
			{
				if(PageHistory.Find(*returnedPage) == NULL)
					PageHistory.Insert(*returnedPage);
			}
			delete returnedPage;
		}//parser destructor parser is called
	}
}

void WebCrawler::printOutput(string _outputFile, string _stopWordFile)
{
	XMLGenerator xmlGen(startURL.getURL(), MasterWordList, PageHistory, _outputFile, _stopWordFile);
	xmlGen.printFile();
}
