#ifndef WORLD_H
#define WORLD_H

#include "Cursor.h"
#include "LTimer.h"
#include "Font.h"

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
    bool operator==(const Stat_Modifier & rhs) const{return m_id == rhs.get_id() && m_slot == rhs.get_slot();}
    string get_id() const{return m_id;}
    string get_type() const{return m_type;}
    string get_stat() const{return m_stat;}
    long get_replace_modifier() const{return m_replace_modifier;}
    long get_add_modifier() const{return m_add_modifier;}
    double get_multiply_modifier() const{return m_multiply_modifier;}
    void set_slot(const long & slot){m_slot = slot;}
    long get_slot() const{return m_slot;}
  private:
    string m_id{"NULL"};
    string m_type{"NULL"};
    string m_stat{"NULL"};
    long m_replace_modifier{0};
    long m_add_modifier{0};
    double m_multiply_modifier{1};
    long m_slot{-1};
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
    virtual void add_modifier(Stat_Modifier & modifier, const long & slot = 0);
    virtual void remove_modifier(Stat_Modifier & modifier, const long & slot = 0);
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
    long exp_formula() const{double pow_i{2.4 + EXP_INFLATION / 100.0}; return EXP_BASE * pow(m_level + 4, pow_i) / pow(5, pow_i);}
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
  const char m_char_code{'0'};
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
    Item(const Item & obj) = delete;
    Item & operator =(const Item & obj) = delete;
    virtual ~Item(){}
    virtual string get_name() const{return m_name;}
    virtual string get_type() const{return m_type;}
    virtual string get_description_create() const = 0;
    virtual string get_description() const = 0;
    virtual long get_icon() const{return m_icon;}
    virtual void increment_count(){}
    virtual void decrement_count(){}
    virtual long get_count() const{return -1;}
    virtual vector<Stat_Modifier> get_stats() const{return vector<Stat_Modifier>{};}
    virtual vector<string> get_usable_by() const{return vector<string>{};}
    virtual bool is_usable_by(const string & character_name) const;
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
    virtual string get_description_create() const{return m_description;}
    virtual string get_description() const{return m_description;}
    virtual void increment_count(){++m_count;}
    virtual void decrement_count(){--m_count;}
    virtual long get_count() const{return m_count;}
//    virtual void use();
  protected:
    long m_count{1};
};

class Key_Item : public Item
{
  public:
    explicit Key_Item(const string & name, const string & description);
    virtual ~Key_Item(){}
    virtual string get_description_create() const{return m_description;}
    virtual string get_description() const{return m_description;}
//    virtual void use();
};

class Equipment : public Item
{
  public:
    explicit Equipment(const string & name, const string & type, const string & description, const long & icon, const vector<Stat_Modifier> stats, const vector<string> & usable_by = vector<string>{}, const long & slot = 0, const string & equipped_by = "NULL", const long & count = 1);
    Equipment(const Equipment & obj) = delete;
    Equipment & operator =(const Equipment & obj) = delete;
    virtual ~Equipment(){}
    virtual string get_description_create() const;
    virtual string get_description() const{return m_description;}
    virtual vector<Stat_Modifier> get_stats() const{return m_stats;}
    virtual vector<string> get_usable_by() const{return m_usable_by;}
    virtual bool is_usable_by(const string & character_name) const;
    virtual void increment_count(){++m_count;}
    virtual void decrement_count(){--m_count;}
    virtual long get_count() const{return m_count;}
    virtual string get_equipped_by() const{return m_equipped_by;}
    virtual long get_slot() const{return m_slot;}

  protected:
    long m_count{1};
    vector<string> m_usable_by{};
    vector<Stat_Modifier> m_stats{};
    long m_slot{0};
    string m_equipped_by{"NULL"};
};

class World;

class Party_Member
{
  public:
    explicit Party_Member(const Player_Info & player);
    Party_Member(const Party_Member & obj) = delete;
    Party_Member & operator =(const Party_Member & obj) = delete;
    ~Party_Member();
    
    void update_stats(){m_stats.update_stats();}
    
    string get_name() const{return m_name;}
    string get_species() const{return m_species;}
    string get_class() const{return m_class;}
    long get_stat(const string & stat) const{return m_stats.get_stat(stat);}
    long get_unmodified_stat(const string & stat) const{return m_stats.get_unmodified_stat(stat);}
    bool get_row() const{return m_row;}
    long get_soul_break_level() const{return m_soul_break_level;}
    bool set_front_row();
    bool set_back_row();
    void swap_party_members(const string & name1, const string & name2);
    void give_member_exp(const long & exp){m_stats.give_exp(exp);}
    void level_up(){m_stats.level_up();}
    void equip(Equipment* equip, const long & slot = 0);
    void unequip(World* world, const string & item_type, const long & slot = 0);
    Equipment* get_equipped_weapon() const;
    Equipment* get_equipped_shield() const;
    Equipment* get_equipped_helm() const;
    Equipment* get_equipped_armor() const;
    Equipment* get_equipped_accessory_one() const;
    Equipment* get_equipped_accessory_two() const;
    long get_icon() const{return m_icon;}
    void render_portrait(const long & x, const long & y) const{DrawTexturePro(m_portrait, Rectangle{0, 0, static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    vector<long> predict_stats(const World* const world, const string & item_name, const string & item_type, const bool & same_item, const long & slot = 0, const long & highlighted_slot = 0, const string & highlighted_equipped_by = "NULL") const;
  private:
    string m_name{"NULL"};
    string m_species{"NULL"};
    string m_class{"NULL"};
    Texture2D m_portrait{};
    Texture2D m_small_portrait{};
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
    
    void update_stats();
    void add_party_member(const Player_Info & player){m_members.add(new Party_Member(player)); ++mem;}
    void remove_party_member(const string & name){m_members.remove(name);}
    
    string get_member_name(const long & index) const{return m_members[index]->get_name();}
    string get_member_species(const string & name) const{return m_members[name]->get_species();}
    string get_member_class(const string & name) const{return m_members[name]->get_class();}
    long get_member_icon(const string & name) const{return m_members[name]->get_icon();}
    long get_member_stat(const string & name, const string & stat) const{return m_members[name]->get_stat(stat);}
    long get_member_unmodified_stat(const string & name, const string & stat) const{return m_members[name]->get_unmodified_stat(stat);}
    bool get_member_row(const string & name) const{return m_members[name]->get_row();}
    long get_member_soul_break_level(const string & name) const{return m_members[name]->get_soul_break_level();}
    long count_equipped_weapons() const;
    long count_equipped_shields() const;
    long count_equipped_helms() const;
    long count_equipped_armor() const;
    long count_equipped_accessories() const;
    long get_size() const{return m_members.get_list_size();}
    bool set_member_front_row(const string & name){return m_members[name]->set_front_row();}
    bool set_member_back_row(const string & name){return m_members[name]->set_back_row();}
    void swap_party_members(const string & name1, const string & name2){m_members.swap(name1, name2);}
    string get_next_member(const string & name) const;
    string get_previous_member(const string & name) const;
    vector<string> get_equipped_weapon_names() const;
    vector<string> get_equipped_shield_names() const;
    vector<string> get_equipped_helm_names() const;
    vector<string> get_equipped_armor_names() const;
    vector<string> get_equipped_accessory_names() const;
    void render_member_portrait(const string & character, const long & x, const long & y) const{m_members[character]->render_portrait(x, y);}
    vector<string> get_equipped_weapon_descriptions() const;
    vector<string> get_equipped_shield_descriptions() const;
    vector<string> get_equipped_helm_descriptions() const;
    vector<string> get_equipped_armor_descriptions() const;
    vector<string> get_equipped_accessory_descriptions() const;
    vector<string> get_equipped_weapon_equipped_bys() const;
    vector<string> get_equipped_shield_equipped_bys() const;
    vector<string> get_equipped_helm_equipped_bys() const;
    vector<string> get_equipped_armor_equipped_bys() const;
    vector<string> get_equipped_accessory_equipped_bys() const;
    vector<long> get_equipped_weapon_icons() const;
    vector<long> get_equipped_shield_icons() const;
    vector<long> get_equipped_helm_icons() const;
    vector<long> get_equipped_armor_icons() const;
    vector<long> get_equipped_accessory_icons() const;
    vector<long> get_equipped_accessory_slots() const;
    void equip(World* world, const string & character, const string & item_name, const string & item_type, const long & slot, const string & highlighted_equipped_by, const long & highlighted_slot);
    string get_member_equipped_weapon_name(const string & character) const{return m_members[character]->get_equipped_weapon() == nullptr ? "NULL" : m_members[character]->get_equipped_weapon()->get_name();}
    string get_member_equipped_shield_name(const string & character) const{return m_members[character]->get_equipped_shield() == nullptr ? "NULL" : m_members[character]->get_equipped_shield()->get_name();}
    string get_member_equipped_helm_name(const string & character) const{return m_members[character]->get_equipped_helm() == nullptr ? "NULL" : m_members[character]->get_equipped_helm()->get_name();}
    string get_member_equipped_armor_name(const string & character) const{return m_members[character]->get_equipped_armor() == nullptr ? "NULL" : m_members[character]->get_equipped_armor()->get_name();}
    string get_member_equipped_accessory_one_name(const string & character) const{return m_members[character]->get_equipped_accessory_one() == nullptr ? "NULL" : m_members[character]->get_equipped_accessory_one()->get_name();}
    string get_member_equipped_accessory_two_name(const string & character) const{return m_members[character]->get_equipped_accessory_two() == nullptr ? "NULL" : m_members[character]->get_equipped_accessory_two()->get_name();}
    vector<long> predict_stats(const World* const world, const string & character, const string & item_name, const string & item_type, const bool & same_item, const long & slot = 0, const long & highlighted_slot = 0, const string & highlighted_equipped_by = "NULL") const{return m_members[character]->predict_stats(world, item_name, item_type, same_item, slot, highlighted_slot, highlighted_equipped_by);}
  private:
    List<Party_Member> m_members{};
};

class World
{
  public:
    explicit World();
    World(const World & obj) = delete;
    World & operator =(const World & obj) = delete;
    ~World();

    void update();

    long get_money() const{return m_money;}
    void render_cursor() const{m_cursor->render();}
    bool has_items() const{return m_items.get_list_size() != 0;}
    bool has_item(const string & item) const{return m_items.is_in_list(item);}
    void add_item(const string & item);
    void remove_item(const string & item);
    bool has_key_items() const{return m_key_items.get_list_size() != 0;}
    bool has_key_item(const string & item) const{return m_key_items.is_in_list(item);}
    void add_key_item(const string & item);
    void remove_key_item(const string & item);
    void add_equipment(const string & item);
    void remove_equipment(const string & item);
    void render_text_center(const string & font_name, string text, const long & y_pos, const long & alpha = 255) const{m_fonts[font_name]->render_text_center(text, y_pos, alpha);}
    void pause_play_time(){m_play_time.pause();}
    void unpause_play_time(){m_play_time.unpause();}
    void render_progress_bar(const string & color, const long & x, const long & y) const;
    void render_letter(const string & font_name, const long & x, const long & y, const char & id, const long & alpha = 255) const{m_fonts[font_name]->render_letter(x, y, id, alpha);}
    void render_text(const string & font_name, string text, const long & x, const long & y, const long & alpha = 255) const{m_fonts[font_name]->render_text(text, x, y, alpha);}
    void render_continue_arrow(const long & x, const long & y, const bool & yflip) const{DrawTexturePro(m_continue_arrow_texture, Rectangle{0, 0, static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Rectangle{static_cast<float>(x - m_continue_arrow_texture.width / 2), static_cast<float>(y), static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Vector2{static_cast<float>(m_continue_arrow_texture.width / 2), 0}, 180 * yflip, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    void render_panel(const long & x, const long & y, const long & w, const long & h) const;
    void set_cursor_destination(const long & x, const long & y){m_cursor->set_destination(x, y);}
    void add_party_member(const Player_Info* const member){m_party.add_party_member(*member);}
    long get_number_of_items() const{return m_items.get_list_size();}
    long get_number_of_key_items() const{return m_key_items.get_list_size();}
    long get_party_size() const{return m_party.get_size();}
    string get_party_member_name(const long & index) const{return m_party.get_member_name(index);}
    string get_party_member_species(const string & name) const{return m_party.get_member_species(name);}
    string get_party_member_class(const string & name) const{return m_party.get_member_class(name);}
    const Player_Info & get_party_member_info(const string & name) const;
    long get_party_member_stat(const string & name, const string & stat) const{return m_party.get_member_stat(name, stat);}
    long get_party_member_unmodified_stat(const string & name, const string & stat) const{return m_party.get_member_unmodified_stat(name, stat);}
    bool get_party_member_row(const string & name) const{return m_party.get_member_row(name);}
    bool set_party_member_front_row(const string & name){return m_party.set_member_front_row(name);}
    bool set_party_member_back_row(const string & name){return m_party.set_member_back_row(name);}
    void swap_party_members(const string & name1, const string & name2){m_party.swap_party_members(name1, name2);}
    double get_play_time_ticks() const{return m_play_time.get_ticks();}
    string get_item_name(const long & index) const{return m_items[index]->get_name();}
    void render_item_icon(const long & icon, const long & x, const long & y) const{DrawTexturePro(m_item_icons_tex, Rectangle{static_cast<float>(ICON_WIDTH * icon), 0, ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y + (TEXT_FONT_HEIGHT - m_item_icons_tex.height) / 2), ICON_WIDTH, static_cast<float>(m_item_icons_tex.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    vector<string> get_inventory_item_names() const;
    vector<string> get_inventory_key_item_names() const;
    vector<string> get_inventory_item_descriptions() const;
    vector<string> get_inventory_key_item_descriptions() const;
    vector<long> get_inventory_item_quantities() const;
    long get_number_of_equipped_and_inventory_weapons() const;
    long get_number_of_equipped_and_inventory_shields() const;
    long get_number_of_equipped_and_inventory_helms() const;
    long get_number_of_equipped_and_inventory_armor() const;
    long get_number_of_equipped_and_inventory_accessories() const;
    string get_next_party_member(const string & character) const{return m_party.get_next_member(character);}
    string get_previous_party_member(const string & character) const{return m_party.get_previous_member(character);}
    vector<string> get_equipped_and_inventory_weapon_names() const;
    vector<string> get_equipped_and_inventory_shield_names() const;
    vector<string> get_equipped_and_inventory_helm_names() const;
    vector<string> get_equipped_and_inventory_armor_names() const;
    vector<string> get_equipped_and_inventory_accessory_names() const;
    bool can_use_equipment(const string & character_name, const string & item_name) const{return m_item_database[item_name]->is_usable_by(character_name);}
    void render_party_member_portrait(const string & character, const long & x, const long & y) const{m_party.render_member_portrait(character, x, y);}
    vector<string> get_equipped_and_inventory_weapon_descriptions() const;
    vector<string> get_equipped_and_inventory_shield_descriptions() const;
    vector<string> get_equipped_and_inventory_helm_descriptions() const;
    vector<string> get_equipped_and_inventory_armor_descriptions() const;
    vector<string> get_equipped_and_inventory_accessory_descriptions() const;
    vector<long> get_equipped_and_inventory_weapon_quantities() const;
    vector<long> get_equipped_and_inventory_shield_quantities() const;
    vector<long> get_equipped_and_inventory_helm_quantities() const;
    vector<long> get_equipped_and_inventory_armor_quantities() const;
    vector<long> get_equipped_and_inventory_accessory_quantities() const;
    vector<string> get_equipped_and_inventory_weapon_equipped_bys() const;
    vector<string> get_equipped_and_inventory_shield_equipped_bys() const;
    vector<string> get_equipped_and_inventory_helm_equipped_bys() const;
    vector<string> get_equipped_and_inventory_armor_equipped_bys() const;
    vector<string> get_equipped_and_inventory_accessory_equipped_bys() const;
    vector<long> get_equipped_and_inventory_weapon_icons() const;
    vector<long> get_equipped_and_inventory_shield_icons() const;
    vector<long> get_equipped_and_inventory_helm_icons() const;
    vector<long> get_equipped_and_inventory_armor_icons() const;
    vector<long> get_equipped_and_inventory_accessory_icons() const;
    vector<bool> get_equipped_and_inventory_weapon_usable_bys(const string & character) const;
    vector<bool> get_equipped_and_inventory_shield_usable_bys(const string & character) const;
    vector<bool> get_equipped_and_inventory_helm_usable_bys(const string & character) const;
    vector<bool> get_equipped_and_inventory_armor_usable_bys(const string & character) const;
    vector<bool> get_equipped_and_inventory_accessory_usable_bys(const string & character) const;
    vector<long> get_equipped_and_inventory_accessory_slots() const;
    void equip(World* world, const string & character, const string & item_name, const string & item_type, const long & slot, const string & highlighted_equipped_by, const long & highlighted_slot = 0){m_party.equip(world, character, item_name, item_type, slot, highlighted_equipped_by, highlighted_slot);}
    string get_item_description(const string & item_name) const{return m_item_database[item_name]->get_description();}
    string get_item_description_create(const string & item_name) const{return m_item_database[item_name]->get_description_create();}
    vector<Stat_Modifier> get_equipment_stat_modifiers(const string & item_name) const{return m_item_database[item_name]->get_stats();}
    vector<string> get_equipment_usable_by(const string & item_name) const{return m_item_database[item_name]->get_usable_by();}
    long get_item_icon(const string & item_name) const{return m_item_database.is_in_list(item_name) == true ? m_item_database[item_name]->get_icon() : 0;}
    string get_party_member_equipped_weapon_name(const string & character) const{return m_party.get_member_equipped_weapon_name(character);}
    string get_party_member_equipped_shield_name(const string & character) const{return m_party.get_member_equipped_shield_name(character);}
    string get_party_member_equipped_helm_name(const string & character) const{return m_party.get_member_equipped_helm_name(character);}
    string get_party_member_equipped_armor_name(const string & character) const{return m_party.get_member_equipped_armor_name(character);}
    string get_party_member_equipped_accessory_one_name(const string & character) const{return m_party.get_member_equipped_accessory_one_name(character);}
    string get_party_member_equipped_accessory_two_name(const string & character) const{return m_party.get_member_equipped_accessory_two_name(character);}
    vector<long> predict_stats(const World* const world, const string & character, const string & item_name, const string & item_type, const bool & same_item, const long & slot = 0, const long & highlighted_slot = 0, const string & highlighted_equipped_by = "NULL") const{return m_party.predict_stats(world, character, item_name, item_type, same_item, slot, highlighted_slot, highlighted_equipped_by);}
  private:
    LTimer m_play_time{};
    long m_money{0};
    List<Consumable_Item> m_items{};
    List<Key_Item> m_key_items{};
    List<Equipment> m_equipment{};
    Texture2D m_item_icons_tex{};
    Texture2D m_panel_texture{};
    Texture2D m_continue_arrow_texture{};
    Party m_party{};
    List<Fnt> m_fonts{};
    Cursor* m_cursor{nullptr};
    List<Item> m_item_database{};
    vector<string> m_progress_bar_image_names{};
    vector<Texture2D> m_progress_bar_textures{};
};

#endif
