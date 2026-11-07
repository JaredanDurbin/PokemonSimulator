#include <iostream>

#include "./../include/smorgans_demise/von_neumann.hpp"

std::string IntVectorToString(const std::vector<int> vec)
{
   std::string out = "{";
   for (int num : vec)
   {
      out += std::to_string(num) + ", ";
   }
   out.erase(out.size() - 2);
   out += "}";
   return out;
}

void PrintVersusData(const SmorgansDemise::Versus& data_in)
{
   for (const auto& [p1, data1] : data_in)
   {
      for (const auto& [p2, data2] : data1)
      {
         for (const auto& [m, data3] : data2)
         {
            std::cout << p1 << ": " << p2 << ": " << m << ": " << data3->FullDescription() << "\n";
            //std::cout << p1 << ": " << p2 << ": " << m << ": " 
            //          << data3->MoveDescription() << "\n";
            std::cout << p1 << ": " << p2 << ": " << m << ": " << data3->Recoil().second << "\n";
            std::cout << p1 << ": " << p2 << ": " << m << ": " << data3->Recovery().second << "\n";
            std::cout << IntVectorToString(data3->GetDamageSpread()) << "\n";
         }
      }
   }
}

int main()
{
   SmorgansDemise::VonNeumann calc;
   const auto& team1 = calc.GetData().GetTeam("team-1");

   for (const auto& mem : team1)
   {
      std::cout << "Team 1: " << mem.GetName() << "\n";
   }

   const auto& team2 = calc.GetData().GetTeam("team-2");

   for (const auto& mem : team2)
   {
      std::cout << "Team 2: " << mem.GetName() << "\n";
   }

   const auto& versus_data = calc.GetVersuses();

   PrintVersusData(versus_data.first);
   std::cout << "\n";
   PrintVersusData(versus_data.second);
   //std::cout << calc.GetTurnMatrix().ToString();
   calc.GetTurnMatrix().ToCSV();

   return 0;
}
