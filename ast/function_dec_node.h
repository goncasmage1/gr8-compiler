// $Id: function_dec_node.h,v 1.10 2018/05/15 18:21:20 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_FUNCTION_DECNODE_H__
#define __GR8_FUNCTION_DECNODE_H__

#include <cdk/ast/typed_node.h>
#include <cdk/basic_type.h>
#include "function_def_node.h"
#include "../access_specifier.h"

namespace gr8 {

  /**
   * Class for describing function nodes.
   */
  class function_dec_node: public cdk::typed_node {
    gr8::access_specifier _access;
    std::string nameHelper;
    std::string* _functionName; 
    cdk::sequence_node* _arguments;
    bool _fromDefinition = false;

    public:
      inline function_dec_node(int lineno,  gr8::access_specifier access,
                                            std::string* functionName,
                                            basic_type* type,
                                            cdk::sequence_node* arguments) :
                cdk::typed_node(lineno),
                _access(access),
                _functionName(functionName),
                _arguments(arguments) {
        _type = type;
      }

      inline function_dec_node(gr8::function_def_node* def_node) :
                cdk::typed_node(0),
                _access(def_node->access()),
                _arguments(def_node->arguments()) {
        nameHelper = def_node->functionName();
        _functionName = &nameHelper;
        _type = def_node->type();
        _fromDefinition = true;
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

      inline bool fromDefinition() {
        return _fromDefinition;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_function_dec_node(this, level);
      }

  };

} // gr8

#endif
