#include <iostream>
#include <chrono>
using namespace std::chrono;

#include "TableTestN.h"

size_t size = 0;

void TableTest::insertByKeyTest(Table &table, int num) {

    cout << "-INSERT-BY-KEY-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (i % 2 == 0 && temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
        else if (i % 2 != 0 && temp != nullptr) {
            cout << "The element has not been inserted but has been found\n";
            exit(1);
        }
        if (temp != nullptr && *(int*)temp->getElement(size) != i) {
            cout << "The element that has been found does not equal the element that has been inserted\n";
            exit(1);
        }
        delete temp;
    }

    cout << "Size: " << table.size() << endl;

    char elem[] = "checkData";

    for (int i = 1; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &elem, sizeof(elem));
    }

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
        if ((i % 2 == 0 && *(int*)temp->getElement(size) != i) ||
        (i % 2 == 1 && (memcmp(temp->getElement(size), elem, sizeof(size))) != 0)) {
            cout << "The element that has been found does not equal the element that has been inserted\n";
            exit(1);
        }
        delete temp;
    }

    cout << "Size: " << table.size() << endl;

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "insertByKeyTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::findByKeyTest(Table &table, int num) {

    cout << "-FIND-BY-KEY-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    for (int i = 1; i < num; i+=2) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp != nullptr) {
            cout << "The element has not been inserted but has been found\n";
            exit(1);
        }
        delete temp;
    }

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "findByKeyTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::removeByKeyTest(Table &table, int num) {

    cout << "-REMOVE-BY-KEY-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    for (int i = 0; i < num; i+=2) {
        table.removeByKey(&i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (i % 2 == 0 && temp != nullptr) {
            cout << "The element has been removed but has been found\n";
            exit(1);
        }
        else if (i % 2 != 0 && temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
        delete temp;
    }

    for (int i = 0; i < num; i++) {
        table.removeByKey(&i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp != nullptr) {
            cout << "The element has been removed but has been found\n";
            exit(1);
        }
        delete temp;
    }

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "removeByKeyTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::removeTest(Table &table, int num) {

    cout << "-REMOVE-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    Container::Iterator* temp = table.newIterator();

    while (temp->getElement(size) != nullptr) {
        table.remove(temp);
    }

    cout << "Size: " << table.size() << endl;

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    temp = table.newIterator();

    while (true) {
        if (temp->getElement(size) == nullptr)
            break;
        int elem = *(int*)temp->getElement(size);

        if (elem % 2 == 0 && temp->hasNext())
            temp->goToNext();
        else if (elem % 2 == 1)
            table.remove(temp);
        else
            break;
    }

    for (int i = 0; i < num; i++) {
        temp = table.findByKey(&i, sizeof(int));
        if (i % 2 == 1 && temp != nullptr) {
            cout << "The element has been removed but has been found\n";
            exit(1);
        }
        else if (i % 2 == 0 && temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
    }

    cout << "Size: " << table.size() << endl;

    temp = table.newIterator();

    while (temp->getElement(size) != nullptr) {
        table.remove(temp);
    }

    cout << "Size: " << table.size() << endl;

    delete temp;

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "removeTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::clearTest(Table &table, int num) {

    cout << "-CLEAR-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    table.clear();

    cout << "Size: " << table.size() << endl;

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp != nullptr) {
            cout << "The element has been removed but has been found\n";
            exit(1);
        }
        delete temp;
    }

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "removeByKeyTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::iteratorTest(Table &table, int num) {

    cout << "-ITERATOR-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    Container::Iterator* temp = table.newIterator();
    Container::Iterator* tempEnd = table.newIterator();

    while (tempEnd->hasNext()) {
        tempEnd->goToNext();
    }

    while (!temp->equals(tempEnd)) {
        table.remove(temp);
    }

    if (table.size() != 1) {
        cout << "The table has to contain 1 element but multiple or none have been found\n";
        exit(1);
    }

    cout << "Size: " << table.size() << endl;

    table.remove(tempEnd);

    cout << "Size: " << table.size() << endl;

    delete temp;
    delete tempEnd;

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "iteratorTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::sizeTest(Table &table, int num) {

    cout << "-SIZE-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i+=2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    cout << "Size: " << table.size() << endl;

    for (long long int i = 1; i < num; i+=2) {
        table.insertByKey(&i, sizeof(long long int), &i, sizeof(long long int));
    }

    for (int i = 0; i < num; i+=2) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp == nullptr) {
            cout << "Error11\n";
            exit(1);
        }
        if (temp->getElement(size) == nullptr || size != sizeof(int)) {
            cout << "Error12\n";
            exit(1);
        }
    }

    for (long long int i = 1; i < num; i+=2) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(long long int));
        if (temp == nullptr) {
            cout << "Error21\n";
            exit(1);
        }
        if (temp->getElement(size) == nullptr || size != sizeof(long long int)) {
            cout << "Error22\n";
            exit(1);
        }
    }

    if (table.size() != num) {
        cout << "The size of the table is not correct\n";
        exit(1);
    }

    cout << "Size: " << table.size() << endl;

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "sizeTest Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}

void TableTest::timeTest(Table &table, int num) {

    cout << "-TIME-TEST-" << endl;

    auto now = system_clock::now();

    for (int i = 0; i < num; i++) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    auto elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "insertByKey Time : " << elapsed.count() << "ms.\n";

    now = system_clock::now();

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
        delete temp;
    }

    elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "findByKey Time : " << elapsed.count() << "ms.\n";

    now = system_clock::now();

    for (int i = 1; i < num; i+=2) {
        table.removeByKey(&i, sizeof(int));
    }

    elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "removeByKey Time : " << elapsed.count() << "ms.\n";

    now = system_clock::now();

    for (int i = 0; i < num; i++) {
        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
        if (i % 2 == 0 && temp == nullptr) {
            cout << "The element has been inserted but has not been found\n";
            exit(1);
        }
        else if (i % 2 != 0 && temp != nullptr) {
            cout << "The element has been removed but has been found\n";
            exit(1);
        }
        delete temp;
    }

    elapsed = duration_cast<milliseconds>(system_clock::now() - now);
    cout << "findByKey Time : " << elapsed.count() << "ms.\n";

    table.clear();
    cout << "Table has been cleaned. Size: " << table.size() << endl << endl;
}
