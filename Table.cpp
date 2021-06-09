#include "Table.h"

///////////////* ФУНКЦИИ КЛАССА ITERATOR *\\\\\\\\\\\\\\\

void* Table::TableIterator::getElement(size_t &size) {
	ArrayCell* temp = static_cast<ArrayCell*>(current_cell->getElement(size));
	return temp->elem;
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
			if (table->map[i] != nullptr) {
				current_cell = table->map[i]->newIterator();
				index = i;
				flag = true;
				break;
			}
		}
		if (!flag) {
//            throw Error("There is no next one");
			current_cell = nullptr;
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

	char *keyToSave = static_cast<char*>(_memory.allocMem(sizeof(keySize)));
	char *elemToSave = static_cast<char*>(_memory.allocMem(sizeof(elemSize)));
	memcpy(keyToSave, key, keySize);
	memcpy(elemToSave, elem, elemSize);

	ArrayCell temp = {keyToSave, keySize, elemToSave, elemSize};
	void* data = static_cast<void*>(&temp);
	size_t data_size = sizeof(temp);
	if(map[index] == nullptr) {
		map[index] = new TableList(_memory);
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

	TableList::Iterator *tmp = map[index]->find(key, keySize);
	if (tmp != nullptr) {
		map[index]->remove(tmp);
		elements_count--;
	}

	if (map[index]->empty()){
		_memory.freeMem(map[index]);
		map[index] = nullptr;
	}
}

Container::Iterator* Table::findByKey(void *key, size_t keySize){
	size_t index = hash_function(key, keySize);
	if(map[index] == nullptr || map[index]->empty())
		return nullptr;
	TableList::Iterator* temp = dynamic_cast<TableList::Iterator*>(map[index]->find(key, keySize));
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

///////////////* ФУНКЦИИ КЛАССА TABLE *\\\\\\\\\\\\\\\

int Table::size() {
	return elements_count;
}

size_t Table::max_bytes() {
	return _memory.maxBytes();
}

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
	for (int i = 0; i < container_size; ++i) {
		if(map[i] != nullptr)
			return new TableIterator(dynamic_cast<TableList::Iterator*>(map[i]->newIterator()), i, this);
	}
	return nullptr;
}

void Table::remove(Iterator *iter){
	TableIterator* Iter = dynamic_cast<TableIterator *>(iter);
	if(Iter != nullptr && Iter->current_cell != nullptr) {
		map[Iter->index]->remove(Iter->current_cell);
		elements_count--;
	}

	if (map[Iter->index]->empty()){
		_memory.freeMem(map[Iter->index]);
		map[Iter->index] = nullptr;
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

