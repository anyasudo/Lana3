#include <iostream>
#include <locale>
#include "car.hpp"
#include "garage.hpp"

using namespace mt;

// Функция для вывода личной оценки лабораторной работы
void print_personal_assessment() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "     ЛИЧНАЯ ОЦЕНКА ЛАБОРАТОРНОЙ РАБОТЫ" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Интерес: 3/5" << std::endl;
    std::cout << std::endl;
    std::cout << "Наполненность: 5/5" << std::endl;
    std::cout << std::endl;
    std::cout << "Сложность: 5/5" << std::endl;
    std::cout << "=========================================\n" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Ru");  
    try {
        std::cout << "--- Создание автомобилей ---" << std::endl;
        Car car1("Toyota", "Camry", "123456789", "А123ВС", 50000, 
                 {"аптечка", "огнетушитель", "домкрат", "запаска"});
        Car car2("BMW", "X5", "987654321", "М456ОР", 30000, 
                 {"огнетушитель", "набор ключей", "аптечка", "буксировочный трос"});
        
        std::cout << "\ncar1: " << car1 << std::endl;
        std::cout << "car2: " << car2 << std::endl;
        
        std::cout << "\n--- Демонстрация геттеров ---" << std::endl;
        std::cout << "Марка car1: " << car1.get_brand() << std::endl;
        std::cout << "Модель car1: " << car1.get_model() << std::endl;
        std::cout << "Госномер car1: " << car1.get_license_plate() << std::endl;
        std::cout << "Пробег car1: " << car1.get_mileage() << " км" << std::endl;
        
        std::cout << "\n--- Демонстрация сеттеров ---" << std::endl;
        car1.set_body_number("NEW123456");
        try {
            car1.set_license_plate("Е789КХ");  // правильный номер
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
        std::cout << "\n--- Работа с пробегом ---" << std::endl;
        car1.drive(150);
        std::cout << "После поездки: пробег = " << car1.get_mileage() << " км" << std::endl;
        car1.rollback_mileage(50);
        std::cout << "После скручивания: пробег = " << car1.get_mileage() << " км" << std::endl;
        
        std::cout << "\n--- Работа с багажником ---" << std::endl;
        car1.add_to_trunk("канистра");
        car1.remove_from_trunk("аптечка");
        std::cout << "Текущий багажник car1: " << car1 << std::endl;
        
        std::cout << "\n--- Демонстрация операторов ---" << std::endl;
        Car car3 = car1 + car2;
        std::cout << "car1 + car2 = " << car3 << std::endl;
        
        Car car4 = car1 - car2;
        std::cout << "car1 - car2 = " << car4 << std::endl;
        
        Car car5 = car1 / car2;
        std::cout << "car1 / car2 = " << car5 << std::endl;
        
        std::cout << "\ncar1 == car2: " << (car1 == car2 ? "да" : "нет") << std::endl;
        
        std::cout << "\n\n********** ЧАСТЬ 2: ДЕМОНСТРАЦИЯ КЛАССА GARAGE **********\n" << std::endl;
        
        std::cout << "--- Создание автомастерской ---" << std::endl;
        Garage garage("ул. Ленина, д. 10");
        
        std::cout << "\n--- Добавление магнитол ---" << std::endl;
        garage.add_radio(Radio("Pioneer DEH-80", "CD/MP3-ресивер с Bluetooth", 15000));
        garage.add_radio(Radio("Sony MEX-XB", "Мощный усилитель встроен", 22000));
        garage.add_radio(Radio("Alpine UTE-73", "Цифровой медиа-ресивер", 18000));
        
        garage.print_available_radios();
        
        std::cout << "\n--- Прикрепление машин к мастерской ---" << std::endl;
        garage.attach_car(&car1);
        garage.attach_car(&car2);
        
        garage.print_attached_cars();
        
        std::cout << "\n--- Установка магнитол в машины ---" << std::endl;
        garage.install_radio_to_car("А123ВС", "Pioneer DEH-80");
        garage.install_radio_to_car("М456ОР", "Alpine UTE-73");
        
        // пробуем установить несуществующую магнитолу
        garage.install_radio_to_car("А123ВС", "JBL");
        
        // пробуем найти несуществующую машину
        garage.install_radio_to_car("Х999ХХ", "Pioneer DEH-80");
        
        std::cout << "\n--- Обновленная информация о машинах ---" << std::endl;
        std::cout << "\ncar1:" << std::endl;
        car1.print_info();
        std::cout << "\ncar2:" << std::endl;
        car2.print_info();
        
        std::cout << "\n--- Поиск машины по номеру ---" << std::endl;
        Car* found_car = garage.find_car("А123ВС");
        if (found_car) {
            std::cout << "Найдена машина: " << found_car->get_brand() 
                      << " " << found_car->get_model() << std::endl;
        }
        
        std::cout << "\n--- Удаление магнитолы ---" << std::endl;
        garage.remove_radio("Sony MEX-XB");
        garage.print_available_radios();
        
        std::cout << "\n--- Открепление машины ---" << std::endl;
        garage.detach_car("М456ОР");
        garage.print_attached_cars();
        
        std::cout << "\n--- Информация о мастерской ---" << std::endl;
        garage.print_info();
        
        std::cout << "--- Конструктор копирования Car ---" << std::endl;
        Car car6 = car1;  // конструктор копирования
        std::cout << "car6 (копия car1): " << car6 << std::endl;
        
        std::cout << "\n--- Оператор присваивания Car ---" << std::endl;
        Car car7;
        car7 = car2;  // оператор присваивания
        std::cout << "car7 (после присваивания car2): " << car7 << std::endl;
        
        std::cout << "\n--- Конструктор копирования Garage ---" << std::endl;
        Garage garage2 = garage;  // конструктор копирования
        std::cout << "garage2 (копия garage) создана" << std::endl;
        
        std::cout << "\n--- Оператор присваивания Garage ---" << std::endl;
        Garage garage3;
        garage3 = garage;  // оператор присваивания
        std::cout << "garage3 (после присваивания) создана" << std::endl;
        print_personal_assessment();
        
    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== КОНЕЦ ПРОГРАММЫ ===" << std::endl;
    return 0;
}
