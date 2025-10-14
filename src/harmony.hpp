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
//****************************************************************************


namespace harmony {

  // -------------------
  // Pitch Class
  // -------------------
  struct Pitch 
  {
  public:
    // ---Special Member Functions ---
    Pitch(int midi_note = 0); 
    Pitch(const Pitch& other);
    Pitch& operator=(const Pitch& other);
    ~Pitch();

    // ---Accessors---
    int midi();
    double frequency();

    // ---Mutating member operators---
    Pitch& operator+=(int semitones);
    Pitch& operator-=(int semitones);

  private:
    int midi_note_;  // 0–127

  };

  //---Non member functions---
    
  // Arithmetic Operators
  Pitch operator+(Pitch lhs, int semitones);
  Pitch operator-(Pitch lhs, int semitones);

  // Utitlity Functions
  bool is_octave_equivalent(const Pitch& lhs, const Pitch& rhs);

  // Scientific Pitch Notation accessors
  std::string name(const Pitch& p);
  int octave(const Pitch& p);

  // -------------------
  // Frequency Class
  // -------------------

  struct Frequency 
  {
  public:
    // ---Special Member Functions---
    Frequency(double hz = 0.0);
    Frequency(const Frequency& other);
    Frequency& operator=(const Frequency& other);
    ~Frequency();

    // ---Accessors---
    double hz();

    // ---Mutating Member Operators---
    Frequency& operator+=(double delta_hz);
    Frequency& operator-=(double delta_hz);

  private:
    double hz_; 
  };

  // ---Non-member functions---

  // Arithmetic Operators
  Frequency operator+(Frequency lhs, double delta_hz);
  Frequency operator-(Frequency lhs, double delta_hz);
  Frequency operator*(Frequency lhs, double factor);
  Frequency operator/(Frequency lhs, double divisor);

  // Utitlity Functions
  bool is_octave_equivalent(const Frequency& lhs, const Frequency& rhs);

  // -------------------
  // Note Class
  // -------------------
  struct Note 
  {
  public:
    // ---Special Member Functions---
    Note(Pitch p);
    Note(Frequency f);
    Note(const Note& other);
    Note& operator=(const Note& other);
    ~Note();

    // ---Accessors---
    Pitch pitch();
    Frequency frequency();

    // ---Mutating member operators---
    Note& transpose(int semitones); 

  private:
    Pitch pitch_;
    Frequency frequency_;
  };

  // ---Non-member functions---
  Note operator+(Note n, int semitones); // transpose copy
  int interval_in_semitones(const Note& lhs, const Note& rhs);
  bool is_octave_equivalent(const Note& lhs, const Note& rhs);

} // namespace harmony