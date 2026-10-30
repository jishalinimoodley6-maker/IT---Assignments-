#pragma once

#include <string>

class Engineer
{
private:
    std::string engineerID;
    std::string username;
    std::string encryptedPassword;
    std::string clearanceLevel;

public:
    Engineer(const std::string& id,
             const std::string& user,
             const std::string& password,
             const std::string& clearance);

    std::string getEngineerID() const;
    std::string getUsername() const;
    std::string getEncryptedPassword() const;
    std::string getClearanceLevel() const;

    bool checkLogin(const std::string& user,
                    const std::string& password) const;
};
