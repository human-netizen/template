vector<int>mul(vector<int>ddd,int k)  //k<=10
{
    int pre=0;
    vector<int>ans;
    for(int i=0; i<ddd.size(); i++)
    {
        int tem=ddd[i]*k+pre;
        ans.push_back(tem%10);
        pre=tem/10;
    }
    if(pre>0)
    {
        ans.push_back(pre);
    }
    return ans;
}
vector<int>plu(vector<int>ddd,vector<int>eee)
{
    vector<int>ans;
    int pre=0;
    for(int i=0;i<max(ddd.size(),eee.size());i++)
    {
        int cur=pre;
        if(i<ddd.size())
        {
            cur+=ddd[i];
        }
        if(i<eee.size())
        {
            cur+=eee[i];
        }
        ans.push_back(cur%10);
        pre=cur/10;
    }
    if(pre>0)
    {
        ans.push_back(pre);
    }
    return ans;
}