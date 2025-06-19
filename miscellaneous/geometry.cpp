bool is_cross(ld a,ld b,ld c,int x1,int y1,int x2,int y2)
{
    ld f1=a*x1+b*y1+c;
    ld f2=a*x2+b*y2+c;
    if(f1<0&&f2<0)return 0;
    if(f1>0&&f2>0)return 0;
    return 1;
}
pair<ld,ld>cross_point(ld a ,ld b,ld c,ld aa,ld bb,ll cc)
{
    ld xx=(cc*b/bb-c)/(a-aa*b/bb);
    ld yy=(-c-a*xx)/b;3
    return {xx,yy};
}
ld dis(ld x1,ld y1,ld x2,ld y2)
{
    return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}