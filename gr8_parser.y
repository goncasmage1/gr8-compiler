%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!

%}

%union {
  int                   i;	/* integer value */
  double                d;  /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::string_node     *snode;
  cdk::basic_node      *node;	/* node pointer */
  gr8::block_node      *block;
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type           *btype;
  gr8::access_specifier accessSpec;
  gr8::variable_node   *var;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tIF tTHEN tELSIF tELSE tSMALL tHUGE tNEWS tFAKE tINITIALLY tNULL
%token tUSE tPUBLIC tDEFINE tPROCEDURE tFUNCTION tON tAS tDO tUSES tFOR tRETURN
%token tASSIGN tCELL tINPUT tOBJECTS tSTOP tAGAIN tPOST tTWEET tSWEEPING tFROM tBY
%token tAT tTO
%token tINSIDE tOUTSIDE tCOMMA tOPEN tCLOSE

%nonassoc tIFX
%nonassoc tELSE

%nonassoc tUNARY tNOT tOBJECTS tADDRESS
%left tAND tOR
%left tABOVE tBELOW tEQUALS 
%left tPLUS tMINUS
%left tTIMES tOVER tMODULUS

%type <node> inst decl elif
%type <sequence> list indent_list decl_chain uses params expr_chain func_params var_chain
%type <expression> expr initially sweepBy
%type <block> blockStart
%type <lvalue> lval
%type <btype> type small huge news small_chain huge_chain func_type
%type <accessSpec> access decl_access
%type <var> variable var_decl
%type <s> str_chain

%{

%}

%%

program	    : decl_chain                                      { compiler->ast($1); }

decl_chain  : decl	                                          { $$ = new cdk::sequence_node(LINE, $1); }
            | decl_chain decl                                 { $$ = new cdk::sequence_node(LINE, $2, $1); }
            |                                                 { $$ = nullptr; }
            ;

decl        : var_decl                                        { $$ = $1; }
            | access func_type tIDENTIFIER uses               { $$ = new gr8::function_dec_node(LINE, $1, $3, $2, $4); }
            | func_type tIDENTIFIER uses                      { $$ = new gr8::function_dec_node(LINE, gr8::access_specifier::_none, $2, $1, $3); }
            | tDEFINE decl_access func_type tIDENTIFIER func_params tAS blockStart  { $$ = new gr8::function_def_node(LINE, $2, $4, $3, $5, $7);}
            ;

var_decl    : access type tIDENTIFIER initially               { $$ = new gr8::variable_node(LINE, $1, $3, $2, $4); }
            | type tIDENTIFIER initially                      { $$ = new gr8::variable_node(LINE, gr8::access_specifier::_none, $2, $1, $3); }

initially   : tOPEN tINITIALLY expr tCLOSE                    { $$ = $3; }
            |                                                 { $$ = nullptr; }
            ;

access      : tPUBLIC                                         { $$ = gr8::access_specifier::_public; }
            | tUSE                                            { $$ = gr8::access_specifier::_use; }
            ;
decl_access : tPUBLIC                                         { $$ = gr8::access_specifier::_public; }
            |                                                 { $$ = gr8::access_specifier::_none; }
            ;

func_type   : type tFUNCTION                                  { $$ = $1 ;}
            | tPROCEDURE                                      { $$ = nullptr;}
            ;
func_params : tON params                                      { $$ = $2; }
            |                                                 { $$ = nullptr; }
            ;

uses        : tUSES params                                    { $$ = $2; }
            |                                                 { $$ = nullptr; }
            ;
params      : variable                                        { $$ = new cdk::sequence_node(LINE, $1); }
            | params tCOMMA variable                          { $$ = new cdk::sequence_node(LINE, $3, $1); }
            ;
variable    : type tIDENTIFIER                                { $$ = new gr8::variable_node(LINE, gr8::access_specifier::_none, $2, $1, nullptr); }
            ;

type        : small | huge | news                             { $$ = $1; }
            ;

small       : tSMALL                                  { $$ = new basic_type(4, basic_type::TYPE_INT); }
            | tSMALL small_chain                      { basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = $2;
                                                        $$ = typ; }
            ;
small_chain : tSMALL small_chain                      { basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = $2;
                                                        $$ = typ; }
            | tFAKE                                   { $$ = new basic_type(4, basic_type::TYPE_INT); }
            ;

huge        : tHUGE                                   { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
            | tHUGE huge_chain                        { basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = $2;
                                                        $$ = typ; }
            ;
huge_chain  : tHUGE huge_chain                        { basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = $2;
                                                        $$ = typ; }
            | tFAKE                                   { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
            ;

news        : tFAKE news                              { basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = $2;
                                                        $$ = typ; }
            | tNEWS                                   { $$ = new basic_type(4, basic_type::TYPE_STRING); }
            ;



blockStart  : tINSIDE var_chain list tOUTSIDE                 { $$ = new gr8::block_node(LINE, $2, $3); }
            | tINSIDE var_chain tOUTSIDE                      { $$ = new gr8::block_node(LINE, $2, nullptr); }
            | tINSIDE list tOUTSIDE                           { $$ = new gr8::block_node(LINE, nullptr, $2); }
            ;

var_chain   : var_decl                                        { $$ = new cdk::sequence_node(LINE, $1); }
            | var_chain var_decl                              { $$ = new cdk::sequence_node(LINE, $2, $1); }
            ;

list        : inst	                                          { $$ = new cdk::sequence_node(LINE, $1); }
            | list inst                                       { $$ = new cdk::sequence_node(LINE, $2, $1); }
            ;

inst        : expr                                            { $$ = new gr8::evaluation_node(LINE, $1); }
            | tASSIGN expr tTO lval                           { $$ = new cdk::assignment_node(LINE, $4, $2); }
            | tTWEET expr                                     { $$ = new gr8::print_node(LINE, false, $2); }
            | tPOST expr                                      { $$ = new gr8::print_node(LINE, true, $2); }
            | tAGAIN tINTEGER                                 { $$ = new gr8::again_node(LINE, $2); }
            | tSTOP tINTEGER                                  { $$ = new gr8::stop_node(LINE, $2); }
            | tAGAIN                                          { $$ = new gr8::again_node(LINE, 1); }
            | tSTOP                                           { $$ = new gr8::stop_node(LINE, 1); }
            | tRETURN expr                                    { $$ = new gr8::return_node(LINE, $2); }
            | tIF expr tTHEN indent_list %prec tIFX           { $$ = new gr8::if_node(LINE, $2, $4); }
            | tIF expr tTHEN indent_list tELSE indent_list    { $$ = new gr8::if_else_node(LINE, $2, $4, $6); }
            | tIF expr tTHEN indent_list tELSIF elif          { $$ = new gr8::if_else_node(LINE, $2, $4, $6); }
            | tSWEEPING lval tFROM expr tTO expr sweepBy tDO indent_list  { $$ = new gr8::sweeping_node(LINE, $2, $4, $6, $7, $9); }
            | tINPUT                                          { $$ = new gr8::input_node(LINE); }
            ;

indent_list : tINSIDE list tOUTSIDE                           { $$ = $2; }
            ;

elif        : expr tTHEN indent_list tELSIF elif              { $$ = new gr8::if_else_node(LINE, $1, $3, $5); }
            | expr tTHEN indent_list                          { $$ = new gr8::if_node(LINE, $1, $3); }
            | expr tTHEN indent_list tELSE indent_list        { $$ = new gr8::if_else_node(LINE, $1, $3, $5); }
            ;

sweepBy     : tBY expr                                        { $$ = $2; }
            |                                                 { $$ = nullptr; }
            ;

expr_chain  : expr                                            { $$ = new cdk::sequence_node(LINE, $1); }
            | expr_chain tCOMMA expr                          { $$ = new cdk::sequence_node(LINE, $3, $1); }
            ;

lval        : tIDENTIFIER                                     { $$ = new cdk::identifier_node(LINE, $1); }
            | tCELL expr tAT lval                             { $$ = new gr8::cell_node(LINE, new cdk::rvalue_node(LINE, $4), $2); }
            | tCELL expr tAT tOPEN expr tCLOSE                { $$ = new gr8::cell_node(LINE, $5, $2); }
            ;


expr        : tINTEGER                                        { $$ = new cdk::integer_node(LINE, $1); }
            | tDOUBLE                                         { $$ = new cdk::double_node(LINE, $1); }
            | tNULL                                           { $$ = new gr8::null_node(LINE); }
            | str_chain                                       { $$ = new cdk::string_node(LINE, $1); }
            | expr tBELOW expr	                              { $$ = new cdk::lt_node(LINE, $1, $3); }
            | expr tABOVE expr	                              { $$ = new cdk::gt_node(LINE, $1, $3); }
            | expr tEQUALS expr	                              { $$ = new cdk::eq_node(LINE, $1, $3); }
            | expr tAND expr                                  { $$ = new cdk::and_node(LINE, $1, $3); }
            | expr tOR expr                                   { $$ = new cdk::or_node(LINE, $1, $3); }
            | expr tTIMES expr	                              { $$ = new cdk::mul_node(LINE, $1, $3); }
            | expr tOVER expr	                                { $$ = new cdk::div_node(LINE, $1, $3); }
            | expr tMODULUS expr	                            { $$ = new cdk::mod_node(LINE, $1, $3); }
            | expr tPLUS expr	                                { $$ = new cdk::add_node(LINE, $1, $3); }
            | expr tMINUS expr	                              { $$ = new cdk::sub_node(LINE, $1, $3); }
            | tNOT expr %prec tUNARY                          { $$ = new cdk::not_node(LINE, $2);}
            | tPLUS expr %prec tUNARY                         { $$ = new gr8::identity_node(LINE, $2); }
            | tMINUS expr %prec tUNARY                        { $$ = new cdk::neg_node(LINE, $2); }
            | tOPEN expr tCLOSE                               { $$ = $2; }
            | tUSE expr_chain tFOR tIDENTIFIER                { $$ = new gr8::function_call_node(LINE, $4, $2); }
            | tDO tIDENTIFIER                                 { $$ = new gr8::function_call_node(LINE, $2, nullptr); }
            | expr tOBJECTS                                   { $$ = new gr8::objects_node(LINE, $1); }
            | lval tADDRESS                                   { $$ = new gr8::address_node(LINE, $1); }
            | lval                                            { $$ = new cdk::rvalue_node(LINE, $1); }
            ;

str_chain   : tSTRING                                         { $$ = $1; }
            | str_chain tSTRING                               { $$ = new std::string(*$1 + *$2); }
            ;

%%

