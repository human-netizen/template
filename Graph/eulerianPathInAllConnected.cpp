for(int i=0; i<ans; i++)
        {
            cal[i]=i;
            for(int j=0; j<ans; j++)tra[i][j]=0;
        }
inds.clear();
inds.push_back(0);
fun(0,ans);
//fun
vector<int>inds;
int cal[P];
void fun(int cur,int ans)
{
    while(1)
    {
        if(tra[cur][cal[cur]]==0)
        {
            int i=cal[cur];
            inds.push_back(i);
            tra[cur][i]=1;
            tra[i][cur]=1;
            fun(i,ans);
            return ;
        }
        cal[cur]=(cal[cur]+1)%ans;
        if(cal[cur]==cur)break;
    }
}