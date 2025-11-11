#include <map>
#include <sstream>
#include "chord.hpp"


using namespace harmony;

chord::chord(note root, chord_quality quality)
  : root_{ root }, quality_{ quality } {}

note chord::root() const { return root_; }

chord_quality chord::quality() const { return quality_;}


std::string chord::name() const 
{ // chord* this; 
  static const std::map<chord_quality, std::string> quality_names = 
  {
    {chord_quality::Major, ""},
    {chord_quality::Minor, "m"},
    {chord_quality::Diminished, "dim"},
    {chord_quality::Augmented, "aug"},
  };

  std::ostringstream o;
  //o << root_.name();
  o << root_;


  switch (quality_)
  {
  case chord_quality::Major:
      /*o << "";*/
      break;
  case chord_quality::Minor:
      o << ´-´;
      break;
  case chord_quality::Diminished:
      o << "o";
      break;
  case chord_quality::Augmented:
      o << "+";
      break;
  }
  return o.str();
  return (*this).root_.name() + quality_names.at(quality_);
}

std::vector<pitch> chord::get_pitches(int octave) const 
{
  std::map<chord_quality, std::vector<int>> intervals =
  {
    {chord_quality::Major, {0, 4, 7}},
    {chord_quality::Minor, {0, 3, 7}},
    {chord_quality::Diminished, {0, 3, 6}},
    {chord_quality::Augmented, {0, 4, 8}},
  };

  std::vector<pitch> result;
  auto base = root_.get_pitch(octave);
  int base_midi = base.get_midi();

  for (int semitones : intervals.at(quality_)) 
  {
    result.push_back(pitch(base_midi + semitones));
  }
  return result;
}

std::ostream& harmony::operator<<(std::ostream& os, const chord& c) {
  os << c.name();
  return os;
}
