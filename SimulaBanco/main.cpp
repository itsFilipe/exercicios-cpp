// Section 15
// Challenge 
#include <iostream>
#include <vector>
#include "Savings_Account.h"
#include "Account_Util.h"
#include "Checking_Account.h"
#include "Trust_Account.h"

using namespace std;

int main() {
    cout.precision(2);
    cout << fixed;
   
    // Accounts
    vector<Account *> accounts;
    accounts.push_back(new Account {});
    accounts.push_back(new Account {"Larry"});
    accounts.push_back(new Account {"Moe", 2000} );
    accounts.push_back(new Account {"Curly", 5000} );
    
    accounts.push_back(new Savings_Account {} );
    accounts.push_back(new Savings_Account {"Superman"} );
    accounts.push_back(new Savings_Account {"Batman", 2000} );
    accounts.push_back(new Savings_Account {"Wonderwoman", 5000, 5.0} );

    accounts.push_back(new Checking_Account {} );
    accounts.push_back(new Checking_Account {"Filipe"} );
    accounts.push_back(new Checking_Account {"Bianka", 2000} );
    accounts.push_back(new Checking_Account {"Scott", 5000, 50} );

    accounts.push_back(new Trust_Account {} );
    accounts.push_back(new Trust_Account {"Michael"} );
    accounts.push_back(new Trust_Account {"Kelly", 2000} );
    accounts.push_back(new Trust_Account {"Gabe", 5000, 0} );

    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts,2000);

    for (auto acc : accounts) {
        delete acc; 
    }
    accounts.clear(); 

    return 0;
}

