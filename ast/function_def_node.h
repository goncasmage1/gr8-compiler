// $Id: function_def_node.h,v 1.10 2018/05/15 11:23:08 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_FUNCTION_DEFNODE_H__
#define __GR8_FUNCTION_DEFNODE_H__

#include <cdk/ast/typed_node.h>
#include "block_node.h"

namespace gr8 {

  /**
   * Class for describing function nodes.
   */
  class function_def_node: public cdk::typed_node {
    gr8::access_specifier _access;
    std::string* _functionName; 
    cdk::sequence_node* _arguments;
    gr8::block_node *_block;

    public:
      inline function_def_node(int lineno,  gr8::access_specifier access,
                                            std::string* functionName,
                                            basic_type* type,
                                            cdk::sequence_node* arguments,
                                            gr8::block_node *block) :
        cdk::typed_node(lineno), _access(access), _functionName(functionName),
                                _arguments(arguments), _block(block) {
        _type = type;
      }

    public:

      inline std::string functionName() {
        return *_functionName;
      }

      inline gr8::access_specifier access() {
        return _access;
      }

      inline cdk::sequence_node* arguments() {
        return _arguments;
      }

      inline gr8::block_node * block() {
          return _block;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_function_def_node(this, level);
      }

  };

} // gr8

#endif
