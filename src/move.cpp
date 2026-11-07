#include "./../include/move.hpp"

#include "./../include/data/moves.h"
#include "./../include/util/util.h"

namespace PokemonDamageCalcCPP
{
namespace Move
{
std::string GetZMoveName
(
   const std::string& move_name, 
   const ENUMS::TypeName move_type, 
   const std::optional<std::string>& item
) 
{
   if (move_name.find("Hidden Power") != std::string::npos) return "Breakneck Blitz";
   if (move_name == "Clanging Scales" && item && item.value() == "Kommonium Z") return "Clangorous Soulblaze";
   if (move_name == "Darkest Lariat" && item && item.value() == "Incinium Z") return "Malicious Moonsault";
   if (move_name == "Giga Impact" && item && item.value() == "Snorlium Z") return "Pulverizing Pancake";
   if (move_name == "Moongeist Beam" && item && item.value() == "Lunalium Z") return "Menacing Moonraze Maelstrom";
   if (move_name == "Photon Geyser" && item && item.value() == "Ultranecrozium Z") 
   {
      return "Light That Burns the Sky";
   }
   if (move_name == "Play Rough" && item && item.value() == "Mimikium Z") return "Let\'s Snuggle Forever";
   if (move_name == "Psychic" && item && item.value() == "Mewnium Z") return "Genesis Supernova";
   if (move_name == "Sparkling Aria" && item && item.value() == "Primarium Z") return "Oceanic Operetta";
   if (move_name == "Spectral Thief" && item && item.value() == "Marshadium Z") 
   {
      return "Soul-Stealing 7-Star Strike";
   }
   if (move_name == "Spirit Shackle" && item && item.value() == "Decidium Z") return "Sinister Arrow Raid";
   if (move_name == "Stone Edge" && item && item.value() == "Lycanium Z") return "Splintered Stormshards";
   if (move_name == "Sunsteel Strike" && item && item.value() == "Solganium Z") return "Searing Sunraze Smash";
   if (move_name == "Volt Tackle" && item && item.value() == "Pikanium Z") return "Catastropika";
   if (move_name == "Nature\'s Madness" && item && item.value() == "Tapunium Z") return "Guardian of Alola";
   if (move_name == "Thunderbolt") 
   {
      if (item && item.value() == "Aloraichium Z") return "Stoked Sparksurfer";
      if (item && item.value() == "Pikashunium Z") return "10,000,000 Volt Thunderbolt";
   }

   return ZMOVES_TYPING.at(move_type);
}

std::string GetMaxMoveName
(
   const ENUMS::TypeName move_type,
   const std::optional<std::string>& move_name,
   const std::optional<std::string>& pokemon_species,
   const bool is_status,
   const std::optional<std::string>& pokemon_ability
)
{
   if (is_status) return "Max Guard";
   if (pokemon_ability && pokemon_ability.value() == "Normalize") return "Max Strike";
   if (move_type == ENUMS::TypeName::Fire) 
   {
      if (pokemon_species && pokemon_species.value() == "Charizard-Gmax") return "G-Max Wildfire";
      if (pokemon_species && pokemon_species.value() == "Centiskorch-Gmax") return "G-Max Centiferno";
      if (pokemon_species && pokemon_species.value() == "Cinderace-Gmax") return "G-Max Fire Ball";
   }
   if (move_type == ENUMS::TypeName::Normal) 
   {
      if (pokemon_species && pokemon_species.value() == "Eevee-Gmax") return "G-Max Cuddle";
      if (pokemon_species && pokemon_species.value() == "Meowth-Gmax") return "G-Max Gold Rush";
      if (pokemon_species && pokemon_species.value() == "Snorlax-Gmax") return "G-Max Replenish";
      if (!(move_name && move_name.value() == "Weather Ball" || move_name && move_name.value() == "Terrain Pulse")) 
      {
         if (pokemon_ability && pokemon_ability.value() == "Pixilate") return "Max Starfall";
         if (pokemon_ability && pokemon_ability.value() == "Aerilate") return "Max Airstream";
         if (pokemon_ability && pokemon_ability.value() == "Refrigerate") return "Max Hailstorm";
         if (pokemon_ability && pokemon_ability.value() == "Galvanize") return "Max Lightning";
      }
   }
   if (move_type == ENUMS::TypeName::Fairy) 
   {
      if (pokemon_species && pokemon_species.value() == "Alcremie-Gmax") return "G-Max Finale";
      if (pokemon_species && pokemon_species.value() == "Hatterene-Gmax") return "G-Max Smite";
   }
   if (move_type == ENUMS::TypeName::Steel) 
   {
      if (pokemon_species && pokemon_species.value() == "Copperajah-Gmax") return "G-Max Steelsurge";
      if (pokemon_species && pokemon_species.value() == "Melmetal-Gmax") return "G-Max Meltdown";
   }
   if (move_type == ENUMS::TypeName::Electric) 
   {
      if (pokemon_species && pokemon_species.value() == "Pikachu-Gmax") return "G-Max Volt Crash";
      if (pokemon_species && pokemon_species.value().starts_with("Toxtricity") &&
          pokemon_species.value().ends_with("Gmax")) return "G-Max Stun Shock";
   }
   if (move_type == ENUMS::TypeName::Grass) 
   {
      if (pokemon_species && pokemon_species.value() == "Appletun-Gmax") return "G-Max Sweetness";
      if (pokemon_species && pokemon_species.value() == "Flapple-Gmax") return "G-Max Tartness";
      if (pokemon_species && pokemon_species.value() == "Rillaboom-Gmax") return "G-Max Drum Solo";
      if (pokemon_species && pokemon_species.value() == "Venusaur-Gmax") return "G-Max Vine Lash";
   }
   if (move_type == ENUMS::TypeName::Water) 
   {
      if (pokemon_species && pokemon_species.value() == "Blastoise-Gmax") return "G-Max Cannonade";
      if (pokemon_species && pokemon_species.value() == "Drednaw-Gmax") return "G-Max Stonesurge";
      if (pokemon_species && pokemon_species.value() == "Inteleon-Gmax") return "G-Max Hydrosnipe";
      if (pokemon_species && pokemon_species.value() == "Kingler-Gmax") return "G-Max Foam Burst";
      if (pokemon_species && pokemon_species.value() == "Urshifu-Rapid-Strike-Gmax") return "G-Max Rapid Flow";
   }
   if (move_type == ENUMS::TypeName::Dark) 
   {
      if (pokemon_species && pokemon_species.value() == "Grimmsnarl-Gmax") return "G-Max Snooze";
      if (pokemon_species && pokemon_species.value() == "Urshifu-Gmax") return "G-Max One Blow";
   }
   if (move_type == ENUMS::TypeName::Poison && pokemon_species && pokemon_species.value() == "Garbodor-Gmax") return "G-Max Malodor";
   if (move_type == ENUMS::TypeName::Fighting && pokemon_species && pokemon_species.value() == "Machamp-Gmax") return "G-Max Chi Strike";
   if (move_type == ENUMS::TypeName::Ghost && pokemon_species && pokemon_species.value() == "Gengar-Gmax") return "G-Max Terror";
   if (move_type == ENUMS::TypeName::Ice && pokemon_species && pokemon_species.value() == "Lapras-Gmax") return "G-Max Resonance";
   if (move_type == ENUMS::TypeName::Flying && pokemon_species && pokemon_species.value() == "Corviknight-Gmax") return "G-Max Wind Rage";
   if (move_type == ENUMS::TypeName::Dragon && pokemon_species && pokemon_species.value() == "Duraludon-Gmax") return "G-Max Depletion";
   if (move_type == ENUMS::TypeName::Psychic && pokemon_species && pokemon_species.value() == "Orbeetle-Gmax") return "G-Max Gravitas";
   if (move_type == ENUMS::TypeName::Rock && pokemon_species && pokemon_species.value() == "Coalossal-Gmax") return "G-Max Volcalith";
   if (move_type == ENUMS::TypeName::Ground && pokemon_species && pokemon_species.value() == "Sandaconda-Gmax") return "G-Max Sandblast";
   if (move_type == ENUMS::TypeName::Dark && pokemon_species && pokemon_species.value() == "Grimmsnarl-Gmax") return "G-Max Snooze";
   return "Max " + MAXMOVES_TYPING.at(move_type);
}

Move::Move
(
   const ENUMS::GenerationNumber gen_in,
   const std::string name_in,
   const State::Move options
) 
{
   const int g = static_cast<int>(gen_in);

   name = options.name ? options.name.value() : name_in;
   original_name = name;
   Data::Move data;
   if (options.overrides)
   {
      data = Data::Moves::Instance().ExtendMove
      (
         Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(name)), 
         options.overrides.value()
      );
   } 
   else
   {
      data = Data::Moves::Instance().ExtendMove
      (
         Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(name))
      );
   }

   hits = 1;
   // If is_z_move but there isn't a corresponding z-move, use the original move
   if (options.use_max && options.use_max.value() && 
       data.max_move) 
   {
      const std::string max_move_name = GetMaxMoveName
      (
         data.type.value(),
         data.name,
         options.species,
         (data.category && data.category.value() == ENUMS::MoveCategory::Status),
         options.ability
      );
      const Data::Move max_move = Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(max_move_name));
      
      auto MaxPower = [&]() -> int 
      {
         if (max_move_name == "G-Max Drum Solo" ||
             max_move_name == "G-Max Fire Ball" ||
             max_move_name == "G-Max Hydrosnipe")
         {
            return 160;
         }

         // TODO: checking basePower == 10 is fragile (what if the maxMove"s basePower is
         // overridden?) and also fails for Max Flare, which is strangely 100 BP in the game data
         if ((max_move.bp && max_move.bp.value() == 10) || 
             max_move_name == "Max Flare") 
         {
            return Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(data.max_move.value())).bp.value();
         }
         return max_move.bp.value();
      };

      Data::Move temp{.name = max_move_name, .bp = MaxPower(), .category = data.category,};
      data = Data::Moves::Instance().ExtendMove
      (   
         max_move, 
         temp
      );
   }

   if (options.use_z && options.use_z.value() && 
       data.z_move) 
   {
      const std::string z_move_name = GetZMoveName(data.name.value(), data.type.value(), options.item);
      const Data::Move z_move = Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(z_move_name));
      Data::Move temp = 
      {
         .name = z_move_name,
         .bp = (z_move.bp && z_move.bp.value() == 1) 
            ? std::optional<int>{Data::Moves::Instance().GetMoveByGen_ID(g, Util::ToID(data.z_move.value())).bp.value()} 
            : z_move.bp,
         .category = data.category
      };
      data = Data::Moves::Instance().ExtendMove
      (
         z_move, 
         temp
      );
   } 
   else 
   {
      if (data.multihit) 
      {
         if (data.multiaccuracy && data.multihit.value().size() == 1) 
         {
            hits = options.hits
               ? options.hits.value() 
               : data.multihit.value().at(0);
         } 
         else 
         {
            if (data.multihit.value().size() == 1) 
            {
               hits = data.multihit.value().at(0);
            } else if (options.hits) 
            {
               hits = options.hits.value();
            } 
            else 
            {
               hits = (options.ability && options.ability.value() == "Skill Link")
                  ? data.multihit.value().at(1)
                  : data.multihit.value().at(0) + 1;
            }
         }
      }
      times_used_with_metronome = options.times_used_with_metronome 
         ? options.times_used_with_metronome.value() 
         : 0;
   }
   gen = gen_in;
   name = data.name ? data.name.value() : name ;
   ability = options.ability;
   item = options.item;
   use_z = options.use_z;
   use_max = options.use_max;
   overrides = options.overrides;
   species = options.species;

   bp = data.bp ? data.bp.value() : bp;
   // These moves have a type, but the damage they deal is typeless so we override it
   const bool typeless_damage =
      (g >= 2 && data.id == "struggle") ||
      (g <= 4 && (data.id == "futuresight" || data.id == "doomdesire"));
   type = typeless_damage ? ENUMS::TypeName::QQQ : data.type ? data.type.value() : type;
   category = data.category ? data.category.value()
      : (g < 4 
         ? (SPECIAL.contains(data.type ? data.type.value() : type) 
            ? ENUMS::MoveCategory::Special : ENUMS::MoveCategory::Physical) 
         : ENUMS::MoveCategory::Status);

   const ENUMS::StatID stat = category == ENUMS::MoveCategory::Special 
      ? ENUMS::StatID::spa 
      : ENUMS::StatID::atk;
   if (data.self && data.self.value().boosts && 
       data.self.value().boosts.value().find(stat) != data.self.value().boosts.value().end() && 
       data.self.value().boosts.value().at(stat) < 0) 
   {
      drops_stats = std::abs(data.self.value().boosts.value().at(stat));
   }
   times_used = (drops_stats && options.times_used) || 1;
   secondaries = data.secondaries ? data.secondaries.value() : false;
   // For the purposes of the damage formula only "all_adjacent" and "all_adjacent_foes" matter, so we
   // simply default to "any" for the others even though they may not actually be "any"-target
   target = data.target ? data.target.value() : ENUMS::MoveTarget::any;
   recoil = data.recoil;
   has_crash_damage = data.has_crash_damage ? data.has_crash_damage.value() : false;
   mind_blown_recoil = data.mind_blown_recoil ? data.mind_blown_recoil.value() : false;
   struggle_recoil = data.struggle_recoil ? data.struggle_recoil.value() : false;
   is_crit = options.is_crit ? options.is_crit.value() : false || 
             data.will_crit ? data.will_crit.value() : false ||
             // These don"t *always* crit (255/256 chance), but for the purposes of the calc they do
             g == 1 && (data.id == "crabhammer" ||
                        data.id == "razorleaf" ||
                        data.id ==  "slash" ||
                        data.id == "karate chop");
   is_stellar_first_use = options.is_stellar_first_use ? options.is_stellar_first_use.value() : false;
   drain = data.drain;
   flags = data.flags ? data.flags.value() : ENUMS::MoveFlags{};
   // The calc doesn't currently care about negative priority moves so we simply default to 0
   priority = data.priority ? data.priority.value() : 0;

   ignore_defensive = data.ignore_defensive ? data.ignore_defensive.value() : false;
   override_offensive_stat = data.override_offensive_stat;
   override_defensive_stat = data.override_defensive_stat;
   override_offensive_pokemon = data.override_offensive_pokemon;
   override_defensive_pokemon = data.override_defensive_pokemon;
   breaks_protect = data.breaks_protect ? data.breaks_protect.value() : false;
   is_z = data.is_z ? data.is_z.value() : false;
   is_max = data.is_max ? data.is_max.value() : false;
   multiaccuracy = data.multiaccuracy ? data.multiaccuracy.value() : false;

   if (!bp) 
   {
      // Assume max happiness for these moves because the calc doesn't support happiness
      if (data.id == "return" ||
          data.id == "frustration" ||
          data.id == "pikapapow" ||
          data.id == "veeveevolley") 
      {
         bp = 102;
      }
   }
}

bool Move::Named(std::initializer_list<std::string> names) const 
{
   return std::find(names.begin(), names.end(), name) != names.end();
}

bool Move::HasType(const std::initializer_list<ENUMS::TypeName>& types_in) const
{
   return std::find(types_in.begin(), types_in.end(), type) != types_in.end();
}

bool Move::HasType(const std::vector<ENUMS::TypeName>& types_in) const
{
   return std::find(types_in.begin(), types_in.end(), type) != types_in.end();
}

}
}

