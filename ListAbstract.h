#pragma once

#include "GroupList.h"

// Абстрактный класс - Однонаправленный список.
class AbstractList: public GroupList
{
	public:

	// Конструктор.
	AbstractList(MemoryManager &mem): GroupList(mem) {}

	// Деструктор.
	virtual ~AbstractList() {}

	// Добавляет элемент в начало списка.
	// В случае успешного добавления возвращает значение 0, иначе 1.
	virtual int push_front(void *elem, size_t elemSize) = 0;

	// Удаляет элемент из начала спискаа.
	virtual void pop_front() = 0;

	// Возвращает явно указатель на элемент, находящийся в начале спискаа.
	// Неявно возвращает размер данных.
	virtual void* front(size_t &size) = 0;

	// Добавляет элемент в позицию, на которую указывает итератор iter.
	// В случае успешного добавления возвращает значение 0, иначе 1.
	virtual int insert(Iterator *iter, void *elem, size_t elemSize) = 0;
};
