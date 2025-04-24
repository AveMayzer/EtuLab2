#include <iostream>;
#include <time.h>
#include <chrono> 
using namespace std;
using namespace chrono;


struct DoubleList {
    int data;
    DoubleList* next;
    DoubleList* prev;
};


DoubleList* getListByIndex(DoubleList* head, int index, int len) {

    DoubleList* current = head;

    if (index < 0 || index >= len || head == nullptr) {
        return nullptr;
    }
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}


void deleteList(DoubleList* &head) {
    DoubleList* current;
    while (head) {
        current = head;
        head = current->next;
        delete current;
    }

}

DoubleList* createDoubleList(int len) {

    DoubleList* current = nullptr;
    DoubleList* nextAdress = nullptr;

    for (int i = 0; i < len; i++) {
        current = new DoubleList();

        current->data = rand() % 100;

        current->next = nextAdress;

        if (nextAdress != nullptr) {
            nextAdress->prev = current;
        }

        current->prev = nullptr;
        nextAdress = current;
    }
    return current;
}

DoubleList* createDoubleListFromInput(int& len) {

    DoubleList* current = nullptr;
    DoubleList* nextAdress = nullptr;

    int value;

    cout << "Введите элементы списка (для выхода можно написать любую букву): ";

    while (cin >> value) {
        current = new DoubleList();

        current->data = value;

        current->next = nextAdress;

        if (nextAdress != nullptr) {
            nextAdress->prev = current;
        }

        current->prev = nullptr;
        nextAdress = current;
        len++;
    }
    return current;
}

void insertListByIndex(DoubleList*& head, int data, int index, int& len) {
    
    DoubleList* newList = new DoubleList();

    if (index < 0 || index > len) { 
        cout << "Неверный индекс для вставки. Допустимые индексы от 0 до " << len << endl;
        return;
    }

    newList->data = data;

    if (index == 0) { 
        newList->prev = nullptr;
        newList->next = head;
        if (head != nullptr) {
            head->prev = newList;
        }
        head = newList;
    }
    else { 
        DoubleList* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        newList->next = current->next;
        newList->prev = current;

        if (current->next != nullptr) {
            current->next->prev = newList;
        }
        current->next = newList;
    }
    len++; 
}

void deleteListByIndex(DoubleList*& head, int index, int& len) {
    if (head == nullptr) {
        cout << "Список пуст." << endl; return;
    }
    if (index < 0 || index >= len) {
        cout << "Неверный индекс. Допустимо от 0 до " << len - 1 << endl; return;
    }
    DoubleList* listToDelete = getListByIndex(head, index, len);
    if (!listToDelete) {
        cout << "Не удалось найти лист по индексу " << index << endl; return;
    }

    int deletedData = listToDelete->data;

    if (listToDelete == head) {
        head = listToDelete->next;
        if (head != nullptr) head->prev = nullptr;
    }
    else { 
        listToDelete->prev->next = listToDelete->next;
        if (listToDelete->next != nullptr) listToDelete->next->prev = listToDelete->prev;
    }
    delete listToDelete;
    len--;
    cout << "Элемент был удален." << endl;
}


void deleteListByValue(DoubleList*& head, int value, int& len) {
    if (head == nullptr) {
        cout << "Список пуст." << endl; return;
    }
    DoubleList* current = head;
    int index = 0;
    while (current != nullptr && current->data != value) {
        current = current->next;
        index++;
    }
    if (current == nullptr) {
        cout << "Элемент с введённым значением  не найден." << endl; return;
    }

    if (current == head) { 
        head = current->next;
        if (head != nullptr) head->prev = nullptr;
    }
    else { 
        current->prev->next = current->next;
        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }
    }
    delete current;
    len--;
    cout << "Элемент был удален." << endl;
}




void swapListsByIndex(DoubleList*& head, int index1, int index2, int len) {
    if (index1 < 0 || index1 >= len || index2 < 0 || index2 >= len) {
        cout << "Один или оба индекса некорректны для обмена. Допустимые индексы от 0 до " << len - 1 << endl;
        return;
    }

    if (index1 > index2) {
        swap(index1, index2);
    }

    DoubleList* list1 = getListByIndex(head, index1, len);
    DoubleList* list2 = getListByIndex(head, index2, len);

    DoubleList* prev1 = list1->prev;
    DoubleList* next1 = list1->next;
    DoubleList* prev2 = list2->prev;
    DoubleList* next2 = list2->next;

    if (next1 == list2) { 
        if (prev1 != nullptr) {
            prev1->next = list2;
        }
        else {
            head = list2;
        }
        list2->prev = prev1;
        list2->next = list1;
        list1->prev = list2;
        list1->next = next2;
        if (next2 != nullptr) {
            next2->prev = list1;
        }
    }
    else { 
        if (prev1 != nullptr) {
            prev1->next = list2;
        }
        else {
            head = list2;
        }
        list2->prev = prev1;
        list2->next = next1;
        if (next1 != nullptr) {
            next1->prev = list2;
        }

        if (prev2 != nullptr) {
            prev2->next = list1;
        }
        list1->prev = prev2;
        list1->next = next2;
        if (next2 != nullptr) {
            next2->prev = list1;
        }
    }

    cout << "Список по индексам успешно обменены местами." << endl;
}
void printLists(DoubleList* list) {
    DoubleList* curr = list;
    while (curr) {
        cout << "Объект: " << curr << endl;
        cout << "Данные: " << curr->data << endl;
        cout << "Следующий адрес: " << curr->next << endl;
        cout << "Предыдущий адрес: " << curr->prev << endl;
        cout << endl;

        curr = curr->next;
    }
}


int main() {
    setlocale(0, "");
    srand(time(NULL));
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds resultTime;
    DoubleList* list = nullptr;

    int needIndex;
    int needIndex2;
    int needData;
    int needValue;

    int len = 0;
    int* ptrlen = &len;
    
    bool running = true;
    bool listCreated = false;

    


    while (running) {
        if (!listCreated) {
            int choice;
            cout << "  | Ввыберите действия как вы хотите создать список." << endl;
            cout << "1 | Создать список размерностью N со случайными цифрами." << endl;
            cout << "2 | Создать список наполняя своими данными." << endl;
            cout << "0 | Выход из программы" << endl;

            cin >> choice;

            switch (choice) {
                    case 1: {
                        int n;
                        cout << "Введите количество элементов в списке: ";
                        cin >> n;

                        start = steady_clock::now();
                        list = createDoubleList(n);
                        end = steady_clock::now();
                        resultTime = duration_cast<nanoseconds>(end - start);
                        len = n;
                        cout << "Двусвязный список успешно создал. Затрачено времени: " << resultTime.count() << endl;
                        listCreated = true; break;

                    case 2: {
                        start = steady_clock::now();
                        list = createDoubleListFromInput(*ptrlen);
                        end = steady_clock::now();
                        resultTime = duration_cast<nanoseconds>(end - start);

                        cout << "Двусвязный список успешно создал. Затрачено времени: " << resultTime.count() << endl;
                        listCreated = true; 
                        cin.clear();
                        cin.ignore();
                        break;
                    }
                    case 0: {
                        running = false;
                        break;
                    }
                    }
                }
            }
        else {

            cout << "& | Ввыберите действия для взаимодействия со списком." << endl;
            cout << "1 | Вывести список" << endl;
            cout << "2 | Вставить элемент по индексу" << endl;
            cout << "3 | Удалить элемент по индексу" << endl;
            cout << "4 | Удалить элемент по значению" << endl;
            cout << "5 | Обменять элементы по индексам" << endl;
            cout << "6 | Получить элемент по индексу" << endl;
            cout << "0 | Выход" << endl;

            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "Содержимое списка: " << endl;
                printLists(list); break;
            }
            case 2: {
                cout << "Введите индекс для вставки: " << endl;
                cin >> needIndex;

                cout << "Введите значение для вставки: " << endl;
                cin >> needValue;

                start = steady_clock::now();
                insertListByIndex(list, needValue, needIndex, *ptrlen);
                end = steady_clock::now();
                resultTime = duration_cast<nanoseconds>(end - start);
                cout << "Вставка выполнена за " << resultTime.count() << endl; break;
            }
            case 3: {
                cout << "Введите индекс для удаления: " << endl;
                cin >> needIndex;

                start = steady_clock::now();
                deleteListByIndex(list, needIndex, *ptrlen);
                end = steady_clock::now();
                resultTime = duration_cast<nanoseconds>(end - start);
                cout << "Удаление выполнено за " << resultTime.count() << endl; break;
            }
            case 4: {
                cout << "Введите значение для удаления: " << endl;
                cin >> needValue;

                start = steady_clock::now();
                deleteListByValue(list, needValue, *ptrlen);
                end = steady_clock::now();
                resultTime = duration_cast<nanoseconds>(end - start);
                cout << "Удаление выполнено за " << resultTime.count() << endl; break;
            }
            case 5: {
                cout << "Введите первый индекс: " << endl;
                cin >> needIndex;

                cout << "Введите второй индекс: " << endl;
                cin >> needIndex2;

                swapListsByIndex(list, needIndex, needIndex2, *ptrlen); break;
            }
            case 6: {
                cout << "Введите индекс для получения элемента: " << endl;
                cin >> needIndex;

                start = steady_clock::now();
                DoubleList* current = getListByIndex(list, needIndex, *ptrlen);
                end = steady_clock::now();
                resultTime = duration_cast<nanoseconds>(end - start);
                if (current) {
                    cout << "Объект: " << current << endl;
                    cout << "Данные: " << current->data << endl;
                    cout << "Следующий адрес: " << current->next << endl;
                    cout << "Предыдущий адрес: " << current->prev << endl;
                }
                
                cout << "Получена информация по списку за: " << resultTime.count() << endl; break;

            }
            }
        }
        }

    return 0;
}
