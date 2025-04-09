
#include "spellcheck.h" 

spellcheck::spellcheck()
{
}

spellcheck::~spellcheck()
{
}
void spellcheck::misspelled(const std::string& filecontent){
     std::set<std::string> wordList;
     readWordsFromCSV(wordList);
     std::istringstream iss(filecontent);             
     std::vector<std::string> fileWords;            
     std::string word;            
     while (iss >> word) {           
           fileWords.push_back(removePunctuation(word));           
     }
     if (fileWords.empty()) {           
        std::cerr << "Error: No valid words found in text.txt!" << std::endl;             
        return;             
     }
     std::map<int, std::string> misspelledWords;             
     for (size_t i = 0; i < fileWords.size(); ++i) {       
         if (wordList.find(fileWords[i]) == wordList.end()) {
            misspelledWords[i] = fileWords[i];      
         }           
     }         
     if (misspelledWords.empty()) {
        std::cout << "All words are spelled correctly!" << std::endl;             
     } 
     else {     
          std::cout << "Misspelled words:" << std::endl;
          for (std::map<int, std::string>::iterator it = misspelledWords.begin(); it != misspelledWords.end(); ++it) {
              std::cout << it->second << std::endl;
          }
     }

}
std::string spellcheck::textfilecontent(){
            std::ifstream inputFile("text.txt");
            if (!inputFile.is_open()) {
                std::cerr << "Error: Could not open text.txt for reading!" << std::endl;
                return "";
            }
            std::string fileContent, line;
            while (std::getline(inputFile, line)) {
                  fileContent += line + " "; 
            }
            inputFile.close();          
            std::transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::tolower); 
            return fileContent;
}  

void spellcheck::readWordsFromCSV(std::set<std::string>& wordList) {
    std::ifstream file("dictionary.csv"); 
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file "<< std::endl;
        return;
    }
    std::string line, word;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        while (std::getline(stream, word, ',')) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            wordList.insert(word);
        }
    }
    file.close();
}
std::string spellcheck::removePunctuation(const std::string& word) {
    std::string cleanWord;
    for (size_t i = 0; i < word.size(); ++i) { 
        if (!std::ispunct(word[i])) { 
            cleanWord += word[i];
        }
    }
    return cleanWord;
}

 
