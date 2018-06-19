%option c++ prefix="gr8_scanner_" outfile="gr8_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <vector>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "ast/variable_node.h"
#include "gr8_parser.tab.h"

// don't change this
#define yyerror LexerError

int indentCounter = 0;
std::vector<int> indentation (1,0);

%}
%x X_STRING
%x X_STRING_FINISH
%x COMM_1
%x COMM_2
%x INDENT

DIGIT [0-9]                 
INT [1-9]
BASE7 [0-6] 
SMALL ({DIGIT})|({INT}{DIGIT}*)

%%

"small"                     return tSMALL;
"huge"                      return tHUGE;
"news"                      return tNEWS;
"fake"                      return tFAKE;
"initially"                 return tINITIALLY;
"null"                      return tNULL;

"use"                       return tUSE;
"public"                    return tPUBLIC;
"define"                    return tDEFINE;
"procedure"                 return tPROCEDURE;
"function"                  return tFUNCTION;
"on"                        return tON;
"as"                        return tAS;
"do"                        return tDO;
"uses"                      return tUSES;
"for"                       return tFOR;
"return"                    return tRETURN;

"plus"                      return tPLUS;
"minus"                     return tMINUS;
"times"                     return tTIMES;
"over"                      return tOVER;
"modulus"                   return tMODULUS;
"not"                       return tNOT;
"and"                       return tAND;
"or"                        return tOR;
"assign"                    return tASSIGN;
"to"                        return tTO;
"cell"                      return tCELL;
"at"                        return tAT;
"above"                     return tABOVE;
"below"                     return tBELOW;
"equals"                    return tEQUALS;
"input"                     return tINPUT;
"objects"                   return tOBJECTS;
"?"                         return tADDRESS;

"if"                        return tIF;
"then"                      return tTHEN;
"elsif"                     return tELSIF;
"else"                      return tELSE;
"stop"                      return tSTOP;
"again"                     return tAGAIN;
"post"                      return tPOST;
"tweet"                     return tTWEET;
"sweeping"                  return tSWEEPING;
"from"                      return tFROM;
"by"                        return tBY;

","                         return tCOMMA;
"("                         return tOPEN;
")"                         return tCLOSE;

[A-Za-z][A-Za-z0-9-]*       yylval.s = new std::string(yytext); return tIDENTIFIER;

"<<"                        yy_push_state(COMM_1);
<COMM_1>">>"                yy_pop_state();
<COMM_1>.|\n                ;
"!!"                        yy_push_state(COMM_2);
<COMM_2>\n                  yy_pop_state();
<COMM_2>.                   ;

<INITIAL>"...\n"[ \t]*      ;

\"                          yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                yy_pop_state(); return tSTRING;
<X_STRING>"~0"              yy_push_state(X_STRING_FINISH);
<X_STRING>.                 *yylval.s += yytext;
<X_STRING>"~t"              *yylval.s += "\t";
<X_STRING>"~n"              *yylval.s += "\n";
<X_STRING>"~r"              *yylval.s += "\r";
<X_STRING>\~\"              *yylval.s += "\"";
<X_STRING>"~~"              *yylval.s += "~";
<X_STRING>"~"{BASE7}{1,3}   *yylval.s += char(strtol(yytext+1, nullptr, 7));    
<X_STRING>\n                yyerror("newline in string");
<X_STRING_FINISH>\"         yy_pop_state(); yy_pop_state(); return tSTRING;
<X_STRING_FINISH>\n         yyerror("newline in string");
<X_STRING_FINISH>.          ;

<INITIAL>" "                ;
<INITIAL>\n                 yy_push_state(INDENT);
<INDENT>[ \t]*"<<"          yy_push_state(COMM_1); 
<INDENT>[ \t]*"!!"          yy_push_state(COMM_2);    
<INDENT>[ \t]*\n            ;
<INDENT>[ \t]*              {
                                indentCounter = yyleng;
                                if (indentCounter == indentation.back()) {
                                    yy_pop_state();
                                }
                                else if (indentCounter > indentation.back()) {
                                    indentation.push_back(indentCounter);
                                    yy_pop_state();
                                    return tINSIDE;
                                }
                                else if (indentCounter < indentation.back()) {
                                    int last = indentation.back();
                                    int diff = indentation.back() - indentCounter;
                                    indentation.pop_back();
                                    if (indentCounter > indentation.back()) yyerror("Unmatching indentation in file!");
                                    if (indentCounter != 0) yyless(yyleng - last + diff);
                                    if (indentation.back() == 0) yy_pop_state();
                                    return tOUTSIDE;
                                }
                            }
<INITIAL><<EOF>>            {
                                if (indentation.back() != 0) {
                                    indentation.pop_back();
                                    return tOUTSIDE;
                                }
                                return 0;
                            }
<INDENT>.                   {
                                if (indentation.back() != 0) {
                                    indentation.pop_back();
                                    yyless(yyleng-1);
                                    return tOUTSIDE;
                                }
                                yyless(yyleng-1);
                                yy_pop_state();  
                            }
<INDENT><<EOF>>             yy_pop_state();
  
{SMALL}\.{DIGIT}+[Ee]{DIGIT}+           yylval.d = strtod(yytext, nullptr); if (errno == ERANGE) yyerror("Overflow"); return tDOUBLE;
{SMALL}\.{DIGIT}+                       yylval.d = strtod(yytext, nullptr); if (errno == ERANGE) yyerror("Overflow");return tDOUBLE;
{SMALL}[Ee]{DIGIT}+                     yylval.d = strtod(yytext, nullptr); if (errno == ERANGE) yyerror("Overflow");return tDOUBLE;
{SMALL}                                 yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow");return tINTEGER;
0{BASE7}+                               yylval.i = strtol(yytext+1, nullptr, 7); if (errno == ERANGE) yyerror("Overflow");return tINTEGER;
{DIGIT}+                                yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow");return tINTEGER;

[-()<>=+*/%;{}.]            return *yytext;

.                           yyerror("Unknown character");

%%
