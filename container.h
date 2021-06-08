#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "memory-manager.h"
using namespace std;

// Базовый класс для всех абстрактных контейнеров.
class Container
{
	protected:

	// Экземлпяр менеджера памяти.
	MemoryManager &_memory;


	public:

	// Базовый класс для исключений, запускаемых контейнером.
	struct Error
	{
		char msg[256];

		Error(const char *err_msg)
		{
			strcpy(msg, err_msg);
		}
	};

	// Класс итератора контейнера.
	class Iterator
	{
		public:

		// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
		// Неявно возвращает размер данных.
		virtual void* getElement(size_t &size) = 0;

		// Возвращает true, если есть следующий элемент, иначе false.
		virtual bool hasNext() = 0;

		// Переходит к следующему элементу.
		virtual void goToNext() = 0;

		// Возвращает true, если текущий итератор равен заданному, иначе false.
		virtual bool equals(Iterator *right) = 0;
	};

	// Конструктор.
	Container(MemoryManager &mem): _memory(mem) {}

	// Возвращает значение, равное количеству элементов в контейнере.
	virtual int size() = 0;

	// Возвращает значение, равное максимальной вместимости контейнера в байтах.
	virtual size_t max_bytes() = 0;

	// Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
	// Если элемент не найден, возвращает пустой указатель.
	virtual Iterator* find(void *elem, size_t size) = 0;

	// Создает итератор, соответствующий данному типу контейнера.
	virtual Iterator* newIterator() = 0;

	// Удаляет элемент из позиции, на которую указывает итератор iter.
	// После удаления итератор указывает на следующий за удаленным элемент.
	virtual void remove(Iterator *iter) = 0;

	// Удаляет все элементы из контейнера.
	virtual void clear() = 0;

	// Если контейнер пуст возвращает true, иначе false.
	virtual bool empty() = 0;
};
