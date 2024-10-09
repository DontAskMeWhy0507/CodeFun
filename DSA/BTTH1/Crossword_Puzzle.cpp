#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

bool TryHorizontal(vector<string>& crossword, string word, int row, int col) {
    if (col + word.size() > 10) return false;
    for (int i = 0; i < word.size(); i++) {
        if (crossword[row][col + i] != '-' && crossword[row][col + i] != word[i]) {
            return false;
        }
    }
    return true;
}
bool TryVertical(vector<string>& crossword, string word, int row, int col) {
    if (row + word.size() > 10) return false;
    for (int i = 0; i < word.size(); i++) {
        if (crossword[row + i][col] != '-' && crossword[row + i][col] != word[i]) {
            return false;
        }
    }
    return true;
}
void Horizontal(vector<string>& crossword, string word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossword[row][col + i] = word[i];
    }
}
void Vertical(vector<string>& crossword, string word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossword[row + i][col] = word[i];
    }
}
void deleteHorizontal(vector<string>& crossword, string word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossword[row][col + i] = '-';
    }
}
void deleteVertical(vector<string>& crossword, string word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossword[row + i][col] = '-';
    }
}
bool backtracking(vector<string>& crossword, vector<string>& words, int index) {
    if (index == words.size()) return true;
    string word = words[index];
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if (TryHorizontal(crossword, word, row, col)) {
                Horizontal(crossword, word, row, col);
                if (backtracking(crossword, words, index + 1)) {
                    return true;
                }
                deleteHorizontal(crossword, word, row, col);
            }
            if (TryVertical(crossword, word, row, col)) {
                Vertical(crossword, word, row, col);
                if (backtracking(crossword, words, index + 1)) {
                    return true;
                }
                deleteVertical(crossword, word, row, col);
            }
        }
    }
    return false;
}
vector<string> crosswordPuzzle(vector<string> crossword, string words_str) {
    vector<string> words;
    size_t pos = 0;
    while ((pos = words_str.find(';')) != string::npos) {
        words.push_back(words_str.substr(0, pos));
        words_str.erase(0, pos + 1);
    }
    words.push_back(words_str);
    backtracking(crossword, words, 0);
    return crossword;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
