#include "harmony.hpp"
#include <cassert> //for assert
#include <cmath> //for fabs
#include <stdexcept> //for std::inalid_argument

harmony::frequency::frequency(double hz)
  : hz_{hz}
{
  if (hz <= 0.0) 
  {
    throw std::invalid_argument("Frequency must be a positive number.");
  }
}

double harmony::frequency::get_hz() const
{
  return hz_;
}

uint8_t harmony::frequency::get_midi() const
{
  return static_cast<uint8_t>(std::round(69 + 12 * std::log2(hz_ / 440.0)));
}

harmony::pitch harmony::frequency::get_pitch() const
{
  // Convert to nearest MIDI note number.
  int midi_val = static_cast<int>(std::round(69 + 12 * std::log2(hz_ / 440.0)));

  return pitch(midi_val);
}

harmony::frequency& harmony::frequency::operator+=(double delta_hz)
{
  hz_+=delta_hz;
  if (hz_ <= 0.0) 
  {
    throw std::invalid_argument("Frequency mutation resulted in negative value.");
  }
  return *this;
}

harmony::frequency& harmony::frequency::operator-=(double delta_hz)
{
  hz_-=delta_hz;
  if (hz_ <= 0.0) 
  {
    throw std::invalid_argument("Frequency mutation resulted in negative value.");
  }
  return *this;
}

harmony::frequency harmony::operator*(harmony::frequency lhs,double factor)
{
  return harmony::frequency(lhs.get_hz()*factor);
}

harmony::frequency harmony::operator/(harmony::frequency lhs,double factor)
{
  return harmony::frequency(lhs.get_hz()/factor);  
}

bool harmony::is_octave_equivalent(frequency lhs, frequency rhs)
{
  // Octave equivalent if base-2 logarithm of the frequency ratio is an integer
  double freq_ratio = std::log2(lhs.get_hz()/rhs.get_hz());
  // Check if 'freq_ratio' is effectively an integer.
  return std::fabs(freq_ratio - std::round(freq_ratio)) < 1e-9;
}

std::ostream& harmony::operator<<(std::ostream& os, harmony::frequency f)
{
   os << f.get_hz();
   return os;
}