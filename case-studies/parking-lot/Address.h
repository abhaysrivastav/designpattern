#pragma once
#include <string>

// Custom data type for storing addresses
class Address {
private:
    std::string streetAddress;
    std::string city;
    std::string state;
    std::string zipCode;
    std::string country;

public:
    Address() = default;
    
    Address(const std::string& street, const std::string& cityName, 
            const std::string& stateName, const std::string& zip, 
            const std::string& countryName)
        : streetAddress(street), city(cityName), state(stateName), 
          zipCode(zip), country(countryName) {}

    std::string getStreetAddress() const { return streetAddress; }
    std::string getCity() const { return city; }
    std::string getState() const { return state; }
    std::string getZipCode() const { return zipCode; }
    std::string getCountry() const { return country; }

    void setStreetAddress(const std::string& street) { streetAddress = street; }
    void setCity(const std::string& cityName) { city = cityName; }
    void setState(const std::string& stateName) { state = stateName; }
    void setZipCode(const std::string& zip) { zipCode = zip; }
    void setCountry(const std::string& countryName) { country = countryName; }

    std::string getFullAddress() const {
        return streetAddress + ", " + city + ", " + state + " " + zipCode + ", " + country;
    }
};
