class Complex {
private:
  double real;
  double imag;

  bool checkZero() const;

public:
  Complex();

  Complex(double, double);

  ~Complex();

  double getReal() const;

  double getImag() const;

  void setReal(double r);

  void setImag(double i);

  Complex operator+(const Complex &other) const;

  Complex operator-(const Complex &other) const;

  Complex operator*(const Complex &other) const;

  Complex operator/(const Complex &other) const;

  bool operator==(const Complex &other) const;

  bool operator!=(const Complex &other) const;
};