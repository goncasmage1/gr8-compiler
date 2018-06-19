/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170709

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "gr8_parser.y"
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 14 "gr8_parser.y"
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 58 "gr8_parser.y"

#line 56 "gr8_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tDOUBLE 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tIF 261
#define tTHEN 262
#define tELSIF 263
#define tELSE 264
#define tSMALL 265
#define tHUGE 266
#define tNEWS 267
#define tFAKE 268
#define tINITIALLY 269
#define tNULL 270
#define tUSE 271
#define tPUBLIC 272
#define tDEFINE 273
#define tPROCEDURE 274
#define tFUNCTION 275
#define tON 276
#define tAS 277
#define tDO 278
#define tUSES 279
#define tFOR 280
#define tRETURN 281
#define tASSIGN 282
#define tCELL 283
#define tINPUT 284
#define tOBJECTS 285
#define tSTOP 286
#define tAGAIN 287
#define tPOST 288
#define tTWEET 289
#define tSWEEPING 290
#define tFROM 291
#define tBY 292
#define tAT 293
#define tTO 294
#define tINSIDE 295
#define tOUTSIDE 296
#define tCOMMA 297
#define tOPEN 298
#define tCLOSE 299
#define tIFX 300
#define tUNARY 301
#define tNOT 302
#define tADDRESS 303
#define tAND 304
#define tOR 305
#define tABOVE 306
#define tBELOW 307
#define tEQUALS 308
#define tPLUS 309
#define tMINUS 310
#define tTIMES 311
#define tOVER 312
#define tMODULUS 313
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    6,    6,    6,    2,    2,    2,    2,   27,   27,
   13,   13,   24,   24,   25,   25,   23,   23,   10,   10,
    7,    7,    8,    8,   26,   17,   17,   17,   18,   18,
   21,   21,   19,   19,   22,   22,   20,   20,   15,   15,
   15,   11,   11,    4,    4,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    5,
    3,    3,    3,   14,   14,    9,    9,   16,   16,   16,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   28,   28,
};
static const YYINT yylen[] = {                            2,
    1,    1,    2,    0,    1,    4,    3,    7,    4,    3,
    4,    0,    1,    1,    1,    0,    2,    1,    2,    0,
    2,    0,    1,    3,    2,    1,    1,    1,    1,    2,
    2,    1,    1,    2,    2,    1,    2,    1,    4,    3,
    3,    1,    2,    1,    2,    1,    4,    2,    2,    2,
    2,    1,    1,    2,    4,    6,    6,    9,    1,    3,
    5,    3,    5,    2,    0,    1,    3,    1,    4,    6,
    1,    1,    1,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    2,    2,    2,    3,    4,    2,
    2,    2,    1,    1,    2,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   38,    0,   14,   13,    0,   18,    0,    2,
    0,    0,   26,   27,   28,    0,    0,    5,    0,   32,
   30,    0,   36,   34,   37,   15,    0,    3,    0,   17,
    0,    0,    0,   31,   35,    0,    0,    0,   10,    0,
    7,    0,    0,    0,    0,    0,    0,   23,    9,    6,
    0,    0,   71,   72,   68,   94,   73,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   25,    0,
    0,    0,    0,   90,    0,    0,    0,    0,    0,   91,
   11,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   92,   95,   24,    0,    8,    0,    0,    0,   88,
    0,    0,    0,    0,    0,    0,    0,   80,   81,   82,
    0,    0,    0,    0,   59,    0,    0,    0,    0,    0,
   44,    0,    0,    0,    0,    0,   42,   89,    0,    0,
   69,    0,    0,    0,   51,   50,    0,    0,    0,   41,
   45,   40,    0,   43,    0,    0,    0,    0,    0,   39,
   70,    0,    0,   47,    0,    0,    0,    0,    0,   60,
   57,    0,   56,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   58,   61,   63,
};
static const YYINT yydgoto[] = {                          9,
  121,   10,  161,  122,  153,   11,   41,   46,   72,   52,
  123,  124,   39,  167,   96,   66,   47,   13,   14,   15,
   21,   24,   16,   17,   27,   48,   18,   67,
};
static const YYINT yysindex[] = {                      -124,
 -230, -166,    0, -208,    0,    0, -265,    0,    0,    0,
 -124, -249,    0,    0,    0, -247, -145,    0, -230,    0,
    0, -166,    0,    0,    0,    0, -145,    0, -282,    0,
 -246, -219, -207,    0,    0, -205, -175, -173,    0,  -59,
    0, -282, -246, -177,  417, -193, -153,    0,    0,    0,
  -59, -169,    0,    0,    0,    0,    0,  417, -148,  417,
  417,  417,  417,  417, 1037, -187, -147,  -59,    0, -193,
 -171, -280, 1188,    0, 1047, 1076, 1058, 1058, 1058,    0,
    0,  417,  417,  417,  417,  417,  417,  417,  417,  417,
  417,    0,    0,    0,  213,    0, -141,  417, -244,    0,
  885,  885,   13,   13,   13, -231, -231,    0,    0,    0,
  417,  417,  417,  417,    0, -130, -127,  417,  417, -253,
    0, -195,  167, 1188, -121,  -59,    0,    0, 1188,  417,
    0,  -58, 1188, 1105,    0,    0, 1188, 1188, -152,    0,
    0,    0,  247,    0, -119, 1120, -129, -253,  417,    0,
    0,  383, -112,    0, 1149,  281,  417, -129,  417,    0,
    0,  636,    0, 1159, -129,  417, -108,  -63, 1188, -129,
  417, -129,    0,    0,    0,
};
static const YYINT yyrindex[] = {                       154,
 -198, -190,    0,    0,    0,    0,  -69,    0,    0,    0,
  175,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,
   27,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1,   27, -101,    0,   41,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -125,  -68,    0,    0,  -99,
    0,    0, -269,    0,    0,    0,  791,  837,  883,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  693,  742,  526,  578,  630,   59,  113,    0,    0,    0,
    0,   66,    0,    0,    0,  447,  480,    0,    0,    0,
    0,    0,    0,  929,    0,    0,    0,    0, -266,    0,
    0,    0,  963,    0,    0,    0,  997, 1031,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  315,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -83,    0,    0,    0,  349,  -67,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -88,  181,   52, -120,  -60,    0,  189,  182,    0,    0,
    0,  -40,  193,    0,    0,  -95,    2,    0,    0,  252,
  238,  241,   40,  -87,    0,  196,  -86,    0,
};
#define YYTABLESIZE 1501
static const YYINT yytable[] = {                         97,
   12,   12,  143,  131,   65,   55,   26,  126,  127,   29,
   66,   31,   12,   67,   55,   38,   98,   73,   32,   75,
   76,   77,   78,   79,  139,   30,   22,   66,   36,   60,
   67,  156,   40,  141,   19,  126,  144,   20,   60,   42,
   21,  101,  102,  103,  104,  105,  106,  107,  108,  109,
  110,   43,  154,  130,  141,   30,   33,  129,    3,    4,
   29,   53,   54,   55,   56,  111,   37,  141,   33,   30,
  132,   73,  133,  134,   57,   58,   29,  137,  138,   89,
   90,   91,   59,   44,   33,  113,  114,   60,  115,  146,
  116,  117,  118,  119,  120,   45,  125,  163,   51,   22,
  140,   23,   61,   68,  168,   69,   62,   71,  155,  173,
   74,  175,   93,   63,   64,   92,  162,  128,  164,    1,
    2,    3,    4,   95,  125,  169,  135,  145,    8,  136,
  162,   93,   93,   93,   93,   93,   93,   29,  149,   42,
    1,    2,    3,    4,   93,   93,    5,    6,    7,    8,
  157,  158,   93,    4,   93,   93,   93,   93,   93,   93,
   93,   93,   93,   93,   93,  152,   93,   93,   93,  170,
   93,   93,   93,   93,    1,   20,   93,   19,   93,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   74,   74,
   74,   28,   74,   74,   65,   16,   16,   16,   16,  171,
  172,   74,   74,  147,   16,    1,    2,    3,    4,   74,
   64,   74,   74,   74,   74,   74,   74,   74,   74,   74,
   74,   74,  174,   74,   74,   74,   80,   74,   74,   74,
   74,   50,   70,   74,   49,   74,   74,   74,   74,   74,
   74,   74,   74,   74,   74,   82,   83,   84,   85,   86,
   87,   88,   89,   90,   91,   25,   34,   12,   12,   12,
   12,   12,   35,   94,    0,   12,   12,   12,   12,    0,
   12,   12,   12,   12,   12,    0,    0,    0,   12,    0,
    0,   12,   12,   12,   12,    0,   12,   12,   12,   12,
   12,   22,   22,   22,   22,    0,   12,   22,   22,   22,
   22,    0,   12,    0,    0,   21,   21,   21,   21,   12,
   12,   21,   21,   21,   21,   83,   83,   83,   83,   83,
   83,   87,   88,   89,   90,   91,    0,    0,   83,   83,
   14,   14,   14,   14,    0,    0,   83,    0,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,    0,
   83,   83,   83,    0,   83,   83,   83,   83,    0,    0,
   83,    0,   83,   83,   83,   83,   83,   83,   83,   84,
   84,   84,   84,   84,   84,    0,    0,    0,    0,    0,
    0,    0,   84,   84,    0,    0,    0,    0,    0,    0,
   84,    0,   84,   84,   84,   84,   84,   84,   84,   84,
   84,   84,   84,    0,   84,   84,   84,    0,   84,   84,
   84,   84,    0,    0,   84,    0,   84,   84,   84,   84,
   84,   84,   84,   53,   54,   55,   56,  111,    0,    0,
    0,    1,    2,    3,    4,    0,   57,  112,    6,    0,
    0,    0,    0,    0,   59,    0,    0,  113,  114,   60,
  115,    0,  116,  117,  118,  119,  120,    0,    0,    0,
    0,    0,  142,    0,   61,    0,    0,    0,   62,   53,
   54,   55,   56,  111,    0,   63,   64,    1,    2,    3,
    4,    0,   57,  112,    6,    0,    0,    0,    0,    0,
   59,    0,    0,  113,  114,   60,  115,    0,  116,  117,
  118,  119,  120,   53,   54,   55,   56,  111,    0,    0,
   61,    0,    0,    0,   62,    0,   57,   58,    0,    0,
    0,   63,   64,    0,   59,    0,    0,  113,  114,   60,
  115,    0,  116,  117,  118,  119,  120,   53,   54,   55,
   56,  111,  150,    0,   61,    0,    0,    0,   62,    0,
   57,   58,    0,    0,    0,   63,   64,    0,   59,    0,
    0,  113,  114,   60,  115,    0,  116,  117,  118,  119,
  120,   55,   55,   55,   55,   55,  160,    0,   61,    0,
    0,    0,   62,    0,   55,   55,    0,    0,    0,   63,
   64,    0,   55,    0,    0,   55,   55,   55,   55,    0,
   55,   55,   55,   55,   55,   62,   62,   62,   62,   62,
   55,    0,   55,    0,    0,    0,   55,    0,   62,   62,
    0,    0,    0,   55,   55,    0,   62,    0,    0,   62,
   62,   62,   62,    0,   62,   62,   62,   62,   62,   53,
   54,   55,   56,  111,   62,    0,   62,    0,    0,    0,
   62,    0,   57,   58,    0,    0,    0,   62,   62,    0,
   59,    0,    0,  113,  114,   60,  115,    0,  116,  117,
  118,  119,  120,   53,   54,   55,   56,    0,    0,    0,
   61,    0,    0,    0,   62,    0,   57,   58,    0,    0,
    0,   63,   64,    0,   59,    0,    0,    0,    0,   60,
    0,    0,    0,    0,   53,   53,   53,   53,    0,    0,
    0,    0,    0,    0,   61,    0,   53,   53,   62,    0,
    0,    0,    0,    0,   53,   63,   64,   53,   53,   53,
   53,    0,   53,   53,   53,   53,   53,   52,   52,   52,
   52,    0,   53,    0,   53,    0,    0,    0,   53,   52,
   52,    0,    0,    0,    0,   53,   53,   52,    0,    0,
   52,   52,   52,   52,    0,   52,   52,   52,   52,   52,
    0,    0,    0,    0,    0,   52,    0,   52,    0,    0,
    0,   52,   76,   76,   76,   76,   76,   76,   52,   52,
    0,    0,    0,    0,    0,   76,   76,    0,    0,    0,
    0,    0,    0,   76,    0,   76,   76,   76,   76,   76,
   76,   76,   76,   76,   76,   76,    0,   76,   76,   76,
    0,   76,   76,   76,   76,    0,    0,   76,    0,   76,
   76,   76,   76,   76,   75,   75,   75,   75,   75,   75,
    0,    0,    0,    0,    0,    0,    0,   75,   75,    0,
    0,    0,    0,    0,    0,   75,    0,   75,   75,   75,
   75,   75,   75,   75,   75,   75,   75,   75,    0,   75,
   75,   75,    0,   75,   75,   75,   75,    0,    0,   75,
    0,   75,   75,   75,   75,   75,   77,   77,   77,   77,
   77,   77,    0,    0,    0,    0,    0,  165,    0,   77,
   77,    0,    0,    0,    0,    0,    0,   77,    0,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   80,   77,   77,   77,    0,   77,   77,   77,   77,    0,
    0,   77,    0,   77,   77,   77,   77,   77,    0,   82,
   83,   84,   85,   86,   87,   88,   89,   90,   91,   78,
   78,   78,   78,   78,   78,    0,    0,    0,    0,    0,
    0,    0,   78,   78,    0,    0,    0,    0,    0,    0,
   78,    0,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,    0,   78,   78,   78,    0,   78,   78,
   78,   78,    0,    0,   78,    0,   78,   78,   79,   79,
   79,   79,   79,   79,    0,    0,    0,    0,    0,    0,
    0,   79,   79,    0,    0,    0,    0,    0,    0,   79,
    0,   79,   79,   79,   79,   79,   79,   79,   79,   79,
   79,   79,    0,   79,   79,   79,    0,   79,   79,   79,
   79,    0,    0,   79,    0,   79,   79,   85,   85,   85,
   85,   85,   85,    0,    0,    0,    0,    0,    0,    0,
   85,   85,    0,    0,    0,    0,    0,    0,   85,    0,
   85,   85,   85,   85,   85,    0,   85,   85,   85,   85,
   85,    0,   85,   85,   85,    0,   85,   85,   85,   85,
    0,    0,   85,   86,   86,   86,   86,   86,   86,    0,
    0,    0,    0,    0,    0,    0,   86,   86,    0,    0,
    0,    0,    0,    0,   86,    0,   86,   86,   86,   86,
   86,    0,   86,   86,   86,   86,   86,    0,   86,   86,
   86,    0,   86,   86,   86,   86,    0,    0,   86,   87,
   87,   87,   87,   87,   87,    0,    0,    0,    0,    0,
    0,    0,   87,   87,    0,    0,    0,    0,    0,    0,
   87,    0,   87,   87,   87,   87,   87,    0,   87,   87,
   87,   87,   87,    0,   87,   87,   87,    0,   87,   87,
   87,   87,    0,    0,   87,   46,   46,   46,   46,   46,
   84,   85,   86,   87,   88,   89,   90,   91,   46,   46,
    0,    0,    0,    0,    0,    0,   46,    0,    0,   46,
   46,   46,   46,    0,   46,   46,   46,   46,   46,   54,
   54,   54,   54,   54,   46,    0,   46,    0,    0,    0,
   46,    0,   54,   54,    0,    0,    0,    0,    0,    0,
   54,    0,    0,   54,   54,   54,   54,    0,   54,   54,
   54,   54,   54,   49,   49,   49,   49,   49,   54,    0,
   54,    0,    0,    0,   54,    0,   49,   49,    0,    0,
    0,    0,    0,    0,   49,    0,    0,   49,   49,   49,
   49,    0,   49,   49,   49,   49,   49,   48,   48,   48,
   48,   48,   49,    0,   49,    0,    0,    0,   49,    0,
   48,   48,    0,    0,    0,    0,    0,    0,   48,    0,
    0,   48,   48,   48,   48,    0,   48,   48,   48,   48,
   48,   80,    0,    0,    0,    0,   48,    0,   48,    0,
    0,   80,   48,    0,    0,   81,    0,    0,    0,   99,
   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,
   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,
   80,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,    0,    0,    0,  100,    0,    0,    0,    0,   82,
   83,   84,   85,   86,   87,   88,   89,   90,   91,   80,
    0,    0,    0,    0,    0,    0,    0,    0,  148,    0,
    0,    0,    0,    0,   80,    0,    0,    0,   82,   83,
   84,   85,   86,   87,   88,   89,   90,   91,  151,    0,
    0,    0,    0,   82,   83,   84,   85,   86,   87,   88,
   89,   90,   91,   80,    0,    0,    0,    0,    0,    0,
    0,    0,  159,   80,    0,    0,    0,    0,    0,    0,
  166,    0,   82,   83,   84,   85,   86,   87,   88,   89,
   90,   91,   82,   83,   84,   85,   86,   87,   88,   89,
   90,   91,   80,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,
};
static const YYINT yycheck[] = {                        280,
    0,    0,  123,   99,   45,  259,  272,   95,   95,  259,
  280,  259,   11,  280,  259,  298,  297,   58,   17,   60,
   61,   62,   63,   64,  120,  275,    0,  297,   27,  283,
  297,  152,  279,  122,  265,  123,  123,  268,  283,  259,
    0,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,  259,  148,  298,  143,  275,   17,   98,  267,  268,
  259,  257,  258,  259,  260,  261,   27,  156,  259,  275,
  111,  112,  113,  114,  270,  271,  275,  118,  119,  311,
  312,  313,  278,  259,  275,  281,  282,  283,  284,  130,
  286,  287,  288,  289,  290,  269,   95,  158,  276,  266,
  296,  268,  298,  297,  165,  259,  302,  277,  149,  170,
  259,  172,  260,  309,  310,  303,  157,  259,  159,  265,
  266,  267,  268,  295,  123,  166,  257,  126,  274,  257,
  171,  257,  258,  259,  260,  261,  262,  259,  291,  259,
  265,  266,  267,  268,  270,  271,  271,  272,  273,  274,
  263,  264,  278,    0,  280,  281,  282,  283,  284,  285,
  286,  287,  288,  289,  290,  295,  292,  293,  294,  278,
  296,  297,  298,  299,    0,  277,  302,  277,  304,  305,
  306,  307,  308,  309,  310,  311,  312,  313,  257,  258,
  259,   11,  261,  262,  278,  265,  266,  267,  268,  263,
  264,  270,  271,  262,  274,  265,  266,  267,  268,  278,
  278,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  290,  171,  292,  293,  294,  285,  296,  297,  298,
  299,   43,   51,  302,   42,  304,  305,  306,  307,  308,
  309,  310,  311,  312,  313,  304,  305,  306,  307,  308,
  309,  310,  311,  312,  313,    4,   19,  257,  258,  259,
  260,  261,   22,   68,   -1,  265,  266,  267,  268,   -1,
  270,  271,  272,  273,  274,   -1,   -1,   -1,  278,   -1,
   -1,  281,  282,  283,  284,   -1,  286,  287,  288,  289,
  290,  265,  266,  267,  268,   -1,  296,  271,  272,  273,
  274,   -1,  302,   -1,   -1,  265,  266,  267,  268,  309,
  310,  271,  272,  273,  274,  257,  258,  259,  260,  261,
  262,  309,  310,  311,  312,  313,   -1,   -1,  270,  271,
  265,  266,  267,  268,   -1,   -1,  278,   -1,  280,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,   -1,
  292,  293,  294,   -1,  296,  297,  298,  299,   -1,   -1,
  302,   -1,  304,  305,  306,  307,  308,  309,  310,  257,
  258,  259,  260,  261,  262,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
  278,   -1,  280,  281,  282,  283,  284,  285,  286,  287,
  288,  289,  290,   -1,  292,  293,  294,   -1,  296,  297,
  298,  299,   -1,   -1,  302,   -1,  304,  305,  306,  307,
  308,  309,  310,  257,  258,  259,  260,  261,   -1,   -1,
   -1,  265,  266,  267,  268,   -1,  270,  271,  272,   -1,
   -1,   -1,   -1,   -1,  278,   -1,   -1,  281,  282,  283,
  284,   -1,  286,  287,  288,  289,  290,   -1,   -1,   -1,
   -1,   -1,  296,   -1,  298,   -1,   -1,   -1,  302,  257,
  258,  259,  260,  261,   -1,  309,  310,  265,  266,  267,
  268,   -1,  270,  271,  272,   -1,   -1,   -1,   -1,   -1,
  278,   -1,   -1,  281,  282,  283,  284,   -1,  286,  287,
  288,  289,  290,  257,  258,  259,  260,  261,   -1,   -1,
  298,   -1,   -1,   -1,  302,   -1,  270,  271,   -1,   -1,
   -1,  309,  310,   -1,  278,   -1,   -1,  281,  282,  283,
  284,   -1,  286,  287,  288,  289,  290,  257,  258,  259,
  260,  261,  296,   -1,  298,   -1,   -1,   -1,  302,   -1,
  270,  271,   -1,   -1,   -1,  309,  310,   -1,  278,   -1,
   -1,  281,  282,  283,  284,   -1,  286,  287,  288,  289,
  290,  257,  258,  259,  260,  261,  296,   -1,  298,   -1,
   -1,   -1,  302,   -1,  270,  271,   -1,   -1,   -1,  309,
  310,   -1,  278,   -1,   -1,  281,  282,  283,  284,   -1,
  286,  287,  288,  289,  290,  257,  258,  259,  260,  261,
  296,   -1,  298,   -1,   -1,   -1,  302,   -1,  270,  271,
   -1,   -1,   -1,  309,  310,   -1,  278,   -1,   -1,  281,
  282,  283,  284,   -1,  286,  287,  288,  289,  290,  257,
  258,  259,  260,  261,  296,   -1,  298,   -1,   -1,   -1,
  302,   -1,  270,  271,   -1,   -1,   -1,  309,  310,   -1,
  278,   -1,   -1,  281,  282,  283,  284,   -1,  286,  287,
  288,  289,  290,  257,  258,  259,  260,   -1,   -1,   -1,
  298,   -1,   -1,   -1,  302,   -1,  270,  271,   -1,   -1,
   -1,  309,  310,   -1,  278,   -1,   -1,   -1,   -1,  283,
   -1,   -1,   -1,   -1,  258,  259,  260,  261,   -1,   -1,
   -1,   -1,   -1,   -1,  298,   -1,  270,  271,  302,   -1,
   -1,   -1,   -1,   -1,  278,  309,  310,  281,  282,  283,
  284,   -1,  286,  287,  288,  289,  290,  258,  259,  260,
  261,   -1,  296,   -1,  298,   -1,   -1,   -1,  302,  270,
  271,   -1,   -1,   -1,   -1,  309,  310,  278,   -1,   -1,
  281,  282,  283,  284,   -1,  286,  287,  288,  289,  290,
   -1,   -1,   -1,   -1,   -1,  296,   -1,  298,   -1,   -1,
   -1,  302,  257,  258,  259,  260,  261,  262,  309,  310,
   -1,   -1,   -1,   -1,   -1,  270,  271,   -1,   -1,   -1,
   -1,   -1,   -1,  278,   -1,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,   -1,  292,  293,  294,
   -1,  296,  297,  298,  299,   -1,   -1,  302,   -1,  304,
  305,  306,  307,  308,  257,  258,  259,  260,  261,  262,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,   -1,
   -1,   -1,   -1,   -1,   -1,  278,   -1,  280,  281,  282,
  283,  284,  285,  286,  287,  288,  289,  290,   -1,  292,
  293,  294,   -1,  296,  297,  298,  299,   -1,   -1,  302,
   -1,  304,  305,  306,  307,  308,  257,  258,  259,  260,
  261,  262,   -1,   -1,   -1,   -1,   -1,  262,   -1,  270,
  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,   -1,  280,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  285,  292,  293,  294,   -1,  296,  297,  298,  299,   -1,
   -1,  302,   -1,  304,  305,  306,  307,  308,   -1,  304,
  305,  306,  307,  308,  309,  310,  311,  312,  313,  257,
  258,  259,  260,  261,  262,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
  278,   -1,  280,  281,  282,  283,  284,  285,  286,  287,
  288,  289,  290,   -1,  292,  293,  294,   -1,  296,  297,
  298,  299,   -1,   -1,  302,   -1,  304,  305,  257,  258,
  259,  260,  261,  262,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,
   -1,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  290,   -1,  292,  293,  294,   -1,  296,  297,  298,
  299,   -1,   -1,  302,   -1,  304,  305,  257,  258,  259,
  260,  261,  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,   -1,
  280,  281,  282,  283,  284,   -1,  286,  287,  288,  289,
  290,   -1,  292,  293,  294,   -1,  296,  297,  298,  299,
   -1,   -1,  302,  257,  258,  259,  260,  261,  262,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,   -1,   -1,
   -1,   -1,   -1,   -1,  278,   -1,  280,  281,  282,  283,
  284,   -1,  286,  287,  288,  289,  290,   -1,  292,  293,
  294,   -1,  296,  297,  298,  299,   -1,   -1,  302,  257,
  258,  259,  260,  261,  262,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
  278,   -1,  280,  281,  282,  283,  284,   -1,  286,  287,
  288,  289,  290,   -1,  292,  293,  294,   -1,  296,  297,
  298,  299,   -1,   -1,  302,  257,  258,  259,  260,  261,
  306,  307,  308,  309,  310,  311,  312,  313,  270,  271,
   -1,   -1,   -1,   -1,   -1,   -1,  278,   -1,   -1,  281,
  282,  283,  284,   -1,  286,  287,  288,  289,  290,  257,
  258,  259,  260,  261,  296,   -1,  298,   -1,   -1,   -1,
  302,   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
  278,   -1,   -1,  281,  282,  283,  284,   -1,  286,  287,
  288,  289,  290,  257,  258,  259,  260,  261,  296,   -1,
  298,   -1,   -1,   -1,  302,   -1,  270,  271,   -1,   -1,
   -1,   -1,   -1,   -1,  278,   -1,   -1,  281,  282,  283,
  284,   -1,  286,  287,  288,  289,  290,  257,  258,  259,
  260,  261,  296,   -1,  298,   -1,   -1,   -1,  302,   -1,
  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,   -1,
   -1,  281,  282,  283,  284,   -1,  286,  287,  288,  289,
  290,  285,   -1,   -1,   -1,   -1,  296,   -1,  298,   -1,
   -1,  285,  302,   -1,   -1,  299,   -1,   -1,   -1,  293,
  304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
  304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
  285,  304,  305,  306,  307,  308,  309,  310,  311,  312,
  313,   -1,   -1,   -1,  299,   -1,   -1,   -1,   -1,  304,
  305,  306,  307,  308,  309,  310,  311,  312,  313,  285,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  294,   -1,
   -1,   -1,   -1,   -1,  285,   -1,   -1,   -1,  304,  305,
  306,  307,  308,  309,  310,  311,  312,  313,  299,   -1,
   -1,   -1,   -1,  304,  305,  306,  307,  308,  309,  310,
  311,  312,  313,  285,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  294,  285,   -1,   -1,   -1,   -1,   -1,   -1,
  292,   -1,  304,  305,  306,  307,  308,  309,  310,  311,
  312,  313,  304,  305,  306,  307,  308,  309,  310,  311,
  312,  313,  285,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  304,  305,  306,  307,  308,  309,  310,  311,  312,
  313,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 313
#define YYUNDFTOKEN 344
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER","tDOUBLE",
"tIDENTIFIER","tSTRING","tIF","tTHEN","tELSIF","tELSE","tSMALL","tHUGE","tNEWS",
"tFAKE","tINITIALLY","tNULL","tUSE","tPUBLIC","tDEFINE","tPROCEDURE",
"tFUNCTION","tON","tAS","tDO","tUSES","tFOR","tRETURN","tASSIGN","tCELL",
"tINPUT","tOBJECTS","tSTOP","tAGAIN","tPOST","tTWEET","tSWEEPING","tFROM","tBY",
"tAT","tTO","tINSIDE","tOUTSIDE","tCOMMA","tOPEN","tCLOSE","tIFX","tUNARY",
"tNOT","tADDRESS","tAND","tOR","tABOVE","tBELOW","tEQUALS","tPLUS","tMINUS",
"tTIMES","tOVER","tMODULUS",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : decl_chain",
"decl_chain : decl",
"decl_chain : decl_chain decl",
"decl_chain :",
"decl : var_decl",
"decl : access func_type tIDENTIFIER uses",
"decl : func_type tIDENTIFIER uses",
"decl : tDEFINE decl_access func_type tIDENTIFIER func_params tAS blockStart",
"var_decl : access type tIDENTIFIER initially",
"var_decl : type tIDENTIFIER initially",
"initially : tOPEN tINITIALLY expr tCLOSE",
"initially :",
"access : tPUBLIC",
"access : tUSE",
"decl_access : tPUBLIC",
"decl_access :",
"func_type : type tFUNCTION",
"func_type : tPROCEDURE",
"func_params : tON params",
"func_params :",
"uses : tUSES params",
"uses :",
"params : variable",
"params : params tCOMMA variable",
"variable : type tIDENTIFIER",
"type : small",
"type : huge",
"type : news",
"small : tSMALL",
"small : tSMALL small_chain",
"small_chain : tSMALL small_chain",
"small_chain : tFAKE",
"huge : tHUGE",
"huge : tHUGE huge_chain",
"huge_chain : tHUGE huge_chain",
"huge_chain : tFAKE",
"news : tFAKE news",
"news : tNEWS",
"blockStart : tINSIDE var_chain list tOUTSIDE",
"blockStart : tINSIDE var_chain tOUTSIDE",
"blockStart : tINSIDE list tOUTSIDE",
"var_chain : var_decl",
"var_chain : var_chain var_decl",
"list : inst",
"list : list inst",
"inst : expr",
"inst : tASSIGN expr tTO lval",
"inst : tTWEET expr",
"inst : tPOST expr",
"inst : tAGAIN tINTEGER",
"inst : tSTOP tINTEGER",
"inst : tAGAIN",
"inst : tSTOP",
"inst : tRETURN expr",
"inst : tIF expr tTHEN indent_list",
"inst : tIF expr tTHEN indent_list tELSE indent_list",
"inst : tIF expr tTHEN indent_list tELSIF elif",
"inst : tSWEEPING lval tFROM expr tTO expr sweepBy tDO indent_list",
"inst : tINPUT",
"indent_list : tINSIDE list tOUTSIDE",
"elif : expr tTHEN indent_list tELSIF elif",
"elif : expr tTHEN indent_list",
"elif : expr tTHEN indent_list tELSE indent_list",
"sweepBy : tBY expr",
"sweepBy :",
"expr_chain : expr",
"expr_chain : expr_chain tCOMMA expr",
"lval : tIDENTIFIER",
"lval : tCELL expr tAT lval",
"lval : tCELL expr tAT tOPEN expr tCLOSE",
"expr : tINTEGER",
"expr : tDOUBLE",
"expr : tNULL",
"expr : str_chain",
"expr : expr tBELOW expr",
"expr : expr tABOVE expr",
"expr : expr tEQUALS expr",
"expr : expr tAND expr",
"expr : expr tOR expr",
"expr : expr tTIMES expr",
"expr : expr tOVER expr",
"expr : expr tMODULUS expr",
"expr : expr tPLUS expr",
"expr : expr tMINUS expr",
"expr : tNOT expr",
"expr : tPLUS expr",
"expr : tMINUS expr",
"expr : tOPEN expr tCLOSE",
"expr : tUSE expr_chain tFOR tIDENTIFIER",
"expr : tDO tIDENTIFIER",
"expr : expr tOBJECTS",
"expr : lval tADDRESS",
"expr : lval",
"str_chain : tSTRING",
"str_chain : str_chain tSTRING",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 220 "gr8_parser.y"

#line 711 "gr8_parser.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 63 "gr8_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 65 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 3:
#line 66 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 4:
#line 67 "gr8_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 5:
#line 70 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].var; }
break;
case 6:
#line 71 "gr8_parser.y"
	{ yyval.node = new gr8::function_dec_node(LINE, yystack.l_mark[-3].accessSpec, yystack.l_mark[-1].s, yystack.l_mark[-2].btype, yystack.l_mark[0].sequence); }
break;
case 7:
#line 72 "gr8_parser.y"
	{ yyval.node = new gr8::function_dec_node(LINE, gr8::access_specifier::_none, yystack.l_mark[-1].s, yystack.l_mark[-2].btype, yystack.l_mark[0].sequence); }
break;
case 8:
#line 73 "gr8_parser.y"
	{ yyval.node = new gr8::function_def_node(LINE, yystack.l_mark[-5].accessSpec, yystack.l_mark[-3].s, yystack.l_mark[-4].btype, yystack.l_mark[-2].sequence, yystack.l_mark[0].block);}
break;
case 9:
#line 76 "gr8_parser.y"
	{ yyval.var = new gr8::variable_node(LINE, yystack.l_mark[-3].accessSpec, yystack.l_mark[-1].s, yystack.l_mark[-2].btype, yystack.l_mark[0].expression); }
break;
case 10:
#line 77 "gr8_parser.y"
	{ yyval.var = new gr8::variable_node(LINE, gr8::access_specifier::_none, yystack.l_mark[-1].s, yystack.l_mark[-2].btype, yystack.l_mark[0].expression); }
break;
case 11:
#line 79 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 12:
#line 80 "gr8_parser.y"
	{ yyval.expression = nullptr; }
break;
case 13:
#line 83 "gr8_parser.y"
	{ yyval.accessSpec = gr8::access_specifier::_public; }
break;
case 14:
#line 84 "gr8_parser.y"
	{ yyval.accessSpec = gr8::access_specifier::_use; }
break;
case 15:
#line 86 "gr8_parser.y"
	{ yyval.accessSpec = gr8::access_specifier::_public; }
break;
case 16:
#line 87 "gr8_parser.y"
	{ yyval.accessSpec = gr8::access_specifier::_none; }
break;
case 17:
#line 90 "gr8_parser.y"
	{ yyval.btype = yystack.l_mark[-1].btype ;}
break;
case 18:
#line 91 "gr8_parser.y"
	{ yyval.btype = nullptr;}
break;
case 19:
#line 93 "gr8_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 20:
#line 94 "gr8_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 21:
#line 97 "gr8_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 22:
#line 98 "gr8_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 23:
#line 100 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].var); }
break;
case 24:
#line 101 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].var, yystack.l_mark[-2].sequence); }
break;
case 25:
#line 103 "gr8_parser.y"
	{ yyval.var = new gr8::variable_node(LINE, gr8::access_specifier::_none, yystack.l_mark[0].s, yystack.l_mark[-1].btype, nullptr); }
break;
case 28:
#line 106 "gr8_parser.y"
	{ yyval.btype = yystack.l_mark[0].btype; }
break;
case 29:
#line 109 "gr8_parser.y"
	{ yyval.btype = new basic_type(4, basic_type::TYPE_INT); }
break;
case 30:
#line 110 "gr8_parser.y"
	{ basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = yystack.l_mark[0].btype;
                                                        yyval.btype = typ; }
break;
case 31:
#line 114 "gr8_parser.y"
	{ basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = yystack.l_mark[0].btype;
                                                        yyval.btype = typ; }
break;
case 32:
#line 117 "gr8_parser.y"
	{ yyval.btype = new basic_type(4, basic_type::TYPE_INT); }
break;
case 33:
#line 120 "gr8_parser.y"
	{ yyval.btype = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 34:
#line 121 "gr8_parser.y"
	{ basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = yystack.l_mark[0].btype;
                                                        yyval.btype = typ; }
break;
case 35:
#line 125 "gr8_parser.y"
	{ basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = yystack.l_mark[0].btype;
                                                        yyval.btype = typ; }
break;
case 36:
#line 128 "gr8_parser.y"
	{ yyval.btype = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 37:
#line 131 "gr8_parser.y"
	{ basic_type* typ = new basic_type(4, basic_type::TYPE_POINTER);
                                                        typ->_subtype = yystack.l_mark[0].btype;
                                                        yyval.btype = typ; }
break;
case 38:
#line 134 "gr8_parser.y"
	{ yyval.btype = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 39:
#line 139 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 40:
#line 140 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-1].sequence, nullptr); }
break;
case 41:
#line 141 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, nullptr, yystack.l_mark[-1].sequence); }
break;
case 42:
#line 144 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].var); }
break;
case 43:
#line 145 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].var, yystack.l_mark[-1].sequence); }
break;
case 44:
#line 148 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 45:
#line 149 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 46:
#line 152 "gr8_parser.y"
	{ yyval.node = new gr8::evaluation_node(LINE, yystack.l_mark[0].expression); }
break;
case 47:
#line 153 "gr8_parser.y"
	{ yyval.node = new cdk::assignment_node(LINE, yystack.l_mark[0].lvalue, yystack.l_mark[-2].expression); }
break;
case 48:
#line 154 "gr8_parser.y"
	{ yyval.node = new gr8::print_node(LINE, false, yystack.l_mark[0].expression); }
break;
case 49:
#line 155 "gr8_parser.y"
	{ yyval.node = new gr8::print_node(LINE, true, yystack.l_mark[0].expression); }
break;
case 50:
#line 156 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE, yystack.l_mark[0].i); }
break;
case 51:
#line 157 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE, yystack.l_mark[0].i); }
break;
case 52:
#line 158 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE, 1); }
break;
case 53:
#line 159 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE, 1); }
break;
case 54:
#line 160 "gr8_parser.y"
	{ yyval.node = new gr8::return_node(LINE, yystack.l_mark[0].expression); }
break;
case 55:
#line 161 "gr8_parser.y"
	{ yyval.node = new gr8::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].sequence); }
break;
case 56:
#line 162 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].sequence, yystack.l_mark[0].sequence); }
break;
case 57:
#line 163 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 58:
#line 164 "gr8_parser.y"
	{ yyval.node = new gr8::sweeping_node(LINE, yystack.l_mark[-7].lvalue, yystack.l_mark[-5].expression, yystack.l_mark[-3].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].sequence); }
break;
case 59:
#line 165 "gr8_parser.y"
	{ yyval.node = new gr8::input_node(LINE); }
break;
case 60:
#line 168 "gr8_parser.y"
	{ yyval.sequence = yystack.l_mark[-1].sequence; }
break;
case 61:
#line 171 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 62:
#line 172 "gr8_parser.y"
	{ yyval.node = new gr8::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].sequence); }
break;
case 63:
#line 173 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].sequence, yystack.l_mark[0].sequence); }
break;
case 64:
#line 176 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 65:
#line 177 "gr8_parser.y"
	{ yyval.expression = nullptr; }
break;
case 66:
#line 180 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 67:
#line 181 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 68:
#line 184 "gr8_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); }
break;
case 69:
#line 185 "gr8_parser.y"
	{ yyval.lvalue = new gr8::cell_node(LINE, new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue), yystack.l_mark[-2].expression); }
break;
case 70:
#line 186 "gr8_parser.y"
	{ yyval.lvalue = new gr8::cell_node(LINE, yystack.l_mark[-1].expression, yystack.l_mark[-4].expression); }
break;
case 71:
#line 190 "gr8_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 72:
#line 191 "gr8_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); }
break;
case 73:
#line 192 "gr8_parser.y"
	{ yyval.expression = new gr8::null_node(LINE); }
break;
case 74:
#line 193 "gr8_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 75:
#line 194 "gr8_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 76:
#line 195 "gr8_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 196 "gr8_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 197 "gr8_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 79:
#line 198 "gr8_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 80:
#line 199 "gr8_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 81:
#line 200 "gr8_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 82:
#line 201 "gr8_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 83:
#line 202 "gr8_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 84:
#line 203 "gr8_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 85:
#line 204 "gr8_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression);}
break;
case 86:
#line 205 "gr8_parser.y"
	{ yyval.expression = new gr8::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 87:
#line 206 "gr8_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 88:
#line 207 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 89:
#line 208 "gr8_parser.y"
	{ yyval.expression = new gr8::function_call_node(LINE, yystack.l_mark[0].s, yystack.l_mark[-2].sequence); }
break;
case 90:
#line 209 "gr8_parser.y"
	{ yyval.expression = new gr8::function_call_node(LINE, yystack.l_mark[0].s, nullptr); }
break;
case 91:
#line 210 "gr8_parser.y"
	{ yyval.expression = new gr8::objects_node(LINE, yystack.l_mark[-1].expression); }
break;
case 92:
#line 211 "gr8_parser.y"
	{ yyval.expression = new gr8::address_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 93:
#line 212 "gr8_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 94:
#line 215 "gr8_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 95:
#line 216 "gr8_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); }
break;
#line 1292 "gr8_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
