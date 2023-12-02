#ifndef WORLD_H
#define WORLD_H

#include "LTimer.h"
#include "UI.h"

class Fnt;

struct Character_Base_Stats
{
  explicit Character_Base_Stats(){}
  explicit Character_Base_Stats(const long & base_hp, const long & base_mp, const long & defense, const long & resistance, const long & evasion, const long & magic_evasion, const long & critical, const long spirit_growth[MAX_LEVEL], const long stamina_growth[MAX_LEVEL], const long strength_growth[MAX_LEVEL], const long intellect_growth[MAX_LEVEL]) :
                       m_base_hp(base_hp),
                       m_base_mp(base_mp),
                       m_defense(defense),
                       m_resistance(resistance),
                       m_evasion(evasion),
                       m_magic_evasion(magic_evasion),
                       m_critical(critical),
                       m_spirit_growth(spirit_growth),
                       m_stamina_growth(stamina_growth),
                       m_strength_growth(strength_growth),
                       m_intellect_growth(intellect_growth){}
  Character_Base_Stats(const Character_Base_Stats & obj) = default;
  Character_Base_Stats & operator =(const Character_Base_Stats & obj) = default;
  const long m_base_hp{10};
  const long m_base_mp{10};
  const long m_defense{10};
  const long m_resistance{10};
  const long m_evasion{10};
  const long m_magic_evasion{10};
  const long m_critical{10};
  const long* m_spirit_growth{nullptr};
  const long* m_stamina_growth{nullptr};
  const long* m_strength_growth{nullptr};
  const long* m_intellect_growth{nullptr};
};

struct Enemy_Base_Stats
{
  explicit Enemy_Base_Stats(){}
  explicit Enemy_Base_Stats(const long & max_hp, const long & max_mp, const long & defense, const long & resistance, const long & evasion, const long & magic_evasion, const long & critical, const long & spirit, const long & stamina, const long & strength, const long & intellect, const long & level, const long & attack, const long & accuracy) :
                       m_max_hp(max_hp),
                       m_max_mp(max_mp),
                       m_defense(defense),
                       m_resistance(resistance),
                       m_evasion(evasion),
                       m_magic_evasion(magic_evasion),
                       m_critical(critical),
                       m_spirit(spirit),
                       m_stamina(stamina),
                       m_strength(strength),
                       m_intellect(intellect),
                       m_level(level),
                       m_attack(attack),
                       m_accuracy(accuracy){}
  Enemy_Base_Stats(const Enemy_Base_Stats & obj) = default;
  Enemy_Base_Stats & operator =(const Enemy_Base_Stats & obj) = default;
  const long m_max_hp{10};
  const long m_max_mp{10};
  const long m_defense{10};
  const long m_resistance{10};
  const long m_evasion{10};
  const long m_magic_evasion{10};
  const long m_critical{10};
  const long m_spirit{10};
  const long m_stamina{10};
  const long m_strength{10};
  const long m_intellect{10};
  const long m_level{10};
  const long m_attack{10};
  const long m_accuracy{10};
};

class Stat_Modifier
{
  public:
    explicit Stat_Modifier(const string & id, const string & stat, const long & modifier) : m_id(id), m_type("Add"), m_stat(stat), m_add_modifier(modifier){}
    explicit Stat_Modifier(const string & id, const string & stat, const double & modifier) : m_id(id), m_type("Multiply"), m_stat(stat), m_multiply_modifier(modifier){}
    bool operator==(const Stat_Modifier & rhs) const;
    string get_id() const;
    string get_type() const;
    string get_stat() const;
    long get_add_modifier() const;
    double get_multiply_modifier() const;
  private:
    string m_id{"NULL"};
    string m_type{"NULL"};
    string m_stat{"NULL"};
    long m_add_modifier{0};
    double m_multiply_modifier{0};
};

#include "Consts/Base_Stat_Consts.h"

class Stats
{
  public:
    explicit Stats(){}
    explicit Stats(const Enemy_Base_Stats & stats) :
                   m_defense(stats.m_defense),
                   m_resistance(stats.m_resistance),
                   m_evasion(stats.m_evasion),
                   m_magic_evasion(stats.m_magic_evasion),
                   m_critical(stats.m_critical),
                   m_spirit(stats.m_spirit),
                   m_stamina(stats.m_stamina),
                   m_strength(stats.m_strength),
                   m_intellect(stats.m_intellect),
                   m_level(stats.m_level),
                   m_attack(stats.m_attack),
                   m_accuracy(stats.m_accuracy),
                   m_hp_max(stats.m_max_hp),
                   m_mp_max(stats.m_max_mp),
                   m_hp_now(m_hp_max),
                   m_mp_now(m_mp_max){}
    Stats(const Stats & obj) = default;
    Stats & operator =(const Stats & obj) = default;
    virtual ~Stats(){}
    
    virtual void update_stats(){}
    virtual void set_hp(const long & HP);
    virtual void set_mp(const long & mp);
    virtual void add_modifier(const Stat_Modifier & modifier);
    virtual void remove_modifier(const Stat_Modifier & modifier);
    virtual long get_unmodified_stat(const string & stat) const;
    virtual long get_stat(const string & stat) const;

  protected:
    long m_defense{10};
    long m_resistance{10};
    long m_evasion{10};
    long m_magic_evasion{10};
    long m_critical{10};

    long m_spirit{10};
    long m_stamina{10};
    long m_strength{10};
    long m_intellect{10};

    long m_level{1};

    long m_attack{10};
    long m_accuracy{10};
    long m_hp_max{10};
    long m_mp_max{10};
    long m_hp_now{10};
    long m_mp_now{10};

    vector<Stat_Modifier> m_modifiers{};
};

class Player_Stats : public Stats
{
  public:
    explicit Player_Stats(const Character_Base_Stats & stats, const long & level = 1, const long & exp = 0);
    Player_Stats(const Player_Stats & obj) = default;
    Player_Stats & operator =(const Player_Stats & obj) = default;
    
    virtual void update_stats();
    virtual void give_exp(const long & exp);
    virtual void level_up();
    virtual long get_unmodified_stat(const string & stat) const;
    virtual long get_stat(const string & stat) const;

  protected:
    long exp_formula() const;
    long m_base_hp{10};
    long m_base_mp{10};

    const long* m_spirit_growth{nullptr};
    const long* m_stamina_growth{nullptr};
    const long* m_strength_growth{nullptr};
    const long* m_intellect_growth{nullptr};

    long m_exp{0};
    long m_current_level_starting_exp{0};
    
    bool m_ready_to_level_up{false};
};

struct Player_Info
{
  explicit Player_Info(const string & name, const string & species, const string & classs, const bool & starting_row, const Character_Base_Stats & stats, const unsigned char portrait_data[], const long & portrait_size, const unsigned char small_portrait_data[], const long & small_portrait_size) :
                       m_name(name), m_species(species), m_class(classs), m_starting_row(starting_row), m_stats(stats), m_portrait_data(portrait_data), m_portrait_size(portrait_size), m_small_portrait_data(small_portrait_data), m_small_portrait_size(small_portrait_size){}
  Player_Info(const Player_Info & obj) = delete;
  Player_Info & operator =(const Player_Info & obj) = delete;
  
  const string m_name{"NULL"};
  const string m_species{"NULL"};
  const string m_class{"NULL"};
  const bool m_starting_row{true};
  const Character_Base_Stats m_stats{};
  const unsigned char* m_portrait_data{nullptr};
  const long m_portrait_size{1};
  const unsigned char* m_small_portrait_data{nullptr};
  const long m_small_portrait_size{1};
};

#include "Consts/Party_Member_Info_Consts.h"

struct Item
{
  struct Stats
  {
    explicit Stats(const long & strength, const long & speed, const long & intelligence, const long & attack, const long & defense, const long & magic, const long & resist) : m_strength(strength), m_speed(speed), m_intelligence(intelligence), m_attack(attack), m_defense(defense), m_magic(magic), m_resist(resist){}
    long m_strength{0};
    long m_speed{0};
    long m_intelligence{0};
    long m_attack{0};
    long m_defense{0};
    long m_magic{0};
    long m_resist{0};
    ~Stats(){}
  };
  explicit Item(const string & name = "NULL", const string & type = "NULL", const string & description = "", const long & icon = 0, const string & special = "NULL", const long & strength = 0, const long & speed = 0, const long & intelligence = 0, const long & attack = 0, const long & defense = 0, const long & magic = 0, const long & resist = 0) : m_name(name), m_type(type), m_description(description), m_icon(icon), m_special(special), m_stats(strength, speed, intelligence, attack, defense, magic, resist){}
  string get_description() const
  {
    string description{m_description};
    if(m_stats.m_strength != 0)
    {
      (m_stats.m_strength > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_strength) + " Strength";
    }
    if(m_stats.m_speed != 0)
    {
      (m_stats.m_speed > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_speed) + " Speed";
    }
    if(m_stats.m_intelligence != 0)
    {
      (m_stats.m_intelligence > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_intelligence) + " Intelligence";
    }
    if(m_stats.m_attack != 0)
    {
      (m_stats.m_attack > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_attack) + " Attack";
    }
    if(m_stats.m_defense != 0)
    {
      (m_stats.m_defense > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_defense) + " Defense";
    }
    if(m_stats.m_magic != 0)
    {
      (m_stats.m_magic > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_magic) + " Magic";
    }
    if(m_stats.m_resist != 0)
    {
      (m_stats.m_resist > 0) ? (description += " +") : (description += " ");
      description += to_string(m_stats.m_resist) + " Resist";
    }
    return description;
  }
  string m_name{"NULL"};
  string m_type{"NULL"};
  string m_description{"NULL"};
  long m_icon{0};
  string m_special{"NULL"};
  Stats m_stats{0, 0, 0, 0, 0, 0, 0};
  ~Item(){}
};

class Item_Slot
{
  public:
    explicit Item_Slot(const Item & item) : m_item(item){}
    void inc_count()
    {
      ++m_count;
    }
    void dec_count()
    {
      if(m_count > 0)
      {
        --m_count;
      }
    }
    Item get_item() const
    {
      return m_item;
    }
    long get_count() const
    {
      return m_count;
    }
    ~Item_Slot(){}
  private:
    Item m_item{};
    long m_count{1};
};

#include "Consts/Item_Consts.h"

class Party_Member
{
  public:
    explicit Party_Member(const Player_Info & player);
    Party_Member(const Party_Member & obj) = delete;
    Party_Member & operator =(const Party_Member & obj) = delete;
    ~Party_Member();
    
    void update_stats();
    
    string get_name() const;
    string get_species() const;
    string get_class() const;
    long get_portrait_width() const;
    long get_portrait_height() const;
    long get_small_portrait_width() const;
    long get_small_portrait_height() const;
    long get_stat(const string & stat) const;
    long get_unmodified_stat(const string & stat) const;
    bool get_row() const;
    long get_soul_break_level() const;
    void render_portrait(const bool & size, const long & x, const long & y) const;
    void set_front_row();
    void set_back_row();
    void swap_party_members(const string & name1, const string & name2);
    void give_member_exp(const long & exp);
    void level_up();

  private:
    string m_name{"NULL"};
    string m_species{"NULL"};
    string m_class{"NULL"};
    Texture2D m_portrait{};
    Texture2D m_small_portrait{};
    Player_Stats m_stats{TEMPEST_SHADOW_BASE_STATS};
    bool m_row{true};
    long m_soul_break_level{1};
    Item m_equipped_weapon{};
    Item m_equipped_offhand{};
    Item m_equipped_helmet{};
    Item m_equipped_armor{};
    Item m_equipped_accessory_one{};
    Item m_equipped_accessory_two{};
};

class Party
{
  public:
    explicit Party(){}
    Party(const Party & obj) = delete;
    Party & operator =(const Party & obj) = delete;
    ~Party();
    
    void update_stats();
    void add_party_member(const Player_Info & player);
    void remove_party_member(const string & name);
    
    string get_member_name(const long & index) const;
    string get_member_species(const string & name) const;
    string get_member_class(const string & name) const;
    long get_member_portrait_width(const string & name) const;
    long get_member_portrait_height(const string & name) const;
    long get_member_small_portrait_width(const string & name) const;
    long get_member_small_portrait_height(const string & name) const;
    long get_member_stat(const string & name, const string & stat) const;
    long get_member_unmodified_stat(const string & name, const string & stat) const;
    bool get_member_row(const string & name) const;
    long get_member_soul_break_level(const string & name) const;
    void render_member_portrait(const string & name, const bool & size, const long & x, const long & y) const;
    long get_size() const;
    void set_member_front_row(const string & name);
    void set_member_back_row(const string & name);
    void swap_party_members(const string & name1, const string & name2);

  private:
    vector<Party_Member*> m_members{};
};

class World
{
  public:
    explicit World();
    World(const World & obj) = delete;
    World & operator =(const World & obj) = delete;
    ~World();

    void update();
    void render_item(const long & x, const long & y, Fnt* font, const long & item_index, const long & width) const;
    void render_key_item(const long & x, const long & y, Fnt* font, const long & item_index) const;
    void render_stat(const long & x, const long & y, Fnt* font, const long & item_index, const long & width, const string & name) const;
    vector<string> get_items() const;
    vector<string> get_key_items() const;
    Item_Slot get_item(const long & index) const;
    Item_Slot get_item(const string & name) const;
    Item get_key_item(const long & index) const;
    bool has_items() const;
    bool has_item(const string & item) const;
    void add_item(const string & item);
    void remove_item(const string & item);
    void remove_item(const long & item_index);
    bool has_key_items() const;
    bool has_key_item(const string & item) const;
    void add_key_item(const string & item);
    void remove_key_item(const string & item);
    string get_time() const;
    long get_money() const;
    void pause_time();
    void unpause_time();
    
    string get_party_member_name(const long & index) const;
    string get_party_member_species(const string & index) const;
    string get_party_member_class(const string & index) const;
    long get_party_member_portrait_width(const string & index) const;
    long get_party_member_portrait_height(const string & index) const;
    long get_party_member_small_portrait_width(const string & index) const;
    long get_party_member_small_portrait_height(const string & index) const;
    long get_party_member_stat(const string & index, const string & stat) const;
    long get_party_member_unmodified_stat(const string & index, const string & stat) const;
    bool get_party_member_row(const string & index) const;
    long get_party_member_soul_break_level(const string & index) const;
    void render_party_member_portrait(const string & index, const bool & size, const long & x, const long & y) const;
    long get_party_size() const;
    void set_party_member_front_row(const string & index);
    void set_party_member_back_row(const string & index);
    void swap_party_members(const string & name1, const string & name2);
    
  private:
    LTimer m_time{};
    long m_money{0};
    vector<Item_Slot> m_items{};
    vector<Item> m_key_items{};
    Texture2D m_item_icons_tex{};
    Party m_party{};
};

#endif