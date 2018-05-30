
//  longint.cpp
//  Created by Jerryshen on 5/28/17.
//  Copyright © 2017 Zeyu. All rights reserved.
#include "longint.h"
/////////////////////////constructors///////////////////////////
LongInt::LongInt(const string str){
    storedinQ(str);
}
/////////////////////copy constructor///////////////////////
LongInt::LongInt(const LongInt &rhs) {
    negative = rhs.negative; // copying the sign
    digits.clear(); // clearing this digits first before adding
    // creating temp so it wont remove it in the original
    Deque<char> d(rhs.digits);
	while(d.getFront()=='0')
	{
		d.removeFront();
	}
    while (!d.isEmpty()) {
        digits.addBack(d.removeFront());
    }
}
////////////////////////default constructor/////////////////////
LongInt::LongInt() {
    negative = false;
}

///////////////////////// Destructor/////////////////////////
LongInt::~LongInt() {
    digits.clear();
}
//////////////////////////operator+//////////////////////////
LongInt LongInt::operator+(const LongInt &rhs) const {
    LongInt result;

    if (negative != rhs.negative)  // sign are different need call -
    {
        LongInt left(*this);  // temp to hold lhs
        LongInt right(rhs);   // temp to hold rhs
        if (!left.negative)//it is the case when A + (-B) 
        {
            right.negative=false;
            result=left-right;//A-B
        }
        else//it is the case when (-A) + B
        {
            left.negative=false;
            result=right-left;//B-A
        }
        return result;
    }
    
    //now both lhs and rhs is positive
    Deque<char> right(rhs.digits);    // rhs copy
    Deque<char> left(digits);        // lhs copy
    
    int i = 0;
    int carry = 0; // decide whether to carry one or not
 
    // choosing which is longer int to make sure every int is counted
    // converting char into int and doing the addition computation
    while (i < max(right.size(), left.size())) {
        int answer;
        int leftValue;
        int rightValue;
        
        if (!left.isEmpty()) // left hand side
            leftValue = (int) left.removeBack() - '0';
        else
            leftValue = 0; // empty
        
        if (!right.isEmpty())  // right hand side
            rightValue = (int) right.removeBack() - '0';
        else
            rightValue = 0; // empty
        
        answer = leftValue + rightValue + carry;
        carry = answer / 10; // if ans is divisible by 10 then carry
        // ans % 10 to be sure that its only from 0 to 9, for 10 it becomes 0
        // and then carry over
        result.digits.addFront((char) (answer % 10 + '0'));
    }
    // to add the carry to the digits if there is one
    if (carry) // 0 is false, 1 is true
        result.digits.addFront('1');
    
    result.negative=negative;// since lhs and rhs are same sign, the sum will have the same sign;
	return result;
    
}
//////////////////////////operator-//////////////////////////
LongInt LongInt::operator-(const LongInt &rhs) const {
    LongInt result;
    if (negative != rhs.negative)  //if sign are different need call +
    {
        LongInt left(*this);  // temp to hold lhs
        LongInt right(rhs);   // temp to hold rhs
        if (!left.negative)//it is the case when A - (-B)
        {
            right.negative=false;
            result=left+right;//A+B
        }
        else//it is the case when (-A)- B
        {
            left.negative=false;
            result=right+left;//-(A+B)
			result.negative=true;
        }
        return result;
    } 
    //now both lhs and rhs must have same sign.let do minus
    
	Deque<char> right(rhs.digits);    // rhs copy
    Deque<char> left(digits);        // lhs copy
	int borrow=0;
    int i = 0;
	//now find which one has greater absulate value
	if(left.size()<=right.size())//if right size is no less than left
	{
		if(right.size()==left.size())//if same size
		{
			int leftV=0;
			int rightV=0;
			//cout<<"size is same"<<endl;
			int minsize = max(right.size(), left.size());
			while(leftV==rightV)//if right size is greater than left size
			{
				leftV=(int)left.getFront();
				//cout<<"The value of left : "<<leftV-48<<endl;
				rightV=(int)right.getFront();
				//cout<<"The value of right : "<<rightV-48<<endl;
				if(rightV>leftV)//Since B>A, |A-B|=B-A
				{
					right=Deque<char>(digits); 
					left =Deque<char>(rhs.digits); 
					result.negative=true;//swich sign
					//cout<<"R-L"<<endl;
					break;
				}
				else if(rightV<leftV)
				{
					right=Deque<char>(rhs.digits); 
					left =Deque<char>(digits); 
					result.negative=rhs.negative;//keep sign
					//cout<<"L-R"<<endl;
					break;
				}
				left.removeFront();
				right.removeFront();	
			}
		}
		else
		{
			right=Deque<char>(digits); 
			left =Deque<char>(rhs.digits);
			result.negative=true;//result has same sign with lhs
		}
	}

	//Now let do A-B with A>B
	int index= max(right.size(), left.size());
    while (i < index) 
	{
        int answer;
		int leftValue;
        int rightValue;
        
        if (!left.isEmpty()) // left hand side
            leftValue = (int) left.removeBack() - '0';
        else
            leftValue = 0; // empty
        
        if (!right.isEmpty())  // right hand side
            rightValue = (int) right.removeBack() - '0';
        else
            rightValue = 0; // empty
        answer = (leftValue-borrow)-rightValue;
		borrow=0;
        if(answer<0)
		{
			answer+=10;
			borrow=1;
		}
        result.digits.addFront((char) (answer + '0'));
		i++;
    }
	while(result.digits.getFront()=='0')
		result.digits.removeFront();
    return result;
}


///////////////////////////Overloaded =: assignment///////////////////////////
const LongInt &LongInt::operator=(const LongInt &rhs) {
    if (this != &rhs) { // the lhs and rhs is not the same
        digits.clear(); // clear lhs digits first
        (*this).digits = rhs.digits; // copy digits
        negative = rhs.negative; // copy sign
    }
    return *this; // return lhs
}

/////////////////////////////Overloaded <: less than///////////////////////////
// Logical binary operators
bool LongInt::operator<(const LongInt &rhs) const
 {
    if (operator==(rhs))   // lhs is equal to rhs
        return false;
    else {                 // lhs is not equal to rhs
        if (negative != rhs.negative)   // lhs and rhs has opposite signs
            return negative; // depends on the lhs
        if (digits.size() != rhs.digits.size()) // lhs and rhs is not equal in size
            // if lhs is negative, lhs is bigger in size than rhs
            return digits.size() > rhs.digits.size() == negative;
        else {
            Deque<char> right(rhs.digits);        // rhs
            Deque<char> left(digits);            // lhs
            
            int i = 0;
            
            // choosing which is longer int to make sure every int is counted
            // converting char into int and comparing if lhs is less than rhs
            while (i < max(right.size(), left.size())) 
			{
                int leftValue;
                int rightValue;
                
                
                // removeFront() because the front is bigger so saves time to evaluate
                if (!left.isEmpty()) // left hand side
                    leftValue = (int) left.removeFront() - 48; // ASCII char into int
                else
                    leftValue = -1; // empty
                
                if (!right.isEmpty())  // right hand side
                    rightValue = (int) right.removeFront() - 48; // ASCII char into int
                else
                    rightValue = -1; // empty
                
                // both lhs and rhs has the same sign
                if (negative && leftValue != rightValue)
                    return leftValue < rightValue;
                if (!negative && leftValue != rightValue)
                    return leftValue < rightValue;
            }
        }
    }
    return false;
}


/////////////////////////////Overloaded <=///////////////////////////
bool LongInt::operator<=(const LongInt &rhs) const
 {
    return (operator==(rhs) || operator<(rhs));
}


/////////////////////////////Overloaded >//////////////////////////
bool LongInt::operator>(const LongInt &rhs) const 
{
    return !(operator<=(rhs));
} 

/////////////////////////////Overloaded >=///////////////////////////
bool LongInt::operator>=(const LongInt &rhs) const 
{
    return !(operator<(rhs));
} 


/////////////////////////////Overloaded ==///////////////////////////
bool LongInt::operator==(const LongInt &rhs) const
 {
    if (negative == rhs.negative) {
        Deque<char> *right = new Deque<char>(rhs.digits);    // rhs
        Deque<char> *left = new Deque<char>(digits);        // lhs
        
        int i = 0;
        
        // choosing which is longer int to make sure every int is counted
        // converting char into int
        while (i < max(right->size(), left->size())) 
		{
            int leftValue;
            int rightValue;
            
            // removeFront() because the front is bigger so saves time to evaluate
            // left hand side
            if (!left->isEmpty())
                leftValue = (int) left->removeFront();
            else
                leftValue = -1; // empty
            
            // right hand side
            if (!right->isEmpty())
                rightValue = (int) right->removeFront();
            else
                rightValue = -1; // empty
            
            if (leftValue == -1 || rightValue == -1)
                return false;
            if (!(leftValue == rightValue))
                return false;
        }
        return true;
    }
    else 
	{ // lhs and rhs has opposite sign
        return false;
    }
}


///////////////////////////Overloaded !=///////////////////////////
bool LongInt::operator!=(const LongInt &rhs) const {
    return !operator==(rhs);
}

////////////////////////private/////////////////////////
void LongInt::storedinQ(const string str){
    negative=false;
    int index=0;
    for(int i=0;i<str.length();i++)
	{// find the negative sige if there is one, mark the index
        if(str[i]=='-')
        {
            index=i+1;
            negative=true;
            break;
        }
    }
	while(str[index]=='0')
	{
		index++;
	}
    while(index<str.length())//add the interger to the digits
    {
        if(str[index]>='0'&&str[index]<='9')
        {
            digits.addBack(str[index]);
        }
        index++;
    }
}

void LongInt::remove0s()
{
    while (!digits.isEmpty() && negative && digits.getFront() == '9')
        digits.removeFront();
    
    while (!digits.isEmpty() && !negative && digits.getFront() == '0')
        digits.removeFront();
}






/////////////////////////////Overloaded >>///////////////////////////
istream &operator>>(istream &in, LongInt &rhs) 
{
    string input;
    in >> input;
    rhs.storedinQ(input);
    return in;
}


/////////////////////////////Overloaded <<: output///////////////////////////
ostream &operator<<(ostream &out, const LongInt &rhs)
 {
    if (rhs.digits.isEmpty())
        out << "0";
    else {
        Deque<char> d(rhs.digits); // temp
        
        if (rhs.negative)
            out << "-";
        
        while (!d.isEmpty())
		{
				out << d.removeFront(); // normally printing
		}
	}
    return out;
}










