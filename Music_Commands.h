#ifndef MUSIC_COMMANDS_H
#define MUSIC_COMMANDS_H

struct Sound_Params
{
  explicit Sound_Params(){}
  explicit Sound_Params(const string & name, const unsigned char data[], const long & size, const double volume = VOLUME_MAX) : m_name(name), m_data(data), m_size(size), m_volume(volume){}
  explicit Sound_Params(const Sound_Params & obj) = default;
  Sound_Params & operator =(const Sound_Params & obj) = default;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
  double m_volume{1};
};

#include "Consts/Media_Consts.h"

#endif