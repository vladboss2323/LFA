#include <iostream>
#include <bits/stdc++.h>
///lamda nfa -> nfa
///fac lamda tranziitile pt fiecare element(unde pot ajunge cu lamda) ,adaug muchiile lamda
///pt fiecare p,q,r cu p -> q(lamda) q -> r (litera) sterg astea si adaug p -> r (litera)

#include <NFADFA.h>

ofstream out("date.out");
using namespace std;

int main()
{
    NFADFA a;
    a.citire();
    out<<a;
    a.eliminare_lamdauri();
    //a.eliminare_stari_initiale();
    out<<a;
    a.transformare_dfa();
    out<<a;
    a.eliminare_stari_gresite();
    out<<a;
    a.minimizare_dfa();
    out<<a;
    return 0;
}
