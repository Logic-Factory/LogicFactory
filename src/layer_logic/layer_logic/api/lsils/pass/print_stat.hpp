#pragma once

#include "layer_logic/logic_manager.hpp"
#include "mockturtle/views/depth_view.hpp"

#include "nlohmann/json.hpp"

#include <iomanip>
#include <assert.h>

namespace lf
{

namespace logic
{

namespace lsils
{

template<typename Ntk>
void print_logic_stat( const Ntk& ntk, std::string file = "" )
{
  // assert the sequential network
  static_assert( mockturtle::has_num_registers_v<Ntk>, "Ntk does not implement the num_registers method" );

  mockturtle::depth_view<Ntk> ntk_depth( ntk );
  std::string module_name = lfLmINST->ports().get_module_name();
  uint32_t area = ntk_depth.num_gates();
  uint32_t depth = ntk_depth.depth();
  uint32_t latch = ntk_depth.num_registers();

  std::cout << module_name << "\t\t: i/o = " << ntk.num_pis() << "/" << ntk.num_pos()
            << "\tlatch = " << latch
            << "\tarea = " << area
            << "\tdepth = " << depth << std::endl;

  if ( !file.empty() )
  {
    nlohmann::json j = {
        { "input", ntk.num_pis() },
        { "output", ntk.num_pos() },
        { "gates", area },
        { "depth", depth },
        { "area", area },
        { "delay", depth } };
    std::ofstream out( file );
    if ( !out.is_open() )
    {
      std::cerr << "Error: Unable to open file " << file << std::endl;
      return;
    }
    out << j.dump( 4 ) << std::endl;
    out.close();
  }
}

void print_mapping_stat( const lf::logic::lsils::blut_seq_network& ntk, std::string file = "" )
{
  mockturtle::depth_view<lf::logic::lsils::blut_seq_network> ntk_depth( ntk );
  std::string module_name = lfLmINST->ports().get_module_name();
  uint32_t size = ntk_depth.num_gates();
  uint32_t depth = ntk_depth.depth();
  double area = ntk.compute_area();
  double delay = ntk.compute_worst_delay();
  uint32_t latch = ntk.num_registers();

  std::cout << std::fixed << std::setprecision( 3 )
            << module_name << "\t\t: i/o = " << ntk.num_pis() << "/" << ntk.num_pos()
            << "\tlatch = " << latch
            << "\tarea = " << area
            << "\tdepth = " << delay << std::endl;

  if ( !file.empty() )
  {
    nlohmann::json j = {
        { "input", ntk.num_pis() },
        { "output", ntk.num_pos() },
        { "gates", size },
        { "depth", depth },
        { "area", area },
        { "delay", delay } };
    std::ofstream out( file );
    if ( !out.is_open() )
    {
      std::cerr << "Error: Unable to open file " << file << std::endl;
      return;
    }
    out << j.dump( 4 ) << std::endl;
    out.close();
  }
}

/**
 * @brief Logic optimization
 * @example
 *  print_stat [options]
 *  options:
 * @note
 */
void print_stat( std::string file = "" )
{
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_OIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AOG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XAG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XOG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XMG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_MIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_PRIMARY ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_GTG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_OIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AOG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XOG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_PRIMARY ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_GTG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_FPGA ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_ASIC );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_OIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AOG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XAG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XOG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XMG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_MIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_PRIMARY &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_GTG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_OIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AOG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XOG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_PRIMARY &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_GTG &&
       ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_FPGA &&
       ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_ASIC )
  {
    std::cerr << "[ERROR] write_dot: wrong ntk type!" << std::endl;
    return;
  }

  switch ( ntktype )
  {
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AIG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG:
  {
    lf::logic::lsils::aig_seq_network ntk = lfLmINST->current<lf::logic::lsils::aig_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_OIG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_OIG:
  {
    lf::logic::lsils::oig_seq_network ntk = lfLmINST->current<lf::logic::lsils::oig_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_AOG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AOG:
  {
    lf::logic::lsils::aog_seq_network ntk = lfLmINST->current<lf::logic::lsils::aog_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XAG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG:
  {
    lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XOG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XOG:
  {
    lf::logic::lsils::xog_seq_network ntk = lfLmINST->current<lf::logic::lsils::xog_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_XMG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG:
  {
    lf::logic::lsils::xmg_seq_network ntk = lfLmINST->current<lf::logic::lsils::xmg_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_MIG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG:
  {
    lf::logic::lsils::mig_seq_network ntk = lfLmINST->current<lf::logic::lsils::mig_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_PRIMARY:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_PRIMARY:
  {
    lf::logic::lsils::primary_seq_network ntk = lfLmINST->current<lf::logic::lsils::primary_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_LOGIC_GTG:
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_GTG:
  {
    lf::logic::lsils::gtg_seq_network ntk = lfLmINST->current<lf::logic::lsils::gtg_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_FPGA:
  {
    lf::logic::lsils::klut_seq_network ntk = lfLmINST->current<lf::logic::lsils::klut_seq_network>();
    print_logic_stat( ntk, file );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_NETLIST_ASIC:
  {
    lf::logic::lsils::blut_seq_network ntk = lfLmINST->current<lf::logic::lsils::blut_seq_network>();
    print_mapping_stat( ntk, file );
    break;
  }
  default:
  {
    std::cerr << "unsupport network type!\n";
    assert( false );
    break;
  }
  }
}

} // namespace lsils
} // namespace logic
} // namespace lf