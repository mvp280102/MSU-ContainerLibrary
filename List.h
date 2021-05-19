#pragma once

#include "ListAbstract.h"
#include "Mem.h"

// Класс - Однонаправленный список.
class List : public AbstractList
{
	private:

	// Структура узла списка.
	struct Cell
	{
		void* value;
		size_t value_size;
		Cell* next;
	};

	// Указатель на головной узел.
	Cell* beginning = nullptr;

	// Количество узлов.
	int cells_count = 0;


	public:

	// Конструктор.
	List(MemoryManager &mem) : AbstractList(mem), cells_count(0) {}

	// Класс итератора списка.
	class Iterator : public AbstractList::Iterator
	{
		private:

		// Указатель на вершину.
		Cell* current = nullptr;


		public:

		// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
		// Неявно возвращает размер данных.
		void* getElement(size_t &size) override;

		// Возвращает true, если есть следующий элемент, иначе false.
		bool hasNext() override;

		// Переходит к следующему элементу.
		void goToNext() override;

		// Возвращает true, если текущий итератор равен заданному, иначе false.
		bool equals(Container::Iterator *right) override;

		// Деструктор.
		~Iterator() = default;

		// Дружественный класс List.
		friend List;

		// Дружественный класс TableList.
		friend class TableList;
	};

	// Выводит на экран все элементы списка.
	void print()
	{
		Iterator* it = newIterator();

		for (int i = 0; i < size(); ++i)
		{
			cout << "Element " << i << ":" << endl;

			char* string = static_cast<char*>(it->current->value);

			for (int j = 0; j < it->current->value_size; ++j)
				cout << string[j];

			cout << endl;

			it->goToNext();
		}
	}

	//// ФУНКЦИИ СПИСКА:

	// Добавляет элемент в начало списка.
	// В случае успешного добавления возвращает значение 0, иначе 1.
    int push_front(void *elem, size_t elemSize) override;

	// Удаляет элемент из начала списка.
	void pop_front() override;

	// Возвращает явно указатель на элемент, находящийся в начале списка.
	// Неявно возвращает размер данных.
	void* front(size_t &size) override;

	// Добавляет элемент в позицию, на которую указывает итератор iter.
	// В случае успешного добавления возвращает значение 0, иначе 1.
	int insert(AbstractList::Iterator *iter, void *elem, size_t elemSize) override;

	//// ФУНКЦИИ КОНТЕЙНЕРА:

	// Возвращает значение, равное количеству элементов в списке.
	int size() override;

	// Возвращает значение, равное максимальной вместимости спискаа в байтах.
	size_t max_bytes() override;

	// Возвращает указатель на итератор, указывающий на первый найденный в списке элемент.
	// Если элемент не найден, возвращает пустой указатель.
	Container::Iterator * find(void *elem, size_t size) override;

	// Создает итератор, соответствующий списку.
	Iterator* newIterator() override;

	// Возвращает указатель на итератор, указывающий на первый элемент контейнера.
	// Если контейнер пустой, возвращает нулевой указатель.
	Iterator* begin() override;

	// Удаляет элемент из позиции, на которую указывает итератор iter.
	// После удаления итератор указывает на следующий за удаленным элемент.
	void remove(Container::Iterator *iter) override;

	// Удаляет все элементы из списка.
	void clear() override;

	// Если список пуст, возвращает true, иначе false.
	bool empty() override;

	// Дружественный класс TableList.
	friend class TableList;
};