#include "Main.h"
#include "Tilemap.h"

Map_Handler::~Map_Handler()
{
  delete m_map;
  m_map = nullptr;
  --mem;
  if(m_script != nullptr)
  {
    delete m_script;
    m_script = nullptr;
    --mem;
  }
}

void Map_Handler::add_map(const Map_Data & map_data, Map_Handler* map_handler)
{
  if(m_map != nullptr)
  {
    delete m_map;
    m_map = nullptr;
    --mem;
  }
  m_map = new Tilemap(map_data);
  ++mem;
  vector<Entity*> entity_list{};
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
    hero = new Hero(map_handler, m_map, map_data.m_hero_data.m_layer, HERO_WIDTH, map_data.m_hero_data.m_tile_x, map_data.m_hero_data.m_tile_y, map_data.m_hero_data.m_facing_dir, hero_start_animation, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
    ++mem;
  }
  for(long i{0}; i < static_cast<long>(map_data.m_npc_list.size()); ++i)
  {
    Entity* npc{new NPC(map_handler, m_map, map_data.m_npc_list[i])};
    ++mem;
    entity_list.push_back(npc);
  }
  if(map_data.m_show_hero == true)
  {
    entity_list.push_back(hero);
  }
  m_map->set_entities(entity_list);
  
  vector<Trigger*> trigger_list;
  for(long i{0}; i < static_cast<long>(map_data.m_trigger_list.size()); ++i)
  {
    Trigger* trigger{new Trigger(map_data.m_trigger_list[i])};
    ++mem;
    trigger_list.push_back(trigger);
  }
  m_map->set_triggers(trigger_list);
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
  m_map->show_npc(npc_id);
}

void Map_Handler::hide_npc(const string & npc_id)
{
  m_map->hide_npc(npc_id);
}

long Map_Handler::get_map_tile_width() const
{
  return m_map->get_tile_width();
}

long Map_Handler::get_map_tile_height() const
{
  return m_map->get_tile_height();
}

void Map_Handler::change_entity_alpha(const string & npc_id, const long & alpha)
{
  m_map->change_entity_alpha(npc_id, alpha);
}

string Map_Handler::get_npc_speech(const string & npc_id)
{
  return m_map->get_npc_speech(npc_id);
}

bool Map_Handler::check_entity_position(const string & npc_id, const long & x, const long & y) const
{
  return m_map->check_entity_position(npc_id, x, y);
}

long Map_Handler::get_entity_screen_pos_x(const string & npc_id) const
{
  return m_map->get_entity_screen_pos_x(npc_id);
}

long Map_Handler::get_entity_screen_pos_y(const string & npc_id) const
{
  return m_map->get_entity_screen_pos_y(npc_id);
}

void Map_Handler::set_npc_path(const string & npc_id, const long & path)
{
  m_map->set_npc_path(npc_id, path);
}

bool Map_Handler::npc_path_finished(const string & npc_id) const
{
  return m_map->npc_path_finished(npc_id);
}

void Map_Handler::teleport_entity(const string & entity_name, const long & destination_x, const long & destination_y)
{
  m_map->teleport_entity(m_map, entity_name, destination_x, destination_y);
}

void Map_Handler::deactivate_trigger(const string & trigger_to_deactivate)
{
  m_map->deactivate_trigger(m_map, trigger_to_deactivate);
}

long Map_Handler::get_manual_cam_x() const
{
  return m_map->get_manual_cam_x();
}

long Map_Handler::get_manual_cam_y() const
{
  return m_map->get_manual_cam_y();
}

void Map_Handler::set_manual_cam_x(const long & x)
{
  m_map->set_manual_cam_x(x);
}

void Map_Handler::set_manual_cam_y(const long & y)
{
  m_map->set_manual_cam_y(y);
}

void Map_Handler::set_follow_cam(const string & character)
{
  m_map->set_follow_cam(character);
}

void Map_Handler::write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to)
{
  m_map->write_tile(tile_to_change_layer, tile_to_change_sub_layer, new_collision, tile_to_change_x, tile_to_change_y, tile_to_change_to);
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

void Map_Handler::update()
{
  m_map->update();
}

void Map_Handler::update_input(Map_Handler* map_handler, Cursor* cursor, World* world, const vector<Fnt*> & fonts)
{
  if(m_script != nullptr)
  {
    m_script->update_input(map_handler, cursor, world, fonts);
    if(m_script->finished() == true)
    {
      long next_script{m_script->get_next_script()};
      delete m_script;
      m_script = nullptr;
      --mem;
      unlock_controls();
      if(next_script != -1)
      {
        add_script(m_map->get_script(next_script));
      }
    }
  }
  else
  {
    cursor->finish();
  }
  m_map->update_input(map_handler, m_map, m_controls_locked);
}

void Map_Handler::render(const vector<Fnt*> & fonts) const
{
  m_map->render(m_map);
  if(m_script != nullptr)
  {
    m_script->render(fonts);
  }
}

Tilemap::Tilemap(const Map_Data & map_data)
{
  m_map_width = map_data.m_map_width;
  m_map_height = map_data.m_map_height;
  m_tile_width = map_data.m_tile_width;
  m_id = map_data.m_id;
  m_tilemap = map_data.m_tile_map;
  m_script_list = map_data.m_scripts;
  Image image{LoadImageFromMemory(".png", map_data.m_img_data, map_data.m_img_size)};
  m_tiles = LoadTextureFromImage(image);
  UnloadImage(image);
  m_music = map_data.m_music;
  music_op(Music_Command_Params{Music_Command::Add, Add_Music_Params{m_music}});
  music_op(Music_Command_Params{Music_Command::Play, Play_Pause_Music_Params{m_music.m_name}});
}

Tilemap::~Tilemap()
{
  UnloadTexture(m_tiles);
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
  music_op(Music_Command_Params{Music_Command::Remove_All});
}

void Tilemap::set_entities(const vector<Entity*> & entity_list)
{
  m_entity_list = entity_list;
}

void Tilemap::set_triggers(const vector<Trigger*> & trigger_list)
{
  m_trigger_list = trigger_list;
}

void Tilemap::update()
{
  //Update the entities
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    m_entity_list[i]->update();
  }
}

void Tilemap::update_input(Map_Handler* map_handler, Tilemap* map, const bool & controls_locked)
{
  //Update the entities
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_type() != "Hero" || (m_entity_list[i]->get_type() == "Hero" && controls_locked == false))
    m_entity_list[i]->update_input(map_handler, map);
  }

  //Do a bubble sort on the entity list by Y position so they can be rendered in the correct order
  for(long i{0}; i < static_cast<long>(m_entity_list.size()) - 1; ++i)
  {
    for(long j{0}; j < static_cast<long>(m_entity_list.size()) - 1; ++j)
    {
      if(m_entity_list[j + 1]->get_y_pos() < m_entity_list[j]->get_y_pos())
      {
        Entity* temp{m_entity_list[j + 1]};
        m_entity_list[j + 1] = m_entity_list[j];
        m_entity_list[j] = temp;
      }
    }
  }

  update_camera();
}

void Tilemap::render(Tilemap* map) const
{
  long top_left_x = point_to_tile_x(m_cam_x, m_cam_y);
  long top_left_y = point_to_tile_y(m_cam_x, m_cam_y);
  long bottom_right_x = point_to_tile_x(m_cam_x + SCREEN_WIDTH + m_tile_width, m_cam_y + SCREEN_HEIGHT + m_tiles.height);
  long bottom_right_y = point_to_tile_y(m_cam_x + SCREEN_WIDTH + m_tile_width, m_cam_y + SCREEN_HEIGHT + m_tiles.height);

  for(long l{0}; l < static_cast<long>(m_tilemap.size()); ++l)
  {
    for(long k{0}; k < static_cast<long>(m_tilemap[l].size()) - 1; ++k)
    {
      for(long j{top_left_y}; j < bottom_right_y; ++j)
      {
        for(long i{top_left_x}; i < bottom_right_x; ++i)
        {
          DrawTexturePro(m_tiles, Rectangle{static_cast<float>(m_tile_width * get_tile(i, j, l, k)), 0, static_cast<float>(m_tile_width), static_cast<float>(m_tiles.height)}, Rectangle{static_cast<float>(i * m_tile_width - m_cam_x), static_cast<float>(j * m_tiles.height - m_cam_y), static_cast<float>(m_tile_width), static_cast<float>(m_tiles.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
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

string Tilemap::get_npc_speech(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      return m_entity_list[i]->get_speech();
    }
  }
  crash("Entity " + npc_id + " doesn't exist in the current map.");
  return "NULL";
}

bool Tilemap::check_entity_position(const string & npc_id, const long & x, const long & y) const
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id && m_entity_list[i]->get_tile_x() == x + m_last_trigger->get_x_pos() && m_entity_list[i]->get_tile_y() == y + m_last_trigger->get_y_pos())
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
      return m_entity_list[i]->get_x_pos() - m_cam_x;
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
      return m_entity_list[i]->get_y_pos() - m_cam_y;
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

long Tilemap::get_cam_x() const
{
  return m_cam_x;
}

long Tilemap::get_cam_y() const
{
  return m_cam_y;
}

long Tilemap::get_manual_cam_x() const
{
  return m_manual_cam_x;
}

long Tilemap::get_manual_cam_y() const
{
  return m_manual_cam_y;
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

bool Tilemap::is_blocked(const long & x, const long & y, const long & layer) const
{
  if(get_tile(x, y, layer, m_tilemap[layer].size() - 1) == 1)
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

long Tilemap::point_to_tile_x(long x, long y) const
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

long Tilemap::point_to_tile_y(long x, long y) const
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

long Tilemap::get_tile_width() const
{
  return m_tile_width;
}

long Tilemap::get_tile_height() const
{
  return m_tiles.height;
}

long Tilemap::get_tile(const long & x, const long & y, const long & layer, const long & sublayer) const
{
  return m_tilemap[layer][sublayer][x + y * m_map_width];
}

void Tilemap::go_to(const long & x, const long & y)
{
  m_cam_x = x - SCREEN_WIDTH / 2;
  m_cam_y = y - SCREEN_HEIGHT / 2;
}

void Tilemap::go_to_manual(const long & x, const long & y)
{
  m_manual_cam_x = x - SCREEN_WIDTH / 2;
  m_manual_cam_y = y - SCREEN_HEIGHT / 2;
}

void Tilemap::teleport_entity(Tilemap* map, const string & npc_id, const long & destination_x, const long & destination_y)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->set_tiles(map, destination_x, destination_y);
    }
  }
}

void Tilemap::show_npc(const string & npc_id)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->show();
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
      m_entity_list[i]->hide();
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

void Tilemap::change_entity_alpha(const string & npc_id, const long & alpha)
{
  for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
  {
    if(m_entity_list[i]->get_id() == npc_id)
    {
      m_entity_list[i]->change_alpha(alpha);
      return;
    }
  }
  crash("Error: Entity " + npc_id + " doesn't exist in the current map.");
}

Scr Tilemap::get_script(const long & script) const
{
  if(script >= 0 && script < static_cast<long>(m_script_list.size()))
  {
    return m_script_list[script];
  }
  else
  {
    crash("Error: Script ID " + to_string(script) + " doesn't exist in the current map.");
  }
  return DUMMY_SCRIPT;
}

void Tilemap::set_script(Map_Handler* map_handler, const string & script, const long & trigger_index)
{
  long script_index{-1};
  if(script == "Use")
  {
    script_index = m_trigger_list[trigger_index]->get_use_script();
  }
  else if(script == "Enter")
  {
    script_index = m_trigger_list[trigger_index]->get_enter_script();
  }
  if(script_index >= 0 && script_index < static_cast<long>(m_script_list.size()))
  {
    map_handler->add_script(m_script_list[script_index]);
    m_last_trigger = m_trigger_list[trigger_index];
  }
}

long Tilemap::find_trigger(const long & layer, const long & tile_x, const long & tile_y) const
{
  for(long i{0}; i < static_cast<long>(m_trigger_list.size()); ++i)
  {
    if(m_trigger_list[i]->get_layer() == layer && m_trigger_list[i]->in_trigger_x(tile_x) == true && m_trigger_list[i]->in_trigger_y(tile_y) == true)
    {
      return i;
    }
  }
  return -1;
}

void Tilemap::deactivate_trigger(Tilemap* map, const string & trigger_to_deactivate)
{
  if(m_last_trigger != nullptr)
  {
    m_last_trigger->deactivate(map, trigger_to_deactivate);
  }
}

void Tilemap::update_camera()
{
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
        go_to(m_entity_list[i]->get_x_pos(), m_entity_list[i]->get_y_pos());
      }
    }
  }
}

void Tilemap::set_follow_cam(const string & character)
{
  if(character == "NULL")
  {
    for(long i{0}; i < static_cast<long>(m_entity_list.size()); ++i)
    {
      if(m_entity_list[i]->get_id() == m_cam_char_to_follow)
      {
        go_to_manual(m_entity_list[i]->get_x_pos(), m_entity_list[i]->get_y_pos());
      }
    }
  }
  m_cam_char_to_follow = character;
}

void Tilemap::write_tile(const long & tile_to_change_layer, const bool & tile_to_change_sub_layer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to)
{
  m_tilemap[tile_to_change_layer][tile_to_change_sub_layer][tile_to_change_y * m_map_width + tile_to_change_x] = tile_to_change_to;
  m_tilemap[tile_to_change_layer][2][tile_to_change_y * m_map_width + tile_to_change_x] = new_collision;
}

long Trigger::get_id() const
{
  return m_id;
}

long Trigger::get_x_pos() const
{
  return m_x;
}

long Trigger::get_y_pos() const
{
  return m_y;
}

bool Trigger::in_trigger_x(const long & target_tile_x) const
{
  if(m_orientation == 0)
  {
    for(long i{0}; i < m_length; ++i)
    {
      if(m_x + i == target_tile_x)
      {
        return true;
      }
    }
  }
  else
  {
    if(m_x == target_tile_x)
    {
      return true;
    }
  }
  return false;
}

bool Trigger::in_trigger_y(const long & target_tile_y) const
{
  if(m_orientation == 1)
  {
    for(long i{0}; i < m_length; ++i)
    {
      if(m_y + i == target_tile_y)
      {
        return true;
      }
    }
  }
  else
  {
    if(m_y == target_tile_y)
    {
      return true;
    }
  }
  return false;
}

long Trigger::get_layer() const
{
  return m_layer;
}

long Trigger::get_enter_script() const
{
  if(m_deactivated_enter == false)
  {
    return m_enter_script;
  }
  return -1;
}

long Trigger::get_use_script() const
{
  if(m_deactivated_use == false)
  {
    return m_use_script;
  }
  return -1;
}

void Trigger::deactivate(Tilemap* map, const string & trigger_to_deactivate)
{
  if(trigger_to_deactivate == "NULL")
  {
    m_deactivated_enter = true;
    m_deactivated_use = true;
    
    if(m_tile_to_write != -1)
    {
      for(long i{0}; i < m_length; ++i)
      {
        if(m_orientation == 0)
        {
          map->write_tile(m_layer, m_sublayer_to_write, m_new_collision, m_x + i, m_y, m_next_tile == true ? m_tile_to_write + i : m_tile_to_write);
        }
        else
        {
          map->write_tile(m_layer, m_sublayer_to_write, m_new_collision, m_x, m_y + i, m_next_tile == true ? m_tile_to_write + i : m_tile_to_write);
        }
      }
    }
  }
  else if(trigger_to_deactivate == "Enter")
  {
    m_deactivated_enter = true;
  }
  else if(trigger_to_deactivate == "Use")
  {
    m_deactivated_use = true;

    if(m_tile_to_write != -1)
    {
      for(long i{0}; i < m_length; ++i)
      {
        if(m_orientation == 0)
        {
          map->write_tile(m_layer, m_sublayer_to_write, m_new_collision, m_x + i, m_y, m_next_tile == true ? m_tile_to_write + i : m_tile_to_write);
        }
        else
        {
          map->write_tile(m_layer, m_sublayer_to_write, m_new_collision, m_x, m_y + i, m_next_tile == true ? m_tile_to_write + i : m_tile_to_write);
        }
      }
    }
  }
}