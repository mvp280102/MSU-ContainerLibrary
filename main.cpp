#include "myToyList.h"
#include "table.h"
#include "mem.h"

int main() {

    Mem mem(10000000);
    Table table(mem);
    List list(mem);

    size_t size;

    /////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < 10000; i+=2) {
        table.insertByKey(&i, sizeof(int), &i, sizeof(int));
    }

    for (int i = 0; i < 10000; i++) {
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
            cout << "error3\n";
            exit(1);
        }
        delete temp;
    }
//
//    for (int i = 0; i < 10000; i+=4) {
//        table.removeByKey(&i, sizeof(int));
//    }
//
//    for (int i = 0; i < 10000; i++) {
//        Container::Iterator* temp = table.findByKey(&i, sizeof(int));
//        if (temp != nullptr) {
//            if (*(int*)temp->getElement(size) % 4 == 0) {
//                cout << "error4\n";
//                exit(1);
//            }
//        }
//        delete temp;
//    }
//
//    for (int i = 0; i < 10000; i++) {
//        Container::Iterator* temp = table.find(&i, sizeof(int));
//        if (temp != nullptr) {
//            table.remove(temp);
//        }
//        delete temp;
//    }

    /////////////////////////////////////////////////////////////////////////

    cout << table.size() << "\n";
    cout << "test is over\n";

    return 0;

}
