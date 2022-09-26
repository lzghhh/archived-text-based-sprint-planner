#include "Project.hpp"
#include "Task.hpp"
#include "User.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

Task_Type string_to_type_project(string input) {
    if (input == "USER_STORY") {
        return Task_Type::USER_STORY;
    } else if (input == "BUILD") {
        return Task_Type::BUILD;
    } else if (input == "TEST") {
        return Task_Type::TEST;
    }else if (input == "DEBUG") {
        return Task_Type::DEBUG;
    }else if (input == "DOC") {
        return Task_Type::DOC;
    }
    return Task_Type::DOC;
}

Task_Status string_to_status_project(string input) {
    if (input == "OPEN") {
        return Task_Status::OPEN;
    } else if (input == "IN_PROGRESS") {
        return Task_Status::IN_PROGRESS;
    } else if (input == "DONE") {
        return Task_Status::DONE;
    }else if (input == "OVERDUE") {
        return Task_Status::OVERDUE;
    }
    return OVERDUE;
}

Priority string_to_priority_project(string input) {
    if (input == "LOW") {
        return Priority::LOW;
    } else if (input == "MID") {
        return Priority::MID;
    } else if (input == "HIGH") {
        return Priority::HIGH;
    }
    return Priority::HIGH;
}

string num_to_string_project(int input) {
    int in = input;
    stringstream transfer;
    transfer << in;
    return transfer.str();
}

Project::Project(string n, string d, User* man, int id_in) {
    name = n;
    description = d;
    managers.push_back(man);
    new_task_id = 0;
    project_id = id_in;
}

Project::~Project() {
    for(int i = 0; i < task_todo.size(); i++) {
        if(task_todo[i] != nullptr)
            delete task_todo[i];
    }

    for(int i = 0; i < task_doing.size(); i++) {
        if(task_doing[i] != nullptr)
            delete task_doing[i];
    }

    for(int i = 0; i < task_done.size(); i++) {
        if(task_done[i] != nullptr)
            delete task_done[i];
    }
}

Project::Project(const Project& other) {
    project_id = other.project_id;
    name = other.name;
    description = other.description;
    new_task_id = other.new_task_id;
    managers = other.managers;
    devs = other.devs;
    task_todo = other.task_todo;
    task_doing = other.task_doing;
    task_done = other.task_done;
}

Project Project::operator=(const Project& other) {
    if (&other != this) {
        project_id = other.project_id;
        name = other.name;
        description = other.description;
        managers = other.managers;
        devs = other.devs;
        new_task_id = other.new_task_id;
        task_todo = other.task_todo;
        task_doing = other.task_doing;
        task_done = other.task_done;
    }
    return *this;
}

Project::Project(Project&& other) {
    name = other.name;
    description = other.description;
    managers = other.managers;
    devs = other.devs;
    new_task_id = other.new_task_id;
    task_todo = other.task_todo;
    task_doing = other.task_doing;
    task_done = other.task_done;
    other.name = nullptr;
    other.description = nullptr;
    other.managers.clear();
    other.devs.clear();
    other.new_task_id = 0;
    other.task_todo.clear();
    other.task_doing.clear();
    other.task_done.clear();
}

Project Project::operator=(Project&& other) {
    if (&other != this) {
        name = other.name;
        description = other.description;
        managers = other.managers;
        devs = other.devs;
        new_task_id = other.new_task_id;
        task_todo = other.task_todo;
        task_doing = other.task_doing;
        task_done = other.task_done;
        other.name = nullptr;
        other.description = nullptr;
        other.managers.clear();
        other.devs.clear();
        other.new_task_id = 0;
        other.task_todo.clear();
        other.task_doing.clear();
        other.task_done.clear();
    }
    return *this;
}

template<class T>
bool remove_item(vector<T*> vec, const T* rem) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == rem) {
            vec.erase(vec.begin() + i);
            return true;
        }
    }
    return false;
}

bool Project::contains_task(Task* t) {
    return find(task_todo.begin(), task_todo.end(), t) != task_todo.end()
           || find(task_doing.begin(), task_doing.end(), t) != task_doing.end()
           || find(task_done.begin(), task_done.end(), t) != task_done.end();
}

Task* Project::create_task(Task_Type type, Priority p, string d, User *assignee, string due) {
    Task *task = new Task();
    new_task_id++;
    return task;
}

bool Project::remove_task(Task* rem) {
    return remove_item(task_todo, rem) || remove_item(task_doing, rem) || remove_item(task_done, rem);
}

bool Project::update_task_status(Task *t, Task_Status new_status) {
    if (!contains_task(t))
        return false;
    switch (new_status) {
        case (OPEN):
            if (find(task_todo.begin(), task_todo.end(), t) == task_todo.end()) {
                remove_task(t);
                task_todo.push_back(t);
            }
            break;

        case (IN_PROGRESS):
            if (find(task_doing.begin(), task_doing.end(), t) == task_doing.end()) {
                remove_task(t);
                task_doing.push_back(t);
            }
            break;

        case (DONE):
            if (find(task_done.begin(), task_done.end(), t) == task_done.end()) {
                remove_task(t);
                task_done.push_back(t);
            }
            break;

        default: break;
    }
    t->set_status(new_status);
    return true;
}

bool Project::has_manager(User* u) {
    return find(managers.begin(), managers.end(), u) != managers.end();
}

bool Project::has_dev(User* u) {
    return find(devs.begin(), devs.end(), u) != devs.end();
}

void Project::add_manager(User *u) {
    if (!has_manager(u)) {
        if (has_dev(u))
            remove_dev(u);
        managers.push_back(u);
        u->add_proj(this, true);
    }
}

bool Project::remove_manager(User* u) {
    return remove_item(managers, u);
}

void Project::add_dev(User *u) {
    if (!has_dev(u)) {
        if (has_manager(u))
            remove_manager(u);
        devs.push_back(u);
        u->add_proj(this, false);
    }
}

bool Project::remove_dev(User * u) {
    return remove_item(devs, u);
}

void Project::print_simplified() {
    cout << "Project ID: " << project_id << "\t" << "Project Name: " << name << endl;
}
void Project::print_detailed(User* user_in) {
    cout << "Project ID: " << project_id << "\n" << "Project Name: " << name << "\n";
    cout << "Description: " << description << "\n" << "Current Task Amount: " << new_task_id << "\n";
    cout << "Manager and CO-LEAD: \n";
    for (auto &user : managers) {
        cout << user->get_name() << "  ";
    }
        cout << "\n";
    cout << "Devs: \n";
    for (auto &user : devs) {
        cout << user->get_name() << "  ";
    }
    cout << "\n";
    cout << "TASKS -> TO DO: \n";
    for (auto &task : task_todo) {
        if(isLeader(user_in)) {
            task->print_simplified();
        } else {
            if (task->contain_user(user_in)) {
                task->print_simplified();
            }
        }
    }
    cout << "\n";

    cout << "TASKS -> DOING: \n";
    for (auto &task : task_doing) {
        if(isLeader(user_in)) {
            task->print_simplified();
        } else {
            if (task->contain_user(user_in)) {
                task->print_simplified();
            }
        }
    }
    cout << "\n";

    cout << "TASKS -> DONE: \n";
    for (auto &task : task_done) {
        if(isLeader(user_in)) {
            task->print_simplified();
        } else {
            if (task->contain_user(user_in)) {
                task->print_simplified();
            }
        }
    }
    cout << "\n";
}
string Project::to_output_file_format() {
    string result;
    result += num_to_string_project(project_id);
    result += "\n";
    result += name;
    result += "\n";
    result += description;
    result += "\n";
    result += num_to_string_project(new_task_id);
    result += "\n";
    for (int i = 0; i < managers.size(); i++) {
        if (i == managers.size() - 1) {
            result += num_to_string_project(managers.at(i)->get_id());
            break;
        }
        result += num_to_string_project(managers.at(i)->get_id());
        result += " ";
    }
    result += "\n";
    for (int i = 0; i < devs.size(); i++) {
        if (i == devs.size() - 1) {
            result += num_to_string_project(devs.at(i)->get_id());
            break;
        }
        result += num_to_string_project(devs.at(i)->get_id());
        result += " ";
    }
    result += "\n";
    result += "todo:\n";
    for (int i = 0; i < task_todo.size(); i++) {
        if (i == task_todo.size() - 1) {
            result += task_todo.at(i)->to_outpit_file_format();
            break;
        }
        result += task_todo.at(i)->to_outpit_file_format();
        result += "\n";
    }
    if (!task_todo.empty()) {
        result += "\n";
    }
    result += "doing:\n";
    for (int i = 0; i < task_doing.size(); i++) {
        if (i == task_doing.size() - 1) {
            result += task_doing.at(i)->to_outpit_file_format();
            break;
        }
        result += task_doing.at(i)->to_outpit_file_format();
        result += "\n";
    }
    if (!task_doing.empty()) {
        result += "\n";
    }
    result += "done:";
    if (task_done.empty()) {
        return result;
    }
    result += "\n";
    for (int i = 0; i < task_done.size(); i++) {
        if (i == task_done.size() - 1) {
            result += task_done.at(i)->to_outpit_file_format();
            break;
        }
        result += task_done.at(i)->to_outpit_file_format();
        result += "\n";
    }
    return result;
}

bool Project::isLeader(User* user_in) {
    for (auto &user : managers) {
        if (user->get_id() == user_in->get_id()) {
            return true;
        }
    }
    return false;
}


string today_paser_project() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month =  1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    string result;
    result += num_to_string_project(year);
    result += "/";
    result += num_to_string_project(month);
    result += "/";
    result += num_to_string_project(day);
    return result;
}

void Project::third_layer(vector<User*> users, User* current_user) {
    while (true) {
        print_detailed(current_user);
        cout << "1. Change project Name\n";
        cout << "2. Change project description(Team member only allowed field)\n";
        cout << "3. Add Co-lead\n";
        cout << "4. Delete Co-lead\n";
        cout << "5. Add Devs\n";
        cout << "6. Delete Devs\n";
        cout << "7. Get Into Task\n";
        cout << "8. Change task to to_do\n";
        cout << "9. Change task to doing\n";
        cout << "10. Change task to done\n";
        cout << "11. Go back to previous User Menu (Log out)\n";
        cout << "12. Assign a User to A Task\n";
        cout << "13. Delete Task\n";
        cout << "14. Create Task\n";
        cout << "15. Create Individual Task\n";
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
        if (choice == 1) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Enter the new name\n";
            string input;
            getline(cin, input);
            name = input;
        }
        if (choice == 2) {
            cout << "Enter the new description\n";
            string input;
            getline(cin, input);
            description= input;
        }
        if (choice == 3) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            int index;
            cout << "Enter the User ID\n";
            cin >> index;
            cin.ignore(100, '\n');
            bool is_manager = false;
            for (auto &user : managers) {
                if (user->get_id() == index) {
                    cout << "This user has been the manager!\n";
                    is_manager = true;
                    break;
                }
            }
            if (!is_manager) {
                for (auto & user : users) {
                    if (user->get_id() == index) {
                        managers.push_back(user);
                        user->add_proj(this, true);
                        break;
                    }
                }
            }

        }
        if (choice == 4) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Enter User ID\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool find = false;
            int pos = 0;
            for (int i = 0; i < managers.size(); i++) {
                if (managers.at(i)->get_id() == index) {
                    find = true;
                    pos = i;
                    break;
                }
            }
            if (!find) {
                cout << "No such Manager exist\n";
                continue;
            } else {
                for (auto &user : managers) {
                    if (user->get_id() == index) {
                        user->del_managed_project(this);
                        break;
                    }
                }
                managers.erase(managers.begin() + pos);
            }
        }
        if (choice == 5) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            int index;
            cout << "Enter the User ID\n";
            cin >> index;
            cin.ignore(100, '\n');
            bool is_devs = false;
            for (auto &user : devs) {
                if (user->get_id() == index) {
                    cout << "This user has been the manager!\n";
                    is_devs = true;
                    break;
                }
            }
            if (!is_devs) {
                for (auto & user : users) {
                    if (user->get_id() == index) {
                        devs.push_back(user);
                        user->add_proj(this, false);
                        break;
                    }
                }
            }
        }
        if (choice == 6) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Enter User ID\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool find = false;
            int pos = 0;
            for (int i = 0; i < devs.size(); i++) {
                if (devs.at(i)->get_id() == index) {
                    find = true;
                    pos = i;
                    break;
                }
            }
            if (!find) {
                cout << "No such Devs exist\n";
                continue;
            } else {
                for (auto &user : devs) {
                    if (user->get_id() == index) {
                        user->del_dev_project(this);
                        break;
                    }
                }
                devs.erase(devs.begin() + pos);
            }
        }
        if (choice == 7) {
            cout << "Please enter the task number\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool fail = false;
            for (auto &task : task_todo) {
                if (task->get_id() == index) {
                    for (auto & user : task->get_workers()) {
                        if (user->get_id() == current_user->get_id() || has_manager(current_user)) {
                            task->fourth_layer(users, managers, devs, current_user);
                            break;
                        }
                    }
                }
            }
            for (auto &task : task_doing) {
                if (task->get_id() == index) {
                    for (auto & user : task->get_workers()) {
                        if (user->get_id() == current_user->get_id() || has_manager(current_user)) {
                            task->fourth_layer(users, managers, devs, current_user);
                            break;
                        }
                    }
                }
            }
            for (auto &task : task_done) {
                if (task->get_id() == index) {
                    for (auto & user : task->get_workers()) {
                        if (user->get_id() == current_user->get_id() || has_manager(current_user)) {
                            task->fourth_layer(users, managers, devs, current_user);
                            break;
                        }
                    }
                }
            }
        }
        if (choice == 8) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Please enter the task number\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool find = false;
            int pos = 0;
            for (int i = 0; i < task_doing.size(); i++) {
                if (task_doing.at(i)->get_id() == index) {
                    find = true;
                    task_doing.at(i)->set_status(Task_Status::OPEN);
                    pos = i;
                    task_todo.push_back(task_doing.at(i));
                }
            }
            if (find) {
                task_doing.erase(task_doing.begin() + pos);
                continue;
            }
            for (int i = 0; i < task_done.size(); i++) {
                if (task_done.at(i)->get_id() == index) {
                    find = true;
                    task_done.at(i)->set_status(Task_Status::OPEN);
                    pos = i;
                    task_todo.push_back(task_done.at(i));
                }
            }
            if (find) {
                task_done.erase(task_done.begin() + pos);
                continue;
            }
            cout << "No such task found\n";
        }
        if (choice == 9) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Please enter the task number\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool find = false;
            int pos = 0;
            for (int i = 0; i < task_todo.size(); i++) {
                if (task_todo.at(i)->get_id() == index) {
                    find = true;
                    task_todo.at(i)->set_status(Task_Status::IN_PROGRESS);
                    pos = i;
                    task_doing.push_back(task_todo.at(i));
                }
            }
            if (find) {
                task_todo.erase(task_todo.begin() + pos);
                continue;
            }
            for (int i = 0; i < task_done.size(); i++) {
                if (task_done.at(i)->get_id() == index) {
                    find = true;
                    task_done.at(i)->set_status(Task_Status::IN_PROGRESS);
                    pos = i;
                    task_doing.push_back(task_done.at(i));
                }
            }
            if (find) {
                task_done.erase(task_done.begin() + pos);
                continue;
            }
            cout << "No such task found\n";
        }
        if (choice == 10) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Please enter the task number\n";
            int index;
            cin >> index;
            cin.ignore(100, '\n');
            bool find = false;
            int pos = 0;
            for (int i = 0; i < task_todo.size(); i++) {
                if (task_todo.at(i)->get_id() == index) {
                    find = true;
                    task_todo.at(i)->set_status(Task_Status::DONE);
                    pos = i;
                    task_done.push_back(task_todo.at(i));
                }
            }
            if (find) {
                task_todo.erase(task_todo.begin() + pos);
                continue;
            }
            for (int i = 0; i < task_doing.size(); i++) {
                if (task_doing.at(i)->get_id() == index) {
                    find = true;
                    task_doing.at(i)->set_status(Task_Status::DONE);
                    pos = i;
                    task_done.push_back(task_doing.at(i));
                }
            }
            if (find) {
                task_doing.erase(task_doing.begin() + pos);
                continue;
            }
            cout << "No such task found\n";
        }

        if (choice == 12) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
            }
            int task_input_id;
            cout << "Please enter the assigned task id";
            cin >> task_input_id;
            cin.ignore(100, '\n');
            int user_input_id;
            cout << "Please enter the assigned user id";
            cin >> user_input_id;
            cin.ignore(100, '\n');
            bool result = false;
            for (auto &worker : devs) {
                if (worker->get_id() == user_input_id) {
                    for (auto &task : task_doing) {
                        if (task->get_id() == task_input_id) {
                            task->add_workers(worker);
                            cout << "Worker assigned\n";
                            result = true;
                            break;
                        }
                    }
                    for (auto &task : task_todo) {
                        if (task->get_id() == task_input_id) {
                            task->add_workers(worker);
                            cout << "Worker assigned\n";
                            result = true;
                            break;
                        }
                    }
                    for (auto &task : task_done) {
                        if (task->get_id() == task_input_id) {
                            task->add_workers(worker);
                            cout << "Worker assigned\n";
                            result = true;
                            break;
                        }
                    }
                    break;
                }
            }
            if (!result) {
                cout << "No match, please use different number\n";
            }
        }
        if (choice == 13) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
            }
            int task_input_id;
            cout << "Please enter the assigned task id";
            cin >> task_input_id;
            cin.ignore(100, '\n');
            bool finish = false;
            int pos = -10;
            for (int i = 0; i < task_doing.size(); i++) {
                if (task_doing.at(i)->get_id() == task_input_id) {
                    finish = true;
                    pos = i;
                    break;
                }
            }
            if (finish) {
                task_doing.erase(task_doing.begin() + pos);
                continue;
            }
            for (int i = 0; i < task_done.size(); i++) {
                if (task_done.at(i)->get_id() == task_input_id) {
                    finish = true;
                    pos = i;
                    break;
                }
            }
            if (finish) {
                task_done.erase(task_done.begin() + pos);
                continue;
            }
            for (int i = 0; i < task_todo.size(); i++) {
                if (task_todo.at(i)->get_id() == task_input_id) {
                    finish = true;
                    pos = i;
                    break;
                }
            }
            if (finish) {
                task_todo.erase(task_todo.begin() + pos);
                continue;
            }
        }
        if (choice == 14) {
            if (!isLeader(current_user)) {
                cout << "No permission\n";
                continue;
            }
            cout << "Enter Task Name\n";
            string task_name_in;
            getline(cin, task_name_in);
            cout << "Enter Task Type\n";
            string task_type_in;
            getline(cin, task_type_in);
            Task_Type new_type = string_to_type_project(task_type_in);
            cout << "Enter Task Priority\n";
            string task_priority_in;
            getline(cin, task_priority_in);
            Priority new_priority = string_to_priority_project(task_priority_in);
            cout << "Enter Task Description\n";
            string task_description_in;
            getline(cin, task_description_in);
            cout << "Individual Task or not(yes and no)\n";
            string response;
            getline(cin, response);
            bool flag;
            if (response == "yes") {
                flag = true;
            } else {
                flag = false;
            }
            cout << "Enter the Due date\n";
            string due_date_in;
            getline(cin, due_date_in);
            new_task_id++;
            task_todo.push_back(new Task(new_task_id, task_name_in, new_type, task_description_in, current_user, flag, {}, Task_Status::OPEN, new_priority, today_paser_project(), due_date_in));
        }
        if (choice == 15) {
            cout << "Enter Task Name\n";
            string task_name_in;
            getline(cin, task_name_in);
            cout << "Enter Task Type\n";
            string task_type_in;
            getline(cin, task_type_in);
            Task_Type new_type = string_to_type_project(task_type_in);
            cout << "Enter Task Priority\n";
            string task_priority_in;
            getline(cin, task_priority_in);
            Priority new_priority = string_to_priority_project(task_priority_in);
            cout << "Enter Task Description\n";
            string task_description_in;
            getline(cin, task_description_in);
            bool flag = true;
            cout << "Enter the Due date\n";
            string due_date_in;
            getline(cin, due_date_in);
            new_task_id++;
            task_todo.push_back(new Task(new_task_id, task_name_in, new_type, task_description_in, current_user, flag, {}, Task_Status::OPEN, new_priority, today_paser_project(), due_date_in));
        }
        if (choice == 11) {
            break;
        }


    }
}


