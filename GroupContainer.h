#pragma once

#include "Container.h"
#include "List.h"

#define CONTAINER_SIZE 1'000'000

// Базовый класс для контейнеров Таблица и Множество.
class GroupContainer: public Container
{
	protected:

	// Количество элементов в контейнере.
	int elements_count = 0;

	// Хэш-функция.
	size_t hash_function(void *key, size_t keySize);

	// Возвращает значение, равное количеству элементов в контейнере.
	int size() override;

	// Возвращает значение, равное максимальной вместимости контейнера в байтах.
	size_t max_bytes() override;

	// Если контейнер пуст, возвращает true, иначе false.
	bool empty() override;

	//// Функция перехеширования.

	public:

	// Конструктор.
	explicit GroupContainer(MemoryManager &mem): Container(mem) {}
};
