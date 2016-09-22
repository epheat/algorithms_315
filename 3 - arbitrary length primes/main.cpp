//Evan Heaton
//CS315 - Homework 5
//11-5-15
//http://www.cs.uky.edu/~mirek/class-materials/315/fa15/hmwk-5-bonus.pdf

//111100011010
//111111011

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <cmath>

using namespace std;

vector<int> decimal_multiply_by_2(vector<int> decInput);
vector<int> binary_to_decimal(vector<int> bin);
vector<int> generate_prime_candidate(int n);
void printVec(vector<int> v);
void printNormalVec(vector<int> v);
vector<int> binary_subtract(vector<int> v1, vector<int> v2);
void vector_pad(vector<int> &v1, vector<int> &v2);
void twos_complement(vector<int> &v);
void binary_add_one(vector<int> &v);
vector<int> binary_add(vector<int> bin1, vector<int> bin2, int add_not_subtract);
vector<int> binary_multiply(vector<int> bin1, vector<int> bin2);
int binary_greater_than(vector<int>bin1, vector<int> bin2);
void binary_division(vector<int> bin1, vector<int> bin2, vector<int> &q, vector<int> &r);
void vector_trim(vector<int> &v);
vector<int> modular_exponent(vector<int> x, vector<int> y, vector<int> N);

int main(int argc, const char* argv[]) {
    srand((int)time(NULL));
    vector<int> prime_candidate;
    
    vector<int> three, one;
    three.push_back(1);
    three.push_back(1);
    one.push_back(1);
    
    int primes_generated = 0;
    int tries = 0;
    
    while (primes_generated < 100) { //generate 100 16 bit primes??
        
        tries++;
        
        prime_candidate = generate_prime_candidate(16);
        vector<int> mod = modular_exponent(three, binary_subtract(prime_candidate, one), prime_candidate);
        
        if (mod.size() == 1 && mod[0] == 1) { //if it is truly prime
            primes_generated++;
            vector<int> decimal_prime_candidate = binary_to_decimal(prime_candidate);
            stringstream converter; //for converting my prime candidate to decimal int
            for (int i=(int)decimal_prime_candidate.size()-1;i>=0;i--) {
                converter << decimal_prime_candidate[i];
            }
            int integer_decimal_prime_candidate;
            converter >> integer_decimal_prime_candidate;
            
            printNormalVec(prime_candidate);
            cout << " = ";
            printNormalVec(decimal_prime_candidate);
            
            bool is_prime = true;
            for (int i=2;i<=sqrt(integer_decimal_prime_candidate);i++) {
                if (integer_decimal_prime_candidate%i == 0) {
                    is_prime = false;
                    cout << "\nIS NOT PRIME! due to factor of " << i;
                    //break;
                }
            }
            
            if (is_prime)
                cout << "\nPrime by brute force";
            cout << "\n";
        }
        //cout << "that wasn't prime\n";
    }
    
    cout << "TRIES: " << tries;
    
    for (int bits = 16;bits<=128;bits*=2) {
        bool generate_again = true;
        int iterations = 0;
        while (generate_again) {
            prime_candidate = generate_prime_candidate(bits);
        
            vector<int> mod = modular_exponent(three, binary_subtract(prime_candidate, one), prime_candidate);
        
            if (mod.size() == 1)
                if (mod[0] == 1)
                    generate_again = false;
            iterations++;
        }
        cout << "\nTook " << iterations << " iterations to generate prime number with " << bits << " bits ";
        printVec(prime_candidate);
        
        
        vector<int> decimal_prime_candidate = binary_to_decimal(prime_candidate);
        cout << " : ";
        printVec(decimal_prime_candidate);
        cout << " : ";
        printNormalVec(prime_candidate);
        cout << " : ";
        printNormalVec(decimal_prime_candidate);
        
    }
    
    cout << "\n\ngib bonus points pls\n\n";
    
    
    
    
}


vector<int> generate_prime_candidate(int n) {
    vector<int> prime_candidate;
    prime_candidate.push_back(1);
    for (int i=0;i<n-2;i++) {
        prime_candidate.push_back(rand()%2);
    }
    prime_candidate.push_back(1);
    return prime_candidate;
}


void printVec(vector<int> v) { //just to print vectors for debugging purposes
    cout << "<";
    if (v.size()==0)
        cout << ">";
    else {
        for (int i=0;i<v.size()-1;i++)
            cout << v[i] << ", ";
        cout << v[v.size()-1] << ">";
    }
}

void printNormalVec(vector<int> v) { //just to print vectors (normalized) for debugging purposes
    if (v.size()==0)
        cout << 0;
    else {
        for (int i=(int)v.size()-1;i>=0;i--)
            cout << v[i];
    }
}

//subtract v2 from v1, v2 must be less than or equal to v1
vector<int> binary_subtract(vector<int> v1, vector<int> v2) {
    vector_pad(v1, v2);
    twos_complement(v2);
    if (v2.size() > v1.size())
        v2.pop_back();
    return binary_add(v1, v2, 0);
}


//assuming v1's size >= v2's size
void vector_pad(vector<int> &bin1, vector<int> &bin2) {
    bool bin1smaller = false;
    //cout << bin1.size() << " " << bin2.size() << " ";
    if (bin1.size() < bin2.size())
        bin1smaller = true;
    if (bin1smaller) {
        int difference = (int)bin2.size()-(int)bin1.size();
        for (int i=0;i<difference;i++) {
            bin1.push_back(0);
            //cout << "padded bin1";
        }
    } else {
        int difference = (int)bin1.size()-(int)bin2.size();
        for (int i=0;i<difference;i++) {
            bin2.push_back(0);
            //cout << "padded bin2";
        }
    } //FINISHED PADDING
}

//invert each bit and add one
void twos_complement(vector<int> &v) {
    for (int i=0;i<v.size();i++) {
        if (v[i])
            v[i] = 0;
        else
            v[i] = 1;
    }
    binary_add_one(v);
    return;
}


//add one to a binary vector
void binary_add_one(vector<int> &v) {
    int i=0, carry=1;
    while (carry == 1 && i < v.size()) {
        if (v[i]) //if it's a 1, make it a zero and make carry a 1
        {
            v[i] = 0;
            carry = 1;
            i++;
        } else {
            v[i] = 1;
            carry = 0;
        }
    }
    if (carry)
        v.push_back(1);
}

vector<int> binary_add(vector<int> bin1, vector<int> bin2, int add_not_subtract) {
    vector<int> binary_result;
    
    vector_pad(bin1, bin2);
    
    bool carry = false;
    for (int i=0;i<bin1.size();i++) {
        
        if ((carry + bin1[i] + bin2[i])%2 != 0) //Does this work as logical XOR? lmao
            binary_result.push_back(1);
        else
            binary_result.push_back(0);
        
        if ((bin1[i] && bin2[i]) || (bin1[i] && carry) || (bin2[i] && carry))
            carry = true;
        else
            carry = false;
    }
    
    if (carry && add_not_subtract)
        binary_result.push_back(1);
    
    return binary_result;
    
}

vector<int> binary_multiply(vector<int> bin1, vector<int> bin2) {
    vector_pad(bin1, bin2);
    vector<int> z;
    for (int i=(int)bin2.size()-1;i>=0;i--) {
        z.insert(z.begin(), 0); //z = 2z
        if (bin2[i] == 1)
            z = binary_add(z, bin1, 1);
    }
    return z;
}

void binary_division(vector<int> bin1, vector<int> bin2, vector<int> &q, vector<int> &r) {
    if (bin1.size() < bin2.size()) {
        r = bin1;
        vector_trim(q);
        vector_trim(r);
        return;
    }
    
    for (int i=(int)bin1.size()-1;i>=0;i--) {
        q.insert(q.begin(), 0); //q = 2q
        r.insert(r.begin(), 0); //r = 2r
        if (bin1[i] == 1)
            binary_add_one(r);
        if (binary_greater_than(r, bin2) >= 0) {
            binary_add_one(q);
            r = binary_subtract(r, bin2);
        }
    }
    vector_trim(q);
    vector_trim(r);
}

//is bin1 greater than bin2? 1 = true, -1 = false, 0 = equal, -2 = error
int binary_greater_than(vector<int>bin1, vector<int> bin2) {
    vector_pad(bin1, bin2);
    int i=(int)bin1.size()-1;
    while (bin1[i]==bin2[i] && i>0)
        i--;
    if (bin1[i] == bin2[i])
        return 0;
    if (bin1[i]) // if they are different and this is a 1
        return 1;
    if (bin2[i]) // if they are different and this is a 1
        return -1;
    return -2; //can you even get here?
}

void vector_trim(vector<int> &v) {
    if (v.size() == 0)
        return;
    int i = (int)v.size()-1;
    while (v[i] == 0 && i>=0) {
        v.pop_back();
        i--;
    }
}

vector<int> modular_exponent(vector<int> x, vector<int> y, vector<int> N) {
    vector<int> result, quotient, remainder;
    result.push_back(1); // [1]
    
    for (int i=(int)y.size()-1;i>=0;i--) {
        /*cout << "result = ";
        printVec(result);*/
        result = binary_multiply(result, result);
        /*cout << "result = result^2 = ";
        printVec(result);*/
        if (y[i]) {
            result = binary_multiply(result, x); //for 1s, multiply by x as well
            /*cout << "necessary to multiply by x.\nresult = result * x = ";
            printVec(result);*/
        } /*else {
            cout << "result = ";
            printVec(result);
        }
        cout << "N = ";
        printVec(N);*/
        remainder.clear();
        quotient.clear(); //THIS BUG TOOK ME SO LONG TO FIND OMG
        binary_division(result, N, quotient, remainder);
        /*cout << "remainder of result/N (result mod N) = ";
        printVec(remainder);*/
        result = remainder;
    }
    
    return result;
}

//input: vector of ints, reversed binary
//output: vector of ints, reversed decimal
vector<int> binary_to_decimal(vector<int> bin) {
    vector<int> dec;
    if (bin.size() == 0)
        return dec;
    vector<int> z = bin; //copy of the binary vector, then divide it by 2 (erase the least significant digit)
    z.erase(z.begin());
    z = binary_to_decimal(z);
    dec = decimal_multiply_by_2(z);
    if (bin[0] == 1) { //if binary vector is odd
        if (dec.size() == 0)
            dec.push_back(1);
        else
            dec[0]++;
    }
    return dec;
}

//input: vector of ints, reversed decimal
//output: vector of ints, reversed decimal twice as large as input
vector<int> decimal_multiply_by_2(vector<int> decInput) {
    vector<int> result;
    bool carry = false;
    for (int i=0;i<decInput.size();i++) { //loop through the input vector from least significant digit to most significant digit
        if (decInput[i]*2 + carry > 9) {
            //cout << "carry needed\n";
            result.push_back(decInput[i]*2 % 10 + carry);
            carry = true;
        } else {
            //cout << "carry not needed\n";
            result.push_back(decInput[i]*2 + carry);
            carry = false;
        }
    }
    if (carry) {
        result.push_back(1);
    }
    return result;
}