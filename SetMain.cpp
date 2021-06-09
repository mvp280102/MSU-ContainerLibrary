#include "Set.h"
#include "Mem.h"

#include <ctime>


int main()
{
	Mem mm(0);
	Set set(mm);

	unsigned int start = clock();

	for (int i = 0; i < CONTAINER_SIZE; i++)
		set.insert(&i, sizeof(i));

	unsigned int end = clock();

	cout << "Time: " << end - start << endl;

	return 0;
}
