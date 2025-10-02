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
//****************************************************************************

struct Complex
{
  public:
    Complex(double  = 0.0, double  = 0.0);
    Complex(const Complex&);
    Complex& operator=(const Complex&);
    ~Complex();
  private:
    double real_;
    double imag_;
};


//****************************************************************************
