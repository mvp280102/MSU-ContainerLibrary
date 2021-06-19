#include "Table.h"

///////////////* ФУНКЦИИ КЛАССА ITERATOR *\\\\\\\\\\\\\\\

void* Table::TableIterator::getElement(size_t &size) {
    if(current_cell == nullptr)
        return nullptr;
    ArrayCell* temp = static_cast<ArrayCell*>(current_cell->getElement(size));
    if(temp == nullptr)
        return nullptr;
    size = temp->elem_size;
    return temp->elem;
}

bool Table::TableIterator::hasNext() {
    if(current_cell == nullptr)
        return false;
    if(current_cell->hasNext())
        return true;
    else{
        for (int i = index + 1; i < CONTAINER_SIZE; ++i) {
            if(table->map[i] != nullptr && !table->map[i]->empty())
                return true;
        }
    }
    return false;
}

void Table::TableIterator::goToNext() {
    if (current_cell->hasNext())
        current_cell->goToNext();
    else {
        for (int i = index + 1; i < CONTAINER_SIZE; ++i) {
            if (table->map[i] != nullptr && !table->map[i]->empty()) {
                current_cell = table->map[i]->newIterator();
                index = i;
                return;
            }
        }
    }
}

bool Table::TableIterator::equals(Iterator *right) {
    if (current_cell == nullptr || right == nullptr)
        return false;
    return current_cell->equals((dynamic_cast<TableIterator*>(right))->current_cell);
}

///////////////* ПЕРСОНАЛЬНЫЕ ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

int Table::insertByKey(void *key, size_t keySize, void *elem, size_t elemSize){
    size_t index = hash_function(key, keySize);

    char *keyToSave = static_cast<char*>(_memory.allocMem(keySize));
    char *elemToSave = static_cast<char*>(_memory.allocMem(elemSize));
    memcpy(keyToSave, key, keySize);
    memcpy(elemToSave, elem, elemSize);

    ArrayCell temp = {keyToSave, keySize, elemToSave, elemSize};
    void* data = static_cast<void*>(&temp);
    size_t data_size = sizeof(temp);
    if(map[index] == nullptr) {
        map[index] = new (_memory.allocMem(sizeof (ListForTable))) ListForTable(_memory);
    }

    if(map[index]->empty()) {
        map[index]->push_front(data, data_size);
        elements_count++;

        return 0;
    } else {
        if (map[index]->find(key, keySize) == nullptr) {
            map[index]->push_front(data, data_size);
            elements_count++;
            return 0;
        }
    }

    return 1;
}

void Table::removeByKey(void *key, size_t keySize) {
    size_t index = hash_function(key, keySize);

    if(map[index] != nullptr) {
        ListForTable::Iterator *tmp = map[index]->find(key, keySize);
        if (tmp != nullptr) {
            map[index]->remove(tmp);
            elements_count--;
        }

        if (map[index]->empty()) {
            _memory.freeMem(map[index]);
            map[index] = nullptr;
        }
    }
}

Container::Iterator* Table::findByKey(void *key, size_t keySize){
    size_t index = hash_function(key, keySize);
    if(map[index] == nullptr || map[index]->empty())
        return nullptr;
    ListForTable::Iterator* temp = dynamic_cast<ListForTable::Iterator*>(map[index]->find(key, keySize));
    if (temp == nullptr)
        return nullptr;
    return new TableIterator(temp, (int)index, this);
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

size_t Table::hash_function(void *key, size_t keySize) {
    return common_hash_function(key, keySize);
}

///////////////* ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

Container::Iterator* Table::find(void *elem, size_t size) {
    TableIterator* finder = dynamic_cast<TableIterator *>(newIterator());
    while (finder!= nullptr && finder->current_cell != nullptr) {
        size_t trash;
        ArrayCell *findedCell = static_cast<ArrayCell *>(finder->current_cell->getElement(trash));
        if (findedCell->elem_size == size && memcmp(findedCell->elem, elem, size) == 0)
            return new TableIterator(finder->current_cell, finder->index, this);
        finder->goToNext();
    }

    return nullptr;
}

Table::Iterator* Table::newIterator() {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        if(map[i] != nullptr)
            return new TableIterator(dynamic_cast<ListForTable::Iterator*>(map[i]->newIterator()), i, this);
    }
    return nullptr;
}

void Table::remove(Iterator *iter){

    TableIterator* Iter = dynamic_cast<TableIterator *>(iter);
    if(Iter == nullptr || Iter->current_cell == nullptr)
        return;

    if(map[Iter->index] != nullptr || !map[Iter->index]->empty())
    map[Iter->index]->remove(Iter->current_cell);
    elements_count--;


    size_t trash;

    if (Iter->getElement(trash) == nullptr) {
        if (map[Iter->index]->empty()) {
            _memory.freeMem(map[Iter->index]);
            map[Iter->index] = nullptr;
        }
        if(Iter->hasNext())
            Iter->goToNext();
        else{
            delete Iter->current_cell;
            Iter->current_cell = nullptr;
            Iter->index = -1;
        }
    }
}

void Table::clear() {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        _memory.freeMem(map[i]);
        map[i] = nullptr;
    }
    elements_count = 0;
}


