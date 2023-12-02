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

struct Music_Params
{
  explicit Music_Params(){}
  explicit Music_Params(const string & name, const unsigned char data[], const long & size) : m_name(name), m_data(data), m_size(size){}
  explicit Music_Params(const Music_Params & obj) = default;
  Music_Params & operator =(const Music_Params & obj) = default;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
};

struct No_Music_Params{};

struct Add_Music_Params
{
  explicit Add_Music_Params(const Music_Params & params) : m_name(params.m_name), m_data(params.m_data), m_size(params.m_size){}
  Add_Music_Params(const Add_Music_Params & obj) = default;
  Add_Music_Params & operator =(const Add_Music_Params & obj) = default;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
};

struct Play_Pause_Music_Params
{
  explicit Play_Pause_Music_Params(const string & name) : m_name(name){}
  string m_name{"NULL"};
};

struct Volume_Music_Params
{
  explicit Volume_Music_Params(const string & name, const double & volume) : m_name(name), m_volume(volume){}
  string m_name{"NULL"};
  double m_volume{0};
};

enum class Music_Command{Add, Remove, Remove_All, Update, Play, Pause, Volume};
typedef variant<No_Music_Params, Add_Music_Params, Play_Pause_Music_Params, Volume_Music_Params> Music_Commands;

struct Music_Command_Params
{
  explicit Music_Command_Params(const Music_Command & op, const Music_Commands & params = No_Music_Params{}) : m_operation(op), m_params(params){}
  Music_Command m_operation{Music_Command::Update};
  Music_Commands m_params{};
};

#include "Consts/Media_Consts.h"

#endif