#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_

#include "Savings_Account.h"

class Trust_Account : public Savings_Account {
private:
    static constexpr const char *def_name = "Unnamed Savings Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 1.50;
    static constexpr int def_count = 0;
protected:
    int count;
public:
    Trust_Account(std::string name = def_name, double balance =def_balance, double int_rate = def_int_rate, int count = def_count);
    virtual bool deposit(double amount) override;
    virtual bool withdraw(double amount) override;
    virtual void print(std::ostream &os) const;

    virtual ~Trust_Account() = default;
};

#endif
