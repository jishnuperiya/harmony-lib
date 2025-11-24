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

#include <iostream>                 // For cout
#include <array>                    // For std::array
#include "harmony.hpp"              // For pitch, frequency and note                                 
#include "chord.hpp"                // For harmony::chord
#include "progression.hpp"          // For harmony::chord_progression
#include "voicer.hpp"               // For generate_voicings

//****************************************************************************


int main(int , const char* [])
{
  using namespace harmony;

  std::vector<note> notes1 = { note("C"), note("E"), note("G") };
  std::vector<note> notes2 = { note("G"), note("B"), note("D") };
  std::vector<note> notes3 = { note("B"), note("D"), note("F") };

  chord c1(note("C"), notes1.begin(), notes1.end());
  chord c2(note("G"), notes2.begin(), notes2.end());
  chord c3(note("B"), notes3.begin(), notes3.end());

  std::array<chord,3> vec_chords = { c1, c2, c3 };
  chord_progression progression(vec_chords.begin(), vec_chords.end());
  std::cout << "Chord Progression:\n" << progression << "\n";

 auto voicing = generate_voicings(progression, 4);

 for (const auto& chord_voicing : voicing)
 {
     for (const auto& p : chord_voicing)
     {
         std::cout << p << " ";
     }
     std::cout << "\n";
 }

  return 0;
}



//****************************************************************************
