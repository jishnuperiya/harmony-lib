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
		chord_progression(std::vector<chord> chords);

		void add(const chord& c);
		const std::vector<chord>& chords() const;
  };

	std::ostream& operator<<(std::ostream& os, const chord_progression& p);
}