#include "./../include/data/abilities.h"

#include <set>
#include <string>

#include "./../include/util/util.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
const std::set<std::string> Abilities::RBY({});
const std::set<std::string> Abilities::GSC({});
const std::set<std::string> Abilities::ADV = 
{
   "Air Lock",
   "Arena Trap",
   "Battle Armor",
   "Blaze",
   "Chlorophyll",
   "Clear Body",
   "Cloud Nine",
   "Color Change",
   "Compound Eyes",
   "Cute Charm",
   "Drizzle",
   "Damp",
   "Drought",
   "Early Bird",
   "Effect Spore",
   "Flame Body",
   "Flash Fire",
   "Forecast",
   "Guts",
   "Huge Power",
   "Hustle",
   "Hyper Cutter",
   "Illuminate",
   "Immunity",
   "Inner Focus",
   "Insomnia",
   "Intimidate",
   "Keen Eye",
   "Levitate",
   "Lightning Rod",
   "Limber",
   "Liquid Ooze",
   "Magma Armor",
   "Magnet Pull",
   "Marvel Scale",
   "Minus",
   "Natural Cure",
   "Oblivious",
   "Overgrow",
   "Own Tempo",
   "Pickup",
   "Plus",
   "Poison Point",
   "Pressure",
   "Pure Power",
   "Rain Dish",
   "Rock Head",
   "Rough Skin",
   "Run Away",
   "Sand Stream",
   "Sand Veil",
   "Serene Grace",
   "Shadow Tag",
   "Shed Skin",
   "Shell Armor",
   "Shield Dust",
   "Soundproof",
   "Speed Boost",
   "Static",
   "Stench",
   "Sticky Hold",
   "Sturdy",
   "Suction Cups",
   "Swarm",
   "Swift Swim",
   "Synchronize",
   "Thick Fat",
   "Torrent",
   "Trace",
   "Truant",
   "Vital Spirit",
   "Volt Absorb",
   "Water Absorb",
   "Water Veil",
   "White Smoke",
   "Wonder Guard"
};

const std::set<std::string> Abilities::DPP = Util::SetUnion<std::string>
(
   Abilities::ADV,
   std::set<std::string>
   {
      "Adaptability",
      "Aftermath",
      "Anger Point",
      "Anticipation",
      "Bad Dreams",
      "Download",
      "Dry Skin",
      "Filter",
      "Flower Gift",
      "Forewarn",
      "Frisk",
      "Gluttony",
      "Heatproof",
      "Honey Gather",
      "Hydration",
      "Ice Body",
      "Iron Fist",
      "Klutz",
      "Leaf Guard",
      "Magic Guard",
      "Mold Breaker",
      "Motor Drive",
      "Mountaineer",
      "Multitype",
      "No Guard",
      "Normalize",
      "Persistent",
      "Poison Heal",
      "Quick Feet",
      "Rebound",
      "Reckless",
      "Rivalry",
      "Scrappy",
      "Simple",
      "Skill Link",
      "Slow Start",
      "Sniper",
      "Snow Cloak",
      "Snow Warning",
      "Solar Power",
      "Solid Rock",
      "Stall",
      "Steadfast",
      "Storm Drain",
      "Super Luck",
      "Tangled Feet",
      "Technician",
      "Tinted Lens",
      "Unaware",
      "Unburden"
   }
);

const std::set<std::string> Abilities::BW = Util::SetUnion<std::string>
(
   Abilities::DPP,
   std::set<std::string>
   {
      "Analytic",
      "Big Pecks",
      "Contrary",
      "Cursed Body",
      "Defeatist",
      "Defiant",
      "Flare Boost",
      "Friend Guard",
      "Harvest",
      "Healer",
      "Heavy Metal",
      "Illusion",
      "Imposter",
      "Infiltrator",
      "Iron Barbs",
      "Light Metal",
      "Justified",
      "Magic Bounce",
      "Moody",
      "Moxie",
      "Multiscale",
      "Mummy",
      "Overcoat",
      "Pickpocket",
      "Poison Touch",
      "Prankster",
      "Rattled",
      "Regenerator",
      "Sand Force",
      "Sand Rush",
      "Sap Sipper",
      "Sheer Force",
      "Telepathy",
      "Teravolt",
      "Toxic Boost",
      "Turboblaze",
      "Unnerve",
      "Victory Star",
      "Weak Armor",
      "Wonder Skin",
      "Zen Mode"
   }
);

const std::set<std::string> Abilities::XY = Util::SetUnion<std::string>
(
   Abilities::BW,
   std::set<std::string>
   {
      "Aerilate",
      "Aura Break",
      "Aroma Veil",
      "Bulletproof",
      "Cheek Pouch",
      "Competitive",
      "Dark Aura",
      "Delta Stream",
      "Desolate Land",
      "Fairy Aura",
      "Flower Veil",
      "Fur Coat",
      "Gale Wings",
      "Gooey",
      "Grass Pelt",
      "Magician",
      "Mega Launcher",
      "Parental Bond",
      "Pixilate",
      "Primordial Sea",
      "Protean",
      "Refrigerate",
      "Stance Change",
      "Strong Jaw",
      "Sweet Veil",
      "Symbiosis",
      "Tough Claws"
   }
);

const std::set<std::string> Abilities::SM = Util::SetUnion<std::string>
(  
   Abilities::XY,
   std::set<std::string>
   {
      "Battery",
      "Battle Bond",
      "Beast Boost",
      "Berserk",
      "Comatose",
      "Corrosion",
      "Dancer",
      "Dazzling",
      "Disguise",
      "Electric Surge",
      "Emergency Exit",
      "Fluffy",
      "Full Metal Body",
      "Galvanize",
      "Grassy Surge",
      "Innards Out",
      "Liquid Voice",
      "Long Reach",
      "Merciless",
      "Misty Surge",
      "Neuroforce",
      "Power Construct",
      "Power of Alchemy",
      "Prism Armor",
      "Psychic Surge",
      "Queenly Majesty",
      "RKS System",
      "Receiver",
      "Schooling",
      "Shadow Shield",
      "Shields Down",
      "Slush Rush",
      "Stamina",
      "Stakeout",
      "Steelworker",
      "Soul-Heart",
      "Surge Surfer",
      "Tangling Hair",
      "Triage",
      "Water Bubble",
      "Water Compaction",
      "Wimp Out"
   }
);

const std::set<std::string> Abilities::SS = Util::SetUnion<std::string>
(
   Abilities::SM,
   std::set<std::string>
   {
      "As One (Glastrier)",
      "As One (Spectrier)",
      "Ball Fetch",
      "Chilling Neigh",
      "Cotton Down",
      "Curious Medicine",
      "Dauntless Shield",
      "Dragon\"s Maw",
      "Gorilla Tactics",
      "Grim Neigh",
      "Gulp Missile",
      "Hunger Switch",
      "Ice Face",
      "Ice Scales",
      "Intrepid Sword",
      "Libero",
      "Mimicry",
      "Mirror Armor",
      "Neutralizing Gas",
      "Pastel Veil",
      "Perish Body",
      "Power Spot",
      "Propeller Tail",
      "Punk Rock",
      "Quick Draw",
      "Ripen",
      "Sand Spit",
      "Screen Cleaner",
      "Stalwart",
      "Steam Engine",
      "Steely Spirit",
      "Transistor",
      "Unseen Fist",
      "Wandering Spirit"
   }
);

const std::set<std::string> Abilities::SV = Util::SetUnion<std::string>
(
   Abilities::SS,
   std::set<std::string>
   {
      "Anger Shell",
      "Armor Tail",
      "Beads of Ruin",
      "Commander",
      "Costar",
      "Cud Chew",
      "Earth Eater",
      "Electromorphosis",
      "Embody Aspect (Cornerstone)",
      "Embody Aspect (Hearthflame)",
      "Embody Aspect (Teal)",
      "Embody Aspect (Wellspring)",
      "Good as Gold",
      "Guard Dog",
      "Hadron Engine",
      "Hospitality",
      "Lingering Aroma",
      "Mind\"s Eye",
      "Mycelium Might",
      "Opportunist",
      "Orichalcum Pulse",
      "Poison Puppeteer",
      "Protosynthesis",
      "Purifying Salt",
      "Quark Drive",
      "Rocky Payload",
      "Seed Sower",
      "Sharpness",
      "Supersweet Syrup",
      "Supreme Overlord",
      "Sword of Ruin",
      "Tablets of Ruin",
      "Tera Shell",
      "Tera Shift",
      "Teraform Zero",
      "Thermal Exchange",
      "Toxic Chain",
      "Toxic Debris",
      "Vessel of Ruin",
      "Well-Baked Body",
      "Wind Power",
      "Wind Rider",
      "Zero to Hero",
   }
);

std::vector<std::set<std::string>> Abilities::ABILITIES = 
{
   {}, 
   Abilities::RBY, 
   Abilities::GSC, 
   Abilities::ADV, 
   Abilities::DPP, 
   Abilities::BW, 
   Abilities::XY, 
   Abilities::SM, 
   Abilities::SS, 
   Abilities::SV
};

Abilities::Abilities()
{
   for (const auto& abilities : Abilities::ABILITIES) 
   {
      std::map<std::string, Abilities::Ability> temp_map;

      for (const std::string& ability_name : abilities) 
      {
         std::string ability_id = Util::ToID(ability_name);
         temp_map[ability_id].id = ability_id;
         temp_map[ability_id].name = ability_name;
      }

      Abilities::ABILITIES_BY_ID.push_back(temp_map);
   }
}

Abilities& Abilities::Instance()
{
   static Abilities instance;
   return instance;
}

const std::set<std::string>& Abilities::GetRBYAbilities() const
{
   return Abilities::RBY;
}

const std::set<std::string>& Abilities::GetGSCAbilities() const
{
   return Abilities::GSC;
}

const std::set<std::string>& Abilities::GetADVAbilities() const
{
   return Abilities::ADV;
}

const std::set<std::string>& Abilities::GetDPPAbilities() const
{
   return Abilities::DPP;
}

const std::set<std::string>& Abilities::GetBWAbilities() const
{
   return Abilities::BW;
}

const std::set<std::string>& Abilities::GetXYAbilities() const
{
   return Abilities::XY;
}

const std::set<std::string>& Abilities::GetSMAbilities() const
{
   return Abilities::SM;
}

const std::set<std::string>& Abilities::GetSSAbilities() const
{
   return Abilities::SS;
}

const std::set<std::string>& Abilities::GetSVAbilities() const
{
   return Abilities::SV;
}

const std::set<std::string>& Abilities::GetAbilitiesByGeneration(const int gen) const
{
   return Abilities::ABILITIES[gen];
}

/*
const std::map<std::string, std::string>& Abilities::GetAbilitiesByIDByGeneration(const int gen) const
{
   return Abilities::ABILITIES_BY_ID[gen];
}
*/
}
}


