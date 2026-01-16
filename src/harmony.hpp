//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represents the fundamental elements of harmony as value types.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <string>                                        // For std::string
#include <cstdint>                                       // For uint8_t
#include <ostream>                                       // For std::ostream
#include <array>                                         // For std::array
#include <string_view>                                   // For std::string_view
#include <utility>                                       // For std::pair

//****************************************************************************
namespace harmony {
//****************************************************************************

class frequency;
class pitch;
class note;

/**
* Canonical names for the 12 pitch classes.
*/
inline constexpr std::array<const char*, 12> NOTE_NAMES =
{{"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}};

/**
 * Represents a musical pitch using MIDI notation
 *
 * A pitch is internally stored as a MIDI note number and provides conversions
 * to frequency and note representations.
 */
class pitch
{
public:
  /**
  * Construct a pitch from a MIDI note number
  * @param midi_note MIDI note number (default: middle C = 60)
  */
              pitch(int midi_note = 60);

  /**
  * Construct a pitch from a frequency
  */
              pitch(frequency);

  /** @return MIDI note number */
  uint8_t     get_midi()                  const;

  /** @return Frequency corresponding to this pitch */
  frequency   get_frequency()             const;

  /** @return Pitch class (note without octave) */
  note        get_note()                  const;

  /**
   * Transpose pitch upward
   * @param semitones Number of semitones
   */
  pitch&      operator+=(int semitones);

  /**
   * Transpose pitch downward
   * @param semitones Number of semitones
   */
  pitch&      operator-=(int semitones);

private:
  uint8_t     midi_note_;
};

/** Transpose pitch upward */
pitch         operator+(pitch lhs, int semitones);

/** Transpose pitch downward */
pitch         operator-(pitch lhs, int semitones);

/** Interval between two pitches in semitones */
int           operator-(pitch lhs, pitch rhs);

/** Check octave equivalence between two pitches */
bool          is_octave_equivalent(pitch lhs, pitch rhs);

/** Stream output for pitch */
std::ostream& operator<<(std::ostream& os, pitch p);

/** Get octave number of a pitch */
uint8_t       octave(pitch p);

/** Get string name of a pitch (e.g., "C4") */
std::string   name(pitch p);

/**
 * Represents an audio frequency as a real number of Hertz.
 *
 * @see [Here](https://en.wikipedia.org/wiki/Audio_frequency)
 *      for more on audio frequencies.
 *
 * @see [Here](https://en.wikipedia.org/wiki/Hertz)
 *      for more on the Hertz unit.
 */
class frequency
{
public:        // Construction
                  frequency(double hz = 440.0);

public:        // Operations
  double          get_hz()                    const;
  uint8_t         get_midi()                  const;
  pitch           get_pitch()                 const;
  frequency&      operator*=(double δ);
  frequency&      operator/=(double δ);

private:       // Representation
  double          hz_;
};

frequency         operator*(frequency, double);
frequency         operator/(frequency, double);
bool              is_octave_equivalent(frequency, frequency);
std::ostream&     operator<<(std::ostream&, frequency);

/** Represents a musical note (pitch class) */
class note
{
public:

  /** Construct note from value (0-11) */
  explicit   note(uint8_t value=0);

  /** Construct note from name (e.g., "C#", "D") */
  explicit   note(std::string_view name);

  /** @return Note value (0-11) */
  uint8_t     value()                     const;

  /** @return Note name (e.g., "C#", "D") */
  std::string name()                      const;

  /** @return Pitch at given octave */
  pitch       get_pitch(int octave)       const;

  /** @return Frequency at given octave */
  frequency   get_frequency(int octave)   const;

  /** Transpose note by semitones */
  note&       transpose(int semitones);

  /** Transpose note by semitones */
  note&       operator+=(int);

private:
  uint8_t     note_;
};

note          operator+(note, int semitones);
bool          operator<(note, note);
bool 		      operator==(note, note);
int           interval_in_semitones(note, note);
bool          is_octave_equivalent(note, note);
std::ostream& operator<<(std::ostream&, note);

//****************************************************************************
} // namespace harmony
//****************************************************************************
