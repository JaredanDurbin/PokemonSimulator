#include "./../include/result.hpp"

#include <numeric>

#include "./../include/data/moves.h"
#include "./../include/util/util.h"
#include "./../include/stats.hpp"
#include "./../include/data/natures.h"

namespace PokemonDamageCalcCPP
{
namespace Result
{

std::vector<int> Result::GetDamageSpread(const std::string& notation) const
{
   if (notation != "%")
   {
      return std::visit([](const auto& value)
      {
         using T = std::decay_t<decltype(value)>;

         if constexpr (std::is_same_v<T, int>)
         {
            return std::vector<int>{value};
         }
         else if constexpr (std::is_same_v<T, std::vector<int>>)
         {
            return value;
         }
         else if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            return std::vector<int>{value.first + value.second};
         }
         else if constexpr (std::is_same_v<T, std::pair<std::vector<int>, std::vector<int>>>)
         {
            std::vector<int> out{};
            for (auto parent : value.first)
            {
               for (auto child : value.second)
               {
                  out.push_back(parent + child);
               }
            }

            return out;
         }

         return std::vector<int>{};
      }, 
      damage);
   }

   return std::visit([this, notation](const auto& value)
   {
      using T = std::decay_t<decltype(value)>;

      if constexpr (std::is_same_v<T, int>)
      {
         return std::vector<int>{Description::ToDisplay(notation, value, defender.MaxHP())};
      }
      else if constexpr (std::is_same_v<T, std::vector<int>>)
      {
         std::vector<int> out{};
         for (int val : value)
         {
            out.push_back(Description::ToDisplay(notation, val, defender.MaxHP()));
         }
         return out;
      }
      else if constexpr (std::is_same_v<T, std::pair<int, int>>)
      {
         return std::vector<int>
         {
            Description::ToDisplay(notation, value.first + value.second, defender.MaxHP())
         };
      }
      else if constexpr (std::is_same_v<T, std::pair<std::vector<int>, std::vector<int>>>)
      {
         std::vector<int> out{};
         for (auto parent : value.first)
         {
            for (auto child : value.second)
            {
               out.push_back(Description::ToDisplay(notation, parent + child, defender.MaxHP()));
            }
         }

         return out;
      }

      return std::vector<int>{};
   }, 
   damage);
   
}

std::pair<int, int> Result::Range()
{
   Description::DamageRangeResult range = Description::DamageRange(damage);
   return std::visit
   (
      [](const auto& d) -> std::pair<int, int>
      {
         using T = std::decay_t<decltype(d)>;

         if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            return d;
         }
         // Standard Damage
         else if constexpr (std::is_same_v<T, std::pair<std::pair<int, int>, std::pair<int, int>>>)
         {
            return std::make_pair<int, int>(d.first.first + d.first.second, 
                                             d.second.first + d.second.second);
         }

         return std::make_pair(0, 0);
      },
      damage
   );
}

std::string Result::FullDescription(std::string notation, bool err)
{
   return Description::Display(
      gen,
      attacker,
      defender,
      move,
      field,
      damage,
      raw_desc,
      notation,
      err
   );
}

std::string Result::MoveDescription(std::string notation)
{
   return Description::DisplayMove
   (
      gen,
      attacker,
      defender,
      move,
      damage,
      notation
   );
}

std::pair<std::pair<int, int>, std::string> Result::Recovery(const std::string& notation) const
{
   return Description::GetRecovery(gen, attacker, defender, move, damage, notation);
}

std::pair<std::pair<int, int>, std::string> Result::Recoil(const std::string& notation) const
{
   return Description::GetRecoil
   (
      gen,
      attacker,
      defender,
      move,
      damage,
      notation
   );
}

Description::KOChanceHelper Result::KOChance(bool err)
{
   return Description::GetKOChance
   (
      gen,
      attacker,
      defender,
      move,
      field,
      damage,
      err
   );
}

float Result::GetUtility() const
{
   auto dam = GetDamageSpread();
   float dam_size = dam.size();
   auto recover = Recovery().first;
   auto recoil = Recoil().first;

   return (std::accumulate(dam.begin(), dam.end(), 0.0) / dam_size) +
          ((recover.first + recover.second) / 2.0) - 
          ((recoil.first + recoil.second) / 2.0);
}

}
}
