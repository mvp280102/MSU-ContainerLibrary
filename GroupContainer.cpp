#include "GroupContainer.h"

// Хэш-функция.
size_t GroupContainer::hash_function(void *key, size_t keySize)
{
	size_t hash = 0;
	char* temp = static_cast<char*>(key);

	for (int i = 0; i < keySize; ++i)
		hash = 31 * hash + temp[i];

	return hash % CONTAINER_SIZE;
}