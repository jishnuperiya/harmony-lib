#include "harmony.hpp"

#include <cmath>            //for std::pow
#include <cassert>          //for assert
#include <stdexcept>        //for std::inalid_argument
#include <sstream>          //for std::ostringstream
#include <array>            //for std::array

namespace harmony
{
  pitch::pitch(int midi_note)
    : midi_note_{ static_cast<uint8_t>(midi_note) }
  {
    assert(midi_note >= 0 && midi_note <= 127);
  }

  pitch::pitch(frequency freq)
    : midi_note_{ freq.get_pitch().get_midi() }
  {
  }

  uint8_t pitch::get_midi() const
  {
    return midi_note_;
  }

  frequency pitch::get_frequency() const
  {
    return frequency(440.0 * std::pow(2.0, (midi_note_ - 69) / 12.0));
  }

  note pitch::get_note() const
  {
    return note(static_cast<uint8_t>(midi_note_ % 12));
  }

  pitch& pitch::operator+=(int semitones)
  {
    midi_note_ = static_cast<uint8_t>(midi_note_ + semitones);
    return *this;
  }

  pitch& pitch::operator-=(int semitones)
  {
    midi_note_ = static_cast<uint8_t>(midi_note_ - semitones);
    return *this;
  }

  pitch operator+(pitch lhs, int semitones)
  {
    return lhs += semitones;
  }

  pitch operator-(pitch lhs, int semitones)
  {
    return lhs -= semitones;
  }

  int operator-(pitch lhs, pitch rhs)
  {
    return lhs.get_midi() - rhs.get_midi();
  }

  bool is_octave_equivalent(pitch lhs, pitch rhs)
  {
      return ((lhs.get_midi() - rhs.get_midi()) % 12) == 0;
  }

  uint8_t octave(pitch p)
  {
    return static_cast<uint8_t>((p.get_midi() / 12) - 1);
  }


  std::string name(pitch p)
  {
    std::ostringstream os;
	os << NOTE_NAMES[static_cast<std::array<const char*, 12>::size_type>(p.get_midi() % 12)] << static_cast<int>(octave(p));
   
    return os.str();
  }

  std::ostream& operator<<(std::ostream& os, pitch p)
  {
    return os << name(p);
  }
}