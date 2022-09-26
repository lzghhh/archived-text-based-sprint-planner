//
// Created by ASUS on 2022/6/25.
//
#include "Task.hpp"
#include "User.hpp"
#include <sstream>
using namespace std;

Task_Type string_to_type_task(string input) {
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

Priority string_to_priority_task(string input) {
    if (input == "LOW") {
        return Priority::LOW;
    } else if (input == "MID") {
        return Priority::MID;
    } else if (input == "HIGH") {
        return Priority::HIGH;
    }
    return Priority::HIGH;
}

string num_to_string_task(int input) {
    int in = input;
    stringstream transfer;
    transfer << in;
    return transfer.str();
}

string type_to_string_task(Task_Type input) {
    switch (input) {
        case USER_STORY: return "USER_STORY";
        case BUILD: return "BUILD";
        case TEST: return "TEST";
        case DEBUG: return "DEBUG";
        case DOC: return "DOC";
        default:
            return "OTHER";
    }
}

string status_to_string_task(Task_Status input) {
    switch (input) {
        case OPEN: return "OPEN";
        case IN_PROGRESS: return "IN_PROGRESS";
        case DONE: return "DONE";
        case OVERDUE: return "OVERDUE";
        default:
            return "OTHER";
    }
}

string priority_to_string_task(Priority input) {
    switch (input) {
        case LOW: return "LOW";
        case MID: return "MID";
        case HIGH: return "HIGH";
        default:
            return "OTHER";
    }
}


Task::Task(int id, string name, Task_Type ty, string d, User* u, bool individual_flag, vector<User*> workers_in, Task_Status status_in, Priority p, string today, string due) {
    task_id = id;
    task_name = name;
    type = ty;
    description = d;
    assignee = u;
    individual = individual_flag;
    workers = workers_in;
    status = status_in;
    priority = p;
    date_assigned = today;
    date_due = due;
}


Task::Task(Task const& other) {
    task_id = other.task_id;
    task_name = other.task_name;
    type = other.type;
    description = other.description;
    assignee = other.assignee;
    assignee = other.assignee;
    individual = other.individual;
    workers = other.workers;
    status = other.status;
    priority = other.priority;
    date_assigned = other.date_assigned;
    date_due = other.date_due;
}

Task& Task::operator=(const Task &other) {
    if (&other != this) {
        task_id = other.task_id;
        task_name = other.task_name;
        type = other.type;
        description = other.description;
        assignee = other.assignee;
        assignee = other.assignee;
        individual = other.individual;
        workers = other.workers;
        status = other.status;
        priority = other.priority;
        date_assigned = other.date_assigned;
        date_due = other.date_due;
    }
    return *this;
}

Task::Task(Task&& other) {
    task_id = other.task_id;
    task_name = other.task_name;
    type = other.type;
    description = other.description;
    assignee = other.assignee;
    assignee = other.assignee;
    individual = other.individual;
    workers = other.workers;
    status = other.status;
    priority = other.priority;
    date_assigned = other.date_assigned;
    date_due = other.date_due;
    other.description = nullptr;
    other.assignee = nullptr;
    other.workers.clear();
    // other.date_assigned = nullptr;
    // other.date_due = nullptr;
}

Task& Task::operator=(Task&& other) {
    if (&other != this) {
        task_id = other.task_id;
        task_name = other.task_name;
        type = other.type;
        description = other.description;
        assignee = other.assignee;
        assignee = other.assignee;
        individual = other.individual;
        workers = other.workers;
        status = other.status;
        priority = other.priority;
        date_assigned = other.date_assigned;
        date_due = other.date_due;
        other.description = nullptr;
        other.assignee = nullptr;
        other.workers.clear();
    }
    return *this;
}

void Task::print_simplified() {
    cout << "Task id: " << task_id << "\tTask Type: " << type << "\tTask Name: " << task_name << endl;
}
void Task::print_detailed() {
    cout << "Task id: " << task_id << "\n" << "Task name: " << task_name << "\n" << "Type: " <<
    type_to_string_task(type) << "\n" << "Description: " << description << "\n" << "Assignee: " <<
    assignee->get_name() << "\n" << "Is Individual Assignment: " << individual << "\n" << "Workers: ";
    for (auto &worker : workers) {
        cout << worker->get_name() << " ";
    }
    cout << "\n" << "Status: " << status_to_string_task(status) << "\n" << "Priority: " <<
    priority_to_string_task(priority) << "\n" << "Date Assigned: " << date_assigned << "\n" <<
    "Date Due: " << date_due << endl;
}

string Task::to_outpit_file_format() {
    string result;
    result += num_to_string_task(task_id);
    result += "\n";
    result += task_name;
    result += "\n";
    result += type_to_string_task(type);
    result += "\n";
    result += description;
    result += "\n";
    result += num_to_string_task(assignee->get_id());
    result += "\n";
    string individual_flag = "0";
    if (individual) {
        individual_flag = "1";
    }
    result += individual_flag;
    result += "\n";
    string workers_out;
    for (int i = 0; i < workers.size(); i++) {
        if (i == workers.size() - 1) {
            workers_out += num_to_string_task(workers.at(i)->get_id());
            break;
        }
        workers_out += num_to_string_task(workers.at(i)->get_id());
        workers_out += " ";
    }
    result += workers_out;
    result += "\n";
    result += status_to_string_task(status);
    result += "\n";
    result += priority_to_string_task(priority);
    result += "\n";
    result += date_assigned;
    result += "\n";
    result += date_due;
    return result;
}

int Task::remove_devs(User *user) {
    int index = -10;
    for (int i = 0; i < workers.size(); i++) {
        if (workers.at(i) == user) {
            workers.erase(workers.begin() + i);
            return 0;
        }
    }
    return 1;
}

bool Task::contain_user(User *user_in) {
    if (assignee == user_in) {
        return true;
    }
    for (auto &user : workers) {
        if (user->get_id() == user_in->get_id()) {
            return true;
        }
    }
    return false;
}

bool is_manager_task(vector<User*> managers, User* current_user) {
    for (auto &manager : managers) {
        if (manager->get_id() == current_user->get_id()) {
            return true;
        }
    }
    return false;
}

void Task::fourth_layer(vector<User *> user_all, vector<User*> manager, vector<User*> devs, User* current_user) {
    while (true) {
        print_detailed();
        cout << "1. Change task Name\n";
        cout << "2. Change task description\n";
        cout << "3. Change task type\n";
        cout << "4. Add worker\n";
        cout << "5. Del worker\n";
        cout << "6. Change Priority\n";
        cout << "7. Change date_due\n";
        cout << "8. Go back to previous User Menu (Log out)\n";
        int choice;
        cin >> choice;
        cin.ignore(100, '\n');
        if (choice == 1) {
            string new_name;
            cout << "Please enter the new name\n";
            getline(cin, new_name);
            if (individual) {
                if (assignee == current_user || is_manager_task(manager, current_user)) {
                    task_name = new_name;
                } else {
                    cout << "No permission\n";
                }
            }
            if (is_manager_task(manager, current_user)) {
                task_name = new_name;
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 2) {
            string new_description;
            cout << "Please enter the new description\n";
            getline(cin, new_description);
            // Function as the same for is_manager for using workers vector for checking workers
            if(assignee == current_user || contain_user(current_user)) {
                description = new_description;
            }
        }
        if (choice == 3) {
            string new_type_in;
            cout << "Please enter the new type\n";
            getline(cin, new_type_in);
            Task_Type new_type = string_to_type_task(new_type_in);
            if (individual) {
                if (assignee == current_user || contain_user(current_user)) {
                    type = new_type;
                } else {
                    cout << "No permission\n";
                }
            }
            if (is_manager_task(manager, current_user)) {
                type = new_type;
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 4) {
            int worker_id;
            cout << "Please enter the new id for worker\n";
            cin >> worker_id;
            cin.ignore(100, '\n');
            if (is_manager_task(manager, current_user)) {
                for (auto & user : user_all) {
                    if (user->get_id() == worker_id) {
                        workers.push_back(user);
                        break;
                    }
                }
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 5) {
            int worker_id;
            cout << "Please enter the id for worker to be deleted\n";
            cin >> worker_id;
            cin.ignore(100, '\n');
            int pos = -10;
            if (is_manager_task(manager, current_user)) {
                for (auto & user : user_all) {
                    if (user->get_id() == worker_id) {
                        for (int i = 0; i < workers.size(); i++) {
                            if (user == workers.at(i)) {
                                pos = i;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (pos == -10) {
                    cout << "No such worker\n";
                } else {
                    workers.erase(workers.begin() + pos);
                }
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 6) {
            string new_priority;
            cout << "Please enter the new priority\n";
            getline(cin, new_priority);
            if (individual) {
                if (assignee == current_user || is_manager_task(manager, current_user)) {
                    priority = string_to_priority_task(new_priority);
                } else {
                    cout << "No permission\n";
                }
            }
            if (is_manager_task(manager, current_user)) {
                priority = string_to_priority_task(new_priority);
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 7) {
            string new_due_date;
            cout << "Please enter the new priority\n";
            getline(cin, new_due_date);
            if (individual) {
                if (assignee == current_user || is_manager_task(manager, current_user)) {
                    date_due = new_due_date;
                } else {
                    cout << "No permission\n";
                }
            }
            if (is_manager_task(manager, current_user)) {
                date_due = new_due_date;
            } else {
                cout << "No permission\n";
            }
        }
        if (choice == 8) {
            break;
        }
    }
}

ostream& operator<<(ostream& output, const Task& t) {
    output << "Task id: " << t.task_id << "\tTask Type: " << t.type << "\tTask Name: " << t.task_name << endl;
    output << "\"" << t.description << "\"" << endl;
    return output;
}

bool operator<(const Task& t1, const Task& t2) {
    return t1.priority < t2.priority;
}



