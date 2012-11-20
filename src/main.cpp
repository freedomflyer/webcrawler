#include <iostream>
#include "WebCrawler.h"
#include "Word.h"
#include "WordList.h"
#include "Page.h"
#include "UnitTest.h"
#include "StringURLResolver.h"
using namespace std;

//This method is the main driver behind the WebCrawler, and takes
//<start-url> <output-file> <stopword-file>
int main(int argc, char *argv[])
{
	if(argc == 4)
	{
		WebCrawler Crawler(argv[1]);
		Crawler.crawl();
		Crawler.printOutput(argv[2], argv[3]);
	}
	else
		cout << "USAGE: <start-url> <output-file> <stopword-file>" << endl;

	return 0;
}
