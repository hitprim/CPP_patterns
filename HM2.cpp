#include <iostream>
#include <vector>
#include <string>



// Abstract Factory =====================================
class Pizza {
public:
    virtual void prepare(std::string) {};
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
};

class CheesePizza : public Pizza {};
class GreekPizza : public Pizza {};
class PepperoniPizza : public Pizza {};

Pizza* orderPizza(std::string type) {
    Pizza* pizza = nullptr;
    if (type == "cheese") {
        pizza = new CheesePizza;
    }
    else if (type == "greek") {
        pizza = new GreekPizza;
    }
    else if (type == "pepperoni") {
        pizza = new PepperoniPizza;
    }
    return pizza;
}

class UniversalPizza : public Pizza {
    void prepare(std::string p) override {
        std::cout << "Prepare: " << p << std::endl;
    }

    void bake() override {
        std::cout << "Pizza is bake" << std::endl;
    }

    void cut() override {
        std::cout << "Pizza is cut" << std::endl;
    }

    void box() override {
        std::cout << "Pizza in the box!" << std::endl;
    }
};

class PizzaFactory {
public:
    virtual Pizza* creatPizza() = 0;
    virtual ~PizzaFactory() {};
};

class CheesePizzaFactory : public PizzaFactory {
public:
    Pizza* creatPizza() override {
        return new UniversalPizza();
    }
};
//==============================================================
// Command
enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

class Light {
public:
    Light() :state(false), color(Colors::WHITE) {};
    void On() {
        if (!state) {
            state = true;
        }
    };

    void Off() {
        if (state) {
            state = false;
        }
    };

    void changeColor(Colors newColor) {
        color = newColor;
    }

    bool getState() const {
        return state;
    }

private:
    bool state;
    Colors color;
};

class Command {
protected:
    Light* light;
public:
    virtual void chColor() = 0;

    virtual ~Command() {};

    void setLight(Light* newLight) {
        light = newLight;
    }
};

class ChangeColor : public Command {
    Colors col;
public:
    ChangeColor(Colors color) : col(color) {};

    void chColor() override {
        light->changeColor(col);
    }
};

class Invoker {
    std::vector<Command*> donCom;
    Light lig;
    Command* com;
public:
    Invoker() : com(nullptr) {}

    virtual ~Invoker() {
        for (Command* ptr : donCom)
            delete ptr;
    }

    void on() {
        lig.On();
    }

    void off() {
        lig.Off();
    }

    void changeColor(Colors newColor) {
        com = new ChangeColor(newColor);
        com->setLight(&lig);
        com->chColor();
        donCom.push_back(com);
    }
    void show() {
        std::cout << "Show:" << donCom.size() << std::endl;
    }

};
//=======================================================
// Decorator
class Beverage {            
public:
    // virtual std::string getDescription() const ;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

class HouseBlend : public Beverage {   
public:
    double cost() const override {
        return 5.5;
    }
};

class DarkRoast : public Beverage {  
public:
    double cost() const override {
        return 6.0;
    }
};

class Decaf : public Beverage {    
public:
    double cost() const override {
        return 7.3;
    }
};

class Espresso : public Beverage {  
public:
    double cost() const override {
        return 3.5;
    }
};

class Decorator : public Beverage {
    Beverage* _beverage;
public:
    Decorator(Beverage* bever) : _beverage(bever) {}
    double cost() const override {
        return _beverage->cost();
    }
};

class AddSugar : public Decorator {

    std::string _add;

    double Sugar() const {
        if (_add == "sugar") {
            std::cout << "You choose additives: " << _add << "; Price:" << " 1.5" << std::endl;
            return 1.5;
        }
        else if (_add == "without sugar") {
            std::cout << "You choose additives: " << _add << std::endl;
        }

    }

public:
    AddSugar(Beverage* bever, std::string add) : Decorator(bever), _add(add) {}

    double cost() const override {
        Decorator::cost();
        return Sugar();
    }

};

class AddCinnamon : public Decorator {

    std::string _add;

    double Cinnamon() const {

        std::cout << "You choose additives: " << _add << std::endl;
        return 2.5;

    }

public:
    AddCinnamon(Beverage* bever, std::string add) : Decorator(bever), _add(add) {}

    double cost() const override {
        Decorator::cost();
        return Cinnamon();
    }


};

class AddChocolate : public Decorator {

    std::string _add;

    double Chocolate() const {

        std::cout << "You choose additives: " << _add << std::endl;
        return 2.5;

    }

public:
    AddChocolate(Beverage* bever, std::string add) : Decorator(bever), _add(add) {}

    double cost() const override {
        Decorator::cost();
        return Chocolate();
    }
};