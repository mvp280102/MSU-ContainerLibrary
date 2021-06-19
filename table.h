#ifndef MSU_CONTAINERLIBRARY_TABLE_H
#define MSU_CONTAINERLIBRARY_TABLE_H
#include "TableAbstract.h"
#include "myToyListForTable.h"
#include "container.h"


class Table : public AbstractTable {
private:
    ListForTable **map;

public:

    Table(MemoryManager &mem): AbstractTable(mem)  {
            map = new (mem.allocMem(CONTAINER_SIZE * sizeof(ListForTable*))) ListForTable*[CONTAINER_SIZE];
            for (int i = 0; i < CONTAINER_SIZE; i++) {
                map[i] = nullptr;
            }
    }

    class TableIterator : public Container::Iterator  {
    public:
        ListForTable::Iterator *current_cell;
        int index;
        Table *table;

        TableIterator(ListForTable::Iterator *current_cell, int index, Table *table):
                current_cell(current_cell),
                index(index),
                table(table){}

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

    // Возвращает указатель на итератор, указывающий на первый найденный в контейнере элемент.
    // Если элемент не найден, возвращает пустой указатель.
    Iterator *find(void *elem, size_t size) override;

    // Создает итератор, соответствующий данному типу контейнера.
    Iterator *newIterator() override;

    // Удаляет элемент из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
    void remove(Iterator *iter) override;

    // Удаляет все элементы из контейнера.
    void clear() override;

};

#endif //MSU_CONTAINERLIBRARY_TABLE_H
