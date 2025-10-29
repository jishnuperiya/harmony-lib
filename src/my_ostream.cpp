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
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> //for std::fputc, std::fputs
//****************************************************************************
class my_streambuf
{
public:
  virtual void put_char(char c) = 0;
};

class my_consolebuf : public my_streambuf
{
public:
  void put_char(char c) override 
  {
  std::fputc(c, stdout); //stdout is standard output stream, by default it's the console
  std::fflush(stdout); //flush the output buffer to make sure the character appears immediately
  }
};

class my_filebuf : public my_streambuf
{
private:
  FILE* file_ = nullptr;
public:
  my_filebuf(const char* filename) 
  {
	  file_ = std::fopen(filename, "w"); //file_ is a handle returned by fopen
  }

  ~my_filebuf() {if (file_) std::fclose(file_);}

  void put_char(char c) override
  {
   	if (file_) 
	{
	  std::fputc(c, file_);
	  std::fflush(file_);
	}
  }
};

class my_ostream
{
private:
  my_streambuf* buf_ = nullptr; // bridge to my_streambuf class
public:
  my_ostream(my_streambuf* buf = nullptr) : buf_(buf) {};
  
  void insert(char c)
  {
   	if(buf_) buf_->put_char(c);
  }

  my_ostream& operator<<(char c)
  {
	insert(c);
	return *this;
  }
};



//****************************************************************************
