






#include <iostream> // Для операцій вводу-виводу (std::cout, std::cin, std::endl)
#include <string>   // Для використання рядків (std::string)
#include <vector>   // Для використання динамічних масивів (std::vector)
#include <sstream>  // Для роботи з рядковими потоками (std::stringstream)
#include <algorithm> // Для std::all_of (використовується для перевірки символів)

// Базовий клас для зберігання IP-адреси
class IPAddress {
protected:                       // Захищений член, доступний для похідних класів
    std::string ip_value;        // Рядок для зберігання IP-адреси

public:
    // Конструктор, що приймає рядок IP-адреси
    IPAddress(const std::string& ip) : ip_value(ip) {
        // std::cout << "IPAddress constructor called for: " << ip_value << std::endl; // Для відладки
    }

    // Конструктор копіювання
    IPAddress(const IPAddress& other) : ip_value(other.ip_value) {
        // std::cout << "IPAddress copy constructor called for: " << ip_value << std::endl; // Для відладки
    }

    // Віртуальний метод для виведення IP-адреси
    // "virtual" дозволяє похідним класам перевизначати цей метод
    // "const" означає, що метод не змінює стан об'єкта
    virtual void print() const {
        std::cout << ip_value; // Виводимо значення IP-адреси
    }

    // Віртуальний деструктор (хороша практика для базових класів з віртуальними методами)
    virtual ~IPAddress() {
        // std::cout << "IPAddress destructor called for: " << ip_value << std::endl; // Для відладки
    }
};

// Похідний клас, що додає перевірку коректності IP-адреси
class IPAddressChecked : public IPAddress {
private:                        // Приватні члени, доступні тільки всередині цього класу
    bool is_correct;            // Логічне значення: true, якщо IP коректний, false - якщо ні

    // Приватний допоміжний метод для перевірки коректності IP-адреси
    bool validateIP(const std::string& ip) {
        std::stringstream ss(ip); // Створюємо рядковий потік з IP-адреси для легкого розбору
        std::string segment;      // Рядок для зберігання кожного сегмента (октета) IP-адреси
        std::vector<int> segments; // Вектор для зберігання числових значень сегментів

        // Розділяємо рядок IP-адреси по крапках
        while(std::getline(ss, segment, '.')) {
            // Перевіряємо, чи сегмент не порожній і складається лише з цифр
            if (segment.empty() || !std::all_of(segment.begin(), segment.end(), ::isdigit)) {
                return false; // Якщо сегмент порожній або містить нецифрові символи, IP невірний
            }
            try {
                int num = std::stoi(segment); // Конвертуємо рядок сегмента в число
                segments.push_back(num);      // Додаємо числове значення сегмента до вектора
            } catch (const std::out_of_range& oor) {
                return false; // Якщо число занадто велике/мале для int, IP невірний
            } catch (const std::invalid_argument& ia) {
                return false; // Якщо сегмент не може бути конвертований в число, IP невірний
            }
        }

        // IP-адреса повинна мати рівно 4 сегменти
        if (segments.size() != 4) {
            return false; // Якщо кількість сегментів не 4, IP невірний
        }

        // Перевіряємо, чи кожен сегмент знаходиться в діапазоні [0, 255]
        for (int seg_val : segments) {
            if (seg_val < 0 || seg_val > 255) {
                return false; // Якщо значення сегмента виходить за межі [0, 255], IP невірний
            }
        }
        return true; // Якщо всі перевірки пройдені, IP-адреса коректна
    }

public:
    // Конструктор, що приймає рядок IP-адреси
    // Ініціалізує базовий клас IPAddress та встановлює значення is_correct
    IPAddressChecked(const std::string& ip) : IPAddress(ip) {
        is_correct = validateIP(ip_value); // Перевіряємо IP-адресу при створенні об'єкта
        // std::cout << "IPAddressChecked constructor called for: " << ip_value << ", correct: " << is_correct << std::endl; // Для відладки
    }

    // Конструктор копіювання
    IPAddressChecked(const IPAddressChecked& other) : IPAddress(other), is_correct(other.is_correct) {
        // Копіюємо дані базового класу та поле is_correct
        // std::cout << "IPAddressChecked copy constructor called for: " << ip_value << ", correct: " << is_correct << std::endl; // Для відладки
    }

    // Перевизначений метод print для виведення IP-адреси та її коректності
    // "override" гарантує, що ми дійсно перевизначаємо віртуальний метод базового класу
    void print() const override {
        IPAddress::print(); // Викликаємо метод print() базового класу для виведення IP-адреси [cite: 7]
        if (is_correct) {   // Якщо IP-адреса коректна
            std::cout << " Correct"; // Додаємо " Correct"
        } else {            // Якщо IP-адреса некоректна
            std::cout << " Not Correct"; // Додаємо " Not Correct"
        }
    }

    // Деструктор (необов'язковий тут, оскільки немає динамічно виділеної пам'яті в цьому класі)
    ~IPAddressChecked() {
        // std::cout << "IPAddressChecked destructor called for: " << ip_value << std::endl; // Для відладки
    }
};

// Головна функція програми
int main() {
    std::string ip_str1, ip_str2, ip_str3; // Рядки для зберігання введених IP-адрес

    // Отримуємо три IP-адреси від користувача [cite: 8]
    // std::cout << "Enter first IP address: "; // Запит на введення першої IP-адреси
    std::cin >> ip_str1;                    // Зчитуємо першу IP-адресу

    // std::cout << "Enter second IP address (checked): "; // Запит на введення другої IP-адреси
    std::cin >> ip_str2;                    // Зчитуємо другу IP-адресу

    // std::cout << "Enter third IP address (checked): "; // Запит на введення третьої IP-адреси
    std::cin >> ip_str3;                    // Зчитуємо третю IP-адресу

    // Створюємо один об'єкт IPAddress [cite: 8]
    IPAddress ip_obj1(ip_str1);

    // Створюємо два об'єкти IPAddressChecked [cite: 8]
    IPAddressChecked ip_obj2_checked(ip_str2);
    IPAddressChecked ip_obj3_checked(ip_str3);

    // Виводимо інформацію для всіх трьох об'єктів [cite: 9]
    ip_obj1.print();                       // Викликаємо print() для першого об'єкта
    std::cout << std::endl;                // Перехід на новий рядок

    ip_obj2_checked.print();               // Викликаємо print() для другого об'єкта
    std::cout << std::endl;                // Перехід на новий рядок

    ip_obj3_checked.print();               // Викликаємо print() для третього об'єкта
    std::cout << std::endl;                // Перехід на новий рядок

    return 0; // Повертаємо 0, що означає успішне завершення програми
}
