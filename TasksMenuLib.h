#pragma once

#include <string>
using namespace std;

struct Dish {
    string name;
    string type;
    double price = 0.0;
};

struct Order {
    string student;
    string dishName;
    string date;
    int qty = 0;
};

extern Dish* menu;
extern int dishCount;
extern Order* orders;
extern int orderCount;


//dishes
void showDishes();
void addDish();
void removeDish();
void editDish();

//orders
void showOrders();
void addOrder();
void removeOrder();
void editOrder();

//additional functions
void totalByDate();
void sortDishes();
void sortOrders();



void saveDishes();
void loadDishes();
void saveOrders();
void loadOrders();

void runMenu();