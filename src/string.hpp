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

struct string
{  
  public:
    string(const char* = "");
    string(const string&);
    string& operator=(const string&);
    ~string();
  private:
    char* data_ = nullptr;;
    std::size_t length_ = 0;
};




//****************************************************************************
