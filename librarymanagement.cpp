#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


class Book {
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;

    
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}

    
    void display() {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn
             << ", Status: " << (isAvailable ? "Available" : "Checked Out") << endl;
    }
};


class Borrower {
public:
    string name;
    string borrowerID;

    Borrower(string n, string id) : name(n), borrowerID(id) {}

    void display() {
        cout << "Name: " << name << ", ID: " << borrowerID << endl;
    }
};


class Transaction {
public:
    Book* book;
    Borrower* borrower;
    time_t checkoutDate;
    time_t returnDate;

    
    Transaction(Book* b, Borrower* br) : book(b), borrower(br), returnDate(0) {
        book->isAvailable = false;
        checkoutDate = time(0); 
    }

    
    void returnBook() {
        book->isAvailable = true;
        returnDate = time(0); 
    }

    
    double calculateFine() {
        if (returnDate == 0) return 0; 

        double fine = 0;
        double lateFeePerDay = 1.0; 

        
        double diff = difftime(returnDate, checkoutDate) / (60 * 60 * 24);
        if (diff > 14) { 
            fine = (diff - 14) * lateFeePerDay;
        }
        return fine;
    }

    
    void displayTransaction() {
        cout << "Transaction details:" << endl;
        borrower->display();
        book->display();
        cout << "Checkout Date: " << ctime(&checkoutDate);
        if (returnDate != 0) {
            cout << "Return Date: " << ctime(&returnDate);
            cout << "Fine: " << calculateFine() << endl;
        }
    }
};


class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    
    void addBook(string title, string author, string isbn) {
        books.push_back(Book(title, author, isbn));
    }

    
    void addBorrower(string name, string borrowerID) {
        borrowers.push_back(Borrower(name, borrowerID));
    }

    
    void searchBook() {
        string search;
        cout << "Enter title, author, or ISBN to search: ";
        cin.ignore();
        getline(cin, search);

        bool found = false;
        for (auto& book : books) {
            if (book.title.find(search) != string::npos || book.author.find(search) != string::npos || book.isbn.find(search) != string::npos) {
                book.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No book found matching the search criteria." << endl;
        }
    }

    
    void checkoutBook() {
        string borrowerID;
        cout << "Enter borrower ID: ";
        cin >> borrowerID;

        Borrower* borrower = nullptr;
        for (auto& b : borrowers) {
            if (b.borrowerID == borrowerID) {
                borrower = &b;
                break;
            }
        }

        if (borrower == nullptr) {
            cout << "Borrower not found!" << endl;
            return;
        }

        string isbn;
        cout << "Enter ISBN of the book to checkout: ";
        cin >> isbn;

        Book* book = nullptr;
        for (auto& b : books) {
            if (b.isbn == isbn && b.isAvailable) {
                book = &b;
                break;
            }
        }

        if (book == nullptr) {
            cout << "Book not available for checkout!" << endl;
            return;
        }

        transactions.push_back(Transaction(book, borrower));
        cout << "Book checked out successfully!" << endl;
    }

    
    void returnBook() {
        string isbn;
        cout << "Enter ISBN of the book to return: ";
        cin >> isbn;

        for (auto& transaction : transactions) {
            if (transaction.book->isbn == isbn && transaction.book->isAvailable == false) {
                transaction.returnBook();
                cout << "Book returned successfully!" << endl;
                transaction.displayTransaction();
                return;
            }
        }

        cout << "No matching book found or book already returned!" << endl;
    }

    
    void displayBooks() {
        cout << "\nBooks in the Library:" << endl;
        for (auto& book : books) {
            book.display();
        }
    }

    
    void displayBorrowers() {
        cout << "\nRegistered Borrowers:" << endl;
        for (auto& borrower : borrowers) {
            borrower.display();
        }
    }


    void displayTransactions() {
        cout << "\nAll Transactions:" << endl;
        for (auto& transaction : transactions) {
            transaction.displayTransaction();
        }
    }
};


int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System Menu:" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Add a Borrower" << endl;
        cout << "3. Search for a Book" << endl;
        cout << "4. Checkout a Book" << endl;
        cout << "5. Return a Book" << endl;
        cout << "6. Display All the Books" << endl;
        cout << "7. Display All the Borrowers" << endl;
        cout << "8. Display All the Transactions" << endl;
        cout << "9. Exit system ss" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        
        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                break;
            }
            case 2: {
                string name, borrowerID;
                cout << "Enter borrower name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                library.addBorrower(name, borrowerID);
                break;
            }
            case 3:
                library.searchBook();
                break;
            case 4:
                library.checkoutBook();
                break;
            case 5:
                library.returnBook();
                break;
            case 6:
                library.displayBooks();
                break;
            case 7:
                library.displayBorrowers();
                break;
            case 8:
                library.displayTransactions();
                break;
            case 9:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
