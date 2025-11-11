#include <doctest/doctest.h>
#include "harmony.hpp"
#include <cmath>

using namespace harmony;

//open a filebuf
/*
create file buf
ostream helding on to that gilebuf

ofstream subclass

write pitch or note to the ofstream

since ofstream is ostream it can be apssed to <<


----

instead of ofstream use cout.
different streambuffers.


*/

TEST_CASE("frequency construction and accessors")
{  
  pitch p1(69);
  CHECK(doctest::Approx(p1.get_frequency().hz()) == 440.0);
  CHECK_EQ(p1.get_midi(),69);
}

TEST_CASE("compound assignment operators for pitch class")
{
  pitch p1(69);
  p1+=20;
  CHECK_EQ(p1.get_midi(),89);
  
  p1-=10;
  CHECK_EQ(p1.get_midi(),79);
}

TEST_CASE("non-member arithmetic operations")
{
  pitch p1(20);
  pitch p2 = p1+2;
  CHECK_EQ(p2.get_midi(), 22);

  pitch p3 = p2-2;
  CHECK_EQ(p3.get_midi(),20);

  int interval = p3-p2;
  CHECK_EQ(interval,-2);
}

TEST_CASE("octave equivalence")
{
  pitch c4(60);
  pitch c5(72);

  CHECK(is_octave_equivalent(c4, c5));
 
  CHECK_FALSE(is_octave_equivalent(c4, pitch(61)));
}

TEST_CASE("scientific notation")
{
  pitch c4(60);
  CHECK_EQ(name(c4),"C4");   
}