#pragma once
#include <string>
#include "Person.h"

enum class AccountStatus {
    ACTIVE,
    BLOCKED,
    CANCELLED,
    CLOSED
};

// Abstract Account class
class Account {
protected:
    std::string username;
    std::string password;
    Person person;
    AccountStatus status;

public:
    Account(const std::string& uname, const std::string& pwd, const Person& p)
        : username(uname), password(pwd), person(p), status(AccountStatus::ACTIVE) {}

    virtual ~Account() = default;

    std::string getUsername() const { return username; }
    Person getPerson() const { return person; }
    AccountStatus getStatus() const { return status; }

    void setStatus(AccountStatus s) { status = s; }

    bool isActive() const { return status == AccountStatus::ACTIVE; }

    virtual std::string getAccountType() const = 0;

    // Reset password
    bool resetPassword(const std::string& oldPwd, const std::string& newPwd) {
        if (password == oldPwd) {
            password = newPwd;
            return true;
        }
        return false;
    }
};

// Admin account
class Admin : public Account {
private:
    std::string adminId;

public:
    Admin(const std::string& uname, const std::string& pwd, const Person& p, 
          const std::string& id)
        : Account(uname, pwd, p), adminId(id) {}

    std::string getAccountType() const override { return "Admin"; }
    std::string getAdminId() const { return adminId; }

    // Admin-specific operations
    void addParkingFloor() {
        // Implementation for adding a floor
    }

    void addParkingSpot() {
        // Implementation for adding a spot
    }

    void addEntrancePanel() {
        // Implementation for adding an entrance
    }

    void addExitPanel() {
        // Implementation for adding an exit
    }

    void updatePricingRate() {
        // Implementation for updating pricing
    }
};

// Customer account
class Customer : public Account {
private:
    std::string customerId;
    std::string licenseNumber;

public:
    Customer(const std::string& uname, const std::string& pwd, const Person& p, 
             const std::string& id, const std::string& license)
        : Account(uname, pwd, p), customerId(id), licenseNumber(license) {}

    std::string getAccountType() const override { return "Customer"; }
    std::string getCustomerId() const { return customerId; }
    std::string getLicenseNumber() const { return licenseNumber; }

    void setLicenseNumber(const std::string& license) { licenseNumber = license; }
};
