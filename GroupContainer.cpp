#include "GroupContainer.h"

// Хэш-функция.
size_t GroupContainer::common_hash_function(void *key, size_t keySize)
{
	size_t hash = 0;
	char* temp = static_cast<char*>(key);

	for (int i = 0; i < keySize; ++i)
		hash = 31 * hash + temp[i];

	return hash % CONTAINER_SIZE;
}

// Возвращает значение, равное количеству элементов в контейнере.
int GroupContainer::size()
{
	return elements_count;
}

// Возвращает значение, равное максимальной вместимости контейнера в байтах.
size_t GroupContainer::max_bytes()
{
	return _memory.maxBytes();
}

// Если контейнер пуст, возвращает true, иначе false.
bool GroupContainer::empty()
{
	return !elements_count;
}