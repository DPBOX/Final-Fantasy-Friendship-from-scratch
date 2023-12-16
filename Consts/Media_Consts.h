#ifndef MEDIA_CONSTS_H
#define MEDIA_CONSTS_H

const Sound_Params CURSOR_SOUND{"Cursor", binary_Sound_cursor_wav_start, reinterpret_cast<long>(&binary_Sound_cursor_wav_size), .75};
const Sound_Params CONFIRM_SOUND{"Confirm", binary_Sound_confirm_wav_start, reinterpret_cast<long>(&binary_Sound_confirm_wav_size)};
const Sound_Params BACK_SOUND{"Back", binary_Sound_back_wav_start, reinterpret_cast<long>(&binary_Sound_back_wav_size)};
const Sound_Params BUZZER_SOUND{"Buzzer", binary_Sound_buzzer_wav_start, reinterpret_cast<long>(&binary_Sound_buzzer_wav_size)};

#endif