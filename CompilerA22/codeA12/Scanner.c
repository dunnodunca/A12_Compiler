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
#               @@@@|  K A O  |@@@@             #
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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
kao_int line;								/* Current line number of the source code */
extern kao_int errorNumber;				/* Defined in platy_st.c - run-time error number */

extern kao_int stateType[NUM_STATES];
extern kao_string keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern kao_int transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

kao_int startScanner(ReaderPointer psc_buf) {
	/* TO_DO: Start histogram */
	if (readerIsEmpty(psc_buf)) return EXIT_FAILURE;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	/*
	readerSetMark(psc_buf, 0);
	readerGetPosMark(psc_buf);
	*/
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(kao_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	kao_char c;	/* input symbol */
	kao_int state = 0;		/* initial state of the FSM */
	kao_int lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	kao_int lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	kao_int lexLength;		/* token length */
	kao_int i;				/* counter */
	/*
	kao_char newc;			// new char
	*/

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
			continue;
		case '\t':
			continue;
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		
		/* Case Arithmetic*/
		case '+':
			currentToken.code = AVID_T;
			currentToken.attribute.arithmeticOperator = OP_ADD;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '-':
			currentToken.code = AVID_T;
			currentToken.attribute.arithmeticOperator = OP_SUB;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '*':
			currentToken.code = AVID_T;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '/':
			currentToken.code = AVID_T;
			currentToken.attribute.arithmeticOperator = OP_DIV;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '%':
			currentToken.code = AVID_T;
			currentToken.attribute.arithmeticOperator = OP_MOD;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

			/* Relational Token*/
		case '=':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_EQ;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = ASS_OP_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

			
		case '!':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_NE;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = LOG_OP_T;

			currentToken.attribute.relationalOperator = OP_NOT;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

		case '>':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.relationalOperator = OP_GE;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_GT;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '<':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.relationalOperator = OP_LE;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_LT;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		/*case '>=':
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_GE;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '<=':
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_LE;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;*/

			/* Case of  Logical*/
		case '&&':
				currentToken.code = LOG_OP_T;
				currentToken.attribute.relationalOperator = OP_AND;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
		case '||':
				currentToken.code = LOG_OP_T;
				currentToken.attribute.relationalOperator = OP_OR;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			
		/*case '!':
			currentToken.code = LOG_OP_T;
			
			currentToken.attribute.relationalOperator = OP_NOT;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;*/

			// string literal token
		case  '"':
			currentToken.code = STR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */
		

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((kao_int)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			/*input data histogram here*/
			scData.scanHistogram[currentToken.code]++;
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch
		
	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

kao_int nextState(kao_int state, kao_char c) {
	if (state < 0) return KAO_FALSE;
	if (c = '\0') return KAO_FALSE;
	kao_int col;
	kao_int next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

kao_int nextClass(kao_char c) {
	if (c = '\0') return KAO_FALSE;
	kao_int val = -1;
	switch (c) {
	case CHRCOL0:
		val = 0;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL5:
		val = 5;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHRCOL7:
		val = 7;
		break;
	case CHRCOL9:
		val = 9;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 8;
		break;
	default:
		if (isalpha(c))
			val = 1;
		else if (isdigit(c))
			val = 2;
		else
			val = 10;
	}
	/*/case CHRCOL2:
		val = 2;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 5;
		break;
	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else
			val = 7;
	}*/
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT (kao_string lexeme) {
//	if (lexeme == NULL) return;
	Token currentToken = { 0 };
	kao_int i = 0, len = (kao_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
	}
	currentToken.code = CMT_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}

 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(kao_string lexeme) {
	Token currentToken = { 0 };
	kao_long tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			
			currentToken.attribute.intValue = (kao_int)tlong;
			scData.scanHistogram[currentToken.code]++;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(kao_string lexeme) {
	
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	kao_char lastch = lexeme[length - 1];
	kao_int isID = KAO_FALSE;
	switch (lastch) {
		case MNID_SUF:
			currentToken.code = MNID_T;
			scData.scanHistogram[currentToken.code]++;
			isID = KAO_TRUE;
			break;
		default:
			// Test Keyword
			currentToken = funcKEY(lexeme);
			break;
	}
	if (isID == KAO_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(kao_string lexeme) {
//	if (lexeme == NULL) return;
	Token currentToken = { 0 };
	kao_int i = 0, len = (kao_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(kao_string lexeme) {
//	if (lexeme == NULL) return;
	Token currentToken = { 0 };
	kao_int kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.codeType = kwindex;
		scData.scanHistogram[currentToken.code]++;
	}
	else {
		currentToken = funcErr(lexeme);
	}
	return currentToken;
}



/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(kao_string lexeme) {
//	if (lexeme == NULL) return;
	Token currentToken = { 0 };
	kao_int i = 0, len = (kao_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

kao_void printToken(Token t) {
	extern kao_string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:

		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (kao_int)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (kao_int)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
		
		/* extra token*/
	case AVID_T:
		printf("AVID_T\n");
		break;
	case COM_T:
		printf("COM_T\n");
		break;
	case SVID_T:
		printf("SVID_T\n");
		break;
	case FPL_T:
		printf("FPL_T\n");
		break;
	case ASS_OP_T:
		printf("ASS_OP_T\n");
		break;
	case ART_OP_T:
		printf("ART_OP_T\n");
		break;
	case REL_OP_T:
		printf("REL_OP_T\n");
		break;
	case LOG_OP_T:
		printf("LOG_OP_T\n");
		break;

	case EOS_T:
		printf("EOS_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
kao_void printScannerData(ScannerData scData) {
	/* TO_DO: Print Scanner statistics */
	printf("Scanner Statistics: \n");
	printf("---------------------------------- \n");
	int count = 0;
	for (count = 0; count < NUM_TOKENS; count++)
		if (scData.scanHistogram[count] > 0)
			printf("%s%s%s%d\n", "Token[", tokenStrTable[count], "]=", scData.scanHistogram[count]);
	printf("---------------------------------- \n");
	
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
