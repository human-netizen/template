int movious[N];
void make()
{
    for(int i=0;i<N;i++)movious[i]=0;
    movious[1]=1;
    for(int i=1;i<N;i++)
    {
        for(int j=i+i;j<N;j+=i)movious[j]-=movious[i];
    }
}