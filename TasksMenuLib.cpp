#include "TasksMenuLib.h"
#include <cstdlib>
#include "ArrayTemplate.h"
#include <format>
#include <iostream>
using namespace std;



Dish* menu = nullptr;  
int dishCount = 0;    //number dishes


Order* orders = nullptr;   
int orderCount = 0;         // number orders


    void runMenu() {
        int choice;
        do {
            
            cout << "\n\n<:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::>\n";
            cout << "\t\t\t   CANTEEN MANAGEMENT\n";
            cout << "\n";
            cout << "\t\t   1 - Show dishes\n";
            cout << "\t\t   2 - Add dish\n";
            cout << "\t\t   3 - Remove dish\n";
            cout << "\t\t   4 - Edit dish\n";
            cout << "\t\t   5 - Show orders\n";
            cout << "\t\t   6 - Add order\n";
            cout << "\t\t   7 - Remove order\n";
            cout << "\t\t   8 - Edit order\n";
            cout << "\t\t   9 - Total by date\n";
            cout << "\t\t  10 - Sort dishes\n";
            cout << "\t\t  11 - Sort orders\n";
            cout << "\t\t   0 - Exit\n";
            cout << "\n";
            cout << "\t\t\t\t\t\t   Choose option: "; cin >> choice;

            
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #else
                system("clear");
            #endif
                           
            
          
            
            
            cout << "\n";

            switch (choice) {
            case 1: showDishes(); break;
            case 2: addDish(); break;
            case 3: removeDish(); break;
            case 4: editDish(); break;
            case 5: showOrders(); break;
            case 6: addOrder(); break;
            case 7: removeOrder(); break;
            case 8: editOrder(); break;
            case 9: totalByDate(); break;
            case 10: sortDishes(); break;
            case 11: sortOrders(); break;
            case 12: {
                showDishes();
                addOrder();
                break;
            }
            case 0: cout << "\tEnd\n"; break;
            default: cout << "\n\tThere's no such a task\n";
            
            }
        } while (choice != 0);
    }

    //===========================================================================

    //=================== functions of exam.pj ===================>>

    void showDishes() {
        cout << "\tShow all dishes\n";
       
            if (dishCount == 0) {
                cout << format("No dishes yet.\n");
                return;
            }
            cout << format("{:<30} {:<20} {:<10}\n", "Name", "Type", "Price");
            cout << format("{}\n", string(60, '-'));
            for (int i = 0; i < dishCount; i++) {
                cout << format("{:<30} {:<20} {:<10.2f}\n",
                    menu[i].name, menu[i].type, menu[i].price);
            }
        }

    //===========================================================================

    void addDish() {
        cout << "\tAdd new dish\n";
        Dish newDish;

        cout << format("Name: ");
        cin.ignore();
        getline(cin, newDish.name);

        cout << format("Type (soup, main, drink...): ");
        getline(cin, newDish.type);

        cout << format("Price: ");
        cin >> newDish.price;

        addItemBack(menu, dishCount, newDish);
        cout << format("\nDish added successfully!\n");
    }
    //===========================================================================


    void removeDish() {
        cout << "\tRemove dish\n";
       
            if (dishCount == 0) {
                cout << format("No dishes to remove.\n");
                return;
            }

            string name;
            cout << format("Enter dish name to remove: ");
            cin.ignore();
            getline(cin, name);

            // index
            int idx = -1;
            for (int i = 0; i < dishCount; i++) {
                if (menu[i].name == name) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                cout << format("Dish '{}' not found.\n", name);
                return;
            }

            //new array without that element
            Dish* tmp = new Dish[dishCount - 1];
            for (int i = 0, j = 0; i < dishCount; i++) {
                if (i != idx) tmp[j++] = menu[i];
            }
            delete[] menu;
            menu = tmp;
            dishCount--;

            cout << format("Dish '{}' removed.\n", name);
        }
    

    //===========================================================================


    void editDish() {
        cout << "\tEdit dish\n";
   
            if (dishCount == 0) {
                cout << format("No dishes to edit.\n");
                return;
            }

            string name;
            cout << format("Enter dish name to edit: ");
            cin.ignore();
            getline(cin, name);

            int idx = -1;
            for (int i = 0; i < dishCount; i++) {
                if (menu[i].name == name) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                cout << format("Dish '{}' not found.\n", name);
                return;
            }

            cout << format("Current name: {}\n", menu[idx].name);
            cout << format("New name (leave empty to keep): ");
            string newName;
            getline(cin, newName);
            if (!newName.empty()) menu[idx].name = newName;

            cout << format("Current type: {}\n", menu[idx].type);
            cout << format("New type: ");
            string newType;
            getline(cin, newType);
            if (!newType.empty()) menu[idx].type = newType;

            cout << format("Current price: {:.2f}\n", menu[idx].price);
            cout << format("New price: ");
            string newPriceStr;
            getline(cin, newPriceStr);
            if (!newPriceStr.empty()) menu[idx].price = stod(newPriceStr);

            cout << format("Dish updated.\n");
        }
    

    //===========================================================================


    void showOrders() {
        cout << "\tShow all orders\n";
        
            if (orderCount == 0) {
                cout << format("No orders yet.\n");
                return;
            }
            cout << format("{:<25} {:<25} {:<12} {:<8}\n",
                "Student", "Dish", "Date", "Qty");
            cout << format("{}\n", string(70, '-'));
            for (int i = 0; i < orderCount; i++) {
                cout << format("{:<25} {:<25} {:<12} {:<8}\n",
                    orders[i].student, orders[i].dishName,
                    orders[i].date, orders[i].qty);
            }
        }
    

    //===========================================================================


    void addOrder() {
        cout << "\tAdd new order\n";
       
      
            if (dishCount == 0) {
                cout << format("No dishes in menu. Add a dish first.\n");
                return;
            }

            //menu with numbers
            cout << format("Choose dish:\n");
            for (int i = 0; i < dishCount; i++) {
                cout << format("{} - {} ({} UAH)\n", i + 1, menu[i].name, menu[i].price);
            }
            cout << format("Enter dish number: ");
            int choice;
            cin >> choice;
            if (choice < 1 || choice > dishCount) {
                cout << format("Invalid choice.\n");
                return;
            }
            Dish& selected = menu[choice - 1];

            Order newOrder;
            cout << format("Student name: ");
            cin.ignore();
            getline(cin, newOrder.student);
            newOrder.dishName = selected.name;
            cout << format("Date (YYYY-MM-DD): ");
            getline(cin, newOrder.date);
            cout << format("Quantity: ");
            cin >> newOrder.qty;

            addItemBack(orders, orderCount, newOrder);

            double total = selected.price * newOrder.qty;
            cout << format("\nOrder added! Total: {:.2f} UAH\n", total);
        }
    

    //===========================================================================


    void removeOrder() {
        cout << "\tRemove order\n";
        
            if (orderCount == 0) {
                cout << format("No orders to remove.\n");
                return;
            }

            string student, dish, date;
            cout << format("Enter student name: ");
            cin.ignore();
            getline(cin, student);
            cout << format("Enter dish name: ");
            getline(cin, dish);
            cout << format("Enter date (YYYY-MM-DD): ");
            getline(cin, date);

            int idx = -1;
            for (int i = 0; i < orderCount; i++) {
                if (orders[i].student == student &&
                    orders[i].dishName == dish &&
                    orders[i].date == date) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                cout << format("Order not found.\n");
                return;
            }

            // without that order
            Order* tmp = new Order[orderCount - 1];
            for (int i = 0, j = 0; i < orderCount; i++) {
                if (i != idx) tmp[j++] = orders[i];
            }
            delete[] orders;
            orders = tmp;
            orderCount--;

            cout << format("Order removed.\n");
        }
    

    //===========================================================================


    void editOrder() {
        cout << "\tEdit order\n";
        
            if (orderCount == 0) {
                cout << format("No orders to edit.\n");
                return;
            }

            string student, dish, date;
            cout << format("Enter student name: ");
            cin.ignore();
            getline(cin, student);
            cout << format("Enter dish name: ");
            getline(cin, dish);
            cout << format("Enter date (YYYY-MM-DD): ");
            getline(cin, date);

            int idx = -1;
            for (int i = 0; i < orderCount; i++) {
                if (orders[i].student == student &&
                    orders[i].dishName == dish &&
                    orders[i].date == date) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                cout << format("Order not found.\n");
                return;
            }

            cout << format("Current student: {}\n", orders[idx].student);
            cout << format("New student (leave empty to keep): ");
            string newStudent;
            getline(cin, newStudent);
            if (!newStudent.empty()) orders[idx].student = newStudent;

            cout << format("Current dish: {}\n", orders[idx].dishName);
            cout << format("New dish: ");
            string newDish;
            getline(cin, newDish);
            if (!newDish.empty()) {

                // checkin if there is a new dish

                bool found = false;
                for (int i = 0; i < dishCount; i++) {
                    if (menu[i].name == newDish) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << format("Dish '{}' not found. Keeping old dish.\n", newDish);
                }
                else {
                    orders[idx].dishName = newDish;
                }
            }

            cout << format("Current date: {}\n", orders[idx].date);
            cout << format("New date: ");
            string newDate;
            getline(cin, newDate);
            if (!newDate.empty()) orders[idx].date = newDate;

            cout << format("Current quantity: {}\n", orders[idx].qty);
            cout << format("New quantity: ");
            string newQtyStr;
            getline(cin, newQtyStr);
            if (!newQtyStr.empty()) orders[idx].qty = stoi(newQtyStr);

            cout << format("Order updated.\n");
        
    }

    //===========================================================================


    void totalByDate() {
        cout << "\tTotal by date\n";
       
            if (orderCount == 0) {
                cout << format("No orders.\n");
                return;
            }

            string date;
            cout << format("Enter date (YYYY-MM-DD): ");
            cin.ignore();
            getline(cin, date);

            double total = 0;
            for (int i = 0; i < orderCount; i++) {
                if (orders[i].date == date) {

                    // dish pricze

                    for (int j = 0; j < dishCount; j++) {
                        if (menu[j].name == orders[i].dishName) {
                            total += menu[j].price * orders[i].qty;
                            break;
                        }
                    }
                }
            }

            cout << format("Total for {}: {:.2f} UAH\n", date, total);
        }
    

    //===========================================================================


    void sortDishes() {
        cout << "\tSort dishes\n";
        
            if (dishCount == 0) {
                cout << format("No dishes to sort.\n");
                return;
            }

            cout << format("Sort by:\n1 - Name\n2 - Type\n3 - Price\nChoice: ");
            int opt;
            cin >> opt;

            if (opt == 1) {

                //sorting by name

                for (int i = 0; i < dishCount - 1; i++) {
                    for (int j = i + 1; j < dishCount; j++) {
                        if (menu[i].name > menu[j].name) {
                            swap(menu[i], menu[j]);
                        }
                    }
                }
                cout << format("Dishes sorted by name.\n");
            }
            else if (opt == 2) {

                // sorting by type
                for (int i = 0; i < dishCount - 1; i++) {
                    for (int j = i + 1; j < dishCount; j++) {
                        if (menu[i].type > menu[j].type) {
                            swap(menu[i], menu[j]);
                        }
                    }
                }
                cout << format("Dishes sorted by type.\n");
            }
            else if (opt == 3) {

                // by price

                for (int i = 0; i < dishCount - 1; i++) {
                    for (int j = i + 1; j < dishCount; j++) {
                        if (menu[i].price > menu[j].price) {
                            swap(menu[i], menu[j]);
                        }
                    }
                }
                cout << format("Dishes sorted by price.\n");
            }
            else {
                cout << format("Invalid option.\n");
                return;
            }

            // sorted dishes showin
            showDishes();
        }
    

    //===========================================================================


    void sortOrders() {
        cout << "\tSort orders\n";
        
            if (orderCount == 0) {
                cout << format("No orders to sort.\n");
                return;
            }

            cout << format("Sort by:\n1 - Student name\n2 - Dish name\n3 - Date\n4 - Quantity\nChoice: ");
            int opt;
            cin >> opt;

            if (opt == 1) {

                // sort by students name
                for (int i = 0; i < orderCount - 1; i++) {
                    for (int j = i + 1; j < orderCount; j++) {
                        if (orders[i].student > orders[j].student) {
                            swap(orders[i], orders[j]);
                        }
                    }
                }
                cout << format("Orders sorted by student name.\n");
            }
            else if (opt == 2) {

                // by dishe's name
                for (int i = 0; i < orderCount - 1; i++) {
                    for (int j = i + 1; j < orderCount; j++) {
                        if (orders[i].dishName > orders[j].dishName) {
                            swap(orders[i], orders[j]);
                        }
                    }
                }
                cout << format("Orders sorted by dish name.\n");
            }
            else if (opt == 3) {

                // by date
                for (int i = 0; i < orderCount - 1; i++) {
                    for (int j = i + 1; j < orderCount; j++) {
                        if (orders[i].date > orders[j].date) {
                            swap(orders[i], orders[j]);
                        }
                    }
                }
                cout << format("Orders sorted by date.\n");
            }
            else if (opt == 4) {

                // by number of orders
                for (int i = 0; i < orderCount - 1; i++) {
                    for (int j = i + 1; j < orderCount; j++) {
                        if (orders[i].qty > orders[j].qty) {
                            swap(orders[i], orders[j]);
                        }
                    }
                }
                cout << format("Orders sorted by quantity.\n");
            }
            else {
                cout << format("Invalid option.\n");
                return;
            }

            // sort orders
            showOrders();
        }
    

    //===========================================================================


    const char* DISH_FILE = "dishes.bin";
    const char* ORDER_FILE = "orders.bin";

    void saveDishes() {
        FILE* f = nullptr;
        fopen_s(&f, DISH_FILE, "wb");
        if (f) {
            fwrite(&dishCount, sizeof(int), 1, f);
            fwrite(menu, sizeof(Dish), dishCount, f);
            fclose(f);
            cout << format("Dishes saved.\n");
        }
        else {
            cout << format("Error saving dishes.\n");
        }
    }

    void loadDishes() {
        FILE* f = nullptr;
        fopen_s(&f, DISH_FILE, "rb");
        if (f) {
            fread(&dishCount, sizeof(int), 1, f);
            if (menu) delete[] menu;
            menu = new Dish[dishCount];
            fread(menu, sizeof(Dish), dishCount, f);
            fclose(f);
            cout << format("Dishes loaded.\n");
        }
        else {
            cout << format("No saved dishes found.\n");
        }
    }

    //===========================================================================

    void saveOrders() {
        FILE* f = nullptr;
        fopen_s(&f, ORDER_FILE, "wb");
        if (f) {
            fwrite(&orderCount, sizeof(int), 1, f);
            fwrite(orders, sizeof(Order), orderCount, f);
            fclose(f);
            cout << format("Orders saved.\n");
        }
        else {
            cout << format("Error saving orders.\n");
        }
    }

    void loadOrders() {
        FILE* f = nullptr;
        fopen_s(&f, ORDER_FILE, "rb");
        if (f) {
            fread(&orderCount, sizeof(int), 1, f);
            if (orders) delete[] orders;
            orders = new Order[orderCount];
            fread(orders, sizeof(Order), orderCount, f);
            fclose(f);
            cout << format("Orders loaded\n");
        }
        else {
            cout << format("No saved orders found\n");
        }
    }