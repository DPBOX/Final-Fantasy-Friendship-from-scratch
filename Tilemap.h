#ifndef TILEMAP_H
#define TILEMAP_H

#include "Game_State.h"

class Map_Handler
{
  public:
    explicit Map_Handler(){}
    Map_Handler(const Map_Handler & obj) = delete;
    Map_Handler & operator =(const Map_Handler & obj) = delete;
    ~Map_Handler();

    void add_map(World* world, const Map_Data & map_data, Map_Handler* map_handler);
    void add_script(const Scr & events);
    void update_input(Map_Handler* map_handler, World* world);
    void render(Map_Handler* map_handler, World* world) const;
    
    string get_next_game_state();
    bool get_pop();
    
  private:
    class Trigger
    {
      private:
        friend class Map_Handler;
        explicit Trigger(const Trigger_Data & trigger_data) : m_id(trigger_data.m_id), m_layer(trigger_data.m_l), m_x(trigger_data.m_x), m_y(trigger_data.m_y), m_script(trigger_data.m_script){}
        Trigger(const Trigger & obj) = delete;
        Trigger & operator =(const Trigger & obj) = delete;
        ~Trigger(){}

        long get_script() const;

        long m_id{0};
        long m_layer{0};
        long m_x{0};
        long m_y{0};
        long m_script{-1};
        bool m_deactivated{false};
    };

    class Tilemap
    {
      private:
        friend class Map_Handler;
        explicit Tilemap(World* world, const Map_Data & map_data);
        Tilemap(const Tilemap & obj) = delete;
        Tilemap & operator =(const Tilemap & obj) = delete;
        ~Tilemap();

        void render(Map_Handler* map_handler) const;

        long point_to_tile_x(long x, long y) const;
        long point_to_tile_y(long x, long y) const;
        long get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const;
        bool get_collision(const long & x, const long & y, const long & layer) const;
        void go_to(const long & x, const long & y);
        void go_to_manual(const long & x, const long & y);

        long m_map_width{0};
        long m_map_height{0};
        long m_tile_width{16};
        vector<array<vector<long>, 2>> m_tilemap{};
        vector<vector<bool>> m_collision_map{};
        Texture2D m_tiles{};
        long m_cam_x{0};
        long m_cam_y{0};
        long m_last_trigger{-1};
        string m_id{"NULL"};
        string m_cam_char_to_follow{"Hero"};
        long m_manual_cam_x{0};
        long m_manual_cam_y{0};
        string m_music{"City"};
    };

    class Script
    {
      private:
        friend class Map_Handler;
        explicit Script(const Scr & events) : m_events(events){}
        Script(const Script & obj) = delete;
        Script & operator =(const Script & obj) = delete;
        ~Script();

        void update(){}
        void update_input(Map_Handler* map_handler, World* world);
        void render(World* world) const;
        bool finished() const;
        long get_next_script() const;

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
          explicit Caption_Data(const string & font, const string & id, const string & text, const long & y_pos, const long & alpha = 0);
          Caption_Data(const Caption_Data & obj) = delete;
          Caption_Data & operator =(const Caption_Data & obj) = delete;
          ~Caption_Data(){}
          string m_id{"NULL"};
          string m_text{"NULL"};
          long m_y_pos{0};
          long m_alpha{0};
          string m_font{0};
        };

        Scr m_events{};
        long m_outer_index{0};
        long m_inner_index{0};
        long m_inner_index2{0};
        bool m_delete{false};
        long m_choice_index{-1};
        vector<Tween_Data> m_tween_list{};
        vector<Screen_Data*> m_screen_list{};
        vector<Caption_Data*> m_caption_list{};
        Textbox* m_textbox{nullptr};
        long m_new_script{-1};
        vector<string> m_choices{};
        vector<long> m_choice_scripts{};
    };

    class Entity
    {
      protected:
        friend class Map_Handler;
        explicit Entity(){}
        Entity(const Entity & obj) = delete;
        Entity & operator =(const Entity & obj) = delete;
        virtual ~Entity();

        virtual long tile_occupied(const long & x, const long & y, const long & layer) const;
        virtual void turn(const Direction & direction);

        virtual void set_path(const long & path_index);
        virtual bool path_finished() const;

        virtual void update_input(Map_Handler* map_handler) = 0;
        virtual void render(Map_Handler* map_handler) const;

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
        //The animation it's currently playing
        Animation m_animation{vector<long>{}, 0, false, 0};
        //The map layer it's on.
        long m_layer{0};
        //A list of the Entity's animations
        vector<vector<long>> m_animation_list{};
        //The entity's type
        string m_type{"Entity"};
        //The entity's ID
        string m_id{"NULL"};
        //The entity's translucency
        long m_alpha{ALPHA_MAX};
        //The IDs of the scripts in its map it can run
        vector<long> m_scripts{};
        //After going through all scripts in m_scripts, repeat the last script or go back to the first one?
        bool m_script_loop{false};
        //Index into m_scripts
        long m_script_index{0};
    };

    class Treasure_Chest : protected Entity
    {
      protected:
        friend class Map_Handler;
        explicit Treasure_Chest(Map_Handler* map_handler, const NPC_Data & npc_data);
        Treasure_Chest(const Treasure_Chest & obj) = delete;
        Treasure_Chest & operator =(const Treasure_Chest & obj) = delete;
        virtual ~Treasure_Chest(){}
        virtual void update_input(Map_Handler* map_handler);
        virtual void render(Map_Handler* map_handler) const;
        virtual void turn(const Direction & direction);

        bool m_opened{false};
    };

    class Character : protected Entity
    {
      protected:
        friend class Map_Handler;
        explicit Character(){}
        Character(const Character & obj) = delete;
        Character & operator =(const Character & obj) = delete;
        virtual ~Character(){}
        virtual void update_input(Map_Handler* map_handler) = 0;
        virtual void turn(const Direction & direction);

        //Its velocity
        double m_vx{0};
        double m_vy{0};
        //The position it head towards when it moves
        long m_end_x{0};
        long m_end_y{0};
        //Used as a timer for various purposes such as keeping track of how long a direction key has been being held to determine whether the player should turn or move and when an NPC should move
        long m_frame_count{0};
        //Which direction it's facing
        Direction m_facing_dir{Direction::Down};
        //Its raw velocity without X and Y components
        double m_move_speed{1};
    };

    class Hero : protected Character
    {
      protected:
        friend class Map_Handler;
        explicit Hero(Map_Handler* map_handler, const long & layer, const long & width, const long & tile_x, const long & tile_y, const Direction & facing_dir, const vector<long> & animation, const long & start_frame, const bool & loop, const long & speed);
        Hero(const Hero & obj) = delete;
        Hero & operator =(const Hero & obj) = delete;
        virtual ~Hero(){}
        virtual void update_input(Map_Handler* map_handler);
      private:
        void wait_update_tiled(Map_Handler* map_handler);
        void wait_enter();
        void move_exit(Map_Handler* map_handler);
    };

    class NPC : protected Character
    {
      protected:
        friend class Map_Handler;
        explicit NPC(){}
        NPC(const NPC & obj) = delete;
        NPC & operator =(const NPC & obj) = delete;
        virtual ~NPC();

        virtual void update_input(Map_Handler* map_handler);
        virtual void render(Map_Handler* map_handler) const;

        virtual void enter();
        virtual void stand_update(Map_Handler* map_handler) = 0;
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
    };

    class Standing_NPC : protected NPC
    {
      protected:
        friend class Map_Handler;
        explicit Standing_NPC(Map_Handler* map_handler, const NPC_Data & npc_data);
        Standing_NPC(const Standing_NPC & obj) = delete;
        Standing_NPC & operator =(const Standing_NPC & obj) = delete;
        virtual ~Standing_NPC(){}

        virtual void stand_update(Map_Handler* map_handler);
    };

    class Strolling_NPC : protected NPC
    {
      protected:
        friend class Map_Handler;
        explicit Strolling_NPC(Map_Handler* map_handler, const NPC_Data & npc_data);
        Strolling_NPC(const Strolling_NPC & obj) = delete;
        Strolling_NPC & operator =(const Strolling_NPC & obj) = delete;
        virtual ~Strolling_NPC(){}

        virtual void stand_update(Map_Handler* map_handler);
    };

    class Path_NPC : protected NPC
    {
      protected:
        friend class Map_Handler;
        explicit Path_NPC(Map_Handler* map_handler, const NPC_Data & npc_data);
        Path_NPC(const Path_NPC & obj) = delete;
        Path_NPC & operator =(const Path_NPC & obj) = delete;
        virtual ~Path_NPC(){}
    
        virtual void set_path(const long & path_index);
        virtual bool path_finished() const;
    
        virtual void stand_update(Map_Handler* map_handler);
        void set_next_path(Map_Handler* map_handler);
        //The paths the NPC can follow
        vector<vector<Direction>> m_paths{};
        //The path index the NPC is following
        long m_path{-1};
        //Where in the path the NPC is
        long m_path_index{-1};
    };

    friend class Trigger;
    friend class Tilemap;
    friend class Script;
    friend class Entity;
    friend class Character;
    friend class Hero;
    friend class NPC;
    friend class Treasure_Chest;
    friend class Standing_NPC;
    friend class Strolling_NPC;
    friend class Path_NPC;

    Tilemap* m_map{nullptr};
    Script* m_script{nullptr};
    bool m_controls_locked{false};
    bool m_pop{false};
    string m_next_state{"NULL"};
    vector<Trigger*> m_trigger_list{};
    vector<Entity*> m_entity_list{};
    vector<Scr> m_script_list{};
    
    void render_layers_entities(Map_Handler* map_handler, const long & layer) const;
    bool is_blocked(const long & x, const long & y, const long & layer) const;
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
    long get_npc_script(const string & npc_id);
    void change_entity_alpha(const string & npc_id, const long & alpha);
    void deactivate_trigger();
    long get_manual_cam_x() const;
    long get_manual_cam_y() const;
    long get_cam_x() const;
    long get_cam_y() const;
    void set_follow_cam(const string & character);
    void set_manual_cam_x(const long & x);
    void set_manual_cam_y(const long & y);
    void write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to);
    void add_game_state(const string & state);
    void pop_state();
    void set_map_script(const long & trigger_index, const bool & type);
    long find_trigger(const long & layer, const long & tile_x, const long & tile_y) const;
    long find_entity(const long & layer, const long & tile_x, const long & tile_y) const;
    void turn_entity(const long & entity_index, const Direction & direction);
};

#endif
