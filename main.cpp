#include <cstdlib>
#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> 
#include "viewtext.h"
#include "spellcheck.h"
#include "findreplace.h"
#include "synonyms.h"
#include "dictionaryops.h"
#include "modifycontent.h"
#include<cstdlib>
using namespace std;
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
};
int main()
{
    std::ofstream file("text.txt");
    if (file.is_open()) {
        std::string line;
        std::cout << "Enter the content:"<<endl;
        while (true) {
            std::getline(std::cin, line);
            if (line.empty()) {
                break; 
            }
            file << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Error\n";
        return 1;
    }
    int choice;
    do {
        
        std::cout<<"******************************MENU*******************************"<<std::endl;
        std::cout<<"*                        1)Spell Check                          *"<<std::endl;
        std::cout<<"*                        2)Find & Replace                       *"<<std::endl;
        std::cout<<"*                        3)Find Synonyms                        *"<<std::endl;
        std::cout<<"*                        4)View Text                            *"<<std::endl;
        std::cout<<"*                        5)Add Word To Dictionary               *"<<std::endl;
        std::cout<<"*                        6)Edit content                         *"<<std::endl;
        std::cout<<"*                        7)Exit                                 *"<<std::endl;
        std::cout<<"*****************************************************************"<<std::endl;
        std::cout<<"Enter a choice:"<<std::endl; 
        std::cin >> choice;
        std::cout<<std::endl;
        std::cout<<"*****************************************************************"<<std::endl;
        switch (choice) {
            case 1:{
                clearScreen();
                std::cout<<"1)Spell Check"<<std::endl;
                std::cout<<"*****************************************************************"<<std::endl;
                spellcheck sc;
                std:string filecontent=sc.textfilecontent();
                sc.misspelled(filecontent);       
                break;
            }
            case 2:{
                 clearScreen();
                 std::cout<<"2)Find & Replace"<<std::endl;
                 std::cout<<"*****************************************************************"<<std::endl;
                 std::string wordToFind;
                 std::string replacementWord;
                 std::string paragraph;
                findreplace fr;             
                cout << "Enter the word to find: ";
                getline(cin >> ws, wordToFind);
                cout << "Enter the replacement word: ";
                getline(cin >> ws, replacementWord);
                vector<string> words = fr.splitIntoWords();
                string newContent = fr.joinWords(words,wordToFind,replacementWord);
                newContent += "\n"; 
                fr.editContent(newContent);
                break;
            }
            case 3:{
                 clearScreen();
                 std::cout<<"3)Find Synonyms"<<std::endl;
                 std::cout<<"*****************************************************************"<<std::endl;
                 std::cout << "Enter the word to find synonyms for: ";
                 std::string searchWord;
                 std::cin.ignore();
                 std::getline(std::cin, searchWord);
                 synonyms sys;
                 sys.findSynonyms(searchWord);
                 break;
            }
            case 4:{
                 clearScreen();
                 std::cout<<"4)View Text"<<endl;
                std::cout<<"*****************************************************************"<<std::endl;
                 viewText vt;
                 std::cout<<"The content of the file is"<<endl;
                 vt.printcontent();

                 break;
            }
            case 5:{
                 clearScreen();
                 std::cout<<"5)Add Word To Dictionary"<<std::endl;
                 std::cout<<"*****************************************************************"<<std::endl;
                 std::cout << "Enter the main word: "<<std::endl;
                 std::cin.ignore();
                 std::string newWord;
                 std::getline(std::cin,newWord);
                 std::cout<<std::endl;
                 std::cout << "Enter synonyms for the word (separated by commas):";
                 std::string synonymsInput;
                 std::getline(std::cin, synonymsInput);
                 dictionaryops dirops;
                 dirops.addWordToCSV(newWord,synonymsInput);

                 break;
            }
            case 6:{
                 clearScreen();
                 std::cout<<"6)Edit text file"<<std::endl;
                 std::cout<<"*****************************************************************"<<std::endl;
                 modifyContent mc;
                 mc.editFile();
                 break;
            }
            case 7:{
                 clearScreen();
                std::ofstream ofs;
                ofs.open("text.txt", std::ofstream::out | std::ofstream::trunc);
                ofs.close();
                std::cout << "Exiting............."<<std::endl;
                break;
            }
            default:
                clearScreen();
                std::cout << "Invalid choice.........\n";
                break;
        }
    }while (choice != 7);
    system("PAUSE");
    return 0;
}
