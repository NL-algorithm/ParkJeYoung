// 25102543 parkJeYoung 
// compile> g++ --std=gnu++11 FILE.cpp -o FILE

#include <iostream>
#include <string>

class Employee {
public:
    // 1. Default constructor
    Employee() : id(next_id++) {
        // 'id' is initialized, 'name' is default-initialized (empty string)
    }

    // 2. Constructor that takes a name
    Employee(const std::string& s) : name(s), id(next_id++) {
        // 'id' and 'name' are initialized
    }

    // --- No Copy-Control Members Defined ---
    // The compiler provides the correct behavior (Rule of Zero).
    // - Synthesized Destructor
    // - Synthesized Copy Constructor
    // - *Deleted* Copy-Assignment Operator (because id is const)
    // - Synthesized Move Constructor
    // - *Deleted* Move-Assignment Operator (because id is const)

    // Helper function to print employee details
    void print() const {
        std::cout << "Name: " << (name.empty() ? "[N/A]" : name);
        std::cout << ", ID: " << id << std::endl;
    }

private:
    std::string name;
    const int id; // The ID is const, it cannot be changed after creation

    // Static member to generate unique IDs
    static int next_id;
};

// Define and initialize the static data member
int Employee::next_id = 101; // Start IDs from 101


// --- Main function to verify behavior ---
int main() {
    std::cout << "Creating employees..." << std::endl;
    Employee e1;                 // Uses default constructor
    Employee e2("Alice Smith");  // Uses string constructor
    Employee e3("Bob Johnson");  // Uses string constructor

    e1.print(); // Name: [N/A], ID: 101
    e2.print(); // Name: Alice Smith, ID: 102
    e3.print(); // Name: Bob Johnson, ID: 103

    std::cout << "\nTesting copy constructor..." << std::endl;
    Employee e4 = e2; // Uses synthesized copy constructor
    e4.print();       // Name: Alice Smith, ID: 102 (Correctly a copy of e2)

    std::cout << "\nTesting copy assignment (this will fail to compile)..." << std::endl;
    // e1 = e3; // <-- COMPILE ERROR
    //
    // The line above will not compile. The error message will be similar to:
    // "use of deleted function 'Employee& Employee::operator=(const Employee&)'"
    //
    // This is the *desired behavior* because we should not
    // be able to change the constant ID of an existing employee.

    std::cout << "Program finished successfully." << std::endl;

    return 0;
}