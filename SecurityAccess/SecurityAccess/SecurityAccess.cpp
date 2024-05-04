#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class UserRole {
    GUEST,
    EMPLOYEE,
    ADMIN
};

class User {
private:
    string username;
    string password;
    UserRole role;

public:
    User(const string& uname, const string& pword, UserRole r)
        : username(uname), password(pword), role(r) {}

    const string& getUsername() const {
        return username;
    }

    UserRole getRole() const {
        return role;
    }

    bool authenticate(const string& providedPassword) const {
        return password == providedPassword;
    }
};

class AccessControlSystem {
private:
    unordered_map<string, User> userDatabase;

public:
    AccessControlSystem() {
        userDatabase["guest"] = User("guest", "guestpassword", UserRole::GUEST);
        userDatabase["employee"] = User("employee", "employeepassword", UserRole::EMPLOYEE);
        userDatabase["admin"] = User("admin", "adminpassword", UserRole::ADMIN);
    }

    const User* getUser(const string& username) const {
        auto it = userDatabase.find(username);
        if (it != userDatabase.end()) {
            return &(it->second);
        }
        return nullptr;
    }
};

int main() {
    AccessControlSystem accessControl;

    string username, password;
    cout << "Welcome to the Facility Access Control System\n";
    cout << "Enter username: ";
    cin >> username;

    const User* user = accessControl.getUser(username);

    if (user) {
        cout << "Enter password: ";
        cin >> password;

        if (user->authenticate(password)) {
            cout << "Authentication successful. Welcome, " << username << "!\n";
            switch (user->getRole()) {
            case UserRole::GUEST:
                cout << "You have guest access.\n";
                break;
            case UserRole::EMPLOYEE:
                cout << "You have employee access.\n";
                break;
            case UserRole::ADMIN:
                cout << "You have admin access.\n";
                break;
            }
            // Implement actual gate control or other access-related actions here
        }
        else {
            cout << "Authentication failed. Incorrect password.\n";
        }
    }
    else {
        cout << "User not found. Please check your username.\n";
    }

    return 0;
}
