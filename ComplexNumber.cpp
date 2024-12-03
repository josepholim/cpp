#include <iostream>

class ComplexNumber {
public:
  ComplexNumber(double real = 0.0, double imag = 0.0) : real(real), imag(imag) {}

  // Overloaded addition operator
  ComplexNumber operator+(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imag + other.imag);
  }

  // Overloaded subtraction operator
  ComplexNumber operator-(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imag - other.imag);
  }

  // Overloaded multiplication operator
  ComplexNumber operator*(const ComplexNumber& other) const {
    double newReal = real * other.real - imag * other.imag;
    double newImag = real * other.imag + imag * other.real;
    return ComplexNumber(newReal, newImag);
  }

  // Overloaded division operator
  ComplexNumber operator/(const ComplexNumber& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    double newReal = (real * other.real + imag * other.imag) / denominator;
    double newImag = (imag * other.real - real * other.imag) / denominator;
    return ComplexNumber(newReal, newImag);
  }

  // Overloaded output stream operator
  friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& number) {
    os << number.real << " + " << number.imag << "i";
    return os;
  }

private:
  double real;
  double imag;
};

int main() {
  ComplexNumber c1(2, 3);
  ComplexNumber c2(4, 5);

  ComplexNumber sum = c1 + c2;
  ComplexNumber difference = c1 - c2;
  ComplexNumber product = c1 * c2;
  ComplexNumber quotient = c1 / c2;

  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Difference: " << difference << std::endl;
  std::cout << "Product: " << product << std::endl;
  std::cout << "Quotient: " << quotient << std::endl;

  return 0;
}