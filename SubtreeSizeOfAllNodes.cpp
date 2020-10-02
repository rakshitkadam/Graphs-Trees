
 PUSHING STYLE==>
   for(ll i=0;i<n;i++)
    {
        ll a;cin>>a;
        tree[i+n]=a;
    }

ll tree[2*MAX];ll n;


REMEMBER TO CALL THE BUILD FUNCTION ...
REMEMBER THE QUERY IS FOR [L,R) LEFT INCLUSIVE ,RIGHT EXCLUSIVE
===========================================================================
void build()
{
    for(ll i=n-1;i>0;i--)
    {
        
        tree[i]=tree[i<<1] +  tree[i<<1|1];
        
                  //MODIFY THE SIGN AS PER NEED;
    }
}
void modify(ll val ,ll pos)
{
    
    for(tree[pos+=n]=val;pos>1;pos>>=1)
    {
        tree[pos>>1]=tree[pos]  +   tree[pos^1];
                            //MODIFY THE SIGN AS PER NEED;
    }
}
ll query(ll l,ll r)
{
// for querying [1,2]use 0,2 
    ll res=0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1)res+=tree[l++];
        if(r&1)res+=tree[--r];
    }
    return res;
}
================================================================================
LAZY PROPAGATION IN SEGMENT TREES , RANGE UPDATE AND RANGE QUERY
ARRAY OF NODES IS DECLARED OF SIZE 4*N AS N ELEMENT ,N-1 IN TOTAL ELEMENT ABOVE IT AS IF N=4,SO 1,2,WILL BE THEIR
   1
 2   3
4 5 6 7
ABOVE 1,2,3 REQUIRED THE N-1 AND AFTER THAT FOR PROPAGATING PURPOSE ,AS WE WANT TO KEEP THE ALGORITHM GENERALIZE SO WE ADD ANOTHER 
EG. 
			1
		   2	    3
	       4    5   6	  7
          8  9  10   11   12  13  14  15
THE NUMBERS FROM 8-15 DONT CONRTIBUTE IN ANYTHING ....BUT HERE 2*N MORE ELEMENTS ARE REQUIRED

REMEMBER UNLIKE THE ABOVE SEGMENT TREE THE QUERY IS  UPDATE[..,L,R,..] L INCLUSIVE AND R INCLUSIVE .
================================================================================
struct node{
    ll val,laze;
    node()
    {
        val=laze=0;
    }
};
ll pos[MAX];
node tree[4*MAX];
//WHAT BUILD DOES IN THE BELOW CODE IS THAT WE PASS BUILD THE PARAMETER BUILD(1,1,END);...
//NOTE THAT HERE U HAVE TO STORE ARRAYS IN 1 INDEXING AND SUPPOSE U HAVE TO ALLOCATE THE VALUES TO THE NODES WHICH CONTAIN INFORMATION OF ONE NODE ,SO THEIR L==R ,BUT HOW TO GET THE INDEX WHERE SUCH NODES ARE PRESENT SO WE PASS 1,SO IF WE GO TO LEFT AND RIGHT CHILD WE GET THE NUMBER... AND THEN STORE THE VALUE

// call build(1,1,n) in main()...
// in lazy propagation -> numbering starts from 1, so for quay provide original numbers not subtracted by 1..
void build(ll num,ll l ,ll r)
{

    if(l==r)
    {
        tree[num].val = //YOUR ARRAY VALUE...;
	return;
    }
    ll mid = l+r>>1;
    build(num<<1,l,mid);
    build(num<<1|1,mid+1,r);
    push_up(num,l,r);
}
void  go(ll l,ll r,ll i,ll val,ll x)
{
// here val,and x are added to val and laze ,such that ,tree[I].val gets the equivalent addition on values considering l,r range and val->value and x->value..

    
    tree[i].val += (r-l+1)*val+((r*(r+1))/2 -((l)*(l-1))/2)*x;
    tree[i].laze += val;
    tree[i].is += x;
}
void push_down(ll pos,ll l,ll r)
{
    ll mid =l+r>>1;
    go(l,mid,pos<<1,tree[pos].laze,tree[pos].is);
    go(mid+1,r,pos<<1|1,tree[pos].laze,tree[pos].is);
    tree[pos].laze =0;
    tree[pos].is =0;
}
 
void push_up(ll pos,ll l,ll r)
{
//L AND R ARE NOT OF ANY USE HERE..
// USED WHEN U HAVE PROPAGATED THE VALUE SO U HAVE TO UPDATE THIS NODE WITH CORRESPONDING TO ITS CHILD...
    tree[pos].val=tree[pos<<1].val+tree[pos<<1 |1].val;
       // INSTEAD OF MAX YOU CAN DO ANY OPERATION AS YOU WISH BUT ACCORDINGLY WHAT WILL BE OPERATED IS TO HANDLED
}
ll sum(ll v, ll tl, ll tr, ll l, ll r) {
// pass as query(1,1,n,range_left,range_right )range_left,right pass as it is ,don't subtract 1 from it,  
  if (l > r)
        return 0;
    if (l <= tl && r >= tr) {
        return tree[v].val;
    }
    int tm = (tl + tr) / 2;
 push_down(v<<1,tl,tl+tr>>1);
    push_down(v<<1|1,(tl+tr>>1)+1,tr);
//here tl and tr are the ranges which are cutting from 1,n as u proceed...
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
//note here min(r,tm) and similarly max(..,..) is used and l>r is used to eliminate the unrequited part...
}
void update(ll pos,ll l ,ll r,ll L,ll R,ll val)
{
//HOW TO USE: IN MOST OF THE CASES WE PASS FIRST THREE PARAMETERS:posl,R AS 1,1,R(YOUR END)...L AND R IS THE RANGE U HAVE TO UPDATE WITH VALUE VAL AS THE UPDATE FUNCTION ONLY UPDATES THE NODES WHICH LIE IN INTERVAL... 
    if(L<=l && R>=r)
    {
        tree[pos].laze+=val;
        tree[pos].val+=val;
        return;
    }
    push_down(pos,l,r);
    //PROPAGATING THE LAZE OTHER THAN VAL IF  PRESENT IN THE POS ,SO ITS GETS PROPAGATED IN THE CHILDREN


    ll mid=(l+r)>>1;
    if(L<=mid)update(pos<<1,l,mid,L,R,val);
    if(mid<R)update( pos<<1 | 1,mid+1,r,L,R,val);
    push_up(pos,l,r);
}

// we pass 1,n as our range and L,R are the range where certain operation is to be done , so our 1,n range gets short listed as we go on and see whether our current range lies in the given range or not...thats why is sum(queries ) we check from 1,n if not then we first propagate our laziness so that no laziness is pending from this node, we push_down it and then again check for those two ranges which we get by seperating it from mid...


PRACTISE PROBLEM:https://cses.fi/problemset/result/653626/


//question on segment tree with lazy progation https://cses.fi/problemset/result/629426/========================================================================================================================

PRACTISE PROBLEM: https://codeforces.com/problemset/problem/1320/C
========================================================================================================================
Offline queries with segment tree ==>https://cses.fi/problemset/result/637091/
