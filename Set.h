#pragma once

#include "SetAbstract.h"

// Класс - Множество.
class Set : public AbstractSet
{
	private:

	List *map[CONTAINER_SIZE] = { nullptr };

	public:

	// Конструктор.
	explicit Set(MemoryManager &mem): AbstractSet(mem) {}

	// Класс итератора множества.
	class SetIterator : public Container::Iterator
	{
		public:

		Set *set;
		List::Iterator *cur;
		int index;

		SetIterator(Set *set, List::Iterator *cur, int index)
		{
			this->set = set;
			this->cur = cur;
			this->index = index;
		}

		// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
		// Неявно возвращает размер данных.
		void *getElement(size_t &size) override;

		// Возвращает true, если есть следующий элемент, иначе false.
		bool hasNext() override;

		// Переходит к следующему элементу.
		void goToNext() override;

		// Возвращает true, если текущий итератор равен заданному, иначе false.
		bool equals(Iterator *right) override;

		~SetIterator() = default;

		friend Set;
	};

	//// ФУНКЦИИ МНОЖЕСТВА:

	// Добавляет элемент в контейнер в соответствующую позицию, в соответствии с выбором реализации множества.
	// В случае успешного добавления возвращает значение 0, если такой элемент уже есть в контейнере - 1,
	// во всех остальных случаях - 2.
	int insert(void *elem, size_t size) override;

	//// ФУНКЦИИ КОНТЕЙНЕРА:

	// Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
	// Если элемент не найден, возвращает пустой указатель.
	Iterator* find(void *elem, size_t size) override;

	// Создает итератор, соответствующий данному типу контейнера.
	Iterator* newIterator() override;

	// Удаляет элемент из позиции, на которую указывает итератор iter.
	// После удаления итератор указывает на следующий за удаленным элемент.
	void remove(Iterator *iter) override;

	// Удаляет все элементы из контейнера.
	void clear() override;
};