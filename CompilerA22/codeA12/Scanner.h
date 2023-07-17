/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#               @@@@|  K  A O  |@@@@             #
#            @@@@@@@@-----------@@@@@@@@          #
#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #
#       @@@@@@@@@@@@@      @@@       @@@@@@       #
#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #
#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #
#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #
#  @@@@@@@@@@    @@             @@@@      @@@@@@  #
#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #
# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #
# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #
# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #
#  @@@@     @@@@@@@              @@@@@    @@@@@@  #
#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #
#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #
#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #
#     @@@@@@@@@       @@@        @@@@@@@@@@@      #
#       @@@@@@         @@         @@@@@@@@@       #
#         @@@@@       @@@@@     @@@@@@@@@         #
#            @@@@@@@@@@@@@@@@@@@@@@@@@            #
#               @@@@@@@@@@@@@@@@@@@               #
#  COMPILERS        @@@@@@@@@@@        2023-S     #
#                                                 #
###################################################
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 22

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	COM_T,		/* 13: Comma token*/
	SVID_T, 	/* 14: String Variable identifier token*/
	AVID_T,		/* 15: Arithmetic Variable identifier token*/
	FPL_T,		/* 16: Floating point literal token */
	SCC_OP_T,	/* 17: String concatenation operator token */
	ASS_OP_T,	/* 18: Assignment operator token*/
	ART_OP_T,	/* 19: Arithmetic operator token*/
	REL_OP_T,	/* 20: Relational operator token*/
	LOG_OP_T	/* 21: Logical operator token*/
};

/* TO_DO: Define the list of keywords */
static kao_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"COM_T",
	"SVID_T",
	"AVID_T",
	"FPL_T",
	"SCC_OP_T",
	"ASS_OP_T",
	"ART_OP_T",
	"REL_OP_T",
	"LOG_OP_T"
	
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { 
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD
} AriOperator;
typedef enum RelationalOperators { 
	OP_EQ,
	OP_NE, 
	OP_GT, 
	OP_LT,
	OP_GE,
	OP_LE
} RelOperator;
typedef enum LogicalOperators { 
	OP_AND ,
	OP_OR, 
	OP_NOT 
} LogOperator;
typedef enum SourceEndOfFile { 
	SEOF_0,
	SEOF_255 
} EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	kao_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	kao_int intValue;						/* integer literal attribute (value) */
	kao_int keywordIndex;					/* keyword index in the keyword table */
	kao_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	kao_real floatValue;					/* floating-point literal attribute (value) */
	kao_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	kao_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	kao_byte flags;			/* Flags information */
	union {
		kao_int intValue;				/* Integer value */
		kao_real floatValue;			/* Float value */
		kao_string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	kao_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	kao_int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
/*#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''
#define CHRCOL6 '#'*/

#define CHRCOL0 '$'
#define CHRCOL3 ' '
#define CHRCOL4 '_'
#define CHRCOL5 '('
#define CHRCOL6 ')'
#define CHRCOL7 '\''
#define CHRCOL9 '#'

/* These constants will be used on VID / MID function */
#define MNID_SUF '$'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	10		/* Error state with no retract */
#define ESWR	11		/* Error state with retract */
#define FS		12		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		13 //16
#define CHAR_CLASSES	11 //9

/* TO_DO: Transition table - type of states defined in separate table */
static kao_int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
		   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
		   /*        {1, ESNR, ESNR, ESNR,    4, ESWR,	  6, ESNR},	// S0: NOAS
			  {     1,    1,    1,    2,	  3,    3,   3,    3},	// S1: NOAS
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S2: ASNR (MVID)
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S3: ASWR (KEY)
			  {     4,    4,    4,    4,    5, ESWR,	  4,    4},	// S4: NOAS
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
			  {     6,    6,    6,    6,    6, ESWR,	  7,    6},	// S6: NOAS
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S7: ASNR (COM)
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S8: ASNR (ES)
			  {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS}  // S9: ASWR (ER)
			  */

			 /*	$		[a - Z]	[0 - 9]	space	_		(		)		\		SEOF	#		other
			  (0)		L(1)	D(2)	S(3)	U(4)	RB(5)	LR(6)	Q(7)	E(8)	C(9)	O(10)*/
			{	1,		1,		ESNR,	ESNR,	ESNR,	ESNR,	ESNR,	7,		ESWR,	9,		ESNR},	//S00: NOAS
			{	1,		1,		ESNR,	2,		ESNR,	ESNR,	ESNR,	3,		3,		3,		3},	//S01: NOAS
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS},	//S02: KW(ASWR)
			{	ESNR,	3,		3,		ESNR,	3,		3,		4,		5,		5,		5,		5},	//S03: NOAS
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS},	//S04: ASNR(MVID)
			{	ESNR,	5,		5,		5,		5,		ESNR,	6,		7,		ESWR,	ESNR,	ESNR},	//S05: NOAS
			{	ESNR,	ESNR,	ESNR,	6,		ESNR,	ESNR,	ESNR,	7,		6,		6,		6},		//S06: NOAS
			{	7,		7,		7,		7,		7,		7,		7,		8,		ESWR,	7,		7},		//S07: NOAS
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS},	//S08: ASNR(SL)
			{	9,		9,		9,		9,		9,		9,		9,		9,		ESWR,	10,		8},		//S09: NOAS
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS},	//S010: ASNR(COM)
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS},	//S011: ASNR(ES)
			{	FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS,		FS}	//S012: ASWR(ER)
			


};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static kao_int stateType[NUM_STATES] = {

	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY) */
	NOFS, /* 03 */
	FSNR, /* 04 (MVID) - METHOD */ 
	NOFS, /* 05 */
	NOFS, /* 06 */
	NOFS, /* 07 */
	FSNR, /* 08 (SL) */
	NOFS, /* 09 */
	FSNR, /* 10 (COM) */
	FSNR, /* 11 (Err1 - no retract) */
	FSWR  /* 12 (Err2 - retract) */

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
kao_int			startScanner(ReaderPointer psc_buf);
static kao_int	nextClass(kao_char c);					/* character class function */
static kao_int	nextState(kao_int, kao_char);		/* state machine function */
kao_void			printScannerData(ScannerData scData);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(kao_string lexeme);

/* Declare accepting states functions */
Token funcSL	(kao_string lexeme);
Token funcIL	(kao_string lexeme);
Token funcID	(kao_string lexeme);
Token funcCMT   (kao_string lexeme);
Token funcKEY	(kao_string lexeme);
Token funcErr	(kao_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcKEY,	/* KEY  [02] */
	NULL,		/* -    [03] */
	funcID,		/* MNID	[04] */
	NULL,		/* -    [05] */
	NULL,		/* -    [06] */
	NULL,		/* -    [07] */
	funcSL,		/* SL   [08] */
	NULL,		/* -    [09] */
	funcCMT,	/* COM  [10] */
	funcErr,	/* ERR1 [11] */
	funcErr,	/* ERR2 [12] */

};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 35

/* TO_DO: Define the list of keywords */
static kao_string keywordTable[KWT_SIZE] = {
	"as",		/* KW00 */
	"break",		/* KW01 */
	"const",		/* KW02 */
	"continue",		/* KW03 */
	"crate",		/* KW04 */
	"else",		/* KW05 */
	"enum",		/* KW06 */
	"extern",		/* KW07 */
	"false",		/* KW08 */
	"fn",		/* KW09 */
	"for",		/* KW10 */
	"if",		/* KW11 */
	"impl",		/* KW12 */
	"in",		/* KW13 */
	"let",		/* KW14 */
	"loop",		/* KW15 */
	"match",		/* KW16 */
	"mod",		/* KW17 */
	"move",		/* KW18 */
	"mute",		/* KW19 */
	"pub",		/* KW20 */
	"ref",		/* KW21 */
	"return",		/* KW22 */
	"Self",		/* KW23 */
	"self",		/* KW24 */
	"static",		/* KW25 */
	"struct",		/* KW26 */
	"super",		/* KW27 */
	"trait",		/* KW28 */
	"true",		/* KW29 */
	"type",		/* KW30 */
	"unsafe",		/* KW31 */
	"use",		/* KW32 */
	"where",		/* KW33 */
	"while"		/* KW34 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	kao_char indentationCharType;
	kao_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
kao_int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
