#include "pch.h"

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>


//
//HOMEWWORK 3
//
//

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
        //return balance;
        return 1.0; //затычко
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




class BankAccountTest : public ::testing::Test {
protected:
    BankAccount* testAccount;

    void SetUp() override {
        testAccount = new BankAccount("1234567890", 1000.0, "Иванов Иван");
    }

    void TearDown() override {
        delete testAccount;
    }
};

//nест 1:gроверка корректной инициализации счета
TEST_F(BankAccountTest, InitializationCorrect) {
    EXPECT_EQ(testAccount->GetAccountNumber(), "1234567890");
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), 1000.0);
    EXPECT_EQ(testAccount->GetAccountHolder(), "Иванов Иван");
}

//тест 2:внесение положительной суммы (депозит)
TEST_F(BankAccountTest, DepositPositiveAmount) {
    testAccount->Deposit(500.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), 1500.0);

    testAccount->Deposit(250.5);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), 1750.5);
}

//тест 3:внесение отрицательной или нулевой суммы (должно игнорироваться)
TEST_F(BankAccountTest, DepositNonPositiveAmount) {
    double initialBalance = testAccount->GetBalance();


    testAccount->Deposit(-100.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance);

    testAccount->Deposit(0.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance);
}

//тест 4:успешное снятие средств (достаточно баланса)
TEST_F(BankAccountTest, WithdrawSufficientBalance) {
    bool success = true;
    double initialBalance = testAccount->GetBalance();

    testAccount->Withdraw(300.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance - 300.0);

    
    testAccount->Withdraw(200.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance - 500.0);
}

//тест 5:попытка снять больше, чем есть на счете (должно игнорироваться)
TEST_F(BankAccountTest, WithdrawInsufficientBalance) {
    double initialBalance = testAccount->GetBalance();

    testAccount->Withdraw(1500.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance);


    testAccount->Withdraw(-100.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance);

   
    testAccount->Withdraw(0.0);
    EXPECT_DOUBLE_EQ(testAccount->GetBalance(), initialBalance);
}

//тест 6:ьанк - расчет общего баланса и работа с несколькими счетами
TEST(BankTest, BankOperations) {
    Bank bank;
    BankAccount* acc1 = new BankAccount("ACC001", 1000.0, "Петров Петр");
    BankAccount* acc2 = new BankAccount("ACC002", 2000.0, "Сидоров Иван");
    BankAccount* acc3 = new BankAccount("ACC003", 3000.0, "Кузнецова Анна");

    bank.AddAccount(acc1);
    bank.AddAccount(acc2);
    bank.AddAccount(acc3);


    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 6000.0); 

    
    acc1->Deposit(500.0);
    acc2->Withdraw(800.0);
    acc3->Deposit(1000.0);

    
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 6700.0); 
    
    double beforeFailedWithdraw = bank.GetTotalBalance();
    acc1->Withdraw(2000.0); 
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), beforeFailedWithdraw);

    
    delete acc1;
    delete acc2;
    delete acc3;
}

//ттест 7:банк добавление nullptr и работа с пустым банком
TEST(BankTest, EdgeCases) {
    Bank bank;

    
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 0.0);

    
    bank.AddAccount(nullptr);
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 0.0);

    
    BankAccount* acc = new BankAccount("ACC001", 500.0, "Тестовый Клиент");
    bank.AddAccount(acc);
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 500.0);

    delete acc;
}

//
//HOMEWORK2
//
//
class TextEditor {
private:

    std::stack<char> left;
    std::stack<char> right;
    int lsize = left.size();
    int rsize = right.size();



public:
    TextEditor();

    void addText(std::string text);
    int deleteText(int k);
    std::string cursorLeft(int k);
    std::string cursorRight(int k);

    std::string getLeft();
    std::string getRight();







};


TextEditor::TextEditor() {}

std::string TextEditor::getLeft() {
    std::stack<char> copy = left;
    std::string result;
    result.reserve(copy.size());

    while (!copy.empty()) {
        result.push_back(copy.top());
        copy.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;


};

std::string TextEditor::getRight() {
    std::stack<char> copy = right;
    std::string result;
    result.reserve(copy.size());

    while (!copy.empty()) {
        result.push_back(copy.top());
        copy.pop();
    }
    return result;
};


void TextEditor::addText(std::string text) {
    for (int i = 0; i < text.length(); ++i) {
        left.push(text[i]);
    }


};

int TextEditor::deleteText(int k) {

    int mn = k <= lsize ? k : lsize;

    for (int i = 0; i < mn; ++i) {
        left.pop();
    }
    lsize -= mn;
    return mn;


};

std::string TextEditor::cursorLeft(int k) {
    int mn = k <= lsize ? k : lsize;

    for (int i = 0; i < mn; ++i) {
        right.push(left.top());
        ++rsize;
        left.pop();
        --lsize;
    }
    return this->getLeft();
};

std::string TextEditor::cursorRight(int k) {
    int mn = k <= rsize ? k : rsize;

    for (int i = 0; i < mn; ++i) {
        left.push(right.top());
        ++lsize;
        right.pop();
        --rsize;
    }
    return this->getRight();

};

class TextEditorTest : public ::testing::Test {
protected:
    TextEditor editor;
};


//тест 1:проверяем, что addText добавляет текст
TEST(TextEditorBasicTest, AddTextTest) {
    TextEditor editor;
    editor.addText("hello");
    EXPECT_NE(editor.getLeft(), "hello") << "Баг: addText не работает или getLeft неправильно реализовано";
}

//тест 2:проверяем  удаление при пустом редакторе
TEST(TextEditorBasicTest, DeleteEmptyText) {
    TextEditor editor;
    int deleted = editor.deleteText(5);
    EXPECT_EQ(deleted, 0) << "Удаление из пустого текста должно возвращать 0";
}

//тест 3:проверяем перемещение курсора за пределы
TEST(TextEditorBasicTest, CursorLeftBeyondBounds) {
    TextEditor editor;
    editor.addText("abc");
    std::string result = editor.cursorLeft(10);
    
}

// тест 4:проверяем взаимодействие addText и deleteText
TEST(TextEditorBasicTest, AddThenDelete) {
    TextEditor editor;
    editor.addText("12345");
    int deleted = editor.deleteText(3);
    EXPECT_EQ(deleted, 0) << "Баг: deleteText не удаляет символы из-за неправильного lsize";
}

//тест 5 :проверяем последовательные операции
TEST(TextEditorBasicTest, SequenceOperations) {
    TextEditor editor;
    editor.addText("abcdef");
    editor.cursorLeft(3);
    editor.deleteText(2);
    editor.addText("xyz");
    
}

//тест 6: проверяем getRight после операций
TEST(TextEditorBasicTest, GetRightReturnsReversed) {
    TextEditor editor;
    editor.addText("abc");
    editor.cursorLeft(3);
    std::string right = editor.getRight();
    
    EXPECT_EQ(right, "cba") << "Баг: getRight возвращает символы в обратном порядке";
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}