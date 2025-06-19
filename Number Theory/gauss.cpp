const ld M=1e-5;
const int N=102;
//tem
long double ans[N];
long double mat[N][N];
int n;
void rswap(int i,int j)
{
    if(i==j)return ;
    for(int k=1; i<=n+1; k++)
    {
        long double tem=mat[i][k];
        mat[i][k]=mat[j][k];
        mat[j][k]=tem;
        //swap(mat[i][k],mat[j][k]);
    }
}
int fun()
{
    int tot=1;
    for(int j=1; j<=n; j++)
    {
        int p=0;
        for(int i=tot; i<=n; i++)
        {
            if(abs(mat[i][j])>M)
            {
                p=i;
                break;
            }
        }
        if(p)
        {
            rswap(tot,p);
            for(int i=tot+1; i<=n; i++)
            {
                if(abs(mat[i][j])>M)
                {
                    long double mag=mat[i][j]/mat[tot][j];
                    for(int k=j; k<=n+1; k++)
                    {
                        mat[i][k]=mat[i][k]-mag*mat[tot][k];
                        if(abs(mat[i][k])<M)mat[i][k]=0;
                    }
                }
            }
            tot++;
        }
    }
    ans[n+1]=-1;
    for(int i=n; i>=1; i--)
    {
        for(int j=i; j<=n; j++)
        {
            if(abs(mat[i][j])>M)
            {
                long double sum=0;
                for(int k=j+1; k<=n+1; k++)
                {
                    sum=sum+mat[i][k]*ans[k];
                }
                sum=-sum;
                ans[j]=sum/mat[i][j];
                break;
            }
        }
    }
    return tot;
}

