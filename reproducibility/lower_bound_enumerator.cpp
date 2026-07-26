#include <bits/stdc++.h>
using namespace std;

struct Enumerator {
    static constexpr int n=10;
    int m;
    array<int,n> target{}, residual{};
    array<uint16_t,n> adj{};
    vector<array<int,4>> foursets;
    vector<int> lower, upper, second_largest;
    unsigned long long nodes=0, complete=0, pass4=0, passall=0;

    static int ceil_div(int a,int b){
        int q=a/b, r=a%b;
        if(r!=0 && ((r>0)==(b>0))) ++q;
        return q;
    }
    static int floor_div(int a,int b){
        int q=a/b, r=a%b;
        if(r!=0 && ((r>0)!=(b>0))) --q;
        return q;
    }
    bool graphical_from(int start) const {
        vector<int> d;
        for(int i=start;i<n;i++){
            if(residual[i]<0 || residual[i]>n-1-start) return false;
            d.push_back(residual[i]);
        }
        sort(d.begin(),d.end(),greater<int>());
        long long sum=accumulate(d.begin(),d.end(),0LL);
        if(sum&1) return false;
        long long pref=0;
        for(int k=1;k<=(int)d.size();k++){
            pref+=d[k-1];
            long long rhs=1LL*k*(k-1);
            for(int i=k;i<(int)d.size();i++) rhs+=min(d[i],k);
            if(pref>rhs) return false;
        }
        return true;
    }
    bool check_foursets_completed_at(int processed) const {
        for(size_t z=0;z<foursets.size();z++) if(second_largest[z]==processed){
            auto T=foursets[z]; int e=0;
            for(int a=0;a<4;a++) for(int b=a+1;b<4;b++)
                e += (adj[T[a]]>>T[b])&1u;
            if(e<lower[z] || e>upper[z]) return false;
        }
        return true;
    }
    bool check_all_subsets() const {
        constexpr uint16_t mask_all=(1u<<n)-1;
        for(int mask=0;mask<(1<<n);mask++){
            int s=__builtin_popcount((unsigned)mask), cut=0;
            for(int i=0;i<n;i++) if((mask>>i)&1)
                cut += __builtin_popcount((unsigned)(adj[i] & (~mask) & mask_all));
            int k=m+s*(11-s)-2*cut;
            if(k<20 || k>35) return false;
        }
        return true;
    }
    void rec(int v){
        ++nodes;
        while(v<n && residual[v]==0){
            if(!check_foursets_completed_at(v)) return;
            ++v;
        }
        if(v==n){
            ++complete;
            for(int x:residual) if(x!=0) return;
            ++pass4;
            if(check_all_subsets()) ++passall;
            return;
        }
        int need=residual[v];
        vector<int> candidates;
        for(int j=v+1;j<n;j++) if(residual[j]>0) candidates.push_back(j);
        if(need<0 || need>(int)candidates.size()) return;
        vector<int> chosen;
        function<void(int,int)> choose=[&](int pos,int left){
            if(left==0){
                residual[v]=0;
                bool ok=true;
                for(int j:chosen){
                    --residual[j];
                    if(residual[j]<0) ok=false;
                    adj[v]|=uint16_t(1u<<j); adj[j]|=uint16_t(1u<<v);
                }
                if(ok && check_foursets_completed_at(v) && graphical_from(v+1)) rec(v+1);
                for(int j:chosen){
                    ++residual[j];
                    adj[v]&=uint16_t(~(1u<<j)); adj[j]&=uint16_t(~(1u<<v));
                }
                residual[v]=need;
                return;
            }
            if((int)candidates.size()-pos<left) return;
            for(int p=pos;p<=(int)candidates.size()-left;p++){
                chosen.push_back(candidates[p]);
                choose(p+1,left-1);
                chosen.pop_back();
            }
        };
        choose(0,need);
    }
    void init_foursets(){
        for(int a=0;a<n;a++) for(int b=a+1;b<n;b++) for(int c=b+1;c<n;c++) for(int d=c+1;d<n;d++){
            array<int,4>T{a,b,c,d};
            int D=target[a]+target[b]+target[c]+target[d];
            int L=ceil_div(2*D-m-8,4);
            int U=floor_div(2*D+5-m,4);
            L=max(L,0); U=min(U,6);
            foursets.push_back(T); lower.push_back(L); upper.push_back(U); second_largest.push_back(c);
        }
    }
    void run(const array<int,n>& seq,int M){
        m=M; target=seq; residual=seq; init_foursets();
        rec(0);
    }
};

void gen_sequences_rec(int pos,int last,int lo,int hi,int rem,array<int,10>&cur,vector<array<int,10>>&out){
    if(pos==10){ if(rem==0) out.push_back(cur); return; }
    for(int d=min(last,hi);d>=lo;--d){
        int r=rem-d, slots=9-pos;
        if(r<lo*slots || r>d*slots) continue;
        cur[pos]=d; gen_sequences_rec(pos+1,d,lo,hi,r,cur,out);
    }
}

int main(){
    unsigned long long grand_nodes=0,grand_complete=0,grand_pass4=0,grand_passall=0;
    for(int m=20;m<=22;m++){
        int lo=(m-17 + 1)/2;
        int hi=(m-10)/2;
        vector<array<int,10>> seqs; array<int,10> cur{};
        gen_sequences_rec(0,hi,lo,hi,2*m,cur,seqs);
        cerr<<"m="<<m<<" degree_sequences="<<seqs.size()<<" range=["<<lo<<","<<hi<<"]\n";
        for(size_t z=0;z<seqs.size();z++){
            Enumerator E; auto st=chrono::steady_clock::now(); E.run(seqs[z],m); auto en=chrono::steady_clock::now();
            double sec=chrono::duration<double>(en-st).count();
            cout<<"m="<<m<<" seq=";
            for(int i=0;i<10;i++){if(i)cout<<',';cout<<seqs[z][i];}
            cout<<" nodes="<<E.nodes<<" complete="<<E.complete<<" pass4="<<E.pass4<<" passall="<<E.passall<<" sec="<<fixed<<setprecision(6)<<sec<<"\n";
            grand_nodes+=E.nodes;grand_complete+=E.complete;grand_pass4+=E.pass4;grand_passall+=E.passall;
        }
    }
    cout<<"TOTAL nodes="<<grand_nodes<<" complete="<<grand_complete<<" pass4="<<grand_pass4<<" passall="<<grand_passall<<"\n";
    return grand_passall==0?0:2;
}
