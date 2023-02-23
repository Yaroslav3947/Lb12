#include <Function.hpp>

bool isEmpty(List *head) {
    return head == nullptr;
}

List *createList(Employee employee) {
    List *newList = new List;
    newList->employee = employee;
    newList->next = nullptr;
    return newList;
}
void insert(List **head, Employee employee) {
    List *newList = createList(employee);
    if(isEmpty(*head)) {
        *head = newList;
    } else {
        List *current = *head;
        while(!isEmpty(current->next)) {
            current = current->next; // find a node that has a nullptr address
        }
        current->next = newList; // nullptr change to the address of newList(to nullptr)
    }

}
void printEmployee(List *current) {
    std::cout << std::left << std::setw(WIDTH) << current->employee.fullName.firstName
              << std::left << std::setw(WIDTH) << current->employee.fullName.lastName 
              << std::left << std::setw(WIDTH) << current->employee.fullName.middleName 
              << std::left << std::setw(WIDTH) << current->employee.payrollNumber 
              << std::left << std::setw(WIDTH) << current->employee.numberOfWorkedHours 
              << std::left << std::setw(WIDTH) << current->employee.hourlyRate << '\n';
}
void printList(List *head) {
    List *current = head;
    if(isEmpty(current)) {
        std::cout << "List is empty\n";
        return;
    }
    printHeadline();
    while(!isEmpty(current)) {
        printEmployee(current);
        current = current->next;
    }
}

void deleteEmployeeByPayrollNumber(List **head, int payrollNumber) {
    List *current = *head;
    List *previous;


    while (!isEmpty(current) && current->employee.payrollNumber != payrollNumber) {
        previous = current;
        current = current->next; // which has a needed payrollNumber
    }

    if (current == nullptr) {
        std::cerr << "A worker with this payroll number was not found\n";
        return;
    }

    if(!isEmpty(current) && current->employee.payrollNumber == payrollNumber) { // if it is a head node(first)
        *head = current->next; // to skip deleted node
        delete current;
        return;
    } 
    previous->next = current->next; // we like jump over a deleted node
    delete current;

}


List *findEmployee(List *head, int payrollNumber) {
    List *current = head;
    while(!isEmpty(current)) {
        if(current->employee.payrollNumber == payrollNumber) {
            return current;
        }
        current = current->next;
    }
    std::cout << "The employee with this payroll number wasn't found\n";
    return nullptr;
}

void deleteList(List **head) {
    List *current = *head;
    List *next;

    while(!isEmpty(current)) {
        next = current->next;
        delete current;
        current = next;
    }

    *head = nullptr;
}

void printSalary(List *current, const double &salary) {
    std::cout << std::setw(WIDTH) << std::left << current->employee.fullName.firstName
              << std::setw(WIDTH) << std::left << current->employee.fullName.lastName 
              << std::setw(WIDTH) << std::left << current->employee.fullName.middleName
              << std::setw(WIDTH) << std::left << current->employee.payrollNumber 
              << std::setw(WIDTH) << std::left << current->employee.numberOfWorkedHours 
              << std::setw(WIDTH) << std::left << current->employee.hourlyRate 
              << std::setw(WIDTH) << std::left << salary << '\n';

}
void calculateSalary(List *head) {
    const double TAX_RATE = 0.88;
    const size_t MAX_WORKED_HOURS = 144;
    const double OVERTIME_MULTIPLIER = 2.0;
    List *current = head;
    while (!isEmpty(current)) {
        double salary = 0.0;
        if (current->employee.numberOfWorkedHours > MAX_WORKED_HOURS) {
            const double regularHoursPay = MAX_WORKED_HOURS * current->employee.hourlyRate;
            const double overtimePay = (current->employee.numberOfWorkedHours - MAX_WORKED_HOURS) * current->employee.hourlyRate * OVERTIME_MULTIPLIER;
            salary = regularHoursPay + overtimePay;
        } else {
            salary = current->employee.numberOfWorkedHours * current->employee.hourlyRate;
        }
        salary *= TAX_RATE;
        printSalary(current, salary);
        current = current->next;
    }
}


void showMenu() {
    std::cout << "Choose an option:\n"  
         << "1. Add employee\n" 
         << "2. Delete employee\n" 
         << "3. Find employee\n" 
         << "4. Print list\n" 
         << "5. Calculate salary\n" 
         << "6. Delete list\n"
         << "7. Exit\n"
         << "Enter option: ";
}

Employee getEmployee() {
    Employee employee;
    std::cout << "Enter employee details:" << std::endl;
    std::cout << "First name: ";
    std::cin >> employee.fullName.firstName;
    std::cout << "Last name: ";
    std::cin >> employee.fullName.lastName;
    std::cout << "Middle name: ";
    std::cin >> employee.fullName.middleName;
    std::cout << "Payroll number: ";
    std::cin >> employee.payrollNumber;
    std::cout << "Number of worked hours: ";
    std::cin >> employee.numberOfWorkedHours;
    std::cout << "Hourly rate: ";
    std::cin >> employee.hourlyRate;
    return employee;
}
size_t getPayrollNumber(const std::string& message) {
    size_t payrollNumber;
    std::cout << "Enter the payroll number of the employee " << message << '\n';
    std::cin >> payrollNumber;
    return payrollNumber;
}

Option getOption() {
    int option;
    std::cin >> option;
    return static_cast<Option>(option);
}

void printHeadline() {
    std::cout  << std::setw(WIDTH) << std::left << "First Name"
               << std::setw(WIDTH) << std::left << "Last Name"
               << std::setw(WIDTH) << std::left << "Middle Name"
               << std::setw(WIDTH) << std::left << "Payroll Number"
               << std::setw(WIDTH) << std::left << "Worked Hours"
               << std::setw(WIDTH) << std::left << "Hourly Rate" 
               << std::setw(WIDTH) << std::left << "Salary"<< '\n';
}