#include "symbolTable.h"
#include "utilities.h"

SymbolTable *_stack = NULL;

/* Function: recall
 * Parameters: char *identifier
 * Description: Recalls a symbol from the symbol table.
 * Returns: A pointer to the symbol if found, NULL otherwise.
 * Preconditions: The stack must not be empty.
 */
Symbol *recall(char *identifier) {
	if (!_stack)
		ERROR("Recall called on empty stack.", __LINE__, FALSE);

	Symbol *currSymbol = NULL;
	SymbolTable *currTable = NULL;
	
	for(currTable = _stack; currTable; currTable = currTable->below)
		for(currSymbol = currTable->listHead; currSymbol; 
				currSymbol = currSymbol->next)
			if (strcmp(currSymbol->identifier, identifier) == 0)
				return currSymbol;
	
	return NULL;
}

/* Function: recallLocal
 * Parameters: char *identifier
 * Description: Recalls a symbol from the symbol table on top of the stack.
 * Returns: A pointer to the symbol if found, NULL otherwise.
 * Preconditions: The stack must not be empty.
 */
Symbol *recallLocal(char *identifier) {
	if (!_stack)
		ERROR("RecallLocal called on empty stack.", __LINE__, FALSE);

	Symbol *currSymbol = NULL;
	
	for(currSymbol = _stack->listHead; currSymbol; currSymbol = currSymbol->next)
		if (currSymbol->identifier)
			if (strcmp(currSymbol->identifier, identifier) == 0)
				return currSymbol;

	return NULL;
}

/* Function: recallGlobal
 * Parameters: char *identifier
 * Description: Recalls a symbol from the global symbol table.
 * Returns: A pointer to the symbol if found, NULL otherwise.
 * Preconditions: The stack must not be empty.
 */
Symbol *recallGlobal(char *identifier) {
	if (!_stack)
		ERROR("RecallGlobal called on empty stack.", __LINE__, FALSE);

	Symbol *currSymbol = NULL;
	SymbolTable *currTable = _stack;
	
	while(currTable->below)
		currTable = currTable->below;
	
	for(currSymbol = currTable->listHead; currSymbol; currSymbol = currSymbol->next)
		if (strcmp(currSymbol->identifier, identifier) == 0)
			return currSymbol;

	return NULL;
}

/* Function: insert
 * Parameters: char *identifier, Type type
 * Description: Inserts a symbol into the symbol table.
 * Returns: A pointer to the inserted symbol.
 * Preconditions: The stack must not be empty.
 */
Symbol *insert(char *identifier, Type type) {
	if (!_stack)
		ERROR("Insert called on emtpy stack.", __LINE__, FALSE);

	Symbol *toInsert = NULL;
	
	if (!(toInsert = malloc(sizeof(Symbol))))
		ERROR("", __LINE__, TRUE); 					// out of memory
		
	if (identifier) {
		if (!(toInsert->identifier = strdup(identifier)))
			ERROR("", __LINE__, TRUE); 				// out of memory
	} else {
		toInsert->identifier = NULL;
	}
		
	toInsert->type = type;
	toInsert->value.intVal = 0;
	toInsert->location = NULL;
	toInsert->functionType = UNKNOWN;
	toInsert->parameterListHead = NULL;
	toInsert->reference = FALSE;
	
	toInsert->next = _stack->listHead;
	_stack->listHead = toInsert;
	
	return toInsert;
}

/* Function: insertGlobal
 * Parameters: char *identifier, Type type
 * Description: Inserts a symbol into the global symbol table.
 * Returns: A pointer to the inserted symbol.
 * Preconditions: The stack must not be empty.
 */
Symbol *insertGlobal(char *identifier, Type type) {
	if (!_stack)
		ERROR("Insert called on emtpy stack.", __LINE__, FALSE);

	Symbol *toInsert = NULL;
	SymbolTable *currTable = _stack;
	
	while(currTable->below)
		currTable = currTable->below;
	
	if (!(toInsert = malloc(sizeof(Symbol))))
		ERROR("", __LINE__, TRUE); 					// out of memory
		
	if (identifier) {
		if (!(toInsert->identifier = strdup(identifier)))
			ERROR("", __LINE__, TRUE); 				// out of memory	
	} else {
		toInsert->identifier = NULL;
	}
		
	toInsert->type = type;
	toInsert->value.intVal = 0;
	toInsert->location = NULL;
	toInsert->functionType = F_UNKNOWN;
	toInsert->parameterListHead = NULL;
	toInsert->reference = FALSE;
	
	toInsert->next = currTable->listHead;
	currTable->listHead = toInsert;
	
	return toInsert;
}

/* Function: addParameter
 * Parameters: char *identifier, Type type, Symbol *currentFunction
 * Description: Adds a parameter to the given function then inserts it into the
 *					 local symbol table.
 * Returns: The parameter that was inserted if not void. If void returns NULL.
 * Preconditions: none
 */
Symbol *addParameter(char *identifier, Type type, Symbol *currentFunction) {
	Parameter *newParameter = NULL, *currParameter = NULL;
	
	if (!(newParameter = malloc(sizeof(Parameter))))
		ERROR("", __LINE__, TRUE);				// out of memory
	
	newParameter->type = type;
	newParameter->next = NULL;
	
	// if the parameter list is null add at head, if not add at end
	if (!(currentFunction->parameterListHead)) {
		currentFunction->parameterListHead = newParameter;
	} else {
		currParameter = currentFunction->parameterListHead;
		
		while(currParameter->next)
			currParameter = currParameter->next;
			
		currParameter->next = newParameter;
	}
	
	if (type != VOID_TYPE)
		return insert(identifier, type);
	return NULL;
}

<<<<<<< src/aux/symbolTable.c
/* Function: push_symbolTable_toStack
=======
/* Function: pushSymbolTable
>>>>>>> src/aux/symbolTable.c.master
 * Parameters: void
 * Description: Pushes a new symbol table onto the stack.
 * Returns: void
 * Preconditions: none
 */
<<<<<<< src/aux/symbolTable.c
void push_symbolTable_toStack() {
=======
void pushSymbolTable() {
>>>>>>> src/aux/symbolTable.c.master
	SymbolTable *newTable = NULL;
	
	if (!(newTable = malloc(sizeof(SymbolTable))))
		ERROR("", __LINE__, TRUE);				// out of memory
	
	newTable->listHead = NULL;
	newTable->below = _stack;
	_stack = newTable;
}

/* Function: freeParameterList
 * Parameters: Parameter *parameterListHead
 * Description: Destroys the parameter list.
 * Returns: void
 * Preconditions: none
 */
void freeParameterList(Parameter *parameterListHead) {
	if (!parameterListHead)
		return;
	
	Parameter *rear = NULL, *front = NULL;
	
	for(rear = parameterListHead, front = rear->next;
			front; front = front->next) {
		free(rear);
		rear = front;
	}
	free(rear);
	
	parameterListHead = NULL;
}

<<<<<<< src/aux/symbolTable.c
/* Function: pop_symbolTable_fromStack
=======
/* Function: popSymbolTable
>>>>>>> src/aux/symbolTable.c.master
 * Parameters: void
 * Description: Pops the symbol table on the top of the stack.
 * Returns: void
 * Preconditions: The stack must not be empty.
 */
<<<<<<< src/aux/symbolTable.c
void pop_symbolTable_fromStack() {
=======
void popSymbolTable() {
>>>>>>> src/aux/symbolTable.c.master
	if (!_stack)
		ERROR("Pop called on empty stack.", __LINE__, FALSE);
	
	Symbol *rear = NULL, *front = NULL;
	Parameter *rearp = NULL, *frontp = NULL;
	SymbolTable *newStackTop = _stack->below;
	
<<<<<<< src/aux/symbolTable.c
	// if the symbol table has symbols at the top, free them first
=======
	// if the symbol table at the top has symbols, free them first
>>>>>>> src/aux/symbolTable.c.master
	if (_stack->listHead) {
		for(rear = _stack->listHead, front = rear->next; front; front = front->next) {
			free(rear->identifier);
			free(rear->location);
			freeParameterList(rear->parameterListHead);
			free(rear);
			rear = front;
		}
		free(rear->identifier);
		free(rear->location);
		freeParameterList(rear->parameterListHead);
		free(rear);
	}
	
	free(_stack);
	_stack = newStackTop;
}

/* Function: printSymbolTable
 * Parameters: none
 * Description: Prints the symbol table to the screen.
 * Returns: none
 * Preconditions: The stack must not be empty.
 */
void printSymbolTable() {
	if (!_stack)
		ERROR("PrintSymbolTable called on empty stack.", __LINE__, FALSE);

	Symbol *currSymbol = NULL;
	SymbolTable *currTable = NULL;
	
<<<<<<< src/aux/symbolTable.c
	printf("|| SYMBOL TABLE || \n");
=======
>>>>>>> src/aux/symbolTable.c.master
	for(currTable = _stack; currTable; currTable = currTable->below) {
		if (currTable->below)
			printf("LOCAL SCOPE:\n");
		else
			printf("GLOBAL SCOPE:\n");
		for(currSymbol = currTable->listHead; currSymbol; 
				currSymbol = currSymbol->next) {
			printf("\tSymbol: %s\n", currSymbol->identifier);
			printf("\tType: %s\n", typeAsString(currSymbol->type));
			
			switch (currSymbol->type) {
				case CHAR_TYPE:
					printf("\tValue: %c\n", currSymbol->value.charVal);
					break;
				case INT_TYPE:
					printf("\tValue: %d\n", currSymbol->value.intVal);
					break;
<<<<<<< src/aux/symbolTable.c
				case FLOAT_TYPE:
					printf("\tValue: %.2f\n", currSymbol->value.floatVal);
					break;
=======
>>>>>>> src/aux/symbolTable.c.master
				default:
					break;
			}
			
			printf("\tFunctionType: %s\n", functionTypeAsString(currSymbol->functionType));
			printf("\tParameters: ");
			printParamList(currSymbol->parameterListHead);
			printf("\n\n");
		}
	}
}

/* Function: typeAsString
 * Parameters: Type type
 * Description: Converts the enum Type to a string.
 * Returns: Returns the given type as a string.
 * Preconditions: none
 */
char *typeAsString(Type type) {
	if (type == CHAR_TYPE)
		return "CHAR";
	if (type == INT_TYPE)
		return "INT";
<<<<<<< src/aux/symbolTable.c
	if (type == FLOAT_TYPE)
		return "FLOAT";
=======
>>>>>>> src/aux/symbolTable.c.master
	if (type == CHAR_ARRAY)
		return "CHAR_ARRAY";
	if (type == INT_ARRAY)
		return "INT_ARRAY";
<<<<<<< src/aux/symbolTable.c
	if (type == FLOAT_ARRAY)
		return "FLOAT_ARRAY";
=======
>>>>>>> src/aux/symbolTable.c.master
	if (type == VOID_TYPE)
		return "VOID";
	if (type == BOOLEAN)
		return "BOOLEAN";
	if (type == UNKNOWN)
		return "UNKNOWN";
	
	return "MISSING/UNRECOGNIZED";
}

/* Function: functionTypeAsString
 * Parameters: FunctionType functionType
 * Description: Converts the enum FunctionType to a string.
 * Returns: Returns the given functionType as a string.
 * Preconditions: none
 */
char *functionTypeAsString(FunctionType functionType) {
	if (functionType == EXTERN_TYPE)
		return "EXTERN";
	if (functionType == PROTOTYPE)
		return "PROTOTYPE";
	if (functionType == DEFINITION)
		return "DEFINITION";
	if (functionType == NON_FUNCTION)
		return "NON_FUNCTION";
	if (functionType == F_UNKNOWN)
		return "UNKNOWN";
	
	return "MISSING/UNRECOGNIZED";
}

/* Function: printParamList
 * Parameters: Parameter *parameterListHead
 * Description: Prints the given parameter list to the screen.
 * Returns: none
 * Preconditions: none
 */
void printParamList(Parameter *parameterListHead) {
	if (!parameterListHead) {
		printf("NONE");
		return;
	}
	
	Parameter *currParam = NULL;
	
	printf("%s", typeAsString(parameterListHead->type));
	
	for(currParam = parameterListHead->next; currParam; currParam = currParam->next) {
		printf("->%s", typeAsString(currParam->type));
	}
}
	