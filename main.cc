#include <iostream>
#include <memory>
#include <vector>
#include <string>

/*
Name:Roberto Velazquez
CWID:885666107
*/

template<typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    Tab<T>* prev;
    Tab<T>* next;

    Tab(std::string url, std::string name, T memory) {
        this->url = url;
        this->name = name;
        this->memory = memory;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

template<typename T>
class Browser {
private:
    Tab<T>* head;
    Tab<T>* tail;
    Tab<T>* current;
    std::vector<std::pair<std::string, std::string>> bookmarks;

public:
    Browser() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    void addNewTab(std::string url, std::string name, T memory) {
        Tab<T>* newTab = new Tab<T>(url, name, memory);
        if (head == nullptr) {
            head = newTab;
            tail = newTab;
            current = newTab;
        }
        else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab;
        }
    }

    void switchToPrevTab() {
        std::cout << "Switch to previous tab = " << std::endl;
        if (current->prev != nullptr) {
            current = current->prev;
            std::cout << current->url << std::endl;
            std::cout << current->name << std::endl;
            std::cout << current->memory << std::endl;
        }
        else {
            std::cout << "No previous tab" << std::endl;
        }
    }

    void switchToNextTab() {
        std::cout << "Switch to next tab = " << std::endl;
        if (current->next != nullptr) {
            current = current->next;
            std::cout << current->url << std::endl;
            std::cout << current->name << std::endl;
            std::cout << current->memory << std::endl;
        }
        else {
            std::cout << "No next tab" << std::endl;
        }
    }

    void closeCurrentTab() {
        std::cout << "Now the current tab = ";
        if (current == head && current->next == nullptr) {
            std::cout << "None" << std::endl;
            delete current;
            head = nullptr;
            tail = nullptr;
            current = nullptr;
            return;
        }
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
            std::cout << head->name << std::endl;
            delete current;
            current = head;
            return;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            std::cout << tail->name << std::endl;
            delete current;
            current = tail;
            return;
        }
        else {
            Tab<T>* temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->prev;
            std::cout << current->name << std::endl;
            delete temp;
            return;
        }
    }

    void bookmarkCurrent() {
        for (auto bookmark : bookmarks) {
            if (bookmark.first == current->name && bookmark.second == current->url) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }
        bookmarks.push_back(std::make_pair(current->name, current->url));
    }

    void showBookmarkTab() {
        std::cout << "Bookmarks:" << std::endl;
        for (auto bookmark : bookmarks) {
            std::cout << bookmark.first << " (" << bookmark.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        std::cout << "Before function executed:" << std::endl;
        display();
        if (current == head)
            return;
        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        current->prev = nullptr;
        current->next = head;
        head->prev = current;
        head = current;
        std::cout << "After function executed:" << std::endl;
        display();
    }

    T total_memory() {
        T totalMemory = 0;
        Tab<T>* temp = head;
        while (temp != nullptr) {
            totalMemory += temp->memory;
            temp = temp->next;
        }
        return totalMemory;
    }

    void deleteTab() {
        std::cout << "Before deletion:" << std::endl;
        display();
        if (head == nullptr) {
            std::cout << "No tabs to delete" << std::endl;
            return;
        }

        Tab<T>* maxMemoryTab = head;
        Tab<T>* temp = head->next;
        while (temp != nullptr) {
            if (temp->memory > maxMemoryTab->memory)
                maxMemoryTab = temp;
            temp = temp->next;
        }

        if (maxMemoryTab == head) {
            head = head->next;
            if (head != nullptr)
                head->prev = nullptr;
        }
        else if (maxMemoryTab == tail) {
            tail = tail->prev;
            if (tail != nullptr)
                tail->next = nullptr;
        }
        else {
            maxMemoryTab->prev->next = maxMemoryTab->next;
            maxMemoryTab->next->prev = maxMemoryTab->prev;
        }

        std::cout << "Deleted element = " << maxMemoryTab->name << " with memory size = " << maxMemoryTab->memory << std::endl;
        delete maxMemoryTab;
        std::cout << "After deletion:" << std::endl;
        display();
    }

    void display() {
        std::cout << "Browser tab list =" << std::endl;
        Tab<T>* curr = head;
        while (curr) {
            std::cout << "| " << curr->name << " x |-->";
            curr = curr->next;
        }
        std::cout << std::endl << std::endl;
    }
};

int main() {
    
    Browser<double> b1;
    b1.addNewTab("https://www.google.com", "Google", 23.45);
    b1.display();
    b1.switchToPrevTab();
    b1.switchToNextTab();
    b1.addNewTab("https://www.youtube.com", "YouTube", 56);
    b1.bookmarkCurrent();
    b1.display();
    b1.addNewTab("https://www.geeksforgeeks.com", "GeeksForGeeks", 45.78);
    b1.bookmarkCurrent();
    b1.addNewTab("https://chat.openai.com", "ChatGPT", 129);
    b1.addNewTab("https://linkedin.com", "LinkedIn", 410);
    b1.bookmarkCurrent();
    b1.addNewTab("https://github.com", "Github", 110);
    b1.addNewTab("https://kaggle.com", "Kaggle", 310);
    b1.bookmarkCurrent();
    b1.display();
    std::cout << "Total memory consumption = " << b1.total_memory() << "MB" << std::endl;
    b1.showBookmarkTab();
    b1.moveCurrentToFirst();
    b1.deleteTab();
    b1.display();
    b1.switchToNextTab();
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.showBookmarkTab();
    std::cout << "Total Memory Consumption = " << b1.total_memory() << "MB" << std::endl;
    b1.deleteTab();
    b1.display();
    b1.addNewTab("https://docs.google.com/", "Google Docs", 102.34);
    b1.display();
    b1.switchToPrevTab();
    b1.switchToPrevTab();
    b1.switchToPrevTab();
    b1.bookmarkCurrent();
    b1.showBookmarkTab();
    b1.total_memory();
    b1.deleteTab();
    b1.display();
    
    return 0;
}
