//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose :
//*
//*
//****************************************************************************

#pragma once
#include <string>           //For std::string
#include <cstdint>          //For uint8_t
#include <ostream>          //For std::ostream
#include <array>            //For std::array
#include <string_view>      //For std::string_view
#include <utility>          //For std::pair

//****************************************************************************

namespace harmony {

  class frequency;
  class pitch;
  class note;

  inline constexpr std::array<const char*, 12> NOTE_NAMES = 
  {{
    "C", "C#", "D", "D#", "E", "F",
    "F#", "G", "G#", "A", "A#", "B"
  }};

  class pitch 
  {
  public:
                pitch(int midi_note = 60);
                pitch(frequency);

    uint8_t     get_midi()                  const;
    frequency   get_frequency()             const;
    note        get_note()                  const;

    pitch&      operator+=(int semitones);
    pitch&      operator-=(int semitones);

  private:
    uint8_t     midi_note_;  
  };
    
  pitch         operator+(pitch lhs, int semitones);
  pitch         operator-(pitch lhs, int semitones);
  int           operator-(pitch lhs, pitch rhs);

  bool          is_octave_equivalent(pitch lhs, pitch rhs);
  std::ostream& operator<<(std::ostream& os, pitch p);

  uint8_t       octave(pitch p); 
  std::string   name(pitch p);


  class frequency 
  {
  public:

                frequency(double hz = 440.0);

    double      get_hz()                    const;
    uint8_t     get_midi()                  const; 
    pitch       get_pitch()                 const;

    frequency&  operator*=(double delta_hz);
    frequency&  operator/=(double delta_hz);

  private:
    double      hz_; 
  };

  frequency     operator*(frequency lhs, double factor);
  frequency     operator/(frequency lhs, double divisor);

  bool          is_octave_equivalent(frequency lhs, frequency rhs);
  std::ostream& operator<<(std::ostream& os, frequency f);

  class note 
  {
  public:

    explicit   note(uint8_t value=0);
    explicit   note(std::string_view name);
    
    uint8_t     value()                     const;
    std::string name()                      const;
    pitch       get_pitch(int octave)       const;
    frequency   get_frequency(int octave)   const;

    note&       transpose(int semitones); 
    note&       operator+=(int);
  
  private:
    uint8_t     note_; 
  };

  note          operator+(note n, int semitones); 
  int           interval_in_semitones( note lhs,  note rhs);
  bool          is_octave_equivalent( note lhs,  note rhs);
  std::ostream& operator<<(std::ostream& os, note n);

} // namespace harmony