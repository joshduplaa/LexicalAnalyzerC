//Joshua Duplaa, R11583588
//Project1

/* front.c - a lexical analyzer system for DCooke language */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Constants for character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

//Token codes with integer identifiers to simplify comaparisons
#define ASSIGN_OP  10
#define LESSER_OP  20
#define GREATER_OP  30
#define EQUAL_OP  40
#define NEQUAL_OP  50
#define LEQUAL_OP  60
#define GEQUAL_OP  70
#define SEMICOLON  80
#define ADD_OP  90
#define SUB_OP  100
#define MULT_OP  110
#define DIV_OP  120
#define INC_OP  130
#define DEC_OP  140
#define LEFT_PAREN  150
#define RIGHT_PAREN  160
#define IDENT  200
#define INT_LIT  210
#define KEY_READ 69
#define KEY_WRITE 21
#define KEY_WHILE 22
#define KEY_DO 23
#define KEY_OD 24
#define EOF -1

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
static int lookup(char ch);

/******************************************************/


/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
//Main function at end of program

static int lookup(char ch) {
    switch (ch) {
        case ':':
            addChar(); // Add ':' to lexeme
            if ((nextChar = getc(in_fp)) == '=') {
                addChar(); // Add '=' to lexeme
                nextToken = ASSIGN_OP;
            } else {
                ungetc(nextChar, in_fp); // Push the character back for unknown case
                nextToken = UNKNOWN;
            }
            break;

        case '<':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') { //checks for <=
                addChar();
                nextToken = LEQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = LESSER_OP;
            }
            break;

        case '>':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {  //check for >=
                addChar();
                nextToken = GEQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = GREATER_OP;
            }
            break;

        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;

        case '!':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {
                addChar();
                nextToken = NEQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = UNKNOWN;
            }
            break;

        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;

        case '+':
            addChar();
            if ((nextChar = getc(in_fp)) == '+') { //checks for increment ++
                addChar();
                nextToken = INC_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = ADD_OP;
            }
            break;

        case '-':
            addChar();
            if ((nextChar = getc(in_fp)) == '-') { //checks for decrement --
                addChar();
                nextToken = DEC_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = SUB_OP;
            }
            break;

        case '*':
            addChar();
            nextToken = MULT_OP;
            break;

        case '/':
            addChar();
            nextToken = DIV_OP;
            break;

        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;

        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        
        default:
            addChar();          
            nextToken = UNKNOWN;    //Unknown Lexemes
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

//Function to print the actual token name the lexeme identifier is associated with
const char *getTokenName(int token) {
    switch (token) {
        case ASSIGN_OP: return "ASSIGN_OP";
        case LESSER_OP: return "LESSER_OP";
        case GREATER_OP: return "GREATER_OP";
        case EQUAL_OP: return "EQUAL_OP";
        case NEQUAL_OP: return "NEQUAL_OP";
        case LEQUAL_OP: return "LEQUAL_OP";
        case GEQUAL_OP: return "GEQUAL_OP";
        case SEMICOLON: return "SEMICOLON";
        case ADD_OP: return "ADD_OP";
        case SUB_OP: return "SUB_OP";
        case MULT_OP: return "MULT_OP";
        case DIV_OP: return "DIV_OP";
        case INC_OP: return "INC_OP";
        case DEC_OP: return "DEC_OP";
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case KEY_READ: return "KEY_READ";
        case KEY_WRITE: return "KEY_WRITE";
        case KEY_WHILE: return "KEY_WHILE";
        case KEY_DO: return "KEY_DO";
        case KEY_OD: return "KEY_OD";
        case IDENT: return "IDENT";
        case INT_LIT: return "INT_LIT";
        case EOF: return "END OF FILE";
        default: return "UNKNOWN";
    }
}

/*****************************************************/
/* checkForKeywords - a function to check if the lexeme is a keyword and set 
 * the appropriate token */
void checkForKeywords() {
    if (strcmp(lexeme, "read") == 0) {
        nextToken = KEY_READ;
    } else if (strcmp(lexeme, "write") == 0) {
        nextToken = KEY_WRITE;
    } else if (strcmp(lexeme, "while") == 0) {
        nextToken = KEY_WHILE;
    } else if (strcmp(lexeme, "do") == 0) {
        nextToken = KEY_DO;
    } else if (strcmp(lexeme, "od") == 0) {
        nextToken = KEY_OD;
    } else {
        nextToken = IDENT;
    }
}

/*****************************************************/
/* lex - a simple lexical analyzer for DCooke language */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            checkForKeywords(); // Call the checkForKeywords() function
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;

    } /* End of switch */

    //if the current token is EOF, print a line, for visual sake.
    if(nextToken == EOF){
        printf("------------------------------------\n");
    }
    //printed in columns of lexemes and corresponding tokens
    printf("%-10s %-10s\n", lexeme, getTokenName(nextToken));
    return nextToken;
} /* End of function lex */


/* main driver */
int main() 
{
    //file path for source file
    const char *sourceCodeFilePath = "test.dc";

    //Opens the input data file and analyzes the content
    if ((in_fp = fopen(sourceCodeFilePath, "r")) == NULL) {
        printf("ERROR - cannot open the source code file: %s\n", sourceCodeFilePath);
        return 1;
    } else {
        printf("DCooke Analyzer :: R11583588\n\n");
        getChar();
        do {
            lex();
            
        } while (nextToken != EOF); //does lexical analysis until end of file
    }

    fclose(in_fp);  //closes the file stream associated with the file pointer 
    return 0;
}