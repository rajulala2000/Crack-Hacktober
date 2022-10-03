#include <bits/stdc++.h>
using namespace std;

int kadane(int n, int temp[], int& top, int& bottom){
    bottom  = -1;
    int maxsum = INT_MIN, sum = 0, start = 0;
    for(int i=0; i<n; i++){
        sum+=temp[i];
        if(sum<0){
            sum=0, start = i+1;
        }
        if(sum>maxsum){
            maxsum = sum;
            top = start, bottom = i;
        }
    }
    if(bottom!=1) return maxsum;
    //finding max element
    for(int i=0; i<n; i++){
        if(temp[i]>maxsum){
            maxsum = temp[i];
            top = bottom = i;
        }
    }
    return maxsum;
}

void kadane_2D(int n, int m, vector<vector<int>>& a){
    int maxsum = INT_MIN;    //will store the max sum of subarray
    int maxleft,maxright,maxtop,maxbottom;  //store the left,right,top and bootom index of max sum subarray
    int temp[n];    //will store the sum of rows elements from col left to right

    for(int left=0; left<m; left++){
        memset(temp,0,sizeof(temp)); //temp[i] = 0 at starting of every submatrix iteration
        for(int right=left; right<m; right++){
            for(int i=0; i<n; i++) temp[i]+=a[i][right];    //increasing size of subarray in horizontal axis

            int top,bottom;
            //applying kadane's algo in 1D vertically with sum of horizontal values
            int sum = kadane(n,temp,top,bottom);

            if(sum>maxsum){
                maxsum = sum;
                maxtop = top, maxbottom = bottom, maxleft = left, maxright = right;
            }
        }
    }

    cout<<"Maximum sum subarray starts from ("<<maxtop<<","<<maxleft<<") and ends at ("<<maxbottom<<","<<maxright<<") with dimensions ("<<(maxbottom-maxtop+1)<<","<<(maxright-maxleft+1)<<") and with max sum = "<<maxsum<<endl;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin>>a[i][j];
    }

    kadane_2D(n,m,a);
}
