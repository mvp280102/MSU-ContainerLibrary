#include "myToyList.h"
#include "Table.h"
#include <list>

int main() {
//    Mem mem = Mem(1);
//    List list = List(mem);
//    int elem = 48;
//    int* point = &elem;
//    list.push_front(static_cast<void*>(point), 4);
//    elem = 1'000'000'000;
//    list.push_front(static_cast<void*>(point), 4);
//    elem = 100;
//    list.push_front(static_cast<void*>(point), 4);
//    list.print();


    Mem mem2 = Mem(1000000000);
    Table map = Table(mem2);

    char *key1_r = nullptr;
    for (int i = 0; i < 5; ++i) {
        key1_r[i] = 69 + i;
    }
    int elem1_r = 2;
    char *key2_r = nullptr;
    for (int i = 0; i < 5; ++i) {
        key2_r[i] = 75 + i;
    }
    int elem2_r = 5;

    char** key1 = &key1_r;
    int* elem1 = &elem1_r;
    char** key2 = &key2_r;
    int* elem2 = &elem2_r;

    map.insertByKey(static_cast<void*>(key1), sizeof key1, static_cast<void*>(elem1), sizeof elem1);
    map.insertByKey(static_cast<void*>(key2), sizeof key2, static_cast<void*>(elem2), sizeof elem2);

    size_t trash = sizeof elem1;

    cout << map.at(static_cast<void*>(key1), sizeof key1, trash);

    return 0;
}
