//12365
//Jupiter Atacks!
//Misc;Fenwick Tree
#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX 600100
#define ull long long
using namespace std;

struct Node { 
    int a, b, c; 
    int u;

    Node() {}
    Node(int a) : a(a), b(0), c(0), u(0) { }
    Node(int a, int b, int c) : a(a), b(b), c(c), u(0) {}

    void change(int n) {
        n = ((n%3)+3)%3;
        if (n==1) {
            swap(a, b); swap(a, c);
        } else if (n==2) { 
            swap(c, b); swap(c, a); 
        }
    }
    
    Node operator +(Node x) {
        return Node(a+x.a, b+x.b, c+x.c);    
    }
};

struct Segtree {
    Node T[MAX];
    int n;

    Segtree() {
        clear(1);
    }
    
    void clear(int n) {
        this->n = n;               
        
        while(n != n&-n)
            n += n&-n;
        
        build(1, 1, n);
    }
    
    void build(int v, int a, int b) {
        T[v] = Node(b-a+1);
        
        if (a<b) {
            build(2*v, a, (a+b)>>1);
            build(2*v+1, ((a+b)>>1)+1, b);
        }
    }
    
    Node update(int v, int a, int b, int i, int j, int inc1, int inc2) {
        if (i>b || j<a) {
            T[v].u += inc2;
            T[v].change(inc2);
            return T[v];
        }
        
        if (i<=a && b<=j) {
            T[v].u += inc1+inc2;
            T[v].change(inc1+inc2);
            return T[v];
        }
        
        T[v].change(inc2);

        return T[v] = update(v*2, a, (a+b)>>1, i, j, inc1, inc2+T[v].u) + 
                      update(v*2+1, ((a+b)>>1)+1, b, i, j, inc1, inc2+T[v].u);
        
    }

    Node update(int i, int j, int inc) {
        return update(1, 1, n, i, j, inc, 0);
    }
    
    Node query(int v, int a, int b, int i, int j, int inc) {
        T[v].u += inc;
        T[v].change(inc);

        if (i>b || j<a)
            return Node(0);
        
        if (i<=a && b<=j)
            return T[v];
        
        Node answer = query(v*2, a, (a+b)>>1, i, j, T[v].u) + 
                      query(v*2+1, ((a+b)>>1)+1, b, i, j, T[v].u);
        T[v].u = 0;

        return answer;
        
    }

    Node query(int i, int j) {
        return query(1, 1, n, i, j, 0);
    }

};

Segtree T;

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        T.clear(n);
        for(int i=0; i<m; i++) {
            char cmd; int a, b;
            scanf(" %c %d %d", &cmd, &a, &b);
            if (cmd == 'M') {
                T.update(a, b, 1);
            } else {
                Node node = T.query(a, b);            
                printf("%d %d %d\n", node.a, node.b, node.c);
            } 
        }
        printf("\n");
    }
}