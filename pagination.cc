#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_CHARS_LINE = 80;
const int MAX_LINES_PAGE = 25;

void pagination(int num_page) {
    cout << "----- Page " << num_page << " -----" << endl;
}

void processLines(istringstream& iss, int& num_line, int& num_page) {
    string word;
    string current_line;

    // Process each word in the line
    while (iss >> word) {
        // Check if the word fits in the current line
        if (current_line.length() + word.length() + 1 <= MAX_CHARS_LINE) {
            if (!current_line.empty()) {
                current_line += " "; 
            }
            current_line += word;
        } 
        // If you go beyond the limit of the line
        else {
            cout << current_line << endl;
            current_line = word;
            num_line++;
            
            // Check if it is the limit of lines per page
            if (num_line >= MAX_LINES_PAGE) {
                pagination(num_page);
                num_page++;
                num_line = 0;
            }
        }
    }

    // Print the last line of the current word if not empty
    if (!current_line.empty()) {
        cout << current_line << endl;
        num_line++;

        if (num_line >= MAX_LINES_PAGE) {
            pagination(num_page);
            num_page++;
            num_line = 0;
        }
    }
}

int main() {
    string line;
    int num_line = 0;
    int num_page = 1;

    // Read file passed as parameter 
    while (getline(cin, line)) {
        istringstream iss(line); // Stream to process the line
        processLines(iss, num_line, num_page);
    }

    // Add separator if the file does not end on an empty line
    if (num_line > 0) {
        pagination(num_page);
    }
    return 0;
}
