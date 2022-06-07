// c++ program pre dijkstra algoritmus.
// program je urceny na maticovu reprezentaciu grafu

#include <limits.h>
#include <stdio.h>

// pocet vrcholov v grafe
#define V 9

// funkcia na najdenie vrcholu s hodnotou minimalnej vzdialenosti od
// mnoziny vrcholov, ktore este nie su zahrnute v strome najkratsej cesty
int minDistance (int dist[], bool sptSet[])
{
  // najnizsia moznost
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;

  return min_index;
}

// funkcia na printovanie dlziek v poli array
void printSolution (int dist[], int n)
{
  printf ("Vrchol   Vzdialenosť od zdroja \n");
  for (int i = 0; i < V; i++)
    printf ("%d \t\t %d\n", i, dist[i]);
}

// funkcia, ktora implementuje Dijkstrov algoritmus najkratsej cesty s jednym zdrojom
// pre graf reprezentovany pomocou reprezentacie matice susednosti
void dijkstra (int graph[V][V], int src)
{
  int dist[V];			// vystupne pole. dist[i] bude drzat najkratsie vzdialenosti od src po i

  bool sptSet[V];	// sptSet[i] bude pravdive, ak je vrchol i zahrnuty v najkratsom
  // je dokonceny strom cesty alebo najkratsia vzdialenosť od src do i

  // inicializacia vsetkych ciest ako NEKONECNE a stpSet[] ako false
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX, sptSet[i] = false;

  // prvy bod je vzdy 0
  dist[src] = 0;

  // najdi najkratsiu cestu pre vrcholy
  for (int count = 0; count < V - 1; count++)
    {
      // vyberte vrchol minimalnej vzdialenosti od mnoziny vrcholov
      // este spracovane. to sa vzdy rovna src v prvej iteracii.
      int u = minDistance (dist, sptSet);

      // oznac vybrate vrcholy za urobene
      sptSet[u] = true;

      // aktualizuje hodnotu vzdialenosti susednych vrcholov vybraneho vrcholu.
      for (int v = 0; v < V; v++)

	    // aktualizacia dist[v] iba v prrpade, ze nie je v sptSet, existuje hrana z
        // u do v a celkova vaha cesty od src do v cez u je
        // mensia ako aktualna hodnota dist[v]
	    if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
	        && dist[u] + graph[u][v] < dist[v])
	    dist[v] = dist[u] + graph[u][v];
    }

  // printni zostavene pole vzdialenosti
  printSolution (dist, V);
}

// program ovladaca na testovanie vyssiee uvedenej funkcie
int main ()
{
  /* matica na testovanie */
  int graph[V][V] = {   {0, 4, 0, 0, 0, 0, 0, 8, 0},
                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
                        {0, 0, 4, 14, 10, 0, 2, 0, 0},
                        {0, 0, 0, 0, 0, 2, 0, 1, 6},
                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
                        {0, 0, 2, 0, 0, 0, 6, 7, 0}
                  };

  dijkstra (graph, 0);

  return 0;
}
