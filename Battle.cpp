#include "Main.h"
#include "Battle.h"
#include "UI.h"
#include "Input_Wrapper.h"

void Battle_Event::reduce_count_down()
{
  if(m_count_down > 0)
  {
    --m_count_down;
  }
}

CETurn::CETurn(Battle_Character* owner, const World* const world, vector<Battle_Character*> party, vector<Battle_Character*> enemies)
{
  m_name = "CETurn";
  m_owner = owner;
  m_count_down = speed_to_time_points(owner->get_speed(world));
  m_party = party;
  m_enemies = enemies;
}

void CETurn::execute(priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> & queue, Battle_Event_Stack* state_stack)
{
  if(m_owner->is_ally() == true)
  {
    state_stack->create_new_combat_choice_state(m_owner, m_party, m_enemies);
  }
  else
  {
// skip enemy AI, we'll implement it later
  }
  m_finished = true;
}

bool Battle_Event_Queue::actor_has_event(Battle_Character* character) const
{
  if(m_current_event != nullptr && m_current_event->get_owner() == character)
  {
    return true;
  }
  priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> queue{m_queue};
  while(queue.empty() == false)
  {
    if(queue.top()->get_owner() == character)
    {
      return true;
    }
    queue.pop();
  }
  return false;
}

void Battle_Event_Queue::update(Battle_Event_Stack* state_stack)
{
  if(m_current_event != nullptr)
  {
    m_current_event->update();
    if(m_current_event->is_finished() == true)
    {
      delete m_current_event;
      m_current_event = nullptr;
      --mem;
    }
  }
  else if(empty() == true)
  {
    return;
  }
  else
  {
    if(m_queue.top()->get_count_down() == 0 || m_queue.top()->get_count_down() == -1)
    {
      m_current_event = m_queue.top();
      m_queue.pop();
      m_current_event->execute(m_queue, state_stack);
    }

    priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> queue{};
    while(m_queue.empty() == false)
    {
      Battle_Event* e{m_queue.top()};
      e->reduce_count_down();
      queue.push(e);
      m_queue.pop();
    }
    m_queue = queue;
  }
}

void Battle_Event_Queue::clear()
{
  if(m_current_event != nullptr)
  {
    delete m_current_event;
    m_current_event = nullptr;
    --mem;
  }
  while(m_queue.empty() == false)
  {
    Battle_Event* e{m_queue.top()};
    m_queue.pop();
    delete e;
    --mem;
    e = nullptr;
  }
}

long Battle_Event_Queue::get_character_atb_position(const string & name) const
{
  priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> queue{m_queue};
  while(queue.empty() == false)
  {
    if(queue.top()->get_owner()->get_name() == name && queue.top()->get_name() == "CETurn")
    {
      long time_points{queue.top()->get_count_down()};
      return -time_points;
    }
    queue.pop();
  }
  return 0;
}

Battle_Ally::Battle_Ally(const string & name, const long & list_index, const long & animation_speed, const vector<vector<long>> & animation_list)
{
  m_ally = true;
  m_name = name;
  m_list_index = list_index;
  m_animation_list = animation_list;
  m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, true, animation_speed);

  m_hp = new Progress_Bar{"Progress Bar Green", BATTLE_PROGRESS_BAR_LEGNTH};
  m_mp = new Progress_Bar{"Progress Bar Blue", BATTLE_PROGRESS_BAR_LEGNTH};
  m_atb = new Progress_Bar{"Progress Bar Orange", BATTLE_PROGRESS_BAR_LEGNTH};
  m_soulbreak = new Progress_Bar{"Progress Bar Red", BATTLE_PROGRESS_BAR_LEGNTH};
  ++mem;
  ++mem;
  ++mem;
  ++mem;

  Image image{LoadImageFromMemory(".png", BATTLE_ARROW_ICON_IMAGE.m_data, BATTLE_ARROW_ICON_IMAGE.m_size)};
  m_battle_arrow_icon_texture = LoadTextureFromImage(image);
  UnloadImage(image);
}

Battle_Ally::~Battle_Ally()
{
  delete m_hp;
  delete m_mp;
  delete m_atb;
  delete m_soulbreak;
  m_hp = nullptr;
  m_mp = nullptr;
  m_atb = nullptr;
  m_soulbreak = nullptr;
  --mem;
  --mem;
  --mem;
  --mem;
  UnloadTexture(m_battle_arrow_icon_texture);
}

void Battle_Ally::update(World* world, const Battle_Event_Queue* const battle_event_queue)
{
  m_animation.update();
  m_font_animation.update();
  m_arrow_icon_animation.update();
  m_hp->set_value(world->get_party_member_unmodified_stat(m_name, "HP"), world->get_party_member_stat(m_name, "Max HP"));
  m_mp->set_value(world->get_party_member_unmodified_stat(m_name, "MP"), world->get_party_member_stat(m_name, "Max MP"));
  long time_points{speed_to_time_points(world->get_party_member_stat(m_name, "Speed"))};
  m_atb->set_value(battle_event_queue->get_character_atb_position(m_name), 0, -time_points);
}

void Battle_Ally::render(const World* const world) const
{
  long x{0};
  long y{0};
  switch(m_list_index)
  {
    case 0:
      x = BATTLE_ALLY_1_POSITION_X;
      y = BATTLE_ALLY_1_POSITION_Y;
      break;
    case 1:
      x = BATTLE_ALLY_2_POSITION_X;
      y = BATTLE_ALLY_2_POSITION_Y;
      break;
    case 2:
      x = BATTLE_ALLY_3_POSITION_X;
      y = BATTLE_ALLY_3_POSITION_Y;
      break;
    default:
      crash("Error: More than the maximum of 3 party members detected.");
      break;
  }
  world->render_party_member_sprite(m_name, x, y, m_animation.get_frame(), true);
/*  world->render_text("Text", world->get_party_member_name(m_list_index), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * m_list_index);
  world->render_text("Text", "HP    " + to_string(world->get_party_member_unmodified_stat(m_name, "HP")) + "/" + to_string(world->get_party_member_stat(m_name, "Max HP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 2, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * m_list_index + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "MP    " + to_string(world->get_party_member_unmodified_stat(m_name, "MP")) + "/" + to_string(world->get_party_member_stat(m_name, "Max MP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 3, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * m_list_index + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
*/  if(m_animations_enabled == true && m_font_animation.is_visible() == true)
  {
/*    world->render_text("Gray", world->get_party_member_name(m_list_index), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * m_list_index);
*/
  }
/*  m_hp->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 2, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * (m_list_index + 1) + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_mp->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 3, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * (m_list_index + 1) + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_atb->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 4, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * m_list_index - PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_soulbreak->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 4, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2) + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * (m_list_index + 1) + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
*/
  if(m_render_arrow == true)
  {
    DrawTexturePro(m_battle_arrow_icon_texture, Rectangle{static_cast<float>(m_arrow_icon_animation.get_frame() * BATTLE_ARROW_ICON_WIDTH), 0, BATTLE_ARROW_ICON_WIDTH, static_cast<float>(m_battle_arrow_icon_texture.height)}, Rectangle{static_cast<float>(x + BATTLE_ARROW_ICON_PADDING_X), static_cast<float>(y - BATTLE_ARROW_ICON_PADDING_Y), BATTLE_ARROW_ICON_WIDTH, static_cast<float>(m_battle_arrow_icon_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}

Battle_Enemy::Battle_Enemy(const Enemy_Info & enemy, const long & list_index, const long & animation_speed)
{
  m_ally = false;
  m_name = enemy.m_name;
  m_list_index = list_index;
  m_animation_list = enemy.m_animation_list;
  m_animation = Animation(m_animation_list[0], m_animation_list[0].size() - 1, true, animation_speed);

  m_stats = Stats{enemy.m_stats};
  m_sprite_width = enemy.m_sprite_width;

  Image image3{LoadImageFromMemory(".png", enemy.m_sprite_data, enemy.m_sprite_size)};
  m_sprite = LoadTextureFromImage(image3);
  UnloadImage(image3);

  Image image{LoadImageFromMemory(".png", BATTLE_ARROW_ICON_IMAGE.m_data, BATTLE_ARROW_ICON_IMAGE.m_size)};
  m_battle_arrow_icon_texture = LoadTextureFromImage(image);
  UnloadImage(image);
}

void Battle_Enemy::update(World* world, const Battle_Event_Queue* const battle_event_queue)
{
  m_animation.update();
  m_arrow_icon_animation.update();
}

void Battle_Enemy::render(const World* const world) const
{
  long x{0};
  long y{0};
  switch(m_list_index)
  {
    case 0:
      x = BATTLE_ENEMY_1_POSITION_X;
      y = BATTLE_ENEMY_1_POSITION_Y;
      break;
    case 1:
      x = BATTLE_ENEMY_2_POSITION_X;
      y = BATTLE_ENEMY_2_POSITION_Y;
      break;
    case 2:
      x = BATTLE_ENEMY_3_POSITION_X;
      y = BATTLE_ENEMY_3_POSITION_Y;
      break;
    case 3:
      x = BATTLE_ENEMY_4_POSITION_X;
      y = BATTLE_ENEMY_4_POSITION_Y;
      break;
    case 4:
      x = BATTLE_ENEMY_5_POSITION_X;
      y = BATTLE_ENEMY_5_POSITION_Y;
      break;
    case 5:
      x = BATTLE_ENEMY_6_POSITION_X;
      y = BATTLE_ENEMY_6_POSITION_Y;
      break;
    default:
      crash("Error: More than the maximum of 6 enemies detected.");
      break;
  }
  DrawTexturePro(m_sprite, Rectangle{static_cast<float>(m_animation.get_frame() * m_sprite_width), 0, static_cast<float>(m_sprite_width), static_cast<float>(m_sprite.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_sprite_width), static_cast<float>(m_sprite.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  if(m_render_arrow == true)
  {
    DrawTexturePro(m_battle_arrow_icon_texture, Rectangle{static_cast<float>(m_arrow_icon_animation.get_frame() * BATTLE_ARROW_ICON_WIDTH), 0, BATTLE_ARROW_ICON_WIDTH, static_cast<float>(m_battle_arrow_icon_texture.height)}, Rectangle{static_cast<float>(x + m_sprite_width / 2 - BATTLE_ARROW_ICON_WIDTH / 2), static_cast<float>(y - BATTLE_ARROW_ICON_ENEMY_PADDING_Y), BATTLE_ARROW_ICON_WIDTH, static_cast<float>(m_battle_arrow_icon_texture.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  }
}

long Battle_Enemy::get_speed(const World* const world) const
{
  return m_stats.get_stat("Speed");
}

long Battle_Enemy::get_hp(const World* const world) const
{
  return m_stats.get_unmodified_stat("HP");
}

Battle_Event_Stack::~Battle_Event_Stack()
{
  if(m_next_state != nullptr)
  {
    delete m_next_state;
    --mem;
    m_next_state = nullptr;
  }
  if(m_next_state2 != nullptr)
  {
    delete m_next_state2;
    --mem;
    m_next_state2 = nullptr;
  }
  for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
  {
    delete m_states[i];
    m_states[i] = nullptr;
    --mem;
  }
}

void Battle_Event_Stack::set_next_state(Battle_Event_Stack_State* new_state)
{
  m_next_state = new_state;
}

void Battle_Event_Stack::set_next_state2(Battle_Event_Stack_State* new_state)
{
  m_next_state2 = new_state;
}

void Battle_Event_Stack::pop_state()
{
  m_pop = true;
}

void Battle_Event_Stack::pop_all()
{
  m_pop_all = true;
}

void Battle_Event_Stack::change_state()
{
  if(m_pop_all == true)
  {
    m_pop_all = false;
    m_pop = false;
    if(m_next_state != nullptr)
    {
      delete m_next_state;
      --mem;
      m_next_state = nullptr;
    }
    if(m_next_state2 != nullptr)
    {
      delete m_next_state2;
      --mem;
      m_next_state2 = nullptr;
    }
    while(m_states.empty() == false)
    {
      delete m_states[m_states.size() - 1];
      m_states[m_states.size() - 1] = nullptr;
      --mem;
      m_states.pop_back();
    }
    return;
  }

  if(m_next_state == nullptr && m_pop == true)
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
  }

  if(m_next_state != nullptr && m_pop == true)
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
    m_states.push_back(m_next_state);
  }

  if(m_next_state != nullptr && m_pop == false)
  {
    m_states.push_back(m_next_state);
    if(m_next_state2 != nullptr && m_pop == false)
    {
      m_states.push_back(m_next_state2);
    }
    m_next_state2 = nullptr;
  }
  m_next_state = nullptr;
  m_pop = false;
}

bool Battle_Event_Stack::empty()
{
  return m_states.empty();
}

void Battle_Event_Stack::update(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input)
{
  if(m_states.empty() == false)
  {
    m_states[m_states.size() - 1]->update_top(state_manager, world, input);
    for(long i{static_cast<long>(m_states.size()) - 2}; i >= 0; --i)
    {
      m_states[i]->update();
    }
  }
}

void Battle_Event_Stack::render(const World* const world) const
{
  if(m_states.empty() == false)
  {
    for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
    {
      m_states[i]->render(world);
    }
  }
}

string Battle_Event_Stack_State::get_name() const
{
  return m_name;
}

void Battle_Event_Stack::create_new_combat_choice_state(Battle_Character* owner, vector<Battle_Character*> party, vector<Battle_Character*> enemies)
{
  Battle_Event_Stack_State* e{new Combat_Choice_State{owner, party, enemies}};
  ++mem;
  m_states.push_back(e);
}

void Battle_Event_Stack::create_new_combat_target_state(Battle_Character* owner, const Combat_Target_Mode & target_mode, vector<Battle_Character*> party, vector<Battle_Character*> enemies)
{
  Battle_Event_Stack_State* e{new Combat_Target_State{owner, target_mode, party, enemies}};
  ++mem;
  m_states.push_back(e);
}

Combat_Choice_State::Combat_Choice_State(Battle_Character* owner, vector<Battle_Character*> party, vector<Battle_Character*> enemies)
{
  m_character = owner;
  m_party = party;
  m_enemies = enemies;
  m_commands = new Selection(NUM_BATTLE_COMMAND_CHOICES, 1, NUM_BATTLE_COMMAND_CHOICES, NUM_BATTLE_COMMAND_CHOICES);
/*  m_commands_renderer = new Selection_Renderer(m_commands, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 5 + TEXTBOX_PADDING_SHORT), BATTLE_INFO_SECTION_WIDTH);
  m_panel = new Panel(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 5 + TEXTBOX_PADDING_SHORT * 2), BATTLE_INFO_SECTION_WIDTH, TEXT_FONT_HEIGHT * 5 + TEXTBOX_PADDING_SHORT * 2);
*/  m_name = "Combat Choice";
  ++mem;
  ++mem;
  ++mem;
  g_sound_player->play_global_sound("ATB");
  m_character->enable_animations();
}

Combat_Choice_State::~Combat_Choice_State()
{
  delete m_commands;
  m_commands = nullptr;
  delete m_commands_renderer;
  m_commands_renderer = nullptr;
  delete m_panel;
  m_panel = nullptr;
  --mem;
  --mem;
  --mem;
  m_character->disable_animations();
}

void Combat_Choice_State::update_top(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input)
{
  m_character->enable_render_arrow();
/*  m_commands->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 5 + TEXTBOX_PADDING_SHORT), BATTLE_INFO_SECTION_WIDTH);
*/  if(input->A_button_pressed() == true)
  {
    g_sound_player->play_global_sound("Confirm");
    if(m_commands->get_highlighted_item() == 0)
    {
      state_manager->create_new_combat_target_state(m_character, Combat_Target_Mode::Anyone, m_party, m_enemies);
    }
    if(m_commands->get_highlighted_item() == 1)
    {
      state_manager->create_new_combat_target_state(m_character, Combat_Target_Mode::Single_All_Foes, m_party, m_enemies);
    }
    if(m_commands->get_highlighted_item() == 2)
    {
      state_manager->create_new_combat_target_state(m_character, Combat_Target_Mode::Single_All_Allies, m_party, m_enemies);
    }
    if(m_commands->get_highlighted_item() == 3)
    {
      state_manager->create_new_combat_target_state(m_character, Combat_Target_Mode::User, m_party, m_enemies);
    }
    if(m_commands->get_highlighted_item() == 4)
    {
      state_manager->create_new_combat_target_state(m_character, Combat_Target_Mode::All_Allies, m_party, m_enemies);
    }
  }
}

void Combat_Choice_State::render(const World* const world) const
{
  m_panel->render(world);
  m_commands_renderer->render(BATTLE_COMMAND_CHOICES, world);
}

Combat_Target_State::Combat_Target_State(Battle_Character* owner, const Combat_Target_Mode & target_mode, vector<Battle_Character*> party, vector<Battle_Character*> enemies)
{
  m_character = owner;
  m_target_mode = target_mode;
  m_party = party;
  m_enemies = enemies;

  long num_choices{1};
  if(target_mode == Combat_Target_Mode::Single_Foe)
  {
    num_choices = enemies.size();
  }
  if(target_mode == Combat_Target_Mode::Single_All_Foes)
  {
    num_choices = enemies.size() + 1;
  }
  if(target_mode == Combat_Target_Mode::Single_Ally)
  {
    num_choices = party.size();
  }
  if(target_mode == Combat_Target_Mode::Single_All_Allies)
  {
    num_choices = party.size() + 1;
  }
  if(target_mode == Combat_Target_Mode::Anyone)
  {
    num_choices = enemies.size() + party.size();
  }

  m_commands = new Selection(num_choices, 1, num_choices, num_choices);
/*  m_commands_renderer = new Selection_Renderer(m_commands, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 2, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * num_choices + TEXTBOX_PADDING_SHORT), BATTLE_INFO_SECTION_WIDTH);
  m_panel = new Panel(TEXTBOX_PADDING_SCREEN + BATTLE_INFO_SECTION_WIDTH * 2, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * num_choices + TEXTBOX_PADDING_SHORT * 2), BATTLE_INFO_SECTION_WIDTH, TEXT_FONT_HEIGHT * num_choices + TEXTBOX_PADDING_SHORT * 2);
*/  m_name = "Combat Target";
  ++mem;
  ++mem;
  ++mem;
  m_num_choices = num_choices;
}

Combat_Target_State::~Combat_Target_State()
{
  delete m_commands;
  m_commands = nullptr;
  delete m_commands_renderer;
  m_commands_renderer = nullptr;
  delete m_panel;
  m_panel = nullptr;
  --mem;
  --mem;
  --mem;
}

void Combat_Target_State::update_top(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input)
{
/*  m_commands->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + BATTLE_INFO_SECTION_WIDTH * 2, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * m_num_choices + TEXTBOX_PADDING_SHORT), BATTLE_INFO_SECTION_WIDTH);
*/
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    m_enemies[i]->disable_render_arrow();
  }
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    m_party[i]->disable_render_arrow();
  }

  if(m_target_mode == Combat_Target_Mode::Single_Foe)
  {
    m_enemies[m_commands->get_highlighted_item()]->enable_render_arrow();
  }
  if(m_target_mode == Combat_Target_Mode::All_Foes)
  {
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      m_enemies[i]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::Single_All_Foes)
  {
    if(m_commands->get_highlighted_item() == 0)
    {
      for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
      {
        m_enemies[i]->enable_render_arrow();
      }
    }
    else
    {
      m_enemies[m_commands->get_highlighted_item() - 1]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::Single_Ally)
  {
    m_party[m_commands->get_highlighted_item()]->enable_render_arrow();
  }
  if(m_target_mode == Combat_Target_Mode::All_Allies)
  {
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      m_party[i]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::Single_All_Allies)
  {
    if(m_commands->get_highlighted_item() == 0)
    {
      for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
      {
        m_party[i]->enable_render_arrow();
      }
    }
    else
    {
      m_party[m_commands->get_highlighted_item() - 1]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::Anyone)
  {
    if(m_commands->get_highlighted_item() < static_cast<long>(m_enemies.size()))
    {
      m_enemies[m_commands->get_highlighted_item()]->enable_render_arrow();
    }
    else
    {
      m_party[m_commands->get_highlighted_item() - m_enemies.size()]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::Everyone)
  {
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      m_enemies[i]->enable_render_arrow();
    }
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      m_party[i]->enable_render_arrow();
    }
  }
  if(m_target_mode == Combat_Target_Mode::User)
  {
    m_character->enable_render_arrow();
  }

  if(input->A_button_pressed() == true)
  {
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      m_enemies[i]->disable_render_arrow();
    }
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      m_party[i]->disable_render_arrow();
    }
    g_sound_player->play_global_sound("Confirm");
    if(m_commands->get_highlighted_item() == 0)
    {
      state_manager->pop_all();
    }
  }
  if(input->B_button_pressed() == true)
  {
    g_sound_player->play_global_sound("Back");
    state_manager->pop_state();
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      m_enemies[i]->disable_render_arrow();
    }
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      m_party[i]->disable_render_arrow();
    }
  }
}

void Combat_Target_State::render(const World* const world) const
{
  vector<string> target_choices;
  if(m_target_mode == Combat_Target_Mode::Single_Foe)
  {
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      target_choices.push_back(m_enemies[i]->get_name());
    }
  }
  if(m_target_mode == Combat_Target_Mode::All_Foes)
  {
    target_choices.push_back("All foes");
  }
  if(m_target_mode == Combat_Target_Mode::Single_All_Foes)
  {
    target_choices.push_back("All foes");
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      target_choices.push_back(m_enemies[i]->get_name());
    }
  }
  if(m_target_mode == Combat_Target_Mode::Single_Ally)
  {
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      target_choices.push_back(m_party[i]->get_name());
    }
  }
  if(m_target_mode == Combat_Target_Mode::All_Allies)
  {
    target_choices.push_back("All allies");
  }
  if(m_target_mode == Combat_Target_Mode::Single_All_Allies)
  {
    target_choices.push_back("All allies");
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      target_choices.push_back(m_party[i]->get_name());
    }
  }
  if(m_target_mode == Combat_Target_Mode::Anyone)
  {
    for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
    {
      target_choices.push_back(m_enemies[i]->get_name());
    }
    for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
    {
      target_choices.push_back(m_party[i]->get_name());
    }
  }
  if(m_target_mode == Combat_Target_Mode::Everyone)
  {
    target_choices.push_back("Everyone");
  }
  if(m_target_mode == Combat_Target_Mode::User)
  {
    target_choices.push_back(m_character->get_name());
  }

  m_panel->render(world);
  m_commands_renderer->render(target_choices, world);
}
