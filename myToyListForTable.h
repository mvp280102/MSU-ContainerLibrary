#ifndef MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
#define MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
#include "myToyList.h"

struct ArrayCell{
    void* key;
    size_t key_size;
    void* elem;
    size_t elem_size;
};

class ListForTable : public List {
public:
    explicit ListForTable(MemoryManager &mem): List(mem) {}

    Iterator * find(void *elem, size_t size) override {
        if(empty())
            return nullptr;
        Iterator* temp = begin();
        while (temp->current != nullptr){
            if (size != temp->current->value_size) {
                temp->goToNext();
                continue;
            }
            if (compare(elem, temp->current->value))
                break;
            else temp->goToNext();
        }
        if(temp->current == nullptr)
            return nullptr;
        return temp;
    }

    bool compare(void* left, void* right){

        ArrayCell* real_left = static_cast<ArrayCell*>(left);
        ArrayCell* real_right = static_cast<ArrayCell*>(right);

        if (real_left->key_size == real_right->key_size) {
            if(memcmp(real_left->key, real_right->key, real_left->key_size) == 0)
                return true;
        }
        return false;

    }
};

#endif //MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
