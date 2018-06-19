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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
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
extern YYSTYPE yylval;
