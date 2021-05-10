#ifndef MSU_CONTAINERLIBRARY_TABLE_H
#define MSU_CONTAINERLIBRARY_TABLE_H
#include "TableAbstract.h"
#include "myToyList.h"
#include "container.h"

struct ArrayCell{
    void* key;
    size_t key_size;
    void* elem;
    size_t elem_size;
};

class Table : public AbstractTable {
private:
    static const size_t container_size = 1'000'000;
    List *map[1'000'000];
    size_t elements_count = 0;

public:

    Table(MemoryManager &mem): AbstractTable(mem) {}

    class TableIterator : public Container::Iterator  {
    public:
        Table *table;
        List::Iterator *current_cell;
        int index;

        TableIterator(Table *table, List::Iterator *current_cell, int index):
                table(table),
                current_cell(current_cell),
                index(index) {}

        void *getElement(size_t &size) override;

        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext() override;

        // Переходит к следующему элементу.
        void goToNext() override;

        // Возвращает true, если текущий итератор равен заданному, иначе false.
        bool equals(Iterator *right) override;

        ~TableIterator() = default;

        friend Table;
    };

    // Добавление элемента в контейнер, с сответствующим ключом.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    int insertByKey(void *key, size_t keySize, void *elem, size_t elemSize) override;

    // Удаление элемента с сответствующим ключом из контейнера.
    void removeByKey(void *key, size_t keySize) override;

    // Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
    // Если элемент не найден, возвращается нулевой указатель.
    Iterator *findByKey(void *key, size_t keySize) override;

    // доступ к элементу с ключом key
    void *at(void *key, size_t keySize, size_t &valueSize) override;

    // хэш функция
    size_t hash_function(void *key, size_t keySize) override;

    // Возвращает значение, равное количеству элементов в контейнере.
    int size() override;

    // Возвращает значение, равное максимальной вместимости контейнера в байтах.
    size_t max_bytes() override;

    // Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
    // Если элемент не найден, возвращает пустой указатель.
    Iterator *find(void *elem, size_t size) override;

    // Создает итератор, соответствующий данному типу контейнера.
    Iterator *newIterator() override;

    // Возвращает указатель на итератор, указывающий на первый элемент контейнера.
    // Если контейнер пустой, возвращает нулевой указатель.
    Iterator *begin() override;

    // Возвращает указатель на итератор, указывающий позицию за последним элементом контейнера.
    // Если контейнер пустой, возвращает нулевой указатель.
    Iterator *end() override;

    // Удаляет элемент из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    void remove(Iterator *iter) override;

    // Удаляет все элементы из контейнера.
    void clear() override;

    // Если контейнер пуст возвращает true, иначе false.
    bool empty() override;

};

#endif //MSU_CONTAINERLIBRARY_TABLE_H
