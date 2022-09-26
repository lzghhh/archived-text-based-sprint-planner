//
// Created by ASUS on 2022/6/25.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "Project.hpp"
#include "User.hpp"
#include "Task.hpp"
using namespace std;


class System{
private:
    User* current_login;
    Project*  current_project;
    int current_max_project_id;
    int current_max_user_id;
    vector<User *> users;
    vector<Project *> projects;
    string current_date;
public:
    // Rule of 5
    System() {
        current_login = nullptr;
        current_project = nullptr;
    }
    System(User* user, Project* project, int max_project, int max_user, vector<User *> users_in, vector<Project*> projects_in, string today) {
        current_login = user;
        current_project = project;
        current_max_project_id = max_project;
        current_max_user_id = max_user;
        current_date = today;
        users = users_in;
        projects = projects_in;
    }
    ~System() {
        current_project = nullptr;
        current_login = nullptr;
        for (auto user: users) {
            delete user;
        }
        for (auto project : projects) {
            delete project;
        }
    }
    System(const System& other) {
        this->current_project = other.current_project;
        this->current_login = other.current_login;
        this->current_max_user_id = other.current_max_user_id;
        this->current_max_project_id = other.current_max_project_id;
        this->users = other.users;
        this->projects = other.projects;
        this->current_date = other.current_date;
    }
    System& operator=(const System& other) {
        if (this != &other) {
            this->current_project = nullptr;
            this->current_project = other.current_project;
            this->current_login = nullptr;
            this->current_login = other.current_login;
            this->current_max_user_id = other.current_max_user_id;
            this->current_max_project_id = other.current_max_project_id;
            this->users.clear();
            this->users = other.users;
            this->projects.clear();
            this->projects = other.projects;
            this->current_date = other.current_date;
        }
        return *this;
    }
    System(System&& other) {
        this->current_project = other.current_project;
        this->current_login = other.current_login;
        this->current_max_user_id = other.current_max_user_id;
        this->current_max_project_id = other.current_max_project_id;
        this->users = other.users;
        this->projects = other.projects;
        this->current_date = other.current_date;
        other.projects.clear();
        other.users.clear();
        other.current_login = nullptr;
        other.current_project = nullptr;
    }
    System& operator=(System&& other) {
        if (this != &other) {
            this->current_project = other.current_project;
            this->current_login = other.current_login;
            this->current_max_user_id = other.current_max_user_id;
            this->current_max_project_id = other.current_max_project_id;
            this->users = other.users;
            this->projects = other.projects;
            this->current_date = other.current_date;
            other.projects.clear();
            other.users.clear();
            other.current_login = nullptr;
            other.current_project = nullptr;
        }
        return *this;
    }

    // Load File
    Project* load_project(string path);
    User* user_finder(int id);
    Task* task_paser(vector<string> info_holder, int i);
    vector<User*> load_user();
    User* user_paser(vector<string> info_holder);
    string today_paser();
    void load_file();
    void write_file();
    // Setters
    bool isLeader();
    void set_current_max_user_id(int value) {current_max_user_id = value;}
    void set_current_max_project_id(int value) {current_max_project_id = value;}
    int set_current_login(int index);
    void set_current_project(Project *project);
    void set_users(vector<User *> users_in);
    void set_projects(vector<Project *> projects_in);

    // Getters
    User* get_current_user() {return current_login;}
    Project* get_current_project() {return current_project;}
    int get_max_project_id() {return current_max_project_id;}
    int get_max_user_id() {return current_max_user_id;}
    vector<User*> get_users() {return users;}
    vector<Project*> get_projects() {return projects;}
    string get_date() {return current_date;}
    Project* project_finder(int id);

    // ------------------------- Switch Modifiers -------------------------
    int change_current_project(int project_index);
    int change_current_user(int user_index);
    void second_layer();

    // ------------------------- System Level Modifiers -------------------------
    int add_user_to_list() {
        set_current_max_user_id(get_max_user_id() + 1);
        cout << "Please Enter User Name!" << endl;
        string name;
        getline(cin, name);
        cout << "Please Enter User Job Title!" << endl;
        string title;
        getline(cin, title);
        cout << "New user loaded!" << endl;
        users.push_back(new User(name, title, current_max_user_id));
        return 0;
    }

    // ------------------------- Display -------------------------
    void display_users();
    void display_projects();

    // ------------------------- Task modifiers & General User -------------------------
    int createProject();

};


#endif // SYSTEM_H
