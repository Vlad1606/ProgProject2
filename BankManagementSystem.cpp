#include <iostream>
#include "Header.h"
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

char file[13] = "account.dat";

class account {
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void withdraw(int);
    void dep(int);
    void create_account();
    void show_account() const;
    void modify();
    void report() const;
    int getAcNo() const;
    int getBal() const;
    char getAcType() const;
};

bool is_account_number_taken(int acno) {
    account ac;
    ifstream inFile;
    inFile.open(file, ios::binary);
    if (!inFile) {
        return false;
    }
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        if (ac.getAcNo() == acno) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void account::create_account() {
    do {
        std::cout << "\nEnter the account No. : ";
        std::cin >> acno;
        if (is_account_number_taken(acno)) {
            std::cout << "Account number already taken. Please choose another number.\n";
        }
    } while (is_account_number_taken(acno));

    std::cout << "\nEnter account Holder Name :";
    std::cin.ignore();
    std::cin.getline(name, 50);

    while (true) {
        std::cout << "\nEnter Type of Account (Checking/Saving) as C or S : ";
        std::cin >> type;
        type = toupper(type);
        if (type == 'C' || type == 'S') {
            break;
        }
    }

    std::cout << "\nEnter Initial amount: ";
    std::cin >> deposit;
    std::cout << "\n\nAccount Created...";
}

void account::show_account() const {
    std::cout << "\nAccount No. : " << acno;
    std::cout << "\nAccount Holder Name : " << name;
    std::cout << "\nType of Account : " << type;
    std::cout << "\nBalance amount : " << deposit;
}

void account::modify() {
    std::cout << "\nAccount No. : " << acno;
    std::cout << "\nEnter account Holder Name : ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    std::cout << "\nModify Type of Account (C/S) : ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "\nModify Balance amount : ";
    std::cin >> deposit;
}

void account::withdraw(int n) {
    deposit -= n;
}

void account::dep(int n) {
    deposit += n;
}

void account::report() const {
    std::cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::getAcNo() const {
    return acno;
}

int account::getBal() const {
    return deposit;
}

char account::getAcType() const {
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

void write_account() {
    account ac;
    ofstream outFile;
    outFile.open(file, ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n) {
    account ac;
    bool exist_flag = false;
    ifstream inFile;
    inFile.open(file, ios::binary);
    if (!inFile) {
        std::cout << "File could not open !! Press any Key... ";
        return;
    }
    std::cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        if (ac.getAcNo() == n) {
            ac.show_account();
            exist_flag = true;
        }
    }
    inFile.close();
    if (!exist_flag)
        std::cout << "\n\nAccount Number does not exist ";
}

void modify_account(int n) {
    account ac;
    bool found_flag = false;
    fstream kFile;
    kFile.open(file, ios::binary | ios::in | ios::out);
    if (!kFile) {
        std::cout << "File could not open !! Press any Key...";
        return;
    }
    while (!kFile.eof() && !found_flag) {
        kFile.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.getAcNo() == n) {
            ac.show_account();
            std::cout << "\n\nEnter the New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            kFile.seekp(pos, ios::cur);
            kFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
            std::cout << "\n\n\t Record Updated";
            found_flag = true;
        }
    }
    kFile.close();
    if (!found_flag)
        std::cout << "\n\nRecord Not Found";
}

void delete_account(int n) {
    bool found;
    account ac;
    ifstream inFile;
    inFile.open(file, ios::binary);
    ofstream outFile;
    outFile.open("temp.dat", ios::binary | ios::out);

    if (!inFile) {
        std::cout << "File could not open !! Press any Key...";
        return;
    }

    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        if (ac.getAcNo() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove(file);
    rename("temp.dat", file);
    std::cout << "\n\n\tRecord Deleted ...";
}

void display_all() {
    account ac;
    ifstream inFile;
    inFile.open(file, ios::binary);

    if (!inFile) {
        std::cout << "File could not open !! Press any Key...";
        return;
    }

    std::cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
    std::cout << "====================================================\n";
    std::cout << "A/c no.      NAME           Type  Balance\n";
    std::cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open(file, ios::binary | ios::out | ios::in);

    if (!File) {
        std::cout << "File could not open !! Press any Key...";
        return;
    }

    while (!File.eof() && !found) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.getAcNo() == n) {
            ac.show_account();
            if (option == 1) {
                std::cout << "\n\n\tTO DEPOSIT AMOUNT ";
                std::cout << "\n\nEnter The amount to be deposited";
                std::cin >> amt;
                ac.dep(amt);
            }
            if (option == 2) {
                std::cout << "\n\n\tTO WITHDRAW AMOUNT ";
                std::cout << "\n\nEnter The amount to be withdraw";
                std::cin >> amt;
                int bal = ac.getBal() - amt;
                if ((bal < 500 && ac.getAcType() == 'S') || (bal < 1000 && ac.getAcType() == 'C'))
                    std::cout << "Insufficient balance";
                else
                    ac.withdraw(amt);
            }

            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        std::cout << "\n\n Record Not Found ";
}

void intro() {
    std::cout << "\n\n\n\t  BANK";
    std::cout << "\n\n\tMANAGEMENT";
    std::cout << "\n\n\t  SYSTEM";
    std::cout << "\n\n\n\nPress enter to continue...";

    std::cin.get();
}

int main() {
    char ch;
    int num;
    intro();
    do {
        system("cls");
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t01. NEW ACCOUNT";
        std::cout << "\n\n\t02. DEPOSIT AMOUNT";
        std::cout << "\n\n\t03. WITHDRAW AMOUNT";
        std::cout << "\n\n\t04. BALANCE ENQUIRY";
        std::cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        std::cout << "\n\n\t06. CLOSE AN ACCOUNT";
        std::cout << "\n\n\t07. MODIFY AN ACCOUNT";
        std::cout << "\n\n\t08. EXIT";
        std::cout << "\n\n\tSelect Your Option (1-8) ";
        std::cin >> ch;
        system("cls");
        switch (ch) {
        case '1':
            write_account();
            break;
        case '2':
            std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
            delete_account(num);
            break;
        case '7':
            std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
            modify_account(num);
            break;
        case '8':
            std::cout << "\n\n\tThanks for using bank management system";
            break;
        default: std::cout << "\a";
        }
        std::cin.ignore();
        std::cin.get();
    } while (ch != '8');
    return 0;
}
