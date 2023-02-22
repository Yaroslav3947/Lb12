#include <iomanip>
#include <iostream>

const int WIDTH = 20;

struct FullName {
    std::string firstName;
    std::string lastName;
    std::string middleName;
};

struct Employee {
    FullName fullName;
    size_t payrollNumber;
    size_t numberOfWorkedHours;
    size_t hourlyRate;
};

struct List {
    Employee employee;
    List *next;
};

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
    std::cout << current->employee.fullName.firstName << std::setw(WIDTH)
              << current->employee.fullName.lastName << std::setw(WIDTH)
              << current->employee.fullName.middleName << std::setw(WIDTH)
              << current->employee.payrollNumber << std::setw(WIDTH)
              << current->employee.numberOfWorkedHours << std::setw(WIDTH)
              << current->employee.hourlyRate << std::setw(WIDTH) << '\n';
}
void printList(List *head) {
    List *current = head;
    if(isEmpty(current)) {
        std::cout << "List is empty\n";
    }
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
    std::cout << current->employee.fullName.firstName << std::setw(WIDTH)
              << current->employee.fullName.lastName << std::setw(WIDTH)
              << current->employee.fullName.middleName << std::setw(WIDTH)
              << current->employee.payrollNumber << std::setw(WIDTH)
              << salary << '\n';

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

enum class Option {
    ADD_EMPLOYEE = 1,
    DELETE_EMPLOYEE,
    FIND_EMPLOYEE,
    PRINT_LIST,
    CALCULATE_SALARY,
    DELETE_LIST,
    EXIT
};
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
int main() {
    List *head = nullptr;
    Option option;
    do {
        showMenu();
        option = getOption();
        switch (option) {
            case Option::ADD_EMPLOYEE: {
                Employee employee = getEmployee();
                insert(&head, employee);
                break;
            }
            case Option::DELETE_EMPLOYEE: {
                if(isEmpty(head)) {
                    std::cout << "List is empty\n";
                } else {
                    size_t payrollNumberToDelete = getPayrollNumber("to detele");
                    deleteEmployeeByPayrollNumber(&head, payrollNumberToDelete);
                }
                break;
            }
            case Option::FIND_EMPLOYEE: {
                if(isEmpty(head)) {
                    std::cout << "List is empty\n";
                } else {
                    size_t payrollNumberTofind = getPayrollNumber("to find");
                    List *employeeTofind = findEmployee(head,payrollNumberTofind);
                    if(employeeTofind != nullptr) {
                        printEmployee(employeeTofind);
                    }
                }
                break;
            }
            case Option::PRINT_LIST: {
                if(isEmpty(head)) {
                    std::cout << "List is empty\n";
                } else {
                    printList(head);  
                }  
                break;
            }
            case Option::CALCULATE_SALARY: {
                if(isEmpty(head)) {
                    std::cout << "List is empty\n";
                } else {
                    calculateSalary(head);
                }
                break;
            }
            case Option::DELETE_LIST: {
                if(isEmpty(head)) {
                    std::cout << "List is empty\n";
                } else {
                    deleteList(&head);
                }
                break;
            }
            case Option::EXIT: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid option. Please choose other option.\n";
                break;
            }
        }
    } while (option != Option::EXIT);

    deleteList(&head);

    return 0;
}
