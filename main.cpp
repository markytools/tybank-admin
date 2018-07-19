#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include "atm.h"
#include "bankDisplay.h"
#include "utils.h"
#include "datahandler.h"
#include "statementmanager.h"
#include "mastercardapplication.h"
#include "accountmanager.h"
#include "sqldatabase.h"
using namespace std;

bool exitBank = false;
Bank_Home_State bHState;
Selection selection;
int delayClrScrn = 0;

void displayBank(BankDisplay bDisplay, AccountManager acctManager, StatementManager sManager, Atm myAtm,
                 MastercardApplication msApplication){
    bool clrScreen = true;

    switch (bHState){
    case OUT: {
        bDisplay.displayHome();
    }; break;
    case IN: {
        switch (selection){
        case NEW_ACCOUNT: {
            acctManager.displayAccountCreation();
        }; break;
        case ACQUIRE_BS: {
            sManager.acquireBankStatement();
        }; break;
        case APPLY_FOR_MASTERCARD: {
            msApplication.applyForMastercard();
            clearScreen();
            setBHState(OUT);
        }; break;
        case ATM_TRANS: {
           myAtm.displayATM();
        }; break;
        case EXIT_BANK: {
           exitBank = true;
           clrScreen = false;
        }; break;
        default: break;
        }
    }; break;
    default: break;
    }

    if (clrScreen) clearScreen();
}

void setBHState(Bank_Home_State state){
    bHState = state;
}

void setSelection(Selection s){
    selection = s;
}

int main(){
//    string a(1, 'A');
//    string b(1, 'B');
//    string agh = a + b;
//    cout << agh << endl;
//    cout << std::fixed;
//    cout << std::setprecision(0);
    bHState = OUT;

    BankDisplay bDisplay;
    AccountManager acctManager;
    StatementManager sManager;
    Atm myAtm(sManager);
    MastercardApplication msApplication(myAtm);

    SQLDatabase *sqlDatab = new SQLDatabase();
    sqlDatab->connect();


//    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);
//    smtp.setUser("markytools@gmail.com");
//    smtp.setPassword("Destructobotics12");
//    MimeMessage message;

//    message.setSender(new EmailAddress("tybank@gmail.com", "TyBank"));
//    message.addRecipient(new EmailAddress("markytools@gmail.com", "Mark Ty"));
//    message.setSubject("SmtpClient for Qt - Demo");


//    MimeText text;
//    text.setText("Hi,\nThis is a simple email message.\n");
//    message.addPart(&text);
//    smtp.connectToHost();
//    smtp.login();
//    smtp.sendMail(message);
//    smtp.quit();

    while (!exitBank){
        displayBank(bDisplay, acctManager, sManager, myAtm, msApplication);
    }
    cout << "You will now be exiting the bank. Goodbye!" << endl;
}

