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

unsigned long long my_strlen(const char* s)
{
    unsigned long long length_ = 0;
    while (s[length_] != '\0')
      ++length_;
    return length_;
}

string::string(const char* data)
  :data_{nullptr}, length_{0}
{
  std::cout << "Constructor" <<std::endl;
  if(data) length_= my_strlen(data);
  data_ = new char[length_+1];
  memcpy(data_,data,length_);
  data_[length_] = '\0';
};



string::string(const string& other)
  :data_{nullptr},length_{other.length_}
{
  std::cout << "Copy Constructor" <<std::endl;
  data_=new char[length_+1];
  memcpy(data_,other.data_,length_);
  data_[length_] = '\0';
};


string& string::operator=(const string& other)
{
  if(this == &other) return *this;
  length_=other.length_;
  delete[] data_;
  data_=new char[length_+1]; 
  memcpy(data_,other.data_,length_);
  data_[length_] = '\0';
  return *this;
};


string::~string()
{
  delete[] data_;
};




// //****************************************************************************

