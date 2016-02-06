#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Segm
{
    int X;
    int Vid;
};
void Sort(Segm *S, int K);
int main()
{
    int M, N, i, j, K, L;
    long Lp;
    K = -1;
    cin >> N;
    Segm* S = new Segm[2*N];
    for(int i = 0; i< N; i++)
    {
        K = K + 2;
        cin >> S[K-1].X >> S[K].X;
        S[K-1].Vid = 1;
        S[K].Vid = -1;
    }
    Sort(S,K);
    Lp = 0;
    M = 0;
    for(int i = 0; i < K;i++)
    {
       M = M + S[i].Vid;
       if((M == 1)&&(S[i].Vid = 1)) L = S[i].X;
       if((M == 0)&&(S[i].Vid = -1)) Lp = Lp + S[i].X - L;
    }
    cout << Lp;

    return 0;
}

void Sort(Segm *S, int K)
{
    Segm B;
    for(int i = 2; i < K;i++)
    {
        for(int j = K; j > i; j=j-1)
        {
            if(S[j].X<S[j-1].X)
            B=S[j];
            S[j] = S[j-1];
            S[j-1] = B;
        }
    }


}
