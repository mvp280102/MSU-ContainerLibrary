#ifndef MSU_CONTAINERLIBRARY_MYTOYLIST_H
#define MSU_CONTAINERLIBRARY_MYTOYLIST_H

#include "Abstract-List.h"
#include <mem.h>


class List: public AbstractList {
private:
    struct Cell {
        void* value;
        size_t value_size;
        Cell* next;
    };

    Cell* beginning = nullptr;
    int cells_count;

public:
    List(MemoryManager &mem) : AbstractList(mem) {
        cells_count = 0;
    }

    class Iterator: public AbstractList::Iterator {
    private:
        Cell* current;
    public:
        void* getElement(size_t &size) override;

        bool hasNext() override;

        void goToNext() override;

        bool equals(Container::Iterator *right) override;

        ~Iterator() = default;

        friend List;
        friend class ListForTable;
    };

    void print(){
        Iterator* iterator = newIterator();
        for (int i = 0; i < size(); ++i) {
            cout << i << " element" << endl;
            char* string = static_cast<char*>(iterator->current->value);
            for (int j = 0; j < iterator->current->value_size; ++j) {
                cout << string[j];
            }
            cout << endl;
            iterator->goToNext();
        }
    }

    /////////////// * Функции List * \\\\\\\\\\\\\\\

    int push_front(void *elem, size_t elemSize) override;

    void pop_front() override;

    void* front(size_t &size) override;

    int insert(AbstractList::Iterator *iter, void *elem, size_t elemSize) override;

    /////////////// * Функции контейнера * \\\\\\\\\\\\\\\

    int size() override;

    size_t max_bytes() override;

    Iterator* find(void *elem, size_t size) override;

    Iterator* newIterator() override;

    void remove(Container::Iterator *iter) override;

    void clear() override;

    bool empty() override;

    friend class ListForTable;
};

#endif //MSU_CONTAINERLIBRARY_MYTOYLIST_H
