#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdexcept>
using namespace std;
class MenuItem {
    public:
    int id;
    string name;
    double price;
    MenuItem(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};
class Menu {
    protected:
    vector<MenuItem> tiffins;
    vector<MenuItem> meals;
    vector<MenuItem> beverages;
    public:
    Menu() {
        tiffins.emplace_back(1, "Idly", 20);
        tiffins.emplace_back(2, "Dosa", 30);
        tiffins.emplace_back(3, "Puri", 30);
        tiffins.emplace_back(4, "Vada", 25);
        tiffins.emplace_back(5, "Bonda", 20);
        tiffins.emplace_back(6, "Chapathi", 40);
        meals.emplace_back(7, "Chicken Biryani (Mini)", 180);
        meals.emplace_back(8, "Chicken Biryani (Large)", 250);
        meals.emplace_back(9, "Mutton Biryani (Mini)", 300);
        meals.emplace_back(10, "Mutton Biryani (Large)", 350);
        meals.emplace_back(11, "Veg Biryani (Mini)", 150);
        meals.emplace_back(12, "Veg Biryani (Large)", 200);
        meals.emplace_back(13, "Veg Meals", 120);
        beverages.emplace_back(14, "Tea", 10);
        beverages.emplace_back(15, "Green Tea", 30);
        beverages.emplace_back(16, "Ginger Tea", 20);
        beverages.emplace_back(17, "Thumsup (250 ml)", 30);
        beverages.emplace_back(18, "Sting (250 ml)", 30);
        beverages.emplace_back(19, "Coke (250 ml)", 30);
        beverages.emplace_back(20, "Sprite (250 ml)", 30);
    }
    void display_menu() {
        cout << "\n*Menu*\n";
        cout << "\n*Tiffins*\n";
        for (const auto& item : tiffins) {
            cout << item.id << " " << item.name << " --> Rs." << item.price << endl;
        }
        cout << "\n*Meals*\n";
        for (const auto& item : meals) {
            cout << item.id << " " << item.name << " --> Rs." << item.price << endl;
        }
        cout << "\n*Beverages*\n";
        for (const auto& item : beverages) {
            cout << item.id << " " << item.name << " --> Rs." << item.price << endl;
        }
    }
    MenuItem getitem(int choice) {
        for (const auto& item : tiffins) {
            if (item.id == choice) return item;
        }
        for (const auto& item : meals) {
            if (item.id == choice) return item;
        }
        for (const auto& item : beverages) {
            if (item.id == choice) return item;
        }
        throw invalid_argument("Item not found in menu. Please select a valid item.");
    }
};
class Order : public Menu {
    private:
    vector<pair<MenuItem, int>> ordered_items;
    double total_amount = 0;
    bool completed = false;
    public:
    void add_item(const MenuItem& item, int quantity) {
        bool item_already_exists = false;
        for (auto& it : ordered_items) {
            if (it.first.id == item.id) {
                it.second += quantity;
                total_amount += item.price * quantity;
                item_already_exists = true;
                break;
            }
        }
        if (!item_already_exists) {
            ordered_items.emplace_back(item, quantity);
            total_amount += item.price * quantity;
        }
    }
    void cancel_itemsinorder(int itemid) {
        for (auto it = ordered_items.begin(); it != ordered_items.end(); it++) {
            if (it->first.id == itemid) {
                total_amount -= it->first.price * it->second;
                cout << it->first.name << " has been cancelled." << endl;
                ordered_items.erase(it);
                displayOrder();
                return;
            }
        }
        cout << "Item not found in your order." << endl;
    }
    void take_order() {
        display_menu();
        int choice, quantity;
        char ch;
        do {
            bool valid_item = false;
            while (!valid_item) {
                cout << "\nEnter the item number to order: ";
                cin >> choice;
                try {
                    MenuItem item = getitem(choice);
                    valid_item = true;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    add_item(item, quantity);
                }
                catch (const exception& e) {
                    cout << e.what() << endl;
                    cout << "Please try again with a valid item number.\n";
                }
            }
            cout << "Item has been successfully added. Would you like to order another item? (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
        displayOrder();
    }
    void process_payment() {
        cout << "Please pay the payment using any UPI methods." << endl;
        cout << "Redirecting to payment...." << endl;
        sleep(5);
        cout << "Payment Successful" << endl;
    }
    void displayOrder() const {
        cout << "\nOrder Details:\n";
        for (const auto& item : ordered_items) {
            cout << item.first.name << " x " << item.second << " - Rs." << item.first.price*item.second << endl;
        }
        cout << "Total Amount: Rs." << total_amount << endl;
        cout << "Status: " << (completed ? "Completed" : "Pending") << endl;
    }
    void update_completion_status() {
        completed = true;
    }
    bool iscompleted() const {
        return completed;
    }
};
class Table {
    public:
    int table_number;
    bool reserved;
    Table(int number) {
        table_number = number;
        reserved = false;
    }
};
class TableManager {
    private:
    vector<Table> tables;
    static TableManager* instance;
    TableManager() {
        for (int i = 1; i <= 20; ++i) {
            tables.emplace_back(i);
        }
    }
    public:
    static TableManager* getInstance() {
        if (instance == nullptr) {
            instance = new TableManager();
        }
        return instance;
    }
    bool reserve_table(int table_number) {
        if (table_number < 1 || table_number > 20) {
            cout << "Invalid table number. Please select a number between 1 and 20." << endl;
            return false;
        }
        if (tables[table_number - 1].reserved) {
            cout << "Table " << table_number << " is already reserved." << endl;
            return false;
        }
        else {
            tables[table_number - 1].reserved = true;
            cout << "Table " << table_number << " has been reserved successfully." << endl;
            return true;
        }
    }
    bool cancel_reservation(int table_number) {
        if (table_number < 1 || table_number > 20) {
            cout << "Invalid table number. Please select a number between 1 and 20." << endl;
            return false;
        }
        if (!tables[table_number - 1].reserved) {
            cout << "Table " << table_number << " is not reserved." << endl;
            return false;
        }
        else {
            tables[table_number - 1].reserved = false;
            cout << "Table " << table_number << " reservation has been cancelled." << endl;
            return true;
        }
    }
};
TableManager* TableManager::instance = nullptr;
class User : public Menu {
    private:
    string name;
    long long phonenumber;
    string address;
    Order order;
    int reserved_table;
    TableManager* tablemanager;
    public:
    User() {
        tablemanager = TableManager::getInstance();
        reserved_table = 0;
    }
    void read() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        string s;
        do{
            cout << "Enter your phone number: ";
            cin >> phonenumber;
            s=to_string(phonenumber);
            if(s.length()<10||s.length()>10){
                cout<<"Please enter valid phone number."<<endl;
            }
        }while(s.length()<10||s.length()>10);
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
        cout << "User registered successfully.\n";
    }
    void viewuserdetails() const {
        cout << "\nUser Details:\n";
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phonenumber << endl;
        cout << "Address: " << address << endl;
    }
    void reserve_table() {
        int table_number;
        cout << "Enter the table number to reserve (1-20): ";
        cin >> table_number;
        if (tablemanager->reserve_table(table_number)) {
            reserved_table = table_number;
        }
    }
    void cancel_reservation() {
        if (reserved_table != 0) {
            bool success = tablemanager->cancel_reservation(reserved_table);
            if (success) {
                reserved_table = 0;
            }
        }
        else {
            cout << "No reservation found to cancel." << endl;
        }
    }
    void process_order() const {
        cout << "Mr/Mrs " << name << ", your order has been successfully placed." << endl;
    }
    void complete_order() {
        cout << "You cannot cancel any item after you select 1." << endl;
        cout << "Would you like to proceed with completion of order? (1 for yes, 0 for returning to main menu): ";
        int ch;
        cin >> ch;
        if (ch == 1) {
            order.process_payment();
            order.update_completion_status();
            order.displayOrder();
            process_order();
        }
    }
    void cancel_item() {
        if (!order.iscompleted()) {
            display_menu();
            order.displayOrder();
            int itemid;
            cout << "Enter item id to cancel (please check in menu for id): ";
            cin >> itemid;
            order.cancel_itemsinorder(itemid);
        }
        else {
            cout << "You cannot cancel the order right now, it is completed." << endl;
        }
    }
    void showmenu() {
        int choice;
        do {
            cout << "\n1. Display menu\n2. Place Order\n3. Cancel items in Order\n4. Reserve table\n5. Cancel Table Reservation\n6. Complete Order\n7. Exit user\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    display_menu();
                    break;
                case 2:
                    order.take_order();
                    break;
                case 3:
                    cancel_item();
                    break;
                case 4:
                    reserve_table();
                    break;
                case 5:
                    cancel_reservation();
                    break;
                case 6:
                    complete_order();
                    break;
                case 7:
                    cout << "Thank you for visiting. Visit again." << endl;
                    return;
                    break;
                default:
                    cout << "Invalid choice. Please select from the given options." << endl;
            }
        } while (choice != 7);
    }
    Order getorder() {
        return order;
    }
    int get_reserved_table() const {
        return reserved_table;
    }
};
int main() {
    int ch;
    vector<pair<User, Order>> records;
    cout << "\n*Welcome to the VDN Restaurant.*\n";
    do {
        cout << "\n1. Register user\n2. View records\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1: {
                User u;
                u.read();
                u.showmenu();
                records.emplace_back(u, u.getorder());
                break;
            }
            case 2: {
                int key;
                cout << "Enter password: ";
                cin >> key;
                if (key == 123) {
                    if (!records.empty()) {
                        cout << "User Records:" << endl;
                        for (const auto& it : records) {
                            it.first.viewuserdetails();
                            it.second.displayOrder();
                            int table = it.first.get_reserved_table();
                            if (table != 0) {
                                cout << "Reserved Table: " << table << endl;
                            }
                            else {
                                cout << "No Table Reserved." << endl;
                            }
                        }
                    }
                    else {
                        cout << "No Records Found" << endl;
                    }
                }
                else {
                    cout << "Incorrect Password." << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please select from the given options." << endl;
        }
    } while (ch != 3);
    return 0;
}
