#pragma once
#include <string>
#include <chrono>

enum class PaymentStatus {
    PENDING,
    COMPLETED,
    FAILED,
    CANCELLED,
    REFUNDED
};

enum class PaymentMethod {
    CASH,
    CREDIT_CARD,
    DEBIT_CARD
};

class Payment {
protected:
    std::string paymentId;
    double amount;
    PaymentStatus status;
    PaymentMethod method;
    std::chrono::system_clock::time_point paymentTime;

    static int paymentCounter;

public:
    Payment(double amt, PaymentMethod m)
        : amount(amt), status(PaymentStatus::PENDING), method(m) {
        paymentId = "PAY-" + std::to_string(++paymentCounter);
        paymentTime = std::chrono::system_clock::now();
    }

    virtual ~Payment() = default;

    virtual bool processPayment() = 0;

    std::string getPaymentId() const { return paymentId; }
    double getAmount() const { return amount; }
    PaymentStatus getStatus() const { return status; }
    PaymentMethod getMethod() const { return method; }

protected:
    void setStatus(PaymentStatus s) { status = s; }
};

class CashPayment : public Payment {
private:
    double cashReceived;

public:
    CashPayment(double amt, double received)
        : Payment(amt, PaymentMethod::CASH), cashReceived(received) {}

    bool processPayment() override {
        if (cashReceived >= amount) {
            setStatus(PaymentStatus::COMPLETED);
            return true;
        }
        setStatus(PaymentStatus::FAILED);
        return false;
    }

    double getChange() const {
        return (cashReceived > amount) ? (cashReceived - amount) : 0.0;
    }
};

class CardPayment : public Payment {
private:
    std::string cardNumber;
    std::string cardHolderName;

public:
    CardPayment(double amt, PaymentMethod cardType, 
                const std::string& cardNum, const std::string& holderName)
        : Payment(amt, cardType), cardNumber(cardNum), cardHolderName(holderName) {}

    bool processPayment() override {
        // Simulate card processing
        // In real system: connect to payment gateway
        if (!cardNumber.empty() && cardNumber.length() >= 13) {
            setStatus(PaymentStatus::COMPLETED);
            return true;
        }
        setStatus(PaymentStatus::FAILED);
        return false;
    }

    std::string getMaskedCardNumber() const {
        if (cardNumber.length() < 4) return "****";
        return "************" + cardNumber.substr(cardNumber.length() - 4);
    }
};
