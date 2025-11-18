// 25102543 parkJeYoung 
// compile> g++ --std=gnu++11 FILE.cpp -o FILE

#include <iostream>
#include <string>

// Helper function to print headers
void print_header(const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
}

// --- Setup for Question 1 ---

// This class simulates the behavior from Question 1.
// It relies on the compiler-generated (synthesized) copy constructor.
class numbered_q1 {
private:
    // Static member to generate unique IDs, shared by all objects
    static int next_sn; 
public:
    int mysn; // The object's unique serial number

    // Default constructor: assigns a new serial number
    numbered_q1() {
        mysn = next_sn++;
    }

    // We do *not* define a copy constructor.
    // The compiler will synthesize one that looks like this:
    // numbered_q1(const numbered_q1& other) {
    //     mysn = other.mysn; // This is a simple member-wise copy
    // }
};

// Initialize the static member for the Q1 class
int numbered_q1::next_sn = 0;

// The function 'f' from Q1 (pass-by-value)
// This will invoke the synthesized copy constructor.
void f_q1(numbered_q1 s) {
    std::cout << "f_q1() called. Copied object's mysn: " << s.mysn << std::endl;
}


// --- Setup for Question 2 & 3 ---

// This class simulates the behavior from Question 2.
// It has a *custom* copy constructor that generates a new serial number.
class numbered_q2 {
private:
    // A separate static counter for this class
    static int next_sn;
public:
    int mysn;

    // Default constructor
    numbered_q2() {
        mysn = next_sn++;
        std::cout << "Default constructor. mysn = " << mysn << std::endl;
    }

    // Custom copy constructor for Question 2
    numbered_q2(const numbered_q2& other) {
        mysn = next_sn++; // It generates a NEW serial number
        std::cout << "Custom copy constructor. new mysn = " << mysn << std::endl;
    }
};

// Initialize the static member for the Q2 class
int numbered_q2::next_sn = 0;

// The function 'f' for Q2 (pass-by-value)
// This will invoke the CUSTOM copy constructor.
void f_q2(numbered_q2 s) {
    std::cout << "f_q2() output: " << s.mysn << std::endl;
}

// The function 'f' for Q3 (pass-by-reference)
// This will *not* invoke any copy constructor.
void f_q3(const numbered_q2& s) {
    std::cout << "f_q3() output: " << s.mysn << std::endl;
}


int main() {
    // --- Verification for Question 1 ---
    print_header("Question 1: Synthesized Copy Constructor");
    numbered_q1 a1;       // a1.mysn = 0
    numbered_q1 b1 = a1;  // b1.mysn = 0 (synthesized copy)
    numbered_q1 c1 = b1;  // c1.mysn = 0 (synthesized copy)
    
    // Pass-by-value calls f_q1, which uses the synthesized copy ctor.
    // The copied object 's' will have mysn = 0 each time.
    f_q1(a1);
    f_q1(b1);
    f_q1(c1);


    // --- Verification for Question 2 & 3 ---
    // Note: Q2 and Q3 use the *same* objects.
    
    print_header("Question 2: Custom Copy Constructor");
    numbered_q2 a2;       // Prints "Default constructor. mysn = 0"
    numbered_q2 b2 = a2;  // Prints "Custom copy constructor. new mysn = 1"
    numbered_q2 c2 = b2;  // Prints "Custom copy constructor. new mysn = 2"
    
    std::cout << "\nCalling f_q2 (pass-by-value):\n";
    // Each call invokes the custom copy constructor again
    f_q2(a2); // Prints "... new mysn = 3", then "f_q2() output: 3"
    f_q2(b2); // Prints "... new mysn = 4", then "f_q2() output: 4"
    f_q2(c2); // Prints "... new mysn = 5", then "f_q2() output: 5"

    
    print_header("Question 3: Pass-by-Reference");
    std::cout << "Calling f_q3 (pass-by-reference) on the *same* objects:\n";
    // No copy constructor is called.
    // It prints the original serial numbers of a2, b2, and c2.
    f_q3(a2); // Prints "f_q3() output: 0"
    f_q3(b2); // Prints "f_q3() output: 1"
    f_q3(c2); // Prints "f_q3() output: 2"

    return 0;
}