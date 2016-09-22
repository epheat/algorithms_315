// Evan Heaton
// CS315 Homework 8

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>


using namespace std;

void printVec(vector<int> v);
int insertion_sort(vector<int> &v);
int quick_sort(vector<int> &v);
int quick(vector<int> &v, int left, int right, int &comparisons);
int partition(vector<int> &v, int j, int k, int &comparisons);
int merge_sort(vector<int> &v);
vector<int> merge(vector<int> x, vector<int> y, int &comparisons);
void split(vector<int> v, vector<int> &x, vector<int> &y, int partition);
vector<int> get_input_vector();

int main(int argc, const char * argv[]) {
    
    srand((int)time(NULL));
    
    int choice=0;
    
    while (choice<3 && choice >=-1) {
        cout
        << "which sorting algorithm:\n"
        << "0. insertion\n"
        << "1. merge\n"
        << "2. quick\n"
        << "3. quit (continue to large arrays)\n";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "invalid input\n";
        }
        else if (choice == 0) {
            vector<int> insertion = get_input_vector();
            printVec(insertion);
            cout << "\nneeded " << insertion_sort(insertion) << " comparisons for insertion sort\n";
            printVec(insertion);
            cout << "\n";
        }
        else if (choice == 1) {
            vector<int> merge = get_input_vector();
            printVec(merge);
            cout << "\nneeded " << merge_sort(merge) << " comparisons for merge sort\n";
            printVec(merge);
            cout << "\n";
        }
        else if (choice == 2) {
            vector<int> quick = get_input_vector();
            printVec(quick);
            cout << "\nneeded " << quick_sort(quick) << " comparisons for quick sort\n";
            printVec(quick);
            cout << "\n";
        }
        else if (choice == 3) {
        }
        else if (choice == 1337) {
            cout << "Kappa\n";
        }
        else {
            cout << "invalid input\n";
        }
        
    }
    
    
    
    
    cout << "\ndescending order: \n";
    for (int n=100;n<6500;n*=2) {
        vector<int> descending;
        for (int i=n;i>0;i--) {
            descending.push_back(i);
            //descending.push_back(i);
        }
        
        vector<int> descending_insertion = descending;
        vector<int> descending_merge = descending;
        vector<int> descending_quick = descending;
        
        cout << "n = " << n << "\n";
        cout << "needed " << insertion_sort(descending_insertion) << " comparisons for insertion sort\n";
        cout << "needed " << merge_sort(descending_merge) << " comparisons for merge sort\n";
        cout << "needed " << quick_sort(descending_quick) << " comparisons for quick sort\n";
        
    }
    
    cout << "\npress enter to continue to wacky order...";
    cin.ignore(256,'\n');
    cin.get();
    
    cout << "\nwacky order: \n";
    for (int n=100;n<6500;n*=2) {
        vector<int> wacky;
        for (int i=6;i>0;i--) {
            wacky.push_back(i);
        }
        for (int i=7;i<n-2;i++) {
            wacky.push_back(i);
        }
        for (int i=n;i>n-3;i--) {
            wacky.push_back(i);
            //descending.push_back(i);
        }
        if (n==100) {
            printVec(wacky);
            cout << "\n";
        }
        
        vector<int> wacky_insertion = wacky;
        vector<int> wacky_merge = wacky;
        vector<int> wacky_quick = wacky;
        
        cout << "n = " << n << "\n";
        cout << "needed " << insertion_sort(wacky_insertion) << " comparisons for insertion sort\n";
        cout << "needed " << merge_sort(wacky_merge) << " comparisons for merge sort\n";
        cout << "needed " << quick_sort(wacky_quick) << " comparisons for quick sort\n";
        
    }
    
    
    
    
    
    return 0;
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

int insertion_sort(vector<int> &v) {
    int comparisons = 0;
    for (int i=1;i<v.size();i++) {
        int k=i-1;
        int x=v[i];
        while (x<v[k] && k>=0) {
            v[k+1] = v[k];
            k--;
            comparisons++;
        }
        comparisons++;
        v[k+1]=x;
    }
    return comparisons;
}

int quick_sort(vector<int> &v) {
    int comparisons = 0;
    quick(v, 0, (int)v.size()-1, comparisons);
    
    return comparisons;
}

int quick(vector<int> &v, int left, int right, int &comparisons) {
    
    if (left < right) {
    
        int part = partition(v, left, right, comparisons);
    
        quick(v, left, part-1, comparisons);
        quick(v, part+1, right, comparisons);
    }
    
    return comparisons;
}

int partition(vector<int> &v, int left, int right, int &comparisons) {
    int pivot_index = (rand()%(right-left))+left;
    int pivot = v[pivot_index];
    
    //std::swap(v[pivot_index], v[left]);
    
    while (left < right) {
        while(v[left] < pivot) {
            left++;
        }
        
        while(v[right] > pivot) {
            right--;
        }
        if (v[left] == v[right]) {
            left++;
        }
        else if (left < right) {
            int swap_var = v[left];
            v[left] = v[right];
            v[right] = swap_var;
            
            
            //std::swap(v[left], v[right]);
        }
        comparisons++;
    }
    return right;
    
}

int merge_sort(vector<int> &v) {
    static int comparisons = 0;
    vector<int> left_part;
    vector<int> right_part;
    
    if (v.size() > 1) {
        split(v, left_part, right_part, (int)v.size()/2);
    
        merge_sort(left_part);
        merge_sort(right_part);
    
        v = merge(left_part, right_part, comparisons);
    }
    
    return comparisons;
}

vector<int> merge(vector<int> x, vector<int> y, int &comparisons) {
    if (x.size()==0)
        return y;
    if (y.size()==0)
        return x;
    
    vector<int> v;
    int i=0,j=0;
    while (i<x.size() && j<y.size()) {
        comparisons++;
        if (x[i]<y[j]) {
            v.push_back(x[i]);
            i++;
        }
        else if (y[j]<x[i]) {
            v.push_back(y[j]);
            j++;
        }
        else { //equal
            v.push_back(x[i]);
            v.push_back(x[i]);
            i++;
            j++;
        }
    }
    for (; i<x.size(); i++) {
        v.push_back(x[i]);
    }
    for (; j<y.size(); j++) {
        v.push_back(y[j]);
    }
    
    return v;
}

void split(vector<int> v, vector<int> &x, vector<int> &y, int partition) {
    
    for (int i=0;i<partition;i++) {
        x.push_back(v[i]);
    }
    for (int i=partition;i<v.size();i++) {
        y.push_back(v[i]);
    }
}

vector<int> get_input_vector() {
    vector<int> v;
    cout << "enter whitespace delimited integers, q to quit\n";
    int number;
    while (cin >> number) {
        v.push_back(number);
    }
    cin.clear();
    cin.ignore(256,'\n');
    return v;
}


