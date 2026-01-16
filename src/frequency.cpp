//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::frequency`.
//*
//*
//****************************************************************************

#include <cassert>                                       // For assert
#include <cmath>                                         // For fabs
#include <stdexcept>                                     // For invalid_argument

#include "harmony.hpp"

//****************************************************************************
namespace harmony {
//****************************************************************************

/**
 * Construct a frequency from a postive real number of Hertz.
 *
 * @param hz Frequency in Hertz (default: 440.0 Hz)
 */
frequency::frequency(double hz)
         : hz_{hz}
{
  assert(hz_ > 0.0 && "frequency must stay positive");
}

/**
 * Return the underlying Frequency in Hertz.
 */
double frequency::get_hz() const
{
  return hz_;
}

/**
 * Return the nearest MIDI note numbeer.
 *
 * @see [Here](https://computermusicresource.com/midikeys.html)
 *      for more on MIDI note numbers.
 */
uint8_t frequency::get_midi() const
{
  return static_cast<uint8_t>(std::round(69 + 12 * std::log2(hz_ / 440.0)));
}

/**
 * Return the nearest even tempered pitch.
 *
 * @see [Here](...)
 *      for more on the even temperement tuning system.
 */
pitch frequency::get_pitch() const
{
  return pitch(get_midi());
}

frequency& frequency::operator*=(double delta_hz)
{
  hz_*=delta_hz;
  assert(hz_ > 0.0 && "frequency must stay positive");
  return *this;
}

frequency& frequency::operator/=(double delta_hz)
{
  hz_/=delta_hz;
  assert(hz_ > 0.0 && "frequency must stay positive");
  return *this;
}

frequency operator*(frequency lhs,double factor)
{
  return frequency(lhs.get_hz()*factor);
}

frequency operator/(frequency lhs,double factor)
{
  return frequency(lhs.get_hz()/factor);
}

bool is_octave_equivalent(frequency lhs, frequency rhs)
{
  // Octave equivalent if base-2 logarithm of the frequency ratio is an integer
  double freq_ratio = std::log2(lhs.get_hz()/rhs.get_hz());
  // Check if 'freq_ratio' is effectively an integer.
  return std::fabs(freq_ratio - std::round(freq_ratio)) < 1e-9;
}

std::ostream& operator<<(std::ostream& os, frequency f)
{
   return os << f.get_hz();
}

//****************************************************************************
} // namespace harmony
//****************************************************************************
