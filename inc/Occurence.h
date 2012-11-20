#ifndef OCCURENCE_H_
#define OCCURENCE_H_
#include <string>
#include <URL.h>

using namespace std;

//This class will store a url and an accompanying count which
//represents the number of times a particular word has occured
//in this particular URL. It will eventually be printed out
//under the <word> tag
class Occurence
{
	public:
		//Constructor
		Occurence(URL _url);

		//Constructor
		Occurence(const Occurence &_o);

		//Get number of occurences in word.
		int getOccurenceCount();

		//Get url of the occurence
		URL getURL();

		//When a word is seen on a certain page, increment the
		//number of times.
		void incrementOccurenceCount();

		//Comparison functions
		bool operator== (const Occurence & other)  const;
		bool operator< (const Occurence & other)  const;
		bool operator> (const Occurence & other)  const;

	private:
		//The url that the occurence of a word is found on
		URL url;

		//Number of times a word appears on a given url
		int occurenceCount;
};

#endif /* OCCURENCE_H_ */
