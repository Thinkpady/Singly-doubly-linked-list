#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

// Узел двусвязного списка
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура списка
typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
    Node* current; // рабочий указатель
} DoublyLinkedList;

// Прототипы функций
void startWork(DoublyLinkedList* list);
void makeEmpty(DoublyLinkedList* list);
bool isEmpty(DoublyLinkedList* list);
void moveCurrentToHead(DoublyLinkedList* list);
void moveCurrentToTail(DoublyLinkedList* list);
bool isCurrentAtHead(DoublyLinkedList* list);
bool isCurrentAtTail(DoublyLinkedList* list);
void moveCurrentForward(DoublyLinkedList* list);
void moveCurrentBackward(DoublyLinkedList* list);
void showBeforeCurrent(DoublyLinkedList* list);
void showAfterCurrent(DoublyLinkedList* list);
void deleteBeforeCurrent(DoublyLinkedList* list);
void deleteAfterCurrent(DoublyLinkedList* list);
void extractBeforeCurrent(DoublyLinkedList* list);
void extractAfterCurrent(DoublyLinkedList* list);
void changeBeforeCurrent(DoublyLinkedList* list);
void changeAfterCurrent(DoublyLinkedList* list);
void addBeforeCurrent(DoublyLinkedList* list);
void addAfterCurrent(DoublyLinkedList* list);
void endWork(DoublyLinkedList* list);
void printListState(DoublyLinkedList* list);
void showMenu();
void clearList(DoublyLinkedList* list);

// 1. Начать работу
void startWork(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    printf("Работа со списком начата.\n");
}

// 2. Сделать пустым
void makeEmpty(DoublyLinkedList* list) {
    clearList(list);
    printf("Список очищен.\n");
}

// 3. Проверить пуст
bool isEmpty(DoublyLinkedList* list) {
    return list->head == NULL;
}

// 4. Установить указатель в начало
void moveCurrentToHead(DoublyLinkedList* list) {
    if (isEmpty(list)) {
        printf("Список пуст.\n");
        return;
    }
    list->current = list->head;
    printf("Указатель установлен в начало.\n");
}

// 5. Установить указатель в конец
void moveCurrentToTail(DoublyLinkedList* list) {
    if (isEmpty(list)) {
        printf("Список пуст.\n");
        return;
    }
    list->current = list->tail;
    printf("Указатель установлен в конец.\n");
}

// 6. Проверить указатель в начале
bool isCurrentAtHead(DoublyLinkedList* list) {
    return list->current == list->head;
}

// 7. Проверить указатель в конце
bool isCurrentAtTail(DoublyLinkedList* list) {
    return list->current == list->tail;
}

// 8. Передвинуть указатель вперед
void moveCurrentForward(DoublyLinkedList* list) {
    if (list->current && list->current->next) {
        list->current = list->current->next;
        printf("Указатель передвинут вперед.\n");
    }
    else {
        printf("Невозможно передвинуть вперед.\n");
    }
}

// 9. Передвинуть указатель назад
void moveCurrentBackward(DoublyLinkedList* list) {
    if (list->current && list->current->prev) {
        list->current = list->current->prev;
        printf("Указатель передвинут назад.\n");
    }
    else {
        printf("Невозможно передвинуть назад.\n");
    }
}

// 10. Показать значение ДО указателя
void showBeforeCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->prev) {
        printf("Значение до указателя: %d\n", list->current->prev->data);
    }
    else {
        printf("Нет элемента до указателя.\n");
    }
}

// 11. Показать значение ПОСЛЕ указателя
void showAfterCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->next) {
        printf("Значение после указателя: %d\n", list->current->next->data);
    }
    else {
        printf("Нет элемента после указателя.\n");
    }
}

// 12. Удалить элемент ДО указателя
void deleteBeforeCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->prev) {
        Node* toDelete = list->current->prev;
        if (toDelete->prev) toDelete->prev->next = list->current;
        else list->head = list->current;
        list->current->prev = toDelete->prev;
        free(toDelete);
        printf("Элемент до указателя удалён.\n");
    }
    else {
        printf("Нет элемента до указателя.\n");
    }
}

// 13. Удалить элемент ПОСЛЕ указателя
void deleteAfterCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->next) {
        Node* toDelete = list->current->next;
        if (toDelete->next) toDelete->next->prev = list->current;
        else list->tail = list->current;
        list->current->next = toDelete->next;
        free(toDelete);
        printf("Элемент после указателя удалён.\n");
    }
    else {
        printf("Нет элемента после указателя.\n");
    }
}

// 14. Взять элемент ДО указателя
void extractBeforeCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->prev) {
        Node* toExtract = list->current->prev;
        int value = toExtract->data;
        if (toExtract->prev) toExtract->prev->next = list->current;
        else list->head = list->current;
        list->current->prev = toExtract->prev;
        free(toExtract);
        printf("Извлечено значение ДО указателя: %d\n", value);
    }
    else {
        printf("Нет элемента до указателя.\n");
    }
}

// 15. Взять элемент ПОСЛЕ указателя
void extractAfterCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->next) {
        Node* toExtract = list->current->next;
        int value = toExtract->data;
        if (toExtract->next) toExtract->next->prev = list->current;
        else list->tail = list->current;
        list->current->next = toExtract->next;
        free(toExtract);
        printf("Извлечено значение ПОСЛЕ указателя: %d\n", value);
    }
    else {
        printf("Нет элемента после указателя.\n");
    }
}

// 16. Изменить значение ДО указателя
void changeBeforeCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->prev) {
        int newValue;
        printf("Введите новое значение: ");
        scanf("%d", &newValue);
        list->current->prev->data = newValue;
        printf("Значение изменено.\n");
    }
    else {
        printf("Нет элемента до указателя.\n");
    }
}

// 17. Изменить значение ПОСЛЕ указателя
void changeAfterCurrent(DoublyLinkedList* list) {
    if (list->current && list->current->next) {
        int newValue;
        printf("Введите новое значение: ");
        scanf("%d", &newValue);
        list->current->next->data = newValue;
        printf("Значение изменено.\n");
    }
    else {
        printf("Нет элемента после указателя.\n");
    }
}

// 18. Добавить элемент ДО указателя
void addBeforeCurrent(DoublyLinkedList* list) {
    int newValue;
    printf("Введите значение: ");
    scanf("%d", &newValue);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newValue;

    if (isEmpty(list)) {
        list->head = list->tail = list->current = newNode;
        newNode->next = newNode->prev = NULL;
        printf("Элемент добавлен в пустой список.\n");
        return;
    }

    if (!list->current) {
        printf("Указатель не установлен.\n");
        free(newNode);
        return;
    }

    newNode->next = list->current;
    newNode->prev = list->current->prev;
    if (list->current->prev) list->current->prev->next = newNode;
    else list->head = newNode;
    list->current->prev = newNode;
    printf("Элемент добавлен ДО указателя.\n");
}

// 19. Добавить элемент ПОСЛЕ указателя
void addAfterCurrent(DoublyLinkedList* list) {
    int newValue;
    printf("Введите значение: ");
    scanf("%d", &newValue);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newValue;

    if (isEmpty(list)) {
        list->head = list->tail = list->current = newNode;
        newNode->next = newNode->prev = NULL;
        printf("Элемент добавлен в пустой список.\n");
        return;
    }

    if (!list->current) {
        printf("Указатель не установлен.\n");
        free(newNode);
        return;
    }

    newNode->prev = list->current;
    newNode->next = list->current->next;
    if (list->current->next) list->current->next->prev = newNode;
    else list->tail = newNode;
    list->current->next = newNode;
    printf("Элемент добавлен ПОСЛЕ указателя.\n");
}

// 20. Закончить работу со списком
void endWork(DoublyLinkedList* list) {
    clearList(list);
    list->head = list->tail = list->current = NULL;
    printf("Работа со списком завершена.\n");
}

// Очистка списка
void clearList(DoublyLinkedList* list) {
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = list->tail = list->current = NULL;
}

// Печать состояния списка
void printListState(DoublyLinkedList* list) {
    printf("\n--- Состояние списка ---\n");
    if (isEmpty(list)) {
        printf("Список пуст.\n");
    }
    else {
        Node* temp = list->head;
        while (temp) {
            if (temp == list->current) {
                printf("[%d]<- ", temp->data);
            }
            else {
                printf("%d ", temp->data);
            }
            temp = temp->next;
        }
        printf("\n");
    }
    printf("------------------------\n");
}

// Меню
void showMenu() {
    printf("\n========== МЕНЮ ==========\n");
    printf("1. Начать работу\n");
    printf("2. Сделать список пустым\n");
    printf("3. Проверить, пуст ли список\n");
    printf("4. Установить указатель в начало\n");
    printf("5. Установить указатель в конец\n");
    printf("6. Проверить указатель в начале\n");
    printf("7. Проверить указатель в конце\n");
    printf("8. Передвинуть указатель вперед\n");
    printf("9. Передвинуть указатель назад\n");
    printf("10. Показать значение ДО указателя\n");
    printf("11. Показать значение ПОСЛЕ указателя\n");
    printf("12. Удалить элемент ДО указателя\n");
    printf("13. Удалить элемент ПОСЛЕ указателя\n");
    printf("14. Взять элемент ДО указателя\n");
    printf("15. Взять элемент ПОСЛЕ указателя\n");
    printf("16. Изменить значение ДО указателя\n");
    printf("17. Изменить значение ПОСЛЕ указателя\n");
    printf("18. Добавить элемент ДО указателя\n");
    printf("19. Добавить элемент ПОСЛЕ указателя\n");
    printf("20. Закончить работу со списком\n");
    printf("21. Закончить работу программы\n");
    printf("==========================\n");
    printf("Ваш выбор: ");
}

// Главная функция
int main() {
    setlocale(LC_ALL, "RU");

    DoublyLinkedList list;
    list.head = list.tail = list.current = NULL;

    int choice;
    bool working = false;
    bool programRunning = true;

    printf("Программа для работы с двусвязным списком\n");
    printf("===========================================\n");

    while (programRunning) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: // Начать работу
            if (!working) {
                startWork(&list);
                working = true;
            }
            else {
                printf("Работа уже начата.\n");
            }
            break;

        case 2: makeEmpty(&list); break;
        case 3: printf(isEmpty(&list) ? "Список пуст.\n" : "Список НЕ пуст.\n"); break;
        case 4: moveCurrentToHead(&list); break;
        case 5: moveCurrentToTail(&list); break;
        case 6: printf(isCurrentAtHead(&list) ? "Указатель в начале.\n" : "Указатель НЕ в начале.\n"); break;
        case 7: printf(isCurrentAtTail(&list) ? "Указатель в конце.\n" : "Указатель НЕ в конце.\n"); break;
        case 8: moveCurrentForward(&list); break;
        case 9: moveCurrentBackward(&list); break;
        case 10: showBeforeCurrent(&list); break;
        case 11: showAfterCurrent(&list); break;
        case 12: deleteBeforeCurrent(&list); break;
        case 13: deleteAfterCurrent(&list); break;
        case 14: extractBeforeCurrent(&list); break;
        case 15: extractAfterCurrent(&list); break;
        case 16: changeBeforeCurrent(&list); break;
        case 17: changeAfterCurrent(&list); break;
        case 18: addBeforeCurrent(&list); break;
        case 19: addAfterCurrent(&list); break;
        case 20: endWork(&list); working = false; break;
        case 21: endWork(&list); programRunning = false; printf("Программа завершена.\n"); break;
        default: printf("Неверный выбор.\n"); break;
        }

        if (programRunning && working) {
            printListState(&list);
        }
    }

    return 0;
}

