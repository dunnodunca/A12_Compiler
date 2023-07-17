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
#               @@@@|   K  A O  |@@@@             #
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
#define READER_DEFAULT_POSITION		0	/* default initial buffer position*/
#define READER_DEFAULT_HISTOGRAM	0		/* default histogram*/
#define READER_END					250		/*end of reader*/
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
#define READER_FUL 0x80
/* TO_DO: BIT 2: EMP: Empty */
#define READER_EMP 0x40
/* TO_DO: BIT 1: REL = Relocation */
#define READER_REL 0x20
/* TO_DO: BIT 0: END = EndOfBuffer */
#define READER_BIT 0x10
#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct offset {
	kao_int mark;			/* the offset to the mark position (in chars) */
	kao_int read;			/* the offset to the get a char position (in chars) */
	kao_int wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */
typedef struct bufferReader {
	kao_string	content;			/* pointer to the beginning of character array (character buffer) */
	kao_int	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	kao_int	increment;			/* character array increment factor */
	kao_int	mode;				/* operational mode indicator */
	kao_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Offset		offset;				/* Offset / position field */
	kao_int	histogram[NCHAR];	/* Statistics of chars */
	kao_int	numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(kao_int, kao_int, kao_int);
ReaderPointer	readerAddChar		(ReaderPointer const, kao_char);
kao_boln		readerClear		    (ReaderPointer const);
kao_boln		readerFree		    (ReaderPointer const);
kao_boln		readerIsFull		(ReaderPointer const);
kao_boln		readerIsEmpty		(ReaderPointer const);
kao_boln		readerSetMark		(ReaderPointer const, kao_int);
kao_int		readerPrint		    (ReaderPointer const);
kao_int		readerLoad			(ReaderPointer const, FILE* const);
kao_boln		readerRecover		(ReaderPointer const);
kao_boln		readerRetract		(ReaderPointer const);
kao_boln		readerRestore		(ReaderPointer const);
/* Getters */
kao_char		readerGetChar		(ReaderPointer const);
kao_string		readerGetContent	(ReaderPointer const, kao_int);
kao_int		readerGetPosRead	(ReaderPointer const);
kao_int		readerGetPosWrte	(ReaderPointer const);
kao_int		readerGetPosMark	(ReaderPointer const);
kao_int		readerGetSize		(ReaderPointer const);
kao_int		readerGetInc		(ReaderPointer const);
kao_int		readerGetMode		(ReaderPointer const);
kao_byte		readerGetFlags		(ReaderPointer const);
kao_void		readerPrintStat		(ReaderPointer const);
kao_int		readerNumErrors		(ReaderPointer const);

#endif
