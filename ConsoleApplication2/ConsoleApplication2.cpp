#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

// Структура элемента списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура списка с головой и рабочим указателем
typedef struct LinkedList {
    Node* head;
    Node* current; // рабочий указатель
} LinkedList;

// Прототипы функций
void startWork(LinkedList* list);
void makeEmpty(LinkedList* list);
bool isEmpty(LinkedList* list);
void moveCurrentToHead(LinkedList* list);
bool isCurrentAtEnd(LinkedList* list);
void moveCurrentForward(LinkedList* list);
void showCurrentValue(LinkedList* list);
void deleteAfterCurrent(LinkedList* list);
void extractAfterCurrent(LinkedList* list);
void changeAfterCurrent(LinkedList* list);
void addAfterCurrent(LinkedList* list);
void endWork(LinkedList* list);
void printListState(LinkedList* list);
void clearList(LinkedList* list);
void showMenu();
void waitForEnter();

// 1. Начать работу (инициализация)
void startWork(LinkedList* list) {
    list->head = NULL;
    list->current = NULL;
    printf("Работа со списком начата.\n");
}

// 2. Сделать пустым
void makeEmpty(LinkedList* list) {
    clearList(list);
    list->head = NULL;
    list->current = NULL;
    printf("Список очищен.\n");
}

// 3. Проверить пуст или нет
bool isEmpty(LinkedList* list) {
    return list->head == NULL;
}

// 4. Установить рабочий указатель в начало списка
void moveCurrentToHead(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    list->current = list->head;
    printf("Рабочий указатель перемещён в начало списка.\n");
}

// 5. Рабочий указатель находится в конце списка?
bool isCurrentAtEnd(LinkedList* list) {
    if (isEmpty(list) || list->current == NULL) return false;
    return list->current->next == NULL;
}

// 6. Передвинуть рабочий указатель вперед
void moveCurrentForward(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    if (list->current == NULL) {
        printf("Рабочий указатель не установлен. Сначала переместите его в начало.\n");
        return;
    }
    if (isCurrentAtEnd(list)) {
        printf("Невозможно: рабочий указатель уже в конце списка.\n");
        return;
    }
    list->current = list->current->next;
    printf("Рабочий указатель передвинут вперёд.\n");
}

// 7. Показать значение элемента списка за указателем
void showCurrentValue(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    if (list->current == NULL) {
        printf("Рабочий указатель не установлен. Сначала переместите его в начало.\n");
        return;
    }
    printf("Значение текущего элемента: %d\n", list->current->data);
}

// 8. Удалить элемент списка за указателем
void deleteAfterCurrent(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    if (list->current == NULL) {
        printf("Рабочий указатель не установлен.\n");
        return;
    }
    if (list->current->next == NULL) {
        printf("Невозможно: за указателем нет элемента.\n");
        return;
    }

    Node* toDelete = list->current->next;
    list->current->next = toDelete->next;
    free(toDelete);
    printf("Элемент за указателем удалён.\n");
}

// 9. Взять элемент списка за указателем (извлечь и вернуть значение)
void extractAfterCurrent(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    if (list->current == NULL) {
        printf("Рабочий указатель не установлен.\n");
        return;
    }
    if (list->current->next == NULL) {
        printf("Невозможно: за указателем нет элемента.\n");
        return;
    }

    Node* toExtract = list->current->next;
    int value = toExtract->data;
    list->current->next = toExtract->next;
    free(toExtract);
    printf("Элемент за указателем извлечён. Значение: %d\n", value);
}

// 10. Изменить значение элемента списка за указателем
void changeAfterCurrent(LinkedList* list) {
    if (isEmpty(list)) {
        printf("Невозможно: список пуст.\n");
        return;
    }
    if (list->current == NULL) {
        printf("Рабочий указатель не установлен.\n");
        return;
    }
    if (list->current->next == NULL) {
        printf("Невозможно: за указателем нет элемента.\n");
        return;
    }

    int newValue;
    printf("Введите новое значение: ");
    scanf("%d", &newValue);
    list->current->next->data = newValue;
    printf("Значение элемента за указателем изменено.\n");
}

// 11. Добавить элемент за указателем
void addAfterCurrent(LinkedList* list) {
    int newValue;
    printf("Введите значение для добавления: ");
    scanf("%d", &newValue);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    newNode->data = newValue;

    if (isEmpty(list)) {
        // Список пуст — новый элемент становится головой
        newNode->next = NULL;
        list->head = newNode;
        list->current = newNode; // рабочий указатель на новый элемент
        printf("Элемент добавлен в пустой список и стал текущим.\n");
        return;
    }

    if (list->current == NULL) {
        // Рабочий указатель не установлен — добавляем в начало
        newNode->next = list->head;
        list->head = newNode;
        list->current = newNode;
        printf("Элемент добавлен в начало (рабочий указатель был сброшен).\n");
        return;
    }

    // Обычное добавление после текущего
    newNode->next = list->current->next;
    list->current->next = newNode;
    printf("Элемент добавлен за указателем.\n");
}

// 12. Закончить работу со списком (очистить, но не завершать программу)
void endWork(LinkedList* list) {
    clearList(list);
    list->head = NULL;
    list->current = NULL;
    printf("Работа со списком завершена. Память освобождена.\n");
}

// Вспомогательная: очистка всего списка
void clearList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->current = NULL;
}

// Печать текущего состояния списка с указателем
void printListState(LinkedList* list) {
    printf("\n--- Состояние списка ---\n");
    if (isEmpty(list)) {
        printf("Список пуст.\n");
        printf("Указатель: NULL\n");
    }
    else {
        printf("Элементы списка: ");
        Node* temp = list->head;
        int position = 0;
        while (temp != NULL) {
            if (temp == list->current) {
                printf("[%d]<-", temp->data);
            }
            else {
                printf("%d ", temp->data);
            }
            temp = temp->next;
            position++;
        }
        printf("\n");
        if (list->current == NULL) {
            printf("Рабочий указатель не установлен (NULL)\n");
        }
        else {
            printf("Рабочий указатель указывает на элемент со значением %d\n", list->current->data);
        }
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
    printf("5. Указатель в конце?\n");
    printf("6. Передвинуть указатель вперед\n");
    printf("7. Показать значение за указателем\n");
    printf("8. Удалить элемент за указателем\n");
    printf("9. Взять элемент за указателем (извлечь)\n");
    printf("10. Изменить элемент за указателем\n");
    printf("11. Добавить элемент за указателем\n");
    printf("12. Закончить работу со списком\n");
    printf("13. Закончить работу программы\n");
    printf("==========================\n");
    printf("Ваш выбор: ");
}

// Функция для ожидания нажатия Enter (чтобы консоль не закрывалась)
void waitForEnter() {
    printf("\nНажмите Enter для продолжения...");
    while (getchar() != '\n');
    getchar();
}

int main() {
    setlocale(LC_ALL, "RU");

    LinkedList list;
    list.head = NULL;
    list.current = NULL;

    int choice;
    bool working = false;
    bool programRunning = true;

    printf("Программа для работы с односвязным списком\n");
    printf("===========================================\n");

    while (programRunning) {
        showMenu();
        scanf("%d", &choice);
        getchar(); // очистка буфера после scanf

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

        case 2: // Сделать пустым
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                makeEmpty(&list);
            }
            break;

        case 3: // Проверить пуст или нет
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                if (isEmpty(&list)) {
                    printf("Список ПУСТ.\n");
                }
                else {
                    printf("Список НЕ пуст.\n");
                }
            }
            break;

        case 4: // Установить указатель в начало
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                moveCurrentToHead(&list);
            }
            break;

        case 5: // Указатель в конце?
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                if (isEmpty(&list)) {
                    printf("Список пуст.\n");
                }
                else if (isCurrentAtEnd(&list)) {
                    printf("Рабочий указатель в КОНЦЕ списка.\n");
                }
                else {
                    printf("Рабочий указатель НЕ в конце списка.\n");
                }
            }
            break;

        case 6: // Передвинуть вперед
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                moveCurrentForward(&list);
            }
            break;

        case 7: // Показать значение за указателем
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                showCurrentValue(&list);
            }
            break;

        case 8: // Удалить за указателем
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                deleteAfterCurrent(&list);
            }
            break;

        case 9: // Взять элемент за указателем
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                extractAfterCurrent(&list);
            }
            break;

        case 10: // Изменить за указателем
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                changeAfterCurrent(&list);
            }
            break;

        case 11: // Добавить за указателем
            if (!working) {
                printf("Сначала начните работу (пункт 1).\n");
            }
            else {
                addAfterCurrent(&list);
            }
            break;

        case 12: // Закончить работу со списком
            if (!working) {
                printf("Работа со списком ещё не начиналась.\n");
            }
            else {
                endWork(&list);
                working = false;
            }
            break;

        case 13: // Закончить работу программы
            if (working) {
                endWork(&list); // Очищаем перед выходом
            }
            printf("Программа завершена.\n");
            programRunning = false;
            break;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }

        if (programRunning && working) {
            printListState(&list);
        }
        else if (programRunning && !working) {
            printf("\n--- Работа со списком не начата ---\n");
        }
    }

    return 0;
}