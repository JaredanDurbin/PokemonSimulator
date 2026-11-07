// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <algorithm>
#include <fstream>
#include <numeric>

#include "./../include/smorgans_demise/turn_matrix.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

void TurnMatrix::AppendRows
(
   std::vector<std::vector<std::pair<float, float>>>& dst,
   const std::vector<std::vector<std::pair<float, float>>>& src
)
{
   if (dst.size() != src.size()) 
   {
      throw std::runtime_error("Vectors must have the same number of rows.");
   }

   for (size_t i = 0; i < dst.size(); ++i) 
   {
      dst[i].insert(dst[i].end(), src[i].begin(), src[i].end());
   }
}

void TurnMatrix::AddRows
(
   std::vector<std::vector<std::pair<float, float>>>& dst,
   const std::vector<std::vector<std::pair<float, float>>>& src
)
{
   if (!dst.empty() && !src.empty() && dst[0].size() != src[0].size()) 
   {
      throw std::runtime_error("Row counts must match");
   }

   for (size_t i = 0; i < src.size(); ++i) 
   {
      dst.push_back(src.at(i));
   }
}

TurnMatrix::TurnMatrix
(
   const std::map<std::string, 
   std::map<std::string, 
   std::map<std::string, std::unique_ptr<Result::Result>>>>& team1_in,
   const std::map<std::string, 
   std::map<std::string, 
   std::map<std::string, std::unique_ptr<Result::Result>>>>& team2_in
)
{
   for (const auto& [att_poke, def_move_res] : team1_in)
   {
      std::vector<std::vector<std::pair<float, float>>> matrix_line{};

      for (const auto& [def_poke, move_res] : def_move_res)
      {
         std::vector<std::vector<std::pair<float, float>>> mini_matrix{};

         for (const auto& [att_move, res1] : move_res)
         {
            std::vector<std::pair<float, float>> mini_matrix_line{};

            const auto& att_dams = res1->GetDamageSpread();
            const float att_size = att_dams.size();
            const float att_dam 
               = std::accumulate(att_dams.begin(), att_dams.end(), 0.0) / att_size;

            std::string att_poke_move = att_poke + ";" + att_move;
            if (std::find(row_titles.begin(), row_titles.end(), att_poke_move) == row_titles.end())
            {
               row_titles.push_back(att_poke_move);
            }

            for (const auto& [def_move, res2] : team2_in.at(def_poke).at(att_poke))
            {
               std::string def_poke_move = def_poke + ";" + def_move;
               if (std::find(column_titles.begin(), column_titles.end(), def_poke_move) 
                   == column_titles.end())
               {
                  column_titles.push_back(def_poke_move);
               }

               mini_matrix_line.push_back(std::make_pair(res1->GetUtility(), res2->GetUtility()));
            }

            mini_matrix.push_back(mini_matrix_line);
         }

         if (matrix_line.empty())
         {
            matrix_line = mini_matrix;
         }
         else
         {
            AppendRows(matrix_line, mini_matrix);
         }
      }

      if (matrix.empty())
      {
         matrix = matrix_line;
      }
      else
      {
         AddRows(matrix, matrix_line);
      }
   }

   // DEBUG
   //int a = 0;
}

std::string TurnMatrix::ToString() const
{
   std::string out = "         ";
   for (const std::string& titles : column_titles)
   {
      out += titles + "   ";
   }
   out += "\n";

   for (int i = 0; i < row_titles.size(); i++)
   {
      out += row_titles.at(i) + "   ";
      for (const auto& nums : matrix.at(i))
      {
         out += std::to_string(nums.first) + "/" + std::to_string(nums.second) + "   ";
      }
      out += "\n";
   }

   return out;
}

void TurnMatrix::ToCSV() const
{
   std::ofstream csv_file;
   csv_file.open("./../output/matrix.csv");

   csv_file << ",";
   for (const std::string& titles : column_titles)
   {
      csv_file << titles + ",";
   }
   csv_file << "\n";

   for (int i = 0; i < row_titles.size(); i++)
   {
      csv_file << row_titles.at(i) + ",";
      for (const auto& nums : matrix.at(i))
      {
         csv_file << std::to_string(nums.first) + "/" + std::to_string(nums.second) + ",";
      }
      csv_file << "\n";
   }

   csv_file.close();
}

}
