#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Reads lines from a .txt into a vector.
// each new line becomes a separate vector element.
// This does NOT split along the | character (the writeSrt function does)
vector<string> readTxt(const string& filename) {
    
    vector<string> txtLines;
    
    ifstream file(filename);
    if (!file) {
        cout << "File " << filename << " not found" << endl;
        return txtLines;
    }

    string line;

    while (getline(file, line)) {
        txtLines.push_back(line);
    }

    file.close();

    return txtLines;
}

// Reads lines from a .srt into a vector
vector<string> readSrt(const string& filename) {

    vector<string> srtLines;
    
    ifstream file(filename);
    if (!file) {
        cout << "File " << filename << " not found" << endl;
        return srtLines;
    }
    
    string line;

    // TODO : READ ONLY THE SUBTITLES
    while (getline(file, line)) {
        // if the line is a subtitle
        // i.e. --> is not found and it is not a string with just one number
        // CAUTION: MAY CAUSE ISSUES WITH (EXCEPTIONALLY RARE) SINGLE-DIGIT SUBTITLE TEXT
        if (line.find("-->") == string::npos && !(line.length() == 1 && isdigit(line[0]))) {
            srtLines.push_back(line);
        }
    }

    file.close();

    return srtLines;
}

// Writes an unsynced srt file based on lines from a txt file.
// Splits along | into newlines
void writeSrt(const vector<string>& txtLines, const string& filename) {

    // We're disabling overwriting by default
    ifstream file(filename);
    if (file) {
        cout << "File " << filename << " already exists." << endl;
        return;
    }
    file.close();

    ofstream outFile(filename);
    int i = 1;
    string splitLine;
    for (const string& line : txtLines) {
        // line number
        outFile << i << '\n';
        // start time --> end time (blank, unsynced)
        outFile << "00:00:00,000 --> 00:00:00,000" << '\n';

        // stringstream for splitting along |
        stringstream ss(line);

        // this leaves the line unchanged if it has no | symbols
        while (getline(ss, splitLine, '|')) {
            // separate each segment into a new line
            outFile << splitLine << '\n';
        }

        // blank line at the end
        outFile << "\n";

        // increment the line number
        ++i;
    }

    outFile.close();
}

// Writes a txt from an srt with just the lines (transcription)
void writeTxt(const vector<string>& srtLines, const string& filename) {
    // We're disabling overwriting by default
    ifstream file(filename);
    if (file) {
        cout << "File " << filename << " already exists." << '\n';
        return;
    }
    file.close();

    // open the file for output
    ofstream outFile(filename);
    // for each line in the vector
    for (const string& line : srtLines) {
        // write it to the file. End with a newline
        outFile << line << '\n';
    }
    
    outFile.close();
}

int main() {
    // TODO : Write a proper main()
    
    /*
    // DUMMY driver code
    string txtSource, srtDest, srtSource, txtDest;
    cout << "Enter the name of the .txt file to convert to .srt: ";
    getline(cin, txtSource);
    srtDest = txtSource + ".srt";
    vector<string> txtLines = readTxt(txtSource);
    writeSrt(txtLines, srtDest);
    
    cout << "Enter the name of the .srt file to convert to .txt: ";
    getline(cin, srtSource);
    txtDest = srtSource + ".txt";
    vector<string> srtLines = readSrt(srtSource);
    writeTxt(srtLines, txtDest);
    */
    
    return 0;
}