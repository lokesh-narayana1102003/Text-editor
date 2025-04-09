
#ifndef SPELLCHECK_H
#define SPELLCHECK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>
class spellcheck
{
	public:
		spellcheck();
		~spellcheck();
		std::string spellcheck::removePunctuation(const std::string& word);
		void spellcheck::readWordsFromCSV(std::set<std::string>& wordList);
        std::string spellcheck::textfilecontent();
        void spellcheck::misspelled(const std::string& filecontent); 
		
};

#endif // SPELLCHECK_H
