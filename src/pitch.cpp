#include "harmony.hpp"
#include <cmath> //for std::pow
#include <cassert> //for assert
#include <stdexcept> //for std::inalid_argument

harmony::pitch::pitch(int midi_note)
  : midi_note_{static_cast<uint8_t>(midi_note)}
{
  if (midi_note < 0 || midi_note > 127)
  {
    throw std::out_of_range("MIDI note value must be between 0 and 127");
  }
}

int harmony::pitch::get_midi() const
{
  return midi_note_;
}

harmony::frequency harmony::pitch::get_frequency() const
{
    double freq = 440.0 * std::pow(2.0, (midi_note_ - 69) / 12.0);
    return harmony::frequency(freq);
}

harmony::pitch& harmony::pitch::operator+=(int semitones)
{ 
  int new_note = static_cast<int>(midi_note_)+semitones;
  midi_note_=static_cast<uint8_t>(new_note);
  return *this;        
}

harmony::pitch& harmony::pitch::operator-=(int semitones)
{ 
  int new_note = static_cast<int>(midi_note_)-semitones;
  midi_note_=static_cast<uint8_t>(new_note);
  return *this;        
}

harmony::pitch operator+(harmony::pitch lhs, int semitones) 
{
  lhs+=semitones;
  return lhs; 
}

harmony::pitch operator-(harmony::pitch lhs, int semitones)
{
  lhs-=semitones;
  return lhs; 
}

int harmony::operator-(harmony::pitch lhs, harmony::pitch rhs)
{
  return lhs.get_midi()-rhs.get_midi();
}

bool harmony::is_octave_equivalent(harmony::pitch lhs, harmony::pitch rhs)
{
  bool is_octave_eq = (lhs.get_midi()-rhs.get_midi())/12; 
  return is_octave_eq;
}

uint8_t harmony::octave(harmony::pitch p)
{
 return static_cast<uint8_t>((p.get_midi()/12) -1);  
}


std::string harmony::name(harmony::pitch p)
{
  char* note_names[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
  int note_idx = p.get_midi() % 12;
  std::string note_name = note_names[note_idx];
  std::string scientific_notation = note_name + std::to_string(harmony::octave(p));
  return scientific_notation;
}

std::ostream& harmony::operator<<(std::ostream& os, harmony::pitch p)
{
    os << "Pitch{" << p.get_midi() << " " << harmony::name(p) << "}";
    return os;
}