#include <iostream>
#include <string>

// ============================================================================
// ZAVDANNYA 1: Struktura uspadkuvannya zghidno z Rys. 12 (5 klasiv v iyerarkhiyi)
// ============================================================================

// --- Variant BEZ virtualnoho uspadkuvannya ---
class Base1 {
protected:
    int base_val;
public:
    Base1() : base_val(10) { std::cout << "-> Base1 stvoreno\n"; }
    virtual ~Base1() { std::cout << "-> Base1 znyshcheno\n"; }
};

class Derived1_1 : public Base1 {
protected:
    int d1_val;
public:
    Derived1_1() : Base1(), d1_val(20) { std::cout << "-> Derived1_1 stvoreno\n"; }
    ~Derived1_1() override { std::cout << "-> Derived1_1 znyshcheno\n"; }
};

class Derived1_2 : public Base1 {
protected:
    double d2_val;
public:
    Derived1_2() : Base1(), d2_val(30.5) { std::cout << "-> Derived1_2 stvoreno\n"; }
    ~Derived1_2() override { std::cout << "-> Derived1_2 znyshcheno\n"; }
};

// Promizhniy klas romba (Nasleduye Derived1_1 ta Derived1_2 zvychaynym shlyakhom)
class Derived1_3 : public Derived1_1, public Derived1_2 {
protected:
    int d3_val;
public:
    Derived1_3() : Derived1_1(), Derived1_2(), d3_val(40) { std::cout << "-> Derived1_3 stvoreno\n"; }
    ~Derived1_3() override { std::cout << "-> Derived1_3 znyshcheno\n"; }
};

// Kintseviy klas iyerarkhiyi BEZ virtualnoho nasliduvannya
class Final1 : public Derived1_3 {
protected:
    int final_val;
public:
    Final1() : Derived1_3(), final_val(50) { std::cout << "-> Final1 stvoreno\n"; }
    ~Final1() override { std::cout << "-> Final1 znyshcheno\n"; }
};


// --- Variant IZ virtualnym uspadkuvannyam ---
class Base1V {
protected:
    int base_val;
public:
    Base1V() : base_val(10) { std::cout << "-> Base1V (Virtualnyy) stvoreno\n"; }
    virtual ~Base1V() { std::cout << "-> Base1V (Virtualnyy) znyshcheno\n"; }
};

// Vykorystovuyemo virtual dlya usunennya dublyuvannya Base1V u pamyati
class Derived1_1V : virtual public Base1V {
protected:
    int d1_val;
public:
    Derived1_1V() : Base1V(), d1_val(20) { std::cout << "-> Derived1_1V stvoreno\n"; }
    ~Derived1_1V() override { std::cout << "-> Derived1_1V znyshcheno\n"; }
};

class Derived1_2V : virtual public Base1V {
protected:
    double d2_val;
public:
    Derived1_2V() : Base1V(), d2_val(30.5) { std::cout << "-> Derived1_2V stvoreno\n"; }
    ~Derived1_2V() override { std::cout << "-> Derived1_2V znyshcheno\n"; }
};

// Promizhniy klas romba. Oskilky bazy virtualni, vin MAIYE yavno vyklykaty Base1V()
class Derived1_3V : public Derived1_1V, public Derived1_2V {
protected:
    int d3_val;
public:
    Derived1_3V() : Base1V(), Derived1_1V(), Derived1_2V(), d3_val(40) {
        std::cout << "-> Derived1_3V stvoreno\n";
    }
    ~Derived1_3V() override { std::cout << "-> Derived1_3V znyshcheno\n"; }
};

// Kintseviy klas iyerarkhiyi. Vin takozh MAIYE yavno vyklykaty najvyshchyy virtualnyy korin Base1V()
class Final1V : public Derived1_3V {
protected:
    int final_val;
public:
    Final1V() : Base1V(), Derived1_3V(), final_val(50) { std::cout << "-> Final1V stvoreno\n"; }
    ~Final1V() override { std::cout << "-> Final1V znyshcheno\n"; }
};

// Funktsiya demonstratsiyi rozmiriv obyektiv dlya Zavdannya 1
void runTask1() {
    std::cout << "\n--- Zavdannya 1: Doslidzhennya rozmiriv obyektiv (na osnovi Rys. 12) ---\n";

    std::cout << "\nStvorenya obyektiv iyerarkhiyi BEZ virtualnoho uspadkuvannya:\n";
    {
        Final1 obj1;
        std::cout << "Rozmir Base1: " << sizeof(Base1) << " bayt\n";
        std::cout << "Rozmir Derived1_1: " << sizeof(Derived1_1) << " bayt\n";
        std::cout << "Rozmir Derived1_2: " << sizeof(Derived1_2) << " bayt\n";
        std::cout << "Rozmir Derived1_3: " << sizeof(Derived1_3) << " bayt\n";
        std::cout << "Rozmir Final1: " << sizeof(Final1) << " bayt\n";
    }

    std::cout << "\nStvorenya obyektiv iyerarkhiyi Z virtualnym uspadkuvannyam:\n";
    {
        Final1V obj1V;
        std::cout << "Rozmir Base1V: " << sizeof(Base1V) << " bayt\n";
        std::cout << "Rozmir Derived1_1V: " << sizeof(Derived1_1V) << " bayt\n";
        std::cout << "Rozmir Derived1_2V: " << sizeof(Derived1_2V) << " bayt\n";
        std::cout << "Rozmir Derived1_3V: " << sizeof(Derived1_3V) << " bayt\n";
        std::cout << "Rozmir Final1V: " << sizeof(Final1V) << " bayt\n";
    }
}


// ============================================================================
// ZAVDANNYA 2: Abstraktni klasy ta virtualni funktsiyi (Zadacha 2.12)
// ============================================================================

class Data {
protected:
    std::string dataName;
public:
    Data(const std::string& name) : dataName(name) {
        std::cout << "-> Data [" << dataName << "] stvoreno\n";
    }
    virtual ~Data() {
        std::cout << "-> Data [" << dataName << "] znyshcheno\n";
    }

    virtual void display() const = 0;
    virtual void save() const = 0;
    virtual void process() = 0;
};

class SignalData : public Data {
private:
    double frequency;
    double amplitude;
public:
    SignalData(const std::string& name, double freq, double amp)
        : Data(name), frequency(freq), amplitude(amp) {
        std::cout << "-> SignalData stvoreno\n";
    }
    ~SignalData() override {
        std::cout << "-> SignalData znyshcheno\n";
    }

    void display() const override {
        std::cout << "Dani syhnalu: Nazva = " << dataName
            << ", Chastota = " << frequency << " Hz"
            << ", Amplituda = " << amplitude << " V\n";
    }
    void save() const override {
        std::cout << "Zberezhennya danykh syhnalu [" << dataName << "] u fayl...\n";
    }
    void process() override {
        std::cout << "Obrobka syhnalu: Pidsylennya syhnalu shlyakhom mnozhennya komponentiv...\n";
        amplitude *= 1.5;
    }
};

class ResultData : public Data {
private:
    int errorCode;
    std::string status;
public:
    ResultData(const std::string& name, int code, const std::string& stat)
        : Data(name), errorCode(code), status(stat) {
        std::cout << "-> ResultData stvoreno\n";
    }
    ~ResultData() override {
        std::cout << "-> ResultData znyshcheno\n";
    }

    void display() const override {
        std::cout << "Dani rezultatu: Nazva = " << dataName
            << ", Kod pomylky = " << errorCode
            << ", Status = " << status << "\n";
    }
    void save() const override {
        std::cout << "Zberezhennya danykh rezultatu [" << dataName << "] u bazu danykh...\n";
    }
    void process() override {
        std::cout << "Obrobka rezultatu: Perevirka kodiv pomylok ta staniv statusu...\n";
        if (errorCode == 0) status = "Pidtverdzheno uspishno";
    }
};

class AuxiliaryData : public Data {
private:
    std::string systemNode;
public:
    AuxiliaryData(const std::string& name, const std::string& node)
        : Data(name), systemNode(node) {
        std::cout << "-> AuxiliaryData stvoreno\n";
    }
    ~AuxiliaryData() override {
        std::cout << "-> AuxiliaryData znyshcheno\n";
    }

    void display() const override {
        std::cout << "Dopomizhni dani: Nazva = " << dataName
            << ", Systemnyy vuzol = " << systemNode << "\n";
    }
    void save() const override {
        std::cout << "Zberezhennya dopomizhnykh danykh [" << dataName << "] u systemnyy zhurnal...\n";
    }
    void process() override {
        std::cout << "Obrobka dopomizhnykh danykh: Onovlennya statusu systemnoho vuzla...\n";
        systemNode += " (Onovleno)";
    }
};

void runTask2() {
    std::cout << "\n--- Zavdannya 2: Platforma obrobky abstraktnykh danykh ---\n";

    std::string sName, rName, aName, rStatus, aNode;
    double sFreq, sAmp;
    int rCode;

    std::cout << "Vvedit nazvu danykh syhnalu: ";
    std::cin >> sName;
    std::cout << "Vvedit chastotu syhnalu (Hz): ";
    std::cin >> sFreq;
    std::cout << "Vvedit amplitudu syhnalu (V): ";
    std::cin >> sAmp;

    std::cout << "\nVvedit nazvu danykh rezultatu: ";
    std::cin >> rName;
    std::cout << "Vvedit kod pomylky rezultatu (0 dlya uspihu): ";
    std::cin >> rCode;
    std::cout << "Vvedit status rezultatu: ";
    std::cin >> rStatus;

    std::cout << "\nVvedit nazvu dopomizhnykh danykh: ";
    std::cin >> aName;
    std::cout << "Vvedit systemnyy vuzol dlya dopomizhnykh danykh: ";
    std::cin >> aNode;

    std::cout << "\n--- Stvorennya polimorfnykh obyektiv ---\n";
    Data* PolymorphicArray[3];
    PolymorphicArray[0] = new SignalData(sName, sFreq, sAmp);
    PolymorphicArray[1] = new ResultData(rName, rCode, rStatus);
    PolymorphicArray[2] = new AuxiliaryData(aName, aNode);

    std::cout << "\n--- Testuvannya polimorfnykh metodiv ---\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "\n[Obyekt " << i + 1 << "]:\n";
        PolymorphicArray[i]->display();
        PolymorphicArray[i]->process();
        PolymorphicArray[i]->display();
        PolymorphicArray[i]->save();
    }

    std::cout << "\n--- Ochyshchennya pamyati ---\n";
    for (int i = 0; i < 3; ++i) {
        delete PolymorphicArray[i];
    }
}


// ============================================================================
// ZAVDANNYA 3: Mnozhynne uspadkuvannya z virtualnymy bazovymy klasamy (Zadacha 3.12)
// ============================================================================

class DataSource {
protected:
    std::string sourceID;
public:
    DataSource() : sourceID("Nevidomo") {}
    DataSource(const std::string& id) : sourceID(id) {
        std::cout << "-> DataSource stvoreno\n";
    }
    virtual ~DataSource() {
        std::cout << "-> DataSource znyshcheno\n";
    }
};

class Signal : virtual public DataSource {
protected:
    double rawValue;
public:
    Signal(const std::string& id, double val) : DataSource(id), rawValue(val) {
        std::cout << "-> Sehment Signal stvoreno\n";
    }
    ~Signal() override {
        std::cout << "-> Sehment Signal znyshcheno\n";
    }
};

class Result : virtual public DataSource {
protected:
    std::string algorithmName;
public:
    Result(const std::string& id, const std::string& algo) : DataSource(id), algorithmName(algo) {
        std::cout << "-> Sehment Result stvoreno\n";
    }
    ~Result() override {
        std::cout << "-> Sehment Result znyshcheno\n";
    }
};

class SignalResult : public Signal, public Result {
private:
    double processedOutput;
public:
    SignalResult(const std::string& id, double val, const std::string& algo, double output)
        : DataSource(id), Signal(id, val), Result(id, algo), processedOutput(output) {
        std::cout << "-> SignalResult (Kombinovane mnozhynne uspadkuvannya) stvoreno\n";
    }
    ~SignalResult() override {
        std::cout << "-> SignalResult znyshcheno\n";
    }

    SignalResult(const SignalResult& other)
        : DataSource(other.sourceID), Signal(other.sourceID, other.rawValue),
        Result(other.sourceID, other.algorithmName), processedOutput(other.processedOutput) {
        std::cout << "-> Vyklykano konstruktor kopiyuvannya SignalResult\n";
    }

    void printInfo() const {
        std::cout << "Struktura obyekta SignalResult:\n"
            << " - Identyfikator dzherela (spilnyy bazovyy): " << sourceID << "\n"
            << " - Vkhidne pochatkove znachennya: " << rawValue << "\n"
            << " - Zastosovanyy alhorytmy obrobky: " << algorithmName << "\n"
            << " - Kintsevyy obroblenyy rezultat: " << processedOutput << "\n";
    }
};

void runTask3() {
    std::cout << "\n--- Zavdannya 3: Doslidzhennya mnozhnoho uspadkuvannya ---\n";

    std::string id, algo;
    double inputVal, outputVal;

    std::cout << "Vvedit rjadok ID dzherela: ";
    std::cin >> id;
    std::cout << "Vvedit chyslove znachennya vkhidnoho syhnalu: ";
    std::cin >> inputVal;
    std::cout << "Vvedit nazvu zastosovanoho alhorytmu: ";
    std::cin >> algo;
    std::cout << "Vvedit chyslovyy rezultat kintsevoho vyvodu: ";
    std::cin >> outputVal;

    std::cout << "\n--- Stvorennya obyekta z mnozhynnym uspadkuvannyam ---\n";
    SignalResult originalObj(id, inputVal, algo, outputVal);
    originalObj.printInfo();

    std::cout << "\n--- Testuvannya konstruktora kopiyuvannya ---\n";
    SignalResult copiedObj = originalObj;
    copiedObj.printInfo();

    std::cout << "\n--- Protses znyshchennya obyektiv ---\n";
}


// ============================================================================
// HOLOVNA FUNKTSIYA PROHRAMY TA SYSTEMA KONSOLNOHO MENYU
// ============================================================================

int main() {
    int userChoice = 0;

    do {
        std::cout << "\n=============================================\n";
        std::cout << "         MENYU NALASHTUVANNYA LAB 6          \n";
        std::cout << "=============================================\n";
        std::cout << " 1. Vykonaty Zavdannya 1 (Rozmiry: Virtualni vs Zvychayni)\n";
        std::cout << " 2. Vykonaty Zavdannya 2 (Polimorfna iyerarkhiya danykh)\n";
        std::cout << " 3. Vykonaty Zavdannya 3 (Mnozhynne uspadkuvannya virtualnykh baz)\n";
        std::cout << " 4. Vyjty z prohramy\n";
        std::cout << "=============================================\n";
        std::cout << "Vvedit vash vybir (1-4): ";

        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            runTask1();
            break;
        case 2:
            runTask2();
            break;
        case 3:
            runTask3();
            break;
        case 4:
            std::cout << "Vykhid z prohramy. Robotu zaversheno uspishno.\n";
            break;
        default:
            std::cout << "Nekorektnyy vybir. Bud laska, vyberit variant vid 1 do 4.\n";
            break;
        }
    } while (userChoice != 4);

    return 0;
}