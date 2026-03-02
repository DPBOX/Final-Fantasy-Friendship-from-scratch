#include "Main.h"
#include "Tilemap.h"
#include "Entity.h"

Tilemap::Tilemap(Music_Player* music_player, const Map_Data & map_data)
{
  m_map_width = map_data.m_map_width;
  m_map_height = map_data.m_map_height;
  m_id = map_data.m_id;
  m_tilemap = map_data.m_tile_map;
  m_collision_map = map_data.m_collision_map;
  m_north_script = map_data.m_north_script;
  m_south_script = map_data.m_south_script;
  m_east_script = map_data.m_east_script;
  m_west_script = map_data.m_west_script;
  m_music = map_data.m_music;
  m_animated_tiles = map_data.m_animated_tiles;
  Image image{LoadImageFromMemory(".png", map_data.m_img_data, map_data.m_img_size)};
  m_tiles = LoadTextureFromImage(image);
  UnloadImage(image);
  music_player->play_global_music(m_music);
}

void Tilemap::add_entities(Tilemap* map, const Map_Data & map_data, const Direction & hero_start_facing_dir, const long & hero_start_tile_x, const long & hero_start_tile_y, const long & hero_start_layer)
{
  Entity* hero{nullptr};
  if(map_data.m_show_hero == true)
  {
    hero = new Hero(map, hero_start_layer, hero_start_tile_x, hero_start_tile_y, hero_start_facing_dir);
    ++mem;
  }
  for(long i{0}; i < static_cast<long>(map_data.m_npc_list.size()); ++i)
  {
    if(map_data.m_npc_list[i].m_start_state == "Stand")
    {
      Entity* npc{new Standing_NPC(map, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Stroll")
    {
      Entity* npc{new Strolling_NPC(map, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Path")
    {
      Entity* npc{new Path_NPC(map, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Treasure Chest")
    {
      Entity* npc{new Treasure_Chest(map, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else
    {
      crash("Error: Invalid NPC type \"" + map_data.m_npc_list[i].m_start_state + "\".");
    }
  }
  if(map_data.m_show_hero == true)
  {
    m_entity_list.push_back(hero);
  }
}

Tilemap::~Tilemap()
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    delete m_entity_list[i];
    m_entity_list[i] = nullptr;
    --mem;
  }
  m_entity_list.clear();
  UnloadTexture(m_tiles);
}

long Tilemap::update_input(Tilemap* map, Input_Wrapper* input)
{
  if(m_animated_tiles.empty() == false)
  {
    ++m_animated_tile_frame_timer;
    if(m_animated_tile_frame_timer == TILE_ANIMATION_SPEED)
    {
      m_animated_tile_frame_timer = 0;
      ++m_animated_tile_frame_index;
    }
    if(m_animated_tile_frame_index == static_cast<long>(m_animated_tiles[0].m_animation_tiles.size()))
    {
      m_animated_tile_frame_index = 0;
    }
  }

  //Update the entities
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_type() != "Hero" || (m_entity_list[i]->get_type() == "Hero" && m_controls_locked == false))
    {
      m_entity_list[i]->update_input(map, input);
    }
  }

  //Do a bubble sort on the entity list by Y position so they can be rendered in the correct order
  for(long i{0}; i < static_cast<long>(m_entity_list.size()) - 1; ++i)
  {
    for(long j{0}; j < static_cast<long>(m_entity_list.size()) - 1; ++j)
    {
      if(m_entity_list[j + 1]->get_position_y() < m_entity_list[j]->get_position_y())
      {
        Entity* temp{m_entity_list[j + 1]};
        m_entity_list[j + 1] = m_entity_list[j];
        m_entity_list[j] = temp;
      }
    }
  }

  if(m_cam_char_to_follow == "NULL")
  {
    m_cam_x = m_manual_cam_x;
    m_cam_y = m_manual_cam_y;
  }
  else
  {
    for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
    {
      if(m_entity_list[i]->get_id() == m_cam_char_to_follow)
      {
        m_cam_x = m_entity_list[i]->get_position_x() - SCREEN_WIDTH / 2;
        m_cam_y = m_entity_list[i]->get_position_y() - SCREEN_HEIGHT / 2;
      }
    }
  }
  long s{m_script_to_run};
  m_script_to_run = -1;
  return s;
}

void Tilemap::render(Tilemap* map) const
{
  long top_left_x = point_to_tile_x(m_cam_x);
  long top_left_y = point_to_tile_y(m_cam_y);
  long bottom_right_x = point_to_tile_x(m_cam_x + SCREEN_WIDTH + MAP_TILE_WIDTH);
  long bottom_right_y = point_to_tile_y(m_cam_y + SCREEN_HEIGHT + m_tiles.height);

  for(long l{0}; l < static_cast<long>(m_tilemap.size()); ++l)
  {
    for(long k{0}; k < static_cast<long>(m_tilemap[l].size()); ++k)
    {
      for(long j{top_left_y}; j <= bottom_right_y; ++j)
      {
        for(long i{top_left_x}; i <= bottom_right_x; ++i)
        {
          DrawTexturePro(m_tiles, Rectangle{static_cast<float>(MAP_TILE_WIDTH * get_tile(i, j, l, k)), 0, static_cast<float>(MAP_TILE_WIDTH), static_cast<float>(m_tiles.height)}, Rectangle{static_cast<float>(i * MAP_TILE_WIDTH - m_cam_x), static_cast<float>(j * m_tiles.height - m_cam_y), static_cast<float>(MAP_TILE_WIDTH), static_cast<float>(m_tiles.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
        }
      }
    }
    for(long m{0}; m < static_cast<long>(m_entity_list.size()); ++m)
    {
      if(m_entity_list[m]->get_layer() == l)
      {
        m_entity_list[m]->render(map);
      }
    }
  }
}

void Tilemap::run_script(const long & index)
{
  m_script_to_run = index;
  if(index != -1)
  {
    lock_controls();
  }
}

void Tilemap::lock_controls()
{
  m_controls_locked = true;
}

void Tilemap::unlock_controls()
{
  m_controls_locked = false;
}

void Tilemap::show_npc(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->set_alpha(ALPHA_MAX);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

void Tilemap::hide_npc(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->set_alpha(0);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

bool Tilemap::is_blocked(const long & x, const long & y, const long & layer, const string & npc_name) const
{
  if(x < 0 || x >= m_map_width || y < 0 || y >= m_map_height)
  {
    return true;
  }
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_name)
    {
      continue;
    }
    if(m_entity_list[i]->tile_occupied(x, y, layer) == true)
    {
      return true;
    }
  }
  if(get_collision(x, y, layer) == true)
  {
    return true;
  }
  return false;
}

bool Tilemap::is_blocked_hero(const long & x, const long & y, const long & layer)
{
  if(x < 0 || x >= m_map_width || y < 0 || y >= m_map_height)
  {
    if(x < 0)
    {
      run_script(m_west_script);
    }
    else if(x >= m_map_width)
    {
      run_script(m_east_script);
    }
    else if(y < 0)
    {
      run_script(m_north_script);
    }
    else if(y >= m_map_height)
    {
      run_script(m_south_script);
    }
    return true;
  }
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == "Hero")
    {
      continue;
    }
    if(m_entity_list[i]->tile_occupied(x, y, layer) == true)
    {
      if(m_entity_list[i]->get_touch_script() != -1)
      {
        run_script(m_entity_list[i]->get_touch_script());
      }
      return true;
    }
  }
  if(get_collision(x, y, layer) == true)
  {
    return true;
  }
  return false;
}

bool Tilemap::is_blocked_point(const long & x, const long & y, const long & layer)
{
  return is_blocked_hero((x < 0 ? x - MAP_TILE_WIDTH : x) / MAP_TILE_WIDTH, (y < 0 ? y - m_tiles.height : y) / m_tiles.height, layer);
}

long Tilemap::get_tile_height() const
{
  return m_tiles.height;
}

void Tilemap::change_entity_alpha(const string & npc_id, const long & alpha)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->set_alpha(alpha);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

long Tilemap::get_npc_interact_script(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      return m_entity_list[i]->get_interact_script();
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

bool Tilemap::check_entity_position(const string & npc_id, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id && m_entity_list[i]->get_tile_x() == x && m_entity_list[i]->get_tile_y() == y)
    {
      return true;
    }
  }
  return false;
}

long Tilemap::get_entity_screen_pos_x(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      return m_entity_list[i]->get_position_x() - m_cam_x;
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

long Tilemap::get_entity_screen_pos_y(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      return m_entity_list[i]->get_position_y() - m_cam_y;
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

void Tilemap::set_npc_path(const string & npc_id, const long & path)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->set_path(path);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

bool Tilemap::npc_path_finished(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      return m_entity_list[i]->path_finished();
    }
  }
  return true;
}

long Tilemap::get_manual_cam_x() const
{
  return m_manual_cam_x;
}

long Tilemap::get_manual_cam_y() const
{
  return m_manual_cam_y;
}

long Tilemap::get_cam_x() const
{
  return m_cam_x;
}

long Tilemap::get_cam_y() const
{
  return m_cam_y;
}

void Tilemap::set_manual_cam_x(const long & x)
{
  if(m_cam_char_to_follow != "NULL")
  {
    crash("Error: Tried to control the camera manually when it wasn't set to be controlled manually.");
  }
  m_manual_cam_x = x;
}

void Tilemap::set_manual_cam_y(const long & y)
{
  if(m_cam_char_to_follow != "NULL")
  {
    crash("Error: Tried to control the camera manually when it wasn't set to be controlled manually.");
  }
  m_manual_cam_y = y;
}

void Tilemap::set_follow_cam(const string & character)
{
  if(character == "NULL")
  {
    for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
    {
      if(m_entity_list[i]->get_id() == m_cam_char_to_follow)
      {
        m_manual_cam_x = m_entity_list[i]->get_position_x() - SCREEN_WIDTH / 2;
        m_manual_cam_y = m_entity_list[i]->get_position_y() - SCREEN_HEIGHT / 2;
      }
    }
  }
  m_cam_char_to_follow = character;
}

void Tilemap::write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to)
{
  m_tilemap[tile_to_change_layer][tile_to_change_sub_layer][tile_to_change_y * m_map_width + tile_to_change_x] = tile_to_change_to;
  m_collision_map[tile_to_change_layer][tile_to_change_y * m_map_width + tile_to_change_x] = new_collision;
}

void Tilemap::set_map_script(const long & entity_index)
{
  run_script(get_npc_interact_script(m_entity_list[entity_index]->get_id()));
}

long Tilemap::find_entity(const long & layer, const long & tile_x, const long & tile_y) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_layer() == layer && m_entity_list[i]->get_tile_x() == tile_x && m_entity_list[i]->get_tile_y() == tile_y)
    {
      return i;
    }
  }
  return -1;
}

void Tilemap::turn_entity(const long & entity_index, const Direction & direction)
{
  if(entity_index >= 0 && entity_index < static_cast<long>(m_entity_list.size()))
  {
    m_entity_list[entity_index]->turn(direction);
  }
}

long Tilemap::get_tile_foot_x(const long & tile_x) const
{
  return tile_x * MAP_TILE_WIDTH + MAP_TILE_WIDTH / 2;
}

long Tilemap::get_tile_foot_y(const long & tile_y) const
{
  return tile_y * m_tiles.height + m_tiles.height - 1;
}

long Tilemap::point_to_tile_x(long x) const
{
  // Clamp the point to the bounds of the map
  if(x < 0)
  {
    x = 0;
  }
  if(x >= m_map_width * MAP_TILE_WIDTH)
  {
    x = m_map_width * MAP_TILE_WIDTH - 1;
  }

  // Map from the bounded point to a tile
  return x / MAP_TILE_WIDTH;
}

long Tilemap::point_to_tile_y(long y) const
{
  // Clamp the point to the bounds of the map
  if(y < 0)
  {
    y = 0;
  }
  if(y >= m_map_height * m_tiles.height)
  {
    y = m_map_height * m_tiles.height - 1;
  }

  // Map from the bounded point to a tile
  return y / m_tiles.height;
}

long Tilemap::get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const
{
  long tile{m_tilemap[layer][sublayer][x + y * m_map_width]};
  if(m_animated_tiles.empty() == false)
  {
    for(long i{0}; i < static_cast<long>(m_animated_tiles.size()); ++i)
    {
      if(tile == m_animated_tiles[i].m_source_tile)
      {
        tile = m_animated_tiles[i].m_animation_tiles[m_animated_tile_frame_index];
      }
    }
  }
  return tile;
}

bool Tilemap::get_collision(const long & x, const long & y, const long & layer) const
{
  return m_collision_map[layer][x + y * m_map_width];
}
