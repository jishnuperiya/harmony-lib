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

#include <iostream>    // For cout

#include "complex.hpp" // For complex
#include "string.hpp" // For string                                 

//****************************************************************************


// function taking Complex by reference
void takeByReference(const Complex& x)
{
  std::cout << "Inside takeByValue()\n";
}

// function taking string by reference
void takeByReference(const string& x)
{
  std::cout << "Inside takeByReference()\n";
}

// function returning Complex by value
Complex makeComplex()
{
  return Complex(10.0, 20.0);
}

// function returning string by value
string makeString()
{
  return string{"returned_string"};
}
int main(int argc, const char* argv[])
{

  std::cout << "---- Default construction ----\n";
  string a; // default ctor

  std::cout << "---- Non-default construction ----\n";
  string b("hello"); // non-default ctor
  string b2{"hello"};  
  string b3 = string("hello");  
  string b4 = string{"hello"};


  std::cout << "---- Copy construction ----\n";
  string c = a; // copy ctor

  std::cout << "---- Copy assignment ----\n";
  a = b; // copy assignment

  std::cout << "---- Pass by value ----\n";
  takeByReference(b); // copy ctor (to make parameter x)

  std::cout << "---- Return by value ----\n";
  string d = makeString(); // copy ctor

  std::cout << "---- End of main ----\n";
  return 0;
}



//****************************************************************************
