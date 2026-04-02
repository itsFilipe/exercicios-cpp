#ifndef _CHECKINGACC_
#define _CHECKINGACC_

#include "Account.h"

class Checking_Account : public Account {
    friend std::ostream &operator<<(std::ostream &os, const Checking_Account &account);
    
    private:
        static constexpr const char *def_name = "Unnamed Checking Account";
        static constexpr double def_balance = 0.0;
        static constexpr double def_fee = 1.50;
    protected:
        double fee;
    public:

    Checking_Account(std::string n = def_name, double b = def_balance, double f = def_fee);
    bool withdraw(double amount); //cada retirada tem taxa de 1.50
};

#endif