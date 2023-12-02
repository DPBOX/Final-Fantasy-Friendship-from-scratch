#include "Main.h"
#include "Tilemap.h"

Entity::~Entity()
{
  UnloadTexture(m_frames);
}

void Entity::set_path(const long & path_index){}

void Entity::update_input(Map_Handler* map_handler, Tilemap* map){}

void Entity::change_alpha(const long & alpha)
{
  m_alpha = alpha;
}

string Entity::get_speech()
{
  return "NULL";
}

bool Entity::path_finished() const
{
  return true;
}

long Entity::get_x_pos() const
{
  return m_x;
}

long Entity::get_y_pos() const
{
  return m_y;
}

long Entity::get_tile_x() const
{
  return m_tile_x;
}

long Entity::get_tile_y() const
{
  return m_tile_y;
}

long Entity::get_layer() const
{
  return m_layer;
}

long Entity::tile_occupied(const long & x, const long & y, const long & layer) const
{
  return m_tile_x == x && m_tile_y == y && m_layer == layer;
}

string Entity::get_type() const
{
  return m_type;
}

string Entity::get_id() const
{
  return m_id;
}

void Entity::show()
{
  m_alpha = ALPHA_MAX;
}

void Entity::hide()
{
  m_alpha = 0;
}

void Entity::set_tiles(Tilemap* map, const long & x, const long & y)
{
  m_tile_x = x;
  m_tile_y = y;
  m_x = m_tile_x * map->get_tile_width() + map->get_tile_width() / 2;
  m_y = m_tile_y * map->get_tile_height() + map->get_tile_height();
}

void Entity::render(Tilemap* map) const
{
  DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() - m_width / 2), static_cast<float>(m_y  - map->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
}

Hero::Hero(Map_Handler* map_handler, Tilemap* map, const long & layer, const long & width, const long & tile_x, const long & tile_y, const Direction & facing_dir, const vector<long> & animation, const long & start_frame, const bool & loop, const long & speed)
{
  m_width = width;
  m_layer = layer;
  m_tile_x = tile_x;
  m_tile_y = tile_y;
  m_facing_dir = facing_dir;
  m_type = "Hero";
  m_id = "Hero";
  m_animation = Animation(animation, start_frame, loop, speed);
  Image image{LoadImageFromMemory(".png", binary_Image_hero_png_start, reinterpret_cast<long>(&binary_Image_hero_png_size))};
  m_frames = LoadTextureFromImage(image);
  UnloadImage(image);

  m_x = m_tile_x * map->get_tile_width() + map->get_tile_width() / 2;
  m_y = m_tile_y * map->get_tile_height() + map->get_tile_height();
  
  wait_enter();
}

void Hero::update_input(Map_Handler* map_handler, Tilemap* map)
{
  if(m_alpha != 0)
  {
    wait_update_tiled(map_handler, map);
    m_animation.update();
  }
}

void Hero::wait_enter()
{
  if(m_facing_dir == Direction::Up)
  {
    m_animation.set_frames(HERO_ANIM_UP);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation.set_frames(HERO_ANIM_DOWN);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation.set_frames(HERO_ANIM_LEFT);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation.set_frames(HERO_ANIM_RIGHT);
    m_animation.set_loop(false);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
  m_frame_count = 0;
}

void Hero::wait_update(Map_Handler* map_handler, Tilemap* map)
{
  if(IsKeyDown(KEY_RIGHT) == false && IsKeyDown(KEY_LEFT) == false && IsKeyDown(KEY_UP) == false && IsKeyDown(KEY_DOWN) == false)
  {
    m_end_x = 0;
    m_end_y = 0;
    m_animation.set_loop(false);
  }
  else
  {
    m_animation.set_loop(true);
    if(IsKeyDown(KEY_RIGHT) == true)
    {
      m_animation.set_frames(HERO_ANIM_RIGHT);
      m_facing_dir = Direction::Right;
      m_end_x = 1;
    }
    else if(IsKeyDown(KEY_LEFT) == true)
    {
      m_animation.set_frames(HERO_ANIM_LEFT);
      m_facing_dir = Direction::Left;
      m_end_x = -1;
    }
    else if(IsKeyDown(KEY_RIGHT) == false && IsKeyDown(KEY_LEFT) == false)
    {
      m_end_x = 0;
    }
    if(IsKeyDown(KEY_DOWN) == true)
    {
      m_animation.set_frames(HERO_ANIM_DOWN);
      m_facing_dir = Direction::Down;
      m_end_y = 1;
    }
    else if(IsKeyDown(KEY_UP) == true)
    {
      m_animation.set_frames(HERO_ANIM_UP);
      m_facing_dir = Direction::Up;
      m_end_y = -1;
    }
    else if(IsKeyDown(KEY_UP) == false && IsKeyDown(KEY_DOWN) == false)
    {
      m_end_y = 0;
    }
  }
  
  m_vy = HERO_VELOCITY * sin(atan2(m_end_y, m_end_x));
  m_vx = m_end_y == 0 && m_end_x == 0 ? 0 : HERO_VELOCITY * cos(atan2(m_end_y, m_end_x));

  m_x += m_vx;
  m_y += m_vy;
  
  m_tile_x = m_x / map->get_tile_width();
  m_tile_y = (m_y - map->get_tile_height()) / map->get_tile_height();
  
  while(map->is_blocked(m_tile_x, m_tile_y + 1, m_layer) == true)
  {
    --m_y;
    m_tile_y = (m_y - map->get_tile_height()) / map->get_tile_height();
  }
  while(map->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true)
  {
    ++m_y;
    m_tile_y = (m_y - map->get_tile_height()) / map->get_tile_height();
  }
  while(map->is_blocked(m_tile_x + 1, m_tile_y, m_layer) == true)
  {
    --m_x;
    m_tile_x = m_x / map->get_tile_width();
  }
  while(map->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true)
  {
    ++m_x;
    m_tile_x = m_x / map->get_tile_width();
  }

  if(IsKeyPressed(KEY_Z) == true)
  {
    if(m_facing_dir == Direction::Up)
    {
      long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y - 1)};
      if(trigger_index != -1)
      {
        map->set_script(map_handler, "Use", trigger_index);
      }
    }
    if(m_facing_dir == Direction::Down)
    {
      long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y + 1)};
      if(trigger_index != -1)
      {
        map->set_script(map_handler, "Use", trigger_index);
      }
    }
    if(m_facing_dir == Direction::Left)
    {
      long trigger_index{map->find_trigger(m_layer, m_tile_x - 1, m_tile_y)};
      if(trigger_index != -1)
      {
        map->set_script(map_handler, "Use", trigger_index);
      }
    }
    if(m_facing_dir == Direction::Right)
    {
      long trigger_index{map->find_trigger(m_layer, m_tile_x + 1, m_tile_y)};
      if(trigger_index != -1)
      {
        map->set_script(map_handler, "Use", trigger_index);
      }
    }
  }
}

void Hero::wait_update_tiled(Map_Handler* map_handler, Tilemap* map)
{
  if(m_vx == 0 && m_vy == 0 && m_frame_count == 0)
  {
    if(IsKeyDown(KEY_RIGHT) == true)
    {
      if(map->is_blocked(m_tile_x + 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(false);
        m_facing_dir = Direction::Right;
      }
      else
      {
        if(m_facing_dir != Direction::Right)
        {
          m_facing_dir = Direction::Right;
          m_animation.set_frames(HERO_ANIM_RIGHT);
          m_animation.set_loop(false);
          m_frame_count = HERO_TURNING_SPEED;
        }
        else
        {
          m_end_x = m_x + map->get_tile_width();
          m_vx = HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_RIGHT);
          m_animation.set_loop(true);
          m_end_y = 0;
          m_vy = 0;
        }
      }
    }

    else if(IsKeyDown(KEY_LEFT) == true)
    {
      if(map->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(false);
        m_facing_dir = Direction::Left;
      }
      else
      {
        if(m_facing_dir != Direction::Left)
        {
          m_facing_dir = Direction::Left;
          m_animation.set_frames(HERO_ANIM_LEFT);
          m_animation.set_loop(false);
          m_frame_count = HERO_TURNING_SPEED;
        }
        else
        {
          m_end_x = m_x - map->get_tile_width();
          m_vx = -HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_LEFT);
          m_animation.set_loop(true);
          m_end_y = 0;
          m_vy = 0;
        }
      }
    }

    if(IsKeyDown(KEY_UP) == true)
    {
      if(map->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true)
      {
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(false);
        m_facing_dir = Direction::Up;
      }
      else
      {
        if(m_facing_dir != Direction::Up)
        {
          m_facing_dir = Direction::Up;
          m_animation.set_frames(HERO_ANIM_UP);
          m_animation.set_loop(false);
          m_frame_count = HERO_TURNING_SPEED;
        }
        else
        {
          m_end_y = m_y - map->get_tile_height();
          m_vy = -HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_UP);
          m_animation.set_loop(true);
          m_end_x = 0;
          m_vx = 0;
        }
      }
    }

    else if(IsKeyDown(KEY_DOWN) == true)
    {
      if(map->is_blocked(m_tile_x, m_tile_y + 1, m_layer) == true)
      {
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(false);
        m_facing_dir = Direction::Down;
      }
      else
      {
        if(m_facing_dir != Direction::Down)
        {
          m_facing_dir = Direction::Down;
          m_animation.set_frames(HERO_ANIM_DOWN);
          m_animation.set_loop(false);
          m_frame_count = HERO_TURNING_SPEED;
        }
        else
        {
          m_end_y = m_y + map->get_tile_height();
          m_vy = HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_DOWN);
          m_animation.set_loop(true);
          m_end_x = 0;
          m_vx = 0;
        }
      }
    }

    if(IsKeyPressed(KEY_Z) == true)
    {
      if(m_facing_dir == Direction::Up)
      {
        long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y - 1)};
        if(trigger_index != -1)
        {
          map->set_script(map_handler, "Use", trigger_index);
        }
      }
      if(m_facing_dir == Direction::Down)
      {
        long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y + 1)};
        if(trigger_index != -1)
        {
          map->set_script(map_handler, "Use", trigger_index);
        }
      }
      if(m_facing_dir == Direction::Left)
      {
        long trigger_index{map->find_trigger(m_layer, m_tile_x - 1, m_tile_y)};
        if(trigger_index != -1)
        {
          map->set_script(map_handler, "Use", trigger_index);
        }
      }
      if(m_facing_dir == Direction::Right)
      {
        long trigger_index{map->find_trigger(m_layer, m_tile_x + 1, m_tile_y)};
        if(trigger_index != -1)
        {
          map->set_script(map_handler, "Use", trigger_index);
        }
      }
    }
  }
  
  else if(m_vx == 0 && m_vy == 0 && m_frame_count != 0)
  {
    if((IsKeyDown(KEY_RIGHT) == true && m_facing_dir == Direction::Right) ||
       (IsKeyDown(KEY_LEFT) == true && m_facing_dir == Direction::Left) ||
       (IsKeyDown(KEY_UP) == true && m_facing_dir == Direction::Up) ||
       (IsKeyDown(KEY_DOWN) == true && m_facing_dir == Direction::Down))
    {
      --m_frame_count;
    }
    else
    {
      m_frame_count = 0;
      wait_enter();
      return;
    }
    if(m_frame_count == 0)
    {
      if(m_facing_dir == Direction::Right)
      {
        m_end_x = m_x + map->get_tile_width();
        m_vx = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(m_facing_dir == Direction::Left)
      {
        m_end_x = m_x - map->get_tile_width();
        m_vx = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(m_facing_dir == Direction::Up)
      {
        m_end_y = m_y - map->get_tile_height();
        m_vy = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
      if(m_facing_dir == Direction::Down)
      {
        m_end_y = m_y + map->get_tile_height();
        m_vy = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
    }
  }
  
  else if(m_vx != 0 || m_vy != 0)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      m_x = m_tile_x * map->get_tile_width() + map->get_tile_width() / 2;
      if(IsKeyDown(KEY_RIGHT) == false || map->is_blocked(m_tile_x + 1, m_tile_y, m_layer) == true)
      {
        move_exit(map_handler, map);
        wait_enter();
      }
      else
      {
        m_end_x = m_x + map->get_tile_width();
        m_vx = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        move_exit(map_handler, map);
      }
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      m_x = m_tile_x * map->get_tile_width() + map->get_tile_width() / 2;
      if(IsKeyDown(KEY_LEFT) == false || map->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true)
      {
        move_exit(map_handler, map);
        wait_enter();
      }
      else
      {
        m_end_x = m_x - map->get_tile_width();
        m_vx = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        move_exit(map_handler, map);
      }
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      m_y = m_tile_y * map->get_tile_height() + map->get_tile_height();
      if(IsKeyDown(KEY_DOWN) == false || map->is_blocked(m_tile_x, m_tile_y + 1, m_layer) == true)
      {
        move_exit(map_handler, map);
        wait_enter();
      }
      else
      {
        m_end_y = m_y + map->get_tile_height();
        m_vy = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        move_exit(map_handler, map);
      }
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      m_y = m_tile_y * map->get_tile_height() + map->get_tile_height();
      if(IsKeyDown(KEY_UP) == false || map->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true)
      {
        move_exit(map_handler, map);
        wait_enter();
      }
      else
      {
        m_end_y = m_y - map->get_tile_height();
        m_vy = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        move_exit(map_handler, map);
      }
    }
  }
}

void Hero::move_exit(Map_Handler* map_handler, Tilemap* map)
{
  long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y)};
  if(trigger_index != -1)
  {
    map->set_script(map_handler, "Enter", trigger_index);
    wait_enter();
  }
}

NPC::NPC(Map_Handler* map_handler, Tilemap* map, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_state = npc_data.m_start_state;
  m_move_speed = npc_data.m_move_speed;
  m_id = npc_data.m_id;
  m_type = "NPC";
  m_animation_list = npc_data.m_animation_list;
  m_show_effect = npc_data.m_show_effect;
  if(npc_data.m_hidden == true)
  {
    m_alpha = 0;
  }
  else
  {
    m_alpha = ALPHA_MAX;
  }
  m_effect_width = npc_data.m_effect.m_width;
  m_effect_offset_x = npc_data.m_effect.m_offset_x;
  m_effect_offset_y = npc_data.m_effect.m_offset_y;
  Image image{LoadImageFromMemory(".png", npc_data.m_effect.m_img_data, npc_data.m_effect.m_img_size)};
  m_effect_img = LoadTextureFromImage(image);
  UnloadImage(image);
  m_paths = npc_data.m_paths;
  m_speech = npc_data.m_speech;
  m_effect_animation = Animation(npc_data.m_effect.m_animation_list, 0, true, npc_data.m_effect.m_animation_speed);
  if(m_facing_dir == Direction::Up)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);
  m_x = m_tile_x * map->get_tile_width() + m_width / 2;
  m_y = m_tile_y * map->get_tile_height() + map->get_tile_height();
//  enter(map_handler, map);
}

NPC::~NPC()
{
  UnloadTexture(m_effect_img);
}

string NPC::get_speech()
{
  string speech{m_speech[m_speech_index]};
  ++m_speech_index;
  if(m_speech_index == static_cast<long>(m_speech.size()))
  {
    m_speech_index = 0;
  }
  return speech;
}

void NPC::set_path(const long & path_index)
{
  if(path_index >= 0 && path_index < static_cast<long>(m_paths.size()))
  {
    m_path = path_index;
    m_path_index = 0;
  }
  else
  {
    crash("Error: NPC \"" + m_id + "\" doesn't have a " + to_string(path_index) + " path.");
  }
}

bool NPC::path_finished() const
{
  return m_path == -1;
}

void NPC::enter(Map_Handler* map_handler, Tilemap* map)
{/*
  if(m_state == "Stand")
  {
    stand_enter();
  }
  if(m_state == "Plan Stroll")
  {
    plan_stroll_enter();
  }
  if(m_state == "Move")
  {
    move_enter();
  }
  if(m_state == "Follow Path")
  {
    follow_path_enter();
  }*/
}

void NPC::exit(Map_Handler* map_handler, Tilemap* map)
{/*
  if(m_state == "Stand")
  {
    stand_exit();
  }
  if(m_state == "Plan Stroll")
  {
    plan_stroll_exit();
  }
  if(m_state == "Move")
  {
    move_exit();
  }
  if(m_state == "Follow Path")
  {
    follow_path_exit();
  }*/
}

void NPC::update_input(Map_Handler* map_handler, Tilemap* map)
{/*
  if(m_alpha != 0)
  {
    if(m_state == "Stand")
    {
      stand_update();
    }
    if(m_state == "Plan Stroll")
    {
      plan_stroll_update(map);
    }
    if(m_state == "Move")
    {
      move_update();
    }
    if(m_state == "Follow Path")
    {
      follow_path_update(map);
    }
    m_animation.update();
    m_effect_animation.update();
  }*/
}
/*
void NPC::stand_enter()
{
  if(m_facing_dir == Direction::Up)
  {
    m_animation.set_frames(m_animation_list[0]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation.set_frames(m_animation_list[2]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation.set_frames(m_animation_list[3]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation.set_frames(m_animation_list[1]);
    m_animation.set_loop(false);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
  m_x_dir = 0;
  m_y_dir = 0;
}

void NPC::stand_update()
{
  if(m_path != -1)
  {
    m_next_state = "Follow Path";
  }
}

void NPC::plan_stroll_enter()
{
  if(m_facing_dir == Direction::Up)
  {
    m_animation.set_frames(m_animation_list[0]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation.set_frames(m_animation_list[2]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation.set_frames(m_animation_list[3]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation.set_frames(m_animation_list[1]);
    m_animation.set_loop(false);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
  m_x_dir = 0;
  m_y_dir = 0;

  m_frame_count = rand() % (300 - 60) + 60;
}
*/
void NPC::plan_stroll_update(Tilemap* map)
{/*
  --m_frame_count;
  if(m_frame_count == 0)
  {
    long direction = rand() % 4;

    if(direction == 0)
    {
      m_facing_dir = Direction::Right;
      if(map->is_blocked(m_tile_x + 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[1]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_x = m_x + .5 + map->get_tile_width();
        m_vx = m_move_speed;
        m_x_dir = 1;
        m_animation.set_frames(m_animation_list[1]);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        m_y_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == 1)
    {
      m_facing_dir = Direction::Left;
      if(map->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[3]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_x = m_x + .5 - map->get_tile_width();
        m_vx = -m_move_speed;
        m_x_dir = -1;
        m_animation.set_frames(m_animation_list[3]);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        m_y_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == 2)
    {
      m_facing_dir = Direction::Down;
      if(map->is_blocked(m_tile_x, m_tile_y + 1, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[2]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_y = m_y + .5 + map->get_tile_height();
        m_vy = m_move_speed;
        m_y_dir = 1;
        m_animation.set_frames(m_animation_list[2]);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        m_x_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == 3)
    {
      m_facing_dir = Direction::Up;
      if(map->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[0]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_y = m_y + .5 - map->get_tile_height();
        m_vy = -m_move_speed;
        m_y_dir = -1;
        m_animation.set_frames(m_animation_list[0]);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        m_x_dir = 0;
        m_next_state = "Move";
      }
    }
  }*/
}
/*
void NPC::move_update()
{
  m_x += m_vx;
  m_y += m_vy;

  if(m_x_dir == 1 && m_x > m_end_x)
  {
    ++m_tile_x;
    m_x = floor(m_x);
    if(m_path == -1)
    {
      m_next_state = "Plan Stroll";
    }
    else
    {
      if(m_path_index < static_cast<long>(m_paths[m_path].size()))
      {
        m_next_state = "Follow Path";
      }
      else
      {
        m_next_state = "Stand";
        m_path = -1;
        m_path_index = -1;
      }
    }
  }
  if(m_x_dir == -1 && m_x < m_end_x)
  {
    --m_tile_x;
    m_x = ceil(m_x);
    if(m_path == -1)
    {
      m_next_state = "Plan Stroll";
    }
    else
    {
      if(m_path_index < static_cast<long>(m_paths[m_path].size()))
      {
        m_next_state = "Follow Path";
      }
      else
      {
        m_next_state = "Stand";
        m_path = -1;
        m_path_index = -1;
      }
    }
  }
  if(m_y_dir == 1 && m_y > m_end_y)
  {
    ++m_tile_y;
    m_y = floor(m_y);
    if(m_path == -1)
    {
      m_next_state = "Plan Stroll";
    }
    else
    {
      if(m_path_index < static_cast<long>(m_paths[m_path].size()))
      {
        m_next_state = "Follow Path";
      }
      else
      {
        m_next_state = "Stand";
        m_path = -1;
        m_path_index = -1;
      }
    }
  }
  if(m_y_dir == -1 && m_y < m_end_y)
  {
    --m_tile_y;
    m_y = ceil(m_y);
    if(m_path == -1)
    {
      m_next_state = "Plan Stroll";
    }
    else
    {
      if(m_path_index < static_cast<long>(m_paths[m_path].size()))
      {
        m_next_state = "Follow Path";
      }
      else
      {
        m_next_state = "Stand";
        m_path = -1;
        m_path_index = -1;
      }
    }
  }
}

void NPC::follow_path_enter()
{
  if(m_facing_dir == Direction::Up)
  {
    m_animation.set_frames(m_animation_list[0]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation.set_frames(m_animation_list[2]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation.set_frames(m_animation_list[3]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation.set_frames(m_animation_list[1]);
    m_animation.set_loop(false);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
  m_x_dir = 0;
  m_y_dir = 0;
}

void NPC::follow_path_exit()
{
  ++m_path_index;
}
*/
void NPC::follow_path_update(Tilemap* map)
{/*
  if(m_path != -1 && m_path_index < static_cast<long>(m_paths[m_path].size()))
  {
    Direction direction{m_paths[m_path][m_path_index]};

    if(direction == Direction::Right)
    {
      m_facing_dir = Direction::Right;
      if(map->is_blocked(m_tile_x + 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[1]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_x = m_x + .5 + map->get_tile_width();
        m_vx = m_move_speed;
        m_x_dir = 1;
        m_animation.set_frames(m_animation_list[1]);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        m_y_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == Direction::Left)
    {
      m_facing_dir = Direction::Left;
      if(map->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[3]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_x = m_x + .5 - map->get_tile_width();
        m_vx = -m_move_speed;
        m_x_dir = -1;
        m_animation.set_frames(m_animation_list[3]);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        m_y_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == Direction::Down)
    {
      m_facing_dir = Direction::Down;
      if(map->is_blocked(m_tile_x, m_tile_y + 1, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[2]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_y = m_y + .5 + map->get_tile_height();
        m_vy = m_move_speed;
        m_y_dir = 1;
        m_animation.set_frames(m_animation_list[2]);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        m_x_dir = 0;
        m_next_state = "Move";
      }
    }

    if(direction == Direction::Up)
    {
      m_facing_dir = Direction::Up;
      if(map->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true)
      {
        m_animation.set_frames(m_animation_list[0]);
        m_animation.set_loop(false);
        m_frame_count = rand() % (300 - 60) + 60;
      }
      else
      {
        m_end_y = m_y + .5 - map->get_tile_height();
        m_vy = -m_move_speed;
        m_y_dir = -1;
        m_animation.set_frames(m_animation_list[0]);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        m_x_dir = 0;
        m_next_state = "Move";
      }
    }
  }*/
}

void NPC::render(Tilemap* map) const
{
  DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() - m_width / 2), static_cast<float>(m_y - map->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
  if(m_show_effect == true)
  {
    DrawTexturePro(m_effect_img, Rectangle{static_cast<float>(m_effect_animation.get_frame() * m_effect_width), 0, static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() + m_effect_offset_x - m_width / 2), static_cast<float>(m_y - map->get_cam_y() + m_effect_offset_y - m_frames.height), static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}