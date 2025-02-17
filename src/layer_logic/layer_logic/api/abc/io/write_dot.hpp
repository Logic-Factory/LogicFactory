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
 * @brief Reads current logic into a file.
 * @example
 *  write_dot [options] [filename]
 *  options:
 * @note
 */
void write_dot( const std::string& file )
{
  auto ntk_ptr = lfLmINST->current<babc::Abc_Frame_t*>(); // the the network from shared_ptr

  int argc = 1; // command name
  argc += 1;    // file name

  char** argv = ABC_ALLOC( char*, argc + 1 );

  int pos = 0;
  argv[pos++] = babc::Extra_UtilStrsav( "write_dot" );

  argv[pos++] = babc::Extra_UtilStrsav( file.c_str() );

  babc::IoCommandWriteDot( ntk_ptr, argc, argv );
}

} // namespace abc

} // namespace logic

} // end namespace lf