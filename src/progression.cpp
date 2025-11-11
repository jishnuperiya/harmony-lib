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
#include "progression.hpp"

using namespace harmony;

chord_progression::chord_progression() = default;

chord_progression::chord_progression(std::vector<chord> chords)
  : chords_{chords} {}

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