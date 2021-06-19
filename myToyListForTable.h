#ifndef MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
#define MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
#include "myToyList.h"

struct ArrayCell{
    void* key = nullptr;
    size_t key_size;
    void* elem = nullptr;
    size_t elem_size;
};

class ListForTable : public List {
public:
    explicit ListForTable(MemoryManager &mem): List(mem) {}

    Iterator * find(void *elem, size_t size) override {
        Iterator* iter = newIterator();
        size_t trash;
        do {
            ArrayCell temp = *(ArrayCell*)(iter->getElement(trash));
            if(temp.key_size == size) {
                if (memcmp(temp.key, elem, size) == 0)
                    break;
            }
            if (iter->hasNext())
                iter->goToNext();
            else
                return nullptr;
        } while (iter->current != nullptr);
        if(iter->current == nullptr)
            return nullptr;
        return iter;
    }
};

#endif //MSU_CONTAINERLIBRARY_MYTOYLISTFORTABLE_H
