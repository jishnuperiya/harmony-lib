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
#include "harmony.hpp" // For pitch, frequency and note                                 

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

  using namespace harmony;

  // -----Test pitch-----
  pitch middle_c{60};
  pitch a4(69);

  std::cout <<"Middle C: MIDI note: " << middle_c.get_midi()
            <<", Frequency: " <<middle_c.get_frequency().hz() << ".Hz,"
            <<" Scientific Notation: " << name(middle_c) << std::endl;

  std::cout <<"A4: MIDI note: " << a4.get_midi()
            <<", Frequency: " <<a4.get_frequency().hz() << ".Hz,"
            <<" Scientific Notation: " << name(a4) << std::endl;

  std::cout << "Interval (A4 - C4): " << (a4 - middle_c) << " semitones"<< std::endl;
  std::cout << "Octave equivalent? "
            << is_octave_equivalent(a4, middle_c) << std::endl;

  // ---- Test frequency ----
  frequency f1(440.0);
  frequency f2(880.0);

  std::cout << "Frequencies: f1 = " << f1.hz() << " Hz, f2 = " << f2.hz() << " Hz" << std::endl;
  std::cout << "Are they octave equivalent? "
            << std::boolalpha <<is_octave_equivalent(f1, f2) << std::endl;

  // ---- Test note ----
  note n1(pitch(60)); // C4
  note n2 = n1 + 12;  // transpose by one otcave

  std::cout << n1 << "\n" << n2 << std::endl;
  
  std::cout << "Interval (n2 - n1): " << interval_in_semitones(n2, n1) << " semitones"<< std::endl;;
  std::cout << "Are n1 and n2 octave equivalent? "
            << std::boolalpha << is_octave_equivalent(n1, n2) << std::endl;;

  // -------------------------------------------


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
