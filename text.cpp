
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

using namespace std;

ifstream file("test.txt");
int total = 0;
string str1 = "";
string str2 = "";
string str3 = "";

class TextEditor {
private:
    vector<vector<string>> saveData;
    static TextEditor* s_instance;

public:
    void save_vector() {
        ifstream file("test.txt");
        vector<vector <string>> save;
        vector <string> lineSave;

        char buf[100];
        int count = 0;

        // save vector
        while (file >> buf) {
            count += strlen(buf) + 1;
            if (count > 71) {
                count = 0;
                count += strlen(buf) + 1;
                save.push_back(lineSave);
                lineSave.clear();
            }
            lineSave.push_back(buf);
        }
        save.push_back(lineSave);
        set_data(save);
    }

    void resize(vector<vector<string>>& vec) {
        vector<vector <string>> newVec;
        vector <string> lineSave;
        int count = 0;
        string temp;

        for (int i = 0; i < vec.size(); i++) {
            for (int j = 0; j < vec[i].size(); j++) {
                count += vec[i][j].size() + 1;
                if (count > 70) {
                    temp = vec[i][j];
                    count = 0;

                    newVec.push_back(lineSave);
                    lineSave.clear();
                    lineSave.push_back(temp);
                    count = temp.size();
                }
                else {
                    lineSave.push_back(vec[i][j]);
                }
            }
        }
        newVec.push_back(lineSave);
        set_data(newVec);
    }

    void set_data(vector<vector<string>>& vec) {
        saveData = vec;
    }

    vector<vector<string>>& get_data() {
        return saveData;
    }

    static TextEditor* instance() {
        if (!s_instance)
            s_instance = new TextEditor;
        return s_instance;
    }
};

TextEditor* TextEditor::s_instance;

void PrintTwenty(vector<vector<string>>& save, int num) {
    // print 20 line
    int lineNum = 1;
    str1 = "";
    str2 = "last";
    cout << " " << lineNum << "| ";

    while (true) {
        if (save.size() - num <= 20) { // 맨마지막
            for (int i = save.size() - 20; i < save.size(); i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            total = save.size() - 20;
            str2 = "last";
            break;
        }
        else if (num <= 0) { // 맨 앞부분
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            total = 0;
            str1 = "first";
            str2 = "";
            break;
        }

        else {
            for (int i = num; i < save.size(); i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            str2 = "";
            break;
        }
    }
}

void consoleMessage() {
    wchar_t ch2[20] = L" (콘솔메시지)";
    wcout << ch2 << endl;
}

// input n
void next(int n) {
    PrintTwenty(TextEditor::instance()->get_data(), n);
}

// input p
void prev(int n) {
    PrintTwenty(TextEditor::instance()->get_data(), n);
}

// input i
void insert(int line, int number, string word) {
    vector<vector<string>> vec;

    vec = TextEditor::instance()->get_data();

    //cout << vec.at(line + total - 1).at(number - 1) << endl; // check
    vec.at(line + total - 1).insert(vec.at(line + total - 1).begin() + number, word); // error

    TextEditor::instance()->resize(vec);
    PrintTwenty(TextEditor::instance()->get_data(), total);
}

// input d
void del(int line, int number) {
    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();

    vec.at(line + total - 1).erase(vec.at(line + total - 1).begin() + number - 1);
    TextEditor::instance()->resize(vec);
    PrintTwenty(TextEditor::instance()->get_data(), total);
}

// input c
void change(string oldWord, string newWord) {
    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();
    str3 = "";
    bool exitOuterLoop = false;

    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            size_t pos = vec[i][j].find(oldWord);
            if (pos != string::npos) {
                vec[i][j].replace(pos, oldWord.length(), newWord);
                exitOuterLoop = true;
            }
        }
    }
    if (exitOuterLoop == false) {
        str3 = "notSearch";
    }

    TextEditor::instance()->resize(vec);
    PrintTwenty(TextEditor::instance()->get_data(), total);
}

// input s
void search(string searchWord) {
    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();
    bool exitOuterLoop = false;
    int startWord = 0;
    str3 = "";

    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i][j] == searchWord) {
                startWord = i;
                exitOuterLoop = true;
                break;
            }
        }
        if (exitOuterLoop == true)
            break;
    }

    if (exitOuterLoop == false) {
        str3 = "notSearch";
    }

    int lineNum = 1;

    cout << " " << lineNum << "| ";
    for (int i = startWord; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << " ";
        }
        cout << endl;
        lineNum++;
        if (lineNum > 20) {
            break;
        }
        if (i == vec.size() - 1) {
            break;
        }
        cout << setw(2) << lineNum << "| ";
    }
    total = startWord;
}

// input t
void saveEnd() {
    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();
    ofstream write("test.txt", ios::out);

    for (vector<string> temp : vec) {
        for (string s : temp) {
            write << s << " ";
        }
    }
}

void printDash() {
    for (int i = 0; i < 75; i++) {
        cout << "-";
    }
    cout << endl;
}

char* expectionInput(char* input) {
    string t[10];
    int j = 0;
    string temp = input;

    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();

    if (temp.find(" ") != string::npos) {
        throw "[error] Blanks were included. Input again";
    }

    char* tok = strtok(input, "(),");

    while (tok != NULL) {
        t[j] = tok;
        //cout << tok << endl;
        tok = strtok(NULL, "(),");
        j++;
    }
    if (t[0] == "i") {
        for (char const& c : t[1]) {
            if (!isdigit(c)) {
                //wcout << ch4 << endl;
                throw "[error] Special characters are included in the number part. Input again";
            }
        }
        for (char const& c : t[2]) {
            if (!isdigit(c)) {
                throw "[error] Special characters are included in the number part. Input again";
            }
        }
        if (t[3].length() > 71) {
            throw "[error] Exceeded 75 bytes. Input again";
        }
        else if (stoi(t[1]) > 20) {
            throw "[error] Input line does not exist. Input again";
        }
        else if ((stoi(t[2])) > vec.at(stoi(t[1]) + total - 1).size()) {
            throw "[error] The partial word does not exist. Input again";
        }
    }
    else if (t[0] == "d") {
        for (char const& c : t[1]) {
            if (!isdigit(c)) {
                throw "[error] Special characters are included in the number part. Input again";
            }
        }
        for (char const& c : t[2]) {
            if (!isdigit(c)) {
                throw "[error] Special characters are included in the number part. Input again";
            }
        }
        if (stoi(t[1]) > 20) {
            throw "[error] Input line does not exist. Input again";
        }
        else if ((stoi(t[2])) > vec.at(stoi(t[1]) + total - 1).size()) {
            throw "[error] The partial word does not exist. Input again";
        }
    }
    else if (t[0] == "n" || t[0] == "p" || t[0] == "t") {
        if (t[1] != "") {
            throw "[error] Too many input arguments. Input again";
        }
    }
    return input;
}

int main() {
    // UTF-8
    wchar_t ch1[100] = L"n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료";
    wchar_t ch3[10] = L"입력:";

    locale::global(locale("en_US.UTF-8"));

    char optionNum[100];

    vector<vector <string>> save;

    TextEditor::instance()->save_vector();
    save = TextEditor::instance()->get_data();

    PrintTwenty(save, total);

    printDash();
    wcout << ch1 << endl;
    printDash();
    consoleMessage();
    printDash();
    wcout << ch3 << " "; // 입력: 

    while (cin.getline(optionNum, 100, '\n')) {
        //cin.ignore();
        save = TextEditor::instance()->get_data();

        char* sentence = new char[strlen(optionNum) + 1];
        strcpy(sentence, optionNum);
        printDash();
        try {
            expectionInput(optionNum);
        }
        catch (const char* st) {
            PrintTwenty(save, total);
            printDash();
            wcout << ch1 << endl;
            printDash();
            wcout << st << endl;
            printDash();
            wcout << ch3 << " ";
            continue;
        }

        string t[10];
        int j = 0;
        char* tok2 = strtok(sentence, "(),");
        while (tok2 != NULL) {
            t[j] = tok2;
            tok2 = strtok(NULL, "(),");
            j++;
        }

        if (t[0] == "n") {
            if (str2 == "last") {
                next(total);

                printDash();
                wcout << ch1 << endl;
                printDash();
                cout << " This is the last page!" << endl;
            }
            else {
                total += 20;
                next(total);

                printDash();
                wcout << ch1 << endl;
                printDash();
                consoleMessage();
            }
        }
        else if (t[0] == "p") {
            if (str1 == "first") {
                total -= 20;
                prev(total);

                printDash();
                wcout << ch1 << endl;
                printDash();
                cout << " This is the first page!" << endl;
            }
            else {
                total -= 20;
                prev(total);

                printDash();
                wcout << ch1 << endl;
                printDash();
                consoleMessage();
            }
        }
        else if (t[0] == "i") {
            insert(stoi(t[1]), stoi(t[2]), t[3]);
            printDash();
            wcout << ch1 << endl;
            printDash();
            consoleMessage();
        }
        else if (t[0] == "d") {
            del(stoi(t[1]), stoi(t[2]));
            printDash();
            wcout << ch1 << endl;
            printDash();
            consoleMessage();
        }
        else if (t[0] == "c") {
            change(t[1], t[2]);
            printDash();
            wcout << ch1 << endl;
            printDash();
            if (str3 == "notSearch") {
                cout << "[error] Word does not exist. Input again" << endl;
            }
            else {
                consoleMessage();
            }
        }
        else if (t[0] == "s") {
            search(t[1]);
            printDash();
            wcout << ch1 << endl;
            printDash();
            if (str3 == "notSearch") {
                cout << "[error] Word does not exist. Input again" << endl;
            }
            else {
                consoleMessage();
            }
        }
        else if (t[0] == "t") {
            saveEnd();
            break;
        }
        else {
            PrintTwenty(save, total);
            printDash();
            wcout << ch1 << endl;
            printDash();
            cout << "[error] There is no corresponding action menu. Input again" << endl;
        }
        printDash();
        wcout << ch3 << " ";
    }
    file.close();

    return 0;
}
