//
// Created by ASUS on 2022/6/25.
//

#ifndef PROJECT_H
#define PROJECT_H
#include "Task.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class User;

class Project {
private:
    int project_id;
    string name;
    string description;
    int new_task_id;
    vector<User*> managers;
    vector<User*> devs;
    vector<Task*> task_todo;
    vector<Task*> task_doing;
    vector<Task*> task_done;

public:
//constructor
    Project() {}
    Project(string, string, User*, int);

//rule of 5
    ~Project();
    Project(const Project&);
    Project operator=(const Project&);
    Project(Project&&);
    Project operator=(Project&&);

// finders
    bool contains_task(Task*);
    bool has_manager(User*);
    bool has_dev(User*);
//getters
    int get_id() {return project_id;}
    string get_name() {return name;}
    string get_description() {return description;}
    vector<User*> get_managers() {return managers;}
    vector<User*> get_devs() {return devs;}
    vector<Task*> get_todo() {return task_todo;}
    vector<Task*> get_doing() {return task_doing;}
    vector<Task*> get_done() {return task_done;}

//setters
    void set_id(int id_in) {project_id = id_in;}
    void set_max_task_id(int id_in) {new_task_id = id_in;}
    void set_name(string n) {name = n;}
    void set_description(string d) {description = d;}
    void set_managers(vector<User*> input) {managers = input;}
    void set_devs(vector<User*> input) {devs = input;}
    void add_todo(Task* task) {task_todo.push_back(task);}
    void add_doing(Task* task) {task_doing.push_back(task);}
    void add_done(Task* task) {task_done.push_back(task);}
//bool methods indicate whether the method ran successfully
    Task* create_task(Task_Type, Priority, string, User*, string);
    bool remove_task(Task*);
    bool update_task_status(Task*, Task_Status);
    void add_manager(User*);
    bool remove_manager(User*);
    void add_dev(User*);
    bool remove_dev(User*);

    // Controller
    void third_layer(vector<User*> users, User* current_user);
    bool isLeader(User* user_in);

    // Print
    void print_simplified();
    void print_detailed(User* user_in);
    string to_output_file_format();
};
#endif //PROJECT_H

