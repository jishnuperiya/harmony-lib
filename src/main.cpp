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
#include <cassert>					// For assert
#include <algorithm>                // For std::set_intersection	
#include <iostream>                 // For cout
#include <vector>                   // For std::vector
#include <array>                    // For std::array
#include "harmony.hpp"              // For pitch, frequency and note                                 
#include "chord.hpp"                // For harmony::chord
#include "progression.hpp"          // For harmony::chord_progression
#include "voicer.hpp"               // For generate_voicings
#include "note_set.hpp"             // For harmony::note_set

//****************************************************************************


int main(int, const char* [])
{
	using namespace harmony;

	std::vector<note> notes = { note("C"), note("E") };

	note_set ns1(notes.begin(), notes.end());

	ns1.insert(note("G"));

	for (const auto& n : ns1)
	{
		std::cout << n << std::endl;
	}
  return 0;
}



//****************************************************************************
