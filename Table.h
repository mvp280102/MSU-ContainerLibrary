#pragma once

#include "TableAbstract.h"
#include "TableList.h"
#include "Container.h"


class Table : public AbstractTable {
	private:
	static const size_t container_size = 500'000;
	TableList *map[container_size] = {nullptr};
	size_t elements_count = 0;

	public:

	Table(MemoryManager &mem): AbstractTable(mem)  {}

	class TableIterator : public Container::Iterator  {
		public:
		TableList::Iterator *current_cell;
		int index;
		Table *table;

		TableIterator(TableList::Iterator *current_cell, int index, Table *table):
				current_cell(current_cell),
				index(index),
				table(table){}

		void *getElement(size_t &size) override;

		// Возвращает true, если есть следующий элемент, иначе false.
		bool hasNext() override;

		// Переходит к следующему элементу.
		void goToNext() override;

		// Возвращает true, если текущий итератор равен заданному, иначе false.
		bool equals(Iterator *right) override;

		~TableIterator() = default;

		friend Table;
	};

	// Добавление элемента в контейнер, с сответствующим ключом.
	// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
	int insertByKey(void *key, size_t keySize, void *elem, size_t elemSize) override;

	// Удаление элемента с сответствующим ключом из контейнера.
	void removeByKey(void *key, size_t keySize) override;

	// Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
	// Если элемент не найден, возвращается нулевой указатель.
	Iterator *findByKey(void *key, size_t keySize) override;

	// доступ к элементу с ключом key
	void *at(void *key, size_t keySize, size_t &valueSize) override;

	// Возвращает значение, равное количеству элементов в контейнере.
	int size() override;

	// Возвращает значение, равное максимальной вместимости контейнера в байтах.
	size_t max_bytes() override;

	// Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
	// Если элемент не найден, возвращает пустой указатель.
	Iterator *find(void *elem, size_t size) override;

	// Создает итератор, соответствующий данному типу контейнера.
	Iterator *newIterator() override;

	// Удаляет элемент из позиции, на которую указывает итератор iter.
	// После удаления итератор указывает на следующий за удаленным элемент.
	void remove(Iterator *iter) override;

	// Удаляет все элементы из контейнера.
	void clear() override;

	// Если контейнер пуст возвращает true, иначе false.
	bool empty() override;

};