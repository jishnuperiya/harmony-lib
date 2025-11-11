#include "harmony.hpp"
#include <cassert> //for assert
#include <cmath> //for fabs
#include <stdexcept> //for std::inalid_argument
#include <array> //for std::array

std::array<const char*, 12> note_names = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};


harmony::note::note(uint8_t value)
  : note_{static_cast<uint8_t>(value % 12)} 
{}

uint8_t harmony::note::value() const {
  return note_;
}

std::string harmony::note::name() const
{
  return note_names[note_];
}

harmony::pitch harmony::note::get_pitch(int octave) const 
{
  int midi_val = (octave + 1) * 12 + note_;
  return pitch(midi_val);
}

harmony::frequency harmony::note::get_frequency(int octave) const 
{
  return get_pitch(octave).get_frequency();
}

harmony::note& harmony::note::transpose(int semitones)
{
  int new_val = static_cast<int>(note_) + semitones;
  new_val = ((new_val % 12) + 12) % 12; // proper wrapping for negatives
  note_ = static_cast<uint8_t>(new_val);
  return *this;
}
harmony::note harmony::operator+(harmony::note n, int semitones)
{
  n.transpose(semitones);
  return n;
}

int harmony::interval_in_semitones(note lhs, note rhs)
{
  return ((int)lhs.value() - (int)rhs.value() + 12) % 12;
}

bool harmony::is_octave_equivalent(note lhs, note rhs)
{
  return lhs.value() == rhs.value();
}

std::ostream& harmony::operator<<(std::ostream& os, note n)
{
  os << "Note{" << n.name() << "}";
  return os;
}
