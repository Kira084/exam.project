#include <format>
#include "ArrayTemplate.h"
#include "TasksMenuLib.h"
#include <iostream>
using namespace std;

int main()
{

        loadDishes();
        loadOrders();
        runMenu();
        saveDishes();
        saveOrders();
    return 0;
}

