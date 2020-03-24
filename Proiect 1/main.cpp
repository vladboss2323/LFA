#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

ifstream in("date.in");
ofstream out("date.out");

const int N=10005;

vector< pair < int, char > >a[N];
queue < pair <int, string > > Q;
unordered_map <string, int >Map;

int n,m,q0,t,q,pasi,stfinala,gsol=0,nrcuv=0;
bool qf[N],viz[N][N];

bool verif(char cuv[1000])
{
    int i,j,stcurenta,l;
    l=strlen(cuv);
    stcurenta=q0;
    for(i=0; i<l; i++)
    {
        int ok=0;
        for(j=0; j<a[stcurenta].size(); j++)
            if(a[stcurenta][j].second==cuv[i])
            {
                stcurenta=a[stcurenta][j].first;
                ok=1;
                break;
            }
        //out<<stcurenta<<" ";
        if(ok==0)
            return false;
    }
    for(i=1; i<=t; i++)
        if(stcurenta==qf[i])
            return true;
    return false;

}

void dfs(int nod,char c,char cuv[])
{
    int i,vecin;
    char cost;
    //out<<nod<<" "<<pasi<<"|";
    if(gsol==1)
        return;
    if(pasi==strlen(cuv))
    {
        stfinala=nod;
        if(qf[stfinala]==true)
        {
            out<<cuv<<" am solutie "<<1<<'\n';
            gsol=1;
            return;
        }
    }
    int ok=0;
    for(i=0; i<a[nod].size(); i++)
    {
        vecin=a[nod][i].first;
        cost=a[nod][i].second;
        if(c==cost && viz[vecin][pasi]==1)
        {
            //if(vecin==3003)
            //cout<<vecin<<" "<<cost<<" "<<pasi<<" "<<cuv<<" "<<cuv[pasi]<<" "<<cuv[pasi+1]<<'\n';
            viz[vecin][pasi]=0;
            pasi++;
            ok=1;
            dfs(vecin,cuv[pasi],cuv);
            pasi--;
        }
    }
    if(ok==0)
    {
        stfinala=-1;
        return;
    }
}
// sa nu trec prin acelasi loc de 2 ori cu aceeasi lungime


void bfs()
{
    int nodcurent,vecin,litera;
    string aux;
    Q.push({q0,""});
    while(!Q.empty())
    {
        nodcurent=Q.front().first;
        aux=Q.front().second;
        Q.pop();
        for(int i = 0 ; i < a[nodcurent].size() ; i++)
        {
            vecin=a[nodcurent][i].first;
            litera=a[nodcurent][i].second;
            string aux1=aux;
            aux1.push_back(litera);
            int len=aux1.size();
            if(viz[vecin][len]==1)
            {
                Q.push({vecin,aux1});
                viz[vecin][len]=0;
            }
            if(qf[vecin]==true)
            {
                //cout<<vecin<<" "<<litera<<" "<<aux1<<" "<<len<<'\n';
                if(Map.find(aux1)==Map.end())
                {
                    nrcuv++;
                    out<<aux1<<'\n';
                    Map[aux1]=1;
                    if(nrcuv==100)
                        return;
                }
            }

        }
    }
}

void citire()
{
    int i,qfin;
    int x,y;
    char c,cuv[1000];
    in>>n>>m;
    for(i = 1 ; i <= m; i++)
    {
        in>>x>>y>>c;
        a[x].push_back(make_pair(y,c));
    }
    in>>q0;
    in>>t;
    for(i=1; i<=t; i++)
    {
        in>>qfin;
        qf[qfin]=true;
    }
    in>>q;
    for(i=1; i<=q; i++)
    {
        in>>cuv;
        //out<<verif(cuv)<<'\n';
        int l=strlen(cuv);
        for(int j = 0 ; j < n ; j++)
            for(int u = 0 ; u < l ; u++ )
                viz[j][u]=1;
        pasi=0;
        gsol=0;
        dfs(q0,cuv[pasi],cuv);
        if(gsol==0)
            out<<cuv<<" "<<0<<'\n';
        //out<<stfinala<<'\n';
    }
    for(int j = 0 ; j < n ; j++)
        for(int u = 0 ; u < N ; u++ )
            viz[j][u]=1;
    bfs();
}

void generare()
{
    out<<3004<<" "<<1000+1000*1000+1000*1000+1000+2<<'\n';
    for(int i = 1; i <= 1000; ++i)
    {
        out<<0<<" "<<i<<" a"<<'\n';
    }
    for(int i = 1; i <= 1000; ++i)
    {
        for(int j = 1001; j <= 2000; ++j)
            out<<i<<" "<<j<<" b"<<'\n';
    }
    for(int i = 1001; i <= 2000; ++i)
        for(int j = 2001; j <= 3000; ++j)
            out<<i<<" "<<j<<" c"<<'\n';
    for(int i = 2001; i <= 3000; ++i)
        out<<i<<" "<<3001<<" d"<<'\n';
    out<<3000<<" "<<3002<<" d"<<'\n';
    out<<3002<<" "<<3003<<" e"<<'\n';
    out<<0<<'\n';
    out<<1<<'\n';
    out<<3003<<'\n';
    out<<1<<'\n';
    out << "abcde" ;
}

int main()
{
    int i,j;
    //generare();
    citire();
    /*
    for(i = 0; i < n; i++)
    {
        out<<i<<" ";
        for(j = 0; j < a[i].size(); j++)
        {
            out<<a[i][j].first<<" "<<a[i][j].second<<"|";
        }
        out<<endl;
    }
    */
    return 0;
}

/*
8 47
0 1 a
1 0 a
1 2 b
2 1 b
2 3 a
3 2 a
3 0 b
0 3 b
1 4 a
1 4 b
1 4 c
4 5 a
4 5 b
4 5 c
5 4 a
5 4 b
5 4 c
5 6 a
5 6 b
5 6 c
6 5 a
6 5 b
6 5 c
6 7 a
6 7 b
6 7 c
7 6 a
7 6 b
7 6 c
7 4 a
7 4 b
7 4 c
4 7 a
4 7 b
4 7 c
4 6 a
4 6 b
4 6 c
6 4 a
6 4 b
6 4 c
5 7 a
5 7 b
5 7 c
7 5 a
7 5 b
7 5 c
0
1
0
7
a
ab
ba
abab
aaabbb
c
ac



8
26
0 1 a
1 0 a
1 2 b
2 1 b
2 3 a
3 2 a
3 0 b
0 3 b
1 4 a
1 4 b
1 4 c
4 7 a
4 7 b
4 7 c
6 5 a
6 5 b
6 5 c
7 6 a
7 6 b
7 6 c
4 6 a
4 6 b
4 6 c
6 4 a
6 4 b
6 4 c
0
1
2
*/

