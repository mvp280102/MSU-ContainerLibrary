#pragma once

#include "group-container.h.h"

// Абстрактный класс - Множество.
class AbstractSet: public GroupContainer
{
	public:

	// Конструктор.
	AbstractSet(MemoryManager &mem): GroupContainer(mem) {}

	// Деструктор.
	virtual ~AbstractSet() {}

	// Добавляет элемент в контейнер в соответствующую позицию, в соответствии с выбором реализации множества.
	// В случае успешного добавления возвращает значение 0, если такой элемент уже есть в контейнере - 1,
	// во всех остальных случаях - 2.
	virtual int insert(void *elem, size_t size) = 0;
};