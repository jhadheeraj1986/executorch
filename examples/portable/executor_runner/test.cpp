#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <ranges>
#include <algorithm>
#include <functional>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string notes;

protected:
    void display() const {
        std::cout << "Title: " << title
                  << ", Author: " << author
                  << ", Year: " << year;
    }
    
public:
    Book(const std::string& t, const std::string& a, int y)
        : title(t), author(a), year(y), notes("Default notes")
    {}

    Book(const Book&) = delete;
    Book(Book&&) = delete;

    virtual ~Book() = default;

    virtual void displayInfo() const {
        display();
        std::cout << '\n';
    }
};

class EBook : public Book {
public:
    std::string format;

    EBook(const std::string& t, const std::string& a, int y, const std::string& f)
        : Book(t, a, y), format(f) {}

    void displayInfo() const override {
        std::cout << "[EBook] ";
        Book::display();
        std::cout << ", Format: " << format << std::endl;
    }
};

class PrintedBook : public Book {
public:
    int pages;

    PrintedBook(const std::string& t, const std::string& a, int y, int p)
        : Book(t, a, y), pages(p) {}

    void displayInfo() const override {
        std::cout << "[PrintedBook] ";
        Book::display();
        std::cout << ", Pages: " << pages << std::endl;
    }
};

class Library {
public:
    std::vector<std::unique_ptr<Book>> books;

    void addBook(std::unique_ptr<Book> b) {
        books.push_back(std::move(b));
    }

    void displayBooks() {
        std::cout << books.size() << " Books in the library:" << std::endl;
        std::ranges::for_each(books, std::mem_fn(&Book::displayInfo));
    }
};


int main() {
    Library library;

    std::unique_ptr<Book> b1 = std::make_unique<Book>("1984", "George Orwell", 1949);

    std::unique_ptr<Book> ebook = std::make_unique<EBook>("Digital Fortress", "Dan Brown", 1998, "PDF");
    std::unique_ptr<Book> printed = std::make_unique<PrintedBook>("The Alchemist", "Paulo Coelho", 1988, 208);

    library.addBook(std::move(b1));
    library.addBook(std::move(ebook));
    library.addBook(std::move(printed));

    library.displayBooks();

    return 0;
}

