#include <doctest/doctest.h>
#include "harmony.hpp"
#include <cmath>

using namespace harmony;


TEST_CASE("frequency construction and accessors")
{  
  frequency f1(440.0);
  CHECK(doctest::Approx(f1.get_hz()) == 440.0);
  CHECK_EQ(f1.get_midi(),69);
}

TEST_CASE("compound assignment operators for frequency class")
{
  frequency f1(440.0);
  f1+=20.0;
  CHECK(doctest::Approx(f1.get_hz()) == 460.0);
  
  f1-=10.0;
  CHECK(doctest::Approx(f1.get_hz()) == 450.0);
}

TEST_CASE("non-member arithmetic operations")
{
  frequency f1(440.0);  
  frequency f2 = f1*2.0;
  CHECK(doctest::Approx(f2.get_hz()) == 880.0);

  frequency f3 = f2/2.0;
  CHECK(doctest::Approx(f3.get_hz()) == 440.0);
}

TEST_CASE("octave equivalence")
{
  frequency f1(440.0);
  frequency f2(880.0);

  CHECK(is_octave_equivalent(f1, f2));
 
  CHECK_FALSE(is_octave_equivalent(f1, frequency(150.0)));

}