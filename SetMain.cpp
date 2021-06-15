#include "SetTest.h"
#include "Set.h"
#include "Mem.h"

#include <ctime>

int main()
{
	Mem mm(0);
	Set set(mm);

	SetTest set_test(&set);

	unsigned int start, first, second;

	start = clock();

	cout << "Test for insert() and find():" << endl;

	if (!set_test.insert_find_test(1'000'000))
		cout << "Test passed!" << endl;
	else
	{
		cout << "Something's wrong!" << endl
			 << "Aborting program!" << endl;

		exit(1);
	}

	first = clock() - start;

	cout << "Time: " << (double)first / CLOCKS_PER_SEC << " s." << endl << endl;

	cout << "Test for remove() and find():" << endl;

	if (!set_test.remove_find_test(1'000'000))
		cout << "Test passed!" << endl;
	else
	{
		cout << "Something's wrong!" << endl
		     << "Aborting program!" << endl;

		exit(1);
	}

	second = clock() - first;

	cout << "Time: " << (double)second / CLOCKS_PER_SEC << " s." << endl << endl;

	return 0;
}