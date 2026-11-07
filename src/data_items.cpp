#include "./../include/data/items.h"

#include <set>
#include <string>

#include "./../include/data/types.h"
#include "./../include/util/util.h"
#include "./../include/enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
const std::set<std::string> Items::RBY({});
const std::set<std::string> Items::GSC =
{
   "Berry Juice",
   "Berry",
   "Berserk Gene",
   "Bitter Berry",
   "Black Belt",
   "Black Glasses",
   "Bright Powder",
   "Burnt Berry",
   "Charcoal",
   "Dragon Fang",
   "Dragon Scale",
   "Fast Ball",
   "Fire Stone",
   "Focus Band",
   "Friend Ball",
   "Gold Berry",
   "Great Ball",
   "Hard Stone",
   "Heavy Ball",
   "Ice Berry",
   "King\"s Rock",
   "Leaf Stone",
   "Leftovers",
   "Level Ball",
   "Light Ball",
   "Love Ball",
   "Lucky Punch",
   "Lure Ball",
   "Magnet",
   "Mail",
   "Master Ball",
   "Metal Coat",
   "Metal Powder",
   "Mint Berry",
   "Miracle Berry",
   "Miracle Seed",
   "Moon Ball",
   "Moon Stone",
   "Mystery Berry",
   "Mystic Water",
   "Never-Melt Ice",
   "Pink Bow",
   "Poison Barb",
   "Poke Ball",
   "Polkadot Bow",
   "PRZ Cure Berry",
   "PSN Cure Berry",
   "Quick Claw",
   "Safari Ball",
   "Scope Lens",
   "Sharp Beak",
   "Silver Powder",
   "Soft Sand",
   "Spell Tag",
   "Sport Ball",
   "Stick",
   "Sun Stone",
   "Thick Club",
   "Thunder Stone",
   "Twisted Spoon",
   "Ultra Ball",
   "Up-Grade",
   "Water Stone"
};

const std::set<std::string> Items::GSC_ONLY = 
{
  "Berry",
  "Berserk Gene",
  "Bitter Berry",
  "Burnt Berry",
  "Ice Berry",
  "Mint Berry",
  "Miracle Berry",
  "Mystery Berry",
  "PRZ Cure Berry",
  "Gold Berry",
  "Pink Bow",
  "Polkadot Bow",
  "PSN Cure Berry"
};

const std::set<std::string> Items::ADV = Util::SetUnion<std::string>
(
   Util::SetDifference<std::string>(Items::GSC, Items::GSC_ONLY),
   std::set<std::string>
   {
      "Aguav Berry",
      "Apicot Berry",
      "Aspear Berry",
      "Belue Berry",
      "Bluk Berry",
      "Cheri Berry",
      "Chesto Berry",
      "Choice Band",
      "Claw Fossil",
      "Cornn Berry",
      "Deep Sea Scale",
      "Deep Sea Tooth",
      "Dive Ball",
      "Dome Fossil",
      "Durin Berry",
      "Enigma Berry",
      "Figy Berry",
      "Ganlon Berry",
      "Grepa Berry",
      "Helix Fossil",
      "Hondew Berry",
      "Iapapa Berry",
      "Kelpsy Berry",
      "Lansat Berry",
      "Lax Incense",
      "Leppa Berry",
      "Liechi Berry",
      "Lum Berry",
      "Luxury Ball",
      "Macho Brace",
      "Mago Berry",
      "Magost Berry",
      "Mental Herb",
      "Nanab Berry",
      "Nest Ball",
      "Net Ball",
      "Nomel Berry",
      "Old Amber",
      "Oran Berry",
      "Pamtre Berry",
      "Pecha Berry",
      "Persim Berry",
      "Petaya Berry",
      "Pinap Berry",
      "Pomeg Berry",
      "Premier Ball",
      "Qualot Berry",
      "Rabuta Berry",
      "Rawst Berry",
      "Razz Berry",
      "Repeat Ball",
      "Root Fossil",
      "Salac Berry",
      "Sea Incense",
      "Shell Bell",
      "Silk Scarf",
      "Sitrus Berry",
      "Soul Dew",
      "Spelon Berry",
      "Starf Berry",
      "Tamato Berry",
      "Timer Ball",
      "Watmel Berry",
      "Wepear Berry",
      "White Herb",
      "Wiki Berry"
   }
);

const std::set<std::string> Items::DPP = Util::SetUnion<std::string>
(
   Items::ADV,
   std::set<std::string>
   {
      "Adamant Orb",
      "Armor Fossil",
      "Babiri Berry",
      "Big Root",
      "Black Sludge",
      "Charti Berry",
      "Cherish Ball",
      "Chilan Berry",
      "Choice Scarf",
      "Choice Specs",
      "Chople Berry",
      "Coba Berry",
      "Colbur Berry",
      "Custap Berry",
      "Damp Rock",
      "Dawn Stone",
      "Destiny Knot",
      "Draco Plate",
      "Dread Plate",
      "Dubious Disc",
      "Dusk Ball",
      "Dusk Stone",
      "Earth Plate",
      "Electirizer",
      "Expert Belt",
      "Fist Plate",
      "Flame Orb",
      "Flame Plate",
      "Focus Sash",
      "Full Incense",
      "Grip Claw",
      "Griseous Orb",
      "Haban Berry",
      "Heal Ball",
      "Heat Rock",
      "Icicle Plate",
      "Icy Rock",
      "Insect Plate",
      "Iron Ball",
      "Iron Plate",
      "Jaboca Berry",
      "Kasib Berry",
      "Kebia Berry",
      "Lagging Tail",
      "Life Orb",
      "Light Clay",
      "Lustrous Orb",
      "Magmarizer",
      "Meadow Plate",
      "Metronome",
      "Micle Berry",
      "Mind Plate",
      "Muscle Band",
      "Occa Berry",
      "Odd Incense",
      "Oval Stone",
      "Park Ball",
      "Passho Berry",
      "Payapa Berry",
      "Power Anklet",
      "Power Band",
      "Power Belt",
      "Power Bracer",
      "Power Herb",
      "Power Lens",
      "Power Weight",
      "Protector",
      "Quick Ball",
      "Quick Powder",
      "Rare Bone",
      "Razor Claw",
      "Razor Fang",
      "Reaper Cloth",
      "Rindo Berry",
      "Rock Incense",
      "Rose Incense",
      "Rowap Berry",
      "Shed Shell",
      "Shiny Stone",
      "Shuca Berry",
      "Skull Fossil",
      "Sky Plate",
      "Smooth Rock",
      "Splash Plate",
      "Spooky Plate",
      "Sticky Barb",
      "Stone Plate",
      "Tanga Berry",
      "Toxic Orb",
      "Toxic Plate",
      "Wacan Berry",
      "Wave Incense",
      "Wide Lens",
      "Wise Glasses",
      "Yache Berry",
      "Zap Plate",
      "Zoom Lens"
   }
);

const std::set<std::string> Items::BW = Util::SetUnion<std::string>
(
   Items::DPP,
   std::set<std::string>
   {
      "Absorb Bulb",
      "Air Balloon",
      "Big Nugget",
      "Binding Band",
      "Bug Gem",
      "Burn Drive",
      "Cell Battery",
      "Chill Drive",
      "Cover Fossil",
      "Dark Gem",
      "Douse Drive",
      "Dragon Gem",
      "Dream Ball",
      "Eject Button",
      "Electric Gem",
      "Eviolite",
      "Fighting Gem",
      "Fire Gem",
      "Float Stone",
      "Flying Gem",
      "Ghost Gem",
      "Grass Gem",
      "Ground Gem",
      "Ice Gem",
      "Normal Gem",
      "Plume Fossil",
      "Poison Gem",
      "Prism Scale",
      "Psychic Gem",
      "Red Card",
      "Ring Target",
      "Rock Gem",
      "Rocky Helmet",
      "Shock Drive",
      "Steel Gem",
      "Water Gem"
   }
);

const std::map<std::string, std::string> Items::MEGA_STONES = 
{
  {"Absolite", "Absol"},
  {"Abomasite", "Abomasnow"},
  {"Aerodactylite", "Aerodactyl"},
  {"Aggronite", "Aggron"},
  {"Alakazite", "Alakazam"},
  {"Altarianite", "Altaria"},
  {"Ampharosite", "Ampharos"},
  {"Audinite", "Audino"},
  {"Banettite", "Banette"},
  {"Beedrillite", "Beedrill"},
  {"Blastoisinite", "Blastoise"},
  {"Blazikenite", "Blaziken"},
  {"Cameruptite", "Camerupt"},
  {"Charizardite X", "Charizard"},
  {"Charizardite Y", "Charizard"},
  {"Crucibellite", "Crucibelle"},
  {"Diancite", "Diancie"},
  {"Galladite", "Gallade"},
  {"Garchompite", "Garchomp"},
  {"Gardevoirite", "Gardevoir"},
  {"Gengarite", "Gengar"},
  {"Glalitite", "Glalie"},
  {"Gyaradosite", "Gyarados"},
  {"Heracronite", "Heracross"},
  {"Houndoominite", "Houndoom"},
  {"Kangaskhanite", "Kangaskhan"},
  {"Latiasite", "Latias"},
  {"Latiosite", "Latios"},
  {"Lopunnite", "Lopunny"},
  {"Lucarionite", "Lucario"},
  {"Manectite", "Manectric"},
  {"Mawilite", "Mawile"},
  {"Medichamite", "Medicham"},
  {"Metagrossite", "Metagross"},
  {"Mewtwonite X", "Mewtwo"},
  {"Mewtwonite Y", "Mewtwo"},
  {"Pidgeotite", "Pidgeot"},
  {"Pinsirite", "Pinsir"},
  {"Sablenite", "Sableye"},
  {"Salamencite", "Salamence"},
  {"Sceptilite", "Sceptile"},
  {"Scizorite", "Scizor"},
  {"Sharpedonite", "Sharpedo"},
  {"Slowbronite", "Slowbro"},
  {"Steelixite", "Steelix"},
  {"Swampertite", "Swampert"},
  {"Tyranitarite", "Tyranitar"},
  {"Venusaurite", "Venusaur"},
};

const std::set<std::string> Items::XY = Util::SetUnion<std::string>
(  
   Items::BW,
   Util::SetUnion<std::string>
   (
      Util::GetMapKeys<std::string, std::string>(Items::MEGA_STONES),
      {
         "Assault Vest",
         "Blue Orb",
         "Fairy Gem",
         "Jaw Fossil",
         "Kee Berry",
         "Luminous Moss",
         "Maranga Berry",
         "Pixie Plate",
         "Red Orb",
         "Roseli Berry",
         "Sachet",
         "Safety Goggles",
         "Sail Fossil",
         "Snowball",
         "Weakness Policy",
         "Whipped Dream"
      }
   )
);

const std::set<std::string> Items::SM = Util::SetUnion<std::string>
(
   Util::SetDifference(Items::XY, std::set<std::string>{"Old Amber"}),
   std::set<std::string>
   {
      "Adrenaline Orb",
      "Aloraichium Z",
      "Beast Ball",
      "Bottle Cap",
      "Bug Memory",
      "Buginium Z",
      "Dark Memory",
      "Darkinium Z",
      "Decidium Z",
      "Dragon Memory",
      "Dragonium Z",
      "Eevium Z",
      "Electric Memory",
      "Electric Seed",
      "Electrium Z",
      "Fairium Z",
      "Fairy Memory",
      "Fighting Memory",
      "Fightinium Z",
      "Fire Memory",
      "Firium Z",
      "Flying Memory",
      "Flyinium Z",
      "Ghost Memory",
      "Ghostium Z",
      "Gold Bottle Cap",
      "Grass Memory",
      "Grassium Z",
      "Grassy Seed",
      "Ground Memory",
      "Groundium Z",
      "Ice Memory",
      "Ice Stone",
      "Icium Z",
      "Incinium Z",
      "Kommonium Z",
      "Lunalium Z",
      "Lycanium Z",
      "Marshadium Z",
      "Mewnium Z",
      "Mimikium Z",
      "Misty Seed",
      "Normalium Z",
      "Pikanium Z",
      "Pikashunium Z",
      "Poison Memory",
      "Poisonium Z",
      "Primarium Z",
      "Protective Pads",
      "Psychic Memory",
      "Psychic Seed",
      "Psychium Z",
      "Rock Memory",
      "Rockium Z",
      "Snorlium Z",
      "Solganium Z",
      "Steel Memory",
      "Steelium Z",
      "Tapunium Z",
      "Terrain Extender",
      "Ultranecrozium Z",
      "Water Memory",
      "Waterium Z"
   }
);

const std::set<std::string> Items::SS = Util::SetUnion<std::string>
(
   Items::SM,
   Util::SetUnion<std::string>
   (
      Items::GSC_ONLY, // Because we support National Dex all Past items are added back in
      Util::SetUnion<std::string>
      (
         std::set<std::string>{"Old Amber"}, 
         std::set<std::string>
         {
            "Berry Sweet",
            "Blunder Policy",
            "Chipped Pot",
            "Clover Sweet",
            "Cracked Pot",
            "Eject Pack",
            "Flower Sweet",
            "Fossilized Bird",
            "Fossilized Dino",
            "Fossilized Drake",
            "Fossilized Fish",
            "Galarica Cuff",
            "Galarica Wreath",
            "Heavy-Duty Boots",
            "Leek",
            "Love Sweet",
            "Ribbon Sweet",
            "Room Service",
            "Rusted Shield",
            "Rusted Sword",
            "Star Sweet",
            "Strawberry Sweet",
            "Sweet Apple",
            "Tart Apple",
            "Throat Spray",
            "TR00",
            "TR01",
            "TR02",
            "TR03",
            "TR04",
            "TR05",
            "TR06",
            "TR07",
            "TR08",
            "TR09",
            "TR10",
            "TR11",
            "TR12",
            "TR13",
            "TR14",
            "TR15",
            "TR16",
            "TR17",
            "TR18",
            "TR19",
            "TR20",
            "TR21",
            "TR22",
            "TR23",
            "TR24",
            "TR25",
            "TR26",
            "TR27",
            "TR28",
            "TR29",
            "TR30",
            "TR31",
            "TR32",
            "TR33",
            "TR34",
            "TR35",
            "TR36",
            "TR37",
            "TR38",
            "TR39",
            "TR40",
            "TR41",
            "TR42",
            "TR43",
            "TR44",
            "TR45",
            "TR46",
            "TR47",
            "TR48",
            "TR49",
            "TR50",
            "TR51",
            "TR52",
            "TR53",
            "TR54",
            "TR55",
            "TR56",
            "TR57",
            "TR58",
            "TR59",
            "TR60",
            "TR61",
            "TR62",
            "TR63",
            "TR64",
            "TR65",
            "TR66",
            "TR67",
            "TR68",
            "TR69",
            "TR70",
            "TR71",
            "TR72",
            "TR73",
            "TR74",
            "TR75",
            "TR76",
            "TR77",
            "TR78",
            "TR79",
            "TR80",
            "TR81",
            "TR82",
            "TR83",
            "TR84",
            "TR85",
            "TR86",
            "TR87",
            "TR88",
            "TR89",
            "TR90",
            "TR91",
            "TR92",
            "TR93",
            "TR94",
            "TR95",
            "TR96",
            "TR97",
            "TR98",
            "TR99",
            "Utility Umbrella",
            "Vile Vial"
         }
      )
   )
);

const std::set<std::string> Items::SV = Util::SetUnion<std::string>
(
   Items::SS,
   std::set<std::string>
   {
      "Adamant Crystal",
      "Auspicious Armor",
      "Ability Shield",
      "Booster Energy",
      "Clear Amulet",
      "Cornerstone Mask",
      "Covert Cloak",
      "Fairy Feather",
      "Hearthflame Mask",
      "Loaded Dice",
      "Malicious Armor",
      "Masterpiece Teacup",
      "Metal Alloy",
      "Mirror Herb",
      "Punching Glove",
      "Lustrous Globe",
      "Griseous Core",
      "Strange Ball",
      "Syrupy Apple",
      "Unremarkable Teacup",
      "Wellspring Mask",
   }
);

const std::map<std::string, Items::NaturalGift> Items::BERRIES = 
{
   {"Aguav Berry", {ENUMS::Dragon, 80}},
   {"Apicot Berry", {ENUMS::Ground, 100}},
   {"Aspear Berry", {ENUMS::Ice, 80}},
   {"Babiri Berry", {ENUMS::Steel, 80}},
   {"Belue Berry", {ENUMS::Electric, 100}},
   {"Berry", {ENUMS::Poison, 80}},
   {"Bitter Berry", {ENUMS::Ground, 80}},
   {"Bluk Berry", {ENUMS::Fire, 90}},
   {"Burnt Berry", {ENUMS::Ice, 80}},
   {"Charti Berry", {ENUMS::Rock, 80}},
   {"Cheri Berry", {ENUMS::Fire, 80}},
   {"Chesto Berry", {ENUMS::Water, 80}},
   {"Chilan Berry", {ENUMS::Normal, 80}},
   {"Chople Berry", {ENUMS::Fighting, 80}},
   {"Coba Berry", {ENUMS::Flying, 80}},
   {"Colbur Berry", {ENUMS::Dark, 80}},
   {"Cornn Berry", {ENUMS::Bug, 90}},
   {"Custap Berry", {ENUMS::Ghost, 100}},
   {"Durin Berry", {ENUMS::Water, 100}},
   {"Enigma Berry", {ENUMS::Bug, 100}},
   {"Figy Berry", {ENUMS::Bug, 80}},
   {"Ganlon Berry", {ENUMS::Ice, 100}},
   {"Gold Berry", {ENUMS::Psychic, 80}},
   {"Grepa Berry", {ENUMS::Flying, 90}},
   {"Haban Berry", {ENUMS::Dragon, 80}},
   {"Hondew Berry", {ENUMS::Ground, 90}},
   {"Iapapa Berry", {ENUMS::Dark, 80}},
   {"Ice Berry", {ENUMS::Grass, 80}},
   {"Jaboca Berry", {ENUMS::Dragon, 100}},
   {"Kasib Berry", {ENUMS::Ghost, 80}},
   {"Kebia Berry", {ENUMS::Poison, 80}},
   {"Kee Berry", {ENUMS::Fairy, 100}},
   {"Kelpsy Berry", {ENUMS::Fighting, 90}},
   {"Lansat Berry", {ENUMS::Flying, 100}},
   {"Leppa Berry", {ENUMS::Fighting, 80}},
   {"Liechi Berry", {ENUMS::Grass, 100}},
   {"Lum Berry", {ENUMS::Flying, 80}},
   {"Mago Berry", {ENUMS::Ghost, 80}},
   {"Magost Berry", {ENUMS::Rock, 90}},
   {"Maranga Berry", {ENUMS::Dark, 100}},
   {"Micle Berry", {ENUMS::Rock, 100}},
   {"Mint Berry", {ENUMS::Water, 80}},
   {"Miracle Berry", {ENUMS::Flying, 80}},
   {"Mystery Berry", {ENUMS::Fighting, 80}},
   {"Nanab Berry", {ENUMS::Water, 90}},
   {"Nomel Berry", {ENUMS::Dragon, 90}},
   {"Occa Berry", {ENUMS::Fire, 80}},
   {"Oran Berry", {ENUMS::Poison, 80}},
   {"Pamtre Berry", {ENUMS::Steel, 90}},
   {"Passho Berry", {ENUMS::Water, 80}},
   {"Payapa Berry", {ENUMS::Psychic, 80}},
   {"Pecha Berry", {ENUMS::Electric, 80}},
   {"Persim Berry", {ENUMS::Ground, 80}},
   {"Petaya Berry", {ENUMS::Poison, 100}},
   {"Pinap Berry", {ENUMS::Grass, 90}},
   {"Pomeg Berry", {ENUMS::Ice, 90}},
   {"PRZ Cure Berry", {ENUMS::Fire, 80}},
   {"PSN Cure Berry", {ENUMS::Electric, 80}},
   {"Qualot Berry", {ENUMS::Poison, 90}},
   {"Rabuta Berry", {ENUMS::Ghost, 90}},
   {"Rawst Berry", {ENUMS::Grass, 80}},
   {"Razz Berry", {ENUMS::Steel, 80}},
   {"Rindo Berry", {ENUMS::Grass, 80}},
   {"Roseli Berry", {ENUMS::Fairy, 80}},
   {"Rowap Berry", {ENUMS::Dark, 100}},
   {"Salac Berry", {ENUMS::Fighting, 100}},
   {"Shuca Berry", {ENUMS::Ground, 80}},
   {"Sitrus Berry", {ENUMS::Psychic, 80}},
   {"Spelon Berry", {ENUMS::Dark, 90}},
   {"Starf Berry", {ENUMS::Psychic, 100}},
   {"Tamato Berry", {ENUMS::Psychic, 90}},
   {"Tanga Berry", {ENUMS::Bug, 80}},
   {"Wacan Berry", {ENUMS::Electric, 80}},
   {"Watmel Berry", {ENUMS::Fire, 100}},
   {"Wepear Berry", {ENUMS::Electric, 90}},
   {"Wiki Berry", {ENUMS::Rock, 80}},
   {"Yache Berry", {ENUMS::Ice, 80}}
};


std::vector<std::set<std::string>> Items::ITEMS = 
{
   {}, 
   Items::RBY, 
   Items::GSC, 
   Items::ADV, 
   Items::DPP, 
   Items::BW, 
   Items::XY, 
   Items::SM, 
   Items::SS, 
   Items::SV
};

const std::map<std::string, ENUMS::StatID> Items::SEED_BOOSTED_STAT = 
{
   {"Electric Seed", ENUMS::StatID::def},
   {"Grassy Seed", ENUMS::StatID::def},
   {"Misty Seed", ENUMS::StatID::spd},
   {"Psychic Seed", ENUMS::StatID::spd}
};

const std::set<std::string> Items::FLING_130 = std::set<std::string>
{
   "Big Nugget", 
   "Iron Ball", 
   "TR43", 
   "TR71"
};

const std::set<std::string> Items::FLING_120 = std::set<std::string>
{
   "TR24",
   "TR28",
   "TR34",
   "TR39",
   "TR53",
   "TR55",
   "TR64",
   "TR66",
   "TR72",
   "TR73",
};

const std::set<std::string> Items::FLING_110 = std::set<std::string>
{
   "TR03", 
   "TR06", 
   "TR09", 
   "TR15", 
   "TR89"
};

const std::set<std::string> Items::FLING_100 = std::set<std::string>
{
   "Hard Stone",
   "Room Service",
   "Claw Fossil",
   "Dome Fossil",
   "Helix Fossil",
   "Old Amber",
   "Root Fossil",
   "Armor Fossil",
   "Old Amber",
   "Fossilized Bird",
   "Fossilized Dino",
   "Fossilized Drake",
   "Fossilized Fish",
   "Plume Fossil",
   "Jaw Fossil",
   "Cover Fossil",
   "Sail Fossil",
   "Rare Bone",
   "Skull Fossil",
   "TR10",
   "TR31",
   "TR75",
};

const std::set<std::string> Items::FLING_95 = std::set<std::string>
{
   "TR36", 
   "TR78", 
   "TR81", 
   "TR94"
};

const std::set<std::string> Items::FLING_90 = std::set<std::string>
{
   "Deep Sea Tooth",
   "Thick Club",
   "TR02",
   "TR04",
   "TR05",
   "TR08",
   "TR11",
   "TR22",
   "TR35",
   "TR42",
   "TR45",
   "TR50",
   "TR61",
   "TR65",
   "TR67",
   "TR86",
   "TR90",
   "TR96",
};

const std::set<std::string> Items::FLING_85 = std::set<std::string>
{
   "TR01", 
   "TR41", 
   "TR62", 
   "TR93", 
   "TR97", 
   "TR98"
};

const std::set<std::string> Items::FLING_80 = std::set<std::string>
{
   "Assault Vest",
   "Blunder Policy",
   "Chipped Pot",
   "Cracked Pot",
   "Heavy-Duty Boots",
   "Weakness Policy",
   "Quick Claw",
   "Dawn Stone",
   "Dusk Stone",
   "Electirizer",
   "Magmarizer",
   "Oval Stone",
   "Protector",
   "Sachet",
   "Whipped Dream",
   "Razor Claw",
   "Shiny Stone",
   "TR16",
   "TR18",
   "TR19",
   "TR25",
   "TR32",
   "TR33",
   "TR47",
   "TR56",
   "TR57",
   "TR58",
   "TR59",
   "TR60",
   "TR63",
   "TR69",
   "TR70",
   "TR74",
   "TR84",
   "TR87",
   "TR92",
   "TR95",
   "TR99",
};

const std::set<std::string> Items::FLING_70 = std::set<std::string>
{
   "Poison Barb",
   "Dragon Fang",
   "Power Anklet",
   "Power Band",
   "Power Belt",
   "Power Bracer",
   "Power Lens",
   "Power Weight",
};

const std::set<std::string> Items::FLING_60 = std::set<std::string>
{
   "Adamant Orb",
   "Damp Rock",
   "Heat Rock",
   "Leek",
   "Lustrous Orb",
   "Macho Brace",
   "Rocky Helmet",
   "Stick",
   "Utility Umbrella",
   "Terrain Extender",
};

const std::set<std::string> Items::FLING_50 = std::set<std::string>
{
   "Eject Pack", 
   "Sharp Beak", 
   "Dubious Disc"
};

const std::set<std::string> Items::FLING_40 = std::set<std::string>
{
   "Icy Rock", 
   "Eviolite", 
   "Lucky Punch"
};

const std::set<std::string> Items::FLING_30 = std::set<std::string>
{
   "Absorb Bulb",
   "Black Belt",
   "Black Sludge",
   "Black Glasses",
   "Cell Battery",
   "Charcoal",
   "Deep Sea Scale",
   "Flame Orb",
   "King\"s Rock",
   "Life Orb",
   "Light Ball",
   "Light Clay",
   "Magnet",
   "Metal Coat",
   "Miracle Seed",
   "Mystic Water",
   "Never-Melt Ice",
   "Razor Fang",
   "Scope Lens",
   "Soul Dew",
   "Spell Tag",
   "Sweet Apple",
   "Tart Apple",
   "Throat Spray",
   "Toxic Orb",
   "Twisted Spoon",
   "Dragon Scale",
   "Energy Powder",
   "Fire Stone",
   "Leaf Stone",
   "Moon Stone",
   "Sun Stone",
   "Thunder Stone",
   "Up-Grade",
   "Water Stone",
   "Berry Juice",
   "Black Sludge",
   "Prism Scale",
   "Ice Stone",
   "Gold Bottle Cap",
   "Luminous Moss",
   "Eject Button",
   "Snowball",
   "Bottle Cap",
};

const std::set<std::string> Items::FLING_10 = std::set<std::string>
{
   "Air Balloon",
   "Berry Sweet",
   "Choice Band",
   "Choice Scarf",
   "Choice Specs",
   "Clover Sweet",
   "Destiny Knot",
   "Electric Seed",
   "Expert Belt",
   "Flower Sweet",
   "Focus Band",
   "Focus Sash",
   "Full Incense",
   "Grassy Seed",
   "Lagging Tail",
   "Lax Incense",
   "Leftovers",
   "Love Sweet",
   "Mental Herb",
   "Metal Powder",
   "Mint Berry",
   "Miracle Berry",
   "Misty Seed",
   "Muscle Band",
   "Power Herb",
   "Psychic Seed",
   "Odd Incense",
   "Quick Powder",
   "Reaper Cloth",
   "Red Card",
   "Ribbon Sweet",
   "Ring Target",
   "Rock Incense",
   "Rose Incense",
   "Sea Incense",
   "Shed Shell",
   "Silk Scarf",
   "Silver Powder",
   "Smooth Rock",
   "Soft Sand",
   "Soothe Bell",
   "Star Sweet",
   "Strawberry Sweet",
   "Wave Incense",
   "White Herb",
   "Wide Lens",
   "Wise Glasses",
   "Zoom Lens",
   "Silver Powder",
   "Power Herb",
   "TR00",
   "TR07",
   "TR12",
   "TR13",
   "TR14",
   "TR17",
   "TR20",
   "TR21",
   "TR23",
   "TR26",
   "TR27",
   "TR29",
   "TR30",
   "TR37",
   "TR38",
   "TR40",
   "TR44",
   "TR46",
   "TR48",
   "TR49",
   "TR51",
   "TR52",
   "TR54",
   "TR68",
   "TR76",
   "TR77",
   "TR79",
   "TR80",
   "TR83",
   "TR85",
   "TR88",
   "TR91",
};

Items::Items()
{
   int gen = 0;
   for (const auto& items : Items::ITEMS) 
   {
      std::map<std::string, Items::Item> temp_map;

      for (const std::string& item_name : items) 
      {
         std::string item_id = Util::ToID(item_name);
         temp_map[item_id].id = item_id;
         temp_map[item_id].name = item_name;
         if (Items::MEGA_STONES.find(item_name) != MEGA_STONES.end())
         {
            temp_map[item_id].mega_evolves = 
               Items::MEGA_STONES.at(item_name);
         }
         if (Items::BERRIES.find(item_name) != BERRIES.end())
         {
            temp_map[item_id].is_berry = true;
            temp_map[item_id].natural_gift.t 
               = Items::BERRIES.at(item_name).t;
            if (gen < 6)
            {
               temp_map[item_id].natural_gift.p 
                  = Items::BERRIES.at(item_name).p - 20;
            }
            else
            {
               temp_map[item_id].natural_gift.p 
                  = Items::BERRIES.at(item_name).p;
            }
         }
      }

      Items::ITEMS_BY_ID.push_back(temp_map);
      gen++;
   }
}

Items& Items::Instance()
{
   static Items instance;
   return instance;
}

const std::set<std::string>& Items::GetRBYItems() const
{
   return Items::RBY;
}

const std::set<std::string>& Items::GetGSCItems() const
{
   return Items::GSC;
}

const std::set<std::string>& Items::GetADVItems() const
{
   return Items::ADV;
}

const std::set<std::string>& Items::GetDPPItems() const
{
   return Items::DPP;
}

const std::set<std::string>& Items::GetBWItems() const
{
   return Items::BW;
}

const std::set<std::string>& Items::GetXYItems() const
{
   return Items::XY;
}

const std::set<std::string>& Items::GetSMItems() const
{
   return Items::SM;
}

const std::set<std::string>& Items::GetSSItems() const
{
   return Items::SS;
}

const std::set<std::string>& Items::GetSVItems() const
{
   return Items::SV;
}

const std::set<std::string>& Items::GetItemsByGeneration(const int gen) const
{
   return Items::ITEMS[gen];
}

std::optional<ENUMS::TypeName> Items::GetItemBoostType(const std::string& item) 
{
   if (item == "Draco Plate" ||
       item == "Dragon Fang")
   {
      return ENUMS::TypeName::Dragon;
   }
   else if (item == "Dread Plate" ||
       item == "Black Glasses")
   {
      return ENUMS::TypeName::Dark;
   }
   else if (item == "Earth Plate" ||
            item == "Soft Sand")
   {
      return ENUMS::TypeName::Ground;
   }
   else if (item == "Fist Plate" ||
            item == "Black Belt")
   {
      return ENUMS::TypeName::Fighting;
   }
   else if (item == "Flame Plate" ||
            item == "Charcoal")
   {
      return ENUMS::TypeName::Fire;
   }
   else if (item == "Icicle Plate" ||
            item == "Never-Melt Ice")
   {
      return ENUMS::TypeName::Ice;
   }
   else if (item == "Insect Plate" ||
            item == "Silver Powder")
   {
      return ENUMS::TypeName::Bug;
   }
   else if (item == "Iron Plate" ||
            item == "Metal Coat")
   {
      return ENUMS::TypeName::Steel;
   }
   else if (item == "Meadow Plate" ||
            item == "Rose Incense" ||
            item == "Miracle Seed")
   {
      return ENUMS::TypeName::Grass;
   }
   else if (item == "Mind Plate" ||
            item == "Odd Incense" ||
            item == "Twisted Spoon")
   {
      return ENUMS::TypeName::Psychic;
   }
   else if (item == "Fairy Feather" ||
            item == "Pixie Plate")
   {
      return ENUMS::TypeName::Fairy;
   }
   else if (item == "Sky Plate" ||
            item == "Sharp Beak")
   {
      return ENUMS::TypeName::Flying;
   }
   else if (item == "Splash Plate" ||
            item == "Sea Incense" ||
            item == "Wave Incense" ||
            item == "Mystic Water")
   {
      return ENUMS::TypeName::Water;
   }
   else if (item == "Spooky Plate" ||
            item == "Spell Tag")
   {
      return ENUMS::TypeName::Ghost;
   }
   else if (item == "Stone Plate" ||
            item == "Rock Incense" ||
            item == "Hard Stone")
   {
      return ENUMS::TypeName::Rock;
   }
   else if (item == "Toxic Plate" ||
            item == "Poison Barb")
   {
      return ENUMS::TypeName::Poison;
   }
   else if (item == "Zap Plate" ||
            item == "Magnet")
   {
      return ENUMS::TypeName::Electric;
   }
   else if (item == "Silk Scarf" ||
            item == "Pink Bow" ||
            item == "Polkadot Bow")
   {
      return ENUMS::TypeName::Normal;
   }
   
   return std::nullopt;
}

std::optional<ENUMS::TypeName> Items::GetBerryResistType(const std::string& berry) 
{
   if (berry == "Chilan Berry")        return ENUMS::TypeName::Normal;
   else if (berry == "Occa Berry")     return ENUMS::TypeName::Fire;
   else if (berry == "Passho Berry")   return ENUMS::TypeName::Water;
   else if (berry == "Wacan Berry")    return ENUMS::TypeName::Electric;
   else if (berry == "Rindo Berry")    return ENUMS::TypeName::Grass;
   else if (berry == "Yache Berry")    return ENUMS::TypeName::Ice;
   else if (berry == "Chople Berry")   return ENUMS::TypeName::Fighting;
   else if (berry == "Kebia Berry")    return ENUMS::TypeName::Poison;
   else if (berry == "Shuca Berry")    return ENUMS::TypeName::Ground;
   else if (berry == "Coba Berry")     return ENUMS::TypeName::Flying;
   else if (berry == "Payapa Berry")   return ENUMS::TypeName::Psychic;
   else if (berry == "Tanga Berry")    return ENUMS::TypeName::Bug;
   else if (berry == "Charti Berry")   return ENUMS::TypeName::Rock;
   else if (berry == "Kasib Berry")    return ENUMS::TypeName::Ghost;
   else if (berry == "Haban Berry")    return ENUMS::TypeName::Dragon;
   else if (berry == "Colbur Berry")   return ENUMS::TypeName::Dark;
   else if (berry == "Babiri Berry")   return ENUMS::TypeName::Steel;
   else if (berry == "Roseli Berry")   return ENUMS::TypeName::Fairy;
   
   return std::nullopt;
}

int Items::GetFlingPower(std::optional<std::string> item) 
{
   if (!item) return 0;
   if (Items::FLING_130.find(item.value()) != Items::FLING_130.end()) return 130;
   if (Items::FLING_120.find(item.value()) != Items::FLING_120.end()) return 85;
   if (Items::FLING_110.find(item.value()) != Items::FLING_110.end()) return 110;
   if (Items::FLING_100.find(item.value()) != Items::FLING_100.end()) return 100;
   if (Items::FLING_95.find(item.value()) != Items::FLING_95.end()) return 95;
   if (item.value().find("Plate") != std::string::npos || 
       Items::FLING_90.find(item.value()) != Items::FLING_90.end()) 
   {
      return 90;
   }
   if (Items::FLING_85.find(item.value()) != Items::FLING_85.end()) return 85;
   if (Items::FLING_80.find(item.value()) != Items::FLING_80.end()) return 80;
   if (Items::FLING_70.find(item.value()) != Items::FLING_70.end()) return 70;
   if (Items::FLING_60.find(item.value()) != Items::FLING_60.end()) return 60;
   if (Items::FLING_50.find(item.value()) != Items::FLING_50.end()) return 50;
   if (Items::FLING_40.find(item.value()) != Items::FLING_40.end()) return 40;
   if (Items::FLING_30.find(item.value()) != Items::FLING_30.end()) return 30;
   if (item == "TR82") return 20;
   if (item.value().find("Berry") != std::string::npos || 
       Items::FLING_10.find(item.value()) != Items::FLING_10.end()) 
   {
      return 10;
   }
   return 0;
}

Items::NaturalGift Items::GetNaturalGift(const int gen, const std::string& item)
{
   if (Items::ITEMS_BY_ID[gen].find(item) != Items::ITEMS_BY_ID[gen].end())
   {
      return Items::ITEMS_BY_ID[gen].at(item).natural_gift;
   }
   return {.t = ENUMS::TypeName::Normal, .p = 1};
}

std::optional<ENUMS::TypeName> Items::GetTechnoBlast(const std::string& item) 
{
   if (item == "Burn Drive")
   {
      return ENUMS::TypeName::Fire;
   }
   if (item == "Chill Drive")
   {
      return ENUMS::TypeName::Ice;
   }
   if (item == "Douse Drive")
   {
      return ENUMS::TypeName::Water;
   }
   if (item == "Shock Drive")
   {
      return ENUMS::TypeName::Electric;
   }
   
   return std::nullopt;
}

std::optional<ENUMS::TypeName> Items::GetMultiAttack(const std::string& item)
{
   if (item.find("Memory") != std::string::npos) 
   {
      return Types::Instance().StringToTypeNameENUM(item.substr(0, item.find(" ")));
   }
   return std::nullopt;
}

const std::string& Items::GetMegaEvolves(const int gen, const std::string& item)
{
   return Items::ITEMS_BY_ID.at(gen).at(Util::ToID(item)).mega_evolves;
}

const std::optional<ENUMS::Terrain> Items::GetTerrainFromSeed(const std::string& item) const
{
   if (item.starts_with("Psychic")) return ENUMS::Terrain::Psychic_t;
   else if (item.starts_with("Grassy")) return ENUMS::Terrain::Grassy_t;
   else if (item.starts_with("Misty")) return ENUMS::Terrain::Misty_t;
   else if (item.starts_with("Electric")) return ENUMS::Terrain::Electric_t;

   return std::nullopt;
}

}
}
