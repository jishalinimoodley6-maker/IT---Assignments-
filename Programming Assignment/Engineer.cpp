#include "Engineer.h"

Engineer::Engineer(const std::string& id,
                   const std::string& user,
                   const std::string& password,
                   const std::string& clearance)
    : engineerID(id),
      username(user),
      encryptedPassword(password),
      clearanceLevel(clearance)
{
}

std::string Engineer::getEngineerID() const
{
    return engineerID;
}

std::string Engineer::getUsername() const
{
    return username;
}

std::string Engineer::getEncryptedPassword() const
{
    return encryptedPassword;
}

std::string Engineer::getClearanceLevel() const
{
    return clearanceLevel;
}

bool Engineer::checkLogin(const std::string& user,
                          const std::string& password) const
{
    return username == user && encryptedPassword == password;
}
