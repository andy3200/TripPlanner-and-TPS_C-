#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <cppTPS_Transaction.h>


using namespace std;


class addStop_transaction : public cppTPS_Transaction{
private:
    vector<wstring>* stops;
    wstring stopToAdd;

public:
    addStop_transaction(vector<wstring>* stops, const wstring& stopToAdd) {
        this->stops = stops;
        this->stopToAdd = stopToAdd;
    }

    void doTransaction() override {
        stops->push_back(stopToAdd);
    }

    void undoTransaction() override {
        stops->pop_back();
    }
    wstring toString() override {
        return L"Add " + stopToAdd + L" to Stops";
    }
};


