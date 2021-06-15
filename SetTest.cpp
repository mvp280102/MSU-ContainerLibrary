#include "SetTest.h"

// Функция сравнения для сортировки.
bool SetTest::comp(Cell first, Cell second)
{
	return (*((int*)(first.data))) < (*((int*)(second.data)));
}

// Тестирует insert() и find().
// Добавляет 1'000'000 элементов с помощью insert()
// и проверяет их фактическое наличие с помощью find().
// В случае успеха возвращает 0, в случае неудачи - 1.
// В случае неудачи выводит номер элемента, вызвашего ошибку.
int SetTest::insert_find_test(int count)
{
	Set::SetIterator *set_iterator;

	void *data;
	size_t size;

	for (int i = 0; i < count; i++)
	{
		set->insert(&i, sizeof(i));

		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		if (set_iterator == nullptr)
		{
			cout << "Element " << i << " not found!" << endl;
			return 1;
		}

		data = set_iterator->getElement(size);

		if ((*((int*)data) != i) && (size != sizeof(i)))
		{
			cout << "Incorrect data or size of element " << i << "!" << endl;
			return 1;
		}

		delete set_iterator;
	}

	return 0;
}

// Тестирует remove() и find().
// Удаляет все нечетные элементы с помощью remove()
// и проверяет наличие четных и отсутствие нечетных с помощью find().
// В случае успеха возвращает 0, в случае неудачи - 1.
// В случае неудачи выводит номер элемента, вызвашего ошибку.
int SetTest::remove_find_test(int count)
{
	Set::SetIterator *set_iterator;

	vector<Cell> content;
	Cell temp;

	for (int i = 1; i < count; i+=2)
	{
		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		set->remove(set_iterator);

		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		if (set_iterator != nullptr)
		{
			cout << "Uneven element " << i << " found!" << endl;
			return 1;
		}

		delete set_iterator;
	}

	for (int i = 0; i < count; i++)
	{
		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		if (set_iterator != nullptr)
		{
			temp.data = set_iterator->getElement(temp.size);
			content.push_back(temp);
		}

		delete set_iterator;
	}

	sort(content.begin(), content.end(), comp);

	for (int i = 0; i < content.size(); i++)
		if (*((int*)(content[i].data)) != 2 * i)
		{
			cout << "Incorrect data of element " << i << "!" << endl;
			return 1;
		}

	return 0;
}