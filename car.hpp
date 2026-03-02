#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>

// Forward declaration
namespace mt {
    struct Radio;
    class Car;
}

namespace mt {

class Car {
private:
    std::string brand_;
    std::string model_;
    std::string body_number_;
    std::string license_plate_;
    int mileage_;
    
    // ДИНАМИЧЕСКОЕ ПОЛЕ - указатель на вектор вещей в багажнике
    std::vector<std::string>* trunk_items_;
    
    // ПОЛЕ ДЛЯ МАГНИТОЛЫ
    Radio* radio_;  // указатель на магнитолу (может быть nullptr)

    bool is_mileage_valid_(int mileage) const {
        return mileage >= 0;
    }

    // проверка гос номера
    bool check_license_format_(const std::string& plate) const;
    
    // генерация случайного госномера
    std::string generate_random_plate_() const;
    
    // вспомогательный метод для группировки повторов
    void group_duplicates_(std::vector<std::string>& items) const;

public:
    // конструктор по умолчанию
    Car();
    
    // конструктор полного заполнения
    Car(const std::string& brand, const std::string& model,
        const std::string& body_number, const std::string& license_plate,
        int mileage, const std::vector<std::string>& trunk_items = {});
    
    // конструктор копирования (правило трех)
    Car(const Car& other);
    
    // оператор присваивания (правило трех)
    Car& operator=(const Car& other);
    
    // деструктор (правило трех)
    ~Car();
    
    // ГЕТТЕРЫ
    std::string get_brand() const { return brand_; }
    std::string get_model() const { return model_; }
    std::string get_body_number() const { return body_number_; }
    std::string get_license_plate() const { return license_plate_; }
    int get_mileage() const { return mileage_; }
    std::vector<std::string> get_trunk_items() const { return *trunk_items_; }
    Radio* get_radio() const { return radio_; }
    
    // СЕТТЕРЫ
    void set_body_number(const std::string& body_number);
    void set_license_plate(const std::string& license_plate);
    void set_radio(Radio* radio);
    
    // метод для вывода всей информации
    void print_info() const;
    
    // метод для скручивания пробега на X
    void rollback_mileage(int x);
    
    // метод для увеличения пробега
    void drive(int distance);
    
    // метод для добавления вещей в багажник
    void add_to_trunk(const std::string& item);
    
    // метод для удаления вещей из багажника
    void remove_from_trunk(const std::string& item);
    
    // ОПЕРАТОРЫ
    Car operator+(const Car& other) const;
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;
    bool operator==(const Car& other) const;
    bool operator!=(const Car& other) const;
    
    // оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
};

} // namespace mt
