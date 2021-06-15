#include "List.h"
#include "Table.h"
#include "Mem.h"

/*
int main() {

	Mem mem(500000);
	Table table(mem);

	size_t size;

	/////////////////////////////////////////////////////////////////////////
//    int j = 0;
//    table.insertByKey(&j, sizeof(int), &j, sizeof(int));
//    Container::Iterator* temp = table.findByKey(&j, sizeof(int));
//    cout << *(int*)temp->getElement(size) << endl;
//
//    j = 2;
//    cout << *(int*)temp->getElement(size) << endl;
//
//    j = 4;
//    cout << *(int*)temp->getElement(size) << endl;

	for (int j = 0; j < 10'000; j+=2) {
		table.insertByKey(&j, sizeof(int), &j, sizeof(int));
	}

	for (int i = 0; i < 10'000; i++) {
		Container::Iterator* temp = table.findByKey(&i, sizeof(int));

		if (i % 2 == 0 && temp == nullptr) {
			cout << "error1\n" << i;
			exit(1);
		}
		else if (i % 2 == 1 && temp != nullptr) {
			cout << "error2\n";
			exit(1);
		}
		if (temp != nullptr && *(int*)temp->getElement(size) != i) {
			cout << *(int*)temp->getElement(size) << endl;
			cout << "error3\n";
			exit(1);
		}
		delete temp;
	}

	for (int i = 0; i < 10000; i+=4) {
		table.removeByKey(&i, sizeof(int));
	}

	for (int i = 0; i < 10000; i++) {
		Container::Iterator* temp = table.findByKey(&i, sizeof(int));
		if (temp != nullptr) {
			if (*(int*)temp->getElement(size) % 4 == 0) {
				cout << "error4\n";
				exit(1);
			}
		}
		delete temp;
	}

	for (int i = 0; i < 10000; i++) {
		cout << "start : " << i << endl;
		Container::Iterator* temp = table.find(&i, sizeof(int));
		if (temp != nullptr) {
			table.remove(temp);
			cout << table.size() << endl;
		}
		cout << i << " done" << endl;
		delete temp;
	}

	/////////////////////////////////////////////////////////////////////////

	cout << table.size() << "\n";
	cout << "test is over\n";


	return 0;

}*/