#include "Main.h"
#include "World.h"

bool Stat_Modifier::operator==(const Stat_Modifier & rhs) const
{
  return m_id == rhs.get_id() && m_slot == rhs.get_slot();
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

void Stat_Modifier::set_slot(const long & slot)
{
  m_slot = slot;
}

long Stat_Modifier::get_slot() const
{
  return m_slot;
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

vector<Stat_Modifier> Item::get_stats() const
{
  return vector<Stat_Modifier>{};
}

vector<string> Item::get_usable_by() const
{
  return vector<string>{};
}

bool Item::can_equip(const string & party_member_name) const
{
  return false;
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

Equipment::Equipment(const string & name, const string & type, const string & description, const long & icon, const vector<Stat_Modifier> stats, const vector<string> & usable_by, const long & slot, const string & equipped_by, const long & count)
{
  m_name = name;
  m_type = type;
  m_description = description;
  m_icon = icon;
  m_count = count;
  m_stats = stats;
  m_usable_by = usable_by;
  m_slot = slot;
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

vector<Stat_Modifier> Equipment::get_stats() const
{
  return m_stats;
}

vector<string> Equipment::get_usable_by() const
{
  return m_usable_by;
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

string Equipment::get_equipped_by() const
{
  return m_equipped_by;
}

long Equipment::get_slot() const
{
  return m_slot;
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
  if(m_font != nullptr)
  {
    delete m_font;
    m_font = nullptr;
    --mem;
  }
  if(m_equipped_weapon != nullptr)
  {
    delete m_equipped_weapon;
    m_equipped_weapon = nullptr;
    --mem;
  }
  if(m_equipped_offhand != nullptr)
  {
    delete m_equipped_offhand;
    m_equipped_offhand = nullptr;
    --mem;
  }
  if(m_equipped_helmet != nullptr)
  {
    delete m_equipped_helmet;
    m_equipped_helmet = nullptr;
    --mem;
  }
  if(m_equipped_armor != nullptr)
  {
    delete m_equipped_armor;
    m_equipped_armor = nullptr;
    --mem;
  }
  if(m_equipped_accessory_one != nullptr)
  {
    delete m_equipped_accessory_one;
    m_equipped_accessory_one = nullptr;
    --mem;
  }
  if(m_equipped_accessory_two != nullptr)
  {
    delete m_equipped_accessory_two;
    m_equipped_accessory_two = nullptr;
    --mem;
  }
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

void Party_Member::render_letter(const long & x, const long & y, const char & id) const
{
  m_font->render_letter(x, y, id);
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

void Party_Member::equip(World* world, const string & item_name, const long & slot)
{
  string item_type{world->get_item_type(item_name)};

  if(item_type == "Weapon")
  {
    if(m_equipped_weapon != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Weapon", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 0, m_name}};
    ++mem;
    m_equipped_weapon = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_weapon->get_stats().size()); ++i)
    {
      m_stats.add_modifier(m_equipped_weapon->get_stats()[i]);
    }
  }
  if(item_type == "Shield")
  {
    if(m_equipped_offhand != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Shield", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 0, m_name}};
    ++mem;
    m_equipped_offhand = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_offhand->get_stats().size()); ++i)
    {
      m_stats.add_modifier(m_equipped_offhand->get_stats()[i]);
    }
  }
  if(item_type == "Helm")
  {
    if(m_equipped_helmet != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Helm", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 0, m_name}};
    ++mem;
    m_equipped_helmet = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_helmet->get_stats().size()); ++i)
    {
      m_stats.add_modifier(m_equipped_helmet->get_stats()[i]);
    }
  }
  if(item_type == "Armor")
  {
    if(m_equipped_armor != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Armor", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 0, m_name}};
    ++mem;
    m_equipped_armor = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_armor->get_stats().size()); ++i)
    {
      m_stats.add_modifier(m_equipped_armor->get_stats()[i]);
    }
  }
  if(item_type == "Accessory" && slot == 0)
  {
    if(m_equipped_accessory_one != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Accessory", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 0, m_name}};
    ++mem;
    m_equipped_accessory_one = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_accessory_one->get_stats().size()); ++i)
    {
      m_stats.add_modifier(m_equipped_accessory_one->get_stats()[i]);
    }
  }
  if(item_type == "Accessory" && slot == 1)
  {
    if(m_equipped_accessory_two != nullptr)
    {
      unequip(world, item_type, slot);
    }
    Equipment* equip{new Equipment{item_name, "Accessory", world->get_item_description(item_name), m_icon, world->get_equipment_stat_modifiers(item_name, slot), world->get_equipment_usable_by(item_name), 1, m_name}};
    ++mem;
    m_equipped_accessory_two = equip;
    world->remove_equipment(item_name);
    for(long i{0}; i < static_cast<long>(m_equipped_accessory_two->get_stats().size()); ++i)
    {
      Stat_Modifier modifier{m_equipped_accessory_two->get_stats()[i]};
      modifier.set_slot(slot);
      m_stats.add_modifier(modifier);
    }
  }
}

void Party_Member::unequip(World* world, const string & item_type, const long & slot)
{
  if(item_type == "Weapon")
  {
    if(m_equipped_weapon != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_weapon->get_stats().size()); ++i)
      {
        m_stats.remove_modifier(m_equipped_weapon->get_stats()[i]);
      }
      world->add_equipment(m_equipped_weapon->get_name());
      delete m_equipped_weapon;
      m_equipped_weapon = nullptr;
      --mem;
    }
  }
  if(item_type == "Shield")
  {
    if(m_equipped_offhand != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_offhand->get_stats().size()); ++i)
      {
        m_stats.remove_modifier(m_equipped_offhand->get_stats()[i]);
      }
      world->add_equipment(m_equipped_offhand->get_name());
      delete m_equipped_offhand;
      m_equipped_offhand = nullptr;
      --mem;
    }
  }
  if(item_type == "Helm")
  {
    if(m_equipped_helmet != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_helmet->get_stats().size()); ++i)
      {
        m_stats.remove_modifier(m_equipped_helmet->get_stats()[i]);
      }
      world->add_equipment(m_equipped_helmet->get_name());
      delete m_equipped_helmet;
      m_equipped_helmet = nullptr;
      --mem;
    }
  }
  if(item_type == "Armor")
  {
    if(m_equipped_armor != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_armor->get_stats().size()); ++i)
      {
        m_stats.remove_modifier(m_equipped_armor->get_stats()[i]);
      }
      world->add_equipment(m_equipped_armor->get_name());
      delete m_equipped_armor;
      m_equipped_armor = nullptr;
      --mem;
    }
  }
  if(item_type == "Accessory" && slot == 0)
  {
    if(m_equipped_accessory_one != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_one->get_stats().size()); ++i)
      {
        m_stats.remove_modifier(m_equipped_accessory_one->get_stats()[i]);
      }
      world->add_equipment(m_equipped_accessory_one->get_name());
      delete m_equipped_accessory_one;
      m_equipped_accessory_one = nullptr;
      --mem;
    }
  }
  if(item_type == "Accessory" && slot == 1)
  {
    if(m_equipped_accessory_two != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_two->get_stats().size()); ++i)
      {
        Stat_Modifier modifier{m_equipped_accessory_two->get_stats()[i]};
        modifier.set_slot(slot);
        m_stats.remove_modifier(modifier);
      }
      world->add_equipment(m_equipped_accessory_two->get_name());
      delete m_equipped_accessory_two;
      m_equipped_accessory_two = nullptr;
      --mem;
    }
  }
}

string Party_Member::get_equipped_weapon() const
{
  if(m_equipped_weapon != nullptr)
  {
    return m_equipped_weapon->get_name();
  }
  return "NULL";
}

string Party_Member::get_equipped_shield() const
{
  if(m_equipped_offhand != nullptr)
  {
    return m_equipped_offhand->get_name();
  }
  return "NULL";
}

string Party_Member::get_equipped_helm() const
{
  if(m_equipped_helmet != nullptr)
  {
    return m_equipped_helmet->get_name();
  }
  return "NULL";
}

string Party_Member::get_equipped_armor() const
{
  if(m_equipped_armor != nullptr)
  {
    return m_equipped_armor->get_name();
  }
  return "NULL";
}

string Party_Member::get_equipped_accessory_one() const
{
  if(m_equipped_accessory_one != nullptr)
  {
    return m_equipped_accessory_one->get_name();
  }
  return "NULL";
}

string Party_Member::get_equipped_accessory_two() const
{
  if(m_equipped_accessory_two != nullptr)
  {
    return m_equipped_accessory_two->get_name();
  }
  return "NULL";
}

long Party_Member::get_icon() const
{
  return m_icon;
}

void Party_Member::restore_equipped_weapon(Equipment* equipment)
{
  if(m_equipped_weapon != nullptr)
  {
    delete m_equipped_weapon;
    --mem;
  }
  m_equipped_weapon = equipment;
}

void Party_Member::restore_equipped_shield(Equipment* equipment)
{
  if(m_equipped_offhand != nullptr)
  {
    delete m_equipped_offhand;
    --mem;
  }
  m_equipped_offhand = equipment;
}

void Party_Member::restore_equipped_helm(Equipment* equipment)
{
  if(m_equipped_helmet != nullptr)
  {
    delete m_equipped_helmet;
    --mem;
  }
  m_equipped_helmet = equipment;
}

void Party_Member::restore_equipped_armor(Equipment* equipment)
{
  if(m_equipped_armor != nullptr)
  {
    delete m_equipped_armor;
    --mem;
  }
  m_equipped_armor = equipment;
}

void Party_Member::restore_equipped_accessory_one(Equipment* equipment)
{
  if(m_equipped_accessory_one != nullptr)
  {
    delete m_equipped_accessory_one;
    --mem;
  }
  m_equipped_accessory_one = equipment;
}

void Party_Member::restore_equipped_accessory_two(Equipment* equipment)
{
  if(m_equipped_accessory_two != nullptr)
  {
    delete m_equipped_accessory_two;
    --mem;
  }
  m_equipped_accessory_two = equipment;
}

Player_Stats Party_Member::get_stats() const
{
  return m_stats;
}

void Party_Member::set_stats(const Player_Stats & stats)
{
  m_stats = stats;
}

void Party::update_stats()
{
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    m_members[i]->update_stats();
  }
}

void Party::add_party_member(const Player_Info & player)
{
  m_members.add(new Party_Member(player));
  ++mem;
}

void Party::remove_party_member(const string & name)
{
  m_members.remove(name);
}

string Party::get_member_name(const long & index) const
{
  return m_members[index]->get_name();
}

string Party::get_member_species(const string & name) const
{
  return m_members[name]->get_species();
}

string Party::get_member_class(const string & name) const
{
  return m_members[name]->get_class();
}

long Party::get_member_icon(const string & name) const
{
  return m_members[name]->get_icon();
}

string Party::get_next_member_name(const string & name) const
{
  vector<string> party{m_members.get_list()};
  for(long i{0}; i < static_cast<long>(party.size()); ++i)
  {
    if(party[i] == name)
    {
      if(i + 1 == static_cast<long>(party.size()))
      {
        return m_members[party[0]]->get_name();
      }
      return m_members[party[i + 1]]->get_name();
    }
  }
  crash("Error: Tried to get the party member after " + name + ", which is invalid.");
  return "NULL";
}

string Party::get_previous_member_name(const string & name) const
{
  vector<string> party{m_members.get_list()};
  for(long i{0}; i < static_cast<long>(party.size()); ++i)
  {
    if(party[i] == name)
    {
      if(i - 1 < 0)
      {
        return m_members[party[party.size() - 1]]->get_name();
      }
      return m_members[party[i - 1]]->get_name();
    }
  }
  crash("Error: Tried to get the party member before " + name + ", which is invalid.");
  return "NULL";
}

long Party::get_member_portrait_width(const string & name) const
{
  return m_members[name]->get_portrait_width();
}

long Party::get_member_portrait_height(const string & name) const
{
  return m_members[name]->get_portrait_height();
}

long Party::get_member_small_portrait_width(const string & name) const
{
  return m_members[name]->get_small_portrait_width();
}

long Party::get_member_small_portrait_height(const string & name) const
{
  return m_members[name]->get_small_portrait_height();
}

long Party::get_member_stat(const string & name, const string & stat) const
{
  return m_members[name]->get_stat(stat);
}

long Party::get_member_unmodified_stat(const string & name, const string & stat) const
{
  return m_members[name]->get_unmodified_stat(stat);
}

bool Party::get_member_row(const string & name) const
{
  return m_members[name]->get_row();
}

long Party::get_member_soul_break_level(const string & name) const
{
  return m_members[name]->get_soul_break_level();
}

void Party::render_member_portrait(const string & name, const bool & size, const long & x, const long & y) const
{
  m_members[name]->render_portrait(size, x, y);
}

void Party::render_letter_in_member_font(const string & name, const long & x, const long & y, const char & id) const
{
  m_members[name]->render_letter(x, y, id);
}

long Party::get_size() const
{
  return m_members.get_list_size();
}

bool Party::set_member_front_row(const string & name)
{
  return m_members[name]->set_front_row();
}

bool Party::set_member_back_row(const string & name)
{
  return m_members[name]->set_back_row();
}

void Party::swap_party_members(const string & name1, const string & name2)
{
  m_members.swap(name1, name2);
}

void Party::equip(World* world, const string & item_name, const string & target_party_member_name, const long & target_slot, const string & source_party_member_name, const long & source_slot)
{
  if(source_party_member_name == target_party_member_name && source_slot == target_slot)
  {
    m_members[target_party_member_name]->unequip(world, world->get_item_type(item_name), target_slot);
    return;
  }
  if(source_party_member_name != "NULL")
  {
    m_members[source_party_member_name]->unequip(world, world->get_item_type(item_name), source_slot);
  }
  m_members[target_party_member_name]->equip(world, item_name, target_slot);
}


vector<Equipment*> Party::get_equipped_equipment_including_nulls(World* world) const
{
  vector<Equipment*> equipment{};
  string equip{"NULL"};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    equip = m_members[j]->get_equipped_weapon();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Weapon", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 0), world->get_equipment_usable_by(equip), 0, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }

    equip = m_members[j]->get_equipped_shield();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Shield", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 0), world->get_equipment_usable_by(equip), 0, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }

    equip = m_members[j]->get_equipped_helm();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Helm", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 0), world->get_equipment_usable_by(equip), 0, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }

    equip = m_members[j]->get_equipped_armor();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Armor", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 0), world->get_equipment_usable_by(equip), 0, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }

    equip = m_members[j]->get_equipped_accessory_one();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Accessory", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 0), world->get_equipment_usable_by(equip), 0, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }

    equip = m_members[j]->get_equipped_accessory_two();
    if(equip != "NULL")
    {
      equipment.push_back(new Equipment{equip, "Accessory", world->get_item_description(equip), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(equip, 1), world->get_equipment_usable_by(equip), 1, m_members[j]->get_name()});
      ++mem;
    }
    else
    {
      equipment.push_back(nullptr);
    }
  }
  return equipment;
}

vector<Equipment*> Party::get_equipped_weapons(World* world) const
{
  vector<Equipment*> equipped_weapons{};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    string weapon{m_members[j]->get_equipped_weapon()};
    if(weapon != "NULL")
    {
      equipped_weapons.push_back(new Equipment{weapon, "Weapon", world->get_item_description(weapon), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(weapon, 0), world->get_equipment_usable_by(weapon), 0, m_members[j]->get_name()});
      ++mem;
    }
  }
  return equipped_weapons;
}

vector<Equipment*> Party::get_equipped_shields(World* world) const
{
  vector<Equipment*> equipped_weapons{};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    string shield{m_members[j]->get_equipped_shield()};
    if(shield != "NULL")
    {
      equipped_weapons.push_back(new Equipment{shield, "Shield", world->get_item_description(shield), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(shield, 0), world->get_equipment_usable_by(shield), 0, m_members[j]->get_name()});
      ++mem;
    }
  }
  return equipped_weapons;
}

vector<Equipment*> Party::get_equipped_helms(World* world) const
{
  vector<Equipment*> equipped_weapons{};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    string helm{m_members[j]->get_equipped_helm()};
    if(helm != "NULL")
    {
      equipped_weapons.push_back(new Equipment{helm, "Helm", world->get_item_description(helm), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(helm, 0), world->get_equipment_usable_by(helm), 0, m_members[j]->get_name()});
      ++mem;
    }
  }
  return equipped_weapons;
}

vector<Equipment*> Party::get_equipped_armor(World* world) const
{
  vector<Equipment*> equipped_weapons{};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    string armor{m_members[j]->get_equipped_armor()};
    if(armor != "NULL")
    {
      equipped_weapons.push_back(new Equipment{armor, "Armor", world->get_item_description(armor), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(armor, 0), world->get_equipment_usable_by(armor), 0, m_members[j]->get_name()});
      ++mem;
    }
  }
  return equipped_weapons;
}

vector<Equipment*> Party::get_equipped_accessories(World* world) const
{
  vector<Equipment*> equipped_weapons{};
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    string accessory_one{m_members[j]->get_equipped_accessory_one()};
    string accessory_two{m_members[j]->get_equipped_accessory_two()};
    if(accessory_one != "NULL")
    {
      equipped_weapons.push_back(new Equipment{accessory_one, "Accessory", world->get_item_description(accessory_one), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(accessory_one, 0), world->get_equipment_usable_by(accessory_one), 0, m_members[j]->get_name()});
      ++mem;
    }
    if(accessory_two != "NULL")
    {
      equipped_weapons.push_back(new Equipment{accessory_two, "Accessory", world->get_item_description(accessory_two), m_members[j]->get_icon(), world->get_equipment_stat_modifiers(accessory_two, 1), world->get_equipment_usable_by(accessory_two), 1, m_members[j]->get_name()});
      ++mem;
    }
  }
  return equipped_weapons;
}

bool Party::has_equipped_weapons() const
{
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    if(m_members[j]->get_equipped_weapon() != "NULL")
    {
      return true;
    }
  }
  return false;
}

bool Party::has_equipped_shields() const
{
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    if(m_members[j]->get_equipped_shield() != "NULL")
    {
      return true;
    }
  }
  return false;
}

bool Party::has_equipped_helms() const
{
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    if(m_members[j]->get_equipped_helm() != "NULL")
    {
      return true;
    }
  }
  return false;
}

bool Party::has_equipped_armor() const
{
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    if(m_members[j]->get_equipped_armor() != "NULL")
    {
      return true;
    }
  }
  return false;
}

bool Party::has_equipped_accessories() const
{
  for(long j{0}; j < m_members.get_list_size(); ++j)
  {
    if(m_members[j]->get_equipped_accessory_one() != "NULL")
    {
      return true;
    }
    if(m_members[j]->get_equipped_accessory_two() != "NULL")
    {
      return true;
    }
  }
  return false;
}

string Party::get_member_equipped_equipment(const string & party_member_name, const string & type) const
{
  if(type == "Weapon")
  {
    return m_members[party_member_name]->get_equipped_weapon();
  }
  else if(type == "Shield")
  {
    return m_members[party_member_name]->get_equipped_shield();
  }
  else if(type == "Helm")
  {
    return m_members[party_member_name]->get_equipped_helm();
  }
  else if(type == "Armor")
  {
    return m_members[party_member_name]->get_equipped_armor();
  }
  else if(type == "Accessory 1")
  {
    return m_members[party_member_name]->get_equipped_accessory_one();
  }
  else if(type == "Accessory 2")
  {
    return m_members[party_member_name]->get_equipped_accessory_two();
  }
  crash("Error: \"" + type + "\" is not an equipment type.");
  return "NULL";
}

void Party::back_up_party_stats()
{
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    m_stats_back_up.push_back(m_members[i]->get_stats());
  }
}

void Party::restore_party_stats()
{
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    m_members[i]->set_stats(m_stats_back_up[i]);
  }
  m_stats_back_up.clear();
}

void Party::restore_equipment(vector<Equipment*> equipment)
{
  long i{0};
  long j{0};
  while(i != static_cast<long>(equipment.size()))
  {
    m_members[j]->restore_equipped_weapon(equipment[i]);
    ++i;
    m_members[j]->restore_equipped_shield(equipment[i]);
    ++i;
    m_members[j]->restore_equipped_helm(equipment[i]);
    ++i;
    m_members[j]->restore_equipped_armor(equipment[i]);
    ++i;
    m_members[j]->restore_equipped_accessory_one(equipment[i]);
    ++i;
    m_members[j]->restore_equipped_accessory_two(equipment[i]);
    ++i;
    ++j;
  }
}

World::World()
{
  #include "Consts/Item_Consts.h"

  m_cursor = new Cursor;
  ++mem;
  m_fonts.add(vector<Fnt*>
  {
    new Fnt,
    new Fnt{HEADING_FONT},
    new Fnt{CHARACTER_TITLE_FONT},
    new Fnt{RED_FONT},
    new Fnt{GREEN_FONT}
  });
  ++mem;
  ++mem;
  ++mem;
  ++mem;
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
  add_item("Heal Potion");
  add_item("Heal Potion");
  add_item("Money Bag");
  add_item("Money Bag");

  Music music{LoadMusicStreamFromMemory(".mp3", CITY_MUSIC.m_data, CITY_MUSIC.m_size)};
  m_global_music.push_back(music);

  m_global_music_names.push_back(CITY_MUSIC.m_name);
  
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
  for(long i{0}; i < static_cast<long>(m_global_sounds.size()); ++i)
  {
    UnloadSound(m_global_sounds[i]);
  }
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    UnloadMusicStream(m_global_music[i]);
  }
}

void World::update()
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      if(IsMusicStreamPlaying(m_global_music[i]) == true)
      {
        UpdateMusicStream(m_global_music[i]);
      }
    }
  }
  m_party.update_stats();
  m_cursor->finish();
  m_cursor->update();
}

bool World::can_use_equipment(const string & party_member_name, const string & item_name, const string & type) const
{
  if((m_item_database[item_name]->get_name() == item_name && type == "NULL") || m_item_database[item_name]->get_type() == type)
  {
    if(m_item_database[item_name]->can_equip(party_member_name) == true)
    {
      return true;
    }
  }
  return false;
}

void World::equip(World* world, const string & item_name, const string & target_party_member_name, const long & target_slot, const string & source_party_member_name, const long & source_slot)
{
  m_party.equip(world, item_name, target_party_member_name, target_slot, source_party_member_name, source_slot);
}

void World::render_item(const long & x, const long & y, const string & font_name, const string & item_name, const long & width) const
{
  long current_pos{x};
  DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_items[item_name]->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_name]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  current_pos += ICON_WIDTH;

  string text{item_name};
  while(text != "")
  {
    m_fonts[font_name]->render_letter(current_pos, y, text[0]);
    current_pos += m_fonts[font_name]->get_char_width(text[0]);
    text.erase(text.begin());
  }

  current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
  text = "x" + to_string(m_items[item_name]->get_count());
  while(text != "")
  {
    m_fonts[font_name]->render_letter(current_pos, y, text[0]);
    current_pos += m_fonts[font_name]->get_char_width(text[0]);
    text.erase(text.begin());
  }
}

void World::render_key_item(const long & x, const long & y, const string & font_name, const string & item_name) const
{
  long current_pos{x};
  DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_key_items[item_name]->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_name]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  current_pos += ICON_WIDTH;

  string text{item_name};
  while(text != "")
  {
    m_fonts[font_name]->render_letter(current_pos, y, text[0]);
    current_pos += m_fonts[font_name]->get_char_width(text[0]);
    text.erase(text.begin());
  }
}

void World::render_equipment(const long & x, const long & y, const string & font_name, const string & item_name, const long & width, const bool & show_quantity, const string & equipped_by) const
{
  long current_pos{x};
  if(equipped_by == "NULL")
  {
    DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_item_database[item_name]->get_icon()), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (m_fonts[font_name]->get_height() - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
    current_pos += ICON_WIDTH;

    string text{item_name};
    while(text != "")
    {
      m_fonts[font_name]->render_letter(current_pos, y, text[0]);
      current_pos += m_fonts[font_name]->get_char_width(text[0]);
      text.erase(text.begin());
    }
    if(show_quantity == true)
    {
      current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
      text = "x" + to_string(m_equipment[item_name]->get_count());
      while(text != "")
      {
        m_fonts[font_name]->render_letter(current_pos, y, text[0]);
        current_pos += m_fonts[font_name]->get_char_width(text[0]);
        text.erase(text.begin());
      }
    }
  }
  else
  {
    DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * m_party.get_member_icon(equipped_by)), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (FONT_TEXT_HEIGHT - m_item_icons_tex.height) / 2.0), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
    current_pos += ICON_WIDTH;

    string text{item_name};
    while(text != "")
    {
      font_name == "Red" ? m_fonts[font_name]->render_letter(current_pos, y, text[0]) : m_party.render_letter_in_member_font(equipped_by, current_pos, y, text[0]);
      current_pos += m_fonts[font_name]->get_char_width(text[0]);
      text.erase(text.begin());
    }
    current_pos = x + width * ITEM_QUANTITY_LOCATION_FRACTION;
    text = "E";
    while(text != "")
    {
      font_name == "Red" ? m_fonts[font_name]->render_letter(current_pos, y, text[0]) : m_party.render_letter_in_member_font(equipped_by, current_pos, y, text[0]);
      current_pos += m_fonts[font_name]->get_char_width(text[0]);
      text.erase(text.begin());
    }
  }
}

void World::render_stat(const long & x, const long & y, const string & font_name, const string & stat_name, const long & width, const string & party_member_name, const vector<long> & equipment_stat_differences) const
{
  long vec_index{0};
  if(equipment_stat_differences.empty() == true)
  {
    vec_index = -1;
  }
  else if(stat_name == "Strength")
  {
    vec_index = 0;
  }
  else if(stat_name == "Attack")
  {
    vec_index = 1;
  }
  else if(stat_name == "Speed")
  {
    vec_index = 2;
  }
  else if(stat_name == "Defense")
  {
    vec_index = 3;
  }
  else if(stat_name == "Intellect")
  {
    vec_index = 4;
  }
  else if(stat_name == "Resistance")
  {
    vec_index = 5;
  }
  else if(stat_name == "Stamina")
  {
    vec_index = 6;
  }
  else if(stat_name == "Accuracy")
  {
    vec_index = 7;
  }
  else if(stat_name == "Spirit")
  {
    vec_index = 8;
  }
  else if(stat_name == "Critical")
  {
    vec_index = 9;
  }
  else if(stat_name == "Evasion")
  {
    vec_index = 10;
  }
  else if(stat_name == "Magic Evasion")
  {
    vec_index = 11;
  }

  long current_pos{static_cast<long>(x + width * STAT_LOCATION_FRACTION)};
  string text;
  text = to_string(m_party.get_member_stat(party_member_name, stat_name)) + " (" + to_string(m_party.get_member_unmodified_stat(party_member_name, stat_name)) + ")" + (vec_index != -1 ? (" " + (equipment_stat_differences[vec_index] > 0 ? ("+" + to_string(equipment_stat_differences[vec_index])) : (equipment_stat_differences[vec_index] != 0 ? to_string(equipment_stat_differences[vec_index]) : ""))) : "");
  while(text != "")
  {
    m_fonts[vec_index != -1 ? (equipment_stat_differences[vec_index] > 0 ? "Green" : (equipment_stat_differences[vec_index] == 0 ? "Text" : "Red")) : "Text"]->render_letter(current_pos, y, text[0]);
    current_pos += m_fonts[font_name]->get_char_width(text[0]);
    text.erase(text.begin());
  }
}

void World::render_cursor() const
{
  m_cursor->render();
}

void World::render_text_center(const string & font_name, const string & text, const long & y_pos, const long & alpha) const
{
  m_fonts[font_name]->render_text_center(text, y_pos, alpha);
}

void World::render_text(const string & font_name, const string & text, const long & x_pos, const long & y_pos, const long & alpha) const
{
  m_fonts[font_name]->render_text(text, x_pos, y_pos, alpha);
}

void World::render_letter(const string & font_name, const long & x, const long & y, const char & id, const long & alpha) const
{
  m_fonts[font_name]->render_letter(x, y, id, alpha);
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

void World::render_continue_arrow(const long & x, const long & y, const bool & flip_y) const
{
  DrawTexturePro(m_continue_arrow_texture, Rectangle{0, 0, static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Rectangle{static_cast<float>(x - m_continue_arrow_texture.width / 2), static_cast<float>(y), static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Vector2{static_cast<float>(m_continue_arrow_texture.width / 2), 0}, 180 * flip_y, Color{0xFF, 0xFF, 0xFF, 0xFF});
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
  return m_items.get_list();;
}

vector<string> World::get_key_items() const
{
  return m_key_items.get_list();
}
/*
vector<string> World::get_equipment() const
{
  return vector<string>{get_weapons() + get_shields() + get_helms() + get_armor() + get_accessories()};
}
*/
vector<Equipment*> World::get_weapons(World* world) const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_weapons(world)};
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Weapon")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  for(long j{0}; j < static_cast<long>(inventory_equipment.size()); ++j)
  {
    equipped_weapons.push_back(new Equipment{inventory_equipment[j], m_equipment[inventory_equipment[j]]->get_type(), m_equipment[inventory_equipment[j]]->get_description(), m_equipment[inventory_equipment[j]]->get_icon(), m_equipment[inventory_equipment[j]]->get_stats(), m_equipment[inventory_equipment[j]]->get_usable_by(), m_equipment[inventory_equipment[j]]->get_slot(), m_equipment[inventory_equipment[j]]->get_equipped_by()});
    ++mem;
  }
  return equipped_weapons;
}

vector<Equipment*> World::get_shields(World* world) const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_shields(world)};
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Shield")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  for(long j{0}; j < static_cast<long>(inventory_equipment.size()); ++j)
  {
    equipped_weapons.push_back(new Equipment{inventory_equipment[j], m_equipment[inventory_equipment[j]]->get_type(), m_equipment[inventory_equipment[j]]->get_description(), m_equipment[inventory_equipment[j]]->get_icon(), m_equipment[inventory_equipment[j]]->get_stats(), m_equipment[inventory_equipment[j]]->get_usable_by(), m_equipment[inventory_equipment[j]]->get_slot(), m_equipment[inventory_equipment[j]]->get_equipped_by()});
    ++mem;
  }
  return equipped_weapons;
}

vector<Equipment*> World::get_helms(World* world) const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_helms(world)};
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Helm")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  for(long j{0}; j < static_cast<long>(inventory_equipment.size()); ++j)
  {
    equipped_weapons.push_back(new Equipment{inventory_equipment[j], m_equipment[inventory_equipment[j]]->get_type(), m_equipment[inventory_equipment[j]]->get_description(), m_equipment[inventory_equipment[j]]->get_icon(), m_equipment[inventory_equipment[j]]->get_stats(), m_equipment[inventory_equipment[j]]->get_usable_by(), m_equipment[inventory_equipment[j]]->get_slot(), m_equipment[inventory_equipment[j]]->get_equipped_by()});
    ++mem;
  }
  return equipped_weapons;
}

vector<Equipment*> World::get_armor(World* world) const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_armor(world)};
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Armor")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  for(long j{0}; j < static_cast<long>(inventory_equipment.size()); ++j)
  {
    equipped_weapons.push_back(new Equipment{inventory_equipment[j], m_equipment[inventory_equipment[j]]->get_type(), m_equipment[inventory_equipment[j]]->get_description(), m_equipment[inventory_equipment[j]]->get_icon(), m_equipment[inventory_equipment[j]]->get_stats(), m_equipment[inventory_equipment[j]]->get_usable_by(), m_equipment[inventory_equipment[j]]->get_slot(), m_equipment[inventory_equipment[j]]->get_equipped_by()});
    ++mem;
  }
  return equipped_weapons;
}

vector<Equipment*> World::get_accessories(World* world) const
{
  vector<Equipment*> equipped_weapons{m_party.get_equipped_accessories(world)};
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Accessory")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  for(long j{0}; j < static_cast<long>(inventory_equipment.size()); ++j)
  {
    equipped_weapons.push_back(new Equipment{inventory_equipment[j], m_equipment[inventory_equipment[j]]->get_type(), m_equipment[inventory_equipment[j]]->get_description(), m_equipment[inventory_equipment[j]]->get_icon(), m_equipment[inventory_equipment[j]]->get_stats(), m_equipment[inventory_equipment[j]]->get_usable_by(), m_equipment[inventory_equipment[j]]->get_slot(), m_equipment[inventory_equipment[j]]->get_equipped_by()});
    ++mem;
  }
  return equipped_weapons;
}

string World::get_item_type(const string & item_name) const
{
  return m_item_database[item_name]->get_type();
}

string World::get_item_description(const string & item_name) const
{
  return m_item_database[item_name]->get_description();
}

vector<Stat_Modifier> World::get_equipment_stat_modifiers(const string & item_name, const long & slot) const
{
  vector<Stat_Modifier> stats{m_item_database[item_name]->get_stats()};
  for(long i{0}; i < static_cast<long>(stats.size()); ++i)
  {
    stats[i].set_slot(slot);
  }
  return stats;
}

long World::get_equipment_add_modifier(const string & item_name, const string & stat_name) const
{
  vector<Stat_Modifier> stats{m_item_database[item_name]->get_stats()};
  for(long i{0}; i < static_cast<long>(stats.size()); ++i)
  {
    if(stats[i].get_stat() == stat_name)
    {
      return stats[i].get_add_modifier();
    }
  }
  return 0;
}

long World::get_equipment_replace_modifier(const string & item_name, const string & stat_name) const
{
  vector<Stat_Modifier> stats{m_item_database[item_name]->get_stats()};
  for(long i{0}; i < static_cast<long>(stats.size()); ++i)
  {
    if(stats[i].get_stat() == stat_name)
    {
      return stats[i].get_replace_modifier();
    }
  }
  return 0;
}

double World::get_equipment_multiply_modifier(const string & item_name, const string & stat_name) const
{
  vector<Stat_Modifier> stats{m_item_database[item_name]->get_stats()};
  for(long i{0}; i < static_cast<long>(stats.size()); ++i)
  {
    if(stats[i].get_stat() == stat_name)
    {
      return stats[i].get_multiply_modifier();
    }
  }
  return 1;
}

vector<string> World::get_equipment_usable_by(const string & item_name) const
{
  return m_item_database[item_name]->get_usable_by();
}

bool World::has_items() const
{
  return m_items.get_list_size() != 0;
}

bool World::has_item(const string & item) const
{
  return m_items.is_in_list(item);
}

void World::add_item(const string & item)
{
  //Does it already exist?
  if(m_items.is_in_list(item) == true)
  {
    m_items[item]->increment_count();
  }
  else
  {
    //No it doesn't, add it to the list
    Consumable_Item* new_item{new Consumable_Item{m_item_database[item]->get_name(), m_item_database[item]->get_description()}};
    m_items.add(new_item);
    ++mem;
  }
}

void World::remove_item(const string & item)
{
  //Does it already exist?
  if(m_items.is_in_list(item) == true)
  {
    m_items[item]->decrement_count();
    // if you don't have any more, remove it
    if(m_items[item]->get_count() == 0)
    {
      m_items.remove(item);
    }
  }
}

bool World::has_key_items() const
{
  return m_key_items.get_list_size() != 0;
}

bool World::has_key_item(const string & item) const
{
  return m_key_items.is_in_list(item);
}

void World::add_key_item(const string & item)
{
  //Does it already exist?
  if(m_key_items.is_in_list(item) == false)
  {
    //No it doesn't, add it to the list
    Key_Item* new_item{new Key_Item{m_item_database[item]->get_name(), m_item_database[item]->get_description()}};
    m_key_items.add(new_item);
    ++mem;
  }
}

void World::remove_key_item(const string & item)
{
  //Does it already exist?
  if(m_key_items.is_in_list(item) == true)
  {
    //Remove it
    m_key_items.remove(item);
  }
}

bool World::has_weapons() const
{
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Weapon")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  if(m_party.has_equipped_weapons() == true || inventory_equipment.empty() == false)
  {
    return true;
  }
  return false;
}

bool World::has_shields() const
{
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Shield")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  if(m_party.has_equipped_shields() == true || inventory_equipment.empty() == false)
  {
    return true;
  }
  return false;
}

bool World::has_helms() const
{
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Helm")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  if(m_party.has_equipped_helms() == true || inventory_equipment.empty() == false)
  {
    return true;
  }
  return false;
}

bool World::has_armor() const
{
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Armor")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  if(m_party.has_equipped_armor() == true || inventory_equipment.empty() == false)
  {
    return true;
  }
  return false;
}

bool World::has_accessories() const
{
  vector<string> inventory_equipment{m_equipment.get_list()};
  long i{0};
  while(i != static_cast<long>(inventory_equipment.size()))
  {
    if(m_equipment[inventory_equipment[i]]->get_type() != "Accessory")
    {
      inventory_equipment.erase(inventory_equipment.begin() + i);
      i = -1;
    }
    ++i;
  }
  if(m_party.has_equipped_accessories() == true || inventory_equipment.empty() == false)
  {
    return true;
  }
  return false;
}
/*
bool World::has_equipment(const string & item) const
{
    return m_items.get_list_size() != 0;
}
*/
void World::add_equipment(const string & item)
{
  //Does it already exist?
  if(m_equipment.is_in_list(item) == true)
  {
    m_equipment[item]->increment_count();
  }
  else
  {
    //No it doesn't, add it to the list
    Equipment* new_item{new Equipment{m_item_database[item]->get_name(), m_item_database[item]->get_type(), m_item_database[item]->get_description(), m_item_database[item]->get_icon(), m_item_database[item]->get_stats(), m_item_database[item]->get_usable_by()}};
    m_equipment.add(new_item);
    ++mem;
  }
}

void World::remove_equipment(const string & item)
{
  //Does it already exist?
  if(m_equipment.is_in_list(item) == true)
  {
    m_equipment[item]->decrement_count();
    // if you don't have any more, remove it
    if(m_equipment[item]->get_count() == 0)
    {
      m_equipment.remove(item);
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

long World::get_font_height(const string & font_name) const
{
  return m_fonts[font_name]->get_height();
}

long World::get_word_width(const string & font_name, const string & text) const
{
  return m_fonts[font_name]->get_word_width(text);
}

long World::get_char_width(const string & font_name, const char & text) const
{
  return m_fonts[font_name]->get_char_width(text);
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

void World::play_global_music(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      StopMusicStream(m_global_music[i]);
      m_music_playing = "NULL";
    }
  }
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == name)
    {
      PlayMusicStream(m_global_music[i]);
      m_music_playing = name;
      return;
    }
  }
  crash("Error: Global music \"" + name + "\" doesn't exist.");
}

void World::pause_play_global_music() const
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      if(IsMusicStreamPlaying(m_global_music[i]) == true)
      {
        PauseMusicStream(m_global_music[i]);
      }
      else
      {
        PlayMusicStream(m_global_music[i]);
      }
      return;
    }
  }
  crash("Error: Global music \"" + m_music_playing + "\" doesn't exist.");
}

void World::stop_global_music()
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      StopMusicStream(m_global_music[i]);
      m_music_playing = "NULL";
      return;
    }
  }
  crash("Error: Global music \"" + m_music_playing + "\" doesn't exist.");
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

string World::get_party_member_equipped_equipment(const string & party_member_name, const string & type, const long & slot) const
{
  if(type == "Accessory")
  {
    if(slot == 0)
    {
      return m_party.get_member_equipped_equipment(party_member_name, "Accessory 1");
    }
    else if(slot == 1)
    {
      return m_party.get_member_equipped_equipment(party_member_name, "Accessory 2");
    }
  }
  return m_party.get_member_equipped_equipment(party_member_name, type);
}

vector<long> World::build_equipment_stat_differences(World* world, const string & item_name, const string & target_party_member_name, const long & target_slot, const string & source_party_member_name, const long & source_slot)
{
  vector<long> current_stats{}; // target party member's current stats
  vector<long> new_stats{}; // target party member's new stats
  vector<long> stat_differences{}; // target party member's stat differences between old equipment and highlighted equipment
  vector<Equipment*> equipment_copy{};
  vector<Equipment*> party_equipment_copy{m_party.get_equipped_equipment_including_nulls(world)};
  m_party.back_up_party_stats();

  current_stats.push_back(get_party_member_stat(target_party_member_name, "Strength"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Attack"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Speed"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Defense"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Intellect"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Resistance"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Stamina"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Accuracy"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Spirit"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Critical"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Evasion"));
  current_stats.push_back(get_party_member_stat(target_party_member_name, "Magic Evasion"));

  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    equipment_copy.push_back(new Equipment{m_equipment[i]->get_name(), m_equipment[i]->get_type(), m_equipment[i]->get_description(), m_equipment[i]->get_icon(), m_equipment[i]->get_stats(), m_equipment[i]->get_usable_by(), m_equipment[i]->get_slot(), m_equipment[i]->get_equipped_by(), m_equipment[i]->get_count()});
    ++mem;
  }

  equip(world, item_name, target_party_member_name, target_slot, source_party_member_name, source_slot);

  new_stats.push_back(get_party_member_stat(target_party_member_name, "Strength"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Attack"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Speed"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Defense"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Intellect"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Resistance"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Stamina"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Accuracy"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Spirit"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Critical"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Evasion"));
  new_stats.push_back(get_party_member_stat(target_party_member_name, "Magic Evasion"));

  m_equipment.add(equipment_copy);
  m_party.restore_equipment(party_equipment_copy);
  m_party.restore_party_stats();

  for(long i{0}; i < static_cast<long>(new_stats.size()); ++i)
  {
    stat_differences.push_back(new_stats[i] - current_stats[i]);
  }

  return stat_differences;
}
