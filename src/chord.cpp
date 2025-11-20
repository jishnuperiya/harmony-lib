#include <map>
#include <sstream>
#include "chord.hpp"

using namespace harmony;

note chord::root() const { return root_; }

std::string chord::name() const 
{ 
  std::ostringstream o;
  o << root_;
  // Add quality implementation later
  /*switch (quality_)
  {
  case chord_quality::Major:
      break;
  case chord_quality::Minor:
      o << '-';
      break;
  case chord_quality::Diminished:
      o << 'o';
      break;
  case chord_quality::Augmented:
      o << '+';
      break;
  }*/
  return o.str();
}

std::vector<note> chord::get_notes() const
{

	std::vector<note> result;
	result.reserve(12);

    for (int pc = 0; pc < 12; ++pc)
    {
        if (notes_[pc]) {
            result.emplace_back(NOTE_NAMES[pc]); // construct note from name
        }
    }

    return result;

    //std::vector<int> semitones;
    //switch (quality_)
    //{
    //case chord_quality::Major:      semitones = { 0, 4, 7 }; break;
    //case chord_quality::Minor:      semitones = { 0, 3, 7 }; break;
    //case chord_quality::Diminished: semitones = { 0, 3, 6 }; break;
    //case chord_quality::Augmented:  semitones = { 0, 4, 8 }; break;
    //}
    //std::vector<note> result;
    //for (int semitone : semitones)
    //{
    //    //note transposed_note = root_.transpose(semitone) -> doesnt work bc root_ is const
    //    result.push_back(root_ + semitone);//not able to use the transpose function here. should i make the get_ntoes non const?
    //    // but access methods need to be const? or what the solution here
    //}
    //return result;
}

//std::vector<pitch> chord::get_pitches(int octave) const 
//{
//	auto notes = get_notes();
//	std::vector<pitch> pitches(std::begin(notes), std::end(notes));
//
//
//    /*for(const auto& n : notes)
//    {
//	  pitches.push_back(n.get_pitch(octave));
//	}*/
//	return pitches;
//}
//
std::vector<pitch> chord::get_pitches(int octave) const
{
    auto notes = get_notes();

    std::vector<pitch> pitches;
    pitches.reserve(notes.size());

    for (const auto& n : notes)
        pitches.push_back(n.get_pitch(octave));

    return pitches;
}

std::ostream& harmony::operator<<(std::ostream& os, const chord& c) {
  os << c.name();
  return os;
}
