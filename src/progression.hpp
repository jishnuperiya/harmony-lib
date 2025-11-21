//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent musical chord progression
//*
//*
//****************************************************************************

#pragma once
#include "chord.hpp" //for harmony::chord
#include <vector> //for std::vector

namespace harmony
{
  class chord_progression
  {
  private:
	std::vector<chord> chords_;
    public:
	  chord_progression();
	  template<typename container>
	  chord_progression(const container& chords)
	    : chords_{std::begin(chords),std::end(chords)} {}
	  // Explicit overload for brace-init syntax
	 // //chord_progression(std::initializer_list<chord> chords)
		//: chords_{ chords } {}
	  void add(const chord& c);
	  const std::vector<chord>& chords() const;
  };

  std::ostream& operator<<(std::ostream& os, const chord_progression& p);
}