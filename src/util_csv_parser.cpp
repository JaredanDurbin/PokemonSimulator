// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./../include/util/csv_parser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "./../include/util/util.h"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
namespace PokemonDamageCalcCPP
{
namespace Util
{
namespace CSV
{

std::vector<std::string> GetNextLineAndSplitIntoTokens(std::istream& str)
{
   // Initialize the "result".
   std::vector<std::string>   result;
   // Initialize the "line".
   std::string                line;
   // Put the stream line into the "line".
   std::getline(str, line);

   // We will do this through a "stringstream".
   std::stringstream          line_stream(line);
   // The cells we will push back.
   std::string                cell;

   // While we have lines to get push back the cells which
   // is the information.
   while(std::getline(line_stream, cell, ','))
   {
      result.push_back(cell);
   }
   // This checks for a trailing comma with no data after it.
   if (!line_stream && cell.empty())
   {
      // If there was a trailing comma then add an empty element.
      result.push_back("");
   }
   return result;
}

std::vector<std::string> SplitStringByDelimiter(const char del,
                                                const std::string& str)
{
   // Create a stringstream object to str
   std::stringstream ss(str);
   
   // Temporary object to store the splitted
   // string
   std::string t;

   std::vector<std::string> out;
   // Splitting the str string by delimiter
   while (getline(ss, t, del))
   {
      out.push_back(t);
   }
   
   return out;
}

CSVLoader::CSVLoader(std::string file)
{
   std::fstream file_to_be_read(file, std::ios_base::in);
   if (!file_to_be_read) std::cerr << "Could not open the move file.\n";

   CSVFile data;
   // If the move file is open.
   if (file_to_be_read.is_open())
   {
      // Then get all of the move data and fill the temp variable.
      while (!file_to_be_read.eof())
      {
         CSVLine line = GetNextLineAndSplitIntoTokens(file_to_be_read);

         if (line.empty() || line[0] == "")
         {
            break;
         }

         data.push_back(line);
      }

      // Make sure to close the file.
      file_to_be_read.close();
   }
   else
   {
      std::cout << "The file is not open.\n";
   }

   file_data = data;
}

int CSVLoader::GetNumRows() const { return file_data.size(); }

int CSVLoader::GetNumColumns() const
{
   if (GetNumRows() > 0)
   {
      return file_data[0].size();
   }

   return -1;
}

std::pair<int, int> CSVLoader::GetNumRowsAndColumns() const
{ 
   return std::make_pair(GetNumRows(), GetNumColumns()); 
}

const std::string CSVLoader::GetRowColumnEntry(const int r, const int c) const
{
   return file_data[r][c];
}

}
} // namespace Util
}
// ----------------------------------------------------------------------------

