#include <map>
#include <sstream>
#include "chord.hpp"

using namespace harmony;

note chord::root() const { return root_; }

std::string chord::name() const 
{ 
  std::ostringstream o;
  o << root_;
  // Add quality implementation later
  
  /*switch (quality_)
  {
  case chord_quality::Major:
      break;
  case chord_quality::Minor:
      o << '-';
      break;
  case chord_quality::Diminished:
      o << 'o';
      break;
  case chord_quality::Augmented:
      o << '+';
      break;
  }*/
  return o.str();
}

std::vector<note> chord::get_notes() const
{

	std::vector<note> result;
	result.reserve(12);

    for (int pc = 0; pc < 12; ++pc)
    {
        if (notes_[pc]) {
            result.emplace_back(NOTE_NAMES[pc]); 
        }
    }

return result;
}

std::vector<pitch> chord::get_pitches(int octave) const
{

    std::vector<pitch> result;
    auto notes = get_notes();

    result.reserve(notes.size());

    for (auto it = notes.begin(); it != notes.end(); ++it)
    {
        result.emplace_back(it->get_pitch(octave));
    }

    return result;
}

std::ostream& harmony::operator<<(std::ostream& os, const chord& c) {
  os << c.name();
  return os;
}
