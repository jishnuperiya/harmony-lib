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
#include <string> //For std::string
#include <cstdint> //For uint8_t
#include <ostream> //For std::ostream
//****************************************************************************


namespace harmony {

  class frequency;
  class pitch;
  class note;
  // -------------------
  // pitch Class
  // -------------------
  class pitch 
  {
  public:
    // ---Special Member Functions ---
    pitch(int midi_note = 60);
//  pitch(frequency);bfreq class could have a fn called get pitch Or calclualtion here 
    // ---Accessors---
    uint8_t get_midi() const;
    frequency get_frequency() const;
    note get_note() const;
    // ---Mutating member operators---
    pitch& operator+=(int semitones);
    pitch& operator-=(int semitones);

  private:
    uint8_t midi_note_ = 60;  // 0–127
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
    double hz_ = 440.0; 
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