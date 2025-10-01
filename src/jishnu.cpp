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

#include <iostream>                                      // For cout

#include "complex.hpp"                                   // For example

//****************************************************************************


// function taking Complex by value
void takeByValue(Complex x)
{
  std::cout << "Inside takeByValue()\n";
}

// function returning Complex by value
Complex makeComplex()
{
  Complex tmp(10.0, 20.0);
  return tmp;
}

int main(int argc, const char* argv[])
{

  std::cout << "---- Default construction ----\n";
  Complex a; // default ctor

  std::cout << "---- Non-default construction ----\n";
  Complex b(3.0, 4.0); // non-default ctor

  std::cout << "---- Copy construction ----\n";
  Complex c = b; // copy ctor

  std::cout << "---- Copy assignment ----\n";
  a = b; // copy assignment

  std::cout << "---- Pass by value ----\n";
  takeByValue(b); // copy ctor (to make parameter x)

  std::cout << "---- Return by value ----\n";
  Complex d = makeComplex(); // copy ctor

  std::cout << "---- End of main ----\n";
  return 0;
}

//****************************************************************************
