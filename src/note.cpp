#include "harmony.hpp"
#include <cassert> //for assert
#include <cmath> //for fabs
#include <stdexcept> //for std::inalid_argument

harmony::note::note(pitch p)
  :pitch_{p}, freq_{p.get_frequency()}
{
}

harmony::note::note(frequency f)
  :freq_{f}, pitch_{f.midi()}
{
}

harmony::pitch harmony::note::get_pitch()
{
  return pitch_;
}

harmony::frequency harmony::note::get_frequency()
{
  return freq_;
}

harmony::note& harmony::note::transpose(int semitones)
{
  pitch_+=semitones;
  double new_hz = freq_.hz() * std::pow(2.0, semitones / 12.0);
  freq_=harmony::frequency{new_hz};
  return *this;
}

harmony::note harmony::operator+(harmony::note n, int semitones)
{
  n.transpose(semitones);
  return n;
}

int harmony::interval_in_semitones(note lhs, note rhs)
{
  return lhs.get_pitch().get_midi() - rhs.get_pitch().get_midi();
}

bool harmony::is_octave_equivalent(note lhs, note rhs)
{
  int diff = std::abs(lhs.get_pitch().get_midi() - rhs.get_pitch().get_midi());
  return diff % 12 == 0;
}
std::ostream& harmony::operator<<(std::ostream&os, harmony::frequency f);
std::ostream& harmony::operator<<(std::ostream& os, harmony::note n)
{
   return os << "Note{" 
      << n.get_pitch() << ", "
      << n.get_frequency();
}
// printf("pitch {%d}" , 72.05) //casting - garbage int... printf-variadic-not typesafe.
/*

not tpysafe
not extensible

void print(pitch );

void print(note);

function overlaoind 

stream insertion - chaining - possible because

operator<<((operator<<(os, "Note{")) , harmony::name(n.get_pitch()))

ios
|
ostream -> streambuf
               |
            filebuf

            bridge design pattern

struct streambuf
{
  virtual void put_char(char)=0;
  virtual void put_char(cost char*, size_t)=0;
}

struct filebuf : streambuf
{
  filebuf(const char* filename);
  ~filebuf(); // close the filehandle
  void put_char(char) override;
  private:
    int m_filehandle;
}

//diff strem buf diff destinations. 
struct ostream
{
  private:
    streambuf* m_buf;
  public:
    void insert(char)
    {
      m_buf->put_char(c);
    }
    void insert(const char*)
    void insert(int i)
    {
      for each digit of i convert to char and send it to stream buf
      possibly a enum for format of int: oct, hex 
    }
    void insert(dobule);
}
*/