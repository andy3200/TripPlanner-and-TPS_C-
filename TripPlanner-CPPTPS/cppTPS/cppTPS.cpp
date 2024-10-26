// cppTPS.cpp : Defines the functions for the static library.

// C++ LIBRARIES FOR I/O AND TEXT
#include <sstream>
#include <string>
#include "cppTPS.h"

cppTPS::cppTPS() {
    mostRecentTransaction = -1;
    numTransactions = 0;
    performingDo = false;
    performingUndo = false;
}

void cppTPS::addTransaction(cppTPS_Transaction* transaction) {
    if (mostRecentTransaction < 0 || mostRecentTransaction < (transactions.size() - 1)) {
        int numElementsToRemove = transactions.size() - (mostRecentTransaction + 1);
        if (numElementsToRemove > 0) {
            for (int i = mostRecentTransaction + 1; i < transactions.size(); i++) {
                delete transactions[i];
            }
            transactions.erase(transactions.begin() + mostRecentTransaction + 1, transactions.end());
        }
        numTransactions = mostRecentTransaction + 2;
    }
    else {
        numTransactions++;
    }
    transactions.push_back(transaction);
    doTransaction();
}

void cppTPS::doTransaction() {
    if (hasTransactionToRedo()) {
        performingDo = true;
        cppTPS_Transaction* transaction = transactions[mostRecentTransaction + 1];
        transaction->doTransaction();
        mostRecentTransaction++;
        performingDo = false;
    }
}

void cppTPS::undoTransaction() {
    if (hasTransactionToUndo()) {
        performingUndo = true;
        cppTPS_Transaction* transaction = transactions[mostRecentTransaction];
        transaction->undoTransaction();
        mostRecentTransaction--;
        performingUndo = false;
    }
}

void cppTPS::clearAllTransactions() {
    transactions.clear();
    mostRecentTransaction = -1;
    numTransactions = 0;
}


wstring cppTPS::toString() {
    std::wstring text = L"--Number of Transactions: " + std::to_wstring(numTransactions) + L"\n";
    text += L"--Current Index on Stack: " + std::to_wstring(mostRecentTransaction) + L"\n";
    text += L"--Current Transaction Stack:\n";
    for (int i = 0; i <= mostRecentTransaction; i++) {
        cppTPS_Transaction* cT = transactions[i];
        text += L"----" + cT->toString() + L"\n";
    }
    return text;
}