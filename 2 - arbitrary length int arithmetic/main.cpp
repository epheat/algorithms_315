//Evan Heaton
//CS315 - Homework 3
//9-29-15
//http://www.cs.uky.edu/~mirek/class-materials/315/fa15/hmwk-3.pdf

//111100011010
//111111011

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void printVec(vector<int> v);
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
    
    ifstream input(argv[1]);
    vector<int> x1, x2, y1, y2;
    int temp;
    
    while (input >> temp)
        x1.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        y1.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        x2.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        y2.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    
    cout << "x1 = ";
    printVec(x1);
    cout << "y1 = ";
    printVec(y1);
    cout << "x2 = ";
    printVec(x2);
    cout << "y2 = ";
    printVec(y2);
    cout << "x1 - y1 = ";
    printVec(binary_subtract(x1, y1));
    cout << "x2 - y2 = ";
    printVec(binary_subtract(x2, y2));
    
    vector<int> q1, q2, r1, r2;
    
    cout << "\nx1 * y1 = ";
    printVec(binary_multiply(x1, y1));
    cout << "x2 * y2 = ";
    printVec(binary_multiply(x2, y2));
    cout << "x1 / y1 = ";
    binary_division(x1, y1, q1, r1);
    printVec(q1);
    cout << "with remainder: ";
    printVec(r1);
    cout << "x2 / y2 = ";
    binary_division(x2, y2, q2, r2);
    printVec(q2);
    cout << "with remainder: ";
    printVec(r2);
    
    
    //Now for problem 3 input stuff
    vector<int> N3, x3, y3, N4, x4, y4;
    while (input >> temp)
        N3.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        x3.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        y3.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        N4.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        x4.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    while (input >> temp)
        y4.push_back(temp);
    input.clear();
    input.ignore(256, '\n');
    
    cout << "\nN3 = ";
    printVec(N3);
    cout << "x3 = ";
    printVec(x3);
    cout << "y3 = ";
    printVec(x1);
    cout << "N4 = ";
    printVec(x1);
    cout << "x4 = ";
    printVec(x1);
    cout << "y4 = ";
    printVec(x1);
    
    cout << "x3^y3(modN3) = ";
    printVec(modular_exponent(x3, y3, N3));
    cout << "x4^y4(modN4) = ";
    printVec(modular_exponent(x4, y4, N4));
    
    
    time_t t1, t2;
    
    for (int n=100;n<12801;n*=2) {
        
        vector<int> LargeN, LargeX, LargeY;
        LargeN.push_back(1);
        LargeN.push_back(1);
        LargeN.push_back(1);
        for (int i=0;i<n;i++)
            LargeN.push_back(0);
        for (int i=0;i<n;i++)
            LargeN.push_back(1);
        LargeN.push_back(0);
        LargeN.push_back(1);
        
        LargeX.push_back(1);
        LargeX.push_back(0);
        LargeX.push_back(1);
        for (int i=0;i<n;i++)
            LargeX.push_back(0);
        for (int i=0;i<n;i++)
            LargeX.push_back(1);
        
        LargeY.push_back(1);
        LargeY.push_back(1);
        for (int i=0;i<n;i++)
            LargeY.push_back(1);
        for (int i=0;i<n;i++)
            LargeY.push_back(0);
        LargeY.push_back(1);
        //generation done
        
        t1 = time(0);
        //printVec(binary_multiply(LargeX, LargeY));
        binary_multiply(LargeX, LargeY);
        t2 = time(0);
        printf("Time elapsed (multiplication): %ld seconds ", t2 - t1);
        cout << "for n = " << n << "\n";
        
        if (n<=400){
            t1 = time(0);
            //modular_exponent(LargeX, LargeY, LargeN);
            t2 = time(0);
            printf("Time elapsed (modular exponentiation): %ld seconds ", t2 - t1);
            cout << "for n = " << n << "\n";
        }
    }
}

void printVec(vector<int> v) { //just to print vectors for debugging purposes
    cout << "[";
    if (v.size()==0)
        cout << "]\n";
    else {
        for (int i=0;i<v.size()-1;i++)
            cout << v[i] << ", ";
        cout << v[v.size()-1] << "]\n";
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