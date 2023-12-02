#ifndef TILEMAP_H
#define TILEMAP_H

#include "World.h"
#include "Consts/Script_Structs.h"
#include "Game_State.h"

class Tilemap;
class Map_Handler;

class Entity
{
  public:
    explicit Entity(){}
    Entity(const Entity & obj) = delete;
    Entity & operator =(const Entity & obj) = delete;
    virtual ~Entity();

    virtual void change_alpha(const long & alpha);
    virtual long get_x_pos() const;
    virtual long get_y_pos() const;
    virtual long get_tile_x() const;
    virtual long get_tile_y() const;
    virtual long get_layer() const;
    virtual long tile_occupied(const long & x, const long & y, const long & layer) const;
    virtual string get_type() const;
    virtual string get_id() const;
    virtual void show();
    virtual void hide();
    virtual string get_speech();

    virtual void set_path(const long & path_index);
    virtual bool path_finished() const;
    virtual void set_tiles(Tilemap* map, const long & x, const long & y);

    virtual void update(){}
    virtual void update_input(Map_Handler* map_handler, Tilemap* map);
    virtual void render(Tilemap* map) const;
  protected:
    //The width in pixels of the Entity
    long m_width{1};
    //The animation frames
    Texture2D m_frames{};
    //The tile it's currently standing on
    long m_tile_x{0};
    long m_tile_y{0};
    //Its position
    double m_x{0};
    double m_y{0};
    //Its velocity
    double m_vx{0};
    double m_vy{0};
    //The position it head towards when it moves
    long m_end_x{0};
    long m_end_y{0};
    //The animation it's currently playing
    Animation m_animation{vector<long>{}, 0, false, 0};
    //Used as a timer for various purposes such as keeping track of how long a direction key has been being held to determine whether the player should turn or move and when an NPC should move
    long m_frame_count{0};
    //The map layer it's on.
    long m_layer{0};
    //Which direction it's facing
    Direction m_facing_dir{Direction::Down};
    //Its raw velocity without X and Y components
    double m_move_speed{1};
    //A list of the Entity's animations
    vector<vector<long>> m_animation_list{};
    //The entity's type
    string m_type{"Entity"};
    //The entity's ID
    string m_id{"NULL"};
    //The entity's translucency
    long m_alpha{ALPHA_MAX};
};

class Hero : public Entity
{
  public:
    explicit Hero(Map_Handler* map_handler, Tilemap* map, const long & layer, const long & width, const long & tile_x, const long & tile_y, const Direction & facing_dir, const vector<long> & animation, const long & start_frame, const bool & loop, const long & speed);
    Hero(const Hero & obj) = delete;
    Hero & operator =(const Hero & obj) = delete;
    virtual ~Hero(){}

    virtual void update_input(Map_Handler* map_handler, Tilemap* map);
  private:
    void wait_update(Map_Handler* map_handler, Tilemap* map);
    void wait_update_tiled(Map_Handler* map_handler, Tilemap* map);
    void wait_enter();
    void move_exit(Map_Handler* map_handler, Tilemap* map);
};

class NPC : public Entity
{
  public:
    explicit NPC(Map_Handler* map_handler, Tilemap* map, const NPC_Data & npc_data);
    NPC(const NPC & obj) = delete;
    NPC & operator =(const NPC & obj) = delete;
    virtual ~NPC();

    virtual void set_path(const long & path_index);
    virtual string get_speech();
    virtual bool path_finished() const;

    virtual void update_input(Map_Handler* map_handler, Tilemap* map);
    virtual void enter(Map_Handler* map_handler, Tilemap* map);
    virtual void exit(Map_Handler* map_handler, Tilemap* map);
    virtual void stand_enter(){}
    virtual void plan_stroll_enter(){}
    virtual void plan_stroll_update(Tilemap* map);
    virtual void stand_update(){}
    virtual void move_update(){}
    virtual void follow_path_enter(){}
    virtual void follow_path_exit(){}
    virtual void follow_path_update(Tilemap* map);

    virtual void render(Tilemap* map) const;
  private:
    //The image that's sometimes shown above the NPC's head
    Texture2D m_effect_img{};
    //Shows m_effect_img above the NPC's head if this is true
    bool m_show_effect{false};
    //The width of one frame of the effect
    long m_effect_width{1};
    //The position of the effect compared to the entity's position
    long m_effect_offset_x{0};
    long m_effect_offset_y{0};
    //The effect's animation
    Animation m_effect_animation{vector<long>{}, 0, false, 0};
    //What the NPC can say
    vector<string> m_speech{};
    //What speech line is being processed
    long m_speech_index{0};
    //The paths the NPC can follow
    vector<vector<Direction>> m_paths{};
    //The path index the NPC is following
    long m_path{-1};
    //Where in the path the NPC is
    long m_path_index{-1};
    //The state the NPC is in
    string m_state{"NULL"};
};

class Trigger
{
  public:
    explicit Trigger(const Trigger_Data & trigger_data) : m_id(trigger_data.m_id), m_layer(trigger_data.m_l), m_x(trigger_data.m_x), m_y(trigger_data.m_y), m_enter_script(trigger_data.m_enter_script), m_use_script(trigger_data.m_use_script), m_orientation(trigger_data.m_orientation), m_length(trigger_data.m_length), m_next_tile(trigger_data.m_next_tile), m_sublayer_to_write(trigger_data.m_sublayer_to_write), m_tile_to_write(trigger_data.m_tile_to_write), m_new_collision(trigger_data.m_new_collision){}
    Trigger(const Trigger & obj) = delete;
    Trigger & operator =(const Trigger & obj) = delete;
    ~Trigger(){}

    long get_id() const;
    long get_x_pos() const;
    long get_y_pos() const;
    bool in_trigger_x(const long & target_tile_x) const;
    bool in_trigger_y(const long & target_tile_y) const;
    long get_layer() const;
    long get_enter_script() const;
    long get_use_script() const;
    void deactivate(Tilemap* map, const string & trigger_to_deactivate = "NULL");

  protected:
    long m_id{0};
    long m_layer{0};
    long m_x{0};
    long m_y{0};
    long m_enter_script{-1};
    long m_use_script{-1};
    bool m_deactivated_enter{false};
    bool m_deactivated_use{false};
    bool m_orientation{0};
    long m_length{1};
    bool m_next_tile{false};
    bool m_sublayer_to_write{0};
    long m_tile_to_write{-1};
    bool m_new_collision{0};
};

class Tilemap
{
  public:
    explicit Tilemap(const Map_Data & map_data);
    void set_entities(const vector<Entity*> & entity_list);
    void set_triggers(const vector<Trigger*> & trigger_list);
    Tilemap(const Tilemap & obj) = delete;
    Tilemap & operator =(const Tilemap & obj) = delete;
    ~Tilemap();

    void update();
    void update_input(Map_Handler* map_handler, Tilemap* map, const bool & controls_locked);
    void render(Tilemap* map) const;

    void change_entity_alpha(const string & npc_id, const long & alpha);
    string get_npc_speech(const string & npc_id);
    bool check_entity_position(const string & npc_id, const long & x, const long & y) const;
    long get_entity_screen_pos_x(const string & npc_id) const;
    long get_entity_screen_pos_y(const string & npc_id) const;
    void set_npc_path(const string & npc_id, const long & path);
    bool npc_path_finished(const string & npc_id) const;
    long get_cam_x() const;
    long get_cam_y() const;
    long get_manual_cam_x() const;
    long get_manual_cam_y() const;
    void teleport_entity(Tilemap* map, const string & entity_name, const long & destination_x, const long & destination_y);
    bool is_blocked(const long & x, const long & y, const long & layer) const;
    long get_tile_width() const;
    long get_tile_height() const;
    void show_npc(const string & npc_id);
    void hide_npc(const string & npc_id);
    void set_script(Map_Handler* map_handler, const string & script, const long & trigger_index);
    Scr get_script(const long & script) const;
    void deactivate_trigger(Tilemap* map, const string & trigger_to_deactivate = "NULL");
    void write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to);
    void set_follow_cam(const string & character);
    void set_manual_cam_x(const long & x);
    void set_manual_cam_y(const long & y);
    long find_trigger(const long & layer, const long & tile_x, const long & tile_y) const;
  private:
    long point_to_tile_x(long x, long y) const;
    long point_to_tile_y(long x, long y) const;
    long get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const;
    void go_to(const long & x, const long & y);
    void go_to_manual(const long & x, const long & y);
    void update_camera();

    long m_map_width{0};
    long m_map_height{0};
    long m_tile_width{16};
    vector<vector<vector<long>>> m_tilemap{};
    Texture2D m_tiles{};
    long m_cam_x{0};
    long m_cam_y{0};
    vector<Trigger*> m_trigger_list{};
    vector<Entity*> m_entity_list{};
    vector<Scr> m_script_list{};
    Trigger* m_last_trigger{nullptr};
    string m_id{"NULL"};
    string m_cam_char_to_follow{"Hero"};
    long m_manual_cam_x{0};
    long m_manual_cam_y{0};
    Music_Params m_music{};
};

class Script
{
  public:
    explicit Script(const Scr & events) : m_events(events){}
    Script(const Script & obj) = delete;
    Script & operator =(const Script & obj) = delete;
    ~Script();

    void update(){}
    void update_input(Map_Handler* map_handler, Cursor* cursor, World* world, const vector<Fnt*> & fonts);
    void render(const vector<Fnt*> & fonts) const;
    bool finished() const;
    long get_next_script() const;

  private:
    struct Tween_Data
    {
      explicit Tween_Data(const string & function, const string & target, const double & velocity, const double & start, const double & end) : m_function(function), m_target(target), m_velocity(velocity), m_position(start), m_start(start), m_end(end){}
      string m_function{"NULL"};
      string m_target{"NULL"};
      double m_velocity{0};
      double m_position{0};
      double m_start{0};
      double m_end{0};
      bool m_done{false};
      ~Tween_Data(){}
    };
    struct Sound_Data
    {
      explicit Sound_Data(const Sound_Params & params);
      Sound_Data(const Sound_Data & obj) = delete;
      Sound_Data & operator =(const Sound_Data & obj) = delete;
      ~Sound_Data();
      string m_id{"NULL"};
      Sound m_sound{};
      double m_volume{1};
      double m_target_volume{1};
      long m_size{0};
      const unsigned char* m_data{nullptr};
    };
    struct Screen_Data
    {
      explicit Screen_Data(const string & id, const long & alpha = 255, const long & red = 0, const long & green = 0, const long & blue = 0) : m_id(id), m_alpha(alpha), m_red(red), m_green(green), m_blue(blue){}
      string m_id{"NULL"};
      long m_alpha{255};
      long m_red{0};
      long m_green{0};
      long m_blue{0};
      ~Screen_Data(){}
    };
    struct Caption_Data
    {
      explicit Caption_Data(const long & font, const string & id, const string & text, const long & y_pos, const long & alpha = 0);
      Caption_Data(const Caption_Data & obj) = delete;
      Caption_Data & operator =(const Caption_Data & obj) = delete;
      ~Caption_Data(){}
      string m_id{"NULL"};
      string m_text{"NULL"};
      long m_y_pos{0};
      long m_alpha{0};
      long m_font{0};
    };
    Scr m_events{};
    long m_outer_index{0};
    long m_inner_index{0};
    long m_inner_index2{0};
    bool m_delete{false};
    long m_choice_index{-1};
    vector<Tween_Data> m_tween_list{};
    vector<Screen_Data*> m_screen_list{};
    vector<Sound_Data*> m_sound_list{};
    vector<Caption_Data*> m_caption_list{};
    Textbox* m_textbox{nullptr};
    long m_new_script{-1};
    vector<string> m_choices{};
    vector<long> m_choice_scripts{};
};

class Map_Handler
{
  public:
    explicit Map_Handler(){}
    Map_Handler(const Map_Handler & obj) = delete;
    Map_Handler & operator =(const Map_Handler & obj) = delete;
    ~Map_Handler();

    void add_map(const Map_Data & map_dat, Map_Handler* map_handler);
    void add_script(const Scr & events);
    void show_npc(const string & npc_id);
    void hide_npc(const string & npc_id);
    void lock_controls();
    void unlock_controls();
    void set_npc_path(const string & npc_id, const long & path);
    bool npc_path_finished(const string & npc_id) const;
    bool check_entity_position(const string & npc_id, const long & x, const long & y) const;
    long get_entity_screen_pos_x(const string & npc_id) const;
    long get_entity_screen_pos_y(const string & npc_id) const;
    long get_map_tile_width() const;
    long get_map_tile_height() const;
    void teleport_entity(const string & entity_name, const long & destination_x, const long & destination_y);
    string get_npc_speech(const string & npc_id);
    void change_entity_alpha(const string & npc_id, const long & alpha);
    void deactivate_trigger(const string & trigger_to_deactivate = "NULL");
    long get_manual_cam_x() const;
    long get_manual_cam_y() const;
    void set_follow_cam(const string & character);
    void set_manual_cam_x(const long & x);
    void set_manual_cam_y(const long & y);
    void write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to);
    void add_game_state(const string & state);
    void pop_state();
    string get_next_game_state();
    bool get_pop();

    void update();
    void update_input(Map_Handler* map_handler, Cursor* cursor, World* world, const vector<Fnt*> & fonts);
    void render(const vector<Fnt*> & fonts) const;
  private:
    Tilemap* m_map{nullptr};
    Script* m_script{nullptr};
    bool m_controls_locked{false};
    bool m_pop{false};
    string m_next_state{"NULL"};
};

#endif