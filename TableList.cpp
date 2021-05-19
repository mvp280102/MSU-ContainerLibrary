#include "TableList.h"

// TODO: Refactor.

List::Iterator* TableList::find(void *elem, size_t size)
{
	if (empty())
		return nullptr;

	Iterator* temp = begin();

	while (temp->current != nullptr)
	{
		if (size != temp->current->value_size) {
			temp->goToNext();
			continue;
		}
		if (compare(elem, temp->current->value))
			break;
		else temp->goToNext();
	}
	if(temp->current == nullptr)
		return nullptr;
	return temp;
}

bool TableList::compare(void *left, void *right)
{
	ArrayCell *real_left = static_cast<ArrayCell *>(left);
	ArrayCell *real_right = static_cast<ArrayCell *>(right);

	return (real_left->key_size == real_right->key_size) &&
		   !memcmp(real_left->key, real_right->key, real_left->key_size);
}