#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    
    vector<int> fibo;
    
    for (int i = 0; i <= n; i++) {
        if (i == 0) fibo.push_back(0);
        else if (i == 1) fibo.push_back(1);
        else fibo.push_back((fibo[i-1] + fibo[i-2]) % 1234567);
    }
    
    answer = fibo[fibo.size()-1];
    
    return answer;
}