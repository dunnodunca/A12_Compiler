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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(mold_intg size, mold_intg increment, mold_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	if (size ==0) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if(increment==0) mode = MODE_FIXED;

	if (!( mode == MODE_FIXED || mode == MODE_ADDIT || mode==MODE_MULTI)){
		//readerPointer->numReaderErrors++;
		return MOLD_FALSE;
	}

	/* TO_DO: Adjust the values according to parameters */
	//mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer)
		return NULL;
	
	readerPointer->content = (mold_string)malloc(size);
	/* TO_DO: Defensive programming */
	if(readerPointer->content == NULL) return NULL;
	/* TO_DO: Initialize the histogram */
	for(int i=0;i<NCHAR;i++) readerPointer->histogram[i]=0;

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;

	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP */
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, mold_char ch) {
	mold_string tempReader = NULL;
	mold_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL || ch =='\0'){
		//readerPointer->numReaderErrors++;
		return NULL;  
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= ~READER_REL;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->offset.wrte * (mold_intg)sizeof(mold_char) < readerPointer->size) { 
		/* TO_DO: This buffer is NOT full */
		readerPointer->histogram[ch]++;
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= ~READER_FUL;
		
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer ->increment;
			/* TO_DO: Defensive programming */
			if(newSize <=0 && newSize>=READER_MAX_SIZE) return NULL;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer -> increment;
			/* TO_DO: Defensive programming */
			if(newSize<=0 && newSize>READER_MAX_SIZE) return NULL;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		
		/* TO_DO: Defensive programming */
		if (tempReader == NULL) {
			readerPointer->numReaderErrors++;
			return NULL;
		}
		/* TO_DO: Check Relocation */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		if(readerPointer->offset.wrte >= readerPointer->size / sizeof(mold_char)){
			readerPointer->numReaderErrors++;
			return readerPointer;
		}
		
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->offset.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	if(readerPointer->content != NULL){
		readerFree(readerPointer);
		readerPointer->content = NULL;
	}
	/* TO_DO: Adjust flags original */
	readerPointer->size = READER_DEFAULT_SIZE;
	readerPointer->offset.read = READER_DEFAULT_POSITION;
	readerPointer->offset.wrte = READER_DEFAULT_POSITION;
	readerPointer->flags = READER_EMP;
	return MOLD_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer);
	return MOLD_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;

	/* TO_DO: Check flag if buffer is FUL */
	if(readerPointer->flags & READER_FUL) return MOLD_TRUE;
	return MOLD_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if(readerPointer->flags & READER_EMP) return MOLD_TRUE;
	return MOLD_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerSetMark(ReaderPointer const readerPointer, mold_intg mark) {
	/* TO_DO: Defensive programming */
	if(!readerPointer || mark<0 || mark > readerPointer->offset.wrte) return MOLD_FALSE;
	
	/* TO_DO: Adjust mark */
	readerPointer->offset.mark = mark;
	return MOLD_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerPrint(ReaderPointer const readerPointer) {
	mold_intg cont = 0;
	mold_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if(readerPointer == NULL) return MOLD_FALSE;
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	if(readerPointer->flags & READER_END) return MOLD_TRUE;

	while (cont < readerPointer->offset.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	mold_intg size = 0;
	mold_char c;
	/* TO_DO: Defensive programming */
	if(readerPointer==NULL) return MOLD_FALSE;

	c = (mold_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */

	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Recover positions */
	readerPointer->offset.read = 0;
	readerPointer->offset.mark = 0;
	return MOLD_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	if(readerPointer->offset.wrte > 0){
		readerPointer->offset.wrte--;
		if(readerPointer->offset.wrte == readerPointer->offset.mark){
			readerPointer->flags &= ~READER_BIT;
		}
	}
	return MOLD_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	if(readerPointer->offset.mark <0) return MOLD_FALSE;
	else if(readerPointer->offset.mark > readerPointer->offset.wrte) readerPointer->offset.wrte =0;
	else readerPointer->offset.wrte = readerPointer->offset.mark;
	return MOLD_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return READER_TERMINATOR;
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	if(readerPointer->offset.read == readerPointer->offset.wrte){
		readerPointer->flags != READER_BIT;
		return READER_TERMINATOR;
	}
	
	/* TO_DO: Reset EOB flag */
	readerPointer->flags &= ~READER_BIT;

	return readerPointer->content[readerPointer->offset.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_string readerGetContent(ReaderPointer const readerPointer, mold_intg pos) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return content (string) */
	if(pos >= readerPointer->offset.wrte) return NULL;
	return &readerPointer->content[pos];
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return read */

	return readerPointer->offset.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return wrte */
	return readerPointer->offset.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return mark */
	return readerPointer->offset.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_void readerPrintStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Print the histogram */
	return readerPointer->histogram;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mold_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(readerPointer == NULL) return MOLD_FALSE;
	/* TO_DO: Returns the number of errors */
	readerPointer->histogram[readerPointer->numReaderErrors]++;
	return readerPointer->numReaderErrors;
}
