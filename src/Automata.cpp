//"Copyright 2025 Owner"
#include "Automata.h"
#include <string>
#include <vector>
#include <iostream>

Automata::Automata() {
    cash = 0;
    state = OFF;
    currChoice = -1;
    menu = { "Черный чай", "Зеленый чай", "Кофе" };
    price = { 10, 15, 40 };
}
void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "Автомат в режиме ожидания." << std::endl;
    }
}
void Automata::off() {
    state = OFF;
    cash = 0;
    std::cout << "Aвтомат отключен." << std::endl;
}
void Automata::coin(int coin) {
    if (state == WAIT || state == ACCEPT) {
        cash += coin;
        state = ACCEPT;
        std::cout << "Внесено: " << coin 
            << " Текущий баланс: "
            << cash << std::endl;
    }
}
void Automata::getMenu() {
    std::cout << "Меню:" << std::endl;
    for (int i = 0; i < menu.size(); i++) {
        std::cout << menu[i] << " - " 
            << price[i] 
            << std::endl;
    }
}
STATES Automata::getState() {
    return state;
}
void Automata::choice(int choice) {
    if (state == ACCEPT || state == WAIT) {
        if (choice > 0 && choice <= menu.size()) {
            std::cout << "Выбрано: " << menu[choice] << std::endl;
            currChoice = choice;
            state = CHECK;
        } else {
            std::cout << "Некорректный индекс." << std::endl;
        }
    } else {
        std::cout << "Ошибка состояния" << std::endl;
    }
}
void Automata::check() {
    if (state == CHECK) {
        if (cash >= price[currChoice]) {
            std::cout << "Успешно, старт приготовления" << std::endl;
        } else {
            std::cout << "Недостаточно средств" << std::endl;
        }
    } else {
        std::cout << "Ошибка состояния" << std::endl;
    }
}
void Automata::cancel() {
    if (state == CHECK || state == ACCEPT) {
        state = WAIT;
        std::cout << "Отмена, средства возвращены" << std::endl;
        cash = 0;
    } else {
        std::cout << "Ошибка состояния" << std::endl;
    }
}
void Automata::cook() {
    if (state == CHECK) {
        state = COOK;
        std::cout << "Приготовление" << std::endl;
    } else {
        std::cout << "Ошибка состояния" << std::endl;
    }
}
void Automata::finish() {
    if (state == COOK) {
        state = WAIT;
        std::cout << "Приготовление завершено" << std::endl;
        if (cash > price[currChoice]) {
            std::cout << "Сдача: " << cash - price[currChoice] << std::endl;
        }
        cash = 0;
        currChoice = -1;
    } else {
        std::cout << "Ошибка состояния" << std::endl;
    }
}
