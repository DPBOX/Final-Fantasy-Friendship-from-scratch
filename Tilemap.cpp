#include "Main.h"
#include "Tilemap.h"

Map_Handler::~Map_Handler()
{
  delete m_map;
  m_map = nullptr;
  --mem;
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    delete m_entity_list[i];
    m_entity_list[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_trigger_list.size()); ++i)
  {
    delete m_trigger_list[i];
    m_trigger_list[i] = nullptr;
    --mem;
  }
  m_entity_list.clear();
  m_trigger_list.clear();
  if(m_script != nullptr)
  {
    delete m_script;
    m_script = nullptr;
    --mem;
  }
}

void Map_Handler::add_map(World* world, const Map_Data & map_data, Map_Handler* map_handler)
{
  if(m_map != nullptr)
  {
    delete m_map;
    m_map = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    delete m_entity_list[i];
    m_entity_list[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_trigger_list.size()); ++i)
  {
    delete m_trigger_list[i];
    m_trigger_list[i] = nullptr;
    --mem;
  }
  m_entity_list.clear();
  m_trigger_list.clear();
  m_script_list = map_data.m_scripts;
  m_map = new Tilemap(world, map_data);
  ++mem;

  Entity* hero{nullptr};
  if(map_data.m_show_hero == true)
  {
    vector<long> hero_start_animation;
    if(map_data.m_hero_data.m_facing_dir == Direction::Up)
    {
      hero_start_animation = HERO_ANIM_UP;
    }
    else if(map_data.m_hero_data.m_facing_dir == Direction::Down)
    {
      hero_start_animation = HERO_ANIM_DOWN;
    }
    else if(map_data.m_hero_data.m_facing_dir == Direction::Left)
    {
      hero_start_animation = HERO_ANIM_LEFT;
    }
    else
    {
      hero_start_animation = HERO_ANIM_RIGHT;
    }
    hero = new Hero(map_handler, map_data.m_hero_data.m_layer, HERO_WIDTH, map_data.m_hero_data.m_tile_x, map_data.m_hero_data.m_tile_y, map_data.m_hero_data.m_facing_dir, hero_start_animation, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
    ++mem;
  }
  for(long i{0}; i < static_cast<long>(map_data.m_npc_list.size()); ++i)
  {
    if(map_data.m_npc_list[i].m_start_state == "Stand")
    {
      Entity* npc{new Standing_NPC(map_handler, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Stroll")
    {
      Entity* npc{new Strolling_NPC(map_handler, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Path")
    {
      Entity* npc{new Path_NPC(map_handler, map_data.m_npc_list[i])};
      ++mem;
      m_entity_list.push_back(npc);
    }
    else if(map_data.m_npc_list[i].m_start_state == "Treasure Chest")
    {
      Entity* npc{new Treasure_Chest(map_handler, map_data.m_npc_list[i])};
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

  for(long i{0}; i < static_cast<long>(map_data.m_trigger_list.size()); ++i)
  {
    Trigger* trigger{new Trigger(map_data.m_trigger_list[i])};
    ++mem;
    m_trigger_list.push_back(trigger);
  }
}

void Map_Handler::add_script(const Scr & events)
{
  if(m_script == nullptr && events.m_steps.empty() == false)
  {
    m_script = new Script(events);
    ++mem;
    lock_controls();
  }
}

void Map_Handler::update_input(Map_Handler* map_handler, World* world)
{
  if(m_script != nullptr)
  {
    m_script->update_input(map_handler, world);
    if(m_script->finished() == true)
    {
      long next_script{m_script->get_next_script()};
      delete m_script;
      m_script = nullptr;
      --mem;
      unlock_controls();
      if(next_script != -1)
      {
        if(next_script >= 0 && next_script < static_cast<long>(m_script_list.size()))
        {
          add_script(m_script_list[next_script]);
        }
        else
        {
          crash("Error: Script ID " + to_string(next_script) + " doesn't exist in the current map.");
        }
      }
    }
  }

  //Update the entities
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_type != "Hero" || (m_entity_list[i]->m_type == "Hero" && m_controls_locked == false))
    {
      m_entity_list[i]->update_input(map_handler);
    }
  }

  //Do a bubble sort on the entity list by Y position so they can be rendered in the correct order
  for(long i{0}; i < static_cast<long>(m_entity_list.size()) - 1; ++i)
  {
    for(long j{0}; j < static_cast<long>(m_entity_list.size()) - 1; ++j)
    {
      if(m_entity_list[j + 1]->m_y < m_entity_list[j]->m_y)
      {
        Entity* temp{m_entity_list[j + 1]};
        m_entity_list[j + 1] = m_entity_list[j];
        m_entity_list[j] = temp;
      }
    }
  }

  if(m_map->m_cam_char_to_follow == "NULL")
  {
    m_map->m_cam_x = m_map->m_manual_cam_x;
    m_map->m_cam_y = m_map->m_manual_cam_y;
  }
  else
  {
    for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
    {
      if(m_entity_list[i]->m_id == m_map->m_cam_char_to_follow)
      {
        m_map->go_to(m_entity_list[i]->m_x, m_entity_list[i]->m_y);
      }
    }
  }
}

void Map_Handler::render(Map_Handler* map_handler, World* world) const
{
  m_map->render(map_handler);
  if(m_script != nullptr)
  {
    m_script->render(world);
  }
}

void Map_Handler::render_layers_entities(Map_Handler* map_handler, const long & layer) const
{
  for(long m{0}; m < static_cast<long>(m_entity_list.size()); ++m)
  {
    if(m_entity_list[m]->m_layer == layer)
    {
      m_entity_list[m]->render(map_handler);
    }
  }
}

void Map_Handler::lock_controls()
{
  m_controls_locked = true;
}

void Map_Handler::unlock_controls()
{
  m_controls_locked = false;
}

void Map_Handler::show_npc(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      m_entity_list[i]->m_alpha = ALPHA_MAX;
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

void Map_Handler::hide_npc(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      m_entity_list[i]->m_alpha = 0;;
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

bool Map_Handler::is_blocked(const long & x, const long & y, const long & layer) const
{
  if(x < 0 || x >= m_map->m_map_width || y < 0 || y >= m_map->m_map_height || m_map->get_collision(x, y, layer) == true)
  {
    return true;
  }
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->tile_occupied(x, y, layer) == true)
    {
      return true;
    }
  }
  return false;
}

long Map_Handler::get_map_tile_width() const
{
  return m_map->m_tile_width;
}

long Map_Handler::get_map_tile_height() const
{
  return m_map->m_tiles.height;
}

void Map_Handler::change_entity_alpha(const string & npc_id, const long & alpha)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      m_entity_list[i]->m_alpha = alpha;
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

long Map_Handler::get_npc_script(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      if(m_entity_list[i]->m_alpha != 0)
      {
        long speech{m_entity_list[i]->m_scripts[m_entity_list[i]->m_script_index]};
        ++m_entity_list[i]->m_script_index;
        if(m_entity_list[i]->m_script_index == static_cast<long>(m_entity_list[i]->m_scripts.size()))
        {
          if(m_entity_list[i]->m_script_loop == true)
          {
            m_entity_list[i]->m_script_index = 0;
          }
          else
          {
            m_entity_list[i]->m_script_index = m_entity_list[i]->m_scripts.size() - 1;
          }
        }
        return speech;
      }
      else
      {
        return -1;
      }
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

bool Map_Handler::check_entity_position(const string & npc_id, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id && m_entity_list[i]->m_tile_x == x + m_trigger_list[m_map->m_last_trigger]->m_x && m_entity_list[i]->m_tile_y == y + m_trigger_list[m_map->m_last_trigger]->m_y)
    {
      return true;
    }
  }
  return false;
}

long Map_Handler::get_entity_screen_pos_x(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      return m_entity_list[i]->m_x - m_map->m_cam_x;
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

long Map_Handler::get_entity_screen_pos_y(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      return m_entity_list[i]->m_y - m_map->m_cam_y;
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return -1;
}

void Map_Handler::set_npc_path(const string & npc_id, const long & path)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      m_entity_list[i]->set_path(path);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

bool Map_Handler::npc_path_finished(const string & npc_id) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == npc_id)
    {
      return m_entity_list[i]->path_finished();
    }
  }
  return true;
}

void Map_Handler::teleport_entity(const string & entity_name, const long & destination_x, const long & destination_y)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_id == entity_name)
    {
      m_entity_list[i]->m_tile_x = destination_x;
      m_entity_list[i]->m_tile_y = destination_y;
      m_entity_list[i]->m_x = m_entity_list[i]->m_tile_x * m_map->m_tile_width + m_map->m_tile_width;
      m_entity_list[i]->m_y = m_entity_list[i]->m_tile_y * m_map->m_tiles.height + m_map->m_tiles.height;
    }
  }
}

void Map_Handler::deactivate_trigger()
{
  if(m_map->m_last_trigger != -1)
  {
    m_trigger_list[m_map->m_last_trigger]->m_deactivated = true;
  }
}

long Map_Handler::get_manual_cam_x() const
{
  return m_map->m_manual_cam_x;
}

long Map_Handler::get_manual_cam_y() const
{
  return m_map->m_manual_cam_y;
}

long Map_Handler::get_cam_x() const
{
  return m_map->m_cam_x;
}

long Map_Handler::get_cam_y() const
{
  return m_map->m_cam_y;
}

void Map_Handler::set_manual_cam_x(const long & x)
{
  if(m_map->m_cam_char_to_follow != "NULL")
  {
    crash("Error: Tried to control the camera manually when it wasn't set to be controlled manually.");
  }
  m_map->m_manual_cam_x = x;
}

void Map_Handler::set_manual_cam_y(const long & y)
{
  if(m_map->m_cam_char_to_follow != "NULL")
  {
    crash("Error: Tried to control the camera manually when it wasn't set to be controlled manually.");
  }
  m_map->m_manual_cam_y = y;
}

void Map_Handler::set_follow_cam(const string & character)
{
  if(character == "NULL")
  {
    for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
    {
      if(m_entity_list[i]->m_id == m_map->m_cam_char_to_follow)
      {
        m_map->go_to_manual(m_entity_list[i]->m_x, m_entity_list[i]->m_y);
      }
    }
  }
  m_map->m_cam_char_to_follow = character;
}

void Map_Handler::write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to)
{
  m_map->m_tilemap[tile_to_change_layer][tile_to_change_sub_layer][tile_to_change_y * m_map->m_map_width + tile_to_change_x] = tile_to_change_to;
  m_map->m_collision_map[tile_to_change_layer][tile_to_change_y * m_map->m_map_width + tile_to_change_x] = new_collision;
}

void Map_Handler::add_game_state(const string & state)
{
  m_next_state = state;
}

void Map_Handler::pop_state()
{
  m_pop = true;
}

string Map_Handler::get_next_game_state()
{
  string s{m_next_state};
  m_next_state = "NULL";
  return s;
}

bool Map_Handler::get_pop()
{
  bool b = m_pop;
  m_pop = false;
  return b;
}

void Map_Handler::set_map_script(const long & trigger_index, const bool & type)
{
  long script_index{type == true ? get_npc_script(m_entity_list[trigger_index]->m_id) : m_trigger_list[trigger_index]->get_script()};
  if(script_index >= 0 && script_index < static_cast<long>(m_script_list.size()))
  {
    add_script(m_script_list[script_index]);
    m_map->m_last_trigger = trigger_index;
  }
}

long Map_Handler::find_trigger(const long & layer, const long & tile_x, const long & tile_y) const
{
  for(long i{0}; i < static_cast<long>(m_trigger_list.size()); ++i)
  {
    if(m_trigger_list[i]->m_layer == layer && m_trigger_list[i]->m_x == tile_x && m_trigger_list[i]->m_y == tile_y)
    {
      return i;
    }
  }
  return -1;
}

long Map_Handler::find_entity(const long & layer, const long & tile_x, const long & tile_y) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->m_layer == layer && m_entity_list[i]->m_tile_x == tile_x && m_entity_list[i]->m_tile_y == tile_y)
    {
      return i;
    }
  }
  return -1;
}

void Map_Handler::turn_entity(const long & entity_index, const Direction & direction)
{
  if(entity_index >= 0 && entity_index < static_cast<long>(m_entity_list.size()))
  {
    m_entity_list[entity_index]->turn(direction);
  }
}

Map_Handler::Tilemap::Tilemap(World* world, const Map_Data & map_data)
{
  m_map_width = map_data.m_map_width;
  m_map_height = map_data.m_map_height;
  m_tile_width = map_data.m_tile_width;
  m_id = map_data.m_id;
  m_tilemap = map_data.m_tile_map;
  m_collision_map = map_data.m_collision_map;
  m_music = map_data.m_music;
  Image image{LoadImageFromMemory(".png", map_data.m_img_data, map_data.m_img_size)};
  m_tiles = LoadTextureFromImage(image);
  UnloadImage(image);
  world->play_global_music(m_music);
}

Map_Handler::Tilemap::~Tilemap()
{
  UnloadTexture(m_tiles);
}

void Map_Handler::Tilemap::render(Map_Handler* map_handler) const
{
  long top_left_x = point_to_tile_x(m_cam_x, m_cam_y);
  long top_left_y = point_to_tile_y(m_cam_x, m_cam_y);
  long bottom_right_x = point_to_tile_x(m_cam_x + SCREEN_WIDTH + m_tile_width, m_cam_y + SCREEN_HEIGHT + m_tiles.height);
  long bottom_right_y = point_to_tile_y(m_cam_x + SCREEN_WIDTH + m_tile_width, m_cam_y + SCREEN_HEIGHT + m_tiles.height);

  for(long l{0}; l < static_cast<long>(m_tilemap.size()); ++l)
  {
    for(long k{0}; k < static_cast<long>(m_tilemap[l].size()); ++k)
    {
      for(long j{top_left_y}; j < bottom_right_y; ++j)
      {
        for(long i{top_left_x}; i < bottom_right_x; ++i)
        {
          DrawTexturePro(m_tiles, Rectangle{static_cast<float>(m_tile_width * get_tile(i, j, l, k)), 0, static_cast<float>(m_tile_width), static_cast<float>(m_tiles.height)}, Rectangle{static_cast<float>(i * m_tile_width - m_cam_x), static_cast<float>(j * m_tiles.height - m_cam_y), static_cast<float>(m_tile_width), static_cast<float>(m_tiles.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
        }
      }
    }
    map_handler->render_layers_entities(map_handler, l);
  }
}

long Map_Handler::Tilemap::point_to_tile_x(long x, long y) const
{
  // Clamp the point to the bounds of the map
  if(x < 0)
  {
    x = 0;
  }
  if(y < 0)
  {
    y = 0;
  }
  if(x > m_map_width * m_tile_width)
  {
    x = m_map_width * m_tile_width;
  }
  if(y > m_map_height * m_tiles.height)
  {
    y = m_map_height * m_tiles.height;
  }

  // Map from the bounded point to a tile
  return static_cast<long>(floor(x / m_tile_width));
}

long Map_Handler::Tilemap::point_to_tile_y(long x, long y) const
{
  // Clamp the point to the bounds of the map
  if(x < 0)
  {
    x = 0;
  }
  if(y < 0)
  {
    y = 0;
  }
  if(x > m_map_width * m_tile_width)
  {
    x = m_map_width * m_tile_width;
  }
  if(y > m_map_height * m_tiles.height)
  {
    y = m_map_height * m_tiles.height;
  }

  // Map from the bounded point to a tile
  return static_cast<long>(floor(y / m_tiles.height));
}

long Map_Handler::Tilemap::get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const
{
  return m_tilemap[layer][sublayer][x + y * m_map_width];
}

bool Map_Handler::Tilemap::get_collision(const long & x, const long & y, const long & layer) const
{
  return m_collision_map[layer][x + y * m_map_width];
}

void Map_Handler::Tilemap::go_to(const long & x, const long & y)
{
  m_cam_x = x - SCREEN_WIDTH / 2;
  m_cam_y = y - SCREEN_HEIGHT / 2;
}

void Map_Handler::Tilemap::go_to_manual(const long & x, const long & y)
{
  m_manual_cam_x = x - SCREEN_WIDTH / 2;
  m_manual_cam_y = y - SCREEN_HEIGHT / 2;
}

long Map_Handler::Trigger::get_script() const
{
  if(m_deactivated == false)
  {
    return m_script;
  }
  return -1;
}
