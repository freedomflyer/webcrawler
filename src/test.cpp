#include <iostream>
#include <string>
#include "BST.h"
#include "StopWords.h"
#include "HTMLParser.h"
#include "Occurence.h"
#include "URLQueue.h"
#include "StopWords.h"
#include "URL.h"
#include "Word.h"
#include "WordList.h"
#include "XMLGenerator.h"
#include "StringURLResolver.h"
#include "LinkedList.h"
#include "WebCrawler.h"

using namespace std;

//This is a driver for testing the WebCrawler.
int main(int argc, char *argv[])
{
	bool success = true;


	cout << "*********RUNNING WEBCRAWLER TEST*********" << endl;

	string url2("http://lightplanet.com/mormons/people/joseph_smith/visions.html");

	WebCrawler Crawler(url2);

	Crawler.crawl();
	Crawler.printOutput("output.xml", "stopwords2.txt");

	return 0;
}

