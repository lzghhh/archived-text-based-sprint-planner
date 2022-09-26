//
// Created by ASUS on 2022/6/26.
//

#include "System.hpp"
#include "Task.hpp"
#include "Project.hpp"
#include "User.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string num_to_string(int input) {
    int in = input;
    stringstream transfer;
    transfer << in;
    return transfer.str();
}

string System::today_paser() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month =  1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    string result;
    result += num_to_string(year);
    result += "/";
    result += num_to_string(month);
    result += "/";
    result += num_to_string(day);
    return result;
}

Task_Type string_to_type(string input) {
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

string type_to_string(Task_Type input) {
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

Task_Status string_to_status(string input) {
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

string status_to_string(Task_Status input) {
    switch (input) {
        case OPEN: return "OPEN";
        case IN_PROGRESS: return "IN_PROGRESS";
        case DONE: return "DONE";
        case OVERDUE: return "OVERDUE";
        default:
            return "OTHER";
    }
}

Priority string_to_priority(string input) {
    if (input == "LOW") {
        return Priority::LOW;
    } else if (input == "MID") {
        return Priority::MID;
    } else if (input == "HIGH") {
        return Priority::HIGH;
    }
    return Priority::HIGH;
}

string priority_to_string(Priority input) {
    switch (input) {
        case LOW: return "LOW";
        case MID: return "MID";
        case HIGH: return "HIGH";
        default:
            return "OTHER";
    }
}


int string_to_num(string str){
    stringstream  transfer(str);
    int result;
    transfer >> result;
    return result;
};

vector<int> string_parser(string input) {
    if (input.empty()) {
        return {};
    }
    string s = input + " ";
    string delimiter = " ";
    size_t pos = 0;
    string token;
    vector<int> result;
    while((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        result.push_back(string_to_num(token));
        s.erase(0, pos + delimiter.length());
    }
    return result;
}

User* System::user_finder(int id) {
    for (auto user: users) {
        if (user->get_id() == id) {
            return user;
        }
    }
    return nullptr;
}

Project* System::project_finder(int id) {
    for (auto project: projects) {
        if (project->get_id() == id) {
            return project;
        }
    }
    return nullptr;
}

Task* System::task_paser(vector<string> info_holder, int i) {
    int temp_task_id = string_to_num(info_holder.at(i + 0));
    string temp_task_name = info_holder.at(i + 1);
    Task_Type temp_task_type = string_to_type(info_holder.at(i + 2));
    string temp_description = info_holder.at(i + 3);
    User* temp_assignee = user_finder(string_to_num(info_holder.at(i + 4)));
    bool temp_individual_flag = false;
    if (info_holder.at(i + 5) == "1") {
        temp_individual_flag = true;
    }
    vector<User*> temp_task_workers_input;
    if (info_holder.at(i + 6).empty()) {
        temp_task_workers_input = {};
    } else {
        vector<int> workers_id = string_parser(info_holder.at(i + 6));
        for (auto &in : workers_id) {
            temp_task_workers_input.push_back(user_finder(in));
        }
    }
    Task_Status temp_task_status = string_to_status(info_holder.at(i + 7));
    Priority temp_task_priority = string_to_priority(info_holder.at(i + 8));
    string temp_task_date_assigned = info_holder.at(i + 9);
    string temp_task_date_due = info_holder.at(i + 10);
    Task* holder = new Task(temp_task_id, temp_task_name, temp_task_type, temp_description,
                            temp_assignee, temp_individual_flag, temp_task_workers_input,
                            temp_task_status, temp_task_priority, temp_task_date_assigned, temp_task_date_due);
    return holder;
}

User* System::user_paser(vector<string> info_holder) {
    string temp_user_name = info_holder.at(0);
    int temp_user_id = string_to_num(info_holder.at(1));
    string temp_job_title = info_holder.at(2);
    vector<int> temp_projects_manage = string_parser(info_holder.at(3));
    vector<int> temp_projects_dev = string_parser(info_holder.at(4));
    User* result = new User(temp_user_name, temp_user_id, temp_job_title, temp_projects_manage, temp_projects_dev);
    return result;
}


Project* System::load_project(string path) {
    string parsed_project;
    ifstream project_file(path);
    vector<string> info_holder;
    Project *result = new Project();
    while(getline(project_file, parsed_project)) {

        if (parsed_project == "todo:") {
            result->set_id(string_to_num(info_holder.at(0)));
            result->set_name(info_holder.at(1));
            result->set_description(info_holder.at(2));
            result->set_max_task_id(string_to_num(info_holder.at(3)));
            vector<User*> manager_input;
            vector<int> manager_id = string_parser(info_holder.at(4));
            for (auto &i : manager_id) {
                manager_input.push_back(user_finder(i));
            }
            result->set_managers(manager_input);
            vector<User*> devs_input;
            vector<int> devs_id = string_parser(info_holder.at(5));
            for (auto &i : devs_id) {
                devs_input.push_back(user_finder(i));
            }
            result->set_devs(devs_input);
            info_holder.clear();
            continue;
        }
        if (parsed_project == "doing:") {
            for (int i = 0; i < info_holder.size(); i+=11) {
                result->add_todo(task_paser(info_holder, i));
            }
            info_holder.clear();
            continue;
        }
        if (parsed_project == "done:") {
            for (int i = 0; i < info_holder.size(); i+=11) {
                result->add_doing(task_paser(info_holder, i));
            }
            info_holder.clear();
            continue;
        }
        info_holder.push_back(parsed_project);
    }
    for (int i = 0; i < info_holder.size(); i+=11) {
        result->add_done(task_paser(info_holder, i));
    }
    info_holder.clear();
    project_file.close();
    return result;
}

vector<User*> System::load_user() {
    ifstream user_file("user.txt");
    string parsed_user;
    vector<string> info_holder;
    vector<User*> result;
    while (getline(user_file, parsed_user)) {
        if(parsed_user == "==") {
            result.push_back(user_paser(info_holder));
            info_holder.clear();
            continue;
        }
        info_holder.push_back(parsed_user);
    }
    info_holder.clear();
    user_file.close();
    return result;
}

void System::load_file() {
    ifstream index_file("maxindex.txt");
    string indexes;
    int count = 0;
    while (getline(index_file, indexes)) {
        if (count == 0) {
            current_max_project_id = string_to_num(indexes);
            count++;
            continue;
        }
        current_max_user_id = string_to_num(indexes);
    }
    cout << "Index file loaded!" << endl;
    index_file.close();
    vector<User*> users_in = load_user();
    users = users_in;
    cout << "User file loaded!" << endl;
    vector<Project*> projects_in;
    for (int i = 1; i <= current_max_project_id; i++) {

        string path = "project";
        ostringstream transfer;
        transfer << i;
        string index = transfer.str();
        path += index;
        path += ".txt";
        projects_in.push_back(load_project(path));
    }
    cout << "Project file loaded!" << endl;
    projects = projects_in;
    current_date = today_paser();
}

void System::write_file() {
    // Write Indexes file
    ofstream indexes_write("maxindex.txt");
    string indexes;
    indexes += num_to_string(current_max_project_id);
    indexes += "\n";
    indexes += num_to_string(current_max_user_id);
    indexes_write << indexes;
    indexes_write.close();
    // Write Users file
    ofstream user_write("user.txt");
    string user_out;
    for (int i = 0; i < users.size(); i++) {
        if (i == users.size() - 1) {
            user_out += users.at(i)->to_output_file_format();
            user_out += "\n==";
            break;
        }
        user_out += users.at(i)->to_output_file_format();
        user_out += "\n==\n";
    }
    user_write << user_out;
    user_write.close();
    // Write Projects in separate files
    for (int i = 0; i < current_max_project_id; i++) {
        string project_out;
        string path = "project";
        ostringstream transfer;
        transfer << (i + 1);
        string index = transfer.str();
        path += index;
        path += ".txt";
        ofstream project_write(path);
        project_out = projects.at(i)->to_output_file_format();
        project_write << project_out;
        project_write.close();
    }
}


bool System::isLeader() {
    return current_project->has_manager(current_login);
}

void System::set_current_project(Project *project) {
    current_project = project;
}

void System::set_users(vector<User *> users_in) {
    users = users_in;
}

void System::set_projects(vector<Project *> projects_in) {
    projects = projects_in;
}

int System::change_current_project(int project_index) {
    for (auto project : projects) {
        if (project->get_id() == project_index) {
            current_project = project;
            return 0;
        }
    }
    return 1;
}

int System::change_current_user(int user_index) {
    for (auto user : users) {
        if (user->get_id() == user_index) {
            current_login = user;
            return 0;
        }
    }
    return 1;
}

void System::display_users() {
    for (auto &user : users) {
        user->print_simplified();
        cout << "\n";
    }
}

void System::display_projects() {
    cout << "Managed Projects: \n";
    for (auto &project : projects) {
        vector<User*> temp_check = project->get_managers();
        for (auto & user : temp_check) {
            if (user == current_login) {
                project->print_simplified();
            }
        }
    }

    cout << "Devs Projects: \n";
    for (auto &project : projects) {
        vector<User*> temp_check = project->get_devs();
        for (auto & user : temp_check) {
            if (user == current_login) {
                project->print_simplified();
            }
        }
    }
}

int System::set_current_login(int index) {
    for (auto & user : users) {
        if (user->get_id() == index) {
            current_login = user;
            return 0;
        }
    }
    return 1;
}

int System::createProject() {
    Project* project = new Project();
    current_max_project_id++;
    project->set_id(current_max_project_id);
    string name_in;
    cout << "Enter Name: \n";
    cin.ignore(100, '\n');
    getline(cin, name_in);
    project->set_name(name_in);
    string description_in;
    cout << "Enter Description: \n";
    getline(cin, description_in);
    project->set_description(description_in);
    project->set_max_task_id(0);
    cout << "Enter co-lead(ID number): \n";
    string co_lead_in;
    getline(cin, co_lead_in);
    vector<int> managers_id = string_parser(co_lead_in);
    for (auto & index : managers_id) {
        project->add_manager(user_finder(index));
        user_finder(index)->add_proj(project, true);
    }
    project->add_manager(current_login);

    cout << "Enter devs(ID number): \n";
    string devs_in;
    getline(cin, devs_in);
    vector<int> devs_id = string_parser(devs_in);
    for (auto & index : devs_id) {
        project->add_dev(user_finder(index));
        user_finder(index)->add_proj(project, false);
    }

    projects.push_back(project);
    return 0;
}

void System::second_layer() {
    while (true) {
        display_projects();
        cout << "Enter a number operator (Non-digit character will cause crash): \n";
        cout << "1. Create a Project\n";
        cout << "2. Set A Project As Current Project\n";
        cout << "3. Delete A Project\n";
        cout << "4. Go to Current Project\n";
        cout << "5. See detailed information about the current project\n";
        cout << "6. Go back to previous User Menu (Log out)\n";
        int index;
        cin >> index;
        if (index == 1) {
            createProject();
        }
        if (index == 2) {
            cout << "Enter a project id number\n";
            int input;
            cin >> input;
            cin.ignore(100, '\n');
            if(nullptr == project_finder(input)){
                cout << "Incorrect ID, try again\n";
            } else {
                current_project = project_finder(input);
            }
        }
        if (index == 3) {
            cout << "Please enter the id of project that wants to be deleted\n";
            int input;
            cin >> input;
            cin.ignore(100, '\n');
            bool find = false;
            for (auto &id : current_login->get_managed_projects()) {
                if (id == input) {
                    find = true;
                }
            }
            if (find) {
                int pos = -10;
                for (int i = 0; i < projects.size(); i++) {
                    if (projects.at(i)->get_id() == input) {
                        pos = i;
                    }
                }
                vector<User*> managers_in = project_finder(input)->get_managers();
                for (auto &manager : managers_in) {
                    manager->del_managed_project(project_finder(input));
                }
                vector<User*> devs_in = project_finder(input)->get_devs();
                for (auto &devs : devs_in) {
                    devs->del_dev_project(project_finder(input));
                }
                delete projects.at(pos);
                projects.erase(projects.begin() + pos);
            } else {
                cout << "No access to delete that project\n";
            }

        }
        if (index == 4) {
            if (current_project == nullptr) {
                cout << "Fail to open, retry please\n";
                continue;
            }
            current_project->third_layer(users, current_login);
        }
        if (index == 5) {
            if (current_project == nullptr) {
                cout << "Fail to open, retry please\n";
                continue;
            }
            current_project->print_detailed(current_login);
        }
        if (index == 6) {
            break;
        }
    }
}
