#ifndef ITEM_CONSTS
#define ITEM_CONSTS

m_item_database.add(vector<Item*>
{
  new Equipment{"Twilight Steel", "Weapon", "Tempest's 1st weapon.", 0, vector<Stat_Modifier>{Stat_Modifier{"Twilight Steel Attack", "Attack", 38, true}, Stat_Modifier{"Twilight Steel Accuracy", "Accuracy", 150, true}, Stat_Modifier{"Twilight Steel Critical", "Critical", 7, false}}, vector<string>{"Tempest"}},
  new Equipment{"Mythril Sword", "Weapon", "A sword made of mythril for Tempest.", 0, vector<Stat_Modifier>{Stat_Modifier{"Mythril Sword Attack", "Attack", 48, true}, Stat_Modifier{"Mythril Sword Accuracy", "Accuracy", 200, true}, Stat_Modifier{"Mythril Sword Critical", "Critical", 2.0}}, vector<string>{"Tempest"}},
  new Equipment{"Seashell Sword", "Weapon", "A sword decorated with seashells for Tempest.", 0, vector<Stat_Modifier>{Stat_Modifier{"Seashell Sword Attack", "Attack", 58, true}, Stat_Modifier{"Seashell Sword Accuracy", "Accuracy", 170, true}, Stat_Modifier{"Seashell Sword Critical", "Critical", 10, false}}, vector<string>{"Tempest"}},
  new Equipment{"Lunar Dagger", "Weapon", "An initial weapon for Nightwish.", 1, vector<Stat_Modifier>{Stat_Modifier{"Lunar Dagger Attack", "Attack", 20, true}, Stat_Modifier{"Lunar Dagger Accuracy", "Accuracy", 120, true}, Stat_Modifier{"Lunar Dagger Critical", "Critical", 5, false}}, vector<string>{"Nightwish"}},
  new Equipment{"Mythril Dagger", "Weapon", "A dagger made of mythril for Nightwish.", 1, vector<Stat_Modifier>{Stat_Modifier{"Mythril Dagger Attack", "Attack", 30, true}, Stat_Modifier{"Mythril Dagger Accuracy", "Accuracy", 145, true}, Stat_Modifier{"Mythril Dagger Critical", "Critical", 10, false}}, vector<string>{"Nightwish"}},
  new Equipment{"Hunting Knife", "Weapon", "A hunting knife for Nightwish.", 1, vector<Stat_Modifier>{Stat_Modifier{"Hunting Knife Attack", "Attack", 200, true}, Stat_Modifier{"Hunting Knife Accuracy", "Accuracy", 220, true}, Stat_Modifier{"Hunting Knife Critical", "Critical", 3.0}}, vector<string>{"Nightwish"}},
  new Equipment{"Solar Guantlets", "Weapon", "An initial weapon for Gallus.", 2, vector<Stat_Modifier>{Stat_Modifier{"Solar Guantlets Attack", "Attack", 20, true}, Stat_Modifier{"Solar Guantlets Accuracy", "Accuracy", 120, true}, Stat_Modifier{"Solar Guantlets Critical", "Critical", 5, false}}, vector<string>{"Gallus"}},
  new Equipment{"Mythril Claws", "Weapon", "Sharp Griffon talons made of mythril for Gallus.", 2, vector<Stat_Modifier>{Stat_Modifier{"Mythril Claws Attack", "Attack", 30, true}, Stat_Modifier{"Mythril Claws Accuracy", "Accuracy", 145, true}, Stat_Modifier{"Mythril Claws Critical", "Critical", 10, false}}, vector<string>{"Gallus"}},
  new Equipment{"Poison Knuckles", "Weapon", "Guantlets containing a potent toxin for Gallus.", 2, vector<Stat_Modifier>{Stat_Modifier{"Poison Knuckles Attack", "Attack", 200, true}, Stat_Modifier{"Poison Knuckles Accuracy", "Accuracy", 220, true}, Stat_Modifier{"Poison Knuckles Critical", "Critical", 3.0}}, vector<string>{"Gallus"}},
  new Equipment{"Iron Helm", "Helm", "A helmet made of iron.", 12, vector<Stat_Modifier>{Stat_Modifier{"Iron Helm Defense", "Defense", 18, false}, Stat_Modifier{"Iron Helm Resistance", "Resistance", 12, false}}, vector<string>{"Tempest", "Gallus"}},
  new Equipment{"Leather Cap", "Helm", "A lightweight, stitched leather cap.", 12, vector<Stat_Modifier>{Stat_Modifier{"Leather Cap Defense", "Defense", 11, false}, Stat_Modifier{"Leather Cap Resistance", "Resistance", 7, false}}},
  new Equipment{"Magnus Hat", "Helm", "A hat for magicians.", 12, vector<Stat_Modifier>{Stat_Modifier{"Magnus Hat Defense", "Defense", 15, false}, Stat_Modifier{"Magnus Hat Resistance", "Resistance", 16, false}}, vector<string>{"Tempest"}},
  new Equipment{"Bandana", "Helm", "A bandana.", 12, vector<Stat_Modifier>{Stat_Modifier{"Bandana Defense", "Defense", 16, false}, Stat_Modifier{"Bandana Resistance", "Resistance", 10, false}}, vector<string>{"Nightwish", "Gallus"}},
  new Equipment{"Tiger Mask", "Helm", "A tiger mask.", 12, vector<Stat_Modifier>{Stat_Modifier{"Tiger Mask Defense", "Defense", 21, false}, Stat_Modifier{"Tiger Mask Resistance", "Resistance", 13, false}}, vector<string>{"Gallus"}},
  new Equipment{"Leather Armor", "Armor", "Armor made of hardened leather.", 13, vector<Stat_Modifier>{Stat_Modifier{"Leather Armor Defense", "Defense", 28, false}, Stat_Modifier{"Leather Armor Resistance", "Resistance", 19, false}}},
  new Equipment{"Iron Armor", "Armor", "Armor made of iron.", 13, vector<Stat_Modifier>{Stat_Modifier{"Iron Armor Defense", "Defense", 40, false}, Stat_Modifier{"Iron Armor Resistance", "Resistance", 27, false}}, vector<string>{"Tempest", "Gallus"}},
  new Equipment{"Kenpo Gi", "Armor", "Traditionally-made armor.", 13, vector<Stat_Modifier>{Stat_Modifier{"Kenpo Gi Defense", "Defense", 34, false}, Stat_Modifier{"Kenpo Gi Resistance", "Resistance", 21, false}, Stat_Modifier{"Kenpo Gi Evasion", "Evasion", 1.05}}, vector<string>{"Nightwish", "Gallus"}},
  new Equipment{"Black Belt Gi", "Armor", "Traditionally-made armor meant for fighting.", 13, vector<Stat_Modifier>{Stat_Modifier{"Black Belt Gi Defense", "Defense", 68, false}, Stat_Modifier{"Black Belt Gi Resistance", "Resistance", 46, false}, Stat_Modifier{"Black Belt Gi Evasion", "Evasion", 6, false}}, vector<string>{"Nightwish"}},
  new Equipment{"Cotton Robe", "Armor", "A robe made of cotton.", 13, vector<Stat_Modifier>{Stat_Modifier{"Cotton Robe Defense", "Defense", 32, false}, Stat_Modifier{"Cotton Robe Resistance", "Resistance", 23, false}}, vector<string>{"Tempest", "Nightwish"}},
  new Equipment{"Heavy Shield", "Shield", "A heavy shield.", 14, vector<Stat_Modifier>{Stat_Modifier{"Heavy Shield Defense", "Defense", 22, false}, Stat_Modifier{"Heavy Shield Resistance", "Resistance", 14, false}, Stat_Modifier{"Heavy Shield Evasion", "Evasion", 1.1}}, vector<string>{"Tempest", "Gallus"}},
  new Equipment{"Crystal Shield", "Shield", "A shield made of crystal.", 14, vector<Stat_Modifier>{Stat_Modifier{"Crystal Shield Defense", "Defense", 50, false}, Stat_Modifier{"Crystal Shield Resistance", "Resistance", 34, false}, Stat_Modifier{"Crystal Shield Evasion", "Evasion", 1.1}}},
  new Equipment{"Force Shield", "Shield", "A shield to ward off magic.", 14, vector<Stat_Modifier>{Stat_Modifier{"Force Shield Resistance", "Resistance", 70, false}, Stat_Modifier{"Force Shield Magic Evasion", "Magic Evasion", 1.5}}, vector<string>{"Tempest", "Nightwish"}},
  new Equipment{"White Cape", "Accessory", "Blocks Mini and Moogle status conditions.", 16, vector<Stat_Modifier>{Stat_Modifier{"White Cape Defense", "Defense", 5, false}, Stat_Modifier{"White Cape Resistance", "Resistance", 5, false}}},
  new Equipment{"Power Band", "Accessory", "A band that makes you stronger.", 16, vector<Stat_Modifier>{Stat_Modifier{"Power Band Strength", "Strength", 10, false}}},
  new Equipment{"Muscle Belt", "Accessory", "A belt that makes you stronger.", 16, vector<Stat_Modifier>{Stat_Modifier{"Muscle Belt Strength", "Strength", 1.25}, Stat_Modifier{"Muscle Belt Stamina", "Stamina", 15, false}}},
  new Equipment{"Crystal Ball", "Accessory", "It sharply boosts your magic power.", 16, vector<Stat_Modifier>{Stat_Modifier{"Crystal Ball MP", "Max MP", 2.0}}},
  new Equipment{"Zephyr Cloak", "Accessory", "A cloak that makes it easier for you to dodge attacks.", 16, vector<Stat_Modifier>{Stat_Modifier{"Zephyr Cloak Evasion", "Evasion", 1.1}, Stat_Modifier{"Zephyr Cloak Magic Evasion", "Magic Evasion", 1.1}}},
  new Consumable_Item{"Heal Potion", "Heals a little HP."},
  new Consumable_Item{"Money Bag", "Gives 50 Bits."},
  new Key_Item{"Old Bone", "A calcified pony femur."}
});
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;
++mem;

#endif
