#ifndef PAGEQUEUE_H_
#define PAGEQUEUE_H_

#include <string>
#include "Page.h"
#include "LinkedList.h"
#include "URL.h"
#include <boost/algorithm/string/predicate.hpp>

using namespace std;

//This is a wrapper class for a LinkedList of pages. It provides enqueue and dequeue functionality.
class URLQueue
{
	public:
		//Default constructor.
		URLQueue(URL * _startURL, BST<Page> * _PageHistory);
		~URLQueue();
		bool isEmpty();
		URL dequeue();
		bool enqueue(URL _url);
		static bool Test(ostream &os);
		int getSize();
		string getScope();
		string generateScope(string _startURL);
		bool isInScope(URL _incomingUrl);
		bool isHTML(URL _url);
	private:
		BST<Page> * PageHistory;
		string scope;

		//Stores all the URLs waiting to be processed
		LinkedList<URL> urlList;
};

#endif /* PAGEQUEUE_H_ */
