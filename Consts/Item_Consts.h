#ifndef ITEM_CONSTS
#define ITEM_CONSTS

m_item_database.add(vector<Item*>
{
  new Consumable_Item{"Red Apple", "Restores 50 HP to somepony."},
  new Consumable_Item{"Green Apple", "Restores 150 HP to somepony."},
  new Consumable_Item{"Apple Pie", "Restores 150 HP to somepony."},
  new Consumable_Item{"Oats", "Restores 65 MP to somepony."},
  new Consumable_Item{"Cake", "Revives somepony."},
  new Consumable_Item{"Blueberries", "Heals poison."},
  new Consumable_Item{"Healing Herb", "Cures all status effects."},
  new Consumable_Item{"Apple Cider", "Restores 150 HP to somepony."},
  new Consumable_Item{"Hide", "Restores 150 HP to somepony."},
  new Consumable_Item{"Cupcake", "One of Pinkie Pie's cupcakes."},
  new Equipment{"Wooden Horseshoe", "Weapon", "Wooden horseshoe for basic bucking.", 0, vector<Stat_Modifier>{Stat_Modifier{"WOOD Attack", "Attack", 1, false}}},
  new Equipment{"Bladed Horseshoe", "Weapon", "A horseshoe with a blade on it.", 0, vector<Stat_Modifier>{Stat_Modifier{"BLAD Attack", "Attack", 3, false}}, vector<string>{"Rainbow Dash", "Applejack"}},
  new Equipment{"Ultimate Physical Weapon", "Weapon", "Wooden horseshoe for basic bucking.", 0, vector<Stat_Modifier>{Stat_Modifier{"WOOD Attack", "Attack", 1, false}}},
  new Equipment{"Stick", "Weapon", "A random stick.", 0, vector<Stat_Modifier>{Stat_Modifier{"STIK Attack", "Attack", 2, false}}, vector<string>{"Pinkie Pie"}},
  new Equipment{"Giant Hat", "Armor", "One of Rarity's many giant hats.", 13, vector<Stat_Modifier>{Stat_Modifier{"HAT Defense", "Defense", 1, false}}},
  new Equipment{"Armor", "Armor", "Protective pony armor.", 13, vector<Stat_Modifier>{Stat_Modifier{"ARMR Defense", "Defense", 3, false}}, vector<string>{"Pinkie Pie", "Applejack"}},
  new Key_Item{"Cloud Walking Spell Book", "A book with instructions on casting a cloud walking spell."},
  new Key_Item{"Map of Equestria", "It will activate actomatically upon leaving a town or dungeon."}
});
mem += 18;

#endif
