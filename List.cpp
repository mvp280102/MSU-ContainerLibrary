#include "List.h"

//// ФУНКЦИИ ИТЕРАТОРА СПИСКА:

// Возврашает явно указатель на элемент, на который указывает текущий итератор в данный момент.
// Неявно возвращает размер данных.
void* List::Iterator::getElement(size_t &size)
{
	size = current->value_size;

	return current->value;
}

// Возвращает true, если есть следующий элемент, иначе false.
bool List::Iterator::hasNext()
{
	return current->next != nullptr;
}

// Переходит к следующему элементу.
void List::Iterator::goToNext()
{
	if(hasNext())
		current = current->next;
	else
		throw Error("There is no next one.");
}

// Возвращает true, если текущий итератор равен заданному, иначе false.
bool List::Iterator::equals(Container::Iterator *right)
{
	return current == dynamic_cast<Iterator*>(right)->current;
}


//// ФУНКЦИИ СПИСКА:

// Добавляет элемент в начало списка.
// В случае успешного добавления возвращает значение 0, иначе 1.
int List::push_front(void *elem, size_t elemSize)
{
	Cell* front = static_cast<Cell*>(_memory.allocMem(sizeof(Cell)));

	front->value = static_cast<void*>(new char[elemSize]);

	if (front->value == nullptr)
	{
		delete front;
		return 1;
	}

	memcpy(front->value, elem, elemSize);

	front->value_size = elemSize;
	front->next = beginning;
	beginning = front;
	cells_count++;

	return 0;
}

// Удаляет элемент из начала списка.
void List::pop_front()
{
	if (beginning == nullptr)
		return;

	Cell* trash = beginning;
	beginning = beginning->next;

	_memory.freeMem(trash->value);
	_memory.freeMem(trash);

	cells_count--;
}

// Возвращает явно указатель на элемент, находящийся в начале списка.
// Неявно возвращает размер данных.
void* List::front(size_t &size)
{
	if (empty())
	{
		size = 0;
		return nullptr;
	}

	size = beginning->value_size;

	return beginning->value;
}

// Добавляет элемент в позицию, на которую указывает итератор iter.
// В случае успешного добавления возвращает значение 0, иначе 1.
int List::insert(AbstractList::Iterator *iter, void *elem, size_t elemSize)
{
	Iterator* iterator = dynamic_cast<Iterator*>(iter);
	Cell* new_cell = static_cast<Cell*>(_memory.allocMem(sizeof(Cell)));

	if(iterator->current == beginning)
	{
		new_cell->next = beginning;
		beginning = new_cell;
	}
	else
	{
		Iterator* trash = newIterator();
		trash->current = beginning->next;
		Cell* previous = beginning;

		while (trash->current != iterator->current && trash->current != nullptr)
		{
			if (trash->hasNext())
				trash->goToNext();
			else
			{
				_memory.freeMem(new_cell);
				return 1;
			}

			previous = previous->next;
		}

		previous->next = new_cell;
		new_cell->next = trash->current;
	}

	new_cell->value = _memory.allocMem(elemSize);

	memcpy(new_cell->value, elem, elemSize);

	new_cell->value_size = elemSize;
	cells_count++;

	return 0;
}

//// ФУНКЦИИ КОНТЕЙНЕРА:

// Возвращает значение, равное количеству элементов в списке.
int List::size()
{
	return cells_count;
}

// Возвращает значение, равное максимальной вместимости спискаа в байтах.
size_t List::max_bytes()
{
	return _memory.maxBytes();
}

// Возвращает указатель на итератор, указывающий на первый найденный в списке элемент.
// Если элемент не найден, возвращает пустой указатель.
Container::Iterator* List::find(void *elem, size_t size)
{
	if(empty())
		return nullptr;

	Iterator* temp = newIterator();
	temp->current = beginning;

	while (temp->current != nullptr)
	{
		if (size != temp->current->value_size)
		{
			temp->goToNext();
			continue;
		}

		if (memcmp(elem, temp->current->value, size) == 0)
			break;
		else
			temp->goToNext();
	}

	return nullptr;
}

// Создает итератор, соответствующий списку.
List::Iterator* List::newIterator()
{
	Iterator* iterator = new Iterator();

	iterator->current = beginning;

	return iterator;
}

// Удаляет элемент из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void List::remove(Container::Iterator *iter)
{
	Iterator* iterator = dynamic_cast<Iterator *>(iter);

	if (iterator->current == beginning)
		pop_front();
	else
	{
		Iterator *trash = newIterator();
		trash->current = beginning->next;
		Cell *previous = beginning;

		while (trash->current != iterator->current && trash->current != nullptr)
		{
			trash->goToNext();
			previous = previous->next;
		}

		previous->next = iterator->current->next;

		_memory.freeMem(trash->current->value);
		_memory.freeMem(trash->current);

		cells_count--;
	}
}

// Удаляет все элементы из списка.
void List::clear()
{
	Cell *trash = beginning;

	while (trash != nullptr)
	{
		beginning = beginning->next;

		_memory.freeMem(trash->value);
		_memory.freeMem(trash);

		trash = beginning;
	}
}

// Если список пуст, возвращает true, иначе false.
bool List::empty()
{
	return cells_count == 0;
}