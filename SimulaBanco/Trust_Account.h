#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_

#include "Savings_Account.h"

class Trust_Account : public Savings_Account {
    friend std::ostream &operator<<(std::ostream &os, const Trust_Account &account);
private:
    static constexpr const char *def_name = "Unnamed Savings Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 1.50;
    static constexpr int def_count = 0;
protected:
    int count;
public:
    Trust_Account(std::string name = def_name, double balance =def_balance, double int_rate = def_int_rate, int count = def_count);
    bool deposit(double amount);
    bool withdraw(double amount);
};

#endif
