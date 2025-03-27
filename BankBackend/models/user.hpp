#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
    int id;
    std::string name;
    double balance;

    User(int id, const std::string& name, double balance);
};

#endif
