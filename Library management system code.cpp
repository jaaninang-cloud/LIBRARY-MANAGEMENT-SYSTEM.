#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// -------------------- Book Class --------------------
class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        available = true;
    }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return isbn; }
    bool isAvailable() { return available; }

    void setAvailability(bool status) { available = status; }

    void displayBook() {
        cout << "Title: " << title
             << ", Author: " << author
             << ", ISBN: " << isbn
             << ", Status: " << (available ? "Available" : "Borrowed")
             << endl;
    }
};

// -------------------- LibraryUser Class --------------------
class LibraryUser {
private:
    string userID;
    string name;
    vector<string> borrowedBooks;

public:
    LibraryUser(string id, string n) {
        userID = id;
        name = n;
    }

    string getUserID() { return userID; }
    string getName() { return name; }

    void borrowBook(string isbn) {
        borrowedBooks.push_back(isbn);
    }

    void returnBook(string isbn) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), isbn), borrowedBooks.end());
    }

    void displayBorrowedBooks() {
        cout << "Borrowed Books by " << name << ":" << endl;
        if (borrowedBooks.empty()) {
            cout << "  None" << endl;
        } else {
            for (auto &b : borrowedBooks) cout << "  ISBN: " << b << endl;
        }
    }
};

// -------------------- Library Class --------------------
class Library {
private:
    vector<Book> books;
    vector<LibraryUser> users;

public:
    void addBook(string title, string author, string isbn) {
        books.push_back(Book(title, author, isbn));
        cout << "Book added successfully!" << endl;
    }

    void displayAllBooks() {
        cout << "\n--- List of Books ---\n";
        for (auto &b : books) {
            b.displayBook();
        }
        if (books.empty()) cout << "No books available." << endl;
    }

    void registerUser(string id, string name) {
        users.push_back(LibraryUser(id, name));
        cout << "User registered successfully!" << endl;
    }

    void displayAllUsers() {
        cout << "\n--- List of Users ---\n";
        for (auto &u : users) {
            cout << "UserID: " << u.getUserID() << ", Name: " << u.getName() << endl;
        }
        if (users.empty()) cout << "No users registered." << endl;
    }

    void borrowBook(string isbn, string userID) {
        for (auto &b : books) {
            if (b.getISBN() == isbn) {
                if (b.isAvailable()) {
                    for (auto &u : users) {
                        if (u.getUserID() == userID) {
                            b.setAvailability(false);
                            u.borrowBook(isbn);
                            cout << u.getName() << " borrowed the book: " << b.getTitle() << endl;
                            return;
                        }
                    }
                    cout << "User not found!" << endl;
                    return;
                } else {
                    cout << "Book is already borrowed!" << endl;
                    return;
                }
            }
        }
        cout << "Book not found!" << endl;
    }

    void returnBook(string isbn, string userID) {
        for (auto &b : books) {
            if (b.getISBN() == isbn) {
                for (auto &u : users) {
                    if (u.getUserID() == userID) {
                        b.setAvailability(true);
                        u.returnBook(isbn);
                        cout << u.getName() << " returned the book: " << b.getTitle() << endl;
                        return;
                    }
                }
                cout << "User not found!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void displayBorrowedBooks(string userID) {
        for (auto &u : users) {
            if (u.getUserID() == userID) {
                u.displayBorrowedBooks();
                return;
            }
        }
        cout << "User not found!" << endl;
    }
};

// -------------------- Main Program --------------------
int main() {
    Library library;
    int choice;

    do {
        cout << "\n===== Library Menu =====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Register User" << endl;
        cout << "4. Display All Users" << endl;
        cout << "5. Borrow Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Display Borrowed Books of a User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author, isbn;
            cout << "Enter book title: "; getline(cin, title);
            cout << "Enter author: "; getline(cin, author);
            cout << "Enter ISBN: "; getline(cin, isbn);
            library.addBook(title, author, isbn);
        } else if (choice == 2) {
            library.displayAllBooks();
        } else if (choice == 3) {
            string id, name;
            cout << "Enter user ID: "; getline(cin, id);
            cout << "Enter name: "; getline(cin, name);
            library.registerUser(id, name);
        } else if (choice == 4) {
            library.displayAllUsers();
        } else if (choice == 5) {
            string isbn, id;
            cout << "Enter ISBN to borrow: "; getline(cin, isbn);
            cout << "Enter User ID: "; getline(cin, id);
            library.borrowBook(isbn, id);
        } else if (choice == 6) {
            string isbn, id;
            cout << "Enter ISBN to return: "; getline(cin, isbn);
            cout << "Enter User ID: "; getline(cin, id);
            library.returnBook(isbn, id);
        } else if (choice == 7) {
            string id;
            cout << "Enter User ID: "; getline(cin, id);
            library.displayBorrowedBooks(id);
        }
    } while (choice != 0);

    cout << "Exiting Library System..." << endl;
    return 0;
}
