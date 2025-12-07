
#include <cassert>                  //for assert
#include <cmath>                    //for fabs
#include <stdexcept>                //for std::inalid_argument
#include "harmony.hpp"              //for harmony::note

namespace harmony{
namespace {

  note note_from_name(std::string_view s)
  {
    for (auto const& [name, n] : std::initializer_list<std::pair<std::string_view, note>>{
      
      {"C", note(0)},  {"B#", note(0)},
      {"C#", note(1)}, {"Db", note(1)},
      {"D", note(2)},
      {"D#", note(3)}, {"Eb", note(3)},
      {"E", note(4)},  {"Fb", note(4)},
      {"F", note(5)},  {"E#", note(5)},
      {"F#", note(6)}, {"Gb", note(6)},
      {"G", note(7)},
      {"G#", note(8)}, {"Ab", note(8)},
      {"A", note(9)},
      {"A#", note(10)}, {"Bb", note(10)},
      {"B", note(11)}, {"Cb", note(11)}
})
    {
        if (s == name)
            return n;
    }
    throw std::invalid_argument("Invalid note name");
  }
}
  note::note(uint8_t value)
    : note_{static_cast<uint8_t>(value % 12)} 
  {}

  note::note(std::string_view s)
	  : note (note_from_name(s))
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
  }

  note& note::operator+=(int semitones)
  {
    return transpose(semitones);
  }

  note operator+(note n, int semitones)
  {
    return n.transpose(semitones);
  }

  bool operator<(note lhs, note rhs)
  {
    return lhs.value() < rhs.value();
  }

  bool operator==(note lhs, note rhs)
  {
    return lhs.value() == rhs.value();
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
