#include<iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <windows.h>
#include "utils.h"
using namespace std;

void clearScreen(){
    if (system("CLS")) system("clear");
}

void renderLoadingAnimTxt(){
    cout << "LOADING.";
    long double startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    cout << "LOADING..";
    startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    cout << "LOADING...";
    startTime = time(0) * 1000;
    while (false || (time(0) * 1000 - startTime) < 50);
    cout<<'\r'<< string(50, ' ') <<'\r';

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void enterToContinue(){
    do {
        cout << "Press enter to continue.......(If does not continue, press enter again.)" << endl;
        cin.ignore();
        string temp;
        getline(cin, temp);
        if (temp.empty()) break;
    } while (1);
}

string getCurrentTime(){
    time_t theTime = time(NULL);
    struct tm * aTime = localtime(&theTime);

    int day = aTime -> tm_mday;
    int month = aTime -> tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime -> tm_year + 1900; // Year is # years since 1900

    ostringstream strs1;
    strs1 << day;
    string strDate = strs1.str();

    ostringstream strs2;
    strs2 << month;
    string strMonth = strs2.str();

    ostringstream strs3;
    strs3 << year;
    string strYear = strs3.str();
    return strDate + "/" + strMonth + "/" + strYear;
}

bool stringIsEmptyOrHasOnlyWS(string str){
    return ((str.find_first_not_of(' ') != std::string::npos) || str.length() == 0);
}

string substringAtPos(string str, int pos, char delim){
    string finalStr = "";
    char strChars[str.length()];
    strcpy(strChars, str.c_str());
    for (int i = pos; i < str.length(); i++){
        if (strChars[i] == delim) break;
        finalStr += convertCharToString(strChars[i]);
    }
    return finalStr;
}

string convertCharToString(char c){
    stringstream ss;
    string target;
    ss << c;
    ss >> target;
    return target;
}

string removeLastOccurrenceStr(string s, char c){
    auto pos = s.rfind(c);
    if (pos != std::string::npos) {
        s.erase(pos);
    }
    return s;
}

string getCurrentFileDirector(){
    TCHAR fullPath[MAX_PATH];
    int bytes = GetModuleFileName(NULL, fullPath, MAX_PATH);
    wstring result(&fullPath[0]);
    if(bytes == 0)
        return to_string(-1);
    else
        return string(result.begin(), result.end());
}
