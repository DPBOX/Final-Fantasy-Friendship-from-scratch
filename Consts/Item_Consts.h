#ifndef ITEM_CONSTS
#define ITEM_CONSTS

m_item_database = vector<Item*>
{
  new Equipment{"Twilight Steel", "Weapon", "Initial weapon. A finely crafted sword for Twilight's Personal Guard.", 0, vector<Stat_Modifier>{Stat_Modifier{"Twilight Steel Attack", "Attack", 38, true}, Stat_Modifier{"Twilight Steel Accuracy", "Accuracy", 150, true}, Stat_Modifier{"Twilight Steel Critical", "Critical", 7, false}}, vector<string>{"Tempest"}},
  new Equipment{"Leather Cap", "Helm", "A lightweight, stitched leather cap.", 15, vector<Stat_Modifier>{Stat_Modifier{"Leather Cap Defense", "Defense", 11, false}, Stat_Modifier{"Leather Cap Resistance", "Resistance", 7, false}}},
  new Equipment{"Leather Armor", "Armor", "Armor made of hardened leather.", 16, vector<Stat_Modifier>{Stat_Modifier{"Leather Armor Defense", "Defense", 28, false}, Stat_Modifier{"Leather Armor Resistance", "Resistance", 19, false}}},
  new Consumable_Item{"Heal Potion", "Heals a little HP."},
  new Consumable_Item{"Money Bag", "Gives 50 Bits."},
  new Key_Item{"Old Bone", "A calcified pony femur."}
};
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;

#endif