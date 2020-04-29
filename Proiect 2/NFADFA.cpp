#include "NFADFA.h"
#include <bits/stdc++.h>

using namespace std;

ifstream in("date.in");

#define lamda '~'

ostream& operator<<(ostream& out, const NFADFA& ob)
{
    out << ob.n << " Numarul de stari(noduri)\n";
    for (int i = 0; i < ob.n; i++)
    {
        out << i << " ";
        for(size_t j = 0 ; j < ob.a[i].size() ; j++)
        {
            out << ob.a[i][j].first << " cu litera " << ob.a[i][j].second << " ";
        }
        out<<'\n';
    }
    out << "Starea initiala: " << ob.q0 << '\n';
    out << "Starile finale: \n";
    for (int i = 0; i < ob.n; i++)
        if (ob.qf[i] == true)
            out << i << ' ';
    out << '\n';
    return out;
}


void NFADFA :: citire()
{
    int i,qfin;
    int x,y;
    char c;
    in>>n>>m>>t;
    in>>q0;
    qin[q0] = 1;
    fill(qin + 1, qin + n + 1,0);
    fill(qf + 1, qf + n + 1,0);
    for(i=1; i<=t; i++)
    {
        in>>qfin;
        qf[qfin]=true;
    }
    for(i = 1 ; i <= m; i++)
    {
        in>>x>>y>>c;
        Alfabet.insert(c);
        a[x].push_back(make_pair(y,c));
    }
}

bool NFADFA :: cauta(std :: pair<int,int> x)
{
    for(auto y : history)
        if(y.first == x.first && y.second == x.second)
            return true;
    return false;

}
void NFADFA :: eliminare_lamda(int nod1,int nod2,int pozitie)
{
    //cout << nod1 << " " << nod2 <<'\n';
    for(size_t i = pozitie ; i < a[nod1].size() ; i++)
        a[nod1][i] = a[nod1][i+1];
    a[nod1].pop_back();
    for(size_t i = 0 ; i < a[nod2].size() ; i++)
    {
        std :: pair <int,int> x;
        x.first = nod1;
        x.second = a[nod2][i].first;
        if(cauta(x) == false)
            a[nod1].push_back(a[nod2][i]);
    }
    /*for (int i = 0; i < n; i++)
    {
        cout << i << " ";
        for(size_t j = 0 ; j < a[i].size() ; j++)
        {
            cout << a[i][j].first << " cu litera " << a[i][j].second << " ";
        }
        cout<<'\n';
    }
    */
    if(qf[nod2] == true)
        qf[nod1] = true;
    if(qin[nod1] == true)
        qin[nod2] = true;
}

void NFADFA :: eliminare_lamdauri()
{
    for(int i = 0 ; i < n ; i++)
    {
        size_t j = 0;
        while(j < a[i].size())
        {
            if(a[i][j].second == lamda)
            {
                eliminare_lamda(i,a[i][j].first,j);
                history.push_back({i,a[i][j].first});
                j--;
            }
            j++;
        }
    }
}

void NFADFA :: eliminare_stari_initiale()
{
    int nod_adevarat[N],ct = 0;
    for(int i = 0 ; i < n ; i++)
    {
        if(qin[i] == true)
            cout<<i<<" ";
    }
    cout<<'\n';
}

void NFADFA :: transformare_dfa()
{
    vector<int>stari_noi[N];
    vector< pair <int,char> > dfa[N];
    map<char,vector<int>>grupare;
    map<vector<int>,bool>viz;
    map<vector<int>,int>poz;
    int nr_noduri,nod_curent,vecin;
    char cost;
    bool efinala;
    nr_noduri = n - 1;
    nod_curent = 0;
    for(int i = 0 ; i < n ; i++)
    {
        stari_noi[i].push_back(i);
        viz[stari_noi[i]] = true;
        poz[stari_noi[i]] = i;
    }
    while(nod_curent <= nr_noduri)
    {
        efinala = false;
        grupare.clear();
        for(auto nod : stari_noi[nod_curent])
        {
            cout<<nod<<" ";
            for(int i = 0 ; i < a[nod].size() ; i++)
            {
                vecin = a[nod][i].first;
                cost = a[nod][i].second;
                if(find(grupare[cost].begin(),grupare[cost].end(),vecin) == grupare[cost].end())
                {
                    grupare[cost].push_back(vecin);
                    if(qf[vecin] == true)
                        efinala = true;
                }
            }
        }
        cout<<'\n';
        cout<<nod_curent<<'\n';
        for(auto x : grupare)
        {
            cout<<x.first<<'\n';
            sort(x.second.begin(),x.second.end());
            for(auto y : x.second)
                cout<<y<< " ";
            cout<<'\n';
            if(viz[x.second] != true)
            {
                viz[x.second] = true;
                nr_noduri++;
                if(efinala == true)
                    qf[nr_noduri] = true;
                poz[x.second] = nr_noduri;
                for(auto y : x.second)
                {
                    stari_noi[nr_noduri].push_back(y);
                }
                dfa[nod_curent].push_back(make_pair(nr_noduri,x.first));
            }
            else
            {
                dfa[nod_curent].push_back(make_pair(poz[x.second],x.first));
            }
        }
        nod_curent++;
        cout<<'\n';
    }
    for(size_t i = 0 ; i <= nr_noduri ; i++)
    {
        a[i].clear();
        for(size_t j = 0 ; j < dfa[i].size(); j++)
        {
            a[i].push_back(dfa[i][j]);
        }
    }
    n = nr_noduri + 1;
}

void NFADFA::dfs(int nod)
{
    int vecin;
    viz[nod] = 1;
    for(size_t i = 0 ; i < a[nod].size() ; i++)
    {
        vecin = a[nod][i].first;
        if(viz[vecin] == 0)
        {
            dfs(vecin);
        }
    }
}

void NFADFA::dfs_reverse(int nod)
{
    int vecin;
    viz[nod] = 1;
    for(size_t i = 0 ; i < rev_a[nod].size() ; i++)
    {
        vecin = rev_a[nod][i];
        if(viz[vecin] == 0)
        {
            dfs_reverse(vecin);
        }
    }
}
void NFADFA::eliminare_stari_gresite()
{
    ///starile in care nu pot ajunge din starea initiala
    bool viz_start[N],viz_final[N];
    vector< pair <char,int> > aux[N];
    for(int i = 0 ; i < n ; i++)
    {
        for(auto vecin : a[i])
        {
            rev_a[vecin.first].push_back(i);
        }
    }
    dfs(q0);///dfs din starea initiala
    for(int i = 0 ; i < n ; i++)
        viz_start[i] = viz[i]; ///nodurile in care nu pot ajunge din starea initiala daca viz[i] = 0
    fill(viz + 1,viz + n + 1,0);
    for(int i = 0 ; i < n ; i++)
    {
        if(qf[i] == 1)
            dfs_reverse(i);  ///dfs din toate starile finale
    }
    for(int i = 0 ; i < n ; i++)
        viz_final[i] = viz[i];  ///nodurile in care nu pot ajunge din staril finale daca viz[i] = 0

    for(int i = 0 ; i < n ; i++)
        if(viz_start[i] == 1 && viz_final[i] == 1) ///nod care trebuie pastrat daca indeplineste ambele conditii
            viz[i] = 1;
        else
            viz[i] = 0;
    int nr_noduri = 0;
    for(int i = 0 ; i < n ; i++)
    {
        if(viz[i] == 1)
        {
            nr_noduri++;
            for(size_t j = 0 ; j < a[i].size() ; j++)
            {
                int vecin = a[i][j].first;
                if(viz[vecin] == 1)
                    aux[i].push_back(make_pair(vecin,a[i][j].second));///construim noul graf cu nodurile bune
            }
        }
        else
        {
            qf[i] = 0;
        }
    }
    for(int i = 0 ; i < n ; i++)
    {
        a[i].clear();
        for(size_t j = 0 ; j < aux[i].size() ; j++)
        {
            a[i].push_back(aux[i][j]);///copiem graful auxilar
        }
    }
    n = nr_noduri;
}

void NFADFA::minimizare_dfa()
{
    //Pasul 1: gasim starile echivalente
    int i,j;
    bool stari_echivalente[1000][1000];	//construim matricea de adiacenta
    for(i = 0 ; i < n ; i++)
        fill(stari_echivalente[i], stari_echivalente[i] + n, true);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (qf[i] != qf[j])
                stari_echivalente[j][i] = false; ///marcam cu false daca i stare finala si j stare nefinala
        }
    }
    ///marchez cu false toate perechile (q, r) pentru care (a(q, litera), a(r, litera)) sunt marcate cu false
    bool gasesc_stari = true;
    while (gasesc_stari)
    {
        gasesc_stari = false;///semnalizator
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                for (const char& litera : Alfabet)	///pentru fiecare litera din alfabet, verific in matrice
                {
                    int vecin1 = -1,vecin2 = -1;
                    for(size_t q = 0 ; q < a[i].size() ; q++)
                    {
                        if(a[i][q].second == litera)
                        {
                            vecin1 = q;
                            break;
                        }
                    }
                    for(size_t q = 0 ; q < a[j].size() ; q++)
                    {
                        if(a[j][q].second == litera)
                        {
                            vecin2 = q;
                            break;
                        }
                    }
                    if(vecin1 != -1 && vecin2 != -1)
                    {
                        if (stari_echivalente[vecin1][vecin2] == false && stari_echivalente[i][j] == true)
                        {
                            stari_echivalente[i][j] = false;	///marchez in matrice cu fals
                            gasesc_stari = true;
                        }
                    }
                }
            }
    }
    /*
    for(j = 0 ; j < n ; j++)
    {
        cout<< j << " ";
        for(i = 0 ; i < n ; i++)
            if(i > j)
                cout<<stari_echivalente[i][j] << " ";
        cout<<'\n';
    }
    */

    //Pasul 2. Gruparea starilor echivalente si calcularea noii functii de tranzitie
    vector<set<int>>stari_noi;

    int nr_noduri = 0;
    for(j = 0 ; j < n ; j++)
        for(i = 0 ; i < n ; i++)
        {
            if( i > j && stari_echivalente[i][j] == true) /// gruparea starilor echivalente in stari noi
            {
                int nod1 = j;
                int nod2 = i;
                if(nr_noduri == 0)/// formam prima stare
                {
                    set<int> aux;
                    aux.insert(nod1);
                    aux.insert(nod2);
                    stari_noi.push_back(aux);
                    nr_noduri++;
                }
                else
                {
                    bool amgasit = false;
                    ///daca am gasit starea in cele adaugate,actualizam starea respectiva
                    for(int q = 0 ; q < nr_noduri ; q++)
                        if(stari_noi[q].find(nod1) != stari_noi[q].end())
                        {
                            stari_noi[q].insert(nod2);
                            amgasit = true;
                            break;
                        }
                    ///in caz contrar formam o stare noua cu cele 2 noduri
                    if(amgasit == false)
                    {
                        set<int> aux;
                        aux.insert(nod1);
                        aux.insert(nod2);
                        stari_noi.push_back(aux);
                        nr_noduri++;
                    }
                }
            }
        }
    for(i = 0 ; i < nr_noduri ; i++)
    {
        cout<< "nodul " << i << " ";
        for(auto x : stari_noi[i])
            cout<< x << " ";
        cout<<'\n';
    }
    map<char,set<int>>grupare;
    map<set<int>,int>noduri_adevarate;
    vector < pair <int,char> > dfa_min[N];
    bool qfaux[N];
    for(i = 0 ; i < nr_noduri ; i++)
    {
        noduri_adevarate[stari_noi[i]] = i ;
    }
    for(i = 0 ; i < nr_noduri ; i++)
    {
        int Nod = noduri_adevarate[stari_noi[i]];
        cout<<'\n';
        cout<<Nod<<'\n';
        grupare.clear();
        bool efinala = false;
        bool einitiala = true;
        ///ma plimb prin starile din care e compus nodul curent pentru a gasi noua tranzitie
        for(auto nod : stari_noi[i])
        {
            cout<<nod<<" ";
            if(qf[nod] == true)
                efinala = true;
            if(q0 == nod)
                einitiala = true;
            for(j = 0 ; j < a[nod].size() ; j++)
            {
                int vecin = a[nod][j].first;
                char cost = a[nod][j].second;
                grupare[cost].insert(vecin);
            }
        }
        cout<<'\n';
        /// actualizez gruparea curenta in functie de starile echivalente
        for(auto x : grupare)
        {
            int nod; ///primul nod din grupare
            for(auto y : x.second)
            {
                nod = y;
                break;
            }
            for(auto y : stari_noi) ///actualizez gruparea
                if(y.find(nod) != y.end())
                {
                    grupare[x.first] = y;
                    break;
                }
        }
        ///formez noiile tranzitii
        for(auto x : grupare)
        {
            cout<<x.first<<'\n';
            for(auto y : x.second)
                cout<<y<< " ";
            cout<<'\n';
            char litera = x.first;
            int nod_dest = noduri_adevarate[x.second];
            if(efinala == true)
                qfaux[Nod] = true;
            if(einitiala == true)
                q0 = Nod;
            dfa_min[Nod].push_back(make_pair(nod_dest,litera));
        }
    }
    n = nr_noduri;
    for(int i = 0 ; i < n ; i++)
        qf[i] = qfaux[i];
    for(int i = 0 ; i < n ; i++)
    {
        a[i].clear();
        for(size_t j = 0 ; j < dfa_min[i].size() ; j++)
        {
            a[i].push_back(dfa_min[i][j]);///copiem graful auxilar
        }
    }
}
