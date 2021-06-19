#pragma once

#include "Table.h"

class TableTest {

public:
    static void insertByKeyTest(Table &table, int num);
    static void findByKeyTest(Table &table, int num);
    static void removeByKeyTest(Table &table, int num);
    static void removeTest(Table &table, int num);
    static void clearTest(Table &table, int num);
    static void iteratorTest(Table &table, int num);
    static void sizeTest(Table &table, int num);
    static void timeTest(Table &table, int num);
};
