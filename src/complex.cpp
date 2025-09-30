//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose :
//*
//*
//****************************************************************************

#include "complex.hpp"


Complex::Complex():real{0}, imag{0}
{
   std::cout << "Default constructor\n";
}

Complex::Complex(double real, double imag) : real{real}, imag{imag}
{
   std::cout << "Explicit constructor\n";
}

Complex::Complex(const Complex& other) : real{other.real}, imag{other.imag}
{
   std::cout << "Copy constructor\n";
}

Complex& Complex::operator=(const Complex& other)
{
  std::cout << "Copy Assignment Operator\n";

  real=other.real;
  imag=other.imag;

  return *this;
}

Complex::~Complex()
{
  std::cout << "Destructor\n";
}
//****************************************************************************
