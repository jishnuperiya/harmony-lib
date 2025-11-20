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
#include <string>       //For std::string
#include <cstdint>      //For uint8_t
#include <ostream>      //For std::ostream
#include <array>        //For std::array
#include <string_view> //For std::string_view
#include <utility>      //For std::pair
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

  inline constexpr std::pair<std::string_view, int> ENHARMONIC_NAMES[] = 
  {
   {"C", 0},  {"B#", 0},

   {"C#", 1}, {"Db", 1},

   {"D", 2},

   {"D#", 3}, {"Eb", 3},

   {"E", 4},  {"Fb", 4},

   {"F", 5},  {"E#", 5},
   
   {"F#", 6}, {"Gb", 6},

   {"G", 7},

   {"G#", 8}, {"Ab", 8},

   {"A", 9},

   {"A#", 10},{"Bb", 10},

   {"B", 11}, {"Cb", 11},
  };

  // Note Parsing Helpers
  int note_index_from_name(std::string_view s);

  // -------------------
  // pitch Class
  // -------------------
  class pitch 
  {
  public:
    // ---Special Member Functions ---
    pitch(int midi_note = 60);
    pitch(frequency);

// ---Accessors---
    uint8_t get_midi() const;
    frequency get_frequency() const;
    note get_note() const;

    // ---Mutating member operators---
    pitch& operator+=(int semitones);
    pitch& operator-=(int semitones);

  private:
    uint8_t midi_note_;  // 0–127
  };

  //---Non member functions---
    
  // Arithmetic Operators
  pitch operator+(pitch lhs, int semitones);
  pitch operator-(pitch lhs, int semitones);
  int operator-(pitch lhs, pitch rhs);

  // Utitlity Functions
  bool is_octave_equivalent(pitch lhs, pitch rhs);
  std::ostream& operator<<(std::ostream& os, pitch p);

  // Scientific pitch Notation accessors
  uint8_t octave(pitch p); //get oct
  std::string name(pitch p);

  // -------------------
  // Frequency Class
  // -------------------
  class frequency 
  {
  public:
    // ---Special Member Functions---
    frequency(double hz = 440.0);

    // ---Accessors---
    double get_hz() const;
    uint8_t get_midi() const; 
    pitch get_pitch() const;

    // ---Mutating Member Operators---
    frequency& operator+=(double delta_hz);
    frequency& operator-=(double delta_hz);
    //*= and /= better than + -

  private:
    double hz_; 
  };

  // ---Non-member functions---

  // Arithmetic Operators
  frequency operator*(frequency lhs, double factor);
  frequency operator/(frequency lhs, double divisor);

  // Utitlity Functions
  bool is_octave_equivalent(frequency lhs, frequency rhs);
  std::ostream& operator<<(std::ostream& os, frequency f);

  // -------------------
  // Note Class
  // -------------------
  class note 
  {
  public:
    // ---Special Member Functions---
    note(uint8_t value=0);
    note(std::string_view name);
    
    // ---Accessors---
    uint8_t value() const;
    std::string name() const;
    pitch get_pitch(int octave) const;
    frequency get_frequency(int octave) const;

    // ---Mutating member operators---
    note& transpose(int semitones); 
    note& operator+=(int);
  private:
    uint8_t note_; // 0 -11
  };

  // ---Non-member functions---
  note operator+(note n, int semitones); // transpose copy
  int interval_in_semitones( note lhs,  note rhs);
  bool is_octave_equivalent( note lhs,  note rhs);
  std::ostream& operator<<(std::ostream& os, note n);

} // namespace harmony