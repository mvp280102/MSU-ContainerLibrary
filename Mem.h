#pragma once

#include "MemoryManager.h"

// Простейший менеджер памяти. Использует ::new и ::delete.
class Mem: public MemoryManager
{
	public:

	// Конструктор.
	Mem(size_t sz): MemoryManager(sz) {}

	// Возвращает указатель на выделенную память заданного размера.
	void* allocMem(size_t sz) override
	{
		return new char[sz];
	}

	// Освобождает участок памяти, на который указывает заданный указатель.
	void freeMem(void* ptr) override
	{
		delete[] static_cast<char*>(ptr);
	}
};
