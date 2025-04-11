// generic list implementation with array
#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <cstdint> // std::size_t
#include <stdexcept>

namespace structures { // declaring the namespace
    
    template <typename T> // declaring the class template
    class ArrayList {   // declaring the class
        private:
            T* contents;  // pointer to the array that stores the elements
            std::size_t size_;  // current number of elements in the list
            std::size_t max_size_;  // maximum size of the list
            static const auto DEFAULT_MAX = 10u; // default maximum size of the list
        public:
            // default constructor
            ArrayList();
            // constructor with parameter
            explicit ArrayList(std::size_t max);
            // destructor
            ~ArrayList();
            // methods
            void clear();
            void push_back(const T& data); // add one element to the end of the list
            void push_front(const T& data); // add one element to the beginning of the list
            void insert(const T& data, std::size_t index); // add one element at the specified index
            void insert_sorted(const T& data); // add one element in sorted order
            T pop(std::size_t index); // remove and return the element at the specified index
            T pop_back(); // remove and return the last element
            T pop_front(); // remove and return the first element
            void remove(const T& data); // remove the first occurrence of the specified element
            bool isFull() const; // check if the list is full
            bool isEmpty() const;
            bool iscontains(const T& data) const; // check if the especified element is present   
            std::size_t find(const T& data) const; // find the index of the specified element
            std::size_t size() const; // get the current size of the list
            std::size_t max_size() const; // get the maximum size of the list
            T& at(std::size_t index); // get the element at the specified index
            T& operator[](std::size_t index); // get the element at the specified index
            const T& at(std::size_t index) const; // get the element at the specified index
            const T& operator[](std::size_t index) const; // get the element at the specified index
    };
} // namespace structures 
#endif

// defining the default constructor
template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX; // set the maximum size to the default value
    contents = new T[max_size_]; // allocate memory for the array
    size_ = 0; // initialize the size to 0
}

// defining the constructior with parameter
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size];
    size_ = 0
}
// implementation of the methods
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (isFull()) {
        throw std::out_of_range("List is full");
    }
    contents[++size_] = data; // Incrementa o primeiro elemento
}
