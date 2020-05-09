#include <bits/stdc++.h>

#ifndef NFADFA_H_INCLUDED
#define NFADFA_H_INCLUDED

const int N = 10000;

using namespace std;

class NFADFA{
private:
    vector< pair < int, char > >a[N];
    vector< int > rev_a[N]; ///graf transpus
    bool qf[N],qin[N];
    int n,m,t,q0;
    vector <pair <int,int> > history;
    set<char>Alfabet;
    bool viz[N];
public:
    void citire();
    void citire_gramatica();
    void eliminare_lamdauri();
    void eliminare_lamda(int,int,int);
    void transformare_dfa();
    void eliminare_stari_gresite();
    void eliminare_stari_initiale();
    void minimizare_dfa();
    void dfs(int);
    void dfs_reverse(int);
    bool cauta(pair <int,int>);
    friend ostream& operator<<(ostream&, const NFADFA&);
};

#endif // NFA-DFA_H_INCLUDED
