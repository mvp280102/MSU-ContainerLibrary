#pragma once

#include "group-container.h"

// Абстрактный класс - Дерево.
class AbstractTree: public GroupContainer
{
	public:

	// Конструктор.
	AbstractTree(MemoryManager &mem): GroupContainer(mem) {}

	// Деструктор.
	virtual ~AbstractTree() {}

	// Класс итератора контейнера.
	class Iterator: public Container::Iterator
	{
		public:
		// Переходит к родительской вершине. Возвращает false если текущая вершина - корень или end().
		virtual bool goToParent() = 0;

		// Переходит к дочерней вершине №child_index. Возвращает false, если дочерней вершины с таким номером нет.
		virtual bool goToChild(int child_index) = 0;
	};

	// Добавляет элемент как дочернюю вершину №child_index вершины, на которую указывает итератор.
	// В случае успешного добавления функция возвращает значение 0, иначе 1.
	virtual int insert(Iterator *iter, int child_index, void *elem, size_t size) = 0;

	// Удаляет вершину, на которую указывает итератор.
	// Если leaf_only = 1 и вершина не является листом, возвращает false.
	// Примечание! Метод remove удаляет вершину вместе со всеми ее потомками.
	virtual bool remove(Iterator *iter, int leaf_only) = 0;
};
