#ifndef WORLD_H
#define WORLD_H

#include "Cursor.h"
#include "LTimer.h"
#include "UI.h"

class Fnt;

struct Character_Base_Stats
{
  explicit Character_Base_Stats(){}
  explicit Character_Base_Stats(const long & base_hp, const long & base_mp, const long & defense, const long & resistance, const long & evasion, const long & magic_evasion, const long & critical, const array<long, MAX_LEVEL> & spirit_growth, const array<long, MAX_LEVEL> & stamina_growth, const array<long, MAX_LEVEL> & strength_growth, const array<long, MAX_LEVEL> & intellect_growth) :
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
  const long m_base_hp{10};
  const long m_base_mp{10};
  const long m_defense{10};
  const long m_resistance{10};
  const long m_evasion{10};
  const long m_magic_evasion{10};
  const long m_critical{10};
  const array<long, MAX_LEVEL> m_spirit_growth{};
  const array<long, MAX_LEVEL> m_stamina_growth{};
  const array<long, MAX_LEVEL> m_strength_growth{};
  const array<long, MAX_LEVEL> m_intellect_growth{};
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
    explicit Stat_Modifier(const string & id, const string & stat, const long & modifier, const bool & replace) : m_id(id), m_type(replace == true ? "Replace" : "Add"), m_stat(stat), m_replace_modifier(replace == true ? modifier : 0), m_add_modifier(replace == true ? 0 : modifier){}
    explicit Stat_Modifier(const string & id, const string & stat, const double & modifier) : m_id(id), m_type("Multiply"), m_stat(stat), m_multiply_modifier(modifier){}
    bool operator==(const Stat_Modifier & rhs) const;
    string get_id() const;
    string get_type() const;
    string get_stat() const;
    long get_replace_modifier() const;
    long get_add_modifier() const;
    double get_multiply_modifier() const;
  private:
    string m_id{"NULL"};
    string m_type{"NULL"};
    string m_stat{"NULL"};
    long m_replace_modifier{0};
    long m_add_modifier{0};
    double m_multiply_modifier{0};
};

const Character_Base_Stats TEMPEST_SHADOW_BASE_STATS{58, 25, 42, 29, 5, 2, 5, TEMPEST_SPIRIT_GROWTH, TEMPEST_STAMINA_GROWTH, TEMPEST_STRENGTH_GROWTH, TEMPEST_INTELLECT_GROWTH};
const Character_Base_Stats NIGHTWISH_BASE_STATS{80, 28, 35, 33, 3, 6, 4, NIGHTWISH_SPIRIT_GROWTH, NIGHTWISH_STAMINA_GROWTH, NIGHTWISH_STRENGTH_GROWTH, NIGHTWISH_INTELLECT_GROWTH};
const Character_Base_Stats GALLUS_BASE_STATS{46, 20, 31, 25, 2, 1, 8, GALLUS_SPIRIT_GROWTH, GALLUS_STAMINA_GROWTH, GALLUS_STRENGTH_GROWTH, GALLUS_INTELLECT_GROWTH};

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
    
    virtual void update_stats();
    virtual void give_exp(const long & exp);
    virtual void level_up();
    virtual long get_unmodified_stat(const string & stat) const;
    virtual long get_stat(const string & stat) const;

  protected:
    long exp_formula() const;
    long m_base_hp{10};
    long m_base_mp{10};

    array<long, MAX_LEVEL> m_spirit_growth{};
    array<long, MAX_LEVEL> m_stamina_growth{};
    array<long, MAX_LEVEL> m_strength_growth{};
    array<long, MAX_LEVEL> m_intellect_growth{};

    long m_exp{0};
    long m_current_level_starting_exp{0};
    
    bool m_ready_to_level_up{false};
};

struct Player_Info
{
  explicit Player_Info(const string & name, const string & species, const string & classs, const bool & starting_row, const long & icon, const Character_Base_Stats & stats, const Image_Params & portrait, const Image_Params & small_portrait, const Font_Params & font) :
                       m_name(name), m_species(species), m_class(classs), m_starting_row(starting_row), m_icon(icon), m_stats(stats), m_portrait_data(portrait.m_data), m_portrait_size(portrait.m_size), m_small_portrait_data(small_portrait.m_data), m_small_portrait_size(small_portrait.m_size), m_font(font){}
  Player_Info(const Player_Info & obj) = delete;
  Player_Info & operator =(const Player_Info & obj) = delete;

  const string m_name{"NULL"};
  const string m_species{"NULL"};
  const string m_class{"NULL"};
  const bool m_starting_row{true};
  const long m_icon{0};
  const Character_Base_Stats m_stats{};
  const unsigned char* m_portrait_data{nullptr};
  const long m_portrait_size{1};
  const unsigned char* m_small_portrait_data{nullptr};
  const long m_small_portrait_size{1};
  const Font_Params m_font{TEXT_FONT};
};

const Player_Info TEMPEST_SHADOW_INFO{"Tempest", "Unicorn", "Battlemage", false, 19, TEMPEST_SHADOW_BASE_STATS, TEMPEST_PORTRAIT_IMAGE, TEMPEST_SMALL_PORTRAIT_IMAGE, TEMPEST_FONT};
const Player_Info NIGHTWISH_INFO{"Nightwish", "Thestral", "Lunar Duelist", true, 20, NIGHTWISH_BASE_STATS, NIGHTWISH_PORTRAIT_IMAGE, NIGHTWISH_SMALL_PORTRAIT_IMAGE, NIGHTWISH_FONT};
const Player_Info GALLUS_INFO{"Gallus", "Griffon", "Solar Fighter", true, 21, GALLUS_BASE_STATS, GALLUS_PORTRAIT_IMAGE, GALLUS_SMALL_PORTRAIT_IMAGE, GALLUS_FONT};

class Item
{
  public:
    explicit Item(){}
    virtual ~Item(){}
    virtual string get_name() const;
    virtual string get_type() const;
    virtual string get_description() const = 0;
    virtual long get_icon() const;
    virtual void increment_count(){}
    virtual void decrement_count(){}
    virtual long get_count() const;
//    virtual void use(){}
  protected:
    string m_name{"NULL"};
    string m_type{"NULL"};
    string m_description{"NULL"};
    long m_icon{0};
};

class Consumable_Item : public Item
{
  public:
    explicit Consumable_Item(const string & name, const string & description);
    virtual ~Consumable_Item(){}
    virtual string get_description() const;
    virtual void increment_count();
    virtual void decrement_count();
    virtual long get_count() const;
//    virtual void use();
  protected:
    long m_count{1};
};

class Key_Item : public Item
{
  public:
    explicit Key_Item(const string & name, const string & description);
    virtual ~Key_Item(){}
    virtual string get_description() const;
//    virtual void use();
};

class Equipment : public Item
{
  public:
    explicit Equipment(const string & name, const string & type, const string & description, const long & icon, const vector<Stat_Modifier> stats, const vector<string> & usable_by = vector<string>{}, const string & equipped_by = "NULL");
    virtual ~Equipment(){}
    virtual string get_description() const;
    virtual void increment_count();
    virtual void decrement_count();
    virtual long get_count() const;
    virtual bool can_equip(const string & party_member_name) const;
    virtual void set_equip_by(const string & name);
    virtual string equipped_by() const;
  protected:
    long m_count{1};
    vector<string> m_usable_by{};
    vector<Stat_Modifier> m_stats{};
    string m_equipped_by{"NULL"};
};
/*
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
*/

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
    bool set_front_row();
    bool set_back_row();
    void swap_party_members(const string & name1, const string & name2);
    void give_member_exp(const long & exp);
    void level_up();
    void equip(World* world, const string & item_name);
    Equipment* get_equipped_weapon() const;
    Equipment* get_equipped_shield() const;
    Equipment* get_equipped_helm() const;
    Equipment* get_equipped_armor() const;
    Equipment* get_equipped_accessory_one() const;
    Equipment* get_equipped_accessory_two() const;
    long get_icon() const;
    Fnt* get_font() const;

  private:
    string m_name{"NULL"};
    string m_species{"NULL"};
    string m_class{"NULL"};
    Texture2D m_portrait{};
    Texture2D m_small_portrait{};
    Fnt* m_font{nullptr};
    Player_Stats m_stats{TEMPEST_SHADOW_BASE_STATS};
    bool m_row{true};
    long m_soul_break_level{1};
    long m_icon{0};
    Equipment* m_equipped_weapon{nullptr};
    Equipment* m_equipped_offhand{nullptr};
    Equipment* m_equipped_helmet{nullptr};
    Equipment* m_equipped_armor{nullptr};
    Equipment* m_equipped_accessory_one{nullptr};
    Equipment* m_equipped_accessory_two{nullptr};
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
    string get_next_member_name(const string & name) const;
    string get_previous_member_name(const string & name) const;
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
    bool set_member_front_row(const string & name);
    bool set_member_back_row(const string & name);
    void swap_party_members(const string & name1, const string & name2);
    void equip(World* world, const string & party_member_name, const string & item_name);
    vector<Equipment*> get_equipped_equipment() const;
    vector<Equipment*> get_equipped_weapons() const;
    vector<Equipment*> get_equipped_shields() const;
    vector<Equipment*> get_equipped_helms() const;
    vector<Equipment*> get_equipped_armor() const;
    vector<Equipment*> get_equipped_accessories() const;
    Party_Member* get_member(const string & name) const;

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
    void render_item(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_key_item(const long & x, const long & y, const long & font_no, const long & item_index) const;
    void render_weapon(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_shield(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_helm(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_armor(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_accessory(const long & x, const long & y, const long & font_no, const long & item_index, const long & width) const;
    void render_stat(const long & x, const long & y, const long & font_no, const long & item_index, const long & width, const string & name) const;
    void render_cursor() const;
    void render_text_center(const long & font_no, const string & text, const long & y_pos, const long & alpha = 255) const;
    void render_text(const long & font_no, const string & text, const long & x_pos, const long & y_pos, const long & alpha = 255) const;
    void render_letter(const long & font_no, const long & x, const long & y, const char & id, const long & alpha = 255) const;
    void render_panel(const double & x, const double & y, const double & w, const double & h) const;
    void render_continue_arrow(const long & x, const long & y) const;
    void render_progress_bar(const string & progress_bar_name, const long & x, const long & y) const;

    vector<string> get_items() const;
    vector<string> get_key_items() const;
    vector<string> get_weapons() const;
    vector<string> get_shields() const;
    vector<string> get_helms() const;
    vector<string> get_armor() const;
    vector<string> get_accessories() const;
    string get_item_description(const string & item_name) const;

    bool can_use_weapon(const string & party_member_name, const long & item_index) const;
    bool can_use_shield(const string & party_member_name, const long & item_index) const;
    bool can_use_helm(const string & party_member_name, const long & item_index) const;
    bool can_use_armor(const string & party_member_name, const long & item_index) const;
    bool can_use_accessory(const string & party_member_name, const long & item_index) const;
    void equip(World* world, const string & party_member_name, const string & item_name);

    bool has_items() const;
    bool has_item(const string & item) const;
    void add_item(const string & item);
    void remove_item(const string & item);
    bool has_key_items() const;
    bool has_key_item(const string & item) const;
    void add_key_item(const string & item);
    void remove_key_item(const string & item);
    bool has_weapons() const;
    bool has_shields() const;
    bool has_helms() const;
    bool has_armor() const;
    bool has_accessories() const;
    bool has_equipment(const string & item) const;
    void add_equipment(const string & item);
    void remove_equipment(const string & item);

    string get_time() const;
    long get_money() const;
    void pause_time();
    void unpause_time();
    void set_cursor_destination(const long & end_x, const long & end_y);
    long get_font_height(const long & font_no) const;
    long get_word_width(const long & font_no, const string & text) const;
    long get_char_width(const long & font_no, const char & text) const;
    void play_global_sound(const string & name) const;
    
    string get_party_member_name(const long & index) const;
    string get_party_member_species(const string & index) const;
    string get_party_member_class(const string & index) const;
    string get_next_party_member_name(const string & name) const;
    string get_previous_party_member_name(const string & name) const;
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
    bool set_party_member_front_row(const string & index);
    bool set_party_member_back_row(const string & index);
    void swap_party_members(const string & name1, const string & name2);
    void add_party_member(const Player_Info & player);
    string get_equipment_type(const string & name) const;
    Equipment* get_equipment(const string & name) const;
    
  private:
    LTimer m_time{};
    long m_money{0};
    vector<Consumable_Item*> m_items{};
    vector<Key_Item*> m_key_items{};
    vector<Equipment*> m_equipment{};
    Texture2D m_item_icons_tex{};
    Texture2D m_panel_texture{};
    Texture2D m_continue_arrow_texture{};
    Party m_party{};
    vector<Fnt*> m_fonts{};
    Cursor* m_cursor{nullptr};
    vector<Sound> m_global_sounds{};
    vector<string> m_global_sound_names{};
    vector<Item*> m_item_database{};
    vector<string> m_progress_bar_image_names{};
    vector<Texture2D> m_progress_bar_textures{};
};

#endif
