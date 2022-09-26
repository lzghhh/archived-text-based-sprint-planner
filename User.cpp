//
// Created by ASUS on 2022/6/26.
//
#include "User.hpp"
#include "Project.hpp"
#include <sstream>

string num_to_string_user(int input) {
    int in = input;
    stringstream transfer;
    transfer << in;
    return transfer.str();
}

void User::add_proj(Project* proj, bool is_manager) {
    if(is_manager) {
        this->projects_manage.push_back(proj->get_id());
    }
    else {
        this->projects_dev.push_back(proj->get_id());
    }
}

int User::del_managed_project(Project* project) {
    int result_index = -1;
    for (int i = 0; i < projects_manage.size(); i++) {
        if (projects_manage.at(i)== project->get_id()) {
            result_index = i;
            break;
        }
    }
    if (result_index != -1) {
        projects_manage.erase(projects_manage.begin() + result_index);
        return 0;
    }
    return 1;
}

int User::del_dev_project(Project* project) {
    int result_index = -1;
    for (int i = 0; i < projects_dev.size(); i++) {
        if (projects_dev.at(i) == project->get_id()) {
            result_index = i;
            break;
        }
    }
    if (result_index != -1) {
        projects_dev.erase(projects_dev.begin() + result_index);
        return 0;
    }
    return 1;
}

void User::print_simplified() {
    cout << "Name: " << name << "\t" << "ID: " << user_id << "\t" << "Job Title: " << job_title << endl;
}
void User::print_detailed() {
    cout << "Name: " << name << "\n" << "ID: " << user_id << "\n" << "Job Title: " << job_title << "\n";
    cout << "Managed Project: \n";
    for (auto &project_id : projects_manage) {
        cout << project_id << " ";
    }
    cout << "\n";
    cout << "Devs Project: \n";
    for (auto &project_id : projects_dev) {
        cout << project_id << " ";
    }
    cout << "\n";
}
string User::to_output_file_format() {
    string result;
    result += name;
    result += "\n";
    result += num_to_string_user(user_id);
    result += "\n";
    result += job_title;
    result += "\n";
    if (projects_manage.empty()) {

    } else {
        for (int i = 0; i < projects_manage.size(); i++) {
            if (i == projects_manage.size() - 1) {
                result += num_to_string_user(projects_manage.at(i));
                break;
            }
            result += num_to_string_user(projects_manage.at(i));
            result += " ";
        }
    }
    result += "\n";
    if (projects_dev.empty()) {
        return result;
    }
    for (int i = 0; i < projects_dev.size(); i++) {
        if (i == projects_dev.size() - 1) {
            result += num_to_string_user(projects_dev.at(i));
            break;
        }
        result += num_to_string_user(projects_dev.at(i));
        result += " ";
    }
    return result;
}



