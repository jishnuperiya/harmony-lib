/**
 * @file harmony.hpp
 * @brief Pitch, frequency, and note abstractions for music theory
 *
 * This header defines lightweight value types representing musical
 * pitches, frequencies, and notes, along with common operations such
 * as transposition, comparison, and conversion.
 *
 * Copyright © 2025 Jishnu Periya, Jonathon Bell.
 * All rights reserved.
 */

#pragma once
#include <string>           //For std::string
#include <cstdint>          //For uint8_t
#include <ostream>          //For std::ostream
#include <array>            //For std::array
#include <string_view>      //For std::string_view
#include <utility>          //For std::pair

//****************************************************************************

/**
 * @namespace harmony
 * @brief Core music theory types and utilities
 */
namespace harmony {

  class frequency;
  class pitch;
  class note;

  /**
  * @brief Canonical names of the 12 pitch classes
  */
  inline constexpr std::array<const char*, 12> NOTE_NAMES = 
  {{
    "C", "C#", "D", "D#", "E", "F",
    "F#", "G", "G#", "A", "A#", "B"
  }};
  
  /**
  * @brief Represents a musical pitch using MIDI notation
  *
  * A pitch is internally stored as a MIDI note number and provides
  * conversions to frequency and note representations.
  */
  class pitch 
  {
  public:
    /**
    * @brief Construct a pitch from a MIDI note number
    * @param midi_note MIDI note number (default: middle C = 60)
    */
                pitch(int midi_note = 60);
    
    /**
    * @brief Construct a pitch from a frequency
    */
                pitch(frequency);
    
    /** @return MIDI note number */
    uint8_t     get_midi()                  const;
    
    /** @return Frequency corresponding to this pitch */
    frequency   get_frequency()             const;
    
    /** @return Pitch class (note without octave) */
    note        get_note()                  const;

    /**
     * @brief Transpose pitch upward
     * @param semitones Number of semitones
     */
    pitch&      operator+=(int semitones);

    /**
     * @brief Transpose pitch downward
     * @param semitones Number of semitones
     */
    pitch&      operator-=(int semitones);

  private:
    uint8_t     midi_note_;  
  };
    
  /** @brief Transpose pitch upward */
  pitch         operator+(pitch lhs, int semitones);

  /** @brief Transpose pitch downward */
  pitch         operator-(pitch lhs, int semitones);

  /** @brief Interval between two pitches in semitones */
  int           operator-(pitch lhs, pitch rhs);

  /** @brief Check octave equivalence between two pitches */
  bool          is_octave_equivalent(pitch lhs, pitch rhs);

  /** @brief Stream output for pitch */
  std::ostream& operator<<(std::ostream& os, pitch p);

  /** @brief Get octave number of a pitch */
  uint8_t       octave(pitch p); 
  
  /** @brief Get string name of a pitch (e.g., "C4") */
  std::string   name(pitch p);

  /** @brief Represents a frequency in Hertz */
  class frequency 
  {
  public:
    /** @brief Construct frequency from Hertz */
                frequency(double hz = 440.0);
   
    /** @return Frequency in Hertz */
    double      get_hz()                    const;
    
    /** @return Corresponding MIDI note number */
    uint8_t     get_midi()                  const;

    /** @return Corresponding pitch */
    pitch       get_pitch()                 const;

    /** @brief Increase frequency by delta_hz */
    frequency&  operator*=(double delta_hz);
    
    /** @brief Decrease frequency by delta_hz */
    frequency&  operator/=(double delta_hz);

  private:
    double      hz_; 
  };

  /** @brief Multiply frequency by a factor */
  frequency     operator*(frequency lhs, double factor);
  
  /** @brief Divide frequency by a factor */
  frequency     operator/(frequency lhs, double divisor);
  
  /** @brief Check octave equivalence between two frequencies */
  bool          is_octave_equivalent(frequency lhs, frequency rhs);

  /** @brief Stream output for frequency */ 
  std::ostream& operator<<(std::ostream& os, frequency f);

  /** @brief Represents a musical note (pitch class) */
  class note 
  {
  public:
    
    /** @brief Construct note from value (0-11) */
    explicit   note(uint8_t value=0);
    
    /** @brief Construct note from name (e.g., "C#", "D") */ 
    explicit   note(std::string_view name);

    /** @return Note value (0-11) */
    uint8_t     value()                     const;

    /** @return Note name (e.g., "C#", "D") */
    std::string name()                      const;
    
    /** @return Pitch at given octave */
    pitch       get_pitch(int octave)       const;
    
    /** @return Frequency at given octave */
    frequency   get_frequency(int octave)   const;
    
    /** @brief Transpose note by semitones */
    note&       transpose(int semitones); 
    
    /** @brief Transpose note by semitones */ 
    note&       operator+=(int);
  
  private:
    uint8_t     note_; 
  };

  /** @brief Transpose note by semitones */
  note          operator+(note n, int semitones);

  /** @brief Compare two notes */ 
  bool          operator<(note lhs, note rhs);
  
  /** @brief Check equality of two notes */
  bool 		      operator==(note lhs, note rhs); 
  
  /** @brief Interval between two notes in semitones */ 
  int           interval_in_semitones( note lhs,  note rhs);
  
  /** @brief Check octave equivalence between two notes */ 
  bool          is_octave_equivalent( note lhs,  note rhs);
  
  /** @brief Stream output for note */
  std::ostream& operator<<(std::ostream& os, note n);

} // namespace harmony