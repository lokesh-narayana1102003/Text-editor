
#include "modifycontent.h" 
modifyContent::modifyContent()
{
}

modifyContent::~modifyContent()
{
}
std::vector<std::string> modifyContent::readFile() { 
    std::vector<std::string> lines;
    std::ifstream file("text.txt"); 
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

void modifyContent::writeFile(const std::vector<std::string>& lines) {
    std::ofstream file("text.txt"); // Hardcoded "text.txt"
    if (file.is_open()) {
        for (int i=0;i<lines.size();i++) {
            file << lines[i] << std::endl;
        }
        file.close();
    }
}

void modifyContent::editFile() {
    std::vector<std::string> lines = readFile();
    for (size_t i = 0; i < lines.size(); ++i) {
        std::cout << i + 1 << ": " << lines[i] << std::endl;
    }
    std::string command;
    while (true) {
        std::cout << "\nEnter command ('edit', 'add', 'remove', or 'save'): ";
        std::getline(std::cin, command);
        if (command == "save") {
            writeFile(lines);
            std::cout << "File saved.\n";
            break;
        } else if (command == "add") {
            std::cout << "Enter new line: ";
            std::string newLine;
            std::getline(std::cin, newLine);
            lines.push_back(newLine);
        } else if (command == "remove") {
            std::cout << "Enter line number to remove: ";
            int lineNumber;
            std::cin >> lineNumber;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (lineNumber >= 1 && lineNumber <= lines.size()) {
                lines.erase(lines.begin() + lineNumber - 1);
            } else {
                std::cout << "Invalid line number.\n";
            }
        } else if (command == "edit") {
            int linenum;
            std::cout << "Enter the line number which u want to edit: ";
            std::cin >> linenum;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

            if (linenum >= 1 && linenum <= lines.size()) {
                std::cout << "Enter new line content: ";
                std::string newLine;
                std::getline(std::cin, newLine);
                lines[linenum - 1] = newLine;
            } else {
                std::cout << "Invalid line number.\n";
            }
        } else {
            std::cout << "Invalid command.\n";
        }
    }
}


