//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent musical chords (root + quality + notes)
//*
//*
//****************************************************************************

#pragma once
#include "harmony.hpp" //for harmony::note
#include <vector> //for std::vector

namespace harmony 
{
  enum class chord_quality
  {
    Major = 0,
    Minor = 1,
    Diminished = 2,
    Augmented = 3
  };
// -------------------
// chord Class
// -------------------
  class chord
  {
  private:
    note root_;
    chord_quality quality_;
  public:
    chord(harmony::note, harmony::chord_quality);
    note root() const;
    chord_quality quality() const;
    std::string name() const;

    //generate list of pitches
    std::vector<note> get_notes() const;
    std::vector<pitch> get_pitches(int octave = 4) const;
  };
  std::ostream& operator<<(std::ostream& os, const chord& c);
}