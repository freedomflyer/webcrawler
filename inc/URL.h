#ifndef URL_H_
#define URL_H_

#include <string>

using namespace std;

//This class is a wrapper class for a URL string. We include this class simply for readability
//throughout the program. However, it will also aid in further extending the program should that
//be later decided.
class URL
{
	public:
		//Constructor.
		URL(string _incomingURL);

		//Construcotr
		URL();

		//Get the URL
		const string getURL()
		{
			return url;
		}

		//Testing function
		static bool Test(ostream & os);

		string ResolveRelative(string _relativeURL);

		bool operator== (const URL & other) const;
		bool operator< (const URL & other) const;
		bool operator> (const URL & other) const;
	private:

		//URL of the URL
		string url;

		//Contains the scope of the crawling process.
		string URLScope;
};

#endif /* URL_H_ */
