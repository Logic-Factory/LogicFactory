#pragma once

#include "mockturtle/mockturtle.hpp"

#include <vector>
#include <assert.h>
#include <iostream>
#include <memory>

namespace lf
{

namespace logic
{

namespace lsils
{

///////////////////////////////////////////////////////////
//  combinational
///////////////////////////////////////////////////////////
using aig_comb_network = mockturtle::aig_network;
using oig_comb_network = mockturtle::oig_network;
using aog_comb_network = mockturtle::aog_network;
using xag_comb_network = mockturtle::xag_network;
using xog_comb_network = mockturtle::xog_network;
using mig_comb_network = mockturtle::mig_network;
using xmg_comb_network = mockturtle::xmg_network;
using primary_comb_network = mockturtle::primary_network;
using gtg_comb_network = mockturtle::gtg_network;
using cvg_comb_network = mockturtle::cover_network;

using klut_comb_network = mockturtle::klut_network;
using blut_comb_network = mockturtle::binding_view<klut_comb_network>;

///////////////////////////////////////////////////////////
//  sequential
///////////////////////////////////////////////////////////
using aig_seq_network = mockturtle::sequential<aig_comb_network>;
using oig_seq_network = mockturtle::sequential<oig_comb_network>;
using aog_seq_network = mockturtle::sequential<aog_comb_network>;
using xag_seq_network = mockturtle::sequential<xag_comb_network>;
using xog_seq_network = mockturtle::sequential<xog_comb_network>;
using mig_seq_network = mockturtle::sequential<mig_comb_network>;
using xmg_seq_network = mockturtle::sequential<xmg_comb_network>;
using primary_seq_network = mockturtle::sequential<primary_comb_network>;
using gtg_seq_network = mockturtle::sequential<gtg_comb_network>;
using cvg_seq_network = mockturtle::sequential<cvg_comb_network>;

using klut_seq_network = mockturtle::sequential<klut_comb_network>;
using blut_seq_network = mockturtle::binding_view<klut_seq_network>;

///////////////////////////////////////////////////////////
//  library
///////////////////////////////////////////////////////////
using lib_gates = std::vector<mockturtle::gate>;
using lib_techlib_np = mockturtle::tech_library<6u, mockturtle::classification_type::np_configurations>;

/**
 * @brief struct Lsils_Frame_t
 *  it stores all the networks and the libraries
 */
struct Lsils_Frame_t
{
  // technology-independent network
  aig_seq_network curr_aig;
  oig_seq_network curr_oig;
  aog_seq_network curr_aog;
  xag_seq_network curr_xag;
  xog_seq_network curr_xog;
  mig_seq_network curr_mig;
  xmg_seq_network curr_xmg;
  primary_seq_network curr_primary;
  gtg_seq_network curr_gtg;
  cvg_seq_network curr_cvg;

  // technology-dependent netlist
  blut_seq_network curr_asic;
  klut_seq_network curr_fpga;

  // technology-dependent library
  lib_gates gates;

  // flag the storage of the ntks
  bool has_logic_aig{ false };
  bool has_logic_oig{ false };
  bool has_logic_aog{ false };
  bool has_logic_xag{ false };
  bool has_logic_xog{ false };
  bool has_logic_mig{ false };
  bool has_logic_xmg{ false };
  bool has_logic_primary{ false };
  bool has_logic_gtg{ false };
  bool has_libs{ false };
  bool has_netlist_asic{ false };
  bool has_netlist_fpga{ false };
};

} // namespace lsils

} // namespace logic

} // namespace lf