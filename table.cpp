#include "table.h"

///////////////* ФУНКЦИИ КЛАССА ITERATOR *\\\\\\\\\\\\\\\

void* Table::TableIterator::getElement(size_t &size) {
    return (current_cell->getElement(size));
}

bool Table::TableIterator::hasNext() {
    if(current_cell->hasNext())
        return true;
    else{
        for (int i = index + 1; i < container_size; ++i) {
            if(table->map[i]->empty())
                return true;
        }
    }
    return false;
}

void Table::TableIterator::goToNext() {
    bool flag = false;
    if (current_cell->hasNext())
        current_cell->goToNext();
    else {
        for (int i = index + 1; i < container_size; ++i) {
            if (table->map[i]->empty()) {
                current_cell = table->map[i]->begin();
                flag = true;
                break;
            }
        }
        if (!flag) {
            throw Error("There is no next one");
        }
    }
}

bool Table::TableIterator::equals(Iterator *right) {
    if (current_cell == dynamic_cast<TableIterator*>(right)->current_cell)
        return true;
    return false;
}

///////////////* ПЕРСОНАЛЬНЫЕ ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

int Table::insertByKey(void *key, size_t keySize, void *elem, size_t elemSize){
    size_t index = hash_function(key, keySize);
    ArrayCell temp = {key, keySize, elem, elemSize};
    void* data = static_cast<void*>(&temp);
    size_t data_size = sizeof(temp);
    if(map[index] == nullptr) {
        map[index] = new ListForTable(_memory);
    }

    if(map[index]->empty()) {
        map[index]->push_front(data, data_size);
        elements_count++;
        return 0;
    } else {
        if (map[index]->find(data, data_size) == nullptr) {
            map[index]->push_front(data, data_size);
            elements_count++;
            return 0;
        }
    }
    return 1;
}

void Table::removeByKey(void *key, size_t keySize) {
    size_t index = hash_function(key, keySize);
    ArrayCell temp = {key, keySize, nullptr, 0};
    void* data = static_cast<void*>(&temp);
    size_t data_size = sizeof data;
    List::Iterator *tmp = map[index]->find(data, data_size);
    if(tmp != nullptr) {
        map[index]->remove(tmp);
        elements_count--;
    }
}

Container::Iterator* Table::findByKey(void *key, size_t keySize){
    size_t index = hash_function(key, keySize);
    ArrayCell temp = {key, keySize, nullptr, 0};
    void* data = static_cast<void*>(&temp);
    size_t data_size = sizeof(temp);
    return map[index]->find(data, data_size);
}

///// головная боль № 1\\\\\

void* Table::at(void *key, size_t keySize, size_t &valueSize){
    size_t index = hash_function(key, keySize);
    ArrayCell temp = {key, keySize, nullptr, 0};
    void* data = static_cast<void*>(&temp);
    size_t data_size = sizeof data;
    ArrayCell* findedCell = static_cast<ArrayCell*>(map[index]->find(data, data_size)->getElement(valueSize));
    return findedCell->elem;
}


size_t Table::hash_function(void *key, size_t keySize){
    size_t hash = 0;
    char* why_not = static_cast<char*>(key);
    for(int i = 0; i < keySize; ++i)
        hash = 31 * hash + why_not[i];
    return hash % container_size;
}

///////////////* ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

int Table::size() {
    return elements_count;
}

size_t Table::max_bytes() {
    return _memory.maxBytes();
}

Container::Iterator* Table::find(void *elem, size_t size) {
    TableIterator* finder = dynamic_cast<TableIterator *>(newIterator());
    size_t trash;
    for (int i = 0; i < container_size; ++i) {
        if(!map[i]->empty()) {
            finder->current_cell = map[i]->begin();
            do {
                ArrayCell *findedCell = static_cast<ArrayCell *>(finder->current_cell->getElement(trash));
                if (findedCell->elem == elem && findedCell->elem_size == size)
                    return new TableIterator(finder->current_cell, i, this);
                finder->goToNext();
            } while (finder->current_cell->hasNext());
        }
    }
    return nullptr;
}

Table::Iterator* Table::newIterator() {
    TableIterator* iterator = new TableIterator(nullptr, 0, this);
    return iterator;
}

Table::Iterator* Table::begin(){
    TableIterator* iterator = dynamic_cast<TableIterator *>(newIterator());
    if(iterator == nullptr)
        return nullptr;
    for (int i = 0; i < container_size; ++i) {
        if(!map[i]->empty())
            return new TableIterator(dynamic_cast<ListForTable::Iterator*>(map[i]->begin()), i, this);
    }
    return nullptr;
}

Table::Iterator* Table::end(){
    TableIterator* iterator = dynamic_cast<TableIterator *>(newIterator());
    if(iterator == nullptr)
        return nullptr;
    for (int i = container_size - 1; i >= 0; ++i) {
        if(!map[i]->empty())
            return new TableIterator(dynamic_cast<ListForTable::Iterator*>(map[i]->end()), i, this);
    }
    return nullptr;
}

void Table::remove(Iterator *iter) {
    bool okFlag = false;
    TableIterator* iterator = dynamic_cast<TableIterator *>(begin());
    ListForTable::Iterator* Iter = dynamic_cast<ListForTable::Iterator *>(iter);
    for (int i = 0; i < container_size; ++i) {
        do {
            if (iterator->current_cell == Iter) {
                map[i]->remove(Iter);
                okFlag = true;
                break;
            }
            iterator->current_cell->goToNext();
        }
        while(iterator->current_cell->hasNext());
        if(okFlag)
            break;
    }
}

void Table::clear() {
    for (int i = 0; i < container_size; ++i) {
        _memory.freeMem(map[i]);
        map[i] = nullptr;
    }
    elements_count = 0;
}

bool Table::empty() {
    if(size() == 0)
        return true;
    return false;
}

