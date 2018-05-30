template<class NumericType>
bool Tokenizer<NumericType>::getChar(char &ch) {
    char tmp;
    
    // skip blanks
    while (in.get(tmp) && tmp == ' ');
    
    // read a char
    if (in.good() && tmp != '\n' && tmp != '\0') {
        //prevToken = temp;
        ch = tmp;
        return true; // if it is not a delimiter
    }
    else
        return false; // if it's a delimitter
} // end getChar

///////////////////////////////getToken///////////////////////////////

template<class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken() {
    
    char ch;
    NumericType theValue;
    
    // return token then record token into prevToken data member
    if (getChar(ch) == true) {
        switch (ch) {
            case '/':                        // /
                prevToken = DIV;
                return DIV;
            case '*':                        // *
                prevToken = MULT;
                return MULT;
            case '(':                        // (
                prevToken = OPAREN;
                return OPAREN;
            case ')':                        // )
                prevToken = CPAREN;
                return CPAREN;
            case '+':                        // +
                if (prevToken == OPAREN) {
                    prevToken = UN_PLUS;
                    return UN_PLUS;
                } else {
                    prevToken = PLUS;
                    return PLUS;
                }
            case '-':                        // -
                if (prevToken == OPAREN ) {
                    prevToken = UN_MINUS;
                    return UN_MINUS;
                } else {
                    prevToken = MINUS;
                    return MINUS;
                }
            case '^':                        // ^
                prevToken = EXP;
                return EXP;
            case '%':                        // %
                prevToken = MODULUS;
                return MODULUS;
            case '<':
                getChar(ch);                   // gets next char
                if (ch == '<') {              // <<
                    prevToken = SHIFT_L;
                    return SHIFT_L;
                }
                else if (ch == '=') {         // <=
                    prevToken = LE;
                    return LE;
                }
                else in.putback(ch);         // puts back char
                prevToken = LT;              // <
                return LT;
            case '>':
                getChar(ch);                // gets next char
                if (ch == '>') {            // >>
                    prevToken = SHIFT_R;
                    return SHIFT_R;
                }
                else if (ch == '=') {       // >=
                    prevToken = GE;
                    return GE;
                }
                in.putback(ch);              // puts back char
                prevToken = GT;             // >
                return GT;
            case '=':
                getChar(ch);                 // gets next char
                if (ch == '=') {            // ==
                    prevToken = EQUAL;
                    return EQUAL;
                }
                in.putback(ch);              // puts back char
                prevToken = ASSIGN;         // =
                return ASSIGN;
            case '!':
                getChar(ch);                 // gets next char
                if (ch == '=') {            // !=
                    prevToken = NOTEQUAL;
                    return NOTEQUAL;
                }
                else in.putback(ch);        // puts back char
                prevToken = NOT;            // !
                return NOT;
            case '&':
                getChar(ch);               // gets next char
                if (ch == '&') {           // &&
                    prevToken = LOG_AND;
                    return LOG_AND;
                }
                else in.putback(ch);       // puts back char
                prevToken = BIT_AND;       // &
                return BIT_AND;
            case '|':
                getChar(ch);              // gets next char
                if (ch == '|') {          // ||
                    prevToken = LOG_OR;
                    return LOG_OR;
                }
                else in.putback(ch);      // puts back char
                prevToken = BIT_IOR;      // |
                return BIT_IOR;
            case '~':
                prevToken = BIT_COMP;     // ~
                return BIT_COMP;
            case 'a':
                prevToken = VAR_A;        // a
                return Token<NumericType>(VAR_A, 0);
            case 'b':
                prevToken = VAR_B;        // b
                return Token<NumericType>(VAR_B, 0);
            case 'c':
                prevToken = VAR_C;        // c
                return Token<NumericType>(VAR_C, 0);
                
            default:
                in.putback(ch);            // puts back char
                if (!(in >> theValue)) {
                    cerr << "Parse error" << endl;
                    prevToken = EOL;
                    return EOL;
                }
                prevToken = VALUE;        // value
                return Token<NumericType>(VALUE, theValue);
        }
    }
    return EOL;
} 

