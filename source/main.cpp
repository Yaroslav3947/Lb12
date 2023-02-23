
#include <Function.hpp>

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
                        printHeadline();
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
                    printHeadline();
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
