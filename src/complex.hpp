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
#pragma once
#include <iostream>
//****************************************************************************

struct Complex
{
  private:
    double real;
    double imag;
  public:
    //default constructor
    Complex();
    //non-default constructor
    Complex(double, double);
    //copy constructor
    Complex(const Complex&);
    //copy assignment operator
    Complex& operator=(const Complex&);
    //destructor
    ~Complex();
};

//****************************************************************************
