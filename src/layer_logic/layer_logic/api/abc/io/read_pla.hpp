#pragma once

#include "layer_logic/logic_manager.hpp"
#include "layer_logic/api/abc/frame.hpp"
#include "utility/string.hpp"

#include <cstdio>
#include <string>

namespace lf
{

namespace logic
{

namespace abc
{

/**
 * @brief Reads file into the current logic network.
 * @example
 *  read_pla [options] [filename]
 *  options: -z -b -d -x -c
 * @note
 */
void read_pla( const std::string& file, bool is_zeors = false, bool is_both = false, bool is_dont_care = false, bool is_exor_sop = false, bool is_checking = false )
{
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_ABC_LOGIC_SOP );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_ABC_LOGIC_SOP )
  {
    std::cerr << "Unmatched pla ntk type." << std::endl;
    return;
  }

  auto ntk_ptr = lfLmINST->current<babc::Abc_Frame_t*>(); // the the network from shared_ptr

  int argc = 1; // command name
  argc += 1;    // file name
  if ( is_zeors )
    argc += 1;
  if ( is_both )
    argc += 1;
  if ( is_dont_care )
    argc += 1;
  if ( is_exor_sop )
    argc += 1;
  if ( is_checking )
    argc += 1;

  char** argv = ABC_ALLOC( char*, argc + 1 );

  int pos = 0;

  argv[pos++] = babc::Extra_UtilStrsav( "read_pla" );

  if ( is_zeors )
    argv[pos++] = babc::Extra_UtilStrsav( " -z " );
  if ( is_both )
    argv[pos++] = babc::Extra_UtilStrsav( " -b " );
  if ( is_dont_care )
    argv[pos++] = babc::Extra_UtilStrsav( " -d " );
  if ( is_exor_sop )
    argv[pos++] = babc::Extra_UtilStrsav( " -x " );
  if ( is_checking )
    argv[pos++] = babc::Extra_UtilStrsav( " -c " );

  argv[pos++] = babc::Extra_UtilStrsav( file.c_str() );

  babc::IoCommandReadPla( ntk_ptr, argc, argv );
}

} // namespace abc

} // namespace logic

} // end namespace lf