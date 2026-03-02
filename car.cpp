#include "car.hpp"
#include "garage.hpp"

namespace mt {

// проверка гос номера
bool Car::check_license_format_(const std::string& plate) const {
    if (plate.length() != 6) {
        return false;
    }

    std::string allowed_letters = "АВЕКМНОРСТУХ";

    // первый символ должен быть буква из списка
    bool first_ok = false;
    for (char letter : allowed_letters) {
        if (plate[0] == letter) {
            first_ok = true;
            break;
        }
    }

    // 2-4 символы должны быть цифры
    bool digits_ok = true;
    for (int i = 1; i <= 3; i++) {
        if (plate[i] < '0' || plate[i] > '9') {
            digits_ok = false;
            break;
        }
    }

    // 5-6 символы должны быть буквы из списка
    bool last_ok = false;
    for (char letter1 : allowed_letters) {
        for (char letter2 : allowed_letters) {
            if (plate[4] == letter1 && plate[5] == letter2) {
                last_ok = true;
                break;
            }
        }
        if (last_ok) break;
    }

    return first_ok && digits_ok && last_ok;
}

// генерация случайного госномера
std::string Car::generate_random_plate_() const {
    static const std::string letters = "АВЕКМНОРСТУХ";
    static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    static std::uniform_int_distribution<int> letter_dist(0, static_cast<int>(letters.size()) - 1);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    
    std::string plate;
    
    do {
        plate.clear();
        plate += letters[letter_dist(rng)];
        plate += std::to_string(digit_dist(rng));
        plate += std::to_string(digit_dist(rng));
        plate += std::to_string(digit_dist(rng));
        plate += letters[letter_dist(rng)];
        plate += letters[letter_dist(rng)];
    } while (!check_license_format_(plate));
    
    return plate;
}

// вспомогательный метод для группировки повторов
void Car::group_duplicates_(std::vector<std::string>& items) const {
    if (items.empty()) return;
    std::sort(items.begin(), items.end());
}

// конструктор по умолчанию
Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
    body_number_("000000"), license_plate_("А000АА"),
    mileage_(0), radio_(nullptr) {
    
    trunk_items_ = new std::vector<std::string>();
    std::cerr << "Вызван конструктор по умолчанию" << std::endl;
}

// конструктор полного заполнения
Car::Car(const std::string& brand, const std::string& model,
    const std::string& body_number, const std::string& license_plate,
    int mileage, const std::vector<std::string>& trunk_items) :
    brand_(brand), model_(model), body_number_(body_number),
    license_plate_(license_plate), mileage_(mileage), radio_(nullptr) {
    
    if (!is_mileage_valid_(mileage)) {
        throw std::invalid_argument("Пробег должен быть неотрицательным");
    }

    if (!check_license_format_(license_plate)) {
        throw std::invalid_argument(
            "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
            "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
            "Пример: А123ВС, М456ОР, Х789ТУ");
    }
    
    trunk_items_ = new std::vector<std::string>(trunk_items);
    
    std::cerr << "Вызван конструктор с параметрами" << std::endl;
}

// конструктор копирования
Car::Car(const Car& other) :
    brand_(other.brand_), model_(other.model_),
    body_number_(other.body_number_),
    license_plate_(other.license_plate_),
    mileage_(other.mileage_), radio_(other.radio_) {
    
    trunk_items_ = new std::vector<std::string>(*other.trunk_items_);
    
    std::cerr << "Вызван конструктор копирования" << std::endl;
}

// оператор присваивания
Car& Car::operator=(const Car& other) {
    std::cerr << "Вызван оператор присваивания" << std::endl;
    
    if (this != &other) {
        brand_ = other.brand_;
        model_ = other.model_;
        body_number_ = other.body_number_;
        license_plate_ = other.license_plate_;
        mileage_ = other.mileage_;
        radio_ = other.radio_;
        
        delete trunk_items_;
        trunk_items_ = new std::vector<std::string>(*other.trunk_items_);
    }
    
    return *this;
}

// деструктор
Car::~Car() {
    if (trunk_items_ != nullptr) {
        trunk_items_->clear();
        std::cerr << "Вектор вещей опустошен. Размер: " << trunk_items_->size() << std::endl;
        
        delete trunk_items_;
        std::cerr << "Память вектора вещей освобождена" << std::endl;
    }
    
    std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
}

// сеттер для номера кузова
void Car::set_body_number(const std::string& body_number) {
    body_number_ = body_number;
}

// сеттер для гос. номера с проверкой
void Car::set_license_plate(const std::string& license_plate) {
    if (!check_license_format_(license_plate)) {
        throw std::invalid_argument(
            "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
            "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
            "Пример: А123ВС, М456ОР, Х789ТУ");
    }

    license_plate_ = license_plate;
    std::cout << "Гос. номер успешно изменен на: " << license_plate_ << std::endl;
}

// метод для установки магнитолы
void Car::set_radio(Radio* radio) {
    radio_ = radio;
    if (radio_ != nullptr) {
        std::cout << "Магнитола \"" << radio_->model << "\" установлена в автомобиль "
                  << brand_ << " " << model_ << std::endl;
    } else {
        std::cout << "Магнитола удалена из автомобиля" << std::endl;
    }
}

// метод для вывода всей информации
void Car::print_info() const {
    std::cout << "=== Информация об автомобиле ===" << std::endl;
    std::cout << "Марка: " << brand_ << std::endl;
    std::cout << "Модель: " << model_ << std::endl;
    std::cout << "Номер кузова: " << body_number_ << std::endl;
    std::cout << "Гос. номер: " << license_plate_ << std::endl;
    std::cout << "Пробег: " << mileage_ << " км" << std::endl;
    
    // Информация о магнитоле
    std::cout << "Магнитола: ";
    if (radio_ != nullptr) {
        std::cout << radio_->model << " (" << radio_->description 
                  << ") - " << radio_->price << " руб." << std::endl;
    } else {
        std::cout << "не установлена" << std::endl;
    }
    
    // Информация о вещах в багажнике
    std::cout << "Вещи в багажнике (" << trunk_items_->size() << "): ";
    if (trunk_items_->empty()) {
        std::cout << "багажник пуст";
    } else {
        for (size_t i = 0; i < trunk_items_->size(); ++i) {
            std::cout << (*trunk_items_)[i];
            if (i < trunk_items_->size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl << "================================" << std::endl;
}

// метод для скручивания пробега на X
void Car::rollback_mileage(int x) {
    if (x < 0) {
        throw std::invalid_argument("Значение скручивания должно быть неотрицательным");
    }

    if (mileage_ - x < 0) {
        throw std::invalid_argument("Нельзя скрутить больше, чем текущий пробег");
    }

    mileage_ -= x;
    std::cout << "Пробег уменьшен на " << x << " км" << std::endl;
}

// метод для увеличения пробега
void Car::drive(int distance) {
    if (distance < 0) {
        throw std::invalid_argument("Расстояние должно быть неотрицательным");
    }
    mileage_ += distance;
    std::cout << "Автомобиль проехал " << distance << " км" << std::endl;
}

// метод для добавления вещей в багажник
void Car::add_to_trunk(const std::string& item) {
    trunk_items_->push_back(item);
    std::cout << "Добавлено в багажник: " << item << std::endl;
}

// метод для удаления вещей из багажника
void Car::remove_from_trunk(const std::string& item) {
    auto it = std::find(trunk_items_->begin(), trunk_items_->end(), item);
    if (it != trunk_items_->end()) {
        trunk_items_->erase(it);
        std::cout << "Удалено из багажника: " << item << std::endl;
    } else {
        std::cout << "Предмет " << item << " не найден в багажнике" << std::endl;
    }
}

// ОПЕРАТОР +
Car Car::operator+(const Car& other) const {
    std::cout << "Выполняется оператор +" << std::endl;
    
    Car result;
    result.brand_ = this->brand_;
    result.model_ = this->model_;
    result.body_number_ = this->body_number_;
    result.license_plate_ = generate_random_plate_();
    result.mileage_ = 0;
    
    delete result.trunk_items_;
    result.trunk_items_ = new std::vector<std::string>(*this->trunk_items_);
    result.trunk_items_->insert(result.trunk_items_->end(), 
                               other.trunk_items_->begin(), 
                               other.trunk_items_->end());
    
    group_duplicates_(*result.trunk_items_);
    
    return result;
}

// ОПЕРАТОР -
Car Car::operator-(const Car& other) const {
    std::cout << "Выполняется оператор -" << std::endl;
    
    Car result;
    result.brand_ = this->brand_;
    result.model_ = this->model_;
    result.body_number_ = this->body_number_;
    result.license_plate_ = generate_random_plate_();
    result.mileage_ = 0;
    
    delete result.trunk_items_;
    result.trunk_items_ = new std::vector<std::string>();
    
    std::vector<std::string> all_items = *this->trunk_items_;
    all_items.insert(all_items.end(), other.trunk_items_->begin(), other.trunk_items_->end());
    
    std::sort(all_items.begin(), all_items.end());
    auto last = std::unique(all_items.begin(), all_items.end());
    all_items.erase(last, all_items.end());
    
    *result.trunk_items_ = all_items;
    
    return result;
}

// ОПЕРАТОР /
Car Car::operator/(const Car& other) const {
    std::cout << "Выполняется оператор /" << std::endl;
    
    Car result;
    result.brand_ = other.brand_;
    result.model_ = other.model_;
    result.body_number_ = other.body_number_;
    result.license_plate_ = generate_random_plate_();
    result.mileage_ = 0;
    
    delete result.trunk_items_;
    result.trunk_items_ = new std::vector<std::string>();
    
    for (const auto& item1 : *this->trunk_items_) {
        for (const auto& item2 : *other.trunk_items_) {
            if (item1 == item2) {
                if (std::find(result.trunk_items_->begin(), 
                             result.trunk_items_->end(), item1) 
                    == result.trunk_items_->end()) {
                    result.trunk_items_->push_back(item1);
                }
                break;
            }
        }
    }
    
    return result;
}

// оператор сравнения ==
bool Car::operator==(const Car& other) const {
    return license_plate_ == other.license_plate_;
}

// оператор сравнения !=
bool Car::operator!=(const Car& other) const {
    return !(*this == other);
}

// оператор вывода в поток
std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << "[" << car.brand_ << "," << car.license_plate_ << ",(";
    
    if (car.trunk_items_->empty()) {
        os << "пусто";
    } else {
        for (size_t i = 0; i < car.trunk_items_->size(); ++i) {
            os << (*car.trunk_items_)[i];
            if (i < car.trunk_items_->size() - 1) {
                os << ",";
            }
        }
    }
    
    os << ")]";
    return os;
}

} // namespace mt
