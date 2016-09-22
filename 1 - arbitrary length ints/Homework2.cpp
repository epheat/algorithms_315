//Evan Heaton
//CS315 - Homework 2
//9-14-15
//http://www.cs.uky.edu/~mirek/class-materials/315/fa15/hmwk-2.pdf

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void printVec(vector<int> v);
vector<int> decimal_multiply_by_2(vector<int> decInput);
vector<int> binary_to_decimal(vector<int> bin);
vector<int> base2k_to_binary(vector<int> base2k, int base);
vector<int> lookup(int digit);
vector<int> binary_multiply_by_ten(vector<int> bin);
vector<int> binary_add(vector<int> bin1, vector<int> bin2);
vector<int> decimal_to_binary(int decimal, int k);
vector<int> recursive_decimal_to_binary(int decimal);
int power_squat(int base, int exp);
vector<int> base2k_add(vector<int> v1, vector<int> v2, int k);

int main(int argc, char *argv[]) {
    ifstream problem1("problem1.txt");
    ifstream problem2("problem2.txt");
    ifstream problem3("problem3.txt");
    
    vector<int> p1a, p1b, p1c, p1d, p2a, p2b, p3a1, p3a2, p3b1, p3b2, p3c1, p3c2;
    int temp;
    while (problem1 >> temp)
        p1a.push_back(temp);
    problem1.clear();
    problem1.ignore(256, '\n');
    printVec(p1a);
    printVec(binary_to_decimal(p1a));
    
    while (problem1 >> temp)
        p1b.push_back(temp);
    problem1.clear();
    problem1.ignore(256, '\n');
    printVec(p1b);
    printVec(binary_to_decimal(p1b));
    
    while (problem1 >> temp)
        p1c.push_back(temp);
    problem1.clear();
    problem1.ignore(256, '\n');
    printVec(p1c);
    printVec(binary_to_decimal(p1c));
    
    while (problem1 >> temp)
        p1d.push_back(temp);
    problem1.clear();
    problem1.ignore(256, '\n');
    printVec(p1d);
    printVec(binary_to_decimal(p1d));
    
    problem1.close();
    
    //NOW FOR PROBLEM 2
    
    while (problem2 >> temp)
        p2a.push_back(temp);
    problem2.clear();
    problem2.ignore(256, '\n');
    problem2 >> temp;
    problem2.clear();
    problem2.ignore(256, '\n');
    printVec(p2a);
    printVec(base2k_to_binary(p2a, temp));
    
    while (problem2 >> temp)
        p2b.push_back(temp);
    problem2.clear();
    problem2.ignore(256, '\n');
    problem2 >> temp;
    problem2.clear();
    problem2.ignore(256, '\n');
    printVec(p2b);
    printVec(base2k_to_binary(p2b, temp));
    
    problem2.close();
    
    //NOW FOR PROBLEM 3
    while (problem3 >> temp)
        p3a1.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    while (problem3 >> temp)
        p3a2.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    problem3 >> temp;
    problem3.clear();
    problem3.ignore(256, '\n');
    //printVec(p3a1);
    printVec(p3a2);
    printVec(base2k_add(p3a1, p3a2, temp));
    
    while (problem3 >> temp)
        p3b1.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    while (problem3 >> temp)
        p3b2.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    problem3 >> temp;
    problem3.clear();
    problem3.ignore(256, '\n');
    printVec(p3b1);
    printVec(p3b2);
    printVec(base2k_add(p3b1, p3b2, temp));
    
    while (problem3 >> temp)
        p3c1.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    while (problem3 >> temp)
        p3c2.push_back(temp);
    problem3.clear();
    problem3.ignore(256, '\n');
    problem3 >> temp;
    problem3.clear();
    problem3.ignore(256, '\n');
    printVec(p3c1);
    printVec(p3c2);
    printVec(base2k_add(p3c1, p3c2, temp));
    
    
    
    /*
    vector<int> v1, v2;
    int temp, k;
    while (problem3 >> temp) {
        v1.push_back(temp);
    }
    problem3.clear();
    problem3.ignore(256, '\n');
    while (problem3 >> temp) {
        v2.push_back(temp);
    }
    problem3.clear();
    problem3.ignore(256, '\n');
    problem3 >> k;
    printVec(v1);
    printVec(v2);
    printVec(base2k_add(v1, v2, k));
    */

    return 0;
}

void printVec(vector<int> v) { //just to print vectors for debugging purposes
	cout << "[";
	for (int i=0;i<v.size()-1;i++)
		cout << v[i] << ", ";
	cout << v[v.size()-1] << "]\n";
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

vector<int> base2k_to_binary(vector<int> base2k, int k) {
    vector<int> result;
    for (int i=0;i<base2k.size();i++) {
        vector<int> temp = decimal_to_binary(base2k[i], k); // turn elements in base2k vector to binary vectors
        //
        //  5    4    3    7
        // 101  100  011  111
        //******************** represented as
        // [7]  [3]  [4]  [5]
        //[111][110][001][101]
        //   [111110001101]
        //
        for(int j=0;j<k;j++) { //place binary bits into the result vector
            result.push_back(temp[j]);
        }
    }
    return result;
}

vector<int> decimal_to_binary(int decimal, int k) {
    vector<int> binary;
    for (int i=k-1;i>=0;i--) {
        if (decimal >= power_squat(2, i)) {
            decimal -= power_squat(2, i);
            binary.insert(binary.begin(),1);
        } else {
            binary.insert(binary.begin(),0);
        }
    }
    return binary;
}

int power_squat(int base, int exp) { //WHYYYY
    int result = 1;
    for (int i=0;i<exp;i++) {
        result *= base;
    }
    return result;
}

vector<int> recursive_decimal_to_binary(int decimal) {
    vector<int> binary_result, decimal_vec;
    //do I need to convert this integer to a vector of integer digits? NEVER!!
    if (decimal == 0)
        return binary_result;
    vector<int> temp = recursive_decimal_to_binary(decimal/10); //chop off the last digit
    binary_result = binary_multiply_by_ten(temp);
    binary_result = binary_add(binary_result, lookup(decimal));
    
    return binary_result;
}

//input: integer from 0-9
//output: vector of ints, reversed binary of that decimal digit
vector<int> lookup(int digit) {
    
    vector<vector<int>> ZERO_TO_NINE_TABLE(10); //Lookup table for digits 0-9 in binary
    bool one = true, two = true, four = true, eight = true; //to count
    for (int i=0;i<10;i++) {
        
        if (true) //flip "one"
            one = !one;
        if (i%2 == 0) //flip "two"
            two = !two;
        if (i%4 == 0) //flip "four"
            four = !four;
        if (i%8 == 0) //flip "eight"
            eight = !eight;
        
        ZERO_TO_NINE_TABLE[i].push_back(one);
        ZERO_TO_NINE_TABLE[i].push_back(two);
        ZERO_TO_NINE_TABLE[i].push_back(four);
        ZERO_TO_NINE_TABLE[i].push_back(eight);
    }
    return ZERO_TO_NINE_TABLE[digit];
}

//input: vector of ints, reversed binary
//output: vector of ints, reversed binary multiplied by 1010
vector<int> binary_multiply_by_ten(vector<int> bin) {
    vector<int> binary_result, times_2 = bin, times_8 = bin;
    times_2.insert(times_2.begin(), 0); //multiply by 2
    times_8.insert(times_8.begin(), 0);
    times_8.insert(times_8.begin(), 0);
    times_8.insert(times_8.begin(), 0); //multiply by 8
    
    binary_result = binary_add(times_2, times_8);
    return binary_result;
}

vector<int> binary_add(vector<int> bin1, vector<int> bin2) {
    vector<int> binary_result;
    bool bin1smaller = false;
    //cout << bin1.size() << " " << bin2.size() << " ";
    if (bin1.size() < bin2.size())
        bin1smaller = true;
    if (bin1smaller) {
        for (int i=0;i<(bin2.size()-bin1.size());i++) {
            bin1.push_back(0);
            //cout << "padded bin1";
        }
    } else {
        for (int i=0;i<(bin1.size()-bin2.size());i++) {
            bin2.push_back(0);
            //cout << "padded bin2";
        }
    } //FINISHED PADDING
    
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
    
    if (carry)
        binary_result.push_back(1);

    return binary_result;
}

vector<int> base2k_add(vector<int> v1, vector<int> v2, int k) {
    vector<int> result;
    bool v1smaller = false;
    //cout << v1.size() << " " << v2.size() << " ";
    if (v1.size() < v2.size())
        v1smaller = true;
    if (v1smaller) {
        int diff = v2.size()-v1.size();
        for (int i=0;i<diff;i++) {
            v1.push_back(0);
            //cout << "padded v1";
        }
    } else {
        int diff = v1.size()-v2.size();
        for (int i=0;i<diff;i++) {
            v2.push_back(0);
            //cout << "padded v2";
        }
    } //FINISHED PADDING
    
    bool carry = false;
    int addition;
    for(int i=0;i<v1.size();i++) {
        addition = v1[i] + v2[i] + carry;
        if (addition > (power_squat(2, k) - 1)) {
            result.push_back(addition%power_squat(2, k));
            carry = true;
        } else {
            result.push_back(addition);
            carry = false;
        }
    }
    if (carry)
        result.push_back(1);
    
    return result;
}
