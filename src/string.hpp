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
#include <cstddef>   // for std::size_t
//****************************************************************************

struct string
{  
  public:
    string(const char* = "");
    string(const string&);
    string& operator=(const string&);
    ~string();
  private:
    char* data_ = nullptr;
    std::size_t length_ = 0;
};




//****************************************************************************
