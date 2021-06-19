#include "myToyList.h"
#include "Table.h"
#include "mem.h"
#include "TableTest.h"

int main() {

    Mem mem(10000000);
    Table table(mem);

    int num = 1'000'000;

    TableTest::universalTest(table, num);

    return 0;

}
