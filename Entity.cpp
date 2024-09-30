#include "Main.h"
#include "Tilemap.h"

Map_Handler::Entity::~Entity()
{
  UnloadTexture(m_frames);
}

void Map_Handler::Entity::set_path(const long & path_index){}

void Map_Handler::Entity::turn(const Direction & direction){}

bool Map_Handler::Entity::path_finished() const
{
  return true;
}

long Map_Handler::Entity::tile_occupied(const long & x, const long & y, const long & layer) const
{
  return m_alpha != 0 && m_tile_x == x && m_tile_y == y && m_layer == layer;
}

void Map_Handler::Entity::render(Map_Handler* map_handler) const
{
  DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map_handler->get_cam_x() - m_width / 2), static_cast<float>(m_y - map_handler->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
}

Map_Handler::Treasure_Chest::Treasure_Chest(Map_Handler* map_handler, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_id = npc_data.m_id;
  m_type = "Treasure Chest";
  m_scripts = npc_data.m_scripts;
  if(npc_data.m_hidden == true)
  {
    m_alpha = 0;
  }
  else
  {
    m_alpha = ALPHA_MAX;
  }

  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);
  m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
  m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
}

void Map_Handler::Treasure_Chest::update_input(Map_Handler* map_handler){}

void Map_Handler::Treasure_Chest::turn(const Direction & direction)
{
  m_opened = true;
}

void Map_Handler::Treasure_Chest::render(Map_Handler* map_handler) const
{
  DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_opened * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map_handler->get_cam_x() - m_width / 2), static_cast<float>(m_y - map_handler->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
}

void Map_Handler::Character::turn(const Direction & direction)
{
  if(m_alpha != 0)
  {
    m_facing_dir = direction;
    if(m_facing_dir == Direction::Up)
    {
      m_animation.set_frames(m_animation_list[3]);
      m_animation.set_loop(false);
    }
    if(m_facing_dir == Direction::Down)
    {
      m_animation.set_frames(m_animation_list[0]);
      m_animation.set_loop(false);
    }
    if(m_facing_dir == Direction::Left)
    {
      m_animation.set_frames(m_animation_list[1]);
      m_animation.set_loop(false);
    }
    if(m_facing_dir == Direction::Right)
    {
      m_animation.set_frames(m_animation_list[2]);
      m_animation.set_loop(false);
    }
  }
}

Map_Handler::Hero::Hero(Map_Handler* map_handler, const long & layer, const long & width, const long & tile_x, const long & tile_y, const Direction & facing_dir, const vector<long> & animation, const long & start_frame, const bool & loop, const long & speed)
{
  m_width = width;
  m_layer = layer;
  m_tile_x = tile_x;
  m_tile_y = tile_y;
  m_facing_dir = facing_dir;
  m_type = "Hero";
  m_id = "Hero";
  m_animation = Animation(animation, start_frame, loop, speed);
  Image image{LoadImageFromMemory(".png", TEMPEST_IMAGE.m_data, TEMPEST_IMAGE.m_size)};
  m_frames = LoadTextureFromImage(image);
  UnloadImage(image);

  m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
  m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
  
  wait_enter();
}

void Map_Handler::Hero::update_input(Map_Handler* map_handler)
{
  if(m_alpha != 0)
  {
    wait_update_tiled(map_handler);
    m_animation.update();
  }
}

void Map_Handler::Hero::wait_enter()
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

void Map_Handler::Hero::wait_update_tiled(Map_Handler* map_handler)
{
  if(m_vx < .001 && m_vy < .001 && m_vx > -.001 && m_vy > -.001 && m_frame_count == 0)
  {
    if(IsKeyDown(KEY_RIGHT) == true)
    {
      if(map_handler->is_blocked(m_tile_x + 2, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 3, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 2, m_tile_y + 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 3, m_tile_y + 1, m_layer) == true)
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
          m_end_x = m_x + map_handler->get_map_tile_width() * 2;
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
      if(map_handler->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 2, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 1, m_tile_y + 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 2, m_tile_y + 1, m_layer) == true)
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
          m_end_x = m_x - map_handler->get_map_tile_width() * 2;
          m_vx = -HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_LEFT);
          m_animation.set_loop(true);
          m_end_y = 0;
          m_vy = 0;
        }
      }
    }

    else if(IsKeyDown(KEY_UP) == true)
    {
      if(map_handler->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x, m_tile_y - 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y - 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y - 2, m_layer) == true)
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
          m_end_y = m_y - map_handler->get_map_tile_height() * 2;
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
      if(map_handler->is_blocked(m_tile_x, m_tile_y + 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x, m_tile_y + 3, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y + 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y + 3, m_layer) == true)
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
          m_end_y = m_y + map_handler->get_map_tile_height() * 2;
          m_vy = HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_DOWN);
          m_animation.set_loop(true);
          m_end_x = 0;
          m_vx = 0;
        }
      }
    }

    else if(IsKeyPressed(KEY_Z) == true)
    {
      if(m_facing_dir == Direction::Up)
      {
        long entity_index{map_handler->find_entity(m_layer, m_tile_x, m_tile_y - 2)};
        long trigger_index{map_handler->find_trigger(m_layer, m_tile_x, m_tile_y - 1)};
        if(entity_index != -1)
        {
          map_handler->turn_entity(entity_index, Direction::Down);
          map_handler->set_map_script(entity_index, true);
        }
        else if(trigger_index != -1)
        {
          map_handler->set_map_script(trigger_index, false);
        }
      }
      if(m_facing_dir == Direction::Down)
      {
        long entity_index{map_handler->find_entity(m_layer, m_tile_x, m_tile_y + 2)};
        long trigger_index{map_handler->find_trigger(m_layer, m_tile_x, m_tile_y + 1)};
        if(entity_index != -1)
        {
          map_handler->turn_entity(entity_index, Direction::Up);
          map_handler->set_map_script(entity_index, true);
        }
        else if(trigger_index != -1)
        {
          map_handler->set_map_script(trigger_index, false);
        }
      }
      if(m_facing_dir == Direction::Left)
      {
        long entity_index{map_handler->find_entity(m_layer, m_tile_x - 2, m_tile_y)};
        long trigger_index{map_handler->find_trigger(m_layer, m_tile_x - 1, m_tile_y)};
        if(entity_index != -1)
        {
          map_handler->turn_entity(entity_index, Direction::Right);
          map_handler->set_map_script(entity_index, true);
        }
        else if(trigger_index != -1)
        {
          map_handler->set_map_script(trigger_index, false);
        }
      }
      if(m_facing_dir == Direction::Right)
      {
        long entity_index{map_handler->find_entity(m_layer, m_tile_x + 2, m_tile_y)};
        long trigger_index{map_handler->find_trigger(m_layer, m_tile_x + 1, m_tile_y)};
        if(entity_index != -1)
        {
          map_handler->turn_entity(entity_index, Direction::Left);
          map_handler->set_map_script(entity_index, true);
        }
        else if(trigger_index != -1)
        {
          map_handler->set_map_script(trigger_index, false);
        }
      }
    }
  }
  
  else if(m_vx < .001 && m_vy < .001 && m_vx > -.001 && m_vy > -.001 && m_frame_count != 0)
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
        m_end_x = m_x + map_handler->get_map_tile_width() * 2;
        m_vx = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(m_facing_dir == Direction::Left)
      {
        m_end_x = m_x - map_handler->get_map_tile_width() * 2;
        m_vx = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(m_facing_dir == Direction::Up)
      {
        m_end_y = m_y - map_handler->get_map_tile_height() * 2;
        m_vy = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
      if(m_facing_dir == Direction::Down)
      {
        m_end_y = m_y + map_handler->get_map_tile_height() * 2;
        m_vy = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
    }
  }
  
  else if(m_vx > .001 || m_vy > .001 || m_vx < -.001 || m_vy < -.001)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      ++m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      if(IsKeyDown(KEY_RIGHT) == false || 
         map_handler->is_blocked(m_tile_x + 2, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 3, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 2, m_tile_y + 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 3, m_tile_y + 1, m_layer) == true)
      {
        move_exit(map_handler);
        wait_enter();
      }
      else
      {
        m_end_x = m_x + map_handler->get_map_tile_width() * 2;
        m_vx = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        move_exit(map_handler);
      }
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      --m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      if(IsKeyDown(KEY_LEFT) == false ||
         map_handler->is_blocked(m_tile_x - 1, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 2, m_tile_y, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 1, m_tile_y + 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x - 2, m_tile_y + 1, m_layer) == true)
      {
        move_exit(map_handler);
        wait_enter();
      }
      else
      {
        m_end_x = m_x - map_handler->get_map_tile_width() * 2;
        m_vx = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
        move_exit(map_handler);
      }
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      ++m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      if(IsKeyDown(KEY_DOWN) == false ||
         map_handler->is_blocked(m_tile_x, m_tile_y + 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x, m_tile_y + 3, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y + 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y + 3, m_layer) == true)
      {
        move_exit(map_handler);
        wait_enter();
      }
      else
      {
        m_end_y = m_y + map_handler->get_map_tile_height() * 2;
        m_vy = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        move_exit(map_handler);
      }
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      --m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      if(IsKeyDown(KEY_UP) == false ||
         map_handler->is_blocked(m_tile_x, m_tile_y - 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x, m_tile_y - 2, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y - 1, m_layer) == true ||
         map_handler->is_blocked(m_tile_x + 1, m_tile_y - 2, m_layer) == true)
      {
        move_exit(map_handler);
        wait_enter();
      }
      else
      {
        m_end_y = m_y - map_handler->get_map_tile_height() * 2;
        m_vy = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
        move_exit(map_handler);
      }
    }
  }
}

void Map_Handler::Hero::move_exit(Map_Handler* map_handler)
{
  long trigger_index{map_handler->find_trigger(m_layer, m_tile_x, m_tile_y)};
  if(trigger_index != -1)
  {
    map_handler->set_map_script(trigger_index, false);
    wait_enter();
  }
}

void Map_Handler::NPC::update_input(Map_Handler* map_handler)
{
  if(m_alpha != 0)
  {
    stand_update(map_handler);
    m_animation.update();
    m_effect_animation.update();
  }
}

void Map_Handler::NPC::render(Map_Handler* map_handler) const
{
  DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map_handler->get_cam_x() - m_width / 2), static_cast<float>(m_y - map_handler->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
  if(m_show_effect == true)
  {
    DrawTexturePro(m_effect_img, Rectangle{static_cast<float>(m_effect_animation.get_frame() * m_effect_width), 0, static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Rectangle{static_cast<float>(m_x - map_handler->get_cam_x() + m_effect_offset_x - m_width / 2), static_cast<float>(m_y - map_handler->get_cam_y() + m_effect_offset_y - m_frames.height), static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}

Map_Handler::NPC::~NPC()
{
  UnloadTexture(m_effect_img);
}

void Map_Handler::NPC::enter()
{
  if(m_facing_dir == Direction::Up)
  {
    m_animation.set_frames(m_animation_list[3]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation.set_frames(m_animation_list[0]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation.set_frames(m_animation_list[1]);
    m_animation.set_loop(false);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation.set_frames(m_animation_list[2]);
    m_animation.set_loop(false);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
}

Map_Handler::Standing_NPC::Standing_NPC(Map_Handler* map_handler, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_id = npc_data.m_id;
  m_type = "Standing NPC";
  m_animation_list = npc_data.m_animation_list;
  m_show_effect = npc_data.m_show_effect;
  m_scripts = npc_data.m_scripts;
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
  m_effect_animation = Animation(npc_data.m_effect.m_animation_list, 0, true, npc_data.m_effect.m_animation_speed);
  if(m_facing_dir == Direction::Up)
  {
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);
  m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
  m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
  enter();
}

void Map_Handler::Standing_NPC::stand_update(Map_Handler* map_handler){}

Map_Handler::Strolling_NPC::Strolling_NPC(Map_Handler* map_handler, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_move_speed = npc_data.m_move_speed;
  m_id = npc_data.m_id;
  m_type = "Strolling NPC";
  m_animation_list = npc_data.m_animation_list;
  m_show_effect = npc_data.m_show_effect;
  m_scripts = npc_data.m_scripts;
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
  m_effect_animation = Animation(npc_data.m_effect.m_animation_list, 0, true, npc_data.m_effect.m_animation_speed);
  if(m_facing_dir == Direction::Up)
  {
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);
  m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
  m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
  enter();
  m_frame_count = rand() % (300 - 60) + 60;
}

void Map_Handler::Strolling_NPC::stand_update(Map_Handler* map_handler)
{
  if(m_vx > .001 || m_vy > .001 || m_vx < -.001 || m_vy < -.001)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      ++m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      enter();
      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      --m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      enter();
      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      ++m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      enter();
      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      --m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      enter();
      m_frame_count = rand() % (300 - 60) + 60;
    }
  }
  else if(m_frame_count != 0)
  {
    --m_frame_count;
    if(m_frame_count == 0)
    {
      long direction = rand() % 4;
      if(direction == 0)
      {
        m_end_x = m_x + map_handler->get_map_tile_width() * 2;
        m_vx = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_RIGHT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(direction == 1)
      {
        m_end_x = m_x - map_handler->get_map_tile_width() * 2;
        m_vx = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_LEFT);
        m_animation.set_loop(true);
        m_end_y = 0;
        m_vy = 0;
      }
      if(direction == 2)
      {
        m_end_y = m_y - map_handler->get_map_tile_height() * 2;
        m_vy = -HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_UP);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
      if(direction == 3)
      {
        m_end_y = m_y + map_handler->get_map_tile_height() * 2;
        m_vy = HERO_VELOCITY;
        m_animation.set_frames(HERO_ANIM_DOWN);
        m_animation.set_loop(true);
        m_end_x = 0;
        m_vx = 0;
      }
    }
  }
}

Map_Handler::Path_NPC::Path_NPC(Map_Handler* map_handler, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_move_speed = npc_data.m_move_speed;
  m_id = npc_data.m_id;
  m_type = "Path NPC";
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
  m_effect_animation = Animation(npc_data.m_effect.m_animation_list, 0, true, npc_data.m_effect.m_animation_speed);
  if(m_facing_dir == Direction::Up)
  {
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, npc_data.m_loop, npc_data.m_animation_speed);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);
  m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
  m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
  enter();
}

void Map_Handler::Path_NPC::stand_update(Map_Handler* map_handler)
{
  if(m_vx > .001 || m_vy > .001 || m_vx < -.001 || m_vy < -.001)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      ++m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      set_next_path(map_handler);
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      --m_tile_x;
      m_x = m_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width();
      set_next_path(map_handler);
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      ++m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      set_next_path(map_handler);
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      --m_tile_y;
      m_y = m_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() * 2;
      set_next_path(map_handler);
    }
  }
}

void Map_Handler::Path_NPC::set_path(const long & path_index)
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

bool Map_Handler::Path_NPC::path_finished() const
{
  return m_path == -1;
}

void Map_Handler::Path_NPC::set_next_path(Map_Handler* map_handler)
{
  if(m_path_index < static_cast<long>(m_paths[m_path].size()))
  {
    Direction direction{m_paths[m_path][m_path_index]};

    if(direction == Direction::Right)
    {
      m_end_x = m_x + map_handler->get_map_tile_width() * 2;
      m_vx = HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_RIGHT);
      m_animation.set_loop(true);
      m_end_y = 0;
      m_vy = 0;
      ++m_path_index;
    }
    if(direction == Direction::Left)
    {
      m_end_x = m_x - map_handler->get_map_tile_width() * 2;
      m_vx = -HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_LEFT);
      m_animation.set_loop(true);
      m_end_y = 0;
      m_vy = 0;
      ++m_path_index;
    }
    if(direction == Direction::Up)
    {
      m_end_y = m_y - map_handler->get_map_tile_height() * 2;
      m_vy = -HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_UP);
      m_animation.set_loop(true);
      m_end_x = 0;
      m_vx = 0;
      ++m_path_index;
    }
    if(direction == Direction::Down)
    {
      m_end_y = m_y + map_handler->get_map_tile_height() * 2;
      m_vy = HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_DOWN);
      m_animation.set_loop(true);
      m_end_x = 0;
      m_vx = 0;
      ++m_path_index;
    }
  }
  else
  {
    enter();
  }
}
