#include <iostream>
#include <vector>
#include <string>
#include <cstring>

int bookCount = 0;

class Book {
public:
    std::string title;
    std::string author;
    int year;
    char* notes;

    Book(const std::string& t, const std::string& a, int y)
        : title(t), author(a), year(y) {
        notes = new char[100];
        std::strcpy(notes, "Default notes");
    }


    Book(const Book& other)
        : title(other.title), author(other.author), year(other.year), notes(other.notes) {}

    virtual ~Book() {}

 
    virtual void displayInfo() const {
        std::cout << "Title: " << title
                  << ", Author: " << author
                  << ", Notes: "<< notes 
                  << ", Year: " << year << std::endl;
    }
};


class EBook : public Book {
public:
    std::string format;

    EBook(const std::string& t, const std::string& a, int y, const std::string& f)
        : Book(t, a, y), format(f) {}

    void displayInfo() const override {
        std::cout << "[EBook] Title: " << title
                  << ", Author: " << author
                  << ", Year: " << year
                  << ", Notes: "<< notes 
                  << ", Format: " << format << std::endl;
    }
};


class PrintedBook : public Book {
public:
    int pages;

    PrintedBook(const std::string& t, const std::string& a, int y, int p)
        : Book(t, a, y), pages(p) {}

    void displayInfo() const override {
        std::cout << "[PrintedBook] Title: " << title
                  << ", Author: " << author
                  << ", Year: " << year
                  << ", Notes: "<< notes 
                  << ", Pages: " << pages << std::endl;
    }
};


class Library {
public:
    std::vector<Book> books;  

    void addBook(Book b) {
        books.push_back(b);  
        bookCount++;
    }

    void displayBooks() {
        if (books.empty()) {
            std::cout << "No books in the library." << std::endl;
            return;
        }

        std::cout << "********************Books in the library********************" << std::endl;
        for (const auto& book : books) {
            book.displayInfo();  
        }
    }

    void clearLibrary() {
        if (bookCount == 0) {
            std::cout << "Library is already empty." << std::endl;
            goto end;
        }

        books.clear();
        bookCount = 0;

    end:
        std::cout << "Library cleared." << std::endl;
    }

    Book* createBook(const std::string& title, const std::string& author, int year) {
        return new Book(title, author, year); 
    }
};


int main() {
    Library library;

    Book b1("1984", "George Orwell", 1949);
    strcpy(b1.notes, "Classic dystopian novel - 1");

    EBook ebook("Digital Fortress", "Dan Brown", 1998, "PDF");
    PrintedBook printed("The Alchemist", "Paulo Coelho", 1988, 208);

    Book* newBook = library.createBook("Fahrenheit 451", "Ray Bradbury", 1953);
    library.addBook(b1);       
    library.addBook(ebook);     
    library.addBook(printed);   
    
    library.displayBooks();

    Book b2 = b1;
    b2.title = "Thinking in C++";
    b2.author = "Bruce Eckel";
    b2.year = 2000;
    strcpy(b2.notes, "Classic dystopian novel - 2");
    library.addBook(b2);  

    EBook b3(ebook);
    strcpy(b3.notes, "novel - 2");
    library.addBook(b3);
    
    library.displayBooks();

    library.clearLibrary();


    return 0;
}
