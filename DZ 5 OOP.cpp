#include <iostream>
#include <cstring> // для работы с С-строками

class String {
private:
    char* str; // указатель на массив символов
    int length; // текущая длина строки
    int capacity; // выделенная память

    // Приватный метод для проверки и расширения выделенной памяти
    void reserve(int new_capacity) {
        if (new_capacity > capacity) {
            char* new_str = new char[new_capacity + 1]; // выделяем новый буфер
            std::strcpy(new_str, str); // копируем текущую строку
            delete[] str; // удаляем старый буфер
            str = new_str; // обновляем указатель
            capacity = new_capacity; // обновляем размер выделенной памяти
        }
    }

public:
    // Конструкторы
    String() : str(nullptr), length(0), capacity(0) {}

    String(const char* s) {
        length = std::strlen(s);
        capacity = length;
        str = new char[capacity + 1];
        std::strcpy(str, s);
    }

    // Деструктор
    ~String() {
        delete[] str;
    }

    // Конструктор копирования
    String(const String& other) {
        length = other.length;
        capacity = other.capacity;
        str = new char[capacity + 1];
        std::strcpy(str, other.str);
    }

    // Оператор присваивания
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            capacity = other.capacity;
            str = new char[capacity + 1];
            std::strcpy(str, other.str);
        }
        return *this;
    }

    // Методы для работы со строками


     // Метод insert :
     // Принимает позицию(pos) и С - строку(s), которую нужно вставить.
     // Проверяет допустимость позиции.
     // Резервирует дополнительную память при необходимости.
     // Использует std::memmove для сдвига части строки и вставки подстроки.
     // Обновляет длину строки.

    void insert(int pos, const char* s) {
        if (pos < 0 || pos > length) {
            std::cerr << "Invalid position for insertion";
                return;
        }
        int len_insert = std::strlen(s);
        reserve(length + len_insert); // увеличиваем выделенную память при необходимости

        // Сдвигаем часть строки после вставки
        std::memmove(str + pos + len_insert, str + pos, (length - pos + 1) * sizeof(char));

        // Вставляем подстроку
        std::memcpy(str + pos, s, len_insert * sizeof(char));

        // Обновляем длину строки
        length += len_insert;
    }
    // Метод replace :

    // Принимает С - строку(old_s), которую нужно заменить, и новую С - строку(new_s).
    // первое вхождение old_s с помощью метода find.
    // Если подстрока найдена, вычисляет разницу в длине между old_s и new_s.
    // Резервирует память при необходимости, заменяет подстроку и сдвигает оставшуюся часть строки.
    
     
    // Замена подстроки на другую строку
    void replace(const char* old_s, const char* new_s) {
        int pos = find(old_s); // находим позицию подстроки

        if (pos != -1) {
            int len_old = std::strlen(old_s);
            int len_new = std::strlen(new_s);
            int diff = len_new - len_old;

            if (diff > 0)
                reserve(length + diff); // увеличиваем выделенную память при необходимости

            // Заменяем подстроку
            std::memcpy(str + pos, new_s, len_new * sizeof(char));

            // Сдвигаем оставшуюся часть строки
            std::memmove(str + pos + len_new, str + pos + len_old, (length - pos - len_old + 1) * sizeof(char));

            // Обновляем длину строки
            length += diff;
        }
    }
    // Метод find :
    // Принимает С - строку(s), которую нужно найти в текущей строке.
    // Использует std::strstr для поиска первого вхождения подстроки.
    // Возвращает позицию найденной подстроки или - 1, если подстрока не найдена.
    // Вставка подстроки в указанную позицию
    // Поиск подстроки в строке
    int find(const char* s) const {
        char* found = std::strstr(str, s);
        if (found != nullptr) {
            return found - str; // возвращаем позицию найденной подстроки
        }
        return -1; // подстрока не найдена
    }

    // Метод для вывода строки на экран
    void print() const {
        std::cout << str << std::endl;
    }
};