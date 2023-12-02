#ifndef PARTY_MEMBER_INFO_CONSTS_H
#define PARTY_MEMBER_INFO_CONSTS_H

const Player_Info TEMPEST_SHADOW_INFO{"Tempest", "Unicorn", "Battlemage", false, TEMPEST_SHADOW_BASE_STATS, binary_Image_avatar_png_start, reinterpret_cast<long>(&binary_Image_avatar_png_size), binary_Image_tempest_small_portrait_png_start, reinterpret_cast<long>(&binary_Image_tempest_small_portrait_png_size)};
const Player_Info NIGHTWISH_INFO{"Nightwish", "Thestral", "Lunar Duelist", true, NIGHTWISH_BASE_STATS, binary_Image_nightwish_portrait_png_start, reinterpret_cast<long>(&binary_Image_nightwish_portrait_png_size), binary_Image_nightwish_small_portrait_png_start, reinterpret_cast<long>(&binary_Image_nightwish_small_portrait_png_size)};
const Player_Info GALLUS_INFO{"Gallus", "Griffon", "Solar Fighter", true, GALLUS_BASE_STATS, binary_Image_gallus_portrait_png_start, reinterpret_cast<long>(&binary_Image_gallus_portrait_png_size), binary_Image_gallus_small_portrait_png_start, reinterpret_cast<long>(&binary_Image_gallus_small_portrait_png_size)};

#endif