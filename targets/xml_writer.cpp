#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void gr8::xml_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::xml_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  if (node == nullptr) return;
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void gr8::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}

void gr8::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_identity_node(gr8::identity_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

void gr8::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

void gr8::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
//---------------------------------------------------------------------------

void gr8::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
 do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<identifier>" << node->name() << "</identifier>" << std::endl;
}

void gr8::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl + 2);
  reset_new_symbol();

  node->rvalue()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_if_node(gr8::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}


//---------------------------------------------------------------------------------------


void gr8::xml_writer::do_access_specifier(gr8::access_specifier access, int lvl) {

  switch (access) {
    case gr8::access_specifier::_public:
        os() << std::string(lvl, ' ') << "<public/>" << std::endl;
      break;
    case gr8::access_specifier::_use:
        os() << std::string(lvl, ' ') << "<use/>" << std::endl;
      break;
    default:
      break;
  }
}

void gr8::xml_writer::do_address_node(gr8::address_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("lvalue", lvl + 2);
  node->variable()->accept(this, lvl + 4);
  closeTag("lvalue", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_again_node(gr8::again_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<cicle>" << node->number() << "</cicle>" << std::endl;
  closeTag(node, lvl);
}

void gr8::xml_writer::do_basic_type(basic_type* type, int lvl, cdk::expression_node* value = nullptr, int first = 2) {
  if (type == nullptr) {
    if (value == nullptr) {
      if (first <= 0) {
        do_null(lvl + 2);
      }
      return;
    }
    if (first > 0) {
      value->accept(this, lvl + 2);
    }
    else {
      if ((gr8::null_node*)value == nullptr) {
        os() << std::string(lvl + 2, ' ') << "pointer" << std::endl;
      }
      else {
        do_null(lvl + 2);
      }
    }
    return;
  }
  if (type->name() == basic_type::TYPE_INT) {
    os() << std::string(lvl, ' ') + "<small>" << std::endl;
    do_basic_type(type->subtype(), lvl + 2, value, first - 1);
    os() << std::string(lvl, ' ') + "</small>" << std::endl;
  }
  else if (type->name() == basic_type::TYPE_DOUBLE) {
    os() << std::string(lvl, ' ') + "<huge>" << std::endl;
    do_basic_type(type->subtype(), lvl + 2, value, first - 1);
    os() << std::string(lvl, ' ') + "</huge>" << std::endl;
  }
  else if (type->name() == basic_type::TYPE_STRING) {
    os() << std::string(lvl, ' ') + "<news>" << std::endl;
    do_basic_type(type->subtype(), lvl + 2, value, first - 1);
    os() << std::string(lvl, ' ') + "</news>" << std::endl;
  }
  else if (type->name() == basic_type::TYPE_POINTER) {
    os() << std::string(lvl, ' ') + "<pointer>" << std::endl;
    do_basic_type(type->subtype(), lvl + 2, value, first - 1);
    os() << std::string(lvl, ' ') + "</pointer>" << std::endl;
  }
}

void gr8::xml_writer::do_block_node(gr8::block_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  if (node->declarations() != nullptr) node->declarations()->accept(this, lvl + 2);
  if (node->instructions() != nullptr) node->instructions()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_cell_node(gr8::cell_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->value()->accept(this, lvl + 2);
  openTag("index", lvl + 2);
  node->indexing()->accept(this, lvl + 4);
  closeTag("index", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_function_call_node(gr8::function_call_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<identifier>" << node->functionName() << "</identifier>" << std::endl;
  if (node->arguments() != nullptr) {
    openTag("arguments", lvl + 2);
    node->arguments()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
  }
  closeTag(node, lvl);
}

void gr8::xml_writer::do_function_helper(gr8::access_specifier accessSpec, basic_type* bType, std::string name, cdk::sequence_node* arguments, int lvl) {
  do_access_specifier(accessSpec, lvl + 2);
  if (bType != nullptr) {
    openTag("type", lvl + 2);
    do_basic_type(bType, lvl + 4);
    closeTag("type", lvl + 2);
  }
  else {
    os() << std::string(lvl + 2, ' ') << "<procedure/>" << std::endl;
  }
  os() << std::string(lvl + 2, ' ') << "<identifier>" << name << "</identifier>" << std::endl;
  if (arguments != nullptr) {
    openTag("arguments", lvl + 2);
    arguments->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
  }
}

void gr8::xml_writer::do_function_dec_node(gr8::function_dec_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  do_function_helper(node->access(), node->type(), node->functionName(), node->arguments(), lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  do_function_helper(node->access(), node->type(), node->functionName(), node->arguments(), lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_input_node(gr8::input_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl + 2, ' ') << "<input/>" << std::endl;
}

void gr8::xml_writer::do_null(int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "null" << std::endl;
}

void gr8::xml_writer::do_null_node(gr8::null_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  do_null(lvl + 2);
}

void gr8::xml_writer::do_objects_node(gr8::objects_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  do_unary_expression(node, lvl);
}

void gr8::xml_writer::do_print_node(gr8::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  if (node->newLine()) {
    openTag("post", lvl);
    node->argument()->accept(this, lvl + 2);
    closeTag("post", lvl);
  }
  else {
    openTag("tweet", lvl);
    node->argument()->accept(this, lvl + 2);
    closeTag("tweet", lvl);
  }
}

void gr8::xml_writer::do_return_node(gr8::return_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->returnValue()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_stop_node(gr8::stop_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<cicle>" << node->number() << "</cicle>" << std::endl;
  closeTag(node, lvl);
}

void gr8::xml_writer::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("lvalue", lvl + 2);
  node->lvalue()->accept(this, lvl + 4);
  closeTag("lvalue", lvl + 2);
  openTag("from", lvl + 2);
  node->from()->accept(this, lvl + 4);
  closeTag("from", lvl + 2);
  openTag("to", lvl + 2);
  node->to()->accept(this, lvl + 4);
  closeTag("to", lvl + 2);
  if (node->by() != nullptr) {
    openTag("by", lvl + 2);
    node->by()->accept(this, lvl + 4);
    closeTag("by", lvl + 2);
  }
  openTag("do", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("do", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_variable_node(gr8::variable_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  do_access_specifier(node->access(), lvl + 2);
  os() << std::string(lvl + 2, ' ') << "<identifier>" << node->name() << "</identifier>" << std::endl;
  do_basic_type(node->type(), lvl + 2, node->value());

  closeTag(node, lvl);
}