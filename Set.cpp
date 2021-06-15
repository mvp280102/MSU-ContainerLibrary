#include "Set.h"

//// ФУНКЦИИ ИТЕРАТОРА МНОЖЕСТВА:

// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
// Неявно возвращает размер данных.
void* Set::SetIterator::getElement(size_t &size)
{
	return cur->getElement(size);
}

// Возвращает true, если есть следующий элемент, иначе false.
bool Set::SetIterator::hasNext()
{
	if (cur->hasNext())
		return true;
	else
		for (int i = index + 1; i < CONTAINER_SIZE; ++i)
			if (!(set->map[i]->empty()))
				return true;

	return false;
}

// Переходит к следующему элементу.
void Set::SetIterator::goToNext()
{
	bool success = false;

	if (cur->hasNext())
		cur->goToNext();
	else
	{
		for (int i = index + 1; i < CONTAINER_SIZE; ++i)
			if (set->map[i] != nullptr)
			{
				cur = set->map[i]->newIterator();
				success = true;
				break;
			}

		if (!success)
			cout << "Next element doesn't exist." << endl;
	}
}

// Возвращает true, если текущий итератор равен заданному, иначе false.
bool Set::SetIterator::equals(Iterator *right)
{
	return (cur == dynamic_cast<List::Iterator*>(right));
}


//// ФУНКЦИИ МНОЖЕСТВА:

// Добавляет элемент в контейнер в соответствующую позицию, в соответствии с выбором реализации множества.
// В случае успешного добавления возвращает значение 0, если такой элемент уже есть в контейнере - 1,
// во всех остальных случаях - 2.
int Set::insert(void *elem, size_t size)
{
	size_t index = hash_function(elem, size);

	if (map[index] == nullptr)
		map[index] = new List(_memory);
	else if (map[index]->find(elem, size) != nullptr)
		return 1;

	if (!map[index]->push_front(elem, size))
	{
		//cout << "Added successfully!" << endl;

		elements_count++;
		return 0;
	}

	return 2;
}


//// ФУНКЦИИ КОНТЕЙНЕРА:

// Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
// Если элемент не найден, возвращает пустой указатель.
Set::Iterator* Set::find(void *elem, size_t size)
{
	SetIterator *set_iter = nullptr;
	size_t index = hash_function(elem, size);

	if (map[index] == nullptr)
		return nullptr;

	auto *list_iter = dynamic_cast<List::ListIterator *>(map[index]->find(elem, size));

	if (list_iter != nullptr)
		set_iter = new SetIterator(this, list_iter, index);

	return set_iter;
}

// Создает итератор, соответствующий данному типу контейнера.
Set::Iterator* Set::newIterator()
{
	for (int i = 0; i < CONTAINER_SIZE; ++i)
		if (map[i] != nullptr)
			return new SetIterator(this, dynamic_cast<List::ListIterator*>(map[i]->newIterator()), i);

	return nullptr;
}

// Удаляет элемент из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void Set::remove(Iterator *iter)
{
	auto *req_iterator = dynamic_cast<SetIterator*>(iter);

	map[req_iterator->index]->remove(req_iterator->cur);

	if (map[req_iterator->index]->empty())
	{
		map[req_iterator->index] = nullptr;
		req_iterator->goToNext();
	}
}

// Удаляет все элементы из контейнера.
void Set::clear()
{
	for (auto & i : map)
	{
		_memory.freeMem(i);
		i = nullptr;
	}

	elements_count = 0;
}