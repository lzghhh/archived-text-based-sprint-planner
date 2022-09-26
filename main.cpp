// Group 21 Antonio Caceres, Julian Flack, Weixin Kong

#include <iostream>
#include <random>
#include <unistd.h>
#include <ctime>
#include "System.hpp"
using namespace std;

void second_layer(System* sys) {
    while (true) {

    }
}

int main(){
    System* sys = new System();
    sys->load_file();
    if (sys->get_users().empty()) {
        cout << "No user loaded! Please add a user!" << endl;
        sys->add_user_to_list();
        cout << "New user loaded!" << endl;
    }
    while(true) {
        sys->display_users();
        cout << "Top Level: \n";
        cout << "1. Set Current User\n";
        cout << "2. Add New User\n";
        cout << "3. Change current User name and other info\n";
        cout << "4. Write to file\n";
        cout << "5. Get Into Current User Page\n";
        cout << "6. quit\n";

        int user_index;
        cin >> user_index;
        cin.ignore(100, '\n');
        if (user_index > 6 || user_index < 1) {
            cout << "Invalid Input, Try Again!\n";
            continue;
        }
        if (user_index == 6) {
            break;
        }
        switch (user_index) {
            case 1:
                while (true) {
                    cout << "Enter the User ID (Enter Non-digit Number will cause crash)\n";
                    int input;
                    cin >> input;
                    cin.ignore(100, '\n');
                    if (sys->set_current_login(input) == 1) {
                        cout << "Invalid Input, Please Try Again!\n";
                        continue;
                    }
                    cout << "Current User is set as User " << sys->get_current_user()->get_id() << endl;
                    break;
                }
                break;
            case 2:
                sys->add_user_to_list();
                break;
            case 3:
                while (true) {
                    cout << "Enter the User ID (Enter Non-digit Number will cause crash)\n";
                    int input;
                    cin >> input;
                    cin.ignore(100, '\n');
                    cout << "Enter new name\n";
                    string name_new;
                    getline(cin, name_new);
                    cout << "Enter new job title\n";
                    string title_new;
                    getline(cin, title_new);
                    sys->user_finder(input)->set_name(name_new);
                    sys->user_finder(input)->set_job_title(title_new);
                    break;
                }
                break;
            case 4:
                sys->write_file();
                break;
            default:
                break;
        }
        if (user_index == 5) {
            if (sys->get_current_user() == nullptr) {
                cout << "Please choose a User first!\n";
                continue;
            }
            sys->second_layer();
        }
    }


    delete sys;




    return 0;
}
