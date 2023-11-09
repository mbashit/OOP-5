#include <iostream>

class Pair {
public:
    virtual Pair* add(const Pair& other) const = 0;
    virtual Pair* subtract(const Pair& other) const = 0;
    virtual Pair* multiply(const Pair& other) const = 0;
    virtual Pair* divide(const Pair& other) const = 0;
    virtual void display() const = 0;
};

class Money : public Pair {
private:
    int rubles;
    int copecks;

protected:
    int getRubles() const { return rubles; }
    int getCopecks() const { return copecks; }

public:
    Money(int rub, int cop) : rubles(rub), copecks(cop) {}

    Pair* add(const Pair& other) const override {
        const Money& otherMoney = dynamic_cast<const Money&>(other);
        int totalCopecks = getRubles() * 100 + getCopecks() + otherMoney.getRubles() * 100 + otherMoney.getCopecks();
        int newRubles = totalCopecks / 100;
        int newCopecks = totalCopecks % 100;
        return new Money(newRubles, newCopecks);
    }

    Pair* subtract(const Pair& other) const override {
        const Money& otherMoney = dynamic_cast<const Money&>(other);
        int totalCopecks = getRubles() * 100 + getCopecks() - (otherMoney.getRubles() * 100 + otherMoney.getCopecks());
        int newRubles = totalCopecks / 100;
        int newCopecks = totalCopecks % 100;
        return new Money(newRubles, newCopecks);
    }

    Pair* multiply(const Pair& other) const override {
        const Money& otherMoney = dynamic_cast<const Money&>(other);
        int totalCopecks = getRubles() * 100 + getCopecks() * (otherMoney.getRubles() * 100 + otherMoney.getCopecks());
        int newRubles = totalCopecks / 100;
        int newCopecks = totalCopecks % 100;
        return new Money(newRubles, newCopecks);
    }

    Pair* divide(const Pair& other) const override {
        const Money& otherMoney = dynamic_cast<const Money&>(other);
        if (otherMoney.getRubles() == 0 && otherMoney.getCopecks() == 0) {
            std::cerr << "Error: Division by zero in Money class." << std::endl;
            return nullptr; // You may handle division by zero differently based on your requirements
        }
        double divisionResult = static_cast<double>(getRubles() * 100 + getCopecks()) /
            static_cast<double>(otherMoney.getRubles() * 100 + otherMoney.getCopecks());
        int newRubles = static_cast<int>(divisionResult);
        int newCopecks = static_cast<int>((divisionResult - newRubles) * 100);
        return new Money(newRubles, newCopecks);
    }

    void display() const override {
        std::cout << getRubles() << " rubles and " << getCopecks() << " copecks" << std::endl;
    }
};


class Complex : public Pair {
private:
    double real;
    double imaginary;

public:
    Complex(double r, double i) : real(r), imaginary(i) {}

    Pair* add(const Pair& other) const override {
        const Complex& otherComplex = dynamic_cast<const Complex&>(other);
        return new Complex(real + otherComplex.real, imaginary + otherComplex.imaginary);
    }

    Pair* subtract(const Pair& other) const override {
        const Complex& otherComplex = dynamic_cast<const Complex&>(other);
        return new Complex(real - otherComplex.real, imaginary - otherComplex.imaginary);
    }

    Pair* multiply(const Pair& other) const override {
        const Complex& otherComplex = dynamic_cast<const Complex&>(other);
        return new Complex(
            real * otherComplex.real - imaginary * otherComplex.imaginary,
            real * otherComplex.imaginary + imaginary * otherComplex.real
        );
    }

    Pair* divide(const Pair& other) const override {
        const Complex& otherComplex = dynamic_cast<const Complex&>(other);
        double denominator = otherComplex.real * otherComplex.real + otherComplex.imaginary * otherComplex.imaginary;
        if (denominator == 0) {
            std::cerr << "Error: Division by zero in Complex class." << std::endl;
            return nullptr; // You may handle division by zero differently based on your requirements
        }
        return new Complex(
            (real * otherComplex.real + imaginary * otherComplex.imaginary) / denominator,
            (imaginary * otherComplex.real - real * otherComplex.imaginary) / denominator
        );
    }

    void display() const override {
        std::cout << real << " + " << imaginary << "i" << std::endl;
    }
};
int main() {
    Money money1(10, 50);
    Money money2(5, 25);

    Complex complex1(3.0, 4.0);
    Complex complex2(1.5, 2.5);

    // Testing addition, subtraction, multiplication, and division for Money
    Pair* moneySum = money1.add(money2);
    Pair* moneyDiff = money1.subtract(money2);
    Pair* moneyProduct = money1.multiply(money2);
    Pair* moneyQuotient = money1.divide(money2);

    std::cout << "Money Sum: ";
    moneySum->display();
    std::cout << "Money Difference: ";
    moneyDiff->display();
    std::cout << "Money Product: ";
    moneyProduct->display();
    std::cout << "Money Quotient: ";
    moneyQuotient->display();

    // Testing addition, subtraction, multiplication, and division for Complex
    Pair* complexSum = complex1.add(complex2);
    Pair* complexDiff = complex1.subtract(complex2);
    Pair* complexProduct = complex1.multiply(complex2);
    Pair* complexQuotient = complex1.divide(complex2);

    std::cout << "Complex Sum: ";
    complexSum->display();
    std::cout << "Complex Difference: ";
    complexDiff->display();
    std::cout << "Complex Product: ";
    complexProduct->display();
    std::cout << "Complex Quotient: ";
    complexQuotient->display();

    // Don't forget to free the allocated memory
    delete moneySum;
    delete moneyDiff;
    delete moneyProduct;
    delete moneyQuotient;
    delete complexSum;
    delete complexDiff;
    delete complexProduct;
    delete complexQuotient;

    return 0;
}
