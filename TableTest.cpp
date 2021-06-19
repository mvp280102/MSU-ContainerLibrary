#include "TableTest.h"
#include <ctime>
#include <cassert>
using namespace std;

void TableTest::insertByKeyTest(Table &table, int num) {

    cout << "INSERT_BY_KEY_TEST STARTED" << endl;

    clock_t t1 = clock();

    size_t size = 0;

    for (int i = 0; i < num; i+=4) {
        table.insertByKey(&i, sizeof (int), &i, sizeof (int));
    }

    for (int i = 0; i < num; ++i) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (i % 4 == 0 && tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        } else if (i % 4 != 0 && tester != nullptr) {
            cout << "There is an element in the table that was not inserted" << endl;
            assert(tester == nullptr);
        } else if (tester != nullptr) {
            auto elem = *(int *) tester->getElement(size);
            if (elem != i) {
                cout << "The element that was inserted into the table has an invalid value" << endl;
                assert(elem == i);
            }
        }
        delete tester;
    }

    for (int i = 2; i < num; i+=4) {
        table.insertByKey(&i, sizeof (int), &i, sizeof (int));
    }

    for (int i = 0; i < num; ++i) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (i % 2 == 0 && tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        } else if (i % 2 != 0 && tester != nullptr) {
            cout << "There is an element in the table that was not inserted" << endl;
            assert(tester == nullptr);
        } else if (tester != nullptr) {
            auto elem = *(int *) tester->getElement(size);
            if (elem != i) {
                cout << "The element that was inserted into the table has an invalid value" << endl;
                assert(elem == i);
            }
        }
        delete tester;
    }

    assert(table.size() == num/2);

    char elem[] = "Hello, world!";

    for (int i = 1; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &elem, sizeof(elem));
    }

    for (int i = 0; i < num; i++) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        }
        if ((i % 2 == 0 && *(int*)tester->getElement(size) != i) ||
            (i % 2 == 1 && (memcmp(tester->getElement(size), elem, sizeof(size))) != 0)) {
            cout << "The element that was inserted into the table has an invalid value" << endl;
            exit(1);
        }
        delete tester;
    }

    assert(table.size() == num);

    table.clear();
    assert(table.empty());

    cout << "INSERT_BY_KEY_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}


void TableTest::findByKeyTest(Table &table, int num) {

    cout << "FIND_BY_KEY_TEST STARTED" << endl;

    clock_t t1 = clock();

    size_t size = 0;

    for (int i = 0; i < num; i+=3) {
        table.insertByKey(&i, sizeof (int), &i, sizeof (int));
    }

    for (int i = 0; i < num; i++) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (i % 3 != 0 && tester != nullptr) {
            cout << "There is an element in the table that was not inserted" << endl;
            assert(tester == nullptr);
        }
        else if (i % 3 == 0 && tester != nullptr && *(int*)tester->getElement(size) != i) {
            cout << "The element that was inserted into the table has an invalid value" << endl;
            assert(*(int*)tester->getElement(size) == i);
        }
        delete tester;
    }

    size = (int)(num/3) + 1;
    assert(table.size() == size);

    table.clear();
    assert(table.empty());

    cout << "FIND_BY_KEY_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}

void TableTest::removeByKeyTest(Table &table, int num) {
    cout << "REMOVE_BY_KEY_TEST STARTED" << endl;

    clock_t t1 = clock();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    assert(table.size() == num);

    for (int i = 0; i < num; i+=10) {
        table.removeByKey(&i, sizeof(int));
    }

    assert(table.size() == 9 * num / 10);

    for (int i = 0; i < num; i++) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (i % 10 == 0 && tester != nullptr) {
            cout << "Found an element that should have been removed" << endl;
            assert(tester == nullptr);
        }
        else if (i % 10 != 0 && tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        }
        delete tester;
    }

    for (int i = 0; i < num; i++) {
        table.removeByKey(&i, sizeof(int));
    }

    assert(table.size() == 0);

    for (int i = 0; i < num; i++) {
        Container::Iterator* tester = table.findByKey(&i, sizeof(int));
        if (tester != nullptr) {
            cout << "Found an element that should have been removed" << endl;
            assert(tester == nullptr);
        }
        delete tester;
    }

    table.clear();
    assert(table.empty());

    cout << "REMOVE_BY_KEY_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}

void TableTest::removeTest(Table &table, int num) {

    cout << "REMOVE_TEST STARTED" << endl;

    size_t size;

    clock_t t1 = clock();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    assert(table.size() == num);

    Container::Iterator* tester = table.newIterator();

    while (tester->getElement(size) != nullptr) {
        table.remove(tester);
    }

    assert(table.size() == 0);

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    assert(table.size() == num);

    tester = table.newIterator();

    while (true) {
        if (tester->getElement(size) == nullptr)
            break;
        int elem = *(int*)tester->getElement(size);

        if (elem % 2 == 0 && tester->hasNext())
            tester->goToNext();
        else if (elem % 2 == 1)
            table.remove(tester);
        else
            break;
    }

    for (int i = 0; i < num; i++) {
        tester = table.findByKey(&i, sizeof(int));
        if (i % 2 == 1 && tester != nullptr) {
            cout << "Found an element that should have been removed" << endl;
            assert(tester == nullptr);
        }
        else if (i % 2 == 0 && tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        }
    }

    assert(table.size() == num / 2);

    tester = table.newIterator();

    while (tester->getElement(size) != nullptr) {
        table.remove(tester);
    }

    assert(table.size() == 0);

    delete tester;

    table.clear();
    assert(table.empty());

    cout << "REMOVE_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}

void TableTest::sizeTest(Table &table, int num) {
    cout << "SIZE_TEST STARTED" << endl;

    size_t size;

    clock_t t1 = clock();

    for (int i = 0; i < num; i += 2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    assert(table.size() == num / 2);

    for (long long int i = 1; i < num; i += 2) {
        table.insertByKey(&i, sizeof(long long int), &i, sizeof(long long int));
    }

    assert(table.size() == num);

    for (int i = 0; i < num; i += 2) {
        Container::Iterator *tester = table.findByKey(&i, sizeof(int));
        if (tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        }
        if (tester->getElement(size) == nullptr || size != sizeof(int)) {
            cout << "The found element has the wrong size" << endl;
            assert(size == sizeof(int));
        }
    }

    for (long long int i = 1; i < num; i += 2) {
        Container::Iterator *tester = table.findByKey(&i, sizeof(long long int));
        if (tester == nullptr) {
            cout << "The table doesn't have an element that was inserted" << endl;
            assert(tester != nullptr);
        }
        if (tester->getElement(size) == nullptr || size != sizeof(long long int)) {
            cout << "The found element has the wrong size" << endl;
            assert(size == sizeof(long long));
        }
    }

    table.clear();
    assert(table.empty());

    cout << "SIZE_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}

void TableTest::iteratorTest(Table &table, int num) {
    cout << "ITERATOR_TEST STARTED" << endl;

    clock_t t1 = clock();

    for (int i = 0; i < num; i+= 2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    assert(table.size() == num / 2);

    Container::Iterator* tester = table.newIterator();
    Container::Iterator* last_iterator = table.newIterator();

    while (last_iterator->hasNext()) {
        last_iterator->goToNext();
    }

    while (!tester->equals(last_iterator)) {
        table.remove(tester);
    }

    assert(table.size() == 1);

    table.remove(last_iterator);

    assert(table.size() == 0);

    delete tester;
    delete last_iterator;

    table.clear();
    assert(table.empty());

    cout << "ITERATOR_TEST FINISHED" << endl;
    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1 + .0)  << " ms" << endl;
    cout << endl;
}

void TableTest::timeTest(Table &table, int num) {

    cout << "TIME_TEST STARTED" << endl;

    clock_t t1 = clock();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    clock_t t2 = clock();
    cout << "INSERT_BY_KEY_TIME: " << (t2 - t1 + .0)  << " ms" << endl;

    t1 = clock();

    for (int i = 0; i < num; i++) {
        Container::Iterator *temp = table.findByKey(&i, sizeof(int));
        delete temp;
    }

    t2 = clock();
    cout << "FIND_BY_KEY_TIME: " << (t2 - t1 + .0)  << " ms" << endl;

    t1 = clock();

    for (int i = 1; i < num; i += 2) {
        table.removeByKey(&i, sizeof(int));
    }

    t2 = clock();
    cout << "REMOVE_BY_KEY_TIME: " << (t2 - t1 + .0)  << " ms" << endl;

    t1 = clock();

    for (int i = 0; i < num; i++) {
        Container::Iterator *temp = table.findByKey(&i, sizeof(int));
        delete temp;
    }

    t2 = clock();
    cout << "FIND_BY_KEY_TIME: " << (t2 - t1 + .0)  << " ms" << endl;

    table.clear();
    assert(table.empty());

    cout << "TIME_TEST FINISHED" << endl;
    cout << endl;
}

void TableTest::universalTest(Table &table, int num){
    insertByKeyTest(table, num);
    findByKeyTest(table, num);
    removeByKeyTest(table, num);
    removeTest(table, num);
    sizeTest(table, num);
    iteratorTest(table, num);
    timeTest(table, num);
}