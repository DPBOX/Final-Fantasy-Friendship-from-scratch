#include "Main.h"
#include "World.h"

bool Stat_Modifier::operator==(const Stat_Modifier & rhs) const
{
  return m_id == rhs.get_id();
}

string Stat_Modifier::get_id() const
{
  return m_id;
}

string Stat_Modifier::get_type() const
{
  return m_type;
}

string Stat_Modifier::get_stat() const
{
  return m_stat;
}

long Stat_Modifier::get_add_modifier() const
{
  return m_add_modifier;
}

double Stat_Modifier::get_multiply_modifier() const
{
  return m_multiply_modifier;
}

void Stats::set_hp(const long & HP)
{
  m_hp_now = HP;
  if(m_hp_now < 0)
  {
    m_hp_now = 0;
  }
  if(m_hp_now > m_hp_max)
  {
    m_hp_now = m_hp_max;
  }
}

void Stats::set_mp(const long & MP)
{
  m_mp_now = MP;
  if(m_mp_now < 0)
  {
    m_mp_now = 0;
  }
  if(m_mp_now > m_mp_max)
  {
    m_mp_now = m_mp_max;
  }
}

void Stats::add_modifier(const Stat_Modifier & modifier)
{
  //Does it already exist?
  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i] == modifier)
    {
      //Yes it does, return
      return;
    }
  }
  //No it doesn't, add it to the list
  m_modifiers.push_back(modifier);
}

void Stats::remove_modifier(const Stat_Modifier & modifier)
{
  //Does it already exist?
  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i] == modifier)
    {
      //Yes it does, remove it
      m_modifiers.erase(m_modifiers.begin() + i);
      return;
    }
  }
}

long Stats::get_unmodified_stat(const string & stat) const
{
  if(stat == "HP")
  {
    return m_hp_now;
  }
  else if(stat == "MP")
  {
    return m_mp_now;
  }
  else if(stat == "Max HP")
  {
    return m_hp_max;
  }
  else if(stat == "Max MP")
  {
    return m_mp_max;
  }
  else if(stat == "Level")
  {
    return m_level;
  }
  else if(stat == "Defense")
  {
    return m_defense;
  }
  else if(stat == "Resistance")
  {
    return m_resistance;
  }
  else if(stat == "Evasion")
  {
    return m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    return m_magic_evasion;
  }
  else if(stat == "Critical")
  {
    return m_critical;
  }
  else if(stat == "Attack")
  {
    return m_attack;
  }
  else if(stat == "Accuracy")
  {
    return m_accuracy;
  }
  else if(stat == "Spirit")
  {
    return m_spirit;
  }
  else if(stat == "Stamina")
  {
    return m_stamina;
  }
  else if(stat == "Strength")
  {
    return m_strength;
  }
  else if(stat == "Intellect")
  {
    return m_intellect;
  }
  else
  {
    crash("Error: Tried to get invalid unmodified stat \"" + stat + "\".");
  }
  return -1;
}

long Stats::get_stat(const string & stat) const
{
  long extra{0};
  double modified_stat{0};
  long unmodified_stat{0};

  if(stat == "Max HP")
  {
    unmodified_stat = m_hp_max;
  }
  else if(stat == "Max MP")
  {
    unmodified_stat = m_mp_max;
  }
  else if(stat == "Speed")
  {
    unmodified_stat = 0;
  }
  else if(stat == "Defense")
  {
    unmodified_stat = m_defense;
  }
  else if(stat == "Resistance")
  {
    unmodified_stat = m_resistance;
  }
  else if(stat == "Evasion")
  {
    unmodified_stat = m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    unmodified_stat = m_magic_evasion;
  }
  else if(stat == "Critical")
  {
    unmodified_stat = m_critical;
  }
  else if(stat == "Attack")
  {
    unmodified_stat = m_attack;
  }
  else if(stat == "Accuracy")
  {
    unmodified_stat = m_accuracy;
  }
  else if(stat == "Spirit")
  {
    unmodified_stat = m_spirit;
  }
  else if(stat == "Stamina")
  {
    unmodified_stat = m_stamina;
  }
  else if(stat == "Strength")
  {
    unmodified_stat = m_strength;
  }
  else if(stat == "Intellect")
  {
    unmodified_stat = m_intellect;
  }
  else
  {
    crash("Error: Tried to get invalid stat \"" + stat + "\".");
  }

  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i].get_stat() == stat)
    {
      if(m_modifiers[i].get_type() == "Add")
      {
        extra += m_modifiers[i].get_add_modifier();
      }
    }
  }
  modified_stat = unmodified_stat + extra;
  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i].get_stat() == stat)
    {
      if(m_modifiers[i].get_type() == "Multiply")
      {
        modified_stat *= m_modifiers[i].get_multiply_modifier();
      }
    }
  }
  return modified_stat + .5;
}

Player_Stats::Player_Stats(const Character_Base_Stats & stats, const long & level, const long & exp)
{
  m_base_hp = stats.m_base_hp;
  m_base_mp = stats.m_base_mp;
  m_defense = stats.m_defense;
  m_resistance = stats.m_resistance;
  m_evasion = stats.m_evasion;
  m_magic_evasion = stats.m_magic_evasion;
  m_critical = stats.m_critical;
  m_spirit_growth = stats.m_spirit_growth;
  m_stamina_growth = stats.m_stamina_growth;
  m_strength_growth = stats.m_strength_growth;
  m_intellect_growth = stats.m_intellect_growth;
  m_level = level;
  m_exp = exp;
  m_current_level_starting_exp = exp;
  m_attack = DEFAULT_ATTACK;
  m_accuracy = DEFAULT_ACCURACY;
  if(m_level == 1)
  {
    m_hp_max = m_base_hp;
    m_mp_max = m_base_mp;
  }
  else
  {
    m_hp_max = m_base_hp + (m_level - 1) * m_stamina_growth[m_level - 2] + m_stamina_growth[0] * (m_level - 1) / 2;
    m_mp_max = m_base_mp + (m_spirit_growth[m_level - 2] + m_spirit_growth[0]) * (m_level - 1) / 10;
  }
  m_hp_now = m_hp_max;
  m_mp_now = m_mp_max;
}

void Player_Stats::update_stats()
{
  if(m_level == 1)
  {
    m_hp_max = m_base_hp;
    m_mp_max = m_base_mp;
  }
  else
  {
    m_hp_max = m_base_hp + (m_level - 1) * m_stamina_growth[m_level - 1] + m_stamina_growth[0] * (m_level - 1) / 2;
    m_mp_max = m_base_mp + (m_spirit_growth[m_level - 1] + m_spirit_growth[0]) * (m_level - 1) / 10;
  }
}

void Player_Stats::give_exp(const long & exp)
{
  if(m_level != MAX_LEVEL)
  {
    m_exp += exp;
    if(m_exp >= m_current_level_starting_exp + exp_formula())
    {
      m_ready_to_level_up = true;
    }
  }
}

void Player_Stats::level_up()
{
  if(m_ready_to_level_up == true)
  {
    m_ready_to_level_up = false;
    m_current_level_starting_exp += exp_formula();
    ++m_level;
    if(m_level != MAX_LEVEL && m_exp >= m_current_level_starting_exp + exp_formula())
    {
      m_ready_to_level_up = true;
      level_up();
    }
    if(m_level == MAX_LEVEL)
    {
      m_exp = m_current_level_starting_exp;
    }
  }
}

long Player_Stats::get_unmodified_stat(const string & stat) const
{
  if(stat == "HP")
  {
    return m_hp_now;
  }
  else if(stat == "MP")
  {
    return m_mp_now;
  }
  else if(stat == "Max HP")
  {
    return m_hp_max;
  }
  else if(stat == "Max MP")
  {
    return m_mp_max;
  }
  else if(stat == "Level")
  {
    return m_level;
  }
  else if(stat == "EXP")
  {
    return m_exp;
  }
  else if(stat == "Current Level Starting EXP")
  {
    return m_current_level_starting_exp;
  }
  else if(stat == "Next Level EXP")
  {
    return m_current_level_starting_exp + exp_formula() - m_exp;
  }
    else if(stat == "Next Level Total EXP")
  {
    return m_current_level_starting_exp + exp_formula();
  }
  else if(stat == "Defense")
  {
    return m_defense;
  }
  else if(stat == "Resistance")
  {
    return m_resistance;
  }
  else if(stat == "Evasion")
  {
    return m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    return m_magic_evasion;
  }
  else if(stat == "Critical")
  {
    return m_critical;
  }
  else if(stat == "Attack")
  {
    return m_attack;
  }
  else if(stat == "Accuracy")
  {
    return m_accuracy;
  }
  else if(stat == "Spirit")
  {
    return m_spirit_growth[m_level - 1];
  }
  else if(stat == "Stamina")
  {
    return m_stamina_growth[m_level - 1];
  }
  else if(stat == "Strength")
  {
    return m_strength_growth[m_level - 1];
  }
  else if(stat == "Intellect")
  {
    return m_intellect_growth[m_level - 1];
  }
  else
  {
    crash("Error: Tried to get invalid unmodified stat \"" + stat + "\".");
  }
  return -1;
}

long Player_Stats::get_stat(const string & stat) const
{
  long extra{0};
  double modified_stat{0};
  long unmodified_stat{0};

  if(stat == "Max HP")
  {
    unmodified_stat = m_hp_max;
  }
  else if(stat == "Max MP")
  {
    unmodified_stat = m_mp_max;
  }
  else if(stat == "Speed")
  {
    unmodified_stat = 0;
  }
  else if(stat == "Defense")
  {
    unmodified_stat = m_defense;
  }
  else if(stat == "Resistance")
  {
    unmodified_stat = m_resistance;
  }
  else if(stat == "Evasion")
  {
    unmodified_stat = m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    unmodified_stat = m_magic_evasion;
  }
  else if(stat == "Critical")
  {
    unmodified_stat = m_critical;
  }
  else if(stat == "Attack")
  {
    unmodified_stat = m_attack;
  }
  else if(stat == "Accuracy")
  {
    unmodified_stat = m_accuracy;
  }
  else if(stat == "Spirit")
  {
    unmodified_stat = m_spirit_growth[m_level - 1];
  }
  else if(stat == "Stamina")
  {
    unmodified_stat = m_stamina_growth[m_level - 1];
  }
  else if(stat == "Strength")
  {
    unmodified_stat = m_strength_growth[m_level - 1];
  }
  else if(stat == "Intellect")
  {
    unmodified_stat = m_intellect_growth[m_level - 1];
  }
  else
  {
    crash("Error: Tried to get invalid stat \"" + stat + "\".");
  }

  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i].get_stat() == stat)
    {
      if(m_modifiers[i].get_type() == "Add")
      {
        extra += m_modifiers[i].get_add_modifier();
      }
    }
  }
  modified_stat = unmodified_stat + extra;
  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i].get_stat() == stat)
    {
      if(m_modifiers[i].get_type() == "Multiply")
      {
        modified_stat *= m_modifiers[i].get_multiply_modifier();
      }
    }
  }
  return modified_stat + .5;
}

long Player_Stats::exp_formula() const
{
  double pow_i{2.4 + EXP_INFLATION / 100.0};
  return EXP_BASE * pow(m_level + 4, pow_i) / pow(5, pow_i);
}

Party_Member::Party_Member(const Player_Info & player)
{
  m_name = player.m_name;
  m_species = player.m_species;
  m_class = player.m_class;
  m_row = player.m_starting_row;
  m_soul_break_level = 1;
  m_stats = Player_Stats{player.m_stats};
  Image image{LoadImageFromMemory(".png", player.m_portrait_data, player.m_portrait_size)};
  m_portrait = LoadTextureFromImage(image);
  UnloadImage(image);
  
  Image image2{LoadImageFromMemory(".png", player.m_small_portrait_data, player.m_small_portrait_size)};
  m_small_portrait = LoadTextureFromImage(image2);
  UnloadImage(image2);
}

Party_Member::~Party_Member()
{
  UnloadTexture(m_portrait);
  UnloadTexture(m_small_portrait);
}

void Party_Member::update_stats()
{
  m_stats.update_stats();
}

string Party_Member::get_name() const
{
  return m_name;
}

string Party_Member::get_species() const
{
  return m_species;
}

string Party_Member::get_class() const
{
  return m_class;
}

long Party_Member::get_portrait_height() const
{
  return m_portrait.height;
}

long Party_Member::get_portrait_width() const
{
  return m_portrait.width;
}

long Party_Member::get_small_portrait_height() const
{
  return m_small_portrait.height;
}

long Party_Member::get_small_portrait_width() const
{
  return m_small_portrait.width;
}

long Party_Member::get_stat(const string & stat) const
{
  return m_stats.get_stat(stat);
}

long Party_Member::get_unmodified_stat(const string & stat) const
{
  return m_stats.get_unmodified_stat(stat);
}

bool Party_Member::get_row() const
{
  return m_row;
}

long Party_Member::get_soul_break_level() const
{
  return m_soul_break_level;
}

void Party_Member::render_portrait(const bool & size, const long & x, const long & y) const
{
  if(size == false)
  {
    DrawTexturePro(m_small_portrait, Rectangle{0, 0, static_cast<float>(m_small_portrait.width), static_cast<float>(m_small_portrait.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_small_portrait.width), static_cast<float>(m_small_portrait.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
  else
  {
    DrawTexturePro(m_portrait, Rectangle{0, 0, static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}

void Party_Member::set_front_row()
{
  m_row = true;
}

void Party_Member::set_back_row()
{
  m_row = false;
}

void Party_Member::give_member_exp(const long & exp)
{
  m_stats.give_exp(exp);
}

void Party_Member::level_up()
{
  m_stats.level_up();
}

void Party::update_stats()
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    m_members[i]->update_stats();
  }
}

void Party::add_party_member(const Player_Info & player)
{
  m_members.push_back(new Party_Member(player));
  ++mem;
}

void Party::remove_party_member(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(name == m_members[i]->get_name())
    {
      m_members.erase(m_members.begin() + i);
    }
  }
}

string Party::get_member_name(const long & index) const
{
  if(index < 0 || index >= static_cast<long>(m_members.size()))
  {
    crash("Error: Tried to get invalid party member " + to_string(index) + ".");
  }
  return m_members[index]->get_name();
}

string Party::get_member_species(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_species();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return "NULL";
}

string Party::get_member_class(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_class();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return "NULL";
}

long Party::get_member_portrait_width(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_portrait_width();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

long Party::get_member_portrait_height(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_portrait_height();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

long Party::get_member_small_portrait_width(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_small_portrait_width();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

long Party::get_member_small_portrait_height(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_small_portrait_height();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

long Party::get_member_stat(const string & name, const string & stat) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_stat(stat);
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

long Party::get_member_unmodified_stat(const string & name, const string & stat) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_unmodified_stat(stat);
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

bool Party::get_member_row(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_row();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return false;
}

long Party::get_member_soul_break_level(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->get_soul_break_level();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return -1;
}

void Party::render_member_portrait(const string & name, const bool & size, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      m_members[i]->render_portrait(size, x, y);
      return;
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
}

long Party::get_size() const
{
  return m_members.size();
}

void Party::set_member_front_row(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      m_members[i]->set_front_row();
      return;
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
}

void Party::set_member_back_row(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      m_members[i]->set_back_row();
      return;
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
}

void Party::swap_party_members(const string & name1, const string & name2)
{
  long n1{-1};
  long n2{-1};
  Party_Member* temp{nullptr};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name1)
    {
      n1 = i;
    }
    if(m_members[i]->get_name() == name2)
    {
      n2 = i;
    }
  }
  if(n1 == -1)
  {
    crash("Error: Tried to get invalid party member " + name1 + ".");
  }
  if(n2 == -1)
  {
    crash("Error: Tried to get invalid party member " + name2 + ".");
  }
  temp = m_members[n1];
  m_members[n1] = m_members[n2];
  m_members[n2] = temp;
}

Party::~Party()
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    delete m_members[i];
    m_members[i] = nullptr;
    --mem;
  }
}

World::World()
{
  m_time.start();
  add_item("Bronze Sword");
  add_item("Heal Potion");
  add_item("Heal Potion");
  add_item("Heal Potion");
  add_item("Money Bag");
  add_item("Money Bag");
  add_item("Money Bag");
  add_item("Mysterious Torque");

  Image image{LoadImageFromMemory(".png", binary_Image_inventory_icons_png_start, reinterpret_cast<long>(&binary_Image_inventory_icons_png_size))};
  m_item_icons_tex = LoadTextureFromImage(image);
  UnloadImage(image);
  
  m_party.add_party_member(TEMPEST_SHADOW_INFO);
}

World::~World()
{
  UnloadTexture(m_item_icons_tex);
}

void World::update()
{
  m_party.update_stats();
}

void World::render_item(const long & x, const long & y, Fnt* font, const long & item_index, const long & width) const
{
  if(item_index >= 0 && item_index < static_cast<long>(m_items.size()))
  {
    long current_pos{x};
    if(m_items[item_index].get_item().m_icon != 0)
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_items[item_index].get_item().m_icon), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (font->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;
    }

    string text{m_items[item_index].get_item().m_name};
    while(text != "")
    {
      font->render_letter(current_pos, y, text[0]);
      current_pos += font->get_char_width(text[0]);
      text.erase(text.begin());
    }

    current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
    text = "x" + to_string(m_items[item_index].get_count());
    while(text != "")
    {
      font->render_letter(current_pos, y, text[0]);
      current_pos += font->get_char_width(text[0]);
      text.erase(text.begin());
    }
  }
}

void World::render_key_item(const long & x, const long & y, Fnt* font, const long & item_index) const
{
  if(item_index >= 0 && item_index < static_cast<long>(m_key_items.size()))
  {
    long current_pos{x};
    string text{m_key_items[item_index].m_name};
    while(text != "")
    {
      font->render_letter(current_pos, y, text[0]);
      current_pos += font->get_char_width(text[0]);
      text.erase(text.begin());
    }
  }
}

void World::render_stat(const long & x, const long & y, Fnt* font, const long & item_index, const long & width, const string & name) const
{
  long current_pos{static_cast<long>(x + width * STAT_LOCATION_FRACTION)};
  string text;

  switch(item_index)
  {
    case 0:
      text = to_string(m_party.get_member_stat(name, "Strength"));
      break;
    case 1:
      text = to_string(m_party.get_member_stat(name, "Attack"));
      break;
    case 3:
      text = to_string(m_party.get_member_stat(name, "Speed"));
      break;
    case 4:
      text = to_string(m_party.get_member_stat(name, "Defense"));
      break;
    case 6:
      text = to_string(m_party.get_member_stat(name, "Intellect"));
      break;
    case 7:
      text = to_string(m_party.get_member_stat(name, "Resistance"));
      break;
    case 9:
      text = to_string(m_party.get_member_stat(name, "Stamina"));
      break;
    case 10:
      text = to_string(m_party.get_member_stat(name, "Accuracy"));
      break;
    case 12:
      text = to_string(m_party.get_member_stat(name, "Spirit"));
      break;
    case 13:
      text = to_string(m_party.get_member_stat(name, "Critical"));
      break;
    case 15:
      text = to_string(m_party.get_member_stat(name, "Evasion"));
      break;
    case 16:
      text = to_string(m_party.get_member_stat(name, "Magic Evasion"));
      break;
    default:
      break;
  }

  while(text != "")
  {
    font->render_letter(current_pos, y, text[0]);
    current_pos += font->get_char_width(text[0]);
    text.erase(text.begin());
  }
}

vector<string> World::get_items() const
{
  vector<string> items;
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    items.push_back(m_items[i].get_item().m_name);
  }
  return items;
}

vector<string> World::get_key_items() const
{
  vector<string> key_items;
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    key_items.push_back(m_key_items[i].m_name);
  }
  return key_items;
}

Item_Slot World::get_item(const long & index) const
{
  if(index >= 0 && index < static_cast<long>(m_items.size()))
  {
    return m_items[index];
  }
  return Item_Slot{ITEM_DATABASE[0]};
}

Item_Slot World::get_item(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i].get_item().m_name == name)
    {
      return m_items[i];
    }
  }
  return Item_Slot{ITEM_DATABASE[0]};
}

Item World::get_key_item(const long & index) const
{
  if(index >= 0 && index < static_cast<long>(m_key_items.size()))
  {
    return m_key_items[index];
  }
  return ITEM_DATABASE[0];
}

bool World::has_items() const
{
  return !m_items.empty();
}

bool World::has_item(const string & item) const
{
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i].get_item().m_name == item)
    {
      return true;
    }
  }
  return false;
}

void World::add_item(const string & item)
{
  //Does it already exist?
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i].get_item().m_name == item)
    {
      //Yes it does, increase the count and exit
      m_items[i].inc_count();
      return;
    }
  }
  //No it doesn't, add it to the list
  for(long i{0}; i < static_cast<long>(ITEM_DATABASE.size()); ++i)
  {
    if(ITEM_DATABASE[i].m_name == item)
    {
      m_items.push_back(Item_Slot{ITEM_DATABASE[i]});
    }
  }
}

void World::remove_item(const string & item)
{
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i].get_item().m_name == item)
    {
      if(m_items[i].get_count() > 0)
      {
        m_items[i].dec_count();
        if(m_items[i].get_count() == 0)
        {
          // erase it
          m_items.erase(m_items.begin() + i);
          return;
        }
      }
    }
  }
}

void World::remove_item(const long & item_index)
{
  if(item_index >= 0 && item_index < static_cast<long>(m_items.size()) && m_items[item_index].get_count() > 0)
  {
    m_items[item_index].dec_count();
    if(m_items[item_index].get_count() == 0)
    {
      // erase it
      m_items.erase(m_items.begin() + item_index);
    }
  }
}

bool World::has_key_items() const
{
  return !m_key_items.empty();
}

bool World::has_key_item(const string & item) const
{
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    if(m_key_items[i].m_name == item)
    {
      return true;
    }
  }
  return false;
}

void World::add_key_item(const string & item)
{
  //Does it already exist?
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    if(m_key_items[i].m_name == item)
    {
      //Yes it does, exit
      return;
    }
  }
  //No it doesn't, add it to the list
  for(long i{0}; i < static_cast<long>(ITEM_DATABASE.size()); ++i)
  {
    if(ITEM_DATABASE[i].m_name == item)
    {
      m_key_items.push_back(ITEM_DATABASE[i]);
    }
  }
}

void World::remove_key_item(const string & item)
{
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    if(m_key_items[i].m_name == item)
    {
      // erase it
      m_key_items.erase(m_key_items.begin() + i);
      return;
    }
  }
}

string World::get_time() const
{
  string hours{to_string(m_time.get_ticks() / 3600)};
  long minutes{m_time.get_ticks() / 60 % 60};
  string min_str;
  (minutes < 10) ? (min_str = "0" + to_string(minutes)) : (min_str = to_string(minutes));
  long seconds{m_time.get_ticks() % 60};
  string sec_str;
  (seconds < 10) ? (sec_str = "0" + to_string(seconds)) : (sec_str = to_string(seconds));
  return hours + ":" + min_str + ":" + sec_str;
}

long World::get_money() const
{
  return m_money;
}

void World::pause_time()
{
  m_time.pause();
}

void World::unpause_time()
{
  m_time.unpause();
}

string World::get_party_member_name(const long & index) const
{
  return m_party.get_member_name(index);
}

string World::get_party_member_species(const string & index) const
{
  return m_party.get_member_species(index);
}

string World::get_party_member_class(const string & index) const
{
  return m_party.get_member_class(index);
}

long World::get_party_member_portrait_width(const string & index) const
{
  return m_party.get_member_portrait_width(index);
}

long World::get_party_member_portrait_height(const string & index) const
{
  return m_party.get_member_portrait_height(index);
}

long World::get_party_member_small_portrait_width(const string & index) const
{
  return m_party.get_member_small_portrait_width(index);
}

long World::get_party_member_small_portrait_height(const string & index) const
{
  return m_party.get_member_small_portrait_height(index);
}

long World::get_party_member_stat(const string & index, const string & stat) const
{
  return m_party.get_member_stat(index, stat);
}

long World::get_party_member_unmodified_stat(const string & index, const string & stat) const
{
  return m_party.get_member_unmodified_stat(index, stat);
}

bool World::get_party_member_row(const string & index) const
{
  return m_party.get_member_row(index);
}

long World::get_party_member_soul_break_level(const string & index) const
{
  return m_party.get_member_soul_break_level(index);
}

void World::render_party_member_portrait(const string & index, const bool & size, const long & x, const long & y) const
{
  return m_party.render_member_portrait(index, size, x, y);
}

long World::get_party_size() const
{
  return m_party.get_size();
}

void World::set_party_member_front_row(const string & index)
{
  m_party.set_member_front_row(index);
}

void World::set_party_member_back_row(const string & index)
{
  m_party.set_member_back_row(index);
}

void World::swap_party_members(const string & name1, const string & name2)
{
  m_party.swap_party_members(name1, name2);
}