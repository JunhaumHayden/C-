#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>
#include <cstring>
.3
namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        size_ = 0;
        contents = new T[max_size_];
    }

    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        size_ = 0;
        contents = new T[max_size_];
    }

    ~ArrayList() {
        delete[] contents;
    }

    void clear() {
        size_ = 0;
    }

    void push_back(const T& data) {
        insert(data, size_);
    }

    void push_front(const T& data) {
        insert(data, 0);
    }

    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("List is full");
        }
        if (index > size_) {
            throw std::out_of_range("Invalid index");
        }

        for (std::size_t i = size_; i > index; i--) {
            contents[i] = contents[i - 1];
        }
        contents[index] = data;
        size_++;
    }

    void insert_sorted(const T& data) {
        if (full()) {
            throw std::out_of_range("List is full");
        }

        std::size_t i = 0;
        while (i < size_ && contents[i] < data) {
            i++;
        }
        insert(data, i);
    }

    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        if (index >= size_) {
            throw std::out_of_range("Invalid index");
        }

        T data = contents[index];
        for (std::size_t i = index; i < size_ - 1; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return data;
    }

    T pop_back() {
        return pop(size_ - 1);
    }

    T pop_front() {
        return pop(0);
    }

    void remove(const T& data) {
        std::size_t index = find(data);
        if (index != size_) {
            pop(index);
        }
    }

    bool full() const {
        return size_ == max_size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    bool contains(const T& data) const {
        return find(data) != size_;
    }

    std::size_t find(const T& data) const {
        for (std::size_t i = 0; i < size_; i++) {
            if (contents[i] == data) {
                return i;
            }
        }
        return size_;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t max_size() const {
        return max_size_;
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Invalid index");
        }
        return contents[index];
    }

    T& operator[](std::size_t index) {
        return contents[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Invalid index");
        }
        return contents[index];
    }

    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};

class ArrayListString : public ArrayList<char*> {
 public:
    ArrayListString() : ArrayList() {}
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    ~ArrayListString() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const char *data) {
        insert(data, size());
    }

    void push_front(const char *data) {
        insert(data, 0);
    }

    void insert(const char *data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("List is full");
        }

        char *new_data = new char[strlen(data) + 1];
        strcpy(new_data, data);

        ArrayList<char*>::insert(new_data, index);
    }

    void insert_sorted(const char *data) {
        if (full()) {
            throw std::out_of_range("List is full");
        }

        std::size_t i = 0;
        while (i < size() && strcmp(ArrayList<char*>::at(i), data) < 0) {
            i++;
        }

        insert(data, i);
    }

    char *pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        char *data = ArrayList<char*>::pop(index);
        char *return_data = new char[strlen(data) + 1];
        strcpy(return_data, data);

        delete[] data;
        return return_data;
    }

    char *pop_back() {
        return pop(size() - 1);
    }

    char *pop_front() {
        return pop(0);
    }

    void remove(const char *data) {
        std::size_t index = find(data);
        if (index != size()) {
            char *removed = ArrayList<char*>::pop(index);
            delete[] removed;
        }
    }

    bool contains(const char *data) {
        return find(data) != size();
    }

    std::size_t find(const char *data) {
        for (std::size_t i = 0; i < size(); i++) {
            if (strcmp(ArrayList<char*>::at(i), data) == 0) {
                return i;
            }
        }
        return size();
    }
};

}  // namespace structures

#endif