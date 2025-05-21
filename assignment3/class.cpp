#include "class.h"
#include <iostream>

// Constructor
Complex::Complex() {
  real = 0;
  imag = 0;
}

// Constructor
Complex::Complex(double r, double i) {
  real = r;
  imag = i;
}

// Destructor
Complex::~Complex() {
  // No dynamic memory allocation, so no need to delete anything
}

// Check if the complex number is zero
bool Complex::checkZero() const { return real == 0 && imag == 0; }

// Getter
double Complex::getReal() const { return real; }

// Getter
double Complex::getImag() const { return imag; }

// Setter
void Complex::setReal(double r) { real = r; }

// Setter
void Complex::setImag(double i) { imag = i; }

// Operator overloading
Complex Complex::operator+(const Complex &other) const {
  return Complex(real + other.real, imag + other.imag);
}

// Operator overloading
Complex Complex::operator-(const Complex &other) const {
  return Complex(real - other.real, imag - other.imag);
}

// Operator overloading
Complex Complex::operator*(const Complex &other) const {
  return Complex(real * other.real - imag * other.imag,
                 real * other.imag + imag * other.real);
}

// Operator overloading
Complex Complex::operator/(const Complex &other) const {
  if (other.checkZero()) {
    std::cerr << "Error: Division by zero" << std::endl;
    return Complex();
  }
  double denominator = other.real * other.real + other.imag * other.imag;
  return Complex((real * other.real + imag * other.imag) / denominator,
                 (imag * other.real - real * other.imag) / denominator);
}

// Operator overloading
bool Complex::operator==(const Complex &other) const {
  return real == other.real && imag == other.imag;
}

// Operator overloading
bool Complex::operator!=(const Complex &other) const {
  return real != other.real || imag != other.imag;
}