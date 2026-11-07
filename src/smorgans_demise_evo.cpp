// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./../include/smorgans_demise/evo.hpp"

#include <iostream>

#include "./../include/calc_util.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

std::pair<bool, bool> EffortValueOptimizer::DeterminePhysOrSpecAtker
(
   const Pokemon::Pokemon& pokemon
) const
{
   int g = static_cast<int>(data->GetGeneration());

   bool phys = false;
   bool spec = false;
   for (const auto& move_name : pokemon.GetMoves())
   {
      auto move = Data::Moves::Instance().GetMoveByGen(g, move_name);
      if (move.category == ENUMS::MoveCategory::Physical) phys = true;
      else if (move.category == ENUMS::MoveCategory::Special) spec = true;
   }

   return std::make_pair(phys, spec);
}

std::pair<int, int> EffortValueOptimizer::DeterminePhysOrSpecThreats() const
{
   int phys = 0;
   int spec = 0;
   for (const auto& pokemon : threats)
   {
      auto phys_or_spec = DeterminePhysOrSpecAtker(pokemon);
      if (phys_or_spec.first) phys++;
      if (phys_or_spec.second) spec++;
   }

   return std::make_pair(phys, spec);
}

std::set<int> EffortValueOptimizer::GetThreatsSpeeds() const
{
   std::set<int> out{};
   for (const auto& pokemon : threats)
   {
      const int speed = CalcUtil::GetModifiedStat(pokemon.GetRawStats().at(ENUMS::StatID::spe),
                                                  pokemon.GetBoosts().at(ENUMS::StatID::spe),
                                                  data->GetGeneration());
      out.insert(speed);
   }

   return out;
}

std::pair<std::set<int>, std::set<int>> EffortValueOptimizer::GetThreatsDefenses() const
{
   std::set<int> defenses{};
   std::set<int> special_defenses{};
   for (const auto& pokemon : threats)
   {
      const int defense = CalcUtil::GetModifiedStat(pokemon.GetRawStats().at(ENUMS::StatID::def),
                                                    pokemon.GetBoosts().at(ENUMS::StatID::def),
                                                    data->GetGeneration());
      defenses.insert(defense);

      const int special_defense = CalcUtil::GetModifiedStat
      (
         pokemon.GetRawStats().at(ENUMS::StatID::spd),
         pokemon.GetBoosts().at(ENUMS::StatID::spd),
         data->GetGeneration()
      );
      special_defenses.insert(special_defense);
   }

   return std::make_pair(defenses, special_defenses);
}

int EffortValueOptimizer::OptimizeSpeed
(
   Pokemon::Pokemon& pokemon, 
   const std::set<int>& speeds, 
   int evs_left
)
{
   auto _s = ENUMS::StatID::spe;
   auto _g = data->GetGeneration();
   auto speeds_iter = --speeds.end();
   int speed_ev = evs_left <= 252 ? evs_left : 252;

   if (speed_ev % 4 != 0)
   {
      speed_ev -= (speed_ev % 4);
   }

   pokemon.SetEV(_s, speed_ev);
   
   while (pokemon.CalcStat(_g, _s) < *speeds_iter && speeds_iter != speeds.begin()) --speeds_iter;
   
   if (speeds_iter == speeds.begin() && pokemon.CalcStat(_g, _s) < *speeds_iter) 
   {
      pokemon.SetEV(_s, 0);
      return 0;
   }
   
   while (pokemon.CalcStat(_g, _s) > *speeds_iter && 
          speed_ev >= 0 && 
          pokemon.GetEVs().at(_s) <= 252) 
   {
      speed_ev -= 4;
      pokemon.SetEV(_s, speed_ev);
   }
   speed_ev += 4;
   pokemon.SetEV(_s, speed_ev);

   return pokemon.GetEVs().at(_s);
}

int EffortValueOptimizer::OptimizeAttack
(
   Pokemon::Pokemon& pokemon,
   const std::pair<std::set<int>, std::set<int>>& defenses,
   int evs_left
)
{
   auto phys_or_spec = DeterminePhysOrSpecAtker(pokemon);
   auto _a = ENUMS::StatID::atk;
   auto _s = ENUMS::StatID::spa;
   auto _g = data->GetGeneration();
   signed int attack_evs = evs_left != 252 ? evs_left : 252;
   if (attack_evs > 252 && ((phys_or_spec.first && !phys_or_spec.second) ||
                            (!phys_or_spec.first && phys_or_spec.second)))
   {
      attack_evs = 252;
   }

   if (!phys_or_spec.first && !phys_or_spec.second) return evs_left - attack_evs;

   std::vector<bool> threats_b(threats.size(), true);
   int last_stat = 0;
   // This is only for dual attackers.
   bool use_spec = false;
   while (attack_evs >= 0)
   {
      for (int i = 0; i < pokemon.GetMoves().size(); i++)
      {
         if (Data::Moves::Instance().GetMoveByGen
         (
            static_cast<int>(_g),
            pokemon.GetMoves().at(i)
         ).category == ENUMS::MoveCategory::Status)
         {
            continue;
         }

         Move::Move move(_g, pokemon.GetMoves().at(i));
         for (int j = 0; j < threats_b.size(); j++)
         {
            if (!threats_b.at(j)) continue;

            Result::Result result = f
            (
               _g, 
               pokemon, 
               threats.at(j), 
               move,
               data->GetFields().at(std::make_pair("f1", "s1"))
            );

            if (result.GetDamageSpread().at(0) >= 95)
            {
               threats_b[j] = false;
               last_stat = pokemon.GetEVs().at(_a) || !use_spec
                  ? pokemon.GetEVs().at(_a) 
                  : pokemon.GetEVs().at(_s);
            }
         }
      }

      if (std::find(threats_b.begin(), threats_b.end(), true) == threats_b.end())
      {
         break;
      }

      if (phys_or_spec.first && !use_spec)
      {
         attack_evs -= 4;
         pokemon.SetEV(_a, pokemon.GetEVs().at(_a) + 4);
         pokemon.SetRawStat(_a, pokemon.CalcStat(_g, _a));
         pokemon.SetStat(_a, pokemon.CalcStat(_g, _a));
      }
      else if (phys_or_spec.second)
      {
         attack_evs -= 4;
         pokemon.SetEV(_s, pokemon.GetEVs().at(_s) + 4);
         pokemon.SetRawStat(_s, pokemon.CalcStat(_g, _s));
         pokemon.SetStat(_s, pokemon.CalcStat(_g, _s));
      }

      // DEBUG
      //std::cout << std::to_string(attack_evs) << "\n";

      if (attack_evs < 0)
      {
         if (phys_or_spec.first && !use_spec)
         {
            attack_evs = evs_left - last_stat;
            pokemon.SetEV(_a, last_stat);
            pokemon.SetRawStat(_a, pokemon.CalcStat(_g, _a));
            pokemon.SetStat(_a, pokemon.CalcStat(_g, _a));

            if (!phys_or_spec.second)
            {
               break;
            }
         }
         else if (phys_or_spec.second)
         {
            attack_evs = evs_left - last_stat;
            pokemon.SetEV(_s, last_stat);
            pokemon.SetRawStat(_s, pokemon.CalcStat(_g, _s));
            pokemon.SetStat(_s, pokemon.CalcStat(_g, _s));

            if (!phys_or_spec.first)
            {
               break;
            }
         }

         use_spec = true;
      }
   }

   return evs_left - attack_evs;
}

int EffortValueOptimizer::OptimizeDefenses(Pokemon::Pokemon& pokemon, int evs_left)
{
   auto _g = data->GetGeneration();
   auto _d = ENUMS::StatID::def;
   auto _s = ENUMS::StatID::spd;
   signed int defense_evs = evs_left;
   int orig_def_evs = pokemon.GetEVs().at(_d);
   int orig_spec_evs = pokemon.GetEVs().at(_s);

   std::pair<int, int> phys_and_spec_atks = std::make_pair(-1, -1);
   int last_def_ev = 0;
   int last_spec_ev = 0;
   while (defense_evs >= 0)
   {
      std::map<ENUMS::MoveCategory, std::set<int>> category_damage{};
      for (int i = 0; i < threats.size(); i++)
      {
         for (int j = 0; j < threats.at(i).GetMoves().size(); j++)
         {
            Move::Move move(_g, threats.at(i).GetMoves().at(j));
            if (move.GetMoveCategory() == ENUMS::MoveCategory::Status)
            {
               continue;
            }

            Result::Result result = f
            (
               _g, 
               threats.at(i), 
               pokemon,
               move,
               data->GetFields().at(std::make_pair("f1", "s1"))
            );

            // DEBUG
            //std::cout << pokemon.GetName() << " - " 
            //          << std::to_string(*--result.GetDamageSpread().end()) << "\n";

            if (*--result.GetDamageSpread().end() >= 95.0)
            {
               category_damage[move.GetMoveCategory()].insert(*--result.GetDamageSpread().end());
            }
         }
      }

      if (phys_and_spec_atks.first < 0 && phys_and_spec_atks.second < 0)
      {
         phys_and_spec_atks.first = category_damage[ENUMS::MoveCategory::Physical].size();
         phys_and_spec_atks.second = category_damage[ENUMS::MoveCategory::Special].size();
      }
      else if (phys_and_spec_atks.first != category_damage[ENUMS::MoveCategory::Physical].size())
      {
         last_def_ev = pokemon.GetEVs().at(_d) - orig_def_evs;
         phys_and_spec_atks.first = category_damage[ENUMS::MoveCategory::Physical].size();
      }
      else if (phys_and_spec_atks.second != category_damage[ENUMS::MoveCategory::Special].size())
      {
         last_spec_ev = pokemon.GetEVs().at(_s) - orig_spec_evs;
         phys_and_spec_atks.second = category_damage[ENUMS::MoveCategory::Special].size();
      }

      if (category_damage[ENUMS::MoveCategory::Physical].size() > 0 &&
          category_damage[ENUMS::MoveCategory::Physical].size() >= 
             category_damage[ENUMS::MoveCategory::Special].size() &&
          pokemon.GetEVs().at(_d) <= 248)
      {
         defense_evs -= 4;
         pokemon.SetEV(_d, pokemon.GetEVs().at(_d) + 4);
         pokemon.SetRawStat(_d, pokemon.CalcStat(_g, _d));
         pokemon.SetStat(_d, pokemon.CalcStat(_g, _d));
      }
      else if (category_damage[ENUMS::MoveCategory::Special].size() > 0 &&
               pokemon.GetEVs().at(_s) <= 248)
      {
         defense_evs -= 4;
         pokemon.SetEV(_s, pokemon.GetEVs().at(_s) + 4);
         pokemon.SetRawStat(_s, pokemon.CalcStat(_g, _s));
         pokemon.SetStat(_s, pokemon.CalcStat(_g, _s));
      }

      if ((defense_evs < 0) ||
          (category_damage[ENUMS::MoveCategory::Physical].size() > 0 &&
           category_damage[ENUMS::MoveCategory::Special].size() == 0 &&
           pokemon.GetEVs().at(_d) == 252) || 
          (category_damage[ENUMS::MoveCategory::Special].size() > 0 &&
           category_damage[ENUMS::MoveCategory::Physical].size() == 0 &&
           pokemon.GetEVs().at(_s) == 252) || 
          (category_damage[ENUMS::MoveCategory::Special].size() > 0 &&
           category_damage[ENUMS::MoveCategory::Physical].size() > 0 &&
           pokemon.GetEVs().at(_s) == 252 && pokemon.GetEVs().at(_d) == 252) ||
          (category_damage[ENUMS::MoveCategory::Special].size() == 0 &&
           category_damage[ENUMS::MoveCategory::Physical].size() == 0))
      {
         defense_evs = evs_left - last_def_ev - last_spec_ev;

         pokemon.SetEV(_d, last_def_ev + orig_def_evs);
         pokemon.SetRawStat(_d, pokemon.CalcStat(_g, _d));
         pokemon.SetStat(_d, pokemon.CalcStat(_g, _d));

         pokemon.SetEV(_s, last_spec_ev + orig_spec_evs);
         pokemon.SetRawStat(_s, pokemon.CalcStat(_g, _s));
         pokemon.SetStat(_s, pokemon.CalcStat(_g, _s));

         break;
      }
   }

   return evs_left - defense_evs;
}

int EffortValueOptimizer::OptimizeHP(Pokemon::Pokemon& pokemon, int evs_left, bool attacker)
{
   auto _g = data->GetGeneration();
   auto _h = ENUMS::StatID::hp;
   if (attacker)
   {
      if (evs_left > 252) pokemon.SetEV(_h, 252);
      else pokemon.SetEV(_h, evs_left);

      pokemon.SetRawStat(_h, pokemon.CalcStat(_g, _h));
      pokemon.SetStat(_h, pokemon.CalcStat(_g, _h));

      return pokemon.GetEVs().at(_h);
   }


   signed int hp_evs = evs_left;
   int last_hp_ev = 0;
   int last_damage_count = 0;

   while (hp_evs >= 0)
   {
      std::set<int> damage{};
      for (int i = 0; i < threats.size(); i++)
      {
         for (int j = 0; j < threats.at(i).GetMoves().size(); j++)
         {
            Move::Move move(_g, threats.at(i).GetMoves().at(j));
            if (move.GetMoveCategory() == ENUMS::MoveCategory::Status)
            {
               continue;
            }

            Result::Result result = f
            (
               _g, 
               threats.at(i), 
               pokemon,
               move,
               data->GetFields().at(std::make_pair("f1", "s1"))
            );

            // DEBUG
            //std::cout << pokemon.GetName() << " - " 
            //          << std::to_string(*--result.GetDamageSpread().end()) << "\n";

            if (*--result.GetDamageSpread().end() >= 95.0)
            {
               damage.insert(*--result.GetDamageSpread().end());
            }
         }
      }

      if (last_damage_count != damage.size())
      {
         last_hp_ev = pokemon.GetEVs().at(_h);
         last_damage_count = damage.size();
      }

      if (pokemon.GetEVs().at(_h) <= 248)
      {
         hp_evs -= 4;
         pokemon.SetEV(_h, pokemon.GetEVs().at(_h) + 4);
         pokemon.SetRawStat(_h, pokemon.CalcStat(_g, _h));
         pokemon.SetStat(_h, pokemon.CalcStat(_g, _h));
      }

      if (hp_evs < 0 || pokemon.GetEVs().at(_h) == 252 || damage.size() == 0)
      {
         hp_evs = evs_left - last_hp_ev;

         pokemon.SetEV(_h, last_hp_ev);
         pokemon.SetRawStat(_h, pokemon.CalcStat(_g, _h));
         pokemon.SetStat(_h, pokemon.CalcStat(_g, _h));

         break;
      }
   }

   return evs_left - hp_evs;
}

void EffortValueOptimizer::OptimizeAttackers()
{
   for (auto& pokemon : opt_atk)
   {
      int ev_total = 510;
      ev_total -= OptimizeSpeed(pokemon, GetThreatsSpeeds());
      ev_total -= OptimizeAttack(pokemon, GetThreatsDefenses(), ev_total);
      ev_total -= OptimizeDefenses(pokemon, ev_total);
      ev_total -= OptimizeHP(pokemon, ev_total);

      // DEBUG
      std::cout << pokemon.GetName() << " EVs Left: " << ev_total << "\n";
   }
}

void EffortValueOptimizer::OptimizeDefenders()
{
   for (auto& pokemon : opt_def)
   {
      int ev_total = 510;
      ev_total -= OptimizeDefenses(pokemon, ev_total);
      ev_total -= OptimizeHP(pokemon, ev_total, false);
      ev_total -= OptimizeAttack(pokemon, GetThreatsDefenses(), ev_total);
      ev_total -= OptimizeHP(pokemon, ev_total);
      ev_total -= OptimizeDefenses(pokemon, ev_total);
      ev_total -= OptimizeSpeed(pokemon, GetThreatsSpeeds(), ev_total);

      // DEBUG
      std::cout << pokemon.GetName() << " EVs Left: " << ev_total << "\n";
   }
}

EffortValueOptimizer::EffortValueOptimizer()
{
   OptimizeAttackers();
   OptimizeDefenders();
}

}