#ifndef TILEMAP_H
#define TILEMAP_H

class Entity;

class Tilemap
{
  public:
    explicit Tilemap(Music_Player* music_player, const Map_Data & map_data);
    void add_entities(Tilemap* map, const Map_Data & map_data, const Direction & hero_start_facing_dir, const long & hero_start_tile_x, const long & hero_start_tile_y, const long & hero_start_layer);
    Tilemap(const Tilemap & obj) = delete;
    Tilemap & operator =(const Tilemap & obj) = delete;
    ~Tilemap();

    long update_input(Tilemap* map, Input_Wrapper* input);
    void render(Tilemap* map) const;

    long get_cam_x() const;
    long get_cam_y() const;
    long get_tile_height() const;
    bool is_blocked(const long & x, const long & y, const long & layer, const string & npc_name) const;
    bool is_blocked_hero(const long & x, const long & y, const long & layer);
    bool is_blocked_point(const long & x, const long & y, const long & layer);
    void set_map_script(const long & entity_index);
    long find_entity(const long & layer, const long & tile_x, const long & tile_y) const;
    void turn_entity(const long & entity_index, const Direction & direction);
    void lock_controls();
    void unlock_controls();
    void show_npc(const string & npc_id);
    void hide_npc(const string & npc_id);
    void run_script(const long & index);
    void change_entity_alpha(const string & npc_id, const long & alpha);
    long get_npc_interact_script(const string & npc_id) const;
    bool check_entity_position(const string & npc_id, const long & x, const long & y) const;
    long get_entity_screen_pos_x(const string & npc_id) const;
    long get_entity_screen_pos_y(const string & npc_id) const;
    void set_npc_path(const string & npc_id, const long & path);
    bool npc_path_finished(const string & npc_id) const;
    long get_manual_cam_x() const;
    long get_manual_cam_y() const;
    void set_manual_cam_x(const long & x);
    void set_manual_cam_y(const long & y);
    void set_follow_cam(const string & character);
    void write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to);
    long get_tile_foot_x(const long & tile_x) const;
    long get_tile_foot_y(const long & tile_y) const;
    long point_to_tile_x(long x) const;
    long point_to_tile_y(long y) const;
  private:
    long get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const;
    bool get_collision(const long & x, const long & y, const long & layer) const;

    long m_map_width{0};
    long m_map_height{0};
    vector<array<vector<long>, 2>> m_tilemap{};
    vector<vector<bool>> m_collision_map{};
    Texture2D m_tiles{};
    long m_cam_x{0};
    long m_cam_y{0};
    string m_id{"NULL"};
    string m_cam_char_to_follow{"Hero"};
    long m_manual_cam_x{0};
    long m_manual_cam_y{0};
    string m_music{"City"};
    long m_script_to_run{-1};
    long m_north_script{0};
    long m_south_script{0};
    long m_east_script{0};
    long m_west_script{0};
    bool m_controls_locked{true};
    vector<Entity*> m_entity_list{};
    vector<Animated_Tile_Data> m_animated_tiles{};
    long m_animated_tile_frame_timer{0};
    long m_animated_tile_frame_index{0};
};

#endif
