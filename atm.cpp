#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include "atm.h"
#include "utils.h"
#include "datahandler.h"
#include "statementmanager.h"

Atm::Atm(){

}

Atm::Atm(StatementManager sManager){
    this->sManager = sManager;
}

void Atm::resetLoadedAccount(){
    AcctInfo loadedAcct = this->loadedAcct;
    loadedAcct.name = "";
    loadedAcct.address = "";
    loadedAcct.acctNum = "";
    loadedAcct.balance = 0;
    loadedAcct.pin = "";
}

void Atm::setLoadedAccount(){
    loadedAcct = getMatchedATMAcct(loadedAcctNum);
}

void Atm::displayCurrentTransaction(){
    if (system("CLS")) system("clear");
    switch (aTSelection){
    case BALANCE_INQUIRY: {
        balanceInquiry();
    }; break;
    case WITHDRAW_CASH: {
        withdrawCash();
    }; break;
    case FAST_CASH: {
        fastCash();
    }; break;
    case CHANGE_PIN: {
        changePin();
    }; break;
    case DEPOSIT: {
        deposit();
    }; break;
    case BILLS_PAYMENT: {
        billsPayment();
    }; break;
    case FUND_TRANSFER: {
        fundTransfer();
    }; break;
    default: break;
    }
    setLoadedAccount();
}

bool Atm::validatePin(){
    string pin = "";
    int numOfTriesLeft = 2;

    cout << TITLE_AT_INPUT_PIN << endl;
    do {
        char pinChar[6];
        cout << "Please enter your 6-digit pin number: ";
        for(int i = 0; i < 6; i++){
            pinChar[i] = getch();
            printf("*");
        }
        pin = string(pinChar);
        cout << endl;
        renderLoadingAnimTxt();
        while (pin.size() > 6) pin = pin.substr(0, pin.length() - 1);

        if (loadedAcct.pin == pin) return true;
        if (numOfTriesLeft == 0){
            cout << "You have exceeded the maximum number of tries!" << endl;
            cout << "Press enter to exit." << endl;
            enterToContinue();
            return false;
        }
        numOfTriesLeft--;
        cout << "Invalid Pin Number! Please try again." << endl;
        cout << "Tries Left : " << numOfTriesLeft << endl;
    } while (1);
    return false;
}

void Atm::performAnotherTransaction(){
    string newTransaction = "";
    cout << "Would you like to perform another transaction? (Y/N)";
    do {
        cin >> newTransaction;
        if (newTransaction == "Y" || newTransaction == "y") break;
        else if (newTransaction == "N" || newTransaction == "n"){
            exitATM = true;
            setBHState(OUT);
            break;
        }
        cout << ERR_MSG_INPUT << endl;
    } while (1);
}

bool Atm::checkIfWholeNumber(float num){
    if (int(num) == num)
        return true;
    else return false;
}

bool Atm::isDigits(string &str){
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool Atm::checkIfOkToWithdraw(float bal, float amount){
    if (bal - amount >= 0){
        if (amount > 50000) cout << MAX_AMOUNT << endl;
        else {
            if (!checkIfWholeNumber(amount) || int(amount) % 100 != 0) cout << INV_CASH_DENOM << endl;
            else return true;
        }
    }
    else cout << NOT_ENOUGH_BAL << endl;
    return false;
}

void Atm::flushTransInfo(string acctNum, string name, float credits, float debits, string date, string remarks){
    TransactionInfo transInfo;
    transInfo.name = name;
    transInfo.amountCredited = credits;
    transInfo.amountDebited = debits;
    transInfo.dateOfTrans = date;
    transInfo.remarks = remarks;
    sManager.addTransactionInfo(acctNum, transInfo);
}

AcctInfo Atm::getMatchedATMAcct(string acctNumber){
    resetLoadedAccount();
    return getMatchedAccount(acctNumber);
}

void Atm::balanceInquiry(){
    if (validatePin()){
        clearScreen();
        cout << TITLE_AT_BALANCE_INQUIRY << endl;
        cout << "Your net balance is: P " << loadedAcct.balance << endl;
        cout << endl;
        performAnotherTransaction();
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::withdrawCash(){
    if (validatePin()){
        clearScreen();
        float amount;
        cout << TITLE_AT_WITHDRAW_CASH << endl;
        cout << "Balance : P " << loadedAcct.balance << endl;
        do {
            cout << "Please enter an amount : ";
            cin >> amount;
            if (checkIfOkToWithdraw(loadedAcct.balance, amount)){
                float newBal = loadedAcct.balance - amount;
                setBalance(loadedAcct.acctNum, newBal);
                flushTransInfo(loadedAcct.acctNum, TRANS_NAME_CASH, 0, amount, getCurrentTime(), REMARKS_OK1);


                QSqlQuery query;
                query.clear();
                query.prepare("UPDATE amount SET amount=:NEWBALANCE WHERE accountno=:ACCTNO");
                query.bindValue(":NEWBALANCE", newBal);
                query.bindValue(":ACCTNO", QString::fromStdString(loadedAcct.acctNum));
                query.exec();

                query.clear();
                query.prepare("INSERT INTO transaction (credit, debit, account_no, trans_post_id, datetime_post, recipient_num, trans_balance) VALUES (0, :DEBIT, :ACCT_NO, 8, NOW(), '0', :BALANCE)");
                query.bindValue(":DEBIT", amount);
                query.bindValue(":ACCT_NO", QString::fromStdString(loadedAcct.acctNum));
                query.bindValue(":BALANCE", newBal);
                query.exec();


                query.clear();
                query.prepare("SELECT email, firstname, lastname FROM online_acct INNER JOIN personal_info ON "
                              "online_acct.personal_info_id=personal_info.idpersonal_info WHERE personal_info_id IN "
                              "(SELECT personal_info_id FROM user_account where account_no=:ACCTNO)");
                query.bindValue(":ACCTNO", QString::fromStdString(loadedAcct.acctNum));
                query.exec();

                if (query.first()) {
                    QString email = query.value(0).toString();
                    QString firstname = query.value(1).toString();
                    QString lastname = query.value(2).toString();
                    SmtpClient smtp("tybank.heliohost.org", 465, SmtpClient::SslConnection);
                    smtp.setUser("noreply@tybank.heliohost.org");
                    smtp.setPassword("boaconstrictor12");
                    smtp.setAuthMethod(SmtpClient::AuthMethod::AuthPlain);
                    MimeMessage message;

                    message.setSender(new EmailAddress("noreply@tybank.heliohost.org", "TyBank"));
                    message.addRecipient(new EmailAddress(email, firstname + " " + lastname));
                    message.setSubject("TyBank Account Withdrawal Notification");
                    message.setInReplyTo("markytools@gmail.com");

                    MimeText text;
                    QString msg = "Hello " + firstname + " " + lastname + ",\nThis is to notify you that you have recently withdrawn PHP " + QString::number(amount) + " from your bank account ********" + QString::fromStdString(loadedAcct.acctNum.substr(8, 4)) + ".\n";
                    text.setText(msg);
                    message.addPart(&text);
                    smtp.connectToHost();
                    smtp.login();
                    smtp.sendMail(message);
                    smtp.quit();
                }

                cout << "You have successfully withdrawn P " << amount << endl;
                performAnotherTransaction();
                break;
            }
        } while (1);
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::fastCash(){
    if (validatePin()){
        clearScreen();
        int selection = 0;
        float amount = 0;
        cout << TITLE_AT_WITHDRAW_CASH << endl;
        cout << FAST_CASH_SELECTIONS << endl;
        cout << "Balance : P " << loadedAcct.balance << endl;
        cout << "Select an amount to withdraw." << endl;
        do {
            cout << "Please type in the designated number of the amount: ";
            cin >> selection;
            if (!(selection >= 1 && selection <= 5)){
                cout << ERR_MSG_INPUT << endl;
                continue;
            }
            switch (selection){
            case 1: amount = 10000; break;
            case 2: amount = 5000; break;
            case 3: amount = 2000; break;
            case 4: amount = 1000; break;
            case 5: amount = 500; break;
            default: break;
            }
            if (checkIfOkToWithdraw(loadedAcct.balance, amount)){
                setBalance(loadedAcct.acctNum, loadedAcct.balance - amount);
                flushTransInfo(loadedAcct.acctNum, TRANS_NAME_CASH, 0, amount, getCurrentTime(), REMARKS_OK1);
                cout << "You have successfully withdrawn P " << amount << endl;
                performAnotherTransaction();
                break;
            }
        } while (1);
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::changePin(){
    if (validatePin()){
        clearScreen();
        string newPin = "";
        cout << TITLE_AT_CHANGE_PIN << endl;
        do {
            cout << "Please enter your new 6-digit pin number : ";
            cin >> newPin;
            if (isDigits(newPin) && newPin.length() == 6){
                setPin(loadedAcct.acctNum, newPin);
                break;
            }
            else cout << "Error Changing New Pin!" << endl;
        } while (1);
        cout << "You have successfully changed your pin." << endl;
        performAnotherTransaction();
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::deposit(){
    if (validatePin()){
        clearScreen();
        cout << TITLE_AT_CHANGE_PIN << endl;
        float amountToDeposit = 0;
        cout << "Please enter an amount to deposit : ";
        cin >> amountToDeposit;
        float newBal = loadedAcct.balance + amountToDeposit;
        setBalance(loadedAcct.acctNum, newBal);
        flushTransInfo(loadedAcct.acctNum, TRANS_NAME_DEPOSIT, amountToDeposit, 0, getCurrentTime(), REMARKS_OK1);


        QSqlQuery query;
        query.clear();
        query.prepare("UPDATE amount SET amount=:NEWBALANCE WHERE accountno=:ACCTNO");
        query.bindValue(":NEWBALANCE", newBal);
        query.bindValue(":ACCTNO", QString::fromStdString(loadedAcct.acctNum));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO transaction (credit, debit, account_no, trans_post_id, datetime_post, recipient_num, trans_balance) VALUES (:CREDIT, 0, :ACCT_NO, 7, NOW(), '0', :BALANCE)");
        query.bindValue(":CREDIT", amountToDeposit);
        query.bindValue(":ACCT_NO", QString::fromStdString(loadedAcct.acctNum));
        query.bindValue(":BALANCE", newBal);
        query.exec();

        cout << "You have successfully deposited P " << amountToDeposit << " to your account." << endl;
        performAnotherTransaction();
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::billsPayment(){
    if (validatePin()){
        clearScreen();
        float amount = 0;
        int orgToPay = 0;
        string payTo = "";
        string transName = "";
        cout << TITLE_AT_BILLS_PAYMENT << endl;
        cout << MSG_CHOICES << endl;
        cout << BILLS_PAYMENT_SELECTIONS << endl;
        do {
            cout << "Selection : ";
            cin >> orgToPay;
            if (orgToPay >= 1 && orgToPay <= 4) break;
            else cout << ERR_MSG_INPUT << endl;
        } while (1);
        switch (orgToPay){
        case 1: {
            payTo = "SMART.";
            transName = TRANS_NAME_SMART;
        }; break;
        case 2: {
            payTo = "GLOBE.";
            transName = TRANS_NAME_GLOBE;
        }; break;
        case 3: {
            payTo = "NORECO.";
            transName = TRANS_NAME_NORECO;
        }; break;
        case 4: {
            payTo = "SILLIMAN.";
            transName = TRANS_NAME_SILLIMAN;
        }; break;
        default: break;
        }
        cout << "You have requested to pay to " << payTo << endl;
        do {
            cout << "Please type in the amount to pay : P ";
            cin >> amount;
            if (loadedAcct.balance - amount >= 0){
                setBalance(loadedAcct.acctNum, loadedAcct.balance - amount);
                break;
            }
            else cout << NOT_ENOUGH_BAL << endl;
        } while (1);
        flushTransInfo(loadedAcct.acctNum, transName, 0, amount, getCurrentTime(), REMARKS_OK2);
        cout << "Transaction successful." << endl;
        performAnotherTransaction();
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::fundTransfer(){
    if (validatePin()){
        clearScreen();
        bool validAcctNum = false;
        string transfereeAcctNum = "";
        int triesLeft = 3;
        float amount = 0;
        float fee = 0;
        cout << TITLE_AT_FUND_TRANSFER << endl;
        cout << "Fee : " << TRANSFER_COST << endl;
        do {
            cout << "Enter the account number of the account you wish to transfer funds to." << endl;
            cout << "Account Number : ";
            cin >> transfereeAcctNum;
            if (checkSameAcctNum(transfereeAcctNum)){
                if (transfereeAcctNum != loadedAcct.acctNum){
                    validAcctNum = true;
                    break;
                }
            }
            triesLeft--;
            if (triesLeft == 0){
                cout << "You have exceeded the maximum number of tries!" << endl;
                cout << "Press enter to exit." << endl;

                do {
                    cin.ignore();
                    string temp;
                    getline(cin, temp);
                    if (temp.empty()) break;
                } while (1);
                exitATM = true;
                setBHState(OUT);
                break;
            }
            else cout << "Invalid Account Number! Tries Left: " << triesLeft << endl;
        } while (1);

        if (validAcctNum){
            cout << "Balance: P " << loadedAcct.balance << endl;
            do {
                cout << "Enter an amount : ";
                cin >> amount;
                fee = amount / 100;
                if (loadedAcct.balance - amount - fee >= 0){
                    AcctInfo transfereeAcct = getMatchedATMAcct(transfereeAcctNum);
                    string verify = "";
                    cout << endl;
                    cout << "Fee : P " << fee << endl;
                    cout << "You have requested to transfer funds to " << transfereeAcct.name << "." << endl;
                    do {
                        cout << "Please type Y to coninue or N to exit." << endl;
                        cin >> verify;
                        if (verify == "Y" || verify == "y"){
                            float amountDebited = loadedAcct.balance - amount - fee;
                            float amountCredited = transfereeAcct.balance + amount;
                            setBalance(loadedAcct.acctNum, amountDebited);
                            setBalance(transfereeAcctNum, amountCredited);
                            flushTransInfo(loadedAcct.acctNum, TRANS_NAME_MONEY_TRANSFER, 0, amount + fee, getCurrentTime(), REMARKS_OK1);
                            flushTransInfo(transfereeAcct.acctNum, TRANS_NAME_MONEY_RECEIVED, amount, 0, getCurrentTime(), REMARKS_OK1);
                            cout << "Transaction successful." << endl;
                            break;
                        }
                        else if (verify == "N" || verify == "n"){
                            cout << "Transaction discontinued." << endl;
                            break;
                        }
                        else cout << ERR_MSG_INPUT << endl;
                    } while (1);
                    break;
                }
                else cout << NOT_ENOUGH_BAL << endl;
            } while (1);

            performAnotherTransaction();
        }
    }
    else {
        exitATM = true;
        setBHState(OUT);
    }
}

void Atm::displayATM(){
    resetLoadedAccount();
    string acctNumber;

    cout << fixed << setprecision(2);
    cout << TITLE_AT << endl;
    cout << MSG_TYPE_IN << endl;
    do {
        cout << endl;
        cout << "Account Number: ";
        cin >> acctNumber;
        loadedAcct = getMatchedATMAcct(acctNumber);
        if (loadedAcct.name == "") cout << "Invalid Account Number!";
        else break;
    } while (1);
    loadedAcctNum = loadedAcct.acctNum;
    exitATM = false;

    while (!exitATM){
        if (system("CLS")) system("clear");
        cout << TITLE_AT << endl << endl;
        cout << "Hello, " << loadedAcct.name << ". What do you want to do?" << endl;
        cout << MSG_CHOICES << endl;
        cout << SELECTION_ATM_TRANS << endl;

        int selection = 0;

        do {
            cout << "Selection No. : ";
            cin >> selection;
            if (selection >= 1 && selection <= 8) break;
            cout << ERR_MSG_INPUT << endl;
        } while (1);

        switch (selection){
        case 1: aTSelection = BALANCE_INQUIRY; break;
        case 2: aTSelection = WITHDRAW_CASH; break;
        case 3: aTSelection = FAST_CASH; break;
        case 4: aTSelection = CHANGE_PIN; break;
        case 5: aTSelection = DEPOSIT; break;
        case 6: aTSelection = BILLS_PAYMENT; break;
        case 7: aTSelection = FUND_TRANSFER; break;
        case 8: {
            setBHState(OUT);
            exitATM = true;
        }; break;
        default: break;
        }
        if (!exitATM) displayCurrentTransaction();
    }
}

