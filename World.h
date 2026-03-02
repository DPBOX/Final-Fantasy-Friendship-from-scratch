#ifndef WORLD_H
#define WORLD_H
#include "LTimer.h"

class Fnt;
class World;
class Cursor;

struct Character_Base_Stats
{
  explicit Character_Base_Stats(){}
  explicit Character_Base_Stats(const long & base_hp, const long & base_mp, const long & attack, const long & defense, const long & magic, const long & speed) : m_base_hp(base_hp), m_base_mp(base_mp), m_attack(attack), m_defense(defense), m_magic(magic), m_speed(speed){}
  const long m_base_hp{10};
  const long m_base_mp{10};
  const long m_attack{10};
  const long m_defense{10};
  const long m_magic{10};
  const long m_speed{1};
};

struct Enemy_Base_Stats
{
  explicit Enemy_Base_Stats(){}
  explicit Enemy_Base_Stats(const long & max_hp, const long & max_mp, const long & attack, const long & defense, const long & magic, const long & speed) : m_max_hp(max_hp), m_max_mp(max_mp), m_attack(attack), m_defense(defense), m_magic(magic), m_speed(speed){}
  const long m_max_hp{10};
  const long m_max_mp{10};
  const long m_attack{10};
  const long m_defense{10};
  const long m_magic{10};
  const long m_speed{1};
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

const Character_Base_Stats TWILIGHT_SPARKLE_BASE_STATS{31, 19, 6, 16, 28, 16};
const Character_Base_Stats PINKIE_PIE_BASE_STATS{30, 0, 11, 19, 15, 25};
const Character_Base_Stats APPLEJACK_BASE_STATS{41, 0, 16, 20, 12, 15};
const Character_Base_Stats RAINBOW_DASH_BASE_STATS{38, 3, 14, 15, 15, 28};
const Character_Base_Stats FLUTTERSHY_BASE_STATS{24, 13, 16, 16, 24, 20};
const Character_Base_Stats RARITY_BASE_STATS{26, 19, 9, 12, 23, 22};

const Enemy_Base_Stats CHANGELING_STATS{100, 1, 10, 10, 5, 1};

class Stats
{
  public:
    explicit Stats(){}
    explicit Stats(const Enemy_Base_Stats & stats) : m_hp_now(stats.m_max_hp), m_hp_max(stats.m_max_hp), m_mp_now(stats.m_max_mp), m_mp_max(stats.m_max_mp), m_attack(stats.m_attack), m_defense(stats.m_defense), m_magic(stats.m_magic), m_speed(stats.m_speed){}
    virtual ~Stats(){}
    
    virtual void update_stats(){}
    virtual void set_hp(const long & HP);
    virtual void set_mp(const long & mp);
    virtual void add_modifier(Stat_Modifier & modifier, const long & slot = 0);
    virtual void remove_modifier(Stat_Modifier & modifier, const long & slot = 0);
    virtual long get_unmodified_stat(const string & stat) const;
    virtual long get_stat(const string & stat) const;

  protected:
    long m_hp_now{10};
    long m_hp_max{10};
    long m_mp_now{10};
    long m_mp_max{10};
    long m_attack{10};
    long m_defense{10};
    long m_magic{10};
    long m_speed{1};

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
    long exp_formula() const{/*double pow_i{2.4 + EXP_INFLATION / 100.0}; return EXP_BASE * pow(m_level + 4, pow_i) / pow(5, pow_i);*/return 1;}
    long m_base_hp{10};
    long m_base_mp{10};
    long m_level{1};

    long m_exp{0};
    long m_current_level_starting_exp{0};
    
    bool m_ready_to_level_up{false};
};

struct Player_Info
{
  explicit Player_Info(const string & name, const string & species, const string & classs, const long & icon, const Character_Base_Stats & stats, const Image_Params & sprite, const Image_Params & portrait, const Image_Params & small_portrait, const long & sprite_width) :
                       m_name(name), m_species(species), m_class(classs), m_icon(icon), m_stats(stats), m_sprite_data(sprite.m_data), m_sprite_size(sprite.m_size), m_portrait_data(portrait.m_data), m_portrait_size(portrait.m_size), m_small_portrait_data(small_portrait.m_data), m_small_portrait_size(small_portrait.m_size), m_sprite_width(sprite_width){}
  Player_Info(const Player_Info & obj) = delete;
  Player_Info & operator =(const Player_Info & obj) = delete;

  const string m_name{"NULL"};
  const string m_species{"NULL"};
  const string m_class{"NULL"};
  const long m_icon{0};
  const Character_Base_Stats m_stats{};
  const unsigned char* m_sprite_data{nullptr};
  const long m_sprite_size{1};
  const unsigned char* m_portrait_data{nullptr};
  const long m_portrait_size{1};
  const unsigned char* m_small_portrait_data{nullptr};
  const long m_small_portrait_size{1};
  const long m_sprite_width{1};
};

const Player_Info TWILIGHT_SPARKLE_INFO{"Twilight Sparkle", "Unicorn", "Magic", 19, TWILIGHT_SPARKLE_BASE_STATS, TWILIGHT_SPARKLE_IMAGE, TWILIGHT_SPARKLE_PORTRAIT_IMAGE, TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE, 32};
const Player_Info PINKIE_PIE_INFO{"Pinkie Pie", "Earth Pony", "Singer", 20, PINKIE_PIE_BASE_STATS, PINKIE_PIE_IMAGE, PINKIE_PIE_PORTRAIT_IMAGE, PINKIE_PIE_SMALL_PORTRAIT_IMAGE, 32};
const Player_Info APPLEJACK_INFO{"Applejack", "Earth Pony", "Power", 21, APPLEJACK_BASE_STATS, APPLEJACK_IMAGE, APPLEJACK_PORTRAIT_IMAGE, APPLEJACK_SMALL_PORTRAIT_IMAGE, 32};
const Player_Info RAINBOW_DASH_INFO{"Rainbow Dash", "Pegasus", "Speed", 22, RAINBOW_DASH_BASE_STATS, TWILIGHT_SPARKLE_IMAGE, RAINBOW_DASH_PORTRAIT_IMAGE, RAINBOW_DASH_SMALL_PORTRAIT_IMAGE, 32};
const Player_Info FLUTTERSHY_INFO{"Fluttershy", "Pegasus", "Caller", 23, FLUTTERSHY_BASE_STATS, PINKIE_PIE_IMAGE, FLUTTERSHY_PORTRAIT_IMAGE, FLUTTERSHY_SMALL_PORTRAIT_IMAGE, 32};
const Player_Info RARITY_INFO{"Rarity", "Unicorn", "Healer", 24, RARITY_BASE_STATS, APPLEJACK_IMAGE, RARITY_PORTRAIT_IMAGE, RARITY_SMALL_PORTRAIT_IMAGE, 32};

struct Enemy_Info
{
  explicit Enemy_Info(const string & name, const Enemy_Base_Stats & stats, const Image_Params & sprite, const long & sprite_width, const vector<vector<long>> animation_list) : m_name(name), m_stats(stats), m_sprite_data(sprite.m_data), m_sprite_size(sprite.m_size), m_sprite_width(sprite_width), m_animation_list(animation_list){}
  Enemy_Info(const Enemy_Info & obj) = delete;
  Enemy_Info & operator =(const Enemy_Info & obj) = delete;

  const string m_name{"NULL"};
  const Enemy_Base_Stats m_stats{};
  const unsigned char* m_sprite_data{nullptr};
  const long m_sprite_size{1};
  const long m_sprite_width{1};
  vector<vector<long>> m_animation_list{};
};

const Enemy_Info CHANGELING_INFO{"Changeling", CHANGELING_STATS, CHANGELING_ENEMY_IMAGE, 36, vector<vector<long>>{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}}};

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
    void swap_party_members(const string & name1, const string & name2);
    void give_member_exp(const long & exp){m_stats.give_exp(exp);}
    void level_up(){m_stats.level_up();}
    void equip(Equipment* equip, const long & slot = 0);
    void unequip(World* world, const string & item_type, const long & slot = 0);
    Equipment* get_equipped_weapon() const;
    Equipment* get_equipped_armor() const;
    Equipment* get_equipped_accessory_one() const;
    Equipment* get_equipped_accessory_two() const;
    long get_icon() const{return m_icon;}
    void render_sprite(const long & x, const long & y, const long & animation_frame, const bool & flip) const{DrawTexturePro(m_sprite, Rectangle{static_cast<float>(animation_frame * m_sprite_width), 0, flip == true ? static_cast<float>(-m_sprite_width) : static_cast<float>(m_sprite_width), static_cast<float>(m_sprite.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_sprite_width), static_cast<float>(m_sprite.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    void render_portrait(const long & x, const long & y) const{DrawTexturePro(m_portrait, Rectangle{0, 0, static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_portrait.width), static_cast<float>(m_portrait.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    vector<long> predict_stats(const World* const world, const string & item_name, const string & item_type, const bool & same_item, const long & slot = 0, const long & highlighted_slot = 0, const string & highlighted_equipped_by = "NULL") const;
  private:
    string m_name{"NULL"};
    string m_species{"NULL"};
    string m_class{"NULL"};
    Texture2D m_sprite{};
    Texture2D m_portrait{};
    Texture2D m_small_portrait{};
    Player_Stats m_stats{TWILIGHT_SPARKLE_BASE_STATS};
    long m_icon{0};
    long m_sprite_width{1};
    Equipment* m_equipped_weapon{nullptr};
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
    long count_equipped_weapons() const;
    long count_equipped_armor() const;
    long count_equipped_accessories() const;
    long get_size() const{return m_members.get_list_size();}
    void swap_party_members(const string & name1, const string & name2){m_members.swap(name1, name2);}
    string get_next_member(const string & name) const;
    string get_previous_member(const string & name) const;
    vector<string> get_equipped_weapon_names() const;
    vector<string> get_equipped_armor_names() const;
    vector<string> get_equipped_accessory_names() const;
    void render_member_sprite(const string & character, const long & x, const long & y, const long & animation_frame, const bool & flip) const{m_members[character]->render_sprite(x, y, animation_frame, flip);}
    void render_member_portrait(const string & character, const long & x, const long & y) const{m_members[character]->render_portrait(x, y);}
    vector<string> get_equipped_weapon_descriptions() const;
    vector<string> get_equipped_armor_descriptions() const;
    vector<string> get_equipped_accessory_descriptions() const;
    vector<string> get_equipped_weapon_equipped_bys() const;
    vector<string> get_equipped_armor_equipped_bys() const;
    vector<string> get_equipped_accessory_equipped_bys() const;
    vector<long> get_equipped_weapon_icons() const;
    vector<long> get_equipped_armor_icons() const;
    vector<long> get_equipped_accessory_icons() const;
    vector<long> get_equipped_accessory_slots() const;
    void equip(World* world, const string & character, const string & item_name, const string & item_type, const long & slot, const string & highlighted_equipped_by, const long & highlighted_slot);
    string get_member_equipped_weapon_name(const string & character) const{return m_members[character]->get_equipped_weapon() == nullptr ? "NULL" : m_members[character]->get_equipped_weapon()->get_name();}
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
    void render_cursor() const;
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
    void render_text_center(const string & font_name, string text, const long & y_pos, const long & alpha = 255) const;
    void pause_play_time(){m_play_time.pause();}
    void unpause_play_time(){m_play_time.unpause();}
    void render_progress_bar(const string & color, const long & x, const long & y) const;
    void render_letter(const string & font_name, const long & x, const long & y, const char & id, const long & alpha = 255) const;
    void render_text(const string & font_name, string text, const long & x, const long & y, const long & alpha = 255) const;
    void render_continue_arrow(const long & x, const long & y, const bool & yflip) const{DrawTexturePro(m_continue_arrow_texture, Rectangle{0, 0, static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Rectangle{static_cast<float>(x - m_continue_arrow_texture.width / 2), static_cast<float>(y), static_cast<float>(m_continue_arrow_texture.width), static_cast<float>(m_continue_arrow_texture.height)}, Vector2{static_cast<float>(m_continue_arrow_texture.width / 2), 0}, 180 * yflip, Color{0xFF, 0xFF, 0xFF, 0xFF});}
    void render_panel(const long & x, const long & y, const long & w, const long & h) const;
    void set_cursor_destination(const long & x, const long & y);
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
    long get_number_of_equipped_and_inventory_armor() const;
    long get_number_of_equipped_and_inventory_accessories() const;
    string get_next_party_member(const string & character) const{return m_party.get_next_member(character);}
    string get_previous_party_member(const string & character) const{return m_party.get_previous_member(character);}
    vector<string> get_equipped_and_inventory_weapon_names() const;
    vector<string> get_equipped_and_inventory_armor_names() const;
    vector<string> get_equipped_and_inventory_accessory_names() const;
    bool can_use_equipment(const string & character_name, const string & item_name) const{return m_item_database[item_name]->is_usable_by(character_name);}
    void render_party_member_sprite(const string & character, const long & x, const long & y, const long & animation_frame, const bool & flip = false) const{m_party.render_member_sprite(character, x, y, animation_frame, flip);}
    void render_party_member_portrait(const string & character, const long & x, const long & y) const{m_party.render_member_portrait(character, x, y);}
    vector<string> get_equipped_and_inventory_weapon_descriptions() const;
    vector<string> get_equipped_and_inventory_armor_descriptions() const;
    vector<string> get_equipped_and_inventory_accessory_descriptions() const;
    vector<long> get_equipped_and_inventory_weapon_quantities() const;
    vector<long> get_equipped_and_inventory_armor_quantities() const;
    vector<long> get_equipped_and_inventory_accessory_quantities() const;
    vector<string> get_equipped_and_inventory_weapon_equipped_bys() const;
    vector<string> get_equipped_and_inventory_armor_equipped_bys() const;
    vector<string> get_equipped_and_inventory_accessory_equipped_bys() const;
    vector<long> get_equipped_and_inventory_weapon_icons() const;
    vector<long> get_equipped_and_inventory_armor_icons() const;
    vector<long> get_equipped_and_inventory_accessory_icons() const;
    vector<bool> get_equipped_and_inventory_weapon_usable_bys(const string & character) const;
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
