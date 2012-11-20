#ifndef STRINGURLRESOLVER_H_
#define STRINGURLRESOLVER_H_
#include <boost/algorithm/string/predicate.hpp>
#include "URL.h"
#include <iostream>
#include <LinkedList.h>
#include <boost/tokenizer.hpp>
#include <string>
#include <UnitTest.h>
#include <boost/algorithm/string.hpp>


namespace std
{
	//This class will handle resolving URLs from a base and relative URL.
	class StringURLResolver
	{
		public:
			StringURLResolver();
			URL resolveURL(URL _baseURL, URL _relativeURL);
			string GeneratePrefix(string _url);
			void tokenizeString(string _fragment, LinkedList<string> & _tokenList);
			string calculateDotFragment(string _fragment, string _relativeURL);
			string calculateFragment(string _fragment, string _relativeURL);
			static bool Test(ostream &os);
	};

} /* namespace std */
#endif /* STRINGURLRESOLVER_H_ */
