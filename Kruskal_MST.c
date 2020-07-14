// Timothy Khal
// Lab7

// Kruskal's Algorithm Lab

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// for qsort
#include <unistd.h>
// for usleep

#define INF 1000000
// infinity

// The adjacency matrix for the graph :
int N;           // number of nodes (vertices)
int A[100][100]; // adjacency matrix of the graph


void makeTree(int Tree[]);
void my_sort(int lo, int hi);

int input_graph()
{
    int r, c;
    char w[10];

    scanf("%d", &N);

    // scan the first row of labels....not used
    for (c = 0; c < N; c++)
    {
        scanf("%s", w);
    }

    for (r = 0; r < N; r++)
    {
        scanf("%s", w); // label ... not used
        for (c = 0; c < N; c++)
        {
            scanf("%s", w);
            if (w[0] == '-')
            {
                A[r][c] = -1;
            }
            else
            {
                A[r][c] = atoi(w); // ascii to integer
            }
        }
    }
}

int print_graph()
{
    int r, c;

    printf("\n%d\n\n", N);

    printf("  ");
    for (c = 0; c < N; c++)
    {
        printf("   %c", c + 'A');
    }

    printf("\n");

    for (r = 0; r < N; r++)
    {
        printf("%c  ", r + 'A');
        for (c = 0; c < N; c++)
        {
            if (A[r][c] == -1)
            {
                printf("  - ");
            }
            else
            {
                printf("%3d ", A[r][c]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

typedef struct
{
    int vstart;
    int vend;
    int vlen;
} Edge;

Edge elist[100];

int f(Edge test, int *t, int *tc);
int check(int *t);

int compare(const void *p1, const void *p2)
{
    Edge *a, *b;
    a = (Edge *)p1;
    b = (Edge *)p2;
    if ((*a).vlen < (*b).vlen)
    {
        return -1;
    }
    else if ((*a).vlen > (*b).vlen)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int print_edge_list(Edge *elist, int N)
{
    int i;
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("<%c, %c, %d> ",
               'A' + elist[i].vstart, 'A' + elist[i].vend, elist[i].vlen);
    }
    printf("\n");
}

int print_array(int *x, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf(" %3d", x[i]);
    }
}

int kruskal()
{
    // a tree has the property that |E| = |V| - 1

    // 1 .make a list of all edges
    // 2. sort this list (FOR FULL CREDIT use a time
    //    complexity n*log(n) sorting algorithm discussed in class)
    // 3. starting with the shortest edge in the sorted list and
    // continuing until you have N -1 edges (or realize that you can't)
    // adjoin this edge to your potential tree list unless it would
    // create a cyle.

    // assume an undirected graph, hence only need the upper right
    // part of the adjacency matrix :

    // code below creates and then prints array of edges

    int e, r, c;

    e = 0; // number of edges
    for (r = 0; r < N; r++)
    {
        for (c = r + 1; c < N; c++)
        {
            if (A[r][c] != -1)
            {
                elist[e].vstart = r; // start vertex of edge
                elist[e].vend = c;   // end vertex of edge
                elist[e].vlen = A[r][c];
                e++;
            }
        }
    }

    if (e < N - 1)
    {
        printf("there aren't enough edges to build a spanning tree\n");
        return 0;
    }

    print_edge_list(elist, e);

    //  YOUR CODE GOES BELOW!
    //  Note:  this function should call print_edge_list() at the
    //         end to give the edges in a minimum spanning tree

    int Tree[N];
    Edge minTree[N];
    int index = 0;
    int count = 1;
    makeTree(Tree);
    my_sort(0, e - 1);

    for (int i = 0; i < N; ++i)
    {
        int s = elist[i].vstart; // start
        int e = elist[i].vend;   // end

        if (Tree[s] == 0 && Tree[e] == 0)
        {
            Tree[s] = count;
            Tree[e] = count;
            ++count;

            minTree[index] = elist[i];
            ++index;
        }
        // Not a match
        else if (Tree[s] != Tree[e])
        {
            if (Tree[s] == 0)
                Tree[s] = Tree[e];
            else{
                int prevTree = Tree[e];
                Tree[e] = Tree[s];

                for (int j = 0; j < N; ++j){
                    if (Tree[j] != 0 && Tree[j] == prevTree)
                        Tree[j] = Tree[e];
                }
            }

            minTree[index] = elist[i];
            ++index;
        }
    }

    printf("%s", "Sorted List:\n");
    print_edge_list(elist, e);

    printf("%s", "Spanning Tree:\n");
    print_edge_list(minTree, N - 1);
}


void my_sort(int lo, int hi)
{
    if (lo >= hi)
        return;
    int k = elist[lo].vlen; // key
    int l = lo + 1; // left
    int r = hi; // right
    int t = 0; // temp

    while (l < r)
    {
        while (elist[l].vlen < k && l < r)
            ++l;
        while (elist[r].vlen > k && r > l)
            --r;

        if (l != r)
        {
            t = elist[l].vlen;
            elist[l].vlen = elist[r].vlen;
            elist[r].vlen = t;

            t = elist[l].vstart;
            elist[l].vstart = elist[r].vstart;
            elist[r].vstart = t;

            t = elist[l].vend;
            elist[l].vend = elist[r].vend;
            elist[r].vend = t;

            ++l;
            --r;
        }
    }

    if (elist[l].vlen > k)
    {
        t = elist[l - 1].vlen;
        elist[l - 1].vlen = k;
        elist[lo].vlen = t;

        t = elist[l - 1].vstart;
        elist[l - 1].vstart = elist[lo].vstart;
        elist[lo].vstart = t;

        t = elist[l - 1].vend;
        elist[l - 1].vend = elist[lo].vend;
        elist[lo].vend = t;
    }

    else if (elist[l].vlen < k){
        t = elist[l].vlen;
        elist[l].vlen = k;
        elist[lo].vlen = t;

        t = elist[l].vstart;
        elist[l].vstart = elist[lo].vstart;
        elist[lo].vstart = t;

        t = elist[l].vend;
        elist[l].vend = elist[lo].vend;
        elist[lo].vend = t;
    }
    my_sort(lo, l - 1);
    my_sort(l, hi);
}

void makeTree(int Tree[]){
    for (int i = 0; i < N; ++i)
        Tree[i] = 0;
}

int main()
{
    // Before modifying this skeleton, try compiling and then
    // try running with ./a.out < graph08.input
    input_graph(); // N, A{}{}
    print_graph();
    kruskal();
}
