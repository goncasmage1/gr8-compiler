#include "targets/variable_visitor.h"
#include "ast/all.h"

void gr8::variable_visitor::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
  _parent->setTotalBytes(_totalBytes);
  _totalBytes = 0;
}

void gr8::variable_visitor::do_variable_node(gr8::variable_node * const node, int lvl) {
  _totalBytes += node->type()->name() == basic_type::TYPE_DOUBLE ? 8 : 4;
}

void gr8::variable_visitor::do_block_node(gr8::block_node * const node, int lvl) {
  if (node->declarations() != nullptr) node->declarations()->accept(this, lvl);
}

void gr8::variable_visitor::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  node->block()->accept(this, lvl); 
}

void gr8::variable_visitor::do_nil_node(cdk::nil_node * const node, int lvl) {}
void gr8::variable_visitor::do_data_node(cdk::data_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void gr8::variable_visitor::do_integer_node(cdk::integer_node * const node, int lvl) {}

void gr8::variable_visitor::do_double_node(cdk::double_node * const node, int lvl) {}

void gr8::variable_visitor::do_string_node(cdk::string_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void gr8::variable_visitor::do_neg_node(cdk::neg_node * const node, int lvl) {}
void gr8::variable_visitor::do_not_node(cdk::not_node * const node, int lvl) {}
void gr8::variable_visitor::do_identity_node(gr8::identity_node * const node, int lvl) {}
//---------------------------------------------------------------------------

void gr8::variable_visitor::do_add_node(cdk::add_node * const node, int lvl) {}
void gr8::variable_visitor::do_sub_node(cdk::sub_node * const node, int lvl) {}
void gr8::variable_visitor::do_mul_node(cdk::mul_node * const node, int lvl) {}
void gr8::variable_visitor::do_div_node(cdk::div_node * const node, int lvl) {}
void gr8::variable_visitor::do_mod_node(cdk::mod_node * const node, int lvl) {}
void gr8::variable_visitor::do_lt_node(cdk::lt_node * const node, int lvl) {}
void gr8::variable_visitor::do_gt_node(cdk::gt_node * const node, int lvl) {}
void gr8::variable_visitor::do_eq_node(cdk::eq_node * const node, int lvl) {}
void gr8::variable_visitor::do_and_node(cdk::and_node * const node, int lvl) {}
void gr8::variable_visitor::do_or_node(cdk::or_node * const node, int lvl) {}


void gr8::variable_visitor::do_le_node(cdk::le_node * const node, int lvl) {}
void gr8::variable_visitor::do_ge_node(cdk::ge_node * const node, int lvl) {}
void gr8::variable_visitor::do_ne_node(cdk::ne_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void gr8::variable_visitor::do_identifier_node(cdk::identifier_node * const node, int lvl) {}

void gr8::variable_visitor::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {}

void gr8::variable_visitor::do_assignment_node(cdk::assignment_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void gr8::variable_visitor::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {}

void gr8::variable_visitor::do_print_node(gr8::print_node * const node, int lvl) {}

void gr8::variable_visitor::do_if_node(gr8::if_node * const node, int lvl) {}

void gr8::variable_visitor::do_if_else_node(gr8::if_else_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void gr8::variable_visitor::do_address_node(gr8::address_node * const node, int lvl) {}

void gr8::variable_visitor::do_again_node(gr8::again_node * const node, int lvl) {}

void gr8::variable_visitor::do_cell_node(gr8::cell_node * const node, int lvl) {}

void gr8::variable_visitor::do_function_call_node(gr8::function_call_node * const node, int lvl) {}

void gr8::variable_visitor::do_function_dec_node(gr8::function_dec_node * const node, int lvl) {}

void gr8::variable_visitor::do_input_node(gr8::input_node * const node, int lvl) {}

void gr8::variable_visitor::do_null_node(gr8::null_node * const node, int lvl) {}

void gr8::variable_visitor::do_objects_node(gr8::objects_node * const node, int lvl) {}

void gr8::variable_visitor::do_return_node(gr8::return_node * const node, int lvl) {}

void gr8::variable_visitor::do_stop_node(gr8::stop_node * const node, int lvl) {}

void gr8::variable_visitor::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {}