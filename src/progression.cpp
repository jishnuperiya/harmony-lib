//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent musical chord progression
//*
//*
//****************************************************************************

#include "progression.hpp"                               // For chord_progression

//****************************************************************************

using namespace harmony;

void chord_progression::add(const chord& c)
{
  chords_.push_back(c);
}

const std::vector<chord>& chord_progression::chords() const
{
  return chords_;
}

std::ostream& harmony::operator<<(std::ostream& os, const chord_progression& p)
{
  for (const auto& c : p.chords())
  {
	os << c << " ";
  }
  return os;
}

//****************************************************************************
