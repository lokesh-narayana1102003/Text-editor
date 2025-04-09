
#include "dictionaryops.h" // class's header file

dictionaryops::dictionaryops()
{
}
dictionaryops::~dictionaryops()
{
}
void dictionaryops::addWordToCSV(const std::string& word, const std::string& synonymsInput) {
     std::vector<std::string> newSynonyms;
     std::stringstream ss(synonymsInput);
     std::string synonym;
     while (std::getline(ss, synonym, ',')) {
           size_t firstNonSpace = synonym.find_first_not_of(" ");
           if (std::string::npos != firstNonSpace) {
              synonym = synonym.substr(firstNonSpace);
           }
           size_t lastNonSpace = synonym.find_last_not_of(" ");
           if (std::string::npos != lastNonSpace) {
              synonym = synonym.substr(0, lastNonSpace + 1);
           }
           if (!synonym.empty()) {
              newSynonyms.push_back(synonym);
           }
     }
    std::ofstream file("dictionary.csv",std::ios::app); 
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }
    file << word;
    if (!newSynonyms.empty()) {
        file << ",";
        for (size_t i = 0; i < newSynonyms.size(); ++i) {
            file << newSynonyms[i];
            if (i < newSynonyms.size() - 1) {
                file << "#";
            }
        }
    }
    file << "#";
    file << std::endl; 
    file.close();
    std::cout << "Word and synonyms added to dictionary file"<< std::endl;
}

   
 
