#include "Main.h"
#include "Input_Wrapper.h"

void Input_Wrapper::poll()
{
  if(IsKeyPressed(KEY_Z) == true)
  {
    m_a_pressed = true;
  }
  if(IsKeyPressed(KEY_X) == true)
  {
    m_b_pressed = true;
  }
  if(IsKeyPressed(KEY_S) == true)
  {
    m_x_pressed = true;
  }
  if(IsKeyPressed(KEY_A) == true)
  {
    m_y_pressed = true;
  }
  if(IsKeyPressed(KEY_W) == true)
  {
    m_r_pressed = true;
  }
  if(IsKeyPressed(KEY_Q) == true)
  {
    m_l_pressed = true;
  }
  if(IsKeyPressed(KEY_UP) == true)
  {
    m_up_pressed = true;
  }
  if(IsKeyPressed(KEY_DOWN) == true)
  {
    m_down_pressed = true;
  }
  if(IsKeyPressed(KEY_LEFT) == true)
  {
    m_left_pressed = true;
  }
  if(IsKeyPressed(KEY_RIGHT) == true)
  {
    m_right_pressed = true;
  }

  if(IsKeyDown(KEY_Z) == true)
  {
    m_a_held = true;
  }
  if(IsKeyDown(KEY_X) == true)
  {
    m_b_held = true;
  }
  if(IsKeyDown(KEY_S) == true)
  {
    m_x_held = true;
  }
  if(IsKeyDown(KEY_A) == true)
  {
    m_y_held = true;
  }
  if(IsKeyDown(KEY_W) == true)
  {
    m_r_held = true;
  }
  if(IsKeyDown(KEY_Q) == true)
  {
    m_l_held = true;
  }
  if(IsKeyDown(KEY_UP) == true)
  {
    m_up_held = true;
  }
  if(IsKeyDown(KEY_DOWN) == true)
  {
    m_down_held = true;
  }
  if(IsKeyDown(KEY_LEFT) == true)
  {
    m_left_held = true;
  }
  if(IsKeyDown(KEY_RIGHT) == true)
  {
    m_right_held = true;
  }

  if(IsKeyUp(KEY_Z) == true)
  {
    m_a_held = false;
  }
  if(IsKeyUp(KEY_X) == true)
  {
    m_b_held = false;
  }
  if(IsKeyUp(KEY_S) == true)
  {
    m_x_held = false;
  }
  if(IsKeyUp(KEY_A) == true)
  {
    m_y_held = false;
  }
  if(IsKeyUp(KEY_W) == true)
  {
    m_r_held = false;
  }
  if(IsKeyUp(KEY_Q) == true)
  {
    m_l_held = false;
  }
  if(IsKeyUp(KEY_UP) == true)
  {
    m_up_held = false;
  }
  if(IsKeyUp(KEY_DOWN) == true)
  {
    m_down_held = false;
  }
  if(IsKeyUp(KEY_LEFT) == true)
  {
    m_left_held = false;
  }
  if(IsKeyUp(KEY_RIGHT) == true)
  {
    m_right_held = false;
  }
}

void Input_Wrapper::finish()
{
  m_a_pressed = false;
  m_b_pressed = false;
  m_x_pressed = false;
  m_y_pressed = false;
  m_l_pressed = false;
  m_r_pressed = false;
  m_up_pressed = false;
  m_down_pressed = false;
  m_left_pressed = false;
  m_right_pressed = false;
}

bool Input_Wrapper::A_button_pressed()
{
  bool ret{m_a_pressed};
  if(m_a_pressed == true)
  {
    m_a_pressed = false;
  }
  return ret;
}
bool Input_Wrapper::A_button_held() const{return m_a_held;}
bool Input_Wrapper::B_button_pressed(){bool ret{m_b_pressed}; if(m_b_pressed == true){m_b_pressed = false;} return ret;}
bool Input_Wrapper::B_button_held() const{return m_b_held;}
bool Input_Wrapper::X_button_pressed(){bool ret{m_x_pressed}; if(m_x_pressed == true){m_x_pressed = false;} return ret;}
bool Input_Wrapper::X_button_held() const{return m_x_held;}
bool Input_Wrapper::Y_button_pressed(){bool ret{m_y_pressed}; if(m_y_pressed == true){m_y_pressed = false;} return ret;}
bool Input_Wrapper::Y_button_held() const{return m_y_held;}
bool Input_Wrapper::L_button_pressed(){bool ret{m_l_pressed}; if(m_l_pressed == true){m_l_pressed = false;} return ret;}
bool Input_Wrapper::L_button_held() const{return m_l_held;}
bool Input_Wrapper::R_button_pressed(){bool ret{m_r_pressed}; if(m_r_pressed == true){m_r_pressed = false;} return ret;}
bool Input_Wrapper::R_button_held() const{return m_r_held;}
bool Input_Wrapper::up_button_pressed(){bool ret{m_up_pressed}; if(m_up_pressed == true){m_up_pressed = false;} return ret;}
bool Input_Wrapper::up_button_held() const{return m_up_held;}
bool Input_Wrapper::down_button_pressed(){bool ret{m_down_pressed}; if(m_down_pressed == true){m_down_pressed = false;} return ret;}
bool Input_Wrapper::down_button_held() const{return m_down_held;}
bool Input_Wrapper::left_button_pressed(){bool ret{m_left_pressed}; if(m_left_pressed == true){m_left_pressed = false;} return ret;}
bool Input_Wrapper::left_button_held() const{return m_left_held;}
bool Input_Wrapper::right_button_pressed(){bool ret{m_right_pressed}; if(m_right_pressed == true){m_right_pressed = false;} return ret;}
bool Input_Wrapper::right_button_held() const{return m_right_held;}
