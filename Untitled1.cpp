#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map> // Use std::map instead of std::unordered_map
using namespace std;

// Function to create the word index from a CSV file (index as CSV)
bool createWordIndexCSV(const std::string& csvFile, const std::string& indexFile) {
    map<string, vector<string>> wordIndex; // Use std::map

    ifstream infile(csvFile);
    if (!infile.is_open()) {
        cerr << "Error: Could not open CSV file " << endl;
        return false;
    }

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue; // Skip empty lines.
        stringstream ss(line);
        string word, synonymsStr;

        if (getline(ss, word, ',')) {
            if (getline(ss, synonymsStr)) {
                vector<string> synonyms;
                stringstream synonymsSs(synonymsStr);
                string synonym;
                while (getline(synonymsSs, synonym, '#')) {
                    synonyms.push_back(synonym);
                }

                wordIndex[word] = synonyms;
                for (map<string,vector<string>>::const_iterator it = wordIndex.begin(); it != wordIndex.end(); ++it) { //Use iterator for old compiler.
                  for (string const& syn : it->second) {
                    wordIndex[syn] = it -> second;
                  }
                }
            } else {
                wordIndex[word] = vector<string>(); // Word with no synonyms.
            }
        }
    }
    infile.close();

    ofstream outfile(indexFile);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open index file " << endl;
        return false;
    }

    // Write the index to the CSV file
    for (map<string, vector<string>>::const_iterator it = wordIndex.begin(); it != wordIndex.end(); ++it) { //Use iterator for old compiler.
        outfile << it->first << ",";
        for (size_t i = 0; i < it->second.size(); ++i) {
            outfile << it->second[i];
            if (i < it->second.size() - 1) {
                outfile << "#";
            }
        }
        outfile << endl;
    }

    outfile.close();

    cout << "Index file created successfully." << endl;
    return true;
}

// Function to lookup a word in the CSV index file
vector<string> lookupWordCSV(const std::string& searchWord, const std::string& indexFile) {
    ifstream infile(indexFile);
    if (!infile.is_open()) {
        cerr << "Error: Could not open index file " << endl;
        return {};
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string word, synonymsStr;

        if (getline(ss, word, ',')) {
            if (word == searchWord) {
                vector<string> synonyms;
                if (getline(ss, synonymsStr)) {
                    stringstream synonymsSs(synonymsStr);
                    string synonym;
                    while (getline(synonymsSs, synonym, '#')) {
                        synonyms.push_back(synonym);
                    }
                }
                return synonyms;
            }
        }
    }
    infile.close();
    return {}; // Word not found
}

int main() {
    string csvFilename = "dictionary.csv";
    string indexFilename = "test.csv";

    if (createWordIndexCSV(csvFilename, indexFilename)) {
        string searchTerm = "happy";
        vector<string> result = lookupWordCSV(searchTerm, indexFilename);

        if (!result.empty()) {
            cout << "Synonyms for '" << searchTerm << "': ";
            for (const auto& syn : result) {
                cout << syn << " ";
            }
            cout << endl;
        } else {
            cout << "'" << searchTerm << "' not found in the index." << endl;
        }

        searchTerm = "joyful";
        result = lookupWordCSV(searchTerm, indexFilename);

        if (!result.empty()) {
            cout << "Synonyms for '" << searchTerm << "': ";
            for (const auto& syn : result) {
                cout << syn << " ";
            }
            cout << endl;
        } else {
            cout << "'" << searchTerm << "' not found in the index." << endl;
        }
    }
    system("pause");
    return 0;
}
