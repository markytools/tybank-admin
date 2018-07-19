#include<iostream>
#include <iomanip>
#include "datamanager.h"
#include "utils.h"
using namespace std;

void displayHome(){
    int selection = 0;
    cout << TITLE_HOME << endl;
    cout << MSG_CHOICES << endl;
    cout << SELECTION_HOME << endl;
    do {
        cout << endl;
        cout << "Selection No. : ";
        cin >> selection;
        if (selection >= 1 && selection <= 4) break;
        cout << ERR_MSG_INPUT << endl;
    } while (1);
    setBHState(IN);
    switch (selection){
    case 1: setSelection(NEW_ACCOUNT); break;
    case 2: setSelection(ACQUIRE_BS); break;
    case 3: setSelection(ATM_TRANS); break;
    case 4: setSelection(EXIT_BANK); break;
    default: break;
    }
}

