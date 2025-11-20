#include "harmony.hpp"
#include <cassert> //for assert
#include <cmath> //for fabs
#include <stdexcept> //for std::inalid_argument

namespace harmony
{

inline int note_index_from_name(std::string_view s)
{
  for (auto const& [name, index] : ENHARMONIC_NAMES)
  {
    if (s == name)
      return index;
  }
  throw std::invalid_argument("Invalid note name");
}

  note::note(uint8_t value)
    : note_{static_cast<uint8_t>(value % 12)} 
  {}

  note::note(std::string_view s)
	  : note_{ static_cast<uint8_t>(note_index_from_name(s))}
  { }

  uint8_t note::value() const 
  {
    return note_;
  }

  std::string note::name() const
  {
    return NOTE_NAMES[note_];
  }

  pitch note::get_pitch(int octave) const 
  {
    return pitch((octave + 1) * 12 + note_);
  }

  frequency note::get_frequency(int octave) const 
  {
    return get_pitch(octave).get_frequency();
  }

  note& note::transpose(int semitones)
  {
    note_ = static_cast<uint8_t>((((int)note_ + semitones) % 12 + 12) % 12);
    return *this;

    /*int new_val = (int(note_) + semitones) % 12;
    if (new_val < 0) new_val += 12;
    note_ = uint8_t(new_val);
    return *this;*/
  }

  note operator+(note n, int semitones)
  {
    return n.transpose(semitones);
  }

  int interval_in_semitones(note lhs, note rhs)
  {
    return ((int)lhs.value() - (int)rhs.value() + 12) % 12;
  }

  bool is_octave_equivalent(note lhs, note rhs)
  {
    return lhs.value() == rhs.value();
  }

  std::ostream& operator<<(std::ostream& os, note n)
  {
    return os << n.name();
  }

}
