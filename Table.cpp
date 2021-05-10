#include "Table.h"


bool operator== (const ArrayCell& left, const ArrayCell& right) {
    if (left.key == right.key && left.key_size == right.key_size)
        return true;

    return false;
}

///////////////* ФУНКЦИИ КЛАССА ITERATOR *\\\\\\\\\\\\\\\

void* Table::TableIterator::getElement(size_t &size) {
    return (current_cell->getElement(size));
}

bool Table::TableIterator::hasNext() {
    if(current_cell->hasNext())
        return true;
    else{
        for (int i = index + 1; i < container_size; ++i) {
            if(!table->map[i]->empty())
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
            if (!table->map[i]->empty()) {
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
    size_t data_size = sizeof data;
    if(map[index]->find(data, data_size) == nullptr) {
        map[index]->push_front(data, data_size);
        elements_count++;
        return 0;
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
    size_t data_size = sizeof data;
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
    return hash % 1'000'000;
}

///////////////* ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

int Table::size() {
    return elements_count;
}

size_t Table::max_bytes() {
    return _memory.maxBytes();
}

///// головная боль №2 \\\\\

//Container::Iterator* Table::find(void *elem, size_t size) {
//    TableIterator* finder = newIterator();
//    for (int i = 0; i < container_size; ++i) {
//
//    }
//}

Container::Iterator* Table::newIterator() {
    TableIterator* iterator = new TableIterator(this, nullptr, 0);
    return iterator;
}

Container::Iterator* Table::begin(){
    if(empty())
        return nullptr;
    for (int i = 0; i < container_size; ++i) {
        if(!this->map[i]->empty())
            return new TableIterator(this, dynamic_cast<List::Iterator*>(this->map[i]->begin()), i);
    }

}

Container::Iterator* Table::end(){
    if(empty())
        return nullptr;
    for (int i = container_size - 1; i >= 0; ++i) {
        if(!this->map[i]->empty())
            return new TableIterator(this, dynamic_cast<List::Iterator*>(this->map[i]->end()), i);
    }
}

void Table::remove(Iterator *iter) {

}

void Table::clear() {

}

bool Table::empty() {
    if(elements_count == 0)
        true;
    return false;
}

