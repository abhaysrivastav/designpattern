#pragma once
#include <string>
#include <memory>

// Abstract base class for all persons in the system
class Person {
protected:
    std::string id;
    std::string name;
    std::string email;
    std::string phone;

public:
    Person(const std::string& personId, const std::string& personName, 
           const std::string& personEmail, const std::string& personPhone)
        : id(personId), name(personName), email(personEmail), phone(personPhone) {}

    virtual ~Person() = default;

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }

    void updateEmail(const std::string& newEmail) { email = newEmail; }
    void updatePhone(const std::string& newPhone) { phone = newPhone; }
};

// Customer class - represents parking lot users
class Customer : public Person {
private:
    std::string licenseNumber;
    std::string paymentMethod;

public:
    Customer(const std::string& customerId, const std::string& customerName,
             const std::string& customerEmail, const std::string& customerPhone,
             const std::string& license)
        : Person(customerId, customerName, customerEmail, customerPhone),
          licenseNumber(license), paymentMethod("") {}

    std::string getLicenseNumber() const { return licenseNumber; }
    
    void setPreferredPaymentMethod(const std::string& method) {
        paymentMethod = method;
    }
    
    std::string getPreferredPaymentMethod() const { return paymentMethod; }
};

// Admin class - represents system administrators
class Admin : public Person {
private:
    std::string adminLevel; // e.g., "SUPER_ADMIN", "MANAGER", "OPERATOR"
    bool isActive;

public:
    Admin(const std::string& adminId, const std::string& adminName,
          const std::string& adminEmail, const std::string& adminPhone,
          const std::string& level = "OPERATOR")
        : Person(adminId, adminName, adminEmail, adminPhone),
          adminLevel(level), isActive(true) {}

    std::string getAdminLevel() const { return adminLevel; }
    
    bool getIsActive() const { return isActive; }
    
    void setActive(bool active) { isActive = active; }
    
    void promoteToLevel(const std::string& newLevel) {
        adminLevel = newLevel;
    }

    // Admin can perform privileged operations
    bool canAddFloor() const {
        return isActive && (adminLevel == "SUPER_ADMIN" || adminLevel == "MANAGER");
    }

    bool canUpdatePricing() const {
        return isActive && (adminLevel == "SUPER_ADMIN" || adminLevel == "MANAGER");
    }

    bool canViewReports() const {
        return isActive; // All active admins can view reports
    }

    bool canManageSpots() const {
        return isActive;
    }
};
