#include <doctest/doctest.h>
#include "harmony.hpp"
#include <cmath>

using namespace harmony;
double EPS = 1e-2;

// ------------------------------------------------------------
// 1. note basics
// ------------------------------------------------------------
TEST_CASE("note construction and naming") {
    note c(0);
    note a(9);
    note b(11);

    CHECK_EQ(c.value(), 0);
    CHECK_EQ(a.value(), 9);
    CHECK_EQ(b.value(), 11);

    CHECK_EQ(c.name(), "C");
    CHECK_EQ(a.name(), "A");
    CHECK_EQ(b.name(), "B");
}

// ------------------------------------------------------------
// 2. transposition 
// ------------------------------------------------------------
TEST_CASE("note transposition wraps correctly") {
    note n(0); // C
    n.transpose(-1);  // should become B (11)
    CHECK_EQ(n.value(), 11);

    n.transpose(2);   // 11 + 2 = 13 -> 1 (C#)
    CHECK_EQ(n.value(), 1);
}

// ------------------------------------------------------------
// 3. mapping to pitch and frequency
// ------------------------------------------------------------
TEST_CASE("note converts to pitch and frequency correctly") {
    note c(0); // C
    pitch p = c.get_pitch(4); // assuming octave 4
    frequency f = c.get_frequency(4);

    CHECK_EQ(p.get_midi(), 60);
    CHECK(std::fabs(f.get_hz() - 261.63) < EPS);

    note a(9); // A
    pitch p2 = a.get_pitch(4);
    frequency f2 = a.get_frequency(4);

    CHECK_EQ(p2.get_midi(), 69);
    CHECK(std::fabs(f2.get_hz() - 440.0) < EPS);
}

// ------------------------------------------------------------
// 4. interval and equivalence logic
// ------------------------------------------------------------
TEST_CASE("interval_in_semitones and is_octave_equivalent") {
    note c(0);
    note g(7);
    note c2(0);

    CHECK_EQ(interval_in_semitones(g, c), 7);
    CHECK_EQ(interval_in_semitones(c2, c), 0);
    CHECK(is_octave_equivalent(c, c2));
    CHECK_FALSE(is_octave_equivalent(c, g));
}
