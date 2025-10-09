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

#include "string.hpp"
#include <iostream> // For std::cout
#include <cstring> // For memcpy


string::string(const char* s) 
{
  length_ = std::strlen(s);
  data_ = new char[length_ + 1];
  std::strcpy(data_, s);
}

string::string(const string& other)
  : string(other.data_) // constructor chaining (delegates to main ctor)
{}

string& string::operator=(const string& other) 
{
  if (this != &other) 
  {
    delete[] data_;                
    length_ = other.length_;
    data_ = new char[length_ + 1];
    std::strcpy(data_, other.data_);
  }
  return *this;
}


string::~string()
{
  delete[] data_;
};




// //****************************************************************************

