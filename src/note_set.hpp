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
	class note_set
	{
	public:
	  using iterator = std::set<note>::iterator;
	  using const_iterator = std::set<note>::const_iterator;

	  note_set() = default;
		
	  template <typename InputIt>
	  note_set(InputIt b, InputIt e)
		: notes_(b,e){}

	  std::pair<iterator, bool> insert(const note& n)
	  {
	    return notes_.insert(n);
	  }

	  std::size_t erase(const note& n)
	  {
	    return notes_.erase(n);
	  }

	  iterator find(const note& n)
	  {
        return notes_.find(n);
	  }

	  bool  contains(const note& n)
	  {
		return notes_.contains(n);
   	  }
	  
	  iterator begin()
	  {
		return notes_.begin();
	  }

	  const_iterator begin() const
	  {
		return notes_.begin();
   	  }

	  const_iterator cbegin() noexcept
	  {
		return notes_.cbegin();
	  }

	  iterator end()
	  {
		  return notes_.end();
	  }

	  const_iterator end() const
	  {
		return notes_.end();
	  }

	  const_iterator cend() noexcept
	  {
		return notes_.cend();
	  }
	
	private:
	  std::set<note> notes_;
	};
}