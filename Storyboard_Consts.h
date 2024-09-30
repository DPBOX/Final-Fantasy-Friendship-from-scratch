#ifndef STORYBOARD_CONSTS
#define STORYBOARD_CONSTS

const Scr DUMMY_SCRIPT{};
/*
const Scr INTRO
{{
  {{{Script_Op::Black_Screen}}},
  {{{Script_Op::Add_Sound, Add_Sound_Params{DOOR_BREAK_SOUND}}}},
  {{{Script_Op::Add_Sound, Add_Sound_Params{BELL_SOUND}}}},
  {{{Script_Op::Add_Music, Add_Music_Script_Params{RAIN_MUSIC}}}},
  {{{Script_Op::Add_Music, Add_Music_Script_Params{WAGON_MUSIC}}}},
  {{{Script_Op::Add_Music, Add_Music_Script_Params{WIND_MUSIC}}}},
  {{{Script_Op::Set_Music_Volume, Change_Music_Volume_Params{"Rain", 0}}}},
  {{{Script_Op::Set_Music_Volume, Change_Music_Volume_Params{"Wagon", 0}}}},
  {{{Script_Op::Set_Music_Volume, Change_Music_Volume_Params{"Wind", 0}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Place", "Village of Sontos", 1, SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Time", "Midnight", 0, SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2 + FONT_HEADING_HEIGHT}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Time Passes", "Two days later...", 1, SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Dungeon", "Unknown Dungeon", 1, SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2}}}},
  {{
    {Script_Op::Fade_In_Music, Fade_Params{"Rain", 3}},
    {Script_Op::Fade_In_Caption, Fade_Params{"Place", 2}},
    {Script_Op::Fade_In_Caption, Fade_Params{"Time", 2}}
  }},
  {{{Script_Op::Wait, Wait_Params{120}}}},
  {{
    {Script_Op::Fade_Out_Caption, Fade_Params{"Place", 2}},
    {Script_Op::Fade_Out_Caption, Fade_Params{"Time", 2}}
  }},
  {{{Script_Op::Fade_In_Screen, Fade_Screen_Params{2}}}},
  {{{Script_Op::Wait, Wait_Params{120}}}},
  {{{Script_Op::Fade_Out_Screen, Fade_Screen_Params{2}}}},
  {{{Script_Op::Show_NPC, Name_Params{"Sontos House Guard"}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Play_Sound, Name_Params{"Door Break"}}}},
  {{
    {Script_Op::Fade_In_Screen, Fade_Screen_Params{2}},
    {Script_Op::Set_NPC_Path, Set_NPC_Path_Params{"Sontos House Guard", 0}}
  }},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Say, Say_Params{"Sontos House Guard", "Found you!", 8, -40}}}},
  {{{Script_Op::Say, Say_Params{"Sontos House Guard", "You're coming with me!", 8, -40}}}},
  {{{Script_Op::Fade_Out_Screen, Fade_Screen_Params{2}}}},
  {{{Script_Op::Play_Sound, Name_Params{"Bell"}}}},
  {{{Script_Op::Wait, Wait_Params{150}}}},
  {{{Script_Op::Play_Sound, Name_Params{"Bell"}}}},
  {{{Script_Op::Fade_Out_Sound, Fade_Params{"Bell", 1}}}},
  {{{Script_Op::Fade_Out_Music, Fade_Params{"Rain", 1}}}},
  {{
    {Script_Op::Fade_In_Music, Fade_Params{"Wagon", 2}},
    {Script_Op::Fade_In_Music, Fade_Params{"Wind", 2}},
    {Script_Op::Wait, Wait_Params{180}}
  }},
  {{{Script_Op::Fade_In_Caption, Fade_Params{"Time Passes", 2}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Fade_Out_Caption, Fade_Params{"Time Passes", 2}}}},
  {{
    {Script_Op::Fade_Out_Music, Fade_Params{"Wagon", 1}},
    {Script_Op::Fade_Out_Music, Fade_Params{"Wind", 1}},
    {Script_Op::Wait, Wait_Params{120}}
  }},
  {{{Script_Op::Remove_All_Music}}},
  {{{Script_Op::Fade_In_Caption, Fade_Params{"Dungeon", 2}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Fade_Out_Caption, Fade_Params{"Dungeon", 2}}}},
  {{{Script_Op::Change_Map, Name_Params{"Jail Map"}}}},
  {{{Script_Op::Fade_In_Screen, Fade_Screen_Params{2}}}},
  {{{Script_Op::Wait, Wait_Params{30}}}},
  {{{Script_Op::Say, Say_Params{"Hero", "Where am I?", 8, -40}}}}
}};
*/
#endif