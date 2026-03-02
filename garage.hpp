#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace mt {

// Forward declaration
class Car;

// СТРУКТУРА МАГНИТОЛА
struct Radio {
    std::string model;      // название модели
    std::string description; // описание
    double price;           // цена
    
    // Конструктор
    Radio(const std::string& m, const std::string& desc, double p)
        : model(m), description(desc), price(p) {}
    
    // Метод для вывода информации о магнитоле
    void print_info() const {
        std::cout << "Магнитола: " << model 
                  << " (" << description << ") - " 
                  << price << " руб." << std::endl;
    }
};

// КЛАСС АВТОМАСТЕРСКАЯ
class Garage {
private:
    std::string address_;                    // адрес мастерской
    std::vector<Radio> available_radios_;    // список доступных магнитол
    std::vector<Car*> attached_cars_;        // список указателей на машины
    
public:
    // КОНСТРУКТОРЫ (3 штуки)
    Garage();                                   // по умолчанию
    Garage(const std::string& address);         // с адресом
    Garage(const Garage& other);                // копирования
    
    // Деструктор
    ~Garage();
    
    // Оператор присваивания
    Garage& operator=(const Garage& other);
    
    // ГЕТТЕРЫ
    std::string get_address() const { return address_; }
    std::vector<Radio> get_available_radios() const { return available_radios_; }
    std::vector<Car*> get_attached_cars() const { return attached_cars_; }
    
    // СЕТТЕРЫ
    void set_address(const std::string& address) { address_ = address; }
    
    // МЕТОДЫ РАБОТЫ С МАГНИТОЛАМИ
    void add_radio(const Radio& radio);                    // добавить магнитолу
    void remove_radio(const std::string& model);           // удалить магнитолу
    
    // МЕТОДЫ РАБОТЫ С МАШИНАМИ
    void attach_car(Car* car);                             // прикрепить машину
    void detach_car(const std::string& license_plate);    // открепить машину
    Car* find_car(const std::string& license_plate);      // найти машину по номеру
    
    // МЕТОД ПРИКРУЧИВАНИЯ МАГНИТОЛЫ К МАШИНЕ
    bool install_radio_to_car(const std::string& license_plate, 
                              const std::string& radio_model);
    
    // МЕТОДЫ ДЛЯ ВЫВОДА ИНФОРМАЦИИ
    void print_info() const;
    void print_available_radios() const;
    void print_attached_cars() const;
};

} // namespace mt
