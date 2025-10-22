#include "harmony.hpp"
#include <cassert> //for assert
#include <cmath> //for fabs
#include <stdexcept> //for std::inalid_argument

harmony::note::note(pitch p)
  :pitch_{p}, freq_{p.get_frequency()}
{
}

harmony::note::note(frequency f)
  :freq_{f}, pitch_{f.midi()}
{
}

harmony::pitch harmony::note::get_pitch()
{
  return pitch_;
}

harmony::frequency harmony::note::get_frequency()
{
  return freq_;
}

harmony::note& harmony::note::transpose(int semitones)
{
  pitch_+=semitones;
  double new_hz = freq_.hz() * std::pow(2.0, semitones / 12.0);
  freq_=harmony::frequency{new_hz};
  return *this;
}

harmony::note harmony::operator+(harmony::note n, int semitones)
{
  n.transpose(semitones);
  return n;
}

int harmony::interval_in_semitones(note lhs, note rhs)
{
  return lhs.get_pitch().get_midi() - rhs.get_pitch().get_midi();
}

bool harmony::is_octave_equivalent(note lhs, note rhs)
{
  int diff = std::abs(lhs.get_pitch().get_midi() - rhs.get_pitch().get_midi());
  return diff % 12 == 0;
}

std::ostream& harmony::operator<<(std::ostream& os, harmony::note n)
{
   os << "Note{" << harmony::name(n.get_pitch()) << ", "
      << n.get_frequency().hz() << " Hz}";
   return os;
}