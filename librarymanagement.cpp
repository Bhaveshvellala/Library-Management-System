#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

class Book {
    public:
        int id;
        string title;
        string author;
        int stock;
};

vector<Book> library;

int readInt() {
    int x;
    while (!(cin >> x)) {
        if (cin.eof()) {
            cout << "\nInput ended. Exiting...\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    return x;
}

void loadData() {
    ifstream fin("library.txt");
    if (!fin) return;
    Book b;
    while (fin >> b.id) {
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, b.title);
        getline(fin, b.author);
        if (!(fin >> b.stock)) break; 
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        library.push_back(b);
    }
    fin.close();
}

void saveData() {
    ofstream fout("library.txt");
    for (size_t i = 0; i < library.size(); i++) {
        fout << library[i].id << endl;
        fout << library[i].title << endl;
        fout << library[i].author << endl;
        fout << library[i].stock << endl;
    }
    fout.close();
}

bool idExists(int id) {
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].id == id) return true;
    }
    return false;
}

void addBook() {
    Book b;
    cout << "\nEnter Book ID (must be > 0): ";
    b.id = readInt();
    while (b.id <= 0 || idExists(b.id)) {
        if (b.id <= 0)
            cout << "ID must be greater than 0! Enter again: ";
        else
            cout << "A book with this ID already exists! Enter a different ID: ";
        b.id = readInt();
    }
    cout << "Enter Book Title: ";
    getline(cin, b.title);
    cout << "Enter Author Name: ";
    getline(cin, b.author);
    cout << "Enter Number of Copies (must be >= 0): ";
    b.stock = readInt();
    while (b.stock < 0) {
        cout << "Stock cannot be negative! Enter again: ";
        b.stock = readInt();
    }

    library.push_back(b);
    saveData();
    cout << "\nBook Added Successfully!\n";
}

void searchBook() {
    string key;
    cout << "\nEnter Book Title or Author to Search: ";
    getline(cin, key);
    bool found = false;
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].title == key || library[i].author == key) {
            cout << "\nBook Found!\n";
            cout << "ID: " << library[i].id << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Available Copies: " << library[i].stock << endl;
            found = true;
        }
    }
    if (!found)
        cout << "\nNo Book Found!\n";
}

void issueBook() {
    int id;
    cout << "\nEnter Book ID to Issue: ";
    id = readInt();
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            if (library[i].stock > 0) {
                library[i].stock--;
                saveData();
                cout << "\nBook Issued Successfully!\nRemaining Copies: " << library[i].stock << endl;
            } else {
                cout << "\nBook Out of Stock!\n";
            }
            return;
        }
    }
    cout << "\nBook Not Found!\n";
}

void returnBook() {
    int id;
    cout << "\nEnter Book ID to Return: ";
    id = readInt();
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            library[i].stock++;
            saveData();
            cout << "\nBook Returned Successfully!\nTotal Copies: " << library[i].stock << endl;
            return;
        }
    }
    cout << "\nInvalid Book ID!\n";
}

void updateBook() {
    int id;
    cout << "\nEnter Book ID to Update: ";
    id = readInt();
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            cout << "\nCurrent Title: " << library[i].title;
            cout << "\nEnter New Title: ";
            getline(cin, library[i].title);
            cout << "Current Author: " << library[i].author;
            cout << "\nEnter New Author: ";
            getline(cin, library[i].author);
            cout << "Current Copies: " << library[i].stock;
            cout << "\nEnter New Stock (must be >= 0): ";
            library[i].stock = readInt();
            while (library[i].stock < 0) {
                cout << "Stock cannot be negative! Enter again: ";
                library[i].stock = readInt();
            }

            saveData();
            cout << "\nBook Updated Successfully!\n";
            return;
        }
    }
    cout << "\nBook Not Found!\n";
}

void deleteBook() {
    int id;
    cout << "\nEnter Book ID to Delete: ";
    id = readInt();
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            library.erase(library.begin() + i);
            saveData();
            cout << "\nBook Deleted Successfully!\n";
            return;
        }
    }
    cout << "\nBook Not Found!\n";
}

void displayBooks() {
    cout << "\n----- Library Books List -----\n";
    if (library.empty()) {
        cout << "\nNo books in the library yet!\n";
        return;
    }
    for (size_t i = 0; i < library.size(); i++) {
        cout << "\nBook ID: " << library[i].id;
        cout << "\nTitle: " << library[i].title;
        cout << "\nAuthor: " << library[i].author;
        cout << "\nAvailable Copies: " << library[i].stock << endl;
    }
}

int main() {
    loadData();
    int choice;
    while (true) {
        cout << "\n===== LIBRARY MENU =====\n";
        cout << "1. Add New Book\n2. Search Book\n3. Issue Book\n4. Return Book\n";
        cout << "5. Display All Books\n6. Update Book Details\n7. Delete Book\n8. Exit\nEnter your choice: ";
        choice = readInt();
        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: displayBooks(); break;
            case 6: updateBook(); break;
            case 7: deleteBook(); break;
            case 8: cout << "\nThank You! Exiting...\n"; return 0;
            default: cout << "\nInvalid Choice! Try Again.\n";
        }
    }
}
