#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rat, int count)
    : Savings_Account{name, balance, int_rat}, count{count} {}

bool Trust_Account::deposit(double amount) {
    if(amount >= 5000){
        amount += 50; //bonus
    }
    amount += amount * (int_rate/100);
    return Account::deposit(amount);
}

bool Trust_Account::withdraw(double amount) {
    if (count < 4 && amount <= (balance * 0.20) && (balance - amount) >= 0) {
        balance -= amount;
        count++; 
        return true;
    } else {
        return false;
    }
}


std::ostream &operator<<(std::ostream &os, const Trust_Account &account) {
    os << "[Trust_Account: " << account.name << ": " << account.balance << ", " << account.int_rate << "%]";
    return os;
}

