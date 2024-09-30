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

long Stat_Modifier::get_replace_modifier() const
{
  return m_replace_modifier;
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
  else if(stat == "Strength")
  {
    return m_strength;
  }
  else if(stat == "Attack")
  {
    return m_attack;
  }
  else if(stat == "Speed")
  {
    return 0;
  }
  else if(stat == "Defense")
  {
    return m_defense;
  }
  else if(stat == "Intellect")
  {
    return m_intellect;
  }
  else if(stat == "Resistance")
  {
    return m_resistance;
  }
  else if(stat == "Stamina")
  {
    return m_stamina;
  }
  else if(stat == "Accuracy")
  {
    return m_accuracy;
  }
  else if(stat == "Spirit")
  {
    return m_spirit;
  }
  else if(stat == "Critical")
  {
    return m_critical;
  }
  else if(stat == "Evasion")
  {
    return m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    return m_magic_evasion;
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
  else if(stat == "Strength")
  {
    unmodified_stat = m_strength;
  }
  else if(stat == "Attack")
  {
    unmodified_stat = m_attack;
  }
  else if(stat == "Speed")
  {
    unmodified_stat = 0;
  }
  else if(stat == "Defense")
  {
    unmodified_stat = m_defense;
  }
  else if(stat == "Intellect")
  {
    unmodified_stat = m_intellect;
  }
  else if(stat == "Resistance")
  {
    unmodified_stat = m_resistance;
  }
  else if(stat == "Stamina")
  {
    unmodified_stat = m_stamina;
  }
  else if(stat == "Accuracy")
  {
    unmodified_stat = m_accuracy;
  }
  else if(stat == "Spirit")
  {
    unmodified_stat = m_spirit;
  }
  else if(stat == "Critical")
  {
    unmodified_stat = m_critical;
  }
  else if(stat == "Evasion")
  {
    unmodified_stat = m_evasion;
  }
  else if(stat == "Magic Evasion")
  {
    unmodified_stat = m_magic_evasion;
  }
  else
  {
    crash("Error: Tried to get invalid stat \"" + stat + "\".");
  }

  for(long i{0}; i < static_cast<long>(m_modifiers.size()); ++i)
  {
    if(m_modifiers[i].get_stat() == stat)
    {
      if(m_modifiers[i].get_type() == "Replace")
      {
        return m_modifiers[i].get_replace_modifier();
      }
    }
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
  return modified_stat;
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
  else if(stat == "Speed")
  {
    return 0;
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

string Item::get_name() const
{
  return m_name;
}

string Item::get_type() const
{
  return m_type;
}

long Item::get_icon() const
{
  return m_icon;
}

long Item::get_count() const
{
  return -1;
}

Consumable_Item::Consumable_Item(const string & name, const string & description)
{
  m_name = name;
  m_type = "Consumable Item";
  m_description = description;
  m_icon = CONSUMABLE_ITEM_ICON;
  m_count = 1;
}

string Consumable_Item::get_description() const
{
  return m_description;
}

void Consumable_Item::increment_count()
{
  ++m_count;
}

void Consumable_Item::decrement_count()
{
  --m_count;
}

long Consumable_Item::get_count() const
{
  return m_count;
}

Key_Item::Key_Item(const string & name, const string & description)
{
  m_name = name;
  m_type = "Key Item";
  m_description = description;
  m_icon = KEY_ITEM_ICON;
}

string Key_Item::get_description() const
{
  return m_description;
}

Equipment::Equipment(const string & name, const string & type, const string & description, const long & icon, const vector<Stat_Modifier> stats, const vector<string> & usable_by, const string & equipped_by)
{
  m_name = name;
  m_type = type;
  m_description = description;
  m_icon = icon;
  m_count = 1;
  m_stats = stats;
  m_usable_by = usable_by;
  m_equipped_by = equipped_by;
}

string Equipment::get_description() const
{
  string next{""};
  for(long i{0}; i < static_cast<long>(m_stats.size()); ++i)
  {
    if(m_stats[i].get_type() == "Add")
    {
      next += (m_stats[i].get_add_modifier() < 0 ? " " : " +") + to_string(m_stats[i].get_add_modifier()) + " " + m_stats[i].get_stat() + ",";
    }
    else if(m_stats[i].get_type() == "Replace")
    {
      next += " " + to_string(m_stats[i].get_replace_modifier()) + " " + m_stats[i].get_stat() + ",";
    }
    if(m_stats[i].get_type() == "Multiply")
    {
      next += " x" + to_string(m_stats[i].get_multiply_modifier()) + " " + m_stats[i].get_stat() + ",";
    }
  }
  if(next.empty() == false)
  {
    next.pop_back();
  }
  return m_description + next;
}

void Equipment::increment_count()
{
  ++m_count;
}

void Equipment::decrement_count()
{
  --m_count;
}

long Equipment::get_count() const
{
  return m_count;
}

bool Equipment::can_equip(const string & party_member_name) const
{
  if(m_usable_by.empty() == true)
  {
    return true;
  }
  for(long i{0}; i < static_cast<long>(m_usable_by.size()); ++i)
  {
    if(party_member_name == m_usable_by[i])
    {
      return true;
    }
  }
  return false;
}

void Equipment::set_equip_by(const string & name)
{
  m_equipped_by = name;
}

string Equipment::equipped_by() const
{
  return m_equipped_by;
}

Party_Member::Party_Member(const Player_Info & player)
{
  m_name = player.m_name;
  m_species = player.m_species;
  m_class = player.m_class;
  m_row = player.m_starting_row;
  m_soul_break_level = 1;
  m_stats = Player_Stats{player.m_stats};
  m_icon = player.m_icon;
  Image image{LoadImageFromMemory(".png", player.m_portrait_data, player.m_portrait_size)};
  m_portrait = LoadTextureFromImage(image);
  UnloadImage(image);
  
  Image image2{LoadImageFromMemory(".png", player.m_small_portrait_data, player.m_small_portrait_size)};
  m_small_portrait = LoadTextureFromImage(image2);
  UnloadImage(image2);

  m_font = new Fnt(player.m_font);
  ++mem;
}

Party_Member::~Party_Member()
{
  UnloadTexture(m_portrait);
  UnloadTexture(m_small_portrait);
  delete m_font;
  m_font = nullptr;
  --mem;
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

bool Party_Member::set_front_row()
{
  bool ret{m_row == false};
  m_row = true;
  return ret;
}

bool Party_Member::set_back_row()
{
  bool ret{m_row == true};
  m_row = false;
  return ret;
}

void Party_Member::give_member_exp(const long & exp)
{
  m_stats.give_exp(exp);
}

void Party_Member::level_up()
{
  m_stats.level_up();
}

void Party_Member::equip(World* world, const string & item_name)
{
  string item_type{world->get_equipment_type(item_name)};

  if(item_type == "Weapon")
  {
    if(m_equipped_weapon == nullptr)
    {
      m_equipped_weapon = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
  }
  if(item_type == "Shield")
  {
    if(m_equipped_offhand == nullptr)
    {
      m_equipped_offhand = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
  }
  if(item_type == "Helm")
  {
    if(m_equipped_helmet == nullptr)
    {
      m_equipped_helmet = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
  }
  if(item_type == "Armor")
  {
    if(m_equipped_armor == nullptr)
    {
      m_equipped_armor = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
  }
  if(item_type == "Accessory")
  {
    if(m_equipped_accessory_one == nullptr)
    {
      m_equipped_accessory_one = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
    else if(m_equipped_accessory_two == nullptr)
    {
      m_equipped_accessory_two = world->get_equipment(item_name);
      world->get_equipment(item_name)->set_equip_by(m_name);
      world->remove_equipment(item_name);
    }
  }
}

Equipment* Party_Member::get_equipped_weapon() const
{
  return m_equipped_weapon;
}

Equipment* Party_Member::get_equipped_shield() const
{
  return m_equipped_offhand;
}

Equipment* Party_Member::get_equipped_helm() const
{
  return m_equipped_helmet;
}

Equipment* Party_Member::get_equipped_armor() const
{
  return m_equipped_armor;
}

Equipment* Party_Member::get_equipped_accessory_one() const
{
  return m_equipped_accessory_one;
}

Equipment* Party_Member::get_equipped_accessory_two() const
{
  return m_equipped_accessory_two;
}

long Party_Member::get_icon() const
{
  return m_icon;
}

Fnt* Party_Member::get_font() const
{
  return m_font;
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

string Party::get_next_member_name(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      if(i + 1 == static_cast<long>(m_members.size()))
      {
        return m_members[0]->get_name();
      }
      return m_members[i + 1]->get_name();
    }
  }
  crash("Error: Tried to get the party member after " + name + ", which is invalid.");
  return "NULL";
}

string Party::get_previous_member_name(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      if(i - 1 < 0)
      {
        return m_members[m_members.size() - 1]->get_name();
      }
      return m_members[i - 1]->get_name();
    }
  }
  crash("Error: Tried to get the party member before " + name + ", which is invalid.");
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

bool Party::set_member_front_row(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->set_front_row();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return false;
}

bool Party::set_member_back_row(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i]->set_back_row();
    }
  }
  crash("Error: Tried to get invalid party member " + name + ".");
  return false;
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

void Party::equip(World* world, const string & party_member_name, const string & item_name)
{
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == party_member_name)
    {
      m_members[i]->equip(world, item_name);
    }
  }
}

vector<Equipment*> Party::get_equipped_equipment() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_weapon());
    }
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_shield());
    }
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_helm());
    }
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_armor());
    }
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_accessory_one());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_accessory_two());
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_weapons() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_weapon());
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_shields() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_shield());
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_helms() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_helm());
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_armor() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_armor());
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_accessories() const
{
  vector<Equipment*> equipment{};
  for(long i{0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_accessory_one());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      equipment.push_back(m_members[i]->get_equipped_accessory_two());
    }
  }
  return equipment;
}

Party_Member* Party::get_member(const string & name) const
{
  for(long i {0}; i < static_cast<long>(m_members.size()); ++i)
  {
    if(m_members[i]->get_name() == name)
    {
      return m_members[i];
    }
  }
  crash("Error: \"" + name + "\" isn't in the party.");
  return nullptr;
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
  #include "Consts/Item_Consts.h"

  m_cursor = new Cursor;
  ++mem;
  
  m_fonts.push_back(new Fnt);
  ++mem;
  m_fonts.push_back(new Fnt{HEADING_FONT});
  ++mem;
  m_fonts.push_back(new Fnt{CHARACTER_TITLE_FONT});
  ++mem;
  m_fonts.push_back(new Fnt{RED_FONT});
  ++mem;

  m_time.start();

  Image image{LoadImageFromMemory(".png", INVENTORY_ICONS_IMAGE.m_data, INVENTORY_ICONS_IMAGE.m_size)};
  m_item_icons_tex = LoadTextureFromImage(image);
  UnloadImage(image);
  Image image2{LoadImageFromMemory(".png", PANEL_IMAGE.m_data, PANEL_IMAGE.m_size)};
  m_panel_texture = LoadTextureFromImage(image2);
  UnloadImage(image2);
  Image image3{LoadImageFromMemory(".png", CONTINUE_ARROW_IMAGE.m_data, CONTINUE_ARROW_IMAGE.m_size)};
  m_continue_arrow_texture = LoadTextureFromImage(image3);
  UnloadImage(image3);
  
  m_party.add_party_member(TEMPEST_SHADOW_INFO);
  
  Wave wave{LoadWaveFromMemory(".wav", CURSOR_SOUND.m_data, CURSOR_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave));
  UnloadWave(wave);
  Wave wave2{LoadWaveFromMemory(".wav", CONFIRM_SOUND.m_data, CONFIRM_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave2));
  UnloadWave(wave2);
  Wave wave3{LoadWaveFromMemory(".wav", BACK_SOUND.m_data, BACK_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave3));
  UnloadWave(wave3);
  Wave wave4{LoadWaveFromMemory(".wav", BUZZER_SOUND.m_data, BUZZER_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave4));
  UnloadWave(wave4);
  
  m_global_sound_names.push_back(CURSOR_SOUND.m_name);
  m_global_sound_names.push_back(CONFIRM_SOUND.m_name);
  m_global_sound_names.push_back(BACK_SOUND.m_name);
  m_global_sound_names.push_back(BUZZER_SOUND.m_name);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_BACKGROUND_IMAGE.m_name);
  Image progress_bar1{LoadImageFromMemory(".png", PROGRESS_BAR_BACKGROUND_IMAGE.m_data, PROGRESS_BAR_BACKGROUND_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar1));
  UnloadImage(progress_bar1);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_BLUE_IMAGE.m_name);
  Image progress_bar2{LoadImageFromMemory(".png", PROGRESS_BAR_BLUE_IMAGE.m_data, PROGRESS_BAR_BLUE_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar2));
  UnloadImage(progress_bar2);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_GREEN_IMAGE.m_name);
  Image progress_bar3{LoadImageFromMemory(".png", PROGRESS_BAR_GREEN_IMAGE.m_data, PROGRESS_BAR_GREEN_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar3));
  UnloadImage(progress_bar3);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_ORANGE_IMAGE.m_name);
  Image progress_bar4{LoadImageFromMemory(".png", PROGRESS_BAR_ORANGE_IMAGE.m_data, PROGRESS_BAR_ORANGE_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar4));
  UnloadImage(progress_bar4);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_PINK_IMAGE.m_name);
  Image progress_bar5{LoadImageFromMemory(".png", PROGRESS_BAR_PINK_IMAGE.m_data, PROGRESS_BAR_PINK_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar5));
  UnloadImage(progress_bar5);

  m_progress_bar_image_names.push_back(PROGRESS_BAR_RED_IMAGE.m_name);
  Image progress_bar6{LoadImageFromMemory(".png", PROGRESS_BAR_RED_IMAGE.m_data, PROGRESS_BAR_RED_IMAGE.m_size)};
  m_progress_bar_textures.push_back(LoadTextureFromImage(progress_bar6));
  UnloadImage(progress_bar6);
}

World::~World()
{
  UnloadTexture(m_item_icons_tex);
  UnloadTexture(m_panel_texture);
  UnloadTexture(m_continue_arrow_texture);
  delete m_cursor;
  m_cursor = nullptr;
  --mem;
  for(long i{0}; i < static_cast<long>(m_progress_bar_textures.size()); ++i)
  {
    UnloadTexture(m_progress_bar_textures[i]);
  }
  for(long i{0}; i < static_cast<long>(m_fonts.size()); ++i)
  {
    delete m_fonts[i];
    m_fonts[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_global_sounds.size()); ++i)
  {
    UnloadSound(m_global_sounds[i]);
  }
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    delete m_items[i];
    m_items[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    delete m_key_items[i];
    m_key_items[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    delete m_equipment[i];
    m_equipment[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    delete m_item_database[i];
    m_item_database[i] = nullptr;
    --mem;
  }
}

void World::update()
{
  m_party.update_stats();
  m_cursor->finish();
  m_cursor->update();
}

bool World::can_use_weapon(const string & party_member_name, const long & item_index) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_weapons().size()))
  {
    string name{get_weapons().at(item_index)};
    for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
    {
      if(name == m_equipment[i]->get_name())
      {
        equipment = m_equipment[i];
      }
    }
    if(equipment == nullptr)
    {
      vector<Equipment*> equipped_equipment{m_party.get_equipped_equipment()};
      for(long i{0}; i < static_cast<long>(equipped_equipment.size()); ++i)
      {
        if(name == equipped_equipment[i]->get_name())
        {
          equipment = equipped_equipment[i];
        }
      }
    }
  }

  if(equipment != nullptr)
  {
    if(equipment->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

bool World::can_use_shield(const string & party_member_name, const long & item_index) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_shields().size()))
  {
    string name{get_shields().at(item_index)};
    for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
    {
      if(name == m_equipment[i]->get_name())
      {
        equipment = m_equipment[i];
      }
    }
    if(equipment == nullptr)
    {
      vector<Equipment*> equipped_equipment{m_party.get_equipped_equipment()};
      for(long i{0}; i < static_cast<long>(equipped_equipment.size()); ++i)
      {
        if(name == equipped_equipment[i]->get_name())
        {
          equipment = equipped_equipment[i];
        }
      }
    }
  }

  if(equipment != nullptr)
  {
    if(equipment->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

bool World::can_use_helm(const string & party_member_name, const long & item_index) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_helms().size()))
  {
    string name{get_helms().at(item_index)};
    for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
    {
      if(name == m_equipment[i]->get_name())
      {
        equipment = m_equipment[i];
      }
    }
    if(equipment == nullptr)
    {
      vector<Equipment*> equipped_equipment{m_party.get_equipped_equipment()};
      for(long i{0}; i < static_cast<long>(equipped_equipment.size()); ++i)
      {
        if(name == equipped_equipment[i]->get_name())
        {
          equipment = equipped_equipment[i];
        }
      }
    }
  }

  if(equipment != nullptr)
  {
    if(equipment->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

bool World::can_use_armor(const string & party_member_name, const long & item_index) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_armor().size()))
  {
    string name{get_armor().at(item_index)};
    for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
    {
      if(name == m_equipment[i]->get_name())
      {
        equipment = m_equipment[i];
      }
    }
    if(equipment == nullptr)
    {
      vector<Equipment*> equipped_equipment{m_party.get_equipped_equipment()};
      for(long i{0}; i < static_cast<long>(equipped_equipment.size()); ++i)
      {
        if(name == equipped_equipment[i]->get_name())
        {
          equipment = equipped_equipment[i];
        }
      }
    }
  }

  if(equipment != nullptr)
  {
    if(equipment->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

bool World::can_use_accessory(const string & party_member_name, const long & item_index) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_accessories().size()))
  {
    string name{get_accessories().at(item_index)};
    for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
    {
      if(name == m_equipment[i]->get_name())
      {
        equipment = m_equipment[i];
      }
    }
    if(equipment == nullptr)
    {
      vector<Equipment*> equipped_equipment{m_party.get_equipped_equipment()};
      for(long i{0}; i < static_cast<long>(equipped_equipment.size()); ++i)
      {
        if(name == equipped_equipment[i]->get_name())
        {
          equipment = equipped_equipment[i];
        }
      }
    }
  }

  if(equipment != nullptr)
  {
    if(equipment->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

void World::equip(World* world, const string & party_member_name, const string & item_name)
{
  m_party.equip(world, party_member_name, item_name);
}

void World::render_item(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  if(item_index >= 0 && item_index < static_cast<long>(m_items.size()))
  {
    long current_pos{x};
    DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_items[item_index]->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
    current_pos += ICON_WIDTH;

    string text{m_items[item_index]->get_name()};
    while(text != "")
    {
      m_fonts[font_no]->render_letter(current_pos, y, text[0]);
      current_pos += m_fonts[font_no]->get_char_width(text[0]);
      text.erase(text.begin());
    }

    current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
    text = "x" + to_string(m_items[item_index]->get_count());
    while(text != "")
    {
      m_fonts[font_no]->render_letter(current_pos, y, text[0]);
      current_pos += m_fonts[font_no]->get_char_width(text[0]);
      text.erase(text.begin());
    }
  }
}

void World::render_key_item(const long & x, const long & y, const long & font_no, const long & item_index) const
{
  if(item_index >= 0 && item_index < static_cast<long>(m_key_items.size()))
  {
    long current_pos{x};
    DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_key_items[item_index]->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
    current_pos += ICON_WIDTH;

    string text{m_key_items[item_index]->get_name()};
    while(text != "")
    {
      m_fonts[font_no]->render_letter(current_pos, y, text[0]);
      current_pos += m_fonts[font_no]->get_char_width(text[0]);
      text.erase(text.begin());
    }
  }
}

void World::render_weapon(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_weapons().size()))
  {
    string name{get_weapons().at(item_index)};
    long num_equipped_weapons{static_cast<long>(m_party.get_equipped_weapons().size())};
    if(item_index < num_equipped_weapons)
    {
      equipment = m_party.get_equipped_weapons().at(item_index);
    }
    else
    {
      for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
      {
        if(name == m_equipment[i]->get_name())
        {
          equipment = m_equipment[i];
        }
      }
    }

    long current_pos{x};
    if(equipment->equipped_by() == "NULL")
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * equipment->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(equipment->get_count());
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
    else
    {
      Party_Member* member{m_party.get_member(equipment->equipped_by())};
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * member->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (member->get_font()->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "E";
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
}

void World::render_shield(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_shields().size()))
  {
    string name{get_shields().at(item_index)};
    long num_equipped_weapons{static_cast<long>(m_party.get_equipped_shields().size())};
    if(item_index < num_equipped_weapons)
    {
      equipment = m_party.get_equipped_shields().at(item_index);
    }
    else
    {
      for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
      {
        if(name == m_equipment[i]->get_name())
        {
          equipment = m_equipment[i];
        }
      }
    }

    long current_pos{x};
    if(equipment->equipped_by() == "NULL")
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * equipment->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(equipment->get_count());
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
    else
    {
      Party_Member* member{m_party.get_member(equipment->equipped_by())};
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * member->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (member->get_font()->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "E";
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
}

void World::render_helm(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_helms().size()))
  {
    string name{get_helms().at(item_index)};
    long num_equipped_weapons{static_cast<long>(m_party.get_equipped_helms().size())};
    if(item_index < num_equipped_weapons)
    {
      equipment = m_party.get_equipped_helms().at(item_index);
    }
    else
    {
      for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
      {
        if(name == m_equipment[i]->get_name())
        {
          equipment = m_equipment[i];
        }
      }
    }

    long current_pos{x};
    if(equipment->equipped_by() == "NULL")
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * equipment->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(equipment->get_count());
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
    else
    {
      Party_Member* member{m_party.get_member(equipment->equipped_by())};
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * member->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (member->get_font()->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "E";
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
}

void World::render_armor(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_armor().size()))
  {
    string name{get_armor().at(item_index)};
    long num_equipped_weapons{static_cast<long>(m_party.get_equipped_armor().size())};
    if(item_index < num_equipped_weapons)
    {
      equipment = m_party.get_equipped_armor().at(item_index);
    }
    else
    {
      for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
      {
        if(name == m_equipment[i]->get_name())
        {
          equipment = m_equipment[i];
        }
      }
    }

    long current_pos{x};
    if(equipment->equipped_by() == "NULL")
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * equipment->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(equipment->get_count());
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
    else
    {
      Party_Member* member{m_party.get_member(equipment->equipped_by())};
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * member->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (member->get_font()->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "E";
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
}

void World::render_accessory(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const
{
  Equipment* equipment{nullptr};
  if(item_index >= 0 && item_index < static_cast<long>(get_accessories().size()))
  {
    string name{get_accessories().at(item_index)};
    long num_equipped_weapons{static_cast<long>(m_party.get_equipped_accessories().size())};
    if(item_index < num_equipped_weapons)
    {
      equipment = m_party.get_equipped_accessories().at(item_index);
    }
    else
    {
      for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
      {
        if(name == m_equipment[i]->get_name())
        {
          equipment = m_equipment[i];
        }
      }
    }

    long current_pos{x};
    if(equipment->equipped_by() == "NULL")
    {
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * equipment->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_no]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(equipment->get_count());
      while(text != "")
      {
        m_fonts[font_no]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_no]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
    else
    {
      Party_Member* member{m_party.get_member(equipment->equipped_by())};
      DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * member->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (member->get_font()->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      current_pos += ICON_WIDTH;

      string text{equipment->get_name()};
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "E";
      while(text != "")
      {
        member->get_font()->render_letter(current_pos, y, text[0]);
        current_pos += member->get_font()->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
}

void World::render_stat(const long & x, const long & y, const long & font_no, const long & item_index, const long & width, const string & name) const
{
  long current_pos{static_cast<long>(x + width * STAT_LOCATION_FRACTION)};
  string text;

  switch(item_index)
  {
    case 0:
      text = to_string(m_party.get_member_stat(name, "Strength")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Strength")) + ")";
      break;
    case 1:
      text = to_string(m_party.get_member_stat(name, "Attack")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Attack")) + ")";
      break;
    case 3:
      text = to_string(m_party.get_member_stat(name, "Speed")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Speed")) + ")";
      break;
    case 4:
      text = to_string(m_party.get_member_stat(name, "Defense")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Defense")) + ")";
      break;
    case 6:
      text = to_string(m_party.get_member_stat(name, "Intellect")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Intellect")) + ")";
      break;
    case 7:
      text = to_string(m_party.get_member_stat(name, "Resistance")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Resistance")) + ")";
      break;
    case 9:
      text = to_string(m_party.get_member_stat(name, "Stamina")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Stamina")) + ")";
      break;
    case 10:
      text = to_string(m_party.get_member_stat(name, "Accuracy")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Accuracy")) + ")";
      break;
    case 12:
      text = to_string(m_party.get_member_stat(name, "Spirit")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Spirit")) + ")";
      break;
    case 13:
      text = to_string(m_party.get_member_stat(name, "Critical")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Critical")) + ")";
      break;
    case 15:
      text = to_string(m_party.get_member_stat(name, "Evasion")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Evasion")) + ")";
      break;
    case 16:
      text = to_string(m_party.get_member_stat(name, "Magic Evasion")) + " (" + to_string(m_party.get_member_unmodified_stat(name, "Magic Evasion")) + ")";
      break;
    default:
      break;
  }

  while(text != "")
  {
    m_fonts[font_no]->render_letter(current_pos, y, text[0]);
    current_pos += m_fonts[font_no]->get_char_width(text[0]);
    text.erase(text.begin());
  }
}

void World::render_cursor() const
{
  m_cursor->render();
}

void World::render_text_center(const long & font_no, const string & text, const long & y_pos, const long & alpha) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  else
  {
    m_fonts[font_no]->render_text_center(text, y_pos, alpha);
  }
}

void World::render_text(const long & font_no, const string & text, const long & x_pos, const long & y_pos, const long & alpha) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  else
  {
    m_fonts[font_no]->render_text(text, x_pos, y_pos, alpha);
  }
}

void World::render_letter(const long & font_no, const long & x, const long & y, const char & id, const long & alpha) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  else
  {
    m_fonts[font_no]->render_letter(x, y, id, alpha);
  }
}

void World::render_panel(const double & x, const double & y, const double & w, const double & h) const
{
  // corners
  DrawTexturePro(m_panel_texture, Rectangle{0, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 2, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + w - PANEL_TILE_WIDTH), static_cast<float>(y), PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 6, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + h - m_panel_texture.height), PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 8, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + w - PANEL_TILE_WIDTH), static_cast<float>(y + h - m_panel_texture.height), PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});

  // edges
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + PANEL_TILE_WIDTH), static_cast<float>(y), static_cast<float>(w - PANEL_TILE_WIDTH * 2), static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 3, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + m_panel_texture.height), PANEL_TILE_WIDTH, static_cast<float>(h - m_panel_texture.height * 2)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 5, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + w - PANEL_TILE_WIDTH), static_cast<float>(y + m_panel_texture.height), PANEL_TILE_WIDTH, static_cast<float>(h - m_panel_texture.height * 2)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 7, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + PANEL_TILE_WIDTH), static_cast<float>(y + h - m_panel_texture.height), static_cast<float>(w - PANEL_TILE_WIDTH * 2), static_cast<float>(m_panel_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});

  // middle
  DrawTexturePro(m_panel_texture, Rectangle{PANEL_TILE_WIDTH * 4, 0, PANEL_TILE_WIDTH, static_cast<float>(m_panel_texture.height)}, Rectangle{static_cast<float>(x + PANEL_TILE_WIDTH), static_cast<float>(y + m_panel_texture.height), static_cast<float>(w - PANEL_TILE_WIDTH * 2), static_cast<float>(h - m_panel_texture.height * 2)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, PANEL_ALPHA});
}

void World::render_continue_arrow(const long & x, const long & y) const
{
  DrawTexturePro(m_continue_arrow_texture, Rectangle{0, 0, static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Rectangle{static_cast<float>(x - m_continue_arrow_texture.width / 2), static_cast<float>(y), static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void World::render_progress_bar(const string & progress_bar_name, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_progress_bar_image_names.size()); ++i)
  {
    if(m_progress_bar_image_names[i] == progress_bar_name)
    {
      DrawTexturePro(m_progress_bar_textures[i], Rectangle{0, 0, static_cast<float>(m_progress_bar_textures[i].width), static_cast<float>(m_progress_bar_textures[i].height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_progress_bar_textures[i].width), static_cast<float>(m_progress_bar_textures[i].height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
    }
  }
}

vector<string> World::get_items() const
{
  vector<string> items;
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    items.push_back(m_items[i]->get_name());
  }
  return items;
}

vector<string> World::get_key_items() const
{
  vector<string> key_items;
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    key_items.push_back(m_key_items[i]->get_name());
  }
  return key_items;
}

vector<string> World::get_weapons() const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_weapons()};
  vector<string> items;
  for(long i{0}; i < static_cast<long>(equipped_weapons.size()); ++i)
  {
    items.push_back(equipped_weapons[i]->get_name());
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      items.push_back(m_equipment[i]->get_name());
    }
  }
  return items;
}

vector<string> World::get_shields() const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_shields()};
  vector<string> items;
  for(long i{0}; i < static_cast<long>(equipped_weapons.size()); ++i)
  {
    items.push_back(equipped_weapons[i]->get_name());
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      items.push_back(m_equipment[i]->get_name());
    }
  }
  return items;
}

vector<string> World::get_helms() const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_helms()};
  vector<string> items;
  for(long i{0}; i < static_cast<long>(equipped_weapons.size()); ++i)
  {
    items.push_back(equipped_weapons[i]->get_name());
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      items.push_back(m_equipment[i]->get_name());
    }
  }
  return items;
}

vector<string> World::get_armor() const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_armor()};
  vector<string> items;
  for(long i{0}; i < static_cast<long>(equipped_weapons.size()); ++i)
  {
    items.push_back(equipped_weapons[i]->get_name());
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      items.push_back(m_equipment[i]->get_name());
    }
  }
  return items;
}

vector<string> World::get_accessories() const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_accessories()};
  vector<string> items;
  for(long i{0}; i < static_cast<long>(equipped_weapons.size()); ++i)
  {
    items.push_back(equipped_weapons[i]->get_name());
  }
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      items.push_back(m_equipment[i]->get_name());
    }
  }
  return items;
}

string World::get_item_description(const string & item_name) const
{
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    if(m_item_database[i]->get_name() == item_name)
    {
      return m_item_database[i]->get_description();
    }
  }
  crash("Error: Item \"" + item_name + "\" is not in the game.");
  return "NULL";
}

bool World::has_items() const
{
  return !m_items.empty();
}

bool World::has_item(const string & item) const
{
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i]->get_name() == item)
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
    if(m_items[i]->get_name() == item)
    {
      //Yes it does, increase the count and exit
      m_items[i]->increment_count();
      return;
    }
  }
  //No it doesn't, add it to the list
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    if(m_item_database[i]->get_type() == "Consumable Item" && m_item_database[i]->get_name() == item)
    {
      m_items.push_back(new Consumable_Item{*dynamic_cast<Consumable_Item*>(m_item_database[i])});
      ++mem;
    }
  }
}

void World::remove_item(const string & item)
{
  for(long i{0}; i < static_cast<long>(m_items.size()); ++i)
  {
    if(m_items[i]->get_name() == item)
    {
      if(m_items[i]->get_count() > 0)
      {
        m_items[i]->decrement_count();
        if(m_items[i]->get_count() == 0)
        {
          // erase it
          delete m_items[i];
          m_items[i] = nullptr;
          m_items.erase(m_items.begin() + i);
          --mem;
          return;
        }
      }
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
    if(m_key_items[i]->get_name() == item)
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
    if(m_key_items[i]->get_name() == item)
    {
      //Yes it does, exit
      return;
    }
  }
  //No it doesn't, add it to the list
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    if(m_item_database[i]->get_type() == "Key Item" && m_item_database[i]->get_name() == item)
    {
      m_key_items.push_back(new Key_Item{*dynamic_cast<Key_Item*>(m_item_database[i])});
      ++mem;
    }
  }
}

void World::remove_key_item(const string & item)
{
  for(long i{0}; i < static_cast<long>(m_key_items.size()); ++i)
  {
    if(m_key_items[i]->get_name() == item)
    {
      delete m_key_items[i];
      m_key_items[i] = nullptr;
      m_key_items.erase(m_key_items.begin() + i);
      --mem;
      return;
    }
  }
}

bool World::has_weapons() const
{
  return !get_weapons().empty();
}

bool World::has_shields() const
{
  return !get_shields().empty();
}

bool World::has_helms() const
{
  return !get_helms().empty();
}

bool World::has_armor() const
{
  return !get_armor().empty();
}

bool World::has_accessories() const
{
  return !get_accessories().empty();
}

bool World::has_equipment(const string & item) const
{
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_name() == item)
    {
      return true;
    }
  }
  for(long i{0}; i < static_cast<long>(m_party.get_equipped_equipment().size()); ++i)
  {
    if(m_party.get_equipped_equipment().at(i)->get_name() == item)
    {
      return true;
    }
  }
  return false;
}

void World::add_equipment(const string & item)
{
  //Does it already exist?
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_name() == item)
    {
      //Yes it does, increase the count and exit
      m_equipment[i]->increment_count();
      return;
    }
  }
  //No it doesn't, add it to the list
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    if((m_item_database[i]->get_type() == "Weapon" || m_item_database[i]->get_type() == "Shield" || m_item_database[i]->get_type() == "Helm" || m_item_database[i]->get_type() == "Armor" || m_item_database[i]->get_type() == "Accessory") && m_item_database[i]->get_name() == item)
    {
      m_equipment.push_back(new Equipment{*dynamic_cast<Equipment*>(m_item_database[i])});
      ++mem;
    }
  }
}

void World::remove_equipment(const string & item)
{
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(m_equipment[i]->get_name() == item)
    {
      if(m_equipment[i]->get_count() > 0)
      {
        m_equipment[i]->decrement_count();
        if(m_equipment[i]->get_count() == 0)
        {
          // erase it
          delete m_equipment[i];
          m_equipment[i] = nullptr;
          m_equipment.erase(m_equipment.begin() + i);
          --mem;
          return;
        }
      }
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

void World::set_cursor_destination(const long & end_x, const long & end_y)
{
  m_cursor->set_destination(end_x, end_y);
}

long World::get_font_height(const long & font_no) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  return m_fonts[font_no]->get_height();
}

long World::get_word_width(const long & font_no, const string & text) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  return m_fonts[font_no]->get_word_width(text);
}

long World::get_char_width(const long & font_no, const char & text) const
{
  if(font_no < 0 || font_no >= static_cast<long>(m_fonts.size()))
  {
    crash("Error: The game doesn't have " + to_string(font_no) + " fonts.");
  }
  return m_fonts[font_no]->get_char_width(text);
}

void World::play_global_sound(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_global_sounds.size()); ++i)
  {
    if(m_global_sound_names[i] == name)
    {
      PlaySound(m_global_sounds[i]);
      return;
    }
  }
  crash("Error: Global sound effect \"" + name + "\" doesn't exist.");
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

string World::get_next_party_member_name(const string & name) const
{
  return m_party.get_next_member_name(name);
}

string World::get_previous_party_member_name(const string & name) const
{
  return m_party.get_previous_member_name(name);
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

bool World::set_party_member_front_row(const string & index)
{
  return m_party.set_member_front_row(index);
}

bool World::set_party_member_back_row(const string & index)
{
  return m_party.set_member_back_row(index);
}

void World::swap_party_members(const string & name1, const string & name2)
{
  m_party.swap_party_members(name1, name2);
}

void World::add_party_member(const Player_Info & player)
{
  m_party.add_party_member(player);
}

string World::get_equipment_type(const string & item_name) const
{
  for(long i{0}; i < static_cast<long>(m_equipment.size()); ++i)
  {
    if(item_name == m_equipment[i]->get_name())
    {
      return m_equipment[i]->get_type();
    }
  }
  for(long i{0}; i < static_cast<long>(m_party.get_equipped_equipment().size()); ++i)
  {
    if(item_name == m_party.get_equipped_equipment().at(i)->get_name())
    {
      return m_party.get_equipped_equipment().at(i)->get_type();
    }
  }
  crash("Error: \"" + item_name + "\" in not in the equipment list.");
  return "NULL";
}

Equipment* World::get_equipment(const string & item_name) const
{
  for(long i{0}; i < static_cast<long>(m_item_database.size()); ++i)
  {
    if(item_name == m_item_database[i]->get_name())
    {
      return dynamic_cast<Equipment*>(m_item_database[i]);
    }
  }
  crash("Error: \"" + item_name + "\" in not in the game.");
  return nullptr;
}
