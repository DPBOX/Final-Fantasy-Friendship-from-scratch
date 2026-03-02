#include "Main.h"
#include "Entity.h"
#include "Tilemap.h"
#include "Input_Wrapper.h"

Entity::~Entity()
{
  UnloadTexture(m_frames);
}

void Entity::set_path(const long & path_index){}

void Entity::turn(const Direction & direction){}

bool Entity::path_finished() const
{
  return true;
}

string Entity::get_id() const
{
  return m_id;
}

string Entity::get_type() const
{
  return m_type;
}

long Entity::get_layer() const
{
  return m_layer;
}

long Entity::get_tile_x() const
{
  return m_tile_x;
}

long Entity::get_tile_y() const
{
  return m_tile_y;
}

double Entity::get_position_x() const
{
  return m_x;
}

double Entity::get_position_y() const
{
  return m_y;
}

void Entity::set_alpha(const long & alpha)
{
  m_alpha = alpha;
}

long Entity::get_touch_script() const
{
  if(m_alpha != 0)
  {
    return m_touch_script;
  }
  return -1;
}

long Entity::get_interact_script() const
{
  if(m_alpha != 0)
  {
    return m_interact_script;
  }
  return -1;
}

long Entity::tile_occupied(const long & x, const long & y, const long & layer) const
{
  return m_alpha != 0 && m_tile_x == x && m_tile_y == y && m_layer == layer;
}

void Entity::render(const Tilemap* const map) const
{
  if(m_image_name != "NULL")
  {
    DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() - m_width / 2), static_cast<float>(m_y - map->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
  }
}

Treasure_Chest::Treasure_Chest(Tilemap* map, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_id = npc_data.m_id;
  m_type = "Treasure Chest";
  m_interact_script = npc_data.m_interact_script;
  m_image_name = npc_data.m_img_name;
  m_touch_script = npc_data.m_touch_script;
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
  m_x = map->get_tile_foot_x(m_tile_x);
  m_y = map->get_tile_foot_y(m_tile_y);
}

void Treasure_Chest::update_input(Tilemap* map, Input_Wrapper* input){}

void Treasure_Chest::turn(const Direction & direction)
{
  m_opened = true;
}

void Treasure_Chest::render(const Tilemap* const map) const
{
  if(m_image_name != "NULL")
  {
    DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_opened * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() - m_width / 2), static_cast<float>(m_y - map->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
  }
}

void Character::turn(const Direction & direction)
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

Hero::Hero(Tilemap* map, const long & layer, const long & tile_x, const long & tile_y, const Direction & facing_dir)
{
  m_width = HERO_WIDTH;
  m_layer = layer;
  m_tile_x = tile_x;
  m_tile_y = tile_y;
  m_facing_dir = facing_dir;
  m_type = "Hero";
  m_id = "Hero";
  m_image_name = "Hero";
  Image image{LoadImageFromMemory(".png", TWILIGHT_SPARKLE_IMAGE.m_data, TWILIGHT_SPARKLE_IMAGE.m_size)};
  m_frames = LoadTextureFromImage(image);
  UnloadImage(image);

  m_x = map->get_tile_foot_x(m_tile_x);
  m_y = map->get_tile_foot_y(m_tile_y);
  
  if(m_facing_dir == Direction::Up)
  {
    m_animation = Animation(HERO_ANIM_UP, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(HERO_ANIM_DOWN, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(HERO_ANIM_LEFT, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(HERO_ANIM_RIGHT, HERO_START_FRAME, false, HERO_ANIMATION_SPEED);
  }
  m_end_x = 0;
  m_end_y = 0;
  m_vx = 0;
  m_vy = 0;
  m_frame_count = 0;
}

void Hero::update_input(Tilemap* map, Input_Wrapper* input)
{
  if(m_alpha != 0)
  {
    wait_update_continuous(map, input);
    m_animation.update();
  }
}

void Hero::wait_update_continuous(Tilemap* map, Input_Wrapper* input)
{
  if(input->right_button_held() == false && input->left_button_held() == false && input->up_button_held() == false && input->down_button_held() == false)
  {
    m_end_x = 0;
    m_end_y = 0;
    m_animation.set_loop(false);
  }
  else
  {
    m_animation.set_loop(true);
    if(input->right_button_held() == true)
    {
      m_animation.set_frames(HERO_ANIM_RIGHT);
      m_facing_dir = Direction::Right;
      m_end_x = 1;
    }
    else if(input->left_button_held() == true)
    {
      m_animation.set_frames(HERO_ANIM_LEFT);
      m_facing_dir = Direction::Left;
      m_end_x = -1;
    }
    else if(input->right_button_held() == false && input->left_button_held() == false)
    {
      m_end_x = 0;
    }
    if(input->down_button_held() == true)
    {
      m_animation.set_frames(HERO_ANIM_DOWN);
      m_facing_dir = Direction::Down;
      m_end_y = 1;
    }
    else if(input->up_button_held() == true)
    {
      m_animation.set_frames(HERO_ANIM_UP);
      m_facing_dir = Direction::Up;
      m_end_y = -1;
    }
    else if(input->up_button_held() == false && input->down_button_held() == false)
    {
      m_end_y = 0;
    }
  }

  m_vy = HERO_VELOCITY * sin(atan2(m_end_y, m_end_x));
  m_vx = m_end_y == 0 && m_end_x == 0 ? 0 : HERO_VELOCITY * cos(atan2(m_end_y, m_end_x));

  m_x += m_vx;
  m_tile_x = map->point_to_tile_x(m_x);
  if((map->is_blocked_point(m_x + PLAYER_X_COLLISION_POINT, m_y, m_layer) == true || map->is_blocked_point(m_x + PLAYER_X_COLLISION_POINT, m_y + PLAYER_Y_COLLISION_POINT_DOWN, m_layer) == true || map->is_blocked_point(m_x + PLAYER_X_COLLISION_POINT, m_y - PLAYER_Y_COLLISION_POINT_UP, m_layer) == true) && m_end_x > 0)
  {
    m_x -= m_vx;
    m_tile_x = map->point_to_tile_x(m_x);
  }
  if((map->is_blocked_point(m_x - PLAYER_X_COLLISION_POINT, m_y, m_layer) == true || map->is_blocked_point(m_x - PLAYER_X_COLLISION_POINT, m_y + PLAYER_Y_COLLISION_POINT_DOWN, m_layer) == true || map->is_blocked_point(m_x - PLAYER_X_COLLISION_POINT, m_y - PLAYER_Y_COLLISION_POINT_UP, m_layer) == true) && m_end_x < 0)
  {
    m_x -= m_vx;
    m_tile_x = map->point_to_tile_x(m_x);
  }

  m_y += m_vy;
  m_tile_y = map->point_to_tile_y(m_y);

  if((map->is_blocked_point(m_x, m_y + PLAYER_Y_COLLISION_POINT_DOWN, m_layer) == true || map->is_blocked_point(m_x + PLAYER_X_COLLISION_POINT, m_y + PLAYER_Y_COLLISION_POINT_DOWN, m_layer) == true || map->is_blocked_point(m_x - PLAYER_X_COLLISION_POINT, m_y + PLAYER_Y_COLLISION_POINT_DOWN, m_layer) == true) && m_end_y > 0)
  {
    m_y -= m_vy;
    m_tile_y = map->point_to_tile_y(m_y);
  }
  if((map->is_blocked_point(m_x, m_y - PLAYER_Y_COLLISION_POINT_UP, m_layer) == true || map->is_blocked_point(m_x + PLAYER_X_COLLISION_POINT, m_y - PLAYER_Y_COLLISION_POINT_UP, m_layer) == true || map->is_blocked_point(m_x - PLAYER_X_COLLISION_POINT, m_y - PLAYER_Y_COLLISION_POINT_UP, m_layer) == true) && m_end_y < 0)
  {
    m_y -= m_vy;
    m_tile_y = map->point_to_tile_y(m_y);
  }

  if(input->A_button_pressed() == true)
  {
    if(m_facing_dir == Direction::Up)
    {
      long entity_index{map->find_entity(m_layer, m_tile_x, m_tile_y - 1)};
      if(entity_index != -1)
      {
        map->turn_entity(entity_index, Direction::Down);
        map->set_map_script(entity_index);
      }
    }
    if(m_facing_dir == Direction::Down)
    {
      long entity_index{map->find_entity(m_layer, m_tile_x, m_tile_y + 1)};
      if(entity_index != -1)
      {
        map->turn_entity(entity_index, Direction::Up);
        map->set_map_script(entity_index);
      }
    }
    if(m_facing_dir == Direction::Left)
    {
      long entity_index{map->find_entity(m_layer, m_tile_x - 1, m_tile_y)};
      if(entity_index != -1)
      {
        map->turn_entity(entity_index, Direction::Right);
        map->set_map_script(entity_index);
      }
    }
    if(m_facing_dir == Direction::Right)
    {
      long entity_index{map->find_entity(m_layer, m_tile_x + 1, m_tile_y)};
      if(entity_index != -1)
      {
        map->turn_entity(entity_index, Direction::Left);
        map->set_map_script(entity_index);
      }
    }
  }
}

/*
void Hero::move_exit(Tilemap* map)
{

  long trigger_index{map->find_trigger(m_layer, m_tile_x, m_tile_y)};
  if(trigger_index != -1)
  {
    map->set_map_script(trigger_index, false);
    wait_enter();
  }
}
*/

void NPC::update_input(Tilemap* map, Input_Wrapper* input)
{
  if(m_alpha != 0)
  {
    stand_update(map);
    m_animation.update();
    m_effect_animation.update();
  }
}

NPC::~NPC()
{
  UnloadTexture(m_effect_img);
}

void NPC::render(const Tilemap* const map) const
{
  if(m_image_name != "NULL")
  {
    DrawTexturePro(m_frames, Rectangle{static_cast<float>(m_animation.get_frame() * m_width), 0, static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() - m_width / 2), static_cast<float>(m_y - map->get_cam_y() - m_frames.height), static_cast<float>(m_width), static_cast<float>(m_frames.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_alpha)});
  }
  if(m_show_effect == true)
  {
    DrawTexturePro(m_effect_img, Rectangle{static_cast<float>(m_effect_animation.get_frame() * m_effect_width), 0, static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Rectangle{static_cast<float>(m_x - map->get_cam_x() + m_effect_offset_x - m_width / 2), static_cast<float>(m_y - map->get_cam_y() + m_effect_offset_y - m_frames.height), static_cast<float>(m_effect_width), static_cast<float>(m_effect_img.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}

Standing_NPC::Standing_NPC(Tilemap* map, const NPC_Data & npc_data)
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
  m_interact_script = npc_data.m_interact_script;
  m_image_name = npc_data.m_img_name;
  m_touch_script = npc_data.m_touch_script;
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
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);

  m_x = map->get_tile_foot_x(m_tile_x);
  m_y = map->get_tile_foot_y(m_tile_y);

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

void Standing_NPC::stand_update(Tilemap* map){}

Strolling_NPC::Strolling_NPC(Tilemap* map, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_move_speed = HERO_VELOCITY;
  m_id = npc_data.m_id;
  m_type = "Strolling NPC";
  m_animation_list = npc_data.m_animation_list;
  m_show_effect = npc_data.m_show_effect;
  m_interact_script = npc_data.m_interact_script;
  m_image_name = npc_data.m_img_name;
  m_touch_script = npc_data.m_touch_script;
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
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);

  m_x = map->get_tile_foot_x(m_tile_x);
  m_y = map->get_tile_foot_y(m_tile_y);

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

  m_frame_count = rand() % (300 - 60) + 60;
}

void Strolling_NPC::stand_update(Tilemap* map)
{
  if(m_vx > .001 || m_vy > .001 || m_vx < -.001 || m_vy < -.001)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      m_x = map->get_tile_foot_x(m_tile_x);

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

      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      m_x = map->get_tile_foot_x(m_tile_x);

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

      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      m_y = map->get_tile_foot_y(m_tile_y);

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

      m_frame_count = rand() % (300 - 60) + 60;
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      m_y = map->get_tile_foot_y(m_tile_y);

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
        if(map->is_blocked(m_tile_x + 1, m_tile_y, m_layer, m_id) == false)
        {
          m_end_x = m_x + MAP_TILE_WIDTH;
          m_vx = HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_RIGHT);
          m_animation.set_loop(true);
          m_end_y = 0;
          m_vy = 0;
          m_facing_dir = Direction::Right;
        }
        else
        {
          turn(Direction::Right);
          m_frame_count = rand() % (300 - 60) + 60;
        }
      }
      if(direction == 1)
      {
        if(map->is_blocked(m_tile_x - 1, m_tile_y, m_layer, m_id) == false)
        {
          m_end_x = m_x - MAP_TILE_WIDTH;
          m_vx = -HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_LEFT);
          m_animation.set_loop(true);
          m_end_y = 0;
          m_vy = 0;
          m_facing_dir = Direction::Left;
        }
        else
        {
          turn(Direction::Left);
          m_frame_count = rand() % (300 - 60) + 60;
        }
      }
      if(direction == 2)
      {
        if(map->is_blocked(m_tile_x, m_tile_y - 1, m_layer, m_id) == false)
        {
          m_end_y = m_y - map->get_tile_height();
          m_vy = -HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_UP);
          m_animation.set_loop(true);
          m_end_x = 0;
          m_vx = 0;
          m_facing_dir = Direction::Up;
        }
        else
        {
          turn(Direction::Up);
          m_frame_count = rand() % (300 - 60) + 60;
        }
      }
      if(direction == 3)
      {
        if(map->is_blocked(m_tile_x, m_tile_y + 1, m_layer, m_id) == false)
        {
          m_end_y = m_y + map->get_tile_height();
          m_vy = HERO_VELOCITY;
          m_animation.set_frames(HERO_ANIM_DOWN);
          m_animation.set_loop(true);
          m_end_x = 0;
          m_vx = 0;
          m_facing_dir = Direction::Down;
        }
        else
        {
          turn(Direction::Down);
          m_frame_count = rand() % (300 - 60) + 60;
        }
      }
    }
  }
}

Path_NPC::Path_NPC(Tilemap* map, const NPC_Data & npc_data)
{
  m_layer = npc_data.m_layer;
  m_width = npc_data.m_width;
  m_tile_x = npc_data.m_tile_x;
  m_tile_y = npc_data.m_tile_y;
  m_facing_dir = npc_data.m_facing_dir;
  m_move_speed = HERO_VELOCITY;
  m_id = npc_data.m_id;
  m_type = "Path NPC";
  m_animation_list = npc_data.m_animation_list;
  m_show_effect = npc_data.m_show_effect;
  m_image_name = npc_data.m_img_name;
  m_touch_script = npc_data.m_touch_script;
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
    m_animation = Animation(m_animation_list[3], m_animation_list[3].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Right)
  {
    m_animation = Animation(m_animation_list[2], m_animation_list[2].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Down)
  {
    m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  if(m_facing_dir == Direction::Left)
  {
    m_animation = Animation(m_animation_list[1], m_animation_list[1].size() - 1, false, HERO_ANIMATION_SPEED);
  }
  Image image2{LoadImageFromMemory(".png", npc_data.m_img_data, npc_data.m_img_size)};
  m_frames = LoadTextureFromImage(image2);
  UnloadImage(image2);

  m_x = map->get_tile_foot_x(m_tile_x);
  m_y = map->get_tile_foot_y(m_tile_y);

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

void Path_NPC::stand_update(Tilemap* map)
{
  if(m_vx > .001 || m_vy > .001 || m_vx < -.001 || m_vy < -.001)
  {
    m_x += m_vx;
    m_y += m_vy;

    if(m_vx > 0 && m_x > m_end_x)
    {
      ++m_tile_x;
      m_x = map->get_tile_foot_x(m_tile_x);
      set_next_path(map);
    }
    if(m_vx < 0 && m_x < m_end_x)
    {
      --m_tile_x;
      m_x = map->get_tile_foot_x(m_tile_x);
      set_next_path(map);
    }
    if(m_vy > 0 && m_y > m_end_y)
    {
      ++m_tile_y;
      m_y = map->get_tile_foot_y(m_tile_y);
      set_next_path(map);
    }
    if(m_vy < 0 && m_y < m_end_y)
    {
      --m_tile_y;
      m_y = map->get_tile_foot_y(m_tile_y);
      set_next_path(map);
    }
  }
}

void Path_NPC::set_path(const long & path_index)
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

bool Path_NPC::path_finished() const
{
  return m_path == -1;
}

void Path_NPC::set_next_path(Tilemap* map)
{
  if(m_path_index < static_cast<long>(m_paths[m_path].size()))
  {
    Direction direction{m_paths[m_path][m_path_index]};

    if(direction == Direction::Right)
    {
      m_end_x = m_x + MAP_TILE_WIDTH;
      m_vx = HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_RIGHT);
      m_animation.set_loop(true);
      m_end_y = 0;
      m_vy = 0;
      ++m_path_index;
    }
    if(direction == Direction::Left)
    {
      m_end_x = m_x - MAP_TILE_WIDTH;
      m_vx = -HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_LEFT);
      m_animation.set_loop(true);
      m_end_y = 0;
      m_vy = 0;
      ++m_path_index;
    }
    if(direction == Direction::Up)
    {
      m_end_y = m_y - map->get_tile_height();
      m_vy = -HERO_VELOCITY;
      m_animation.set_frames(HERO_ANIM_UP);
      m_animation.set_loop(true);
      m_end_x = 0;
      m_vx = 0;
      ++m_path_index;
    }
    if(direction == Direction::Down)
    {
      m_end_y = m_y + map->get_tile_height();
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
}
