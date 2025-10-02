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
#include <iostream> // For std::cout


Complex::Complex(double real_, double imag_) 
  : real_{real_}, imag_{imag_}
{
  std::cout << "Constructor\n";
}

Complex::Complex(const Complex& other)
  : real_{other.real_}, imag_{other.imag_}
{
  std::cout << "Copy constructor\n";
}

Complex& Complex::operator=(const Complex& other)
{
  std::cout << "Copy assignment\n";
  
  if(this!=&other)
  {
    real_=other.real_;
    imag_=other.imag_;
  }
  return *this;
}

Complex::~Complex()
{
  std::cout << "Destructor\n";
}

//****************************************************************************
