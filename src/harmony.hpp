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
//****************************************************************************


namespace harmony {

  // -------------------
  // pitch Class
  // -------------------
  class pitch 
  {
  public:
    // ---Special Member Functions ---
    pitch(int midi_note = 60);

    // ---Accessors---
    int midi();
    double frequency();

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
  pitch operator-(pitch lhs, pitch rhs);

  // Utitlity Functions
  bool is_octave_equivalent(pitch lhs, pitch rhs);

  // Scientific pitch Notation accessors
  std::string name(pitch p);
  uint8_t octave(pitch p);

  // -------------------
  // Frequency Class
  // -------------------

  class frequency 
  {
  public:
    // ---Special Member Functions---
    frequency(double hz = 440.0);

    // ---Accessors---
    double hz();

    // ---Mutating Member Operators---
    frequency& operator+=(double delta_hz);
    frequency& operator-=(double delta_hz);

  private:
    double hz_ = 0.0; 
  };

  // ---Non-member functions---

  // Arithmetic Operators
  frequency operator*(frequency lhs, double factor);
  frequency operator/(frequency lhs, double divisor);

  // Utitlity Functions
  bool is_octave_equivalent(frequency lhs, frequency rhs);

  // -------------------
  // Note Class
  // -------------------
  class note 
  {
  public:
    // ---Special Member Functions---
    note(pitch p = 60);
    note(frequency f = 440);

    // ---Accessors---
    pitch get_pitch();
    frequency get_frequency();

    // ---Mutating member operators---
    note& transpose(int semitones); 

  private:
    pitch pitch_;
    frequency freq_;
  };

  // ---Non-member functions---
  note operator+(note n, int semitones); // transpose copy
  int interval_in_semitones( note lhs,  note rhs);
  bool is_octave_equivalent( note lhs,  note rhs);

} // namespace harmony