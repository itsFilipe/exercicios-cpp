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

void Checking_Account::print(std::ostream &os) const {
    os << "[Checking_Account: " << name << ": " << balance << ", " << fee << "%]";
}