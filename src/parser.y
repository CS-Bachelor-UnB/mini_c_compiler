%{
#include "utilities.h"
#include "symbolTable.h"
#include "syntaxTree.h"
#include "functionCall.h"

#define DEBUG_SYNTAX
#define DEBUG_SYMBOLS

typedef struct TempVariable {
    Symbol *symbol;
    struct TempVariable *next;
} TempVariable;

typedef struct StringLiteral {
    Symbol 	*symbol;
    struct StringLiteral *next;
} StringLiteral;

/************************
 *						*
 * 		prototypes		*
 *						*
 ************************/

void 	typeError(char *errorMessage),
        generateNewTempID(),
        generateNewLabelID(),
        declareGlobalVariables(SyntaxTree *tree),
        insertStringLiteral(Symbol *stringLiteral),
        popStringLiterals(StringLiteral *stringLiteral),
        insertTempVariable(Symbol *tempVariable),
        popTempVariables(TempVariable *tempVariable);
char	isStringLiteral(Symbol *target);
int		allocateStackSpace(SyntaxTree *declaration, int offset);
Symbol	*recallStringLiteral(char *string);

/************************
 *						*
 *	global variables	*
 *						*
 ************************/

extern int yylineno;
extern char *yytext;
extern FunctionCall	*_callStack;
char	*_currID = NULL,
        *_currFID = NULL,
        _returnedValue = FALSE,
        _parsing_success = TRUE,
        _errorMessage[255],
        _tempID[15],				// up to 10 billion temps > unsigned int max
        _labelID[16];				// up to 10 billion labels > unsigned int max
unsigned int	_tempNum = 0,
                _labelNum = 0,
                _offset = 0,
                _stackSize = 0;
Type	_currType = UNKNOWN,
        _currPType = UNKNOWN;
FunctionType _currFType = F_UNKNOWN;
Parameter *_currParam = NULL;
StringLiteral *_stringLiterals = NULL;
TempVariable *_tempVariables = NULL;
%}

%union {
    char character;
    int integer;
    float real;
    char *string;
    SyntaxTree *tree;
    struct exprReturn {
        Type type;
        SyntaxTree *tree;
    } exprReturn;
}

%start program

%token ID INTCON FLOATCON CHARCON STRCON CHAR INT FLOAT LIST VOID IF ELSE WHILE	FOR	RETURN EXTERN
            UMINUS DBLEQ NOTEQ LTEQ GTEQ LOGICAND LOGICOR OTHER

%type	<character>		CHARCON
%type	<integer>		INTCON
%type	<real>			FLOATCON
%type 	<string>		ID storeID STRCON
%type 	<tree>			assignment statement statementOpt paramTypes arrayTypeOpt
                        args varDcl multiVarDcl multiParam multiExprOpt
                        multiTypeDcl assgOpt
%type	<exprReturn>	expr multiFuncOpt exprOpt

%left LOGICOR
%left LOGICAND
%left DBLEQ NOTEQ
%left '<' LTEQ '>' GTEQ
%left '+' '-'
%left '*' '/'
%right '!' UMINUS

%%

program:	  program declaration ';'
            | program function

            /* error productions */
            | program declaration error { yyerrok; } /* missing semicolon */
            | error ';' { yyerrok; }

            | /* empty */
            ;

declaration:  type varDcl multiVarDcl
            {
              SyntaxTree *declarations = createTree(DECLARATION, NULL, $2, $3);
              declareGlobalVariables(declarations);
              printf("\n");
              destroyTree(declarations);
            }
            | storeExtern type storeFID '(' insertFunc paramTypes ')' multiProtDcl makeProt { _currFType = F_UNKNOWN; }
            | type storeFID '(' insertFunc paramTypes ')' multiProtDcl makeProt { _currFType = F_UNKNOWN; }
            | storeExtern storeVoid storeFID '(' insertFunc paramTypes ')'
                multiProtDcl makeProt { _currFType = F_UNKNOWN; }
            | storeVoid storeFID '(' insertFunc paramTypes ')' multiProtDcl makeProt { _currFType = F_UNKNOWN; }
            ;

storeFID:	  ID
            {
              _currFID = $1;
            };

storeID:	  ID
            {
              _currID = $1;
              $$ = $1;
            };

storeExtern:  EXTERN
            {
              _currFType = EXTERN_TYPE;
            };

storeVoid:	  VOID
            {
              _currType = VOID_TYPE;
            };

makeProt:	{
              Symbol *prevDcl = recallGlobal(_currFID);

              if (prevDcl->functionType == PROTOTYPE || prevDcl->functionType == EXTERN_TYPE) {
                  sprintf(_errorMessage, "prototype %s previously declared",
                      _currFID);
                  typeError(_errorMessage);
              } else {
                  if (_currFType == EXTERN_TYPE)
                      prevDcl->functionType = EXTERN_TYPE;
                  else
                      prevDcl->functionType = PROTOTYPE;
              }

              pop_symbolTable_fromStack();
            }
            ;

multiProtDcl: multiProtDcl ',' makeProt storeFID '(' insertFunc paramTypes ')'
            | /* empty */
            ;

multiVarDcl:  multiVarDcl ',' varDcl { $3->left = $1; $$ = $3; }
            | /* empty */ { $$ = NULL; }
            ;

varDcl:	  	  ID
            {
              _currID = $1;

              if (recallLocal(_currID)) {
                  sprintf(_errorMessage, "%s previously declared in this function", _currID);
                  typeError(_errorMessage);
                  $$ = NULL;
              } else {
                    Symbol *currSymbol = insert(_currID, _currType);
                  currSymbol->functionType = NON_FUNCTION;
                  $$ = createTree(DECLARATION, currSymbol, NULL, NULL);
              }
            }
            | ID '[' INTCON ']'
            {
                _currID = $1;

                if (_currType == CHAR_TYPE)
                    _currType = CHAR_ARRAY;
                else if (_currType == INT_TYPE)
                    _currType = INT_ARRAY;
                else if (_currType == FLOAT_TYPE)
                    _currType = FLOAT_ARRAY;



                if (recallLocal(_currID)) {
                    sprintf(_errorMessage, "%s previously declared in this function", _currID);
                    typeError(_errorMessage);
                    $$ = NULL;
                } else {
                    Symbol *currSymbol = insert(_currID, _currType);
                    currSymbol->functionType = NON_FUNCTION;
                    currSymbol->value.intVal = $3;
                    $$ = createTree(DECLARATION, currSymbol, NULL, NULL);
                }

                if (_currType == CHAR_ARRAY)
                    _currType = CHAR_TYPE;
                else if (_currType == INT_ARRAY)
                    _currType = INT_TYPE;
                else if (_currType == FLOAT_ARRAY)
                    _currType = FLOAT_TYPE;
            }
            ;

type:		CHAR
            {
                _currType = CHAR_TYPE;
            }
            | INT
            {
                _currType = INT_TYPE;
            }
            | FLOAT
            {
                _currType = FLOAT_TYPE;
            }
            ;

initParam: {
  Symbol *currSymbol = recallGlobal(_currFID);
  if (currSymbol)
    _currParam = currSymbol->parameterListHead;};
paramTypes:   initParam VOID
            {
              Symbol *currentFunction = recallGlobal(_currFID);

            if (_currParam) {
                   if (_currParam->type != VOID_TYPE)
                        typeError("Type mismatch: non-VOID parameter(s) expected");
              } else {
                  addParameter(NULL, VOID_TYPE, currentFunction);
              }

              _currParam = NULL;

              $$ = NULL;
            }
            | initParam arrayTypeOpt multiParam
            {
              if (_currParam)
                  typeError("Type mismatch: missing previously declared types");

              _currParam = NULL;


              SyntaxTree *tree = $3;

              if (tree) {
                  while (tree->left)
                      tree = tree->left;

                    tree->left = $2;
                  $$ = $3;
              } else {
                  $$ = $2;
              }

            };

storePType:	CHAR
            {
                _currPType = CHAR_TYPE;
            }
            | INT
            {
                _currPType = INT_TYPE;
            }
            | FLOAT
            {
                _currPType = FLOAT_TYPE;
            }
            ;

arrayTypeOpt: storePType ID
            {
              _currID = $2;

              Symbol *currentFunction = recallGlobal(_currFID);

                if (recallLocal(_currID)) {
                  sprintf(_errorMessage, "%s previously declared in this function",
                      _currID);
                  typeError(_errorMessage);
                  $$ = NULL;
                } else {
                        if (_currParam) {
                          if (_currParam->type != _currPType) {
                            sprintf(_errorMessage, "%s does not match previous declaration",
                                typeAsString(_currPType));
                            typeError(_errorMessage);
                            $$ = NULL;
                        } else {
                            Symbol *currSymbol = insert(_currID, _currPType);
                            currSymbol->functionType = NON_FUNCTION;
                            $$ = createTree(FORMAL, currSymbol, NULL, NULL);
                        }
                       } else {
                          Symbol *currSymbol = addParameter(_currID, _currPType, currentFunction);
                        currSymbol->functionType = NON_FUNCTION;
                        $$ = createTree(FORMAL, currSymbol, NULL, NULL);
                      }
                }

              if (_currParam)
                    _currParam = _currParam->next;
            }
            | storePType ID '['']'
            {
              _currID = $2;
              Symbol *currentFunction = recallGlobal(_currFID);

              if (_currPType == CHAR_TYPE)
                  _currPType = CHAR_ARRAY;
              else
                  _currPType = INT_ARRAY;

              if (recallLocal(_currID)) {
                  sprintf(_errorMessage, "%s previously declared in this function",
                      _currID);
                  typeError(_errorMessage);
                  $$ = NULL;
              } else {
                    if (_currParam) {
                      if (_currParam->type != _currPType) {
                          if (_currPType == CHAR_ARRAY)
                              typeError("CHAR_ARRAY does not match previous declaration");
                          else
                              typeError("INT_ARRAY does not match previous declaration");

                          $$ = NULL;
                      } else {
                          Symbol *currSymbol = insert(_currID, _currPType);
                          currSymbol->functionType = NON_FUNCTION;
                          $$ = createTree(FORMAL, currSymbol, NULL, NULL);
                      }
                    } else {
                        Symbol *currSymbol = addParameter(_currID, _currPType, currentFunction);
                      currSymbol->functionType = NON_FUNCTION;
                      $$ = createTree(FORMAL, currSymbol, NULL, NULL);
                    }
              }

             if (_currParam)
               _currParam = _currParam->next;
            }
            ;

multiParam:   multiParam ',' arrayTypeOpt { $3->left = $1; $$ = $3; }
            | /* empty */ { $$ = NULL; }
            ;

insertFunc:	{
              Symbol *prevDcl = recallGlobal(_currFID);

              if (prevDcl) {
                  if (prevDcl->functionType == DEFINITION) {
                      sprintf(_errorMessage, "function %s previously defined", prevDcl->identifier);
                    typeError(_errorMessage);
                  } else if (prevDcl->functionType == EXTERN_TYPE) {
                        sprintf(_errorMessage, "function %s previously declared as extern", prevDcl->identifier);
                        typeError(_errorMessage);
                  } else if (prevDcl->functionType == NON_FUNCTION) {
                        sprintf(_errorMessage, "function %s previously declared",prevDcl->identifier);
                        typeError(_errorMessage);
                  } else if (prevDcl->type != _currType) {
                        sprintf(_errorMessage, "return type of function %s doesn't match previous declaration", prevDcl->identifier);
                        typeError(_errorMessage);
                  }
              } else {
                    Symbol *currFunction = insert(_currFID, _currType);
                      currFunction->functionType = DEFINITION;
              }

              push_symbolTable_toStack();
            }
            ;

function:	  type storeFID '(' insertFunc paramTypes ')' '{' multiTypeDcl
                    statementOpt '}'
            {
              if (!_returnedValue) {
                  sprintf(_errorMessage, "function %s must have at least one return statement",
                      _currFID);
                  typeError(_errorMessage);
              } else {
                  _returnedValue = FALSE;
              }

              Symbol *currFunction = recallGlobal(_currFID);

              SyntaxTree *declarations = $8;

              if (declarations) {
                  while (declarations->left)
                      declarations = declarations->left;

                  declarations->left = $5;
              } else {
                  $8 = $5;
              }

              SyntaxTree *function = createTree(FUNCTION_ROOT, currFunction, $8, $9);

              #if defined(DEBUG_SYNTAX) || defined(DEBUG_ALL)
                    printf("\nSYNTAX TREE=\n\n");
                    printSyntaxTree(function, 0);
              #endif

              #if defined(DEBUG_SYMBOLS) || defined(DEBUG_ALL)
                    printSymbolTable();
              #endif


              SyntaxTree *parameter = $5;
              SyntaxTree *parameterName = $5;
              int i, j, k, l;
              i = j = k = l = 0;
              for(i = 12, j = 0; parameter; i += 4, j += 4) {

                    // this 'if' is just to get the parameter names in order
                    l = 0;
                    parameterName = $5;
                    if (k == 0 && parameterName == parameter) {
                        while (parameterName->left) {
                            parameterName = parameterName->left;
                            k++;
                        }
                        k--;
                    } else {
                        while (l < k) {
                            parameterName = parameterName->left;
                            l++;
                        }
                        k--;
                    }

                    if (parameter->symbol->type == (CHAR_ARRAY || parameter->symbol->type == INT_ARRAY))
                        parameter->symbol->reference = TRUE;

                    parameter = parameter->left;
              }

              destroyTree(function);
              pop_symbolTable_fromStack();
            }
            | storeVoid storeFID '(' insertFunc paramTypes ')' '{' multiTypeDcl
                  statementOpt '}'
            {
              Symbol *currFunction = recallGlobal(_currFID);

              SyntaxTree *declarations = $8;

              if (declarations) {
                  while (declarations->left)
                      declarations = declarations->left;

                  declarations->left = $5;
              } else {
                  $8 = $5;
              }

              SyntaxTree *function = createTree(FUNCTION_ROOT, currFunction, $8, $9);

              #if defined(DEBUG_SYNTAX) || defined(DEBUG_ALL)
                    printf("\n|| SYNTAX TREE ||\n\n");
                    printSyntaxTree(function, 0);
              #endif

              #if defined(DEBUG_SYMBOLS) || defined(DEBUG_ALL)
                    printSymbolTable();
              #endif

              _stackSize = 8;
              _stackSize += allocateStackSpace(function, 0);

              SyntaxTree *parameter = $5;
              SyntaxTree *parameterName = $5;
              int i, j, k, l;
              i = j = k = l = 0;
              for(i = 12, j = 0; parameter; i += 4, j += 4) {

                    // this 'if' is just to get the parameter names in order
                    l = 0;
                    parameterName = $5;
                    if (k == 0 && parameterName == parameter) {
                        while (parameterName->left) {
                            parameterName = parameterName->left;
                            k++;
                        }
                        k--;
                    } else {
                        while (l < k) {
                            parameterName = parameterName->left;
                            l++;
                        }
                        k--;
                    }

                    if (parameter->symbol->type == (CHAR_ARRAY || parameter->symbol->type == INT_ARRAY))
                        parameter->symbol->reference = TRUE;

                    parameter = parameter->left;
              }

              destroyTree(function);
              pop_symbolTable_fromStack();
            }
            ;

multiTypeDcl: multiTypeDcl type varDcl multiVarDcl ';'
            {
                SyntaxTree *tree = $4;

                if (tree) {

                    while (tree->left)
                        tree = tree->left;

                    tree->left = $3;
                    $3->left = $1;
                    $$ = $4;
                } else {
                    $3->left = $1;
                    $$ = $3;
                }
            }

            /* error productions */
            | multiTypeDcl type error ';' { yyerrok; $$ = NULL; }

            | /* empty */ { $$ = NULL; }
            ;

statement:	  IF '(' expr ')' statement
            {
              if ($3.type != BOOLEAN)
                  typeError("conditional in if statement must be a boolean");

              $$ = createTree(IF_TREE, NULL, $3.tree, $5);
            }
            | IF '(' expr ')' statement ELSE statement
            {
              if ($3.type != BOOLEAN)
                  typeError("conditional in if statement must be a boolean");

                $$ = createTree(IF_TREE, NULL, $3.tree, $5);
                $$->opt = $7;
            }
            | WHILE '(' expr ')' statement
            {
              if ($3.type != BOOLEAN)
                  typeError("conditional in while loop must be a boolean");

              $$ = createTree(WHILE_TREE, NULL, $3.tree, $5);
            }
            | FOR '(' assgOpt ';' exprOpt ';' assgOpt ')' statement
            {
              if ($5.type != BOOLEAN)
                  typeError("conditional in for loop must be a boolean");

            SyntaxTree *tree = createTree(WHILE_TREE, NULL, $5.tree, $9);
            tree->opt = $7;
            $$ = createTree(STATEMENT, NULL, tree, $3);
            }
            | RETURN expr ';'
            {
              Symbol *currSymbol = recallGlobal(_currFID);

              if (!currSymbol) {
                  typeError("unexpected return statement");
                  $$ = NULL;
              } else {
                  if (currSymbol->type != $2.type) {
                      if (((currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE && currSymbol->type != FLOAT_TYPE)
                        || ($2.type != INT_TYPE && $2.type != CHAR_TYPE && $2.type != FLOAT_TYPE))) {
                              sprintf(_errorMessage, "return type for function %s does not match declared type", _currFID);
                          typeError(_errorMessage);
                      } else {
                        _returnedValue = TRUE;
                      }
                    } else {
                      _returnedValue = TRUE;
                  }

                  $$ = createTree(RETURN_TREE, currSymbol, $2.tree, NULL);
              }
            }
            | RETURN ';'
            {
              Symbol *currSymbol = recallGlobal(_currFID);

              if (!currSymbol) {
                  typeError("unexpected return statement");
                  $$ = NULL;
              } else {
                  if (currSymbol->type != VOID_TYPE) {
                      sprintf(_errorMessage, "return type for function %s does not match declared type",
                          _currFID);
                      typeError(_errorMessage);
                  }

                  $$ = createTree(RETURN_TREE, currSymbol, NULL, NULL);
              }


            }
            | assignment ';' { $$ = $1; }
            | storeID '('')' ';'
            {
              Symbol *currSymbol = recallGlobal(_currID);

              if (currSymbol) {
                  if (!currSymbol->parameterListHead) {
                      sprintf(_errorMessage, "%s is not a function", _currID);
                      typeError(_errorMessage);
                  }

                  else if (currSymbol->parameterListHead->type != VOID_TYPE) {
                      sprintf(_errorMessage, "function %s takes non-VOID arguments",
                          _currID);
                         typeError(_errorMessage);
                  }

                  if (currSymbol->type != VOID_TYPE) {
                      sprintf(_errorMessage, "function %s must return VOID to be used as a statement",
                          _currID);
                      typeError(_errorMessage);
                  }

                  $$ = createTree(FUNCTION_CALL, currSymbol, NULL, NULL);
              } else {
                  sprintf(_errorMessage, "%s undefined", _currID);
                  typeError(_errorMessage);
                  $$ = NULL;
              }

            }
            | storeID '('
            {
              Symbol *currSymbol = recallGlobal(_currID);

              if (!currSymbol) {
                      sprintf(_errorMessage, "%s undefined", _currID);
                    typeError(_errorMessage);
              } else {
                  if (currSymbol->functionType == NON_FUNCTION) {
                      sprintf(_errorMessage, "%s is not a function", _currID);
                      typeError(_errorMessage);
                  } else {
                      if (currSymbol->type != VOID_TYPE) {
                          sprintf(_errorMessage, "function %s must return VOID to be used as a statement",
                              _currID);
                          typeError(_errorMessage);
                      }
                      pushFunctionCall(currSymbol);
                  }
              }
            }
              args multiExprOpt ')' ';'
            {
              if (_callStack) {
                    if (_callStack->currParam) {
                        sprintf(_errorMessage, "more arguments expected for function %s",
                            _callStack->identifier);
                        typeError(_errorMessage);
                    }

                  SyntaxTree *tree = $5;

                  if (tree) {
                      while (tree->left)
                          tree = tree->left;

                        tree->left = $4;
                      $$ = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), $5, NULL);
                  } else {
                      $$ = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), $4, NULL);
                  }

                    popFunctionCall();
              }
            }
            | '{' statementOpt '}' { $$ = $2; }
            | ';' { $$ = NULL; }

            /* error productions */
            | error ';' { yyerrok; }
            ;
statementOpt: statementOpt statement
            {
              if ($2) {
                    $$ = createTree(STATEMENT, NULL, $2, $1);
              }
            }
            | /* empty */ { $$ = NULL; }
            ;

exprOpt:	  expr { $$.type = $1.type; $$.tree = $1.tree; }
            | /* empty */ { $$.type = BOOLEAN; $$.tree = NULL; }
            ;

assignment:	  storeID '=' expr
            {
              _currID = $1;
              Symbol *currSymbol = recall(_currID);

              if (!currSymbol) {
                  sprintf(_errorMessage, "%s undefined", _currID);
                  typeError(_errorMessage);
                } else {
                  if ((currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE && currSymbol->type != FLOAT_TYPE)
                        || currSymbol->functionType != NON_FUNCTION) {
                    sprintf(_errorMessage, "%s has incompatible type for assignment",
                        _currID);
                    typeError(_errorMessage);
                }
                  if (currSymbol->type != $3.type) {
                      if ((currSymbol->type != INT_TYPE && currSymbol->type != CHAR_TYPE && currSymbol->type != FLOAT_TYPE)
                          && ($3.type != INT_TYPE && $3.type != CHAR_TYPE && $3.type != FLOAT_TYPE)) {
                        sprintf(_errorMessage, "incompatible types for assignment of %s",
                            _currID);
                        typeError(_errorMessage);
                      }
                  }
              }

              SyntaxTree *leftHandSide = createTree(SYMBOL, currSymbol, NULL, NULL);
              $$ = createTree(ASSIGNMENT, NULL, leftHandSide, $3.tree);
            }
            | storeID '[' expr ']' '=' expr
            {
              _currID = $1;
              Symbol *currSymbol = recall(_currID);

              if (!currSymbol) {
                  sprintf(_errorMessage, "%s undefined", _currID);
                  typeError(_errorMessage);
                } else {
                  if (currSymbol->type != (INT_ARRAY && currSymbol->type != CHAR_ARRAY)) {
                      sprintf(_errorMessage, "%s must be an ARRAY to be indexed", _currID);
                      typeError(_errorMessage);
                  }

                  if (($3.type != INT_TYPE && $3.type != CHAR_TYPE && $3.type != FLOAT_TYPE)) {
                      sprintf(_errorMessage, "ARRAY index for %s must be INT, CHAR or FLOAT",
                          _currID);
                      typeError(_errorMessage);
                  }

                  if (($6.type != INT_TYPE && $6.type != CHAR_TYPE && $6.type != FLOAT_TYPE))  {
                        sprintf(_errorMessage, "incompatible types for assignment of %s",
                            _currID);
                        typeError(_errorMessage);
                  }

                SyntaxTree *symbolTree = createTree(SYMBOL, currSymbol, NULL, NULL);
                generateNewTempID();
                Symbol *newSymbol = insert(_tempID, currSymbol->type);
                SyntaxTree *array = createTree(ARRAY, newSymbol, symbolTree, $3.tree);
                $$ = createTree(ASSIGNMENT, NULL, array, $6.tree);
              }
            }
            ;

assgOpt:	  assignment { $$ = $1; }
            | /* empty */ { $$ = NULL; }
            ;

expr:		  '-' expr %prec UMINUS
            {
                if (($2.type != INT_TYPE && $2.type != CHAR_TYPE && $2.type != FLOAT_TYPE))
                    typeError("incompatible expression for operator '-'");

                $$.type = $2.type;

                generateNewTempID();
                Symbol *newSymbol = insert(_tempID, INT_TYPE);
                $$.tree = createTree(NEG, newSymbol, $2.tree, NULL);
            }
            | '!' expr
            {
                if ($2.type != BOOLEAN)
                    typeError("incompatible expression for operator '!'");

                $$.type = $2.type;

                generateNewTempID();
                Symbol *newSymbol = insert(_tempID, BOOLEAN);
                $$.tree = createTree(NOT, newSymbol, $2.tree, NULL);
            }
            | expr '+' expr
            {
                if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                    typeError("incompatible expression for operator '+'");

                $$.type = $1.type;

                generateNewTempID();
                Symbol *newSymbol = insert(_tempID, INT_TYPE);
                $$.tree = createTree(ADD, newSymbol, $3.tree, $1.tree);
            }
            | expr '-' expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '-'");

              $$.type = $1.type;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, INT_TYPE);
              $$.tree = createTree(SUB, newSymbol, $3.tree, $1.tree);
            }
            | expr '*' expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '*'");

              $$.type = $1.type;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, INT_TYPE);
              $$.tree = createTree(MULT, newSymbol, $3.tree, $1.tree);
            }
            | expr '/' expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '/'");

              $$.type = $1.type;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, INT_TYPE);
              $$.tree = createTree(DIV, newSymbol, $3.tree, $1.tree);
            }
            | expr DBLEQ expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '=='");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(EQUAL, newSymbol, $3.tree, $1.tree);
            }
            | expr NOTEQ expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '!='");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(NOT_EQUAL, newSymbol, $3.tree, $1.tree);
            }
            | expr LTEQ expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '<='");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(LESS_EQUAL, newSymbol, $3.tree, $1.tree);
            }
            | expr '<' expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '<'");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(LESS_THAN, newSymbol, $3.tree, $1.tree);
            }
            | expr GTEQ expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '>='");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(GREATER_EQUAL, newSymbol, $3.tree, $1.tree);
            }
            | expr '>' expr
            {
              if (($1.type != INT_TYPE && $1.type != CHAR_TYPE)
                    || ($3.type != INT_TYPE && $3.type != CHAR_TYPE))
                  typeError("incompatible expression for operator '>'");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(GREATER_THAN, newSymbol, $3.tree, $1.tree);
            }
            | expr LOGICAND expr
            {
              if ($1.type != BOOLEAN || $3.type != BOOLEAN)
                  typeError("incompatible expression for operator '&&'");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(AND, newSymbol, $3.tree, $1.tree);
            }
            | expr LOGICOR expr
            {
              if ($1.type != BOOLEAN || $3.type != BOOLEAN)
                  typeError("incompatible expression for operator '||'");

              $$.type = BOOLEAN;

              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, BOOLEAN);
              $$.tree = createTree(OR, newSymbol, $3.tree, $1.tree);
            }
            | ID
            {
              _currID = $1;
              Symbol *currSymbol = recall(_currID);

              if (!currSymbol) {
                  sprintf(_errorMessage, "%s undefined", _currID);
                  typeError(_errorMessage);
              }

            }
            multiFuncOpt
            {
                $$.type = $3.type;
                $$.tree = $3.tree;
            }
            | '(' expr ')'	{ $$.type = $2.type; $$.tree = $2.tree; }
            | INTCON
            {
              $$.type = INT_TYPE;
              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, INT_TYPE);
              newSymbol->value.intVal = $1;
              newSymbol->functionType = NON_FUNCTION;
              $$.tree = createTree(LITERAL, newSymbol, NULL, NULL);
            }
            | FLOATCON
            {
              $$.type = FLOAT_TYPE;
              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, FLOAT_TYPE);
              newSymbol->value.intVal = $1;
              newSymbol->functionType = NON_FUNCTION;
              $$.tree = createTree(LITERAL, newSymbol, NULL, NULL);
            }
            | CHARCON
            {
              $$.type = CHAR_TYPE;
              generateNewTempID();
              Symbol *newSymbol = insert(_tempID, CHAR_TYPE);
              newSymbol->value.charVal = $1;
              newSymbol->functionType = NON_FUNCTION;
              $$.tree = createTree(LITERAL, newSymbol, NULL, NULL);
            }
            | STRCON
            {
              $$.type = CHAR_ARRAY;

              Symbol *currSymbol = recallStringLiteral($1);

              if (!currSymbol) {
                  generateNewTempID();
                  currSymbol = insertGlobal(_tempID, CHAR_ARRAY);
                  currSymbol->value.strVal = $1;
                  currSymbol->functionType = NON_FUNCTION;

                  if (!(currSymbol->location = malloc(strlen(currSymbol->identifier) + 2)))
                      ERROR(NULL, __LINE__, TRUE);				//out of memory


                  sprintf(currSymbol->location, "_%s", currSymbol->identifier);
                  insertStringLiteral(currSymbol);
              }

              $$.tree = createTree(LITERAL, currSymbol, NULL, NULL);
            }
            ;

multiFuncOpt: '('')'
            {
              Symbol *currSymbol = recallGlobal(_currID);

              if (currSymbol) {
                  if (!currSymbol->parameterListHead) {
                      sprintf(_errorMessage, "%s is not a function", _currID);
                      typeError(_errorMessage);
                  } else if (currSymbol->type == VOID_TYPE) {
                      sprintf(_errorMessage, "void function %s in expression", _currID);
                      typeError(_errorMessage);
                  }	else if (currSymbol->parameterListHead->type != VOID_TYPE) {
                      sprintf(_errorMessage, "function %s takes non-VOID arguments",
                          _currID);
                      typeError(_errorMessage);
                  }
                  $$.type = currSymbol->type;
                  generateNewTempID();
                  Symbol *newSymbol = insert(_tempID, currSymbol->type);
                  SyntaxTree *tree = createTree(FUNCTION_CALL, currSymbol, NULL, NULL);
                  $$.tree = createTree(RETRIEVE, newSymbol, tree, NULL);
              } else {
                  $$.type = UNKNOWN;
                  $$.tree = NULL;
              }
            }
            | '('
            {
              Symbol *currSymbol = recallGlobal(_currID);

              if (currSymbol) {
                  if (currSymbol->functionType == NON_FUNCTION) {
                      sprintf(_errorMessage, "%s is not a function", _currID);
                      typeError(_errorMessage);
                  } else if (currSymbol->type == VOID_TYPE) {
                        sprintf(_errorMessage, "void function %s in expression", _currID);
                      typeError(_errorMessage);
                  }
                  pushFunctionCall(currSymbol);
              }
            }
              args multiExprOpt ')'
            {
              if (_callStack) {
                    if (_callStack->currParam) {
                        sprintf(_errorMessage, "more arguments expected for function %s",
                            _callStack->identifier);
                        typeError(_errorMessage);
                    }
                    $$.type = (recallGlobal(_callStack->identifier))->type;

                  SyntaxTree *tree = $4;

                  if (tree) {
                      while (tree->left)
                          tree = tree->left;

                        tree->left = $3;

                      generateNewTempID();
                      Symbol *newSymbol = insert(_tempID, $$.type);
                      SyntaxTree *tree = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), $4, NULL);
                      $$.tree = createTree(RETRIEVE, newSymbol, tree, NULL);
                  } else {
                      generateNewTempID();
                      Symbol *newSymbol = insert(_tempID, $$.type);
                      SyntaxTree *tree = createTree(FUNCTION_CALL, recallGlobal(_callStack->identifier), $3, NULL);
                      $$.tree = createTree(RETRIEVE, newSymbol, tree, NULL);
                  }

                  popFunctionCall();
              } else {
                  $$.type = UNKNOWN;
                  $$.tree = NULL;
              }

            }
            | '['
            {
              Symbol *currSymbol = recall(_currID);

              if (currSymbol) {
                  if ((currSymbol->type != CHAR_ARRAY && currSymbol->type != INT_ARRAY && currSymbol->type != FLOAT_ARRAY)) {
                      sprintf(_errorMessage, "%s must be an ARRAY to be indexed",
                          _currID);
                      typeError(_errorMessage);
                  }

                  pushFunctionCall(currSymbol);
              }
            }
              expr ']'
            {
                if (($3.type != INT_TYPE && $3.type != CHAR_TYPE && $3.type != FLOAT_TYPE)) {
                    sprintf(_errorMessage, "array index for %s must be INT, CHAR or FLOAT", _currID);
                    typeError(_errorMessage);
              }

              if (!_callStack) {
                    $$.type = UNKNOWN;
                    $$.tree = NULL;
              } else {
                    $$.type = (recall(_callStack->identifier))->type;

                    generateNewTempID();
                    Symbol *newSymbol = insert(_tempID, $$.type);
                    SyntaxTree *tree = createTree(SYMBOL, recall(_callStack->identifier), NULL, NULL);
                    $$.tree = createTree(ARRAY, newSymbol, tree, $3.tree);

                    if ($$.type == CHAR_ARRAY)
                        $$.type = CHAR_TYPE;
                    else if ($$.type == INT_ARRAY)
                        $$.type = INT_TYPE;
                    else if ($$.type == FLOAT_ARRAY)
                        $$.type = FLOAT_TYPE;

                  popFunctionCall();
              }
            }
            | /* empty */
            {
              Symbol *currSymbol = recall(_currID);

              if (currSymbol) {
                  if (currSymbol->functionType != NON_FUNCTION) {
                      sprintf(_errorMessage, "expected arguments for function %s",
                          _currID);
                      typeError(_errorMessage);
                  }
                  $$.type = currSymbol->type;
                  $$.tree = createTree(SYMBOL, currSymbol, NULL, NULL);
              } else {
                  $$.type = UNKNOWN;
                  $$.tree = NULL;
              }
            }
            ;

args:		  expr
            {
                if (_callStack) {
                        if (!_callStack->currParam) {
                        sprintf(_errorMessage, "extra arguments passed to function %s",
                            _callStack->identifier);
                        typeError(_errorMessage);
                        $$ = NULL;
                    } else if (_callStack->currParam->type != $1.type) {
                        if (((_callStack->currParam->type != INT_TYPE && _callStack->currParam->type != CHAR_TYPE) || ($1.type != INT_TYPE && $1.type != CHAR_TYPE))) {
                            typeError("type mismatch in arguments to function");
                            $$ = NULL;
                        } else {
                            $$ = createTree(PARAMETER, NULL, NULL, $1.tree);
                        }
                    } else {
                        $$ = createTree(PARAMETER, NULL, NULL, $1.tree);
                    }
                } else {
                    $$ = NULL;
                }

                if (_callStack->currParam)
                    _callStack->currParam = _callStack->currParam->next;
            }
            ;

multiExprOpt: multiExprOpt ',' args { $3->left = $1; $$ = $3; }
            | /* empty */ { $$ = NULL; }
            ;

%%

/* Function: main
 * Parameters: none
 * Description: Program execution begins here.
 * Returns: 0 for success, 1 if errors were found (syntactic or semantic).
 * Preconditions: none
 */
int main() {
    push_symbolTable_toStack();				// initialize global symbol table

    yyparse();

    // popTempVariables(_tempVariables);
    // popStringLiterals(_stringLiterals);
    pop_symbolTable_fromStack();				// free global symbol table

    if (_parsing_success)
      return 0;					// success
    return 1;						// failure
}

/* Function: insertTempVariable
 * Parameters: Symbol *tempVariable
 * Description: Adds the given temp variable to the list of temp variables.
 * Returns: none
 * Preconditions: none
 */
void insertTempVariable(Symbol *tempVariable) {
    if (!tempVariable)
        return;

    TempVariable *newTemp = NULL;

    if (!(newTemp = malloc(sizeof(TempVariable))))
        ERROR(NULL, __LINE__, TRUE);					// out of memory

    newTemp->symbol = tempVariable;

    newTemp->next = _tempVariables;
    _tempVariables = newTemp;
}

/* Function: popTempVariables
 * Parameters: TempVariable *tempVariable
 * Description: Writes all global temps into mips global data and frees temp
 *					variables list.
 * Returns: none
 * Preconditions: none
 */
void popTempVariables(TempVariable *tempVariable) {
    if (!tempVariable)
        return;

    popTempVariables(tempVariable->next);
    free(tempVariable);
}

/* Function: insertStringLiteral
 * Parameters: Symbol *stringLiteral
 * Description: Adds the given string literal to the list of string literals.
 * Returns: none
 * Preconditions: none
 */
void insertStringLiteral(Symbol *stringLiteral) {
    if (!stringLiteral)
        return;

    StringLiteral *newStringLiteral = NULL;

    if (!(newStringLiteral = malloc(sizeof(StringLiteral))))
        ERROR(NULL, __LINE__, TRUE);						// out of memory

    newStringLiteral->symbol = stringLiteral;

    newStringLiteral->next = _stringLiterals;
    _stringLiterals = newStringLiteral;
}

/* Function: recallStringLiteral
 * Parameters: char *targetString
 * Description: Searches string literals list for target string. If found
 *					returns a reference to its symbol table entry.
 * Returns: A reference to the symbol table entry storing the specified string
 *				if found, NULL otherwise.
 * Preconditions: none
 */
Symbol	*recallStringLiteral(char *targetString) {
    if (!targetString)
        return NULL;

    StringLiteral *currString = _stringLiterals;

    while (currString) {
        if (strcmp(currString->symbol->value.strVal, targetString) == 0)
            return currString->symbol;

        currString = currString->next;
    }

    return NULL;
}

/* Function: popStringLiterals
 * Parameters: Symbol *stringLiteral
 * Description: Writes all global strings into mips global data and frees string
 *					literals list.
 * Returns: none
 * Preconditions: none
 */
void popStringLiterals(StringLiteral *stringLiteral) {
    if (!stringLiteral)
        return;

    popStringLiterals(stringLiteral->next);
    free(stringLiteral->symbol->value.strVal);
    free(stringLiteral);
}

/* Function: yyerror
 * Parameters: char *errorMessage
 * Description: Called when syntax errors are found. Prints error message and flags error.
 * Returns: void
 * Preconditions: none
 */
void yyerror(char* errorMessage) {
    fprintf(stderr, "SYNTAX ERROR: line %d: Near token (%s)\n", yylineno, yytext);
    _parsing_success = FALSE;
}

int yywrap() {
    return 1;
}

/* Function: declareGlobalVariables
 * Parameters: SyntaxTree *tree
 * Description: Converts global declarations to assembly code.
 * Returns: none
 * Preconditions: none
 */
void declareGlobalVariables(SyntaxTree *tree) {
    if (!tree)
        return;

    Symbol *currSymbol = tree->symbol;

    if (!currSymbol) {
        declareGlobalVariables(tree->left);
        declareGlobalVariables(tree->right);
        return;
    }

    if (!(currSymbol->location = malloc(strlen(currSymbol->identifier) + 2)))
        ERROR(NULL, __LINE__, TRUE);				//out of memory

    sprintf(currSymbol->location, "_%s", currSymbol->identifier);

    declareGlobalVariables(tree->left);
    declareGlobalVariables(tree->right);
}

/* Function: allocateStackSpace
 * Parameters: SyntaxTree *declaration, int offset
 * Description: Sets the stack offset for each declaration.
 * Returns: none
 * Preconditions: On the first call to this function the offset is 0.
 */
int allocateStackSpace(SyntaxTree *declaration, int offset) {
    if (!declaration)
        return offset;

    if (!declaration->symbol
            || declaration->operation == LITERAL
            || (declaration->operation != DECLARATION
            && declaration->operation != FORMAL
            && strncmp(declaration->symbol->identifier, "_temp", 5) != 0)) {
        offset = allocateStackSpace(declaration->right, offset);
        offset = allocateStackSpace(declaration->left, offset);
        offset = allocateStackSpace(declaration->opt, offset);
    } else {
        if (!(declaration->symbol->location = malloc(10 * sizeof(char))))
            ERROR(NULL, __LINE__, TRUE);							//out of memory

        sprintf(declaration->symbol->location, "%d($sp)", offset);

        //printf("Declaration %s has location %s\n", declaration->symbol->identifier, declaration->symbol->location);

        if (declaration->operation == DECLARATION) {

            if (declaration->symbol->type == CHAR_ARRAY) {
                offset += declaration->symbol->value.intVal;
                if (offset % 4 != 0)
                    offset += 4 - (offset % 4);
                offset = allocateStackSpace(declaration->left, offset);
            } else	if (declaration->symbol->type == INT_ARRAY) {
                offset += 4 * declaration->symbol->value.intVal;
                offset = allocateStackSpace(declaration->left, offset);
            } else {
                offset = allocateStackSpace(declaration->left, offset + 4);
            }

        } else {
            offset = allocateStackSpace(declaration->right, offset + 4);
            offset = allocateStackSpace(declaration->left, offset);
            offset = allocateStackSpace(declaration->opt, offset);
        }
    }
    return offset;
}

/* Function: typeError
 * Parameters: char *errorMessage
 * Description: Called when semantic errors are found. Prints error message and
 *					turns code generation off.
 * Returns: void
 * Preconditions: none
 */
void typeError(char *errorMessage) {
    fprintf(stderr, "TYPE ERROR: line %d: %s\n", yylineno, errorMessage);
    _parsing_success = FALSE;
}

/* Function: generateNewTempID
 * Parameters: none
 * Description: Updates to a new unique temporary variable ID.
 * Returns: none
 * Preconditions: none
 */
void generateNewTempID() {
    sprintf(_tempID, "_temp%d", _tempNum++);
}

/* Function: generateNewLabelID
 * Parameters: none
 * Description: Updates to a new unique label ID.
 * Returns: none
 * Preconditions: none
 */
void generateNewLabelID() {
    sprintf(_labelID, "_label%d", _labelNum++);
}