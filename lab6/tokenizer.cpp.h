#include <iostream>

///////////////////////////////getChar///////////////////////////////
// gets a char

template<class NumericType>
bool Tokenizer<NumericType>::getChar(char &ch) {
    char tmp;
    
    // skip blanks
    while (in.get(tmp) && tmp == ' ');
    
    // read a char
    if (in.good() && tmp != '\n' && tmp != '\0') {
        ch = tmp;
        return true; // if it is not a delimiter
    }
    else
        return false; // if it's a delimitter
}

///////////////////////////////getToken///////////////////////////////
// gets a token
template<class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken() {
    
    char ch, ch2;
    NumericType theValue;
    
    if (getChar(ch) == true) {
        switch (ch) {
            case '/':
                return DIV;        // /
            case '*':
                return MULT;        // *
            case '(':
                return OPAREN;      // (
            case ')':
                return CPAREN;      // )
            case '+':
                return PLUS;        // +
            case '-':
                return MINUS;       // -
            case '^':
                return EXP;         // ^
            case '%':
                return MODULUS;     // %
            case '<':
                getChar(ch2); // gets the next char
                if (ch2 == '<')
                    return SHIFT_L;  // <<
                else if (ch2 == '=')
                    return LE;       // <=
                // if its non of the above put the char back
                else in.putback(ch2);
                return LT;          // <
            case '>':
                getChar(ch2); // gets the next char
                if (ch2 == '>')
                    return SHIFT_R;  // >>
                else if (ch2 == '=')
                    return GE;      // >=
                // if its non of the above put the char back
                else in.putback(ch2);
                return GT;          // >
            case '=':
                getChar(ch2); // gets the next char
                if (ch2 == '=')
                    return EQUAL;   //==
                // if its non of the above put the char back
                else in.putback(ch2);
            case '!':
                getChar(ch2); // gets the next char
                if (ch2 == '=')
                    return NOTEQUAL;    //!=
                // if its non of the above put the char back
                else in.putback(ch2);
            case '&':
                getChar(ch2); // gets the next char
                if (ch2 == '&')
                    return LOG_AND;    // &&
                // if its non of the above put the char back
                else in.putback(ch2);
                return BIT_AND;         // &
            case '|':
                getChar(ch2); // gets the next char
                if (ch2 == '|')
                    return LOG_OR;      // ||
                // if its non of the above put the char back
                else in.putback(ch2);
                return BIT_IOR;         // |
            default:
                in.putback(ch);
                if (!(in >> theValue)) {
                    cerr << "Parse error" << endl;
                    return EOL;
                }
                return Token<NumericType>(VALUE, theValue);
        }
    }
    
    return EOL;
} 
