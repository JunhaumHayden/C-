// linkedlist_extensions.h
#pragma once

#include "linkedlist.h"  // Classe original da lista encadeada

namespace structures {

template<typename T>
class LinkedListExtensions {
 public:
    void invert() {
        if (size() <2) return;
        Node* next = list.next()
    }

    static LinkedList<T> clone(const LinkedList<T>& list) {
        LinkedList<T> new_list;
        auto* curr = list.head;
        while (curr != nullptr) {
            new_list.push_back(curr->data);
            curr = curr->next;
        }
        return new_list;
    }

    static LinkedList<T> slicing(const LinkedList<T>& list, int start, int stop, int step) {
        LinkedList<T> result;
        if (start < 0 || stop > static_cast<int>(list.size()) || step <= 0) return result;

        auto* curr = list.head;
        int index = 0;

        while (curr != nullptr && index < stop) {
            if (index >= start && ((index - start) % step == 0)) {
                result.push_back(curr->data);
            }
            curr = curr->next;
            ++index;
        }

        return result;
    }

    static void append(LinkedList<T>& list, const LinkedList<T>& list_add) {
        auto* curr = list_add.head;
        while (curr != nullptr) {
            list.push_back(curr->data);
            curr = curr->next;
        }
    }

    static LinkedList< LinkedList<T>* > halve(const LinkedList<T>& list) {
        auto* even = new LinkedList<T>();
        auto* odd = new LinkedList<T>();
        LinkedList< LinkedList<T>* > result;

        auto* curr = list.head;
        int index = 0;

        while (curr != nullptr) {
            if (index % 2 == 0)
                even->push_back(curr->data);
            else
                odd->push_back(curr->data);
            curr = curr->next;
            ++index;
        }

        result.push_back(even);
        result.push_back(odd);
        return result;
    }
};

}  // namespace structures
