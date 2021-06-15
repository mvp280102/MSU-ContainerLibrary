#include "SetTest.h"

// Тестирует insert() и find().
// Добавляет 1'000'000 элементов с помощью insert()
// и проверяет их фактическое наличие с помощью find().
// В случае успеха возвращает 0, в случае неудачи - 1.
// В случае неудачи выводит номер элемента, вызвашего ошибку.
int SetTest::insert_find_test(int count)
{
	Set::SetIterator *set_iterator;

	for (int i = 0; i < count; i++)
	{
		set->insert(&i, sizeof(i));

		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		if (set_iterator == nullptr)
		{
			cout << "Element " << i << " not found!" << endl;
			return 1;
		}
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

	for (int i = 0; i < count; i++)
	{
		set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

		if (i & 1)
		{
			set->remove(set_iterator);

			set_iterator = dynamic_cast<Set::SetIterator*>(set->find(&i, sizeof(i)));

			if (set_iterator != nullptr)
			{
				cout << "Uneven element " << i << " found!" << endl;
				return 1;
			}
		}
		else
		if (set_iterator == nullptr)
		{
			cout << "Even element " << i << " not found!" << endl;
			return 1;
		}
	}

	return 0;
}