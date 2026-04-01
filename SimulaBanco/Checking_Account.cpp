#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string n, double b, double f)
    : Account(n, b), fee(f) {}

bool Checking_Account::withdraw(double amount){
    if (balance-amount >=0) {
        amount += fee;
        balance-=amount;
        return true;
    } else
        return false;
}

std::ostream &operator<<(std::ostream &os, const Checking_Account &account) {
    os << "[Checking_Account: " << account.name << ": " << account.balance << ", " << account.fee << "%]";
    return os;
}