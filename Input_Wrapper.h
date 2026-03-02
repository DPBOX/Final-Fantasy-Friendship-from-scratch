#ifndef INPUT_WRAPPER_H
#define INPUT_WRAPPER_H

class Input_Wrapper
{
  public:
    explicit Input_Wrapper(){}
    Input_Wrapper(const Input_Wrapper & obj) = delete;
    Input_Wrapper & operator =(const Input_Wrapper & obj) = delete;
    ~Input_Wrapper(){}

    void poll();
    void finish();

    bool A_button_pressed();
    bool A_button_held() const;
    bool B_button_pressed();
    bool B_button_held() const;
    bool X_button_pressed();
    bool X_button_held() const;
    bool Y_button_pressed();
    bool Y_button_held() const;
    bool L_button_pressed();
    bool L_button_held() const;
    bool R_button_pressed();
    bool R_button_held() const;
    bool up_button_pressed();
    bool up_button_held() const;
    bool down_button_pressed();
    bool down_button_held() const;
    bool left_button_pressed();
    bool left_button_held() const;
    bool right_button_pressed();
    bool right_button_held() const;

  private:
    bool m_a_pressed{false};
    bool m_a_held{false};
    bool m_b_pressed{false};
    bool m_b_held{false};
    bool m_x_pressed{false};
    bool m_x_held{false};
    bool m_y_pressed{false};
    bool m_y_held{false};
    bool m_l_pressed{false};
    bool m_l_held{false};
    bool m_r_pressed{false};
    bool m_r_held{false};
    bool m_up_pressed{false};
    bool m_up_held{false};
    bool m_down_pressed{false};
    bool m_down_held{false};
    bool m_left_pressed{false};
    bool m_left_held{false};
    bool m_right_pressed{false};
    bool m_right_held{false};
};

#endif
