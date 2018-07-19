#ifndef UTILS
#define UTILS
#include <iostream>
using namespace std;

const string TITLE_HOME = "---------------WELCOME TO TYBANK---------------";
const string TITLE_C_ACCOUNT = "----------CREATE ACCOUNT----------";
const string TITLE_B_STATEMENT = "----------ACQUIRE A BANK STATEMENT----------";
const string TITLE_AT = "----------ATM TRANSACTION----------";

const string TITLE_AT_BALANCE_INQUIRY = "-----BALANCE INQUIRY-----";
const string TITLE_AT_WITHDRAW_CASH = "-----WITHDRAW CASH-----";
const string TITLE_AT_FAST_CASH = "-----FAST CASH-----";
const string TITLE_AT_CHANGE_PIN = "-----CHANGE PIN-----";
const string TITLE_AT_DEPOSIT = "-----DEPOSIT-----";
const string TITLE_AT_BILLS_PAYMENT = "-----BILLS PAYMENT-----";
const string TITLE_AT_FUND_TRANSFER = "-----FUND TRANSFER-----";
const string TITLE_AT_INPUT_PIN = "-----VALIDATE ACCOUNT-----";

const string MSG_CHOICES = "--Type in One of the Following Selections--";
const string MSG_TYPE_IN = "--Please Type in the Requested Information--";

const string ERR_MSG_INPUT = "Invalid Input!";
const string ERR_MSG_DATA = "Invalid Data!";

const string SELECTION_HOME =
        string("1 - New/Existing Account                                       \n") +
        string("2 - Acquire A Bank Statement                          \n") +
        string("3 - ATM Transaction                                   \n") +
        string("4 - Apply for a Mastercard                            \n") +
        string("5 - Exit Bank                                         \n");

const string SELECTION_ATM_TRANS =
        string("1 - Balance Inquiry                                         \n") +
        string("2 - Withdraw Cash                                           \n") +
        string("3 - Fast Cash                                               \n") +
        string("4 - Change Pin                                              \n") +
        string("5 - Deposit                                                 \n") +
        string("6 - Bills Payment                                           \n") +
        string("7 - Fund Transfer                                           \n") +
        string("8 - Exit                                                    \n");

  const string BANK_PIC =
  string("         _._._                       _._._                        \n") +
  string("        _|   |_                     _|   |_                       \n") +
  string("        | ... |_._._._._._._._._._._| ... |                       \n") +
  string("        | ||| |  o    TY BANK    o  | ||| |                       \n") +
  string("        | \"\"\" |  \"\"\"    \"\"\"    \"\"\"  | \"\"\" |        \n") +
  string("   ())  |[-|-]| [-|-]  [-|-]  [-|-] |[-|-]|  ())                  \n") +
  string("  (())) |     |---------------------|     | (()))                 \n") +
  string(" (())())| \"\"\" |  \"\"\"    \"\"\"    \"\"\"  | \"\"\" |(())()) \n") +
  string(" (()))()|[-|-]|  :::   .-\"-.   :::  |[-|-]|(()))()               \n") +
  string(" ()))(()|     | |~|~|  |_|_|  |~|~| |     |()))(()                \n") +
  string("    ||  |_____|_|_|_|__|_|_|__|_|_|_|_____|  ||                   \n") +
  string("  ~ ~^^ @@@@@@@@@@@@@@/=======\@@@@@@@@@@@@@@ ^^~ ~               \n") +
  string("       ^~^~                                ~^~^                   \n");

void clearScreen();
string getCurrentTime();
void enterToContinue();
void renderLoadingAnimTxt();
bool checkSameName(string name);
bool checkSameAcctNum(string acctNum);
string substringAtPos(string str, int pos, char delim);
bool stringIsEmptyOrHasOnlyWS(string str);
string convertCharToString(char c);
string removeLastOccurrenceStr(string s, char c);
string getCurrentFileDirector();

#endif // UTILS
