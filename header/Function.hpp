#pragma once

#include <string>
#include <iomanip>
#include <iostream>

const int WIDTH = 25;


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

enum class Option {
    ADD_EMPLOYEE = 1,
    DELETE_EMPLOYEE,
    FIND_EMPLOYEE,
    PRINT_LIST,
    CALCULATE_SALARY,
    DELETE_LIST,
    EXIT
};

bool isEmpty(List *head);
List *createList(Employee employee);
void insert(List **head, Employee employee);
void printEmployee(List *current);
void printList(List *head);
void deleteEmployeeByPayrollNumber(List **head, int payrollNumber);
List *findEmployee(List *head, int payrollNumber);
void deleteList(List **head);
void printSalary(List *current, const double &salary);
void calculateSalary(List *head);
void showMenu();
Employee getEmployee();
size_t getPayrollNumber(const std::string& message);
Option getOption();
void printHeadline();
