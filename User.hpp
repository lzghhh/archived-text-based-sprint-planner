//
// Created by ASUS on 2022/6/25.
//

#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>

using namespace std;

class Project;
class Task;

class User {
private:
    string name;
    int user_id;
    string job_title;
    vector<int> projects_manage;
    vector<int> projects_dev;

public:
    User() {}
    User(string name_in, string job_title_in, int user_id_in) {
        name = name_in;
        job_title = job_title_in;
        user_id = user_id_in;
    }

    User(string name_in, int user_id_in, string job_title_in, vector<int> manage_in, vector<int> dev_in) {
        name = name_in;
        job_title = job_title_in;
        user_id = user_id_in;
        projects_manage = manage_in;
        projects_dev = dev_in;
    }

    ~User() {
        projects_manage.clear();
        projects_dev.clear();
    }

    User(const User& other) {
        this->name = other.name;
        this->user_id = other.user_id;
        this->job_title = other.job_title;
        this->projects_manage = other.projects_manage;
        this->projects_dev = other.projects_dev;
    }

    User& operator=(const User& other) {
        if (this != &other) {
            this->name = other.name;
            this->user_id = other.user_id;
            this->job_title = other.job_title;
            this->projects_manage.clear();
            this->projects_manage = other.projects_manage;
            this->projects_dev.clear();
            this->projects_dev = other.projects_dev;
        }
        return *this;
    }

    User(User&& other) {
        this->name = other.name;
        this->user_id = other.user_id;
        this->job_title = other.job_title;
        this->projects_manage = other.projects_manage;
        this->projects_dev = other.projects_dev;
        other.projects_manage.clear();
        other.projects_dev.clear();
    }

    User& operator=(User&& other) {
        if (this != &other) {
            this->name = other.name;
            this->user_id = other.user_id;
            this->job_title = other.job_title;
            this->projects_manage = other.projects_manage;
            this->projects_dev = other.projects_dev;
            other.projects_manage.clear();
            other.projects_dev.clear();
        }
        return *this;
    }

    // setters
    void set_name(string input) {name = input;}
    void set_user_id(int id) {user_id = id;}
    void set_job_title(string input) {job_title = input;}
    void add_proj(Project *proj, bool is_manager);
    int del_managed_project(Project* project);
    int del_dev_project(Project* project);
    // getters
    string get_name() {return name;}
    int get_id() {return user_id;}
    string get_job_title() {return job_title;}
    vector<int> get_managed_projects() {return projects_manage;}
    vector<int> get_dev_projects() {return projects_dev;}

    // print
    void print_simplified();
    void print_detailed();
    string to_output_file_format();
};
#endif //USER_H

