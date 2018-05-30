/////////////////////////////getValue/////////////////////////////
// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue() {
    
    Tokenizer<NumericType> tok(str);
    Token<NumericType> lastToken;
    
    do {
        lastToken = tok.getToken();
        processToken(lastToken);
    } while (lastToken.getType() != EOL);
    
    if (postFixStack.empty()) {
        cerr << "Missing operatnd!" << endl;
        return 0;
    }
    
    NumericType theResult = postFixStack.back();
    postFixStack.pop_back();
    if (!postFixStack.empty())
        cerr << "Warning: missing operators!" << endl;
    
    return theResult;
} // end of getValue

///////////////////////////////processToken/////////////////////////////
// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.

template<class NumericType>
void Evaluator<NumericType>::
processToken(const Token<NumericType> &lastToken) {
    TokenType topoperator;
    TokenType lastType = lastToken.getType();
    
    switch (lastType) {
        case VALUE:
            postFixStack.push_back(lastToken.getValue());
            postFixVarStack.push_back(' ');
            return;
            
        case VAR_A:
            postFixStack.push_back(var_a);
            postFixVarStack.push_back('a');
            return;
            
        case VAR_B:
            postFixStack.push_back(var_b);
            postFixVarStack.push_back('b');
            return;
            
        case VAR_C:
            postFixStack.push_back(var_c);
            postFixVarStack.push_back('c');
            return;
            
        case CPAREN:
            while ((topoperator = opStack.back()) != OPAREN &&
                   topoperator != EOL)
                // check binary or unary
                if (topoperator == UN_MINUS || topoperator == UN_PLUS || topoperator == BIT_COMP
                    || topoperator == NOT || topoperator == ASSIGN)
                    unaryoperator(topoperator);
                else
                    binaryoperator(topoperator);
            
            if (topoperator == OPAREN)
                opStack.pop_back(); // get rid of opening parethesis
            else
                cerr << "Missing open parenthesis" << endl;
            break;
            
        default: // general operator case
            while (PREC_TABLE[lastType].inputSymbol <=
                   PREC_TABLE[topoperator = opStack.back()].topOfStack)
                
                // check binary or unary
                if (topoperator == UN_MINUS || topoperator == UN_PLUS || topoperator == BIT_COMP
                    || topoperator == NOT || topoperator == ASSIGN)
                    unaryoperator(topoperator);
                else
                    binaryoperator(topoperator);
            
            if (lastToken.getType() != EOL)
                opStack.push_back(lastType); // it push back the operations into
            break;
    }
}

////////////////////////////////binarytopoperator////////////////////////////////
// Process an operator by taking two items off the postfix stack
// Print error if missing closing parenthesis or division by 0.

template<class NumericType>
void Evaluator<NumericType>::binaryoperator(TokenType topoperator) {
    if (topoperator == OPAREN) {
        cerr << "Unbalanced parenthesis" << endl;
        opStack.pop_back();
        return;
    }
    NumericType rhs = getTop(); // gets the rhs
    NumericType lhs = getTop(); // gets the lhs
    
    if (topoperator == PLUS)                          // +
        postFixStack.push_back(lhs + rhs);
    else if (topoperator == MINUS)                    // -
        postFixStack.push_back(lhs - rhs);
    else if (topoperator == MULT)                     // *
        postFixStack.push_back(lhs * rhs);
    else if (topoperator == DIV) {                    // /
        if (rhs != 0)   // checking for 0 denominator
            postFixStack.push_back(lhs / rhs);
        else {
            cerr << "Division by zero" << endl;
            postFixStack.push_back(lhs);
        }
    } else if (topoperator == EXP)                    // ^
        postFixStack.push_back(pow(lhs, rhs));
    else if (topoperator == MODULUS)                  // %
        postFixStack.push_back(lhs % rhs);
    else if (topoperator == SHIFT_L)                  // <<
        postFixStack.push_back(lhs << rhs);
    else if (topoperator == SHIFT_R)                  // >>
        postFixStack.push_back(lhs >> rhs);
    else if (topoperator == LT)                       // <
        postFixStack.push_back(lhs < rhs);
    else if (topoperator == LE)                       // <=
        postFixStack.push_back(lhs <= rhs);
    else if (topoperator == GT)                       // >
        postFixStack.push_back(lhs > rhs);
    else if (topoperator == GE)                       // >=
        postFixStack.push_back(lhs >= rhs);
    else if (topoperator == EQUAL)                    // ==
        postFixStack.push_back(lhs == rhs);
    else if (topoperator == NOTEQUAL)                 // !=
        postFixStack.push_back(lhs != rhs);
    else if (topoperator == BIT_AND)                  // &
        postFixStack.push_back(lhs & rhs);
    else if (topoperator == BIT_IOR)                  // |
        postFixStack.push_back(lhs | rhs);
    else if (topoperator == LOG_OR)                   // ||
        postFixStack.push_back(lhs || rhs);
    else if (topoperator == LOG_AND)                  // &&
        postFixStack.push_back(lhs && rhs);
    
    postFixVarStack.push_back(' ');
    opStack.pop_back(); // remove the operation in the operation stack
    
    
}

///////////////////////////////Unaryoperator/////////////////////////////
// Process an operator by taking two items off the postfix stack
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::unaryoperator(TokenType topOp) {
    if (topOp == OPAREN) {
        cerr << "Unbalanced parenthesis" << endl;
        opStack.pop_back();
        return;
    }
    
    NumericType rhs = getTop();  // gets the rhs
    
    if (topOp == UN_MINUS)              // -
        postFixStack.push_back(-rhs);
    else if (topOp == UN_PLUS)          // +
        postFixStack.push_back(+rhs);
    else if (topOp == NOT)              // !
        postFixStack.push_back(!rhs);
    else if (topOp == BIT_COMP)         // ~
        postFixStack.push_back(~rhs);
    else if (topOp == ASSIGN) {
        
        NumericType lhs = postFixStack.back(); // gets the variable in the stack
        postFixStack.pop_back();        // pop out the variable in the postFix stack
        postFixVarStack.pop_back();     // pop out the variable in the postFixVar stack
        
        if (lhs == var_a) {
            var_a = rhs;       // assign the right hand side to var_a data member
            postFixStack.push_back(var_a);      // put var back in postFix
            postFixVarStack.push_back('a');     // put var back in postFixVar stack
        }
        else if (lhs == var_b) {
            var_b = rhs;       // assign the right hand side to var_b data member
            postFixStack.push_back(var_b = rhs);    // put var back in postFix
            postFixVarStack.push_back('b');         // put var back in postFixVar stack
        }
        else if (lhs == var_c) {
            var_c = rhs;      // assign the right hand side to var_c data member
            postFixStack.push_back(var_c = rhs);    // put var back in postFix
            postFixVarStack.push_back('c');         // put var back in postFixVar stack
        }
        opStack.pop_back(); // remove the operation in the operation stack
        return;
    }
    
    postFixVarStack.push_back(' ');
    opStack.pop_back(); // remove the operation in the operation stack
    
}

///////////////////////////////getTop/////////////////////////////
// top and pop the postfix machine stack; return the result.
// If is empty, print an error message.

template<class NumericType>
NumericType Evaluator<NumericType>::getTop() {
    if (postFixStack.empty()) {
        cerr << "Missing operand" << endl;
        return 0;
    }
    
    NumericType tmp = postFixStack.back();
    postFixStack.pop_back();
    postFixVarStack.pop_back();
    return tmp;
}
