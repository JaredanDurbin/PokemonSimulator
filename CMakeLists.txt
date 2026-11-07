cmake_minimum_required(VERSION 3.20)

project(SmorganDemise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Library containing all shared code
# -------------------------

add_library(project_lib STATIC 
   src/calc_util.cpp
   src/data_abilities.cpp
   src/data_items.cpp
   src/data_moves.cpp
   src/data_natures.cpp
   src/data_species.cpp
   src/data_types.cpp
   src/description.cpp
   src/mechanics_gen3.cpp
   src/mechanics_gen4.cpp
   src/mechanics_gen12.cpp
   src/mechanics_gen56.cpp
   src/mechanics_gen789.cpp
   src/mechanics_mechanics.cpp
   src/move.cpp
   src/pokemon.cpp
   src/result.cpp
   src/smorgans_demise_data_loader.cpp
   src/smorgans_demise_evo.cpp
   src/smorgans_demise_turn_matrix.cpp
   src/smorgans_demise_von_neumann.cpp
   src/state.cpp
   src/stats.cpp
   src/util_csv_parser.cpp
   src/util_csv_util.cpp
   src/util_util.cpp
)

target_include_directories(project_lib
   PUBLIC
      ${CMAKE_SOURCE_DIR}/include
)

# -------------------------
# Main executables
# -------------------------

#add_executable(app1
#   main/app1.cpp
#)

#target_link_libraries(app1
#   PRIVATE
#      project_lib
#)

#add_executable(app2
#   main/app2.cpp
#)

#target_link_libraries(app2
#   PRIVATE
#      project_lib
#)

# -------------------------
# Tests
# -------------------------

#add_executable(test_calc_gen1
#   test/test_calc_gen1.cpp
#)

#target_link_libraries(test_calc_gen1
#   PRIVATE
#      project_lib
#)

#add_executable(test_calc_gen3
#   test/test_calc_gen3.cpp
#)

#target_link_libraries(test_calc_gen3
#   PRIVATE
#      project_lib
#)

#add_executable(test_pokemon_csv_input
#   test/test_pokemon_csv_input.cpp
#)

#target_link_libraries(test_pokemon_csv_input
#   PRIVATE
#      project_lib
#)

#add_executable(test_von_neumann_and_data_loader
#   test/test_von_neumann_and_data_loader.cpp
#)

#target_link_libraries(test_von_neumann_and_data_loader
#   PRIVATE
#      project_lib
#)

add_executable(test_evo
   test/test_evo.cpp
)

target_link_libraries(test_evo
   PRIVATE
      project_lib
)

