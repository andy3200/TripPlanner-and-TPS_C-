#ifndef ADD_STOP_TRANSACTION_H
#define ADD_STOP_TRANSACTION_H

#include <cppTPS_Transaction.h>
#include <vector>
#include <string>

class AddStopTransaction : public cppTPS_Transaction {
private:
    std::wstring airportCode;
    std::vector<std::wstring>& stops;

public:
    AddStopTransaction(const std::wstring& airportCode, std::vector<std::wstring>& stops);

    virtual void doTransaction() override;
    virtual void undoTransaction() override;
};

#endif // ADD_STOP_TRANSACTION_H