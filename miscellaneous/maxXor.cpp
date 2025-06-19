class trie
{
public:
    trie * next[2];
    int val,co;
    trie()
    {
        next[0]=next[1]=0;
        co=val=0;
    }
};
void insertt(trie * root, int val)
{
    trie* cur=root;
    cur->co++;
    for(int i=31;i>=0;i--)
    {
        bool bit=((1<<i)&val);
        if(cur->next[bit]==NULL)
        {
            cur->next[bit]=new trie();
        }
        cur=cur->next[bit];
        cur->co++;
    }
    cur->val=val;
}
void delnode(trie *root)
{
    if(root->next[0]!=NULL)delnode(root->next[0]);
    if(root->next[1]!=NULL)delnode(root->next[1]);
    delete root;
}
void delett(trie * root, int val)
{
    trie* cur=root;
    cur->co--;
    for(int i=31;i>=0;i--)
    {
        bool bit=((1<<i)&val);
        if(cur->next[bit]->co==1)
        {
            delnode(cur->next[bit]);
            cur->next[bit]=NULL;
            return ;
        }
        cur=cur->next[bit];
        cur->co--;
    }
}
int max_xor(trie * root, int val)
{
    trie* cur=root;
    if(cur->co==0)return -1;
    for(int i=31;i>=0;i--)
    {
        bool bit=((1<<i)&val);
        if(cur->next[1-bit]!=NULL)
        {
           cur=cur->next[1-bit];
        }else
        {
            cur=cur->next[bit];
        }
    }
    return val^cur->val;
}

