#ifndef FINDREPLACE_H
#define FINDREPLACE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>

class findreplace
{
public:
    findreplace();
    ~findreplace();
    std::vector<std::string> splitIntoWords();
    std::string joinWords(const std::vector<std::string>& words, const std::string& wordToFind, const std::string& replacementWord);
    void editContent(const std::string& newContent);
};

#endif // FINDREPLACE_H
