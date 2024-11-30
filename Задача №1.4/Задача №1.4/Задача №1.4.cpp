#include <iostream>
#include <stdexcept>

class VectorShort {
private:
    short* data;     // Динамічний масив
    size_t size;     // Розмір вектора
    int codeError;   // Код помилки
    static int objectCount; // Лічильник об'єктів

public:
    // Конструктор без параметрів
    VectorShort() : size(1), codeError(0) {
        data = new short[1] {0};
        objectCount++;
    }

    // Конструктор із одним параметром (розмір)
    VectorShort(size_t size) : size(size), codeError(0) {
        data = new short[size]();
        objectCount++;
    }

    // Конструктор із двома параметрами (розмір і значення)
    VectorShort(size_t size, short value) : size(size), codeError(0) {
        data = new short[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
        objectCount++;
    }

    // Конструктор копіювання
    VectorShort(const VectorShort& other) : size(other.size), codeError(0) {
        data = new short[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        objectCount++;
    }

    // Деструктор
    ~VectorShort() {
        delete[] data;
        objectCount--;
    }

    // Оператор присвоєння
    VectorShort& operator=(const VectorShort& other) {
        if (this == &other) return *this;
        delete[] data;

        size = other.size;
        data = new short[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        codeError = 0;
        return *this;
    }

    // Префіксний інкремент
    VectorShort& operator++() {
        for (size_t i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    // Постфіксний інкремент
    VectorShort operator++(int) {
        VectorShort temp(*this);
        ++(*this);
        return temp;
    }

    // Префіксний декремент
    VectorShort& operator--() {
        for (size_t i = 0; i < size; ++i) {
            --data[i];
        }
        return *this;
    }

    // Постфіксний декремент
    VectorShort operator--(int) {
        VectorShort temp(*this);
        --(*this);
        return temp;
    }

    // Логічне заперечення
    bool operator!() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != 0) return false;
        }
        return true;
    }

    // Побітове заперечення
    VectorShort operator~() const {
        VectorShort result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = ~data[i];
        }
        return result;
    }

    // Зміна знака елементів
    VectorShort operator-() const {
        VectorShort result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = -data[i];
        }
        return result;
    }

    // Арифметичні оператори
    VectorShort& operator+=(const VectorShort& other) {
        if (size != other.size) throw std::invalid_argument("Sizes must match.");
        for (size_t i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    VectorShort& operator-=(const VectorShort& other) {
        if (size != other.size) throw std::invalid_argument("Sizes must match.");
        for (size_t i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    VectorShort& operator*=(short scalar) {
        for (size_t i = 0; i < size; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    VectorShort& operator/=(short scalar) {
        if (scalar == 0) throw std::invalid_argument("Division by zero.");
        for (size_t i = 0; i < size; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }

    VectorShort operator+(const VectorShort& other) const {
        VectorShort result(*this);
        result += other;
        return result;
    }

    VectorShort operator-(const VectorShort& other) const {
        VectorShort result(*this);
        result -= other;
        return result;
    }

    VectorShort operator*(short scalar) const {
        VectorShort result(*this);
        result *= scalar;
        return result;
    }

    VectorShort operator/(short scalar) const {
        VectorShort result(*this);
        result /= scalar;
        return result;
    }

    // Оператор доступу
    short& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range.");
        return data[index];
    }

    const short& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range.");
        return data[index];
    }

    // Вивід у потік
    friend std::ostream& operator<<(std::ostream& os, const VectorShort& vec) {
        os << "[";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i];
            if (i < vec.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    // Порівняння
    bool operator==(const VectorShort& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const VectorShort& other) const {
        return !(*this == other);
    }

    // Отримання кількості об'єктів
    static int getObjectCount() {
        return objectCount;
    }
};

// Ініціалізація статичного лічильника
int VectorShort::objectCount = 0;

// Тестова програма
int main() {

    setlocale(LC_ALL, "ukr");

    VectorShort v1(5, 2);  // Вектор розміром 5, заповнений 2
    VectorShort v2(5, 3);  // Вектор розміром 5, заповнений 3

    v1 += v2;  // Додавання векторів
    std::cout << "v1 після додавання: " << v1 << std::endl;

    v1 *= 2;  // Множення на скаляр
    std::cout << "v1 після множення на 2: " << v1 << std::endl;

    return 0;
}
