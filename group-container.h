#pragma once
#include "container.h"

// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer: public Container
{
	public:
	GroupContainer(MemoryManager &mem): Container(mem) {}
};
