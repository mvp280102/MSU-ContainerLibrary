#pragma once

#include "List.h"

// TODO: Refactor.

struct ArrayCell
{
	void* key = nullptr;
	size_t key_size;

	void* elem = nullptr;
	size_t elem_size;
};

class TableList : public List
{
	public:

	explicit TableList(MemoryManager &mem): List(mem) {}

	Iterator* find(void *elem, size_t size) override;
};