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
#               @@@@|  M O L D  |@@@@             #
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
	mold_intg mark;			/* the offset to the mark position (in chars) */
	mold_intg read;			/* the offset to the get a char position (in chars) */
	mold_intg wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */
typedef struct bufferReader {
	mold_string	content;			/* pointer to the beginning of character array (character buffer) */
	mold_intg	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	mold_intg	increment;			/* character array increment factor */
	mold_intg	mode;				/* operational mode indicator */
	mold_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Offset		offset;				/* Offset / position field */
	mold_intg	histogram[NCHAR];	/* Statistics of chars */
	mold_intg	numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(mold_intg, mold_intg, mold_intg);
ReaderPointer	readerAddChar		(ReaderPointer const, mold_char);
mold_boln		readerClear		    (ReaderPointer const);
mold_boln		readerFree		    (ReaderPointer const);
mold_boln		readerIsFull		(ReaderPointer const);
mold_boln		readerIsEmpty		(ReaderPointer const);
mold_boln		readerSetMark		(ReaderPointer const, mold_intg);
mold_intg		readerPrint		    (ReaderPointer const);
mold_intg		readerLoad			(ReaderPointer const, FILE* const);
mold_boln		readerRecover		(ReaderPointer const);
mold_boln		readerRetract		(ReaderPointer const);
mold_boln		readerRestore		(ReaderPointer const);
/* Getters */
mold_char		readerGetChar		(ReaderPointer const);
mold_string		readerGetContent	(ReaderPointer const, mold_intg);
mold_intg		readerGetPosRead	(ReaderPointer const);
mold_intg		readerGetPosWrte	(ReaderPointer const);
mold_intg		readerGetPosMark	(ReaderPointer const);
mold_intg		readerGetSize		(ReaderPointer const);
mold_intg		readerGetInc		(ReaderPointer const);
mold_intg		readerGetMode		(ReaderPointer const);
mold_byte		readerGetFlags		(ReaderPointer const);
mold_void		readerPrintStat		(ReaderPointer const);
mold_intg		readerNumErrors		(ReaderPointer const);

#endif
