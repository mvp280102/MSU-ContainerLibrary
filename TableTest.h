#ifndef MSU_CONTAINERLIBRARY_2_TABLETEST_H
#define MSU_CONTAINERLIBRARY_2_TABLETEST_H

#include "Table.h"

class TableTest {
public:
    static void insertByKeyTest(Table &table, int num);
    static void findByKeyTest(Table &table, int num);
    static void removeByKeyTest(Table &table, int num);
    static void removeTest(Table &table, int num);
    static void sizeTest(Table &table, int num);
    static void iteratorTest(Table &table, int num);
    static void timeTest(Table &table, int num);

    static void universalTest(Table &table, int num);
};


#endif //MSU_CONTAINERLIBRARY_2_TABLETEST_H
