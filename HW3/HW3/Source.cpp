

#include <iostream>
#include <vector>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    std::string accountHolder;

public:
    BankAccount(std::string accNumber, double initialBalance, std::string holder) {
        accountNumber = accNumber;
        balance = initialBalance;
        accountHolder = holder;
    }

    void Deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    void Withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }

    double GetBalance() const {
        return balance;
    }

    std::string GetAccountHolder() const {
        return accountHolder;
    }

    std::string GetAccountNumber() const {
        return accountNumber;
    }

    void PrintAccountInfo() const {
        std::cout << "Номер счета: " << accountNumber
            << ", Владелец: " << accountHolder
            << ", Баланс: " << balance << std::endl;
    }
};

class Bank {
private:
    std::vector<BankAccount*> accounts;

public:
    void AddAccount(BankAccount* account) {
        accounts.push_back(account);
    }

    double GetTotalBalance() const {
        double total = 0;
        for (size_t i = 0; i < accounts.size(); i++) {
            total += accounts[i]->GetBalance();
        }
        return total;
    }

    void PrintAllAccounts() const {
        for (size_t i = 0; i < accounts.size(); i++) {
            accounts[i]->PrintAccountInfo();
        }
    }
};

int main() {
    
    BankAccount* account1 = new BankAccount("1234567890", 1000.0, "Иванов И.И.");
    BankAccount* account2 = new BankAccount("0987654321", 500.0, "Петрова А.С.");


    Bank bank;
    bank.AddAccount(account1);
    bank.AddAccount(account2);

    account1->Deposit(500.0);
    account1->Withdraw(200.0);
    account2->Deposit(1000.0);
    account2->Withdraw(300.0);
    account2->Withdraw(2000.0);


    std::cout << "Информация о всех счетах:" << std::endl;
    bank.PrintAllAccounts();
    std::cout << "Общий баланс всех счетов: " << bank.GetTotalBalance() << std::endl;

    delete account1;
    delete account2;

    return 0;
}