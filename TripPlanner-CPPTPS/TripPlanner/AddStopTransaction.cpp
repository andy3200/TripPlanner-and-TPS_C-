
#include <cppTPS_Transaction.h>
#include <vector>
#include <string>
#include "AddStopTransaction.h"

class AddStopTransaction : public cppTPS_Transaction {
private:
    std::wstring airportCode;
    std::vector<std::wstring>& stops;

public:
    AddStopTransaction(const std::wstring& airportCode, std::vector<std::wstring>& stops)
        : airportCode(airportCode), stops(stops) {}

    virtual void doTransaction() override {
        stops.push_back(airportCode);
    }

    virtual void undoTransaction() override {
        stops.pop_back();
    }
};