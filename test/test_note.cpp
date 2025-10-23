#include <doctest/doctest.h>
#include "harmony.hpp"

using namespace harmony;

TEST_CASE("note construction from pitch and frequency stays consistent") {
    note n1(pitch(60));
    note n2(frequency(261.63));
    CHECK_EQ(n2.get_pitch().get_midi(), n1.get_pitch().get_midi());
    CHECK(is_octave_equivalent(n1, n2));
}

TEST_CASE("note transposition changes pitch and frequency correctly") {
    note n(pitch(60));
    n.transpose(12);
    CHECK_EQ(n.get_pitch().get_midi(), 72);
    CHECK(doctest::Approx(n.get_frequency().hz()) == 523.25);
}

TEST_CASE("operator+ creates transposed copy") {
    note c4(pitch(60));
    note c5 = c4 + 12;
    CHECK_EQ(c5.get_pitch().get_midi(), 72);
    CHECK(doctest::Approx(c5.get_frequency().hz()) == 523.25);
}

TEST_CASE("interval_in_semitones and is_octave_equivalent work correctly") {
    note c4(pitch(60));
    note g4(pitch(67));
    note c5(pitch(72));

    CHECK_EQ(interval_in_semitones(g4, c4), 7);
    CHECK_EQ(interval_in_semitones(c5, c4), 12);
    CHECK(is_octave_equivalent(c4, c5));
    CHECK_FALSE(is_octave_equivalent(c4, g4));
}
