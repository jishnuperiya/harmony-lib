//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : wrapper class over std::set for musical notes
//*
//*
//****************************************************************************
#pragma once

#include<set>									// For std::set
#include<utility>							    // For std::pair
#include "harmony.hpp"							// For harmony::note

//****************************************************************************

namespace harmony
{
	class note_set_1
	{
	public:
	  /*using iterator = std::set<note>::iterator;
	  using const_iterator = std::set<note>::const_iterator;*/

	  note_set_1()
		: notes_{ 0 } 
	  {
	  }
		
	  template <typename InputIt>
	  note_set_1(InputIt b, InputIt e)
		: notes_(0)
	  {
		for (auto it = b; it != e; ++it)
		{
		  insert(*it);
		}
	  }

	  void insert(const note& n)
	  {
		notes_ |= uint16_t(1) << n.value();
	  }

	  void erase(const note& n)
	  {
		notes_ &= ~ (uint16_t(1) << n.value());
	  }

	  bool contains(const note& n) const 
	  {
		uint16_t mask = uint16_t(1) << n.value();
		return (notes_ & mask) != 0;
	  }

	  bool find(const note& n)
	  {
		return contains(n);
	  }

	
	private:
	  std::uint16_t notes_;

	 /* std::bitset<12> bits_;*/
	};
}