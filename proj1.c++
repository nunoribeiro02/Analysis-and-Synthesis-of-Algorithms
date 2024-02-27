#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> readinput();
vector<int> readinput_map(unordered_map<int, bool> *um);
vector<int> processinput(unordered_map<int, bool> *um);
bool binarySearch(vector<int> vec, int l, int r, int x);
void problem1(vector<int> sequence);
void problem2(vector<int> seq1, vector<int> seq2);

int main() {
    
    int problem;
    if (scanf("%d", &problem) > 0){
        getchar();

        if (problem == 1) {
            vector<int> sequence = readinput();
    
            problem1(sequence);  
        }
        else if (problem == 2){
            
            unordered_map<int, bool>* um = new unordered_map<int, bool>();
            vector<int> sequence1 = readinput_map(um);

            vector<int> sequence2 = processinput(um);

            /*
            for (int x: sequence2){
                cout << x << endl;
            }
            
            vector<int> sequence3(sequence1.size() + sequence2.size());

            iterator to store return type
            vector<int>::iterator it, end;

            
            end = set_intersection(
            sequence1.begin(), sequence1.end(),
            sequence2.begin(), sequence2.end(),
            sequence3.begin());
            */
            
            problem2(sequence1, sequence2);
        }
    }

    return 0;
}

vector<int> readinput(){
    char c; int num;
    vector<int> sequence = vector<int>();
    if (scanf("%d", &num) > 0){
        sequence.push_back(num);
        while ((c = getchar()) != '\n'){
            if (scanf("%d", &num) > 0)
                sequence.push_back(num);
        }
    }
    return sequence;
}

vector<int> readinput_map(unordered_map<int, bool>* um){
    char c; int num;
    unordered_map<int, bool> &map = *um;
    vector<int> sequence = vector<int>();
    if (scanf("%d", &num) > 0){
        sequence.push_back(num);
        // um->insert(make_pair(num, true));
        // um->at(num) = true;
        map[num] = true;

        while ((c = getchar()) != '\n'){
            if (scanf("%d", &num) > 0){
                sequence.push_back(num);
                // um->insert(make_pair(num, true));
                // um->at(num) = true;
                // map.insert(make_pair(num, true));
                map[num] = true;

            }
        }
    }
    return sequence;
}

vector<int> processinput(unordered_map<int, bool>* um){
    char c; int num;
    vector<int> sequence = vector<int>();
    auto& map = *um;
    if (scanf("%d", &num) > 0){
        if (map.find(num) != map.end()){
                sequence.push_back(num);
            }
        
        while ((c = getchar()) != '\n'){
            if (scanf("%d", &num) > 0){
                if (map.find(num) != map.end()){
                    sequence.push_back(num);
                }
            }
        }
    }
    return sequence;
}

/*
vector<int> processinput(vector<int> vec){
    char c; int num;
    vector<int> sequence = vector<int>();
    int size = vec.size();

    sort(vec.begin(), vec.end());
    if (scanf("%d", &num) > 0){
        for (int i = 0; i < size; i++){
            if (vec[i] == num){
                sequence.push_back(num);
                break;
            }
        }
        while ((c = getchar()) != '\n'){
            if (scanf("%d", &num) > 0){
                for (int i = 0; i < size; i++){
                    if (vec[i] == num){
                        sequence.push_back(num);
                        break;
                    }
                }
            }
        }
    }
    return sequence;
}
*/

bool binarySearch(vector<int> vec, int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (vec[mid] == x)
            return true;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (vec[mid] > x)
            return binarySearch(vec, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(vec, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return false;
}

void problem1(vector<int> sequence){
    //Function to count the number
// of LIS in the array nums[]

    //Store the maximum element
    // from dp_l
    int max_length = 0;

    //Stores the count of LIS
    int count = 0;

    int n = sequence.size();

    //Initialize dp_l array with
    // 1s
    vector<int> dp_l(n, 1);

    //Initialize dp_c array with
    // 1s
    vector<int> dp_c(n, 1);

    for (int i = 0; i < n; i++)
    {   
        int test = dp_l[i];
        int diogo = dp_c[i];
        for (int j = 0; j < i; j++)
        {
            //If current element is
            // smaller
            int jorge = dp_l[j];
            int nuno = dp_c[j];
            if (sequence[i] > sequence[j]){ 
                if (jorge + 1 > test)
                {
                    test = jorge + 1;
                    diogo = nuno;
                }
                else if (jorge + 1 == test)
                    diogo += nuno;
            }
        }

        dp_l[i] = test;
        dp_c[i] = diogo;
        
        if (test == max_length)
            count += diogo;
        else if (test > max_length){
            max_length = test;
            count = diogo;
        }
    }

    printf("%d %d\n", max_length, count);
    
    return;  
}

void problem2(vector<int> seq1, vector<int> seq2){

        // table[j] is going to store length of LCIS 
    // ending with seq2[j]. We initialize it as 0, 
    int n = seq1.size();
    int m = seq2.size();

    // The maximum value in table[] is out result 
    int result = 0; 

    int table[m]; 
    for (int j=0; j<m; j++) 
        table[j] = 0; 
  
    // Traverse all elements of seq1[] 
    for (int i=0; i<n; i++) 
    { 
        // Initialize current length of LCIS 
        int current = 0; 
        
        // For each element of seq1[], traverse all 
        // elements of seq2[]. 
        for (int j=0; j<m; j++) 
        {   
            int dezasete = table[j];
            // If both the array have same elements. 
            // Note that we don't break the loop here. 
            if (seq1[i] == seq2[j]) 
                if (current + 1 > dezasete) {
                    dezasete = current + 1; 
                    table[j] = dezasete;
                }

            /* Now seek for previous smaller common 
               element for current element of seq1 */
            if (seq1[i] > seq2[j]) 
                if (dezasete > current) 
                    current = dezasete; 

            if (dezasete > result) 
                result = dezasete;
    
        } 
    } 

    printf("%d\n", result);
    return;
}

