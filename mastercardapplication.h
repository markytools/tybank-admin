#ifndef MASTERCARDAPPLICATION_H
#define MASTERCARDAPPLICATION_H

#include "datahandler.h"
#include "utils.h"

struct MastercardInfo {
    string acctNumber;
    string cardNumber;
    string expiryDate;
    string cvc;
};

class MastercardApplication
{
    DataHandler dataHandler;

    void outputMCInfo(MastercardInfo mcInfo);
    bool checkIfMastercardExists(string acctNum);
    bool checkIfCardNumExists(string cardNum);

    MastercardInfo getSingleMCInfo(ifstream &infile);
    string generateCVC();
    string generateCardNumber();
    string setDate();
public:
    MastercardApplication();
    MastercardApplication(DataHandler dataHandler);
    void applyForMastercard();
};

#endif // MASTERCARDAPPLICATION_H
