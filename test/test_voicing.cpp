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
#include <doctest/doctest.h>                             // For doctest

#include "chord.hpp"                                     // For harmony::chord

#include "progression.hpp"                               // For harmony::progression

#include "voicer.hpp"                                    // For harmony::generate_voicings
//****************************************************************************

using namespace harmony;

// ------------------------------------------------------------
// 1. chord basics
// ------------------------------------------------------------
TEST_CASE("chord generates correct pitches") 
{
  chord cmaj(note(0), chord_quality::Major);
  auto pitches = cmaj.get_pitches(4);

  // Expect C4 E4 G4
  CHECK_EQ(pitches.size(), 3);
  CHECK_EQ(pitches[0].get_midi(), 60); // C4
  CHECK_EQ(pitches[1].get_midi(), 64); // E4
  CHECK_EQ(pitches[2].get_midi(), 67); // G4
}

// ------------------------------------------------------------
// 2. chord name formatting
// ------------------------------------------------------------
TEST_CASE("chord naming reflects quality") 
{
  CHECK_EQ(chord(note(0), chord_quality::Major).name(), "C");
  CHECK_EQ(chord(note(0), chord_quality::Minor).name(), "C-");
  CHECK_EQ(chord(note(0), chord_quality::Diminished).name(), "Co");
  CHECK_EQ(chord(note(0), chord_quality::Augmented).name(), "C+");
}

// ------------------------------------------------------------
// 3. chord progression stores and prints chords
// ------------------------------------------------------------
TEST_CASE("chord_progression holds chords in order") 
{
  chord_progression prog({
    chord(note(0), chord_quality::Major),
    chord(note(7), chord_quality::Major),
    chord(note(5), chord_quality::Minor)
  });

  const auto& chords = prog.chords();
  CHECK_EQ(chords.size(), 3);
  CHECK_EQ(chords[0].name(), "C");
  CHECK_EQ(chords[1].name(), "G");
  CHECK_EQ(chords[2].name(), "F-");
}

// ------------------------------------------------------------
// 4. voicing generation produces correct structure
// ------------------------------------------------------------
TEST_CASE("generate_voicings basic root position") {
  chord_progression prog({  
    chord(note(0), chord_quality::Major),  // C
    chord(note(7), chord_quality::Major),  // G
  });

  auto voicings = generate_voicings(prog, 4);

  CHECK_EQ(voicings.size(), 2);             
  CHECK_EQ(voicings[0].size(), 3);          // triad
  CHECK_EQ(voicings[1].size(), 3);

  // First chord: C4 E4 G4
  CHECK_EQ(voicings[0][0].get_midi(), 60);
  CHECK_EQ(voicings[0][1].get_midi(), 64);
  CHECK_EQ(voicings[0][2].get_midi(), 67);

  // Second chord: G4 B4 D4
  CHECK_EQ(voicings[1][0].get_midi(), 67);
  CHECK_EQ(voicings[1][1].get_midi(), 71);
  CHECK_EQ(voicings[1][2].get_midi(), 62);
}
