*****************Online***************
struct node
{
    ll val;
    node *left,*right;
    node()
    {
        val=0;
        left=NULL;
        right=NULL;
    }
};
ll updd(ull i,ull n,ull ind,ll val,node *cur)
{
    if(i==n) return cur->val=val;
    ull mid=n-i;
    mid=i+mid/2;
    if(ind<=mid)
    {
        if(cur->left==NULL)cur->left=new node();
        updd(i,mid,ind,val,cur->left);
    }else
    {
        if(cur->right==NULL)cur->right=new node();
        updd(mid+1,n,ind,val,cur->right);
    }
    return cur->val=(cur->left==NULL?0:cur->left->val)+(cur->right==NULL?0:cur->right->val);
}
ll ansd(ull i,ull n,ull p,ull q,node *cur)
{
    if(cur==NULL)return 0;
    if(n<p||i>q)return 0;
    if(i>=p&&n<=q)
    {
        return cur->val;
    }
    ull mid=n-i;
    mid=i+mid/2;
    return ansd(i,mid,p,q,cur->left)+ansd(mid+1,n,p,q,cur->right);
}


*****************online persistant***************
void persist(ull i,ull n,ull ind,ll val,node *cur,node *pre)
{
    if(pre==NULL)
    {
        updd(i,n,ind,val,cur);
        return ;
    }
    if(i==n)
    {
        cur->val=val;
        return ;
    }
    ull mid=n-i;
    mid=i+mid/2;
    if(ind<=mid)
    {
        cur->right=pre->right;
        cur->left=new node();
        persist(i,mid,ind,val,cur->left,pre->left);
    }
    else
    {
        cur->left=pre->left;
        cur->right=new node();
        persist(mid+1,n,ind,val,cur->right,pre->right);
    }
    cur->val=(cur->left==NULL?0:cur->left->val)+(cur->right==NULL?0:cur->right->val);
}