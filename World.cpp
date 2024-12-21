#include "Main.h"
#include "World.h"

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

void Stats::add_modifier(Stat_Modifier & modifier, const long & slot)
{
  modifier.set_slot(slot);
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

void Stats::remove_modifier(Stat_Modifier & modifier, const long & slot)
{
  modifier.set_slot(slot);
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

bool Item::is_usable_by(const string & character_name) const
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

Key_Item::Key_Item(const string & name, const string & description)
{
  m_name = name;
  m_type = "Key Item";
  m_description = description;
  m_icon = KEY_ITEM_ICON;
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

string Equipment::get_description_create() const
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

bool Equipment::is_usable_by(const string & character_name) const
{
  if(m_usable_by.empty() == true)
  {
    return true;
  }
  for(long i{0}; i < static_cast<long>(m_usable_by.size()); ++i)
  {
    if(m_usable_by[i] == character_name)
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
}

Party_Member::~Party_Member()
{
  UnloadTexture(m_portrait);
  UnloadTexture(m_small_portrait);
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

void Party_Member::equip(Equipment* equip, const long & slot)
{
  if(equip->get_type() == "Weapon")
  {
    m_equipped_weapon = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i]);
    }
  }

  if(equip->get_type() == "Shield")
  {
    m_equipped_offhand = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i]);
    }
  }

  if(equip->get_type() == "Helm")
  {
    m_equipped_helmet = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i]);
    }
  }

  if(equip->get_type() == "Armor")
  {
    m_equipped_armor = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i]);
    }
  }

  if(slot == 0 && equip->get_type() == "Accessory")
  {
    m_equipped_accessory_one = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i]);
    }
  }

  if(slot == 1 && equip->get_type() == "Accessory")
  {
    m_equipped_accessory_two = equip;
    for(long i{0}; i < static_cast<long>(equip->get_stats().size()); ++i)
    {
      m_stats.add_modifier(equip->get_stats()[i], slot);
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
        m_stats.remove_modifier(m_equipped_accessory_two->get_stats()[i], slot);
      }
      world->add_equipment(m_equipped_accessory_two->get_name());
      delete m_equipped_accessory_two;
      m_equipped_accessory_two = nullptr;
      --mem;
    }
  }
}

Equipment* Party_Member::get_equipped_weapon() const
{
  if(m_equipped_weapon != nullptr)
  {
    return m_equipped_weapon;
  }
  return nullptr;
}

Equipment* Party_Member::get_equipped_shield() const
{
  if(m_equipped_offhand != nullptr)
  {
    return m_equipped_offhand;
  }
  return nullptr;
}

Equipment* Party_Member::get_equipped_helm() const
{
  if(m_equipped_helmet != nullptr)
  {
    return m_equipped_helmet;
  }
  return nullptr;
}

Equipment* Party_Member::get_equipped_armor() const
{
  if(m_equipped_armor != nullptr)
  {
    return m_equipped_armor;
  }
  return nullptr;
}

Equipment* Party_Member::get_equipped_accessory_one() const
{
  if(m_equipped_accessory_one != nullptr)
  {
    return m_equipped_accessory_one;
  }
  return nullptr;
}

Equipment* Party_Member::get_equipped_accessory_two() const
{
  if(m_equipped_accessory_two != nullptr)
  {
    return m_equipped_accessory_two;
  }
  return nullptr;
}

vector<long> Party_Member::predict_stats(const World* const world, const string & item_name, const string & item_type, const bool & same_item, const long & slot, const long & highlighted_slot, const string & highlighted_equipped_by) const
{
  Player_Stats predict{m_stats};

  if(item_type == "Weapon")
  {
    if(m_equipped_weapon != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_weapon->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_weapon->get_stats()[i]);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i]);
      }
    }
  }
  if(item_type == "Shield")
  {
    if(m_equipped_offhand != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_offhand->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_offhand->get_stats()[i]);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i]);
      }
    }
  }
  if(item_type == "Helm")
  {
    if(m_equipped_helmet != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_helmet->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_helmet->get_stats()[i]);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i]);
      }
    }
  }
  if(item_type == "Armor")
  {
    if(m_equipped_armor != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_armor->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_armor->get_stats()[i]);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i]);
      }
    }
  }
  if(item_type == "Accessory" && slot == 0)
  {
    if(m_equipped_accessory_one != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_one->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_accessory_one->get_stats()[i], slot);
      }
    }
    if(highlighted_slot == 1 && highlighted_equipped_by == m_name)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_two->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_accessory_two->get_stats()[i], highlighted_slot);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i], slot);
      }
    }
  }
  if(item_type == "Accessory" && slot == 1)
  {
    if(m_equipped_accessory_two != nullptr)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_two->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_accessory_two->get_stats()[i], slot);
      }
    }
    if(highlighted_slot == 0 && highlighted_equipped_by == m_name)
    {
      for(long i{0}; i < static_cast<long>(m_equipped_accessory_one->get_stats().size()); ++i)
      {
        predict.remove_modifier(m_equipped_accessory_one->get_stats()[i], highlighted_slot);
      }
    }
    if(same_item == false)
    {
      for(long i{0}; i < static_cast<long>(world->get_equipment_stat_modifiers(item_name).size()); ++i)
      {
        predict.add_modifier(world->get_equipment_stat_modifiers(item_name)[i], slot);
      }
    }
  }

  return vector<long>{predict.get_stat("Strength") - m_stats.get_stat("Strength"), predict.get_stat("Attack") - m_stats.get_stat("Attack"), predict.get_stat("Speed") - m_stats.get_stat("Speed"), predict.get_stat("Defense") - m_stats.get_stat("Defense"), predict.get_stat("Intellect") - m_stats.get_stat("Intellect"), predict.get_stat("Resistance") - m_stats.get_stat("Resistance"), predict.get_stat("Stamina") - m_stats.get_stat("Stamina"), predict.get_stat("Accuracy") - m_stats.get_stat("Accuracy"), predict.get_stat("Spirit") - m_stats.get_stat("Spirit"), predict.get_stat("Critical") - m_stats.get_stat("Critical"), predict.get_stat("Evasion") - m_stats.get_stat("Evasion"), predict.get_stat("Magic Evasion") - m_stats.get_stat("Magic Evasion"), predict.get_stat("Max HP") - m_stats.get_stat("Max HP"), predict.get_stat("Max MP") - m_stats.get_stat("Max MP")};
}

void Party::update_stats()
{
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    m_members[i]->update_stats();
  }
}

long Party::count_equipped_weapons() const
{
  long count{0};
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      ++count;
    }
  }
  return count;
}

long Party::count_equipped_shields() const
{
  long count{0};
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      ++count;
    }
  }
  return count;
}

long Party::count_equipped_helms() const
{
  long count{0};
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      ++count;
    }
  }
  return count;
}

long Party::count_equipped_armor() const
{
  long count{0};
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      ++count;
    }
  }
  return count;
}

long Party::count_equipped_accessories() const
{
  long count{0};
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      ++count;
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      ++count;
    }
  }
  return count;
}

string Party::get_next_member(const string & name) const
{
  vector<Party_Member*> party{m_members.get_list()};
  for(long i{0}; i < static_cast<long>(party.size()); ++i)
  {
    if(party[i]->get_name() == name)
    {
      if(i + 1 == static_cast<long>(party.size()))
      {
        return party[0]->get_name();;
      }
      return party[i + 1]->get_name();
    }
  }
  crash("Error: Tried to get the party member after " + name + ", which is invalid.");
  return nullptr;
}

string Party::get_previous_member(const string & name) const
{
  vector<Party_Member*> party{m_members.get_list()};
  for(long i{0}; i < static_cast<long>(party.size()); ++i)
  {
    if(party[i]->get_name() == name)
    {
      if(i - 1 < 0)
      {
        return party[party.size() - 1]->get_name();
      }
      return party[i - 1]->get_name();
    }
  }
  crash("Error: Tried to get the party member before " + name + ", which is invalid.");
  return nullptr;
}

vector<string> Party::get_equipped_weapon_names() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_weapon()->get_name());
    }
  }
  return count;
}

vector<string> Party::get_equipped_shield_names() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_shield()->get_name());
    }
  }
  return count;
}

vector<string> Party::get_equipped_helm_names() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_helm()->get_name());
    }
  }
  return count;
}

vector<string> Party::get_equipped_armor_names() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_armor()->get_name());
    }
  }
  return count;
}

vector<string> Party::get_equipped_accessory_names() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_one()->get_name());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_two()->get_name());
    }
  }
  return count;
}

vector<string> Party::get_equipped_weapon_descriptions() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_weapon()->get_description());
    }
  }
  return count;
}

vector<string> Party::get_equipped_shield_descriptions() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_shield()->get_description());
    }
  }
  return count;
}

vector<string> Party::get_equipped_helm_descriptions() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_helm()->get_description());
    }
  }
  return count;
}

vector<string> Party::get_equipped_armor_descriptions() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_armor()->get_description());
    }
  }
  return count;
}

vector<string> Party::get_equipped_accessory_descriptions() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_one()->get_description());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_two()->get_description());
    }
  }
  return count;
}

vector<string> Party::get_equipped_weapon_equipped_bys() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_weapon()->get_equipped_by());
    }
  }
  return count;
}

vector<string> Party::get_equipped_shield_equipped_bys() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_shield()->get_equipped_by());
    }
  }
  return count;
}

vector<string> Party::get_equipped_helm_equipped_bys() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_helm()->get_equipped_by());
    }
  }
  return count;
}

vector<string> Party::get_equipped_armor_equipped_bys() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_armor()->get_equipped_by());
    }
  }
  return count;
}

vector<string> Party::get_equipped_accessory_equipped_bys() const
{
  vector<string> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_one()->get_equipped_by());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_two()->get_equipped_by());
    }
  }
  return count;
}

vector<long> Party::get_equipped_weapon_icons() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_weapon() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_weapon()->get_icon());
    }
  }
  return count;
}

vector<long> Party::get_equipped_shield_icons() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_shield() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_shield()->get_icon());
    }
  }
  return count;
}

vector<long> Party::get_equipped_helm_icons() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_helm() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_helm()->get_icon());
    }
  }
  return count;
}

vector<long> Party::get_equipped_armor_icons() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_armor() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_armor()->get_icon());
    }
  }
  return count;
}

vector<long> Party::get_equipped_accessory_icons() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_one()->get_icon());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_two()->get_icon());
    }
  }
  return count;
}

vector<long> Party::get_equipped_accessory_slots() const
{
  vector<long> count;
  for(long i{0}; i < m_members.get_list_size(); ++i)
  {
    if(m_members[i]->get_equipped_accessory_one() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_one()->get_slot());
    }
    if(m_members[i]->get_equipped_accessory_two() != nullptr)
    {
      count.push_back(m_members[i]->get_equipped_accessory_two()->get_slot());
    }
  }
  return count;
}

void Party::equip(World* world, const string & character, const string & item_name, const string & item_type, const long & slot, const string & highlighted_equipped_by, const long & highlighted_slot)
{
  if(character == highlighted_equipped_by && slot == highlighted_slot)
  {
    m_members[character]->unequip(world, item_type, slot);
    return;
  }
  else
  {
    m_members[character]->unequip(world, item_type, slot);
  }
  if(highlighted_equipped_by != "NULL")
  {
    m_members[highlighted_equipped_by]->unequip(world, item_type, highlighted_slot);
  }
  Equipment* equip{new Equipment{item_name, item_type, world->get_item_description_create(item_name), m_members[character]->get_icon(), world->get_equipment_stat_modifiers(item_name), world->get_equipment_usable_by(item_name), slot, character}};
  ++mem;
  m_members[character]->equip(equip, slot);
  world->remove_equipment(item_name);
}

World::World()
{
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

  #include "Consts/Item_Consts.h"

  m_play_time.start();

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
}

void World::update()
{
  m_party.update_stats();
  m_cursor->finish();
  m_cursor->update();
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
    Equipment* new_item{new Equipment{m_item_database[item]->get_name(), m_item_database[item]->get_type(), m_item_database[item]->get_description_create(), m_item_database[item]->get_icon(), m_item_database[item]->get_stats(), m_item_database[item]->get_usable_by()}};
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

void World::render_progress_bar(const string & color, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_progress_bar_image_names.size()); ++i)
  {
    if(color == m_progress_bar_image_names[i])
    {
      DrawTexturePro(m_progress_bar_textures[i], Rectangle{0, 0, static_cast<float>(m_progress_bar_textures[i].width), static_cast<float>(m_progress_bar_textures[i].height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_progress_bar_textures[i].width), static_cast<float>(m_progress_bar_textures[i].height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
      return;
    }
  }
  crash("Error: Progress bar image \"" + color + "\" doesn't exist!");
}

void World::render_panel(const long & x, const long & y, const long & w, const long & h) const
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

const Player_Info & World::get_party_member_info(const string & name) const
{
  if(name == "Tempest")
  {
    return TEMPEST_SHADOW_INFO;
  }
  else if(name == "Nightwish")
  {
    return NIGHTWISH_INFO;
  }
  else if(name == "Gallus")
  {
    return GALLUS_INFO;
  }
  else
  {
    crash("Error: Party member \"" + name + "\" is not in the game.");
  }
  return TEMPEST_SHADOW_INFO;
}

vector<string> World::get_inventory_item_names() const
{
  vector<Consumable_Item*> itm_ptrs{m_items.get_list()};
  vector<string> ret;
  for(long i{0}; i < static_cast<long>(itm_ptrs.size()); ++i)
  {
    ret.push_back(itm_ptrs[i]->get_name());
  }
  return ret;
}

vector<string> World::get_inventory_key_item_names() const
{
  vector<Key_Item*> itm_ptrs{m_key_items.get_list()};
  vector<string> ret;
  for(long i{0}; i < static_cast<long>(itm_ptrs.size()); ++i)
  {
    ret.push_back(itm_ptrs[i]->get_name());
  }
  return ret;
}

vector<string> World::get_inventory_item_descriptions() const
{
  vector<Consumable_Item*> itm_ptrs{m_items.get_list()};
  vector<string> ret;
  for(long i{0}; i < static_cast<long>(itm_ptrs.size()); ++i)
  {
    ret.push_back(itm_ptrs[i]->get_description());
  }
  return ret;
}

vector<string> World::get_inventory_key_item_descriptions() const
{
  vector<Key_Item*> itm_ptrs{m_key_items.get_list()};
  vector<string> ret;
  for(long i{0}; i < static_cast<long>(itm_ptrs.size()); ++i)
  {
    ret.push_back(itm_ptrs[i]->get_description());
  }
  return ret;
}

vector<long> World::get_inventory_item_quantities() const
{
  vector<Consumable_Item*> itm_ptrs{m_items.get_list()};
  vector<long> ret;
  for(long i{0}; i < static_cast<long>(itm_ptrs.size()); ++i)
  {
    ret.push_back(itm_ptrs[i]->get_count());
  }
  return ret;
}

long World::get_number_of_equipped_and_inventory_weapons() const
{
  long num{m_party.count_equipped_weapons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      ++num;
    }
  }
  return num;
}

long World::get_number_of_equipped_and_inventory_shields() const
{
  long num{m_party.count_equipped_shields()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      ++num;
    }
  }
  return num;
}

long World::get_number_of_equipped_and_inventory_helms() const
{
  long num{m_party.count_equipped_helms()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      ++num;
    }
  }
  return num;
}

long World::get_number_of_equipped_and_inventory_armor() const
{
  long num{m_party.count_equipped_armor()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      ++num;
    }
  }
  return num;
}

long World::get_number_of_equipped_and_inventory_accessories() const
{
  long num{m_party.count_equipped_accessories()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      ++num;
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_weapon_names() const
{
  vector<string> num{m_party.get_equipped_weapon_names()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      num.push_back(m_equipment[i]->get_name());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_shield_names() const
{
  vector<string> num{m_party.get_equipped_shield_names()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      num.push_back(m_equipment[i]->get_name());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_helm_names() const
{
  vector<string> num{m_party.get_equipped_helm_names()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      num.push_back(m_equipment[i]->get_name());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_armor_names() const
{
  vector<string> num{m_party.get_equipped_armor_names()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      num.push_back(m_equipment[i]->get_name());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_accessory_names() const
{
  vector<string> num{m_party.get_equipped_accessory_names()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back(m_equipment[i]->get_name());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_weapon_descriptions() const
{
  vector<string> num{m_party.get_equipped_weapon_descriptions()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      num.push_back(m_equipment[i]->get_description());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_shield_descriptions() const
{
  vector<string> num{m_party.get_equipped_shield_descriptions()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      num.push_back(m_equipment[i]->get_description());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_helm_descriptions() const
{
  vector<string> num{m_party.get_equipped_helm_descriptions()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      num.push_back(m_equipment[i]->get_description());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_armor_descriptions() const
{
  vector<string> num{m_party.get_equipped_armor_descriptions()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      num.push_back(m_equipment[i]->get_description());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_accessory_descriptions() const
{
  vector<string> num{m_party.get_equipped_accessory_descriptions()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back(m_equipment[i]->get_description());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_weapon_quantities() const
{
  vector<long> num;
  for(long i{0}; i < m_party.count_equipped_weapons(); ++i)
  {
    num.push_back(1);
  }
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      num.push_back(m_equipment[i]->get_count());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_shield_quantities() const
{
  vector<long> num;
  for(long i{0}; i < m_party.count_equipped_shields(); ++i)
  {
    num.push_back(1);
  }
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      num.push_back(m_equipment[i]->get_count());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_helm_quantities() const
{
  vector<long> num;
  for(long i{0}; i < m_party.count_equipped_helms(); ++i)
  {
    num.push_back(1);
  }
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      num.push_back(m_equipment[i]->get_count());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_armor_quantities() const
{
  vector<long> num;
  for(long i{0}; i < m_party.count_equipped_armor(); ++i)
  {
    num.push_back(1);
  }
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      num.push_back(m_equipment[i]->get_count());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_accessory_quantities() const
{
  vector<long> num;
  for(long i{0}; i < m_party.count_equipped_accessories(); ++i)
  {
    num.push_back(1);
  }
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back(m_equipment[i]->get_count());
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_weapon_equipped_bys() const
{
  vector<string> num{m_party.get_equipped_weapon_equipped_bys()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      num.push_back("NULL");
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_shield_equipped_bys() const
{
  vector<string> num{m_party.get_equipped_shield_equipped_bys()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      num.push_back("NULL");
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_helm_equipped_bys() const
{
  vector<string> num{m_party.get_equipped_helm_equipped_bys()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      num.push_back("NULL");
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_armor_equipped_bys() const
{
  vector<string> num{m_party.get_equipped_armor_equipped_bys()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      num.push_back("NULL");
    }
  }
  return num;
}

vector<string> World::get_equipped_and_inventory_accessory_equipped_bys() const
{
  vector<string> num{m_party.get_equipped_accessory_equipped_bys()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back("NULL");
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_weapon_icons() const
{
  vector<long> num{m_party.get_equipped_weapon_icons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Weapon")
    {
      num.push_back(m_equipment[i]->get_icon());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_shield_icons() const
{
  vector<long> num{m_party.get_equipped_shield_icons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Shield")
    {
      num.push_back(m_equipment[i]->get_icon());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_helm_icons() const
{
  vector<long> num{m_party.get_equipped_helm_icons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Helm")
    {
      num.push_back(m_equipment[i]->get_icon());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_armor_icons() const
{
  vector<long> num{m_party.get_equipped_armor_icons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Armor")
    {
      num.push_back(m_equipment[i]->get_icon());
    }
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_accessory_icons() const
{
  vector<long> num{m_party.get_equipped_accessory_icons()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back(m_equipment[i]->get_icon());
    }
  }
  return num;
}

vector<bool> World::get_equipped_and_inventory_weapon_usable_bys(const string & character) const
{
  vector<string> num2{get_equipped_and_inventory_weapon_names()};
  vector<bool> num;
  for(long i{0}; i < static_cast<long>(num2.size()); ++i)
  {
    num.push_back(can_use_equipment(character, num2[i]));
  }
  return num;
}

vector<bool> World::get_equipped_and_inventory_shield_usable_bys(const string & character) const
{
  vector<string> num2{get_equipped_and_inventory_shield_names()};
  vector<bool> num;
  for(long i{0}; i < static_cast<long>(num2.size()); ++i)
  {
    num.push_back(can_use_equipment(character, num2[i]));
  }
  return num;
}

vector<bool> World::get_equipped_and_inventory_helm_usable_bys(const string & character) const
{
  vector<string> num2{get_equipped_and_inventory_helm_names()};
  vector<bool> num;
  for(long i{0}; i < static_cast<long>(num2.size()); ++i)
  {
    num.push_back(can_use_equipment(character, num2[i]));
  }
  return num;
}

vector<bool> World::get_equipped_and_inventory_armor_usable_bys(const string & character) const
{
  vector<string> num2{get_equipped_and_inventory_armor_names()};
  vector<bool> num;
  for(long i{0}; i < static_cast<long>(num2.size()); ++i)
  {
    num.push_back(can_use_equipment(character, num2[i]));
  }
  return num;
}

vector<bool> World::get_equipped_and_inventory_accessory_usable_bys(const string & character) const
{
  vector<string> num2{get_equipped_and_inventory_accessory_names()};
  vector<bool> num;
  for(long i{0}; i < static_cast<long>(num2.size()); ++i)
  {
    num.push_back(can_use_equipment(character, num2[i]));
  }
  return num;
}

vector<long> World::get_equipped_and_inventory_accessory_slots() const
{
  vector<long> num{m_party.get_equipped_accessory_slots()};
  for(long i{0}; i < m_equipment.get_list_size(); ++i)
  {
    if(m_equipment[i]->get_type() == "Accessory")
    {
      num.push_back(0);
    }
  }
  return num;
}
