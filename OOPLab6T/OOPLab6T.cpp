#include <iostream>
#include <string>

// ============================================================================
// ЗАВДАННЯ 1: Ієрархія класів за Рис. 12 
// ============================================================================

// --- 1.1. Звичайне успадкування (без virtual) ---
class D2 {
protected:
    int d2;
public:
    D2() : d2(2) {}
};

class D3 {
protected:
    int d3;
public:
    D3() : d3(3) {}
};

class D1 : public D2, public D3 {
protected:
    int d1;
public:
    D1() : d1(1) {}
};

class D4 : public D1 {
protected:
    int d4;
public:
    D4() : d4(4) {}
};

class Base : public D1, public D4 {
protected:
    int b;
public:
    Base() : b(10) {}
};

class D5 : public Base {
protected:
    int d5;
public:
    D5() : d5(5) {}
};


// --- 1.2. Віртуальне успадкування (з правильним virtual) ---
class D2V {
protected:
    int d2;
public:
    D2V() : d2(2) {}
};

class D3V {
protected:
    int d3;
public:
    D3V() : d3(3) {}
};

class D1V : virtual public D2V, virtual public D3V {
protected:
    int d1;
public:
    D1V() : d1(1) {}
};

class D4V : virtual public D1V {
protected:
    int d4;
public:
    D4V() : d4(4) {}
};

class BaseV : virtual public D1V, virtual public D4V {
protected:
    int b;
public:
    BaseV() : b(10) {}
};

class D5V : public BaseV {
protected:
    int d5;
public:
    D5V() : d5(5) {}
};


// ============================================================================
// ЗАВДАННЯ 2: Абстрактні класи (Задача 2.12)
// ============================================================================
class Data {
protected:
    std::string name;
public:
    Data(std::string n) : name(n) {}
    virtual ~Data() {}

    // Чисто віртуальні методи
    virtual void display() const = 0;
    virtual void save() = 0;
    virtual void process() = 0;
};

class SignalData : public Data {
private:
    double frequency;
public:
    SignalData(std::string n, double freq) : Data(n), frequency(freq) {}
    void display() const override {
        std::cout << "Сигнал: " << name << ", Частота: " << frequency << " Гц" << std::endl;
    }
    void save() override { std::cout << "Збереження сигналу у файл..." << std::endl; }
    void process() override { std::cout << "Обробка частотного сигналу..." << std::endl; }
};

class ResultData : public Data {
private:
    int errorCode;
public:
    ResultData(std::string n, int err) : Data(n), errorCode(err) {}
    void display() const override {
        std::cout << "Результат: " << name << ", Код помилки: " << errorCode << std::endl;
    }
    void save() override { std::cout << "Збереження результатів у БД..." << std::endl; }
    void process() override { std::cout << "Аналіз помилок виконання..." << std::endl; }
};

class AuxiliaryData : public Data {
private:
    std::string timestamp;
public:
    AuxiliaryData(std::string n, std::string time) : Data(n), timestamp(time) {}
    void display() const override {
        std::cout << "Допоміжні дані: " << name << ", Мітка часу: " << timestamp << std::endl;
    }
    void save() override { std::cout << "Логування мітки часу..." << std::endl; }
    void process() override { std::cout << "Синхронізація часу систем..." << std::endl; }
};


// ============================================================================
// ЗАВДАННЯ 3: Ієрархія типів (Задача 3.12: Сигнал -> Результат -> Допоміжні дані)
// ============================================================================
class Signal {
protected:
    std::string type;
    int duration;
public:
    Signal() : type("Unknown"), duration(0) {}
    Signal(std::string t, int d) : type(t), duration(d) {}

    // Конструктор копіювання
    Signal(const Signal& other) : type(other.type), duration(other.duration) {}

    virtual ~Signal() {}

    // Перевантаження операторів введення/виведення через потоки
    friend std::ostream& operator<<(std::ostream& out, const Signal& s) {
        out << "Тип: " << s.type << ", Тривалість: " << s.duration << " сек";
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Signal& s) {
        std::cout << "Введіть тип сигналу: "; in >> s.type;
        std::cout << "Введіть тривалість: "; in >> s.duration;
        return in;
    }
};

class ProcessingResultObj : public Signal {
private:
    std::string status;
public:
    ProcessingResultObj() : Signal(), status("None") {}
    ProcessingResultObj(std::string t, int d, std::string stat) : Signal(t, d), status(stat) {}

    // Конструктор копіювання
    ProcessingResultObj(const ProcessingResultObj& other) : Signal(other), status(other.status) {}

    ~ProcessingResultObj() override {}

    friend std::ostream& operator<<(std::ostream& out, const ProcessingResultObj& pr) {
        out << static_cast<const Signal&>(pr) << ", Статус обробки: " << pr.status;
        return out;
    }
};

class AuxDataObj : public ProcessingResultObj {
private:
    int systemId;
public:
    AuxDataObj() : ProcessingResultObj(), systemId(0) {}
    AuxDataObj(std::string t, int d, std::string stat, int id) : ProcessingResultObj(t, d, stat), systemId(id) {}

    // Конструктор копіювання
    AuxDataObj(const AuxDataObj& other) : ProcessingResultObj(other), systemId(other.systemId) {}

    ~AuxDataObj() override {}

    friend std::ostream& operator<<(std::ostream& out, const AuxDataObj& ad) {
        out << static_cast<const ProcessingResultObj&>(ad) << ", ID Системи: " << ad.systemId;
        return out;
    }
};


// ============================================================================
// ГОЛОВНА ФУНКЦІЯ ПРОГРАМИ
// ============================================================================
int main() {
    // Встановлення коректного відображення символів (якщо потрібно)
    std::setlocale(LC_ALL, "");

    std::cout << "=== ЗАВДАННЯ 1: Порівняння розмірів об'єктів (Рис. 12) ===" << std::endl;
    std::cout << "Розмір D5 (Без virtual): " << sizeof(D5) << " байт" << std::endl;
    std::cout << "Розмір D5V (З virtual):  " << sizeof(D5V) << " байт" << std::endl;
    std::cout << std::endl;

    std::cout << "=== ЗАВДАННЯ 2: Поліморфний масив абстрактного класу ===" << std::endl;
    SignalData sig("Аналоговий", 120.5);
    ResultData res("Успіх", 0);
    AuxiliaryData aux("Метрика", "12:00");

    Data* arr[3] = { &sig, &res, &aux };
    for (int i = 0; i < 3; ++i) {
        arr[i]->display();
        arr[i]->process();
        arr[i]->save();
        std::cout << "------------------------------------" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== ЗАВДАННЯ 3: Перевірка конструкторів копіювання та потоків ===" << std::endl;
    AuxDataObj original("Спектральний", 45, "Оброблено", 1024);
    std::cout << "Оригінальний об'єкт: " << original << std::endl;

    // Перевірка роботи конструктора копіювання
    AuxDataObj copied = original;
    std::cout << "Скопійований об'єкт: " << copied << std::endl;

    return 0;
}