#include "TableList.h"

// TODO: Refactor.

List::Iterator* TableList::find(void *elem, size_t size)
{
	ListIterator* iter = dynamic_cast<ListIterator *>(newIterator());
	size_t trash;

	do
	{
		ArrayCell temp = *(ArrayCell*)(iter->getElement(trash));

		if (temp.key_size == size)
			if (memcmp(temp.key, elem, size) == 0)
				break;

		iter->goToNext();
	}
	while (iter->current != nullptr);

	if (iter->current == nullptr)
		return nullptr;

	return iter;
}