/*
К уже существующему проекту класса "Дробь" добавьте механизмы сохранения / загрузки 
данных класса. Используйте механизм потоков для файловых операций.
*/
#include <iostream>
#include <fstream>
using namespace std;

class Fraction {
    int numerator;
    int denominator;

public:
    Fraction() : numerator(0), denominator(1) {}  
    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            cerr << "Denominator cannot be zero. Setting to 1." << endl;
            denominator = 1;
        }
    }

    void show() const {
        cout << numerator << "/" << denominator << endl;
    }

    void save(const string& filename) const {
        ofstream file(filename, ios::binary | ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&numerator), sizeof(numerator));
            file.write(reinterpret_cast<const char*>(&denominator), sizeof(denominator));
            file.close();
        }
        else {
            cerr << "Error opening file for writing" << endl;
        }
    }

    void load(const string& filename) {
        ifstream file(filename, ios::binary | ios::in);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&numerator), sizeof(numerator));
            file.read(reinterpret_cast<char*>(&denominator), sizeof(denominator));
            file.close();
            if (denominator == 0) {
                cerr << "Loaded denominator cannot be zero. Setting to 1." << endl;
                denominator = 1;
            }
        }
        else {
            cerr << "Error opening file for reading" << endl;
        }
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            cerr << "Cannot divide by zero fraction." << endl;
            return Fraction(0, 1);
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    Fraction& operator++() {
        numerator++;
        denominator++;
        return *this;
    }

    Fraction operator++(int) { 
        Fraction temp = *this;
        numerator++;
        denominator++;
        return temp;
    }

    friend ostream& operator<<(ostream& out, const Fraction& f);
    friend istream& operator>>(istream& in, Fraction& f);
};

ostream& operator<<(ostream& out, const Fraction& f) {
    out << f.numerator << "/" << f.denominator;
    return out;
}

istream& operator>>(istream& in, Fraction& f) {
    cout << "Enter numerator: ";
    in >> f.numerator;
    cout << "Enter denominator: ";
    in >> f.denominator;
    if (f.denominator == 0) {
        cerr << "Denominator cannot be zero. Setting to 1." << endl;
        f.denominator = 1;
    }
    return in;
}

int main() {
    string file_name = "fraction.dat";

    // Сохранение данных дроби в файл
    Fraction frac1(12, 3); 
    frac1.save(file_name);
    cout << "Saved Fraction: " << frac1 << endl;

    // Загрузка данных дроби из файла
    Fraction frac2;
    frac2.load(file_name);
    cout << "Loaded Fraction: " << frac2 << endl;

    // Примеры операций с дробями
    Fraction frac3(1, 2);
    Fraction frac4(1, 3);

    cout << "frac3 + frac4 = " << frac3 + frac4 << endl;
    cout << "frac3 - frac4 = " << frac3 - frac4 << endl;
    cout << "frac3 * frac4 = " << frac3 * frac4 << endl;
    cout << "frac3 / frac4 = " << frac3 / frac4 << endl;

    // Инкремент
    cout << "frac3++ = " << frac3++ << endl;
    cout << "After frac3++: " << frac3 << endl;
    cout << "++frac3 = " << ++frac3 << endl;
    cout << "After ++frac3: " << frac3 << endl;

    return 0;
}
