#ifndef POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_CSV_CSV_PARSER_HPP
#define POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_CSV_CSV_PARSER_HPP

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <string>
#include <utility>
#include <vector>
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

/// @brief This line will continually get lines and split them into tokens.
/// @param str The stream from a file we want to split.
/// @return Returns a vector of string which is the line split up.
std::vector<std::string> GetNextLineAndSplitIntoTokens(std::istream& str);

/// @brief This will split a string by a delimiter.
/// @param del The delimiting character.
/// @param str The string to split.
/// @return Returns a vector of string which is the line split up.
std::vector<std::string> SplitStringByDelimiter(const char del,
                                                const std::string& str);

// ----------------------------------------------------------------------------
// Type Declarations block.
// ----------------------------------------------------------------------------

/// @brief A CSV line is just a vector of strings so that is what we will call
//         this since that is what we are loading here.
using CSVLine = std::vector<std::string>;
/// @brief The whole file is just a list of the CSV lines so a vector of
///        of CSV lines.
using CSVFile = std::vector<CSVLine>;
// ----------------------------------------------------------------------------

class CSVLoader
{
private:
   CSVFile file_data = {};

public:
   CSVLoader(std::string file);

   int GetNumRows() const;
   int GetNumColumns() const;
   std::pair<int, int> GetNumRowsAndColumns() const;
   const std::string GetRowColumnEntry(const int r, const int c) const;
   inline const CSVLine& GetLineAtRow(const int r) const { return file_data.at(r); }; 
};

}
} // namespace Util
}
// ----------------------------------------------------------------------------

#endif



