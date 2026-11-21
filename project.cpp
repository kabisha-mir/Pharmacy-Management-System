#include <iostream>
#include <string>

using namespace std;

// Base Class (Parent)
class Medicine {
protected:
    string name;
    string expiry;
    double price;
    int quantity;

public:
    // Constructor
    Medicine(string n, string exp, double p, int q) {
        name = n;
        expiry = exp;
        price = p;
        quantity = q;
    }

    virtual ~Medicine() {}

    // Setters & Getters
    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setExpiry(string exp) { expiry = exp; }
    string getExpiry() const { return expiry; }

    void setPrice(double p) { price = p; }
    double getPrice() const { return price; }

    void setQuantity(int q) { quantity = q; }
    int getQuantity() const { return quantity; }

    // Operator Overloading (+) -> Prices add karne ke liye
    double operator+(const Medicine& other) const {
        return this->price + other.price;
    }

    // Virtual Function (Polymorphism)
    virtual void showDetail() const {
        cout << "Name: " << name << " | Expiry: " << expiry
             << " | Price: $" << price << " | Qty: " << quantity;
    }

    // Friend Class Declaration
    friend class SearchHelper;
};

// Derived Class 1: Syrup
class Syrup : public Medicine {
private:
    double volumeInMl;

public:
    Syrup(string n, string exp, double p, int q, double vol)
        : Medicine(n, exp, p, q), volumeInMl(vol) {}

    // Function Overriding
    void showDetail() const override {
        cout << "[SYRUP] ";
        Medicine::showDetail();
        cout << " | Vol: " << volumeInMl << "ml" << endl;
    }

    // Unique Function
    void measureDose(int spoons) const {
        cout << "-> Instruction: Take " << spoons << " spoon(s) of " << name << " (" << spoons * 5 << "ml)." << endl;
    }
};

// Derived Class 2: Capsule
class Capsule : public Medicine {
private:
    string shellType;

public:
    Capsule(string n, string exp, double p, int q, string type)
        : Medicine(n, exp, p, q), shellType(type) {}

    // Function Overriding
    void showDetail() const override {
        cout << "[CAPSULE] ";
        Medicine::showDetail();
        cout << " | Shell: " << shellType << endl;
    }

    // Unique Function
    void showInstructions() const {
        cout << "-> Instruction: Swallow " << name << " whole with a full glass of water." << endl;
    }
};

// Derived Class 3: Tablet
class Tablet : public Medicine {
private:
    int mgPerTablet;

public:
    Tablet(string n, string exp, double p, int q, int mg)
        : Medicine(n, exp, p, q), mgPerTablet(mg) {}

    // Function Overriding
    void showDetail() const override {
        cout << "[TABLET] ";
        Medicine::showDetail();
        cout << " | Power: " << mgPerTablet << "mg" << endl;
    }

    // Unique Function
    void breakDose() const {
        cout << "-> Instruction: " << name << " can be split into two " << mgPerTablet / 2 << "mg half-doses." << endl;
    }
};

// Friend Class
class SearchHelper {
public:
    void checkAvailable(const Medicine* m) const {
        // Direct access to protected member 'quantity' via Friend Class
        if (m->quantity > 0) {
            m->showDetail();
        } else {
            cout << "[OUT OF STOCK] " << m->name << " is not available." << endl;
        }
    }
};

int main() {
    // Derived Objects / Pointers
    Syrup* m1 = new Syrup("Brufen", "2026-12", 50.0, 10, 120.0);
    Capsule* m2 = new Capsule("Risek", "2027-05", 120.0, 81, "Soft Gel");
    Tablet* m3 = new Tablet("Panadol", "2026-10", 20.0, 50, 500);

    SearchHelper helper;
    int choice = 0;

    do {
        cout << "\n====================================\n";
        cout << "       PHARMACY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Show All Details\n";
        cout << "2. Search by Name\n";
        cout << "3. Search by Expiry\n";
        cout << "4. Search by Price\n";
        cout << "5. Show Available Only\n";
        cout << "6. Use Special Medicine Functions\n";
        cout << "7. Total Price (Operator Overloading +)\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
       
        if (!(cin >> choice)) {
            cin.clear();

            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            cout << "\n--- ALL MEDICINES ---\n";
            m1->showDetail();
            m2->showDetail();
            m3->showDetail();
        }
        else if (choice == 2) {
            string searchName;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, searchName);
           
            bool found = false;
            if (m1->getName() == searchName) { m1->showDetail(); found = true; }
            if (m2->getName() == searchName) { m2->showDetail(); found = true; }
            if (m3->getName() == searchName) { m3->showDetail(); found = true; }
           
            if (!found) cout << "No medicine found with name: " << searchName << endl;
        }
        else if (choice == 3) {
            string searchExp;
            cout << "Enter Expiry (YYYY-MM): ";
            cin >> searchExp;
           
            bool found = false;
            if (m1->getExpiry() == searchExp) { m1->showDetail(); found = true; }
            if (m2->getExpiry() == searchExp) { m2->showDetail(); found = true; }
            if (m3->getExpiry() == searchExp) { m3->showDetail(); found = true; }
           
            if (!found) cout << "No medicine found with expiry: " << searchExp << endl;
        }
        else if (choice == 4) {
            double maxPrice;
            cout << "Enter Max Price: ";
            cin >> maxPrice;
           
            bool found = false;
            if (m1->getPrice() <= maxPrice) { m1->showDetail(); found = true; }
            if (m2->getPrice() <= maxPrice) { m2->showDetail(); found = true; }
            if (m3->getPrice() <= maxPrice) { m3->showDetail(); found = true; }
           
            if (!found) cout << "No medicine found within price range: RS" << maxPrice << endl;
        }
        else if (choice == 5) {
            cout << "\n--- AVAILABLE MEDICINES ---\n";
            helper.checkAvailable(m1);
            helper.checkAvailable(m2);
            helper.checkAvailable(m3);
        }
        else if (choice == 6) {
            cout << "\n--- UNIQUE DERIVED FUNCTIONS ---\n";
            m1->measureDose(2);       
            m2->showInstructions();   
            m3->breakDose();          
        }
        else if (choice == 7) {
            cout << "\n--- OPERATOR OVERLOADING (+ PRICE DEMO) ---\n";
            double totalPrice = *m1 + *m3;
            cout << "Total combined price of " << m1->getName()
                 << " ($" << m1->getPrice() << ") and " << m3->getName()
                 << " ($" << m3->getPrice() << ") is: RS" << totalPrice << endl;
        }

    } while (choice != 8);

    // Free dynamically allocated memory
    delete m1;
    delete m2;
    delete m3;

    cout << "\nExiting Program. Memory freed successfully.\n";
    return 0;
}