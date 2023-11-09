#include<bits/stdc++.h>
#include<tuple>
using namespace std;
typedef int ll;
typedef pair<ll,ll> du;
typedef tuple<ll,ll,ll> tri;
#define INF 1e9
#define mod 998244353
#define eps 1e-9
#define N 500005
ll n,k,dp[500005],psum[500005];
string s,t;
struct Node{
    // Node information
    ll minn;
    // initialize
    Node(){minn=INF;}
    // assignment
    Node(ll x){
        minn=x;}
    // Node's information merging
    Node operator + (const Node &x)const{
		return Node(min(minn,x.minn));
	}
};
struct SegT{
	ll lo[N<<2],hi[N<<2];// lo:id the segemt's l,hi:id of the segment's r,pre: initial value, lazy:lazy mark  
	Node val[N<<2];
	void build(ll x,ll l,ll r){
		lo[x]=l,hi[x]=r;
		if(l==r){
			val[x].minn=INF;
			return;
		}
		ll mid=(l+r)>>1,a=x<<1;
		build(a,l,mid);
		build(a|1,mid+1,r);
		val[x]=val[a]+val[a|1];
		return;
	}
	void update(ll v,ll pos,ll x){
		ll tl=lo[x],tr=hi[x];
		if(tl==pos&&tr<=pos){
            val[x].minn=v;
			return;
		}
        ll a=x<<1,mid=(tl+tr)>>1;
		if(mid>=pos)
			update(v,pos,a);
		if(mid<pos)
			update(v,pos,a|1);
		val[x]=val[a]+val[a|1];
		return;
	}
	Node query(ll x,ll l,ll r)
	{
		ll tl=lo[x],tr=hi[x];
        if(tr<l||tl>r)
            return Node(INF);
		if(l<=tl&&tr<=r)
			return val[x];
		ll mid=(tl+tr)>>1,a=x<<1;
		if(mid<l)
			return query(a|1,l,r);
		if(mid>=r)
			return query(a,l,r);
		return query(a,l,r)+query(a|1,l,r);
	}
}segt;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k>>s>>t;
    psum[1]=1;
    for(ll i=1;i<=n;i++)
        if(t[i]!=t[i-1])
            psum[i+1]=1;
    for(ll i=1;i<=n;i++)
        psum[i]+=psum[i-1];
    dp[1]=1;
    segt.build(1,0,n);
    segt.update(-psum[1],0,1);
    for(ll i=1;i<=n;i++){
        if(s[i-1]==t[i-1])
            dp[i]=dp[i-1];
        else{
            dp[i]=(segt.query(1,max(0,i-k),i-1).minn+psum[i]+1)/2+1;
        }
        segt.update(2*dp[i]-psum[i+1],i,1);
        //cout<<i<<" "<<dp[i]<<endl;
    }
    cout<<dp[n]<<endl;
    return 0;
}
