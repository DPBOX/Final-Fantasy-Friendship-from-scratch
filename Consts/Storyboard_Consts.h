#ifndef STORYBOARD_CONSTS
#define STORYBOARD_CONSTS

const Scr DUMMY_SCRIPT{};

const Scr INTRO_SCRIPT
{{
  {{{Script_Op::Black_Screen}}},
  {{{Script_Op::Play_Music, Name_Params{"Intro 1"}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_1_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 1", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 1", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Once upon a time, there was a magical land called Equestria, ruled over by two princesses."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Their names were Princess Celestia and Princess Luna."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 1", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 1", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_2_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 2", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 2", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Born of the forces that governed their world, these two Alicorns wielded power over the sun, moon, and stars."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"It became their responsibility to keep the balance of day and night for all ponies."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 2", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 2", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_3_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 3", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 3", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"To Princess Celestia fell the duty of raising the sun to begin the morning,"}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 3", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 3", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_4_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 4", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 4", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"while her younger sister, Princess Luna, raised the moon at the end of the day."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 4", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 4", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_5_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 5", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 5", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Day and night, night and day, the two sisters maintained the balance of their world for millenia. Theirs seemed an ageless, peaceful rule, and their subjects adored them for it."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 5", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 5", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_6_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 6", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 6", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Yet it did not remain so forever. Little by little, a darkness crept into the heart of the younger Alicorn. Jealousy festered deep in Luna's soul."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 6", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 6", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_7_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 7", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 7", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"The Mare of Moon and Stars came to resent her place in the diarchy. She watched as ponies slept through the night she prepared so carefully and woke again to play in the dawn her sister Celestia brought."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 7", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 7", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_8_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 8", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 8", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Luna's stars glittered like diamonds. Her moon shone as the sky's own pearl. The blackness behind them, like velvet, captured their beauty for all to see."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Her little ponies slept through it all. In time, Luna forgot their love for her and saw only their love for the sun. Bitterness grew on her daily."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 8", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 8", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_9_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 9", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 9", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"The day came when she could bear it no longer. One day, before dawn, Luna refused to lower the moon to make room for Celestia's sun."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Celestia tried to reason with her beloved sister, but, to her dismay, found that the Lunar Princess's anger had passed the point of words."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 9", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 9", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 6", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 6", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Luna's jealousy had blinded her to the love of her subjects and the care of her sister. She perceived only disregard for the night she worked so hard to bring them."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Overcome by her selfishness and hate, the Mare of the Moon and Stars became a thing of darkness..."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 6", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 6", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Play_Music, Name_Params{"Intro 2"}}}},
  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_10_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 10", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 10", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"NIGHTMARE MOON!!"}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Nightmare Moon met her sister's words with violence. She vowed to shroud the world in eternal darkness. She almost succeeded."}}}},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{{Script_Op::Narrate, Name_Params{"Celestia wrested control of the heavens from her sister, delaying the Nightmare's rise to ultimate power. The strain of the battle and of her sister's betrayal left the Sun Princess numb with horror. The Nightmare she once called sister intended to imprison her forever."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 10", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 10", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 1", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 1", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Drained and defeated, Princess Celestia retreated to Canterlot. The weakened monarch put quill to paper to summon Equestria's last hope..."}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 1", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 1", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_11_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 11", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 11", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"The Elements of Harmony!"}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 11", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 11", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Play_Music, Name_Params{"Title Screen"}}}},
  {{{Script_Op::Add_Image, Add_Image_Params{&INTRO_12_IMAGE, SCREEN_HEIGHT / 4 * 3}}}},
  {{
    {Script_Op::Fade_In_Image, Fade_Params{"Intro 12", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 12", 2, 0}}
  }},
  {{{Script_Op::Narrate, Name_Params{"Only Twilight Sparkle and her five friends could find the Elements of Harmony and save Equestria from eternal night!"}}}},
  {{
    {Script_Op::Fade_Out_Image, Fade_Params{"Intro 12", 2}},
    {Script_Op::Scroll_Image_Y, Scroll_Params{"Intro 12", 2, SCREEN_HEIGHT / 4 * 3}}
  }},
  {{{Script_Op::Wait, Wait_Params{180}}}},

  {{{Script_Op::Play_Music, Name_Params{"Ponyville"}}}},
  {{{Script_Op::Wait, Wait_Params{180}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Place", "Ponyville", "Heading", SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2}}}},
  {{{Script_Op::Add_Caption, Add_Caption_Params{"Time", "Golden Oak Library", "Text", SCREEN_HEIGHT / 4 - INTRO_CAPTION_HEIGHT / 2 + FONT_HEADING_HEIGHT}}}},
  {{
    {Script_Op::Fade_In_Caption, Fade_Params{"Place", .25}},
    {Script_Op::Fade_In_Caption, Fade_Params{"Time", .25}}
  }},
  {{{Script_Op::Wait, Wait_Params{60}}}},
  {{
    {Script_Op::Fade_Out_Caption, Fade_Params{"Place", 1}},
    {Script_Op::Fade_Out_Caption, Fade_Params{"Time", 1}},
    {Script_Op::Fade_In_Screen, Fade_Screen_Params{1}}
  }},

  {{{Script_Op::Talk, Talk_Params{"What is it, Spike?", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"The Princess sent you a letter. It has the royal seal and everything.", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Oh? What does it say?", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Let's see...", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"\"Twilight Sparkle, my most faithful student. I don't have much more time. My sister, Luna, has betrayed us all. She plans to seal me away and cover all of Equestria in eternal night. She calls herself Nightmare Moon now. You and your friends must use the power of the Elements of Harmony to stop my sister and save Equestria.\"", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Those stains. Are those ... tears?", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Luna.... Spike, this is terrible! How could she do this? Her own sister....", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"This is impossible! Luna wouldn't do this! Princess Celestia's just pulling a prank, right?", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"You know that's not true, Spike. This is Princess Celestia's royal seal, and I can sense her magic all over it.", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"It's not a fake, and Princess Celestia wouldn't put a royal seal on a prank. She meant every word.", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"What are you going to do, Twilight?", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"I'm going to follow Celestia's orders. Where is everypony?", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"I heard Pinkie Pie say they'd be over at Rarity's house and business, Carousel Boutique. You could go check over there.", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"I'll go tell them what's happened. Watch the library while I'm gone.", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Okay. I will. Good luck, Twilight.", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Also, it looks like Celestia included a map of Equestria in her letter. You should take it.", "Spike", SPIKE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Talk, Talk_Params{"Thanks Spike.", "Twilight Sparkle", TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE}}}},
  {{{Script_Op::Add_Key_Item, Name_Params{"Map of Equestria"}}}},
  {{{Script_Op::Play_Sound, Name_Params{"Equip"}}}},
  {{{Script_Op::Say, Say_Params{"Hero", "You got a Map of Equestria.", 8, -40}}}},
}};

#endif
