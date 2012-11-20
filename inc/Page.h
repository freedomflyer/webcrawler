#ifndef PAGE_H_
#define PAGE_H_

#include "BST.h"
#include "URL.h"
#include <string>

using namespace std;

//This class will store a page description, as well as a URL of that page.
//It will be printed during output.
class Page
{
	public:
		//Constructor. Initializes the URL and the description of a page.
		Page(URL _url, string _description):url(_url),
			description(_description), doesItHaveDescription(false)
		{
		}

		//Constructor
		Page(URL _url):url(_url), description(""), doesItHaveDescription(false)
		{
		}

		//Return URL object of the page.
		URL getURL();

		//Set the description of the page.
		void SetDescription(string _description);

		//Get the description. Read only.
		string GetDescription();

		//Check to see if the description has been set.
		bool hasDescription();

		//Comparison functions.
		bool operator== (const Page & other) const;
		bool operator< (const Page & other) const;
		bool operator> (const Page & other) const;

	private:
		//The description of the page that the parser returns.
		string description;

		//The URL of the page.
		URL url;

		bool doesItHaveDescription;
};

#endif /* PAGE_H_ */
