#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <vector>
#include "Task_Status.hpp"
#include "Task_Type.hpp"
#include "Priority.hpp"
using namespace std;

class User;

class Task {
private:
    int task_id;
    string task_name;
    Task_Type type;
    string description;
    User* assignee;
    bool individual;
    vector<User*> workers;
    Task_Status status;
    Priority priority;
    string date_assigned;
    string date_due;
public:
    Task() {}
    Task(int id, string name, Task_Type ty, string d, User* u, bool individual_flag, vector<User*> workers_in, Task_Status status_in, Priority p, string today, string due);
//rule of 5
    Task(Task const&);
    ~Task() {
        assignee = nullptr;
        workers.clear();
    }
    Task& operator=(const Task&);
    Task(Task&&);
    Task& operator=(Task&&);
//getters
    int get_id() {return task_id;}
    vector<User*> get_workers() {return workers;}
    Task_Type get_type() {return type;}
    string get_description() {return description;}
    User* get_assignee() {return assignee;}
    Task_Status get_status() {return status;}
    Priority get_priority() {return priority;}
    string get_date_assigned() {return date_assigned;}
    string get_date_due() {return date_due;}
//setters
    void set_id(int id_in) {task_id = id_in;}
    void set_description(string d) {description = d;}
    void set_status(Task_Status ts) {status = ts;}
    void set_priority(Priority p) {priority = p;}
    void set_date_due(string d) {date_due = d;}
    void set_assignee(User* u) {assignee = u;}
    void print_simplified();
    void print_detailed();
    string to_outpit_file_format();
    void add_workers(User* user) {workers.push_back(user);}

    int remove_devs(User* user);
    void fourth_layer(vector<User *> user_all, vector<User*> manager, vector<User*> devs, User* current_user);
    bool contain_user(User* user);

//overload
    friend ostream& operator<<(ostream&, const Task&);
    friend bool operator<(const Task& t1, const Task& t2);
};
#endif // TASK_H

