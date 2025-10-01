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
  public:
    Complex();
    Complex(double, double);
    Complex(const Complex&);
    Complex& operator=(const Complex&);
    ~Complex();
  private:
    double real_;
    double imag_;
};


//****************************************************************************
