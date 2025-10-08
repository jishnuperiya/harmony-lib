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
    string(const char* = nullptr);
    string(const string&);
    string& operator=(const string&);
    ~string();
  private:
    char* data_ = nullptr;;
    unsigned long long length_ = 0;
};

unsigned long long my_strlen(const char* s);



//****************************************************************************
