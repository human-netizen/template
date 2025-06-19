int c1[19],c2[19];
int dp[19][10][10][2][2];
int op[19][10][10][2][2];
int fun(int ind,int ma,int mi,bool ismi,bool isma)
{
    if(ind==19)return (ma-mi);
    int &ans=dp[ind][ma][mi][ismi][isma];
    if(ans!=-1)return ans;
    ans=10;
    int &oop=op[ind][ma][mi][ismi][isma];
    if(ismi&&isma)
    {
 
        for(int i=c1[ind]; i<=c2[ind]; i++)
        {
            int tem;
            if(mi+ma==0)
            {
                tem=fun(ind+1,i,i,i==c1[ind],i==c2[ind]);
            }
            else
            {
                tem=fun(ind+1,max(ma,i),min(mi,i),i==c1[ind],i==c2[ind]);
            }
            if(tem<ans)
            {
                ans=tem;
                oop=i;
            }
        }
    }
    else if(ismi)
    {
 
        for(int i=c1[ind]; i<=9; i++)
        {
            int tem;
            if(mi+ma==0)
            {
                tem=fun(ind+1,i,i,i==c1[ind],0);
            }
            else
            {
                tem=fun(ind+1,max(ma,i),min(mi,i),i==c1[ind],0);
            }
            if(tem<ans)
            {
                ans=tem;
                oop=i;
            }
        }
        //cout<<2<<"->";
    }
    else if(isma)
    {
        for(int i=0; i<=c2[ind]; i++)
        {
            int tem;
            if(mi+ma==0)
            {
                tem=fun(ind+1,i,i,0,i==c2[ind]);
            }
            else
            {
                tem=fun(ind+1,max(ma,i),min(mi,i),0,i==c2[ind]);
            }
            if(tem<ans)
            {
                ans=tem;
                oop=i;
            }
        }
        //cout<<3<<"->";
    }
    else
    {
 
        for(int i=0; i<=9; i++)
        {
            int tem;
            if(mi+ma==0)
            {
                tem=fun(ind+1,i,i,0,0);
            }
            else
            {
                tem=fun(ind+1,max(ma,i),min(mi,i),0,0);
            }
            if(tem<ans)
            {
                ans=tem;
                oop=i;
            }
        }
        //cout<<4<<"->";
    }
    //cout<<ind<<" "<<ma<<" "<<mi<<" "<<isma<<" "<<ismi<<" "<<ans<<"\n";
    return ans;
}

