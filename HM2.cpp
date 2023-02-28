#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
class Pizza {
public:
    virtual void prepare(std::string) {};
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
};

class CheesePizza :public Pizza {};
class GreekPizza :public Pizza {};
class PepperoniPizza :public Pizza {};


// Абстрактная фабрика
class PizzaFactory {
public:
    virtual Pizza* createPizza() = 0;
};

// Конкретные фабрики
class CheesePizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new CheesePizza;
    }
};

class GreekPizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new GreekPizza;
    }
};

class PepperoniPizzaFactory : public PizzaFactory {
public:
    Pizza* createPizza() override {
        return new PepperoniPizza;
    }
};


Pizza* orderPizza(std::string type) {
    PizzaFactory* factory = nullptr;
    Pizza* pizza = nullptr;
    if (type == "cheese") {
        factory = new CheesePizzaFactory;
    }
    else if (type == "greek") {
        factory = new GreekPizzaFactory;
    }
    else if (type == "pepperoni") {
        factory = new PepperoniPizzaFactory;
    }
    if (factory != nullptr) {
        pizza = factory->createPizza();
    }
    return pizza;
}

//======================================================================


class Events {
public:
    virtual void getEvent() = 0;
    virtual ~Events() {};
};

class Hotel : public Events {
public:
    void getEvent() {
        std::cout << "Booking Hotel" << std::endl;
    }
};

class Park : public Events {
    void getEvent() {
        std::cout << "Park visiting" << std::endl;
    }
};

class Food : public Events {
public:
    virtual void getEvent() = 0;
    virtual ~Food() {};
};

class Dinner : public Food {
public:
    Dinner();
    Dinner(const std::string& type) : _type("breakfast") {}
    void getEvent() {
        std::cout << "Food " << _type << std::endl;
    };
private:
    std::string _type;
};

class Lunch : public Food {
public:
    Lunch() : _type("lunch") {}
    void getEvent() {
        std::cout << "Food " << _type << std::endl;
    };
private:
    std::string _type;
};

class Breakfast : public Food {
public:
    Breakfast() : _type("breakfast") {}
    void getEvent() {
        std::cout << "Food " << _type << std::endl;
    };
private:
    std::string _type;
};

class Special : public Events {
public:
    virtual void getEvent() = 0;
    virtual ~Special() {};
};

class Skating :public Special {
public:
    Skating();
    Skating(const std::string& type) : _type("skating") {}
    void getEvent() {
        std::cout << _type << std::endl;
    };
private:
    std::string _type;
};

class Circus :public Special {
public:
    Circus();
    Circus(const std::string& type) : _type("circus") {}
    void getEvent() {
        std::cout << _type << std::endl;
    };
private:
    std::string _type;
};




// Интерфейс строителя
class Builder {
public:
    virtual void buildHotel() = 0;
    virtual void buildPark() = 0;
    virtual void buildFood() = 0;
    virtual void buildSpecial() = 0;
    virtual std::vector<Events*> getResult() = 0;
};

// Конкретный строитель
class DayPlanBuilder : public Builder {
public:
    DayPlanBuilder() : _events({}) {}
    void buildHotel() override {
        _events.push_back(new Hotel);
    }
    void buildPark() override {
        _events.push_back(new Park);
    }
    void buildFood() override {
        
        _events.push_back(new Breakfast);
        _events.push_back(new Lunch);
        _events.push_back(new Dinner);
    }
    void buildSpecial() override {
        
        _events.push_back(new Skating);
        _events.push_back(new Circus);
    }
    std::vector<Events*> getResult() override {
        return _events;
    }
private:
    std::vector<Events*> _events;
};

// Класс, который будет использовать строитель для создания плана дня
class DayPlanner {
public:
    void setBuilder(Builder* builder) {
        _builder = builder;
    }
    std::vector<Events*> getDayPlan() {
        _builder->buildHotel();
        _builder->buildPark();
        _builder->buildFood();
        _builder->buildSpecial();
        return _builder->getResult();
    }
private:
    Builder* _builder;
};

//========================================================================


// Implementor
class DrawingImplementor {
public:
    virtual void drawRectangle(double) = 0;

    virtual ~DrawingImplementor() {
    }
};

// Abstraction
class Shape {
protected:
    DrawingImplementor* implementor_;
public:
    Shape(DrawingImplementor* implementor) : implementor_(implementor) {}
    virtual void draw() = 0; // low-level
    virtual void resize(double pct) = 0; // high-level
    virtual ~Shape() {
        delete implementor_;
    }
};



// Concrete Abstraction - Rectangle
class Rectangle : public Shape {
public:
    Rectangle(DrawingImplementor* implementor) : Shape(implementor) {}
    void draw() override {
        implementor_->drawRectangle(10.0); // рисуем прямоугольник
    }
    void resize(double pct) override {
        std::cout << "Resizing rectangle by " << pct << "%" << std::endl;
    }
};



// Concrete Implementor - рисование кистью
class BrushDrawingImplementor : public DrawingImplementor {
public:
    void drawRectangle(double size) override {
        std::cout << "Drawing rectangle with brush of size " << size << std::endl;
    }
};

// Concrete Implementor - рисование карандашом
class PencilDrawingImplementor : public DrawingImplementor {
public:
    void drawRectangle(double size) override {
        std::cout << "Drawing rectangle with pencil of size " << size << std::endl;
    }
};

//===================================================================================


int main()
{

    DrawingImplementor* brushImplementor = new BrushDrawingImplementor();
    Shape* brushRectangle = new Rectangle(brushImplementor);
    brushRectangle->draw(); 

    DrawingImplementor* pencilImplementor = new PencilDrawingImplementor();
    Shape* pencilRectangle = new Rectangle(pencilImplementor);
    pencilRectangle->draw(); 

}
    
    
