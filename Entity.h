#ifndef ENTITY_H
#define ENTITY_H
#include "Animation.h"

class Entity
{
  public:
    explicit Entity(){}
    Entity(const Entity & obj) = delete;
    Entity & operator =(const Entity & obj) = delete;
    virtual ~Entity();

    virtual long tile_occupied(const long & x, const long & y, const long & layer) const;
    virtual void turn(const Direction & direction);

    virtual void set_path(const long & path_index);
    virtual bool path_finished() const;
    virtual string get_id() const;
    virtual string get_type() const;
    virtual void set_alpha(const long & alpha);
    virtual long get_interact_script() const;
    virtual long get_touch_script() const;
    virtual long get_tile_x() const;
    virtual long get_tile_y() const;
    virtual long get_layer() const;
    virtual double get_position_x() const;
    virtual double get_position_y() const;

    virtual void update_input(Tilemap* map, Input_Wrapper* input) = 0;
    virtual void render(const Tilemap* const map) const;
  protected:
    //The width in pixels of the Entity
    long m_width{1};
    //The animation frames
    Texture2D m_frames{};
    //The image's name
    string m_image_name{"NULL"};
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
    //The map script index that runs when the entity is talked to
    long m_interact_script{-1};
    //The map script index that runs when the entity is touched
    long m_touch_script{-1};
};

class Treasure_Chest : public Entity
{
  public:
    explicit Treasure_Chest(Tilemap* map, const NPC_Data & npc_data);
    Treasure_Chest(const Treasure_Chest & obj) = delete;
    Treasure_Chest & operator =(const Treasure_Chest & obj) = delete;
    virtual ~Treasure_Chest(){}
    virtual void update_input(Tilemap* map, Input_Wrapper* input);
    virtual void turn(const Direction & direction);
    virtual void render(const Tilemap* const map) const;
  protected:
    bool m_opened{false};
};

class Character : public Entity
{
  public:
    explicit Character(){}
    Character(const Character & obj) = delete;
    Character & operator =(const Character & obj) = delete;
    virtual ~Character(){}
    virtual void update_input(Tilemap* map, Input_Wrapper* input) = 0;
    virtual void turn(const Direction & direction);
  protected:
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

class Hero : public Character
{
  public:
    explicit Hero(Tilemap* map, const long & layer, const long & tile_x, const long & tile_y, const Direction & facing_dir);
    Hero(const Hero & obj) = delete;
    Hero & operator =(const Hero & obj) = delete;
    virtual ~Hero(){}
    virtual void update_input(Tilemap* map, Input_Wrapper* input);
  protected:
    void wait_update_continuous(Tilemap* map, Input_Wrapper* input);
};

class NPC : public Character
{
  public:
    explicit NPC(){}
    NPC(const NPC & obj) = delete;
    NPC & operator =(const NPC & obj) = delete;
    virtual ~NPC();

    virtual void update_input(Tilemap* map, Input_Wrapper* input);
    virtual void render(const Tilemap* const map) const;
  protected:
    virtual void stand_update(Tilemap* map) = 0;
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

class Standing_NPC : public NPC
{
  public:
    explicit Standing_NPC(Tilemap* map, const NPC_Data & npc_data);
    Standing_NPC(const Standing_NPC & obj) = delete;
    Standing_NPC & operator =(const Standing_NPC & obj) = delete;
    virtual ~Standing_NPC(){}
  protected:
    virtual void stand_update(Tilemap* map);
};

class Strolling_NPC : public NPC
{
  public:
    explicit Strolling_NPC(Tilemap* map, const NPC_Data & npc_data);
    Strolling_NPC(const Strolling_NPC & obj) = delete;
    Strolling_NPC & operator =(const Strolling_NPC & obj) = delete;
    virtual ~Strolling_NPC(){}
  protected:
    virtual void stand_update(Tilemap* map);
};

class Path_NPC : public NPC
{
  public:
    explicit Path_NPC(Tilemap* map, const NPC_Data & npc_data);
    Path_NPC(const Path_NPC & obj) = delete;
    Path_NPC & operator =(const Path_NPC & obj) = delete;
    virtual ~Path_NPC(){}

    virtual void set_path(const long & path_index);
    virtual bool path_finished() const;
  protected:
    virtual void stand_update(Tilemap* map);
    void set_next_path(Tilemap* map);
    //The paths the NPC can follow
    vector<vector<Direction>> m_paths{};
    //The path index the NPC is following
    long m_path{-1};
    //Where in the path the NPC is
    long m_path_index{-1};
};

#endif
