#include <iostream>
#include <string>

class Coffee
{
public:
    virtual ~Coffee()=default;
    virtual std::string getDescritpion() const=0;
    virtual double cost() const=0;
};

class SimpleCoffee : public Coffee
{
public:
    std::string getDescritpion() const override
    {
        return "Simple Coffee";
    }

    double cost() const override
    {
        return 5.00;
    }
};

class CoffeeDecorator: public Coffee
{
protected:
    Coffee* coffee;
public:
    CoffeeDecorator(Coffee* c): coffee(c){}

    std::string getDescritpion() const override
    {
        return coffee->getDescritpion();
    }

    double cost() const override
    {
        return coffee->cost();
    }
};

class MilkDecorator:public CoffeeDecorator
{
public:
    MilkDecorator(Coffee*c): CoffeeDecorator(c){}

    std::string getDescritpion() const override
    {
        return coffee->getDescritpion() + "Milk";
    }

    double cost() const override
    {
        return coffee->cost()+2.0;
    }
};

class SugarDecorator : public CoffeeDecorator
{
public: 
    SugarDecorator(Coffee* c): CoffeeDecorator(c){}
    std::string getDescritpion() const override
    {
        return coffee->getDescritpion() + "Milk+sugar";
    }

    double cost() const override
    {
        return coffee->cost()+5.0;
    }

};


int main()
{
    Coffee* myCoffee = new SimpleCoffee();
    std::cout <<  "Simple Coffee " << myCoffee->getDescritpion() << std::endl;
    std::cout <<  "Simple Coffee Cost " << myCoffee->cost() << std::endl;

    myCoffee = new MilkDecorator(myCoffee);
    std::cout << "Order with milk " << myCoffee->getDescritpion() << std::endl;
    std::cout << "Order with milk Cost " << myCoffee->cost() << std::endl;

    myCoffee= new SugarDecorator(myCoffee);
    std::cout << "Order with milk " << myCoffee->getDescritpion() << std::endl;
    std::cout << "Order with milk Cost " << myCoffee->cost() << std::endl;

    delete myCoffee;
    return 0;
}
