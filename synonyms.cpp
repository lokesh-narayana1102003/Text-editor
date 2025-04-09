
#include "synonyms.h" 

synonyms::synonyms()
{
}

synonyms::~synonyms()
{
}

std::string synonyms::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (std::string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}
std::string synonyms::toLower(std::string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
void synonyms::findSynonyms(std::string searchWord) {
    std::ifstream file("dictionary.csv");
    bool found = false;
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file "<< std::endl;
        return;
    }
    searchWord = toLower(trim(searchWord));
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string mainWordFromFile;
        size_t firstdelimiter = line.find(',');
        if (firstdelimiter != std::string::npos) {
           std::string mainWordFromFile = line.substr(0, firstdelimiter);
           std::string processedMainWord = toLower(trim(mainWordFromFile));
           if (processedMainWord == searchWord) {
                found = true;
                std::string synonymsStr;
                getline(ss, synonymsStr);
                std::stringstream ssSynonyms(synonymsStr);
                std::string synonym;
                std::vector<std::string> synonyms;
                while (getline(ssSynonyms, synonym, '#')) {
                    synonym = trim(synonym);
                    if (!synonym.empty()) {
                        synonyms.push_back(synonym);
                    }
                }
                size_t idx=synonyms[0].find(',');
                synonyms[0]=synonyms[0].substr(idx+1);
                std::cout << "Synonyms for '" << searchWord << "': "<<std::endl;
                for (size_t i = 0; i < synonyms.size()-1; i++) { 
                    std::cout << synonyms[i] <<std::endl;
                }
                std::cout << std::endl;
                break;
            }
        }
    }
    file.close();
    if (!found) {
        std::cout << "Word '" << searchWord << "' not found in the file." << std::endl;
    }
}


 
