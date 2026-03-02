#include "garage.hpp"
#include "car.hpp"

namespace mt {

// конструктор по умолчанию
Garage::Garage() : address_("Неизвестный адрес") {
    std::cout << "Создана автомастерская (конструктор по умолчанию)" << std::endl;
}

// конструктор с адресом
Garage::Garage(const std::string& address) : address_(address) {
    std::cout << "Создана автомастерская по адресу: " << address_ << std::endl;
}

// конструктор копирования
Garage::Garage(const Garage& other) 
    : address_(other.address_), 
      available_radios_(other.available_radios_),
      attached_cars_(other.attached_cars_) {
    std::cout << "Вызван конструктор копирования автомастерской" << std::endl;
}

// деструктор
Garage::~Garage() {
    std::cout << "Удаляется автомастерская по адресу: " << address_ << std::endl;
}

// оператор присваивания
Garage& Garage::operator=(const Garage& other) {
    std::cout << "Вызван оператор присваивания автомастерской" << std::endl;
    
    if (this != &other) {
        address_ = other.address_;
        available_radios_ = other.available_radios_;
        attached_cars_ = other.attached_cars_;
    }
    
    return *this;
}

// добавить магнитолу
void Garage::add_radio(const Radio& radio) {
    available_radios_.push_back(radio);
    std::cout << "Магнитола \"" << radio.model << "\" добавлена в мастерскую" << std::endl;
}

// удалить магнитолу
void Garage::remove_radio(const std::string& model) {
    auto it = std::find_if(available_radios_.begin(), available_radios_.end(),
        [&model](const Radio& r) { return r.model == model; });
    
    if (it != available_radios_.end()) {
        std::cout << "Магнитола \"" << it->model << "\" удалена из мастерской" << std::endl;
        available_radios_.erase(it);
    } else {
        std::cout << "Магнитола \"" << model << "\" не найдена" << std::endl;
    }
}

// прикрепить машину к мастерской
void Garage::attach_car(Car* car) {
    if (car == nullptr) {
        std::cout << "Ошибка: попытка прикрепить nullptr" << std::endl;
        return;
    }
    
    auto it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
        [car](Car* c) { return c->get_license_plate() == car->get_license_plate(); });
    
    if (it == attached_cars_.end()) {
        attached_cars_.push_back(car);
        std::cout << "Автомобиль " << car->get_brand() << " " << car->get_model()
                  << " (" << car->get_license_plate() << ") прикреплен к мастерской" << std::endl;
    } else {
        std::cout << "Автомобиль уже прикреплен к мастерской" << std::endl;
    }
}

// открепить машину от мастерской
void Garage::detach_car(const std::string& license_plate) {
    auto it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
        [&license_plate](Car* c) { return c->get_license_plate() == license_plate; });
    
    if (it != attached_cars_.end()) {
        std::cout << "Автомобиль " << (*it)->get_brand() << " " << (*it)->get_model()
                  << " (" << license_plate << ") откреплен от мастерской" << std::endl;
        attached_cars_.erase(it);
    } else {
        std::cout << "Автомобиль с номером " << license_plate << " не найден" << std::endl;
    }
}

// найти машину по госномеру
Car* Garage::find_car(const std::string& license_plate) {
    auto it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
        [&license_plate](Car* c) { return c->get_license_plate() == license_plate; });
    
    if (it != attached_cars_.end()) {
        return *it;
    }
    
    std::cout << "Автомобиль с номером " << license_plate << " не найден" << std::endl;
    return nullptr;
}

// метод прикручивания магнитолы к машине
bool Garage::install_radio_to_car(const std::string& license_plate, 
                                  const std::string& radio_model) {
    Car* car = find_car(license_plate);
    if (car == nullptr) {
        std::cout << "Не удалось установить магнитолу: машина не найдена" << std::endl;
        return false;
    }
    
    auto it = std::find_if(available_radios_.begin(), available_radios_.end(),
        [&radio_model](const Radio& r) { return r.model == radio_model; });
    
    if (it == available_radios_.end()) {
        std::cout << "Не удалось установить магнитолу: магнитола \"" 
                  << radio_model << "\" не найдена" << std::endl;
        return false;
    }
    
    car->set_radio(&(*it));
    std::cout << "Магнитола \"" << radio_model << "\" успешно установлена в автомобиль "
              << car->get_brand() << " " << car->get_model() 
              << " (" << license_plate << ")" << std::endl;
    
    return true;
}

void Garage::print_info() const {
    std::cout << "\n=== ИНФОРМАЦИЯ ОБ АВТОМАСТЕРСКОЙ ===" << std::endl;
    std::cout << "Адрес: " << address_ << std::endl;
    std::cout << "Доступных магнитол: " << available_radios_.size() << std::endl;
    std::cout << "Прикрепленных автомобилей: " << attached_cars_.size() << std::endl;
    std::cout << "=====================================\n" << std::endl;
}

void Garage::print_available_radios() const {
    std::cout << "\n--- Доступные магнитолы (" << available_radios_.size() << ") ---" << std::endl;
    if (available_radios_.empty()) {
        std::cout << "Нет доступных магнитол" << std::endl;
    } else {
        for (size_t i = 0; i < available_radios_.size(); ++i) {
            std::cout << i + 1 << ". ";
            available_radios_[i].print_info();
        }
    }
    std::cout << "-------------------------------------\n" << std::endl;
}

void Garage::print_attached_cars() const {
    std::cout << "\n--- Прикрепленные автомобили (" << attached_cars_.size() << ") ---" << std::endl;
    if (attached_cars_.empty()) {
        std::cout << "Нет прикрепленных автомобилей" << std::endl;
    } else {
        for (size_t i = 0; i < attached_cars_.size(); ++i) {
            std::cout << i + 1 << ". ";
            attached_cars_[i]->print_info();
        }
    }
    std::cout << "-----------------------------------------\n" << std::endl;
}

} // namespace mt
