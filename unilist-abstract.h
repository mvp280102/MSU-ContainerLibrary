#pragma once

#include "group-container.h.h"

// Абстрактный класс - Однонаправленный список.
class AbstractList: public GroupContainer
{
	public:

	// Конструктор.
	AbstractList(MemoryManager &mem): GroupContainer(mem) {}

	// Деструктор.
	virtual ~AbstractList() {}

	// Добавляет элемент в начало контейнера.
	// В случае успешного добавления функция возвращает значение 0, иначе 1.
	virtual int push_front(void *elem, size_t elemSize) = 0;

	// Удаляет элемент из начала контейнера.
	virtual void pop_front() = 0;

	// Возвращает явно указатель на элемент, находящийся в начале контейнера.
	// Неявно возвращает размер данных.
	virtual void* front(size_t &size) = 0;

	// Добавляет элемент в позицию, на которую указывает итератор iter.
	// В случае успешного добавления функция возвращает значение 0, иначе 1.
	virtual int insert(Iterator *iter, void *elem, size_t elemSize) = 0;
};
