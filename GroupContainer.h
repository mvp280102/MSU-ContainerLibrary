#pragma once

#include "Container.h"
#include "List.h"

#define CONTAINER_SIZE 1'000'000

// Базовый класс для контейнеров Таблица и Множество.
class GroupContainer: public Container
{
	protected:

	// Хэш-функция.
	size_t hash_function(void *key, size_t keySize);

	// Функция перехеширования.

	public:

	explicit GroupContainer(MemoryManager &mem): Container(mem) {}
};
