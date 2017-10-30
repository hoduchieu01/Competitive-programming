#include "query.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxN            30000
#define MaxL            16
#define true 1
#define false 0

static int Init = true;
static char B[2];
static int FullS, NQ;   /*# queries*/
static unsigned int N, M, Half;
static int T[MaxN + 1];
static int D[MaxN + 1];
static FILE *OutF;

static void EndQuery(void)
{
  OutF = fopen("select.out", "w");
  fprintf(OutF, "0 Point\n");
  fflush(OutF);
  if (OutF != NULL)
    fclose(OutF);
  OutF = NULL;
  exit(0);
}

static void Start(void)
{
  int i;
  FILE *InFile;
  int FORLIM;

  B[0] = 0; 
  B[1] = 1;
  InFile = NULL;
  OutF = fopen("select.out", "w");
  InFile = fopen("select.in", "r");
  fscanf(InFile, "%hd%*[^\n]", &N);
  getc(InFile);
  if (InFile != NULL)
    fclose(InFile);
  InFile = NULL;

  FORLIM = N;
  for (i = 1; i <= FORLIM; i++) {
    T[i] = -1;
    D[i] = 0;
  }
  T[0] = 0;
  D[0] = 0;
  if (N & 1)
    M = N;
  else
    M = N - 1;
  Half = M / 2 + 1;

  Init = false;
  NQ = 0;
  FullS = 0;
  for (i = 0; i < MaxL; i++) {
    if ( ((1 << i) & M) != 0 )
      FullS++;
  }
  if (InFile != NULL)
    fclose(InFile);
}

static int Find(int x)
{
  int Nx, xx;

  Nx = x;
  while (T[Nx] > 0)
    Nx = T[Nx];
  while (x != Nx) {  /*path compression*/
    xx = T[x];
    T[x] = Nx;
    x = xx;
  }
  return Nx;
}

static void Union(int *Nx, int Ny)
{
  int X;

  if (*Nx == 0) {
    *Nx = Ny;
    return;
  }
  if (Ny == 0)
    return;
  if (T[*Nx] > T[Ny]) {
    X = *Nx;
    *Nx = Ny;
    Ny = X;
  }
  T[*Nx] += T[Ny];
  T[Ny] = *Nx;
}

int Size(void)
{
  if (Init)
    Start();
  fprintf(OutF, "Size= %d\n", N);
  fflush(OutF);
  return N;
}

int Member(int i, int j)
{
  int Result, Ri, Rj, Di, Dj, Si, Sj, Ui, Vi, Uj, Vj, SDi, SDj;
  unsigned int X;
  int Ans;

  if (Init) {
    fprintf(OutF, "ERROR: Illegal dialog. Size must be called first!\n");
    EndQuery();
  }
  fprintf(OutF, "Member(%d, %d)", i, j);
  if (i < 1 || i > N || j < 1 || j > N) {
    fprintf(OutF, "Member(%d, %d)\n", i, j);
    fprintf(OutF, "ERROR: Value out of range\n");
    fflush(OutF);
    EndQuery();
  }

  NQ++;
  Ans = false;
  Ri = Find(i);
  Rj = Find(j);
  Di = D[Ri];
  Dj = D[Rj];
  if (Ri == Rj) {
    fprintf(OutF, "%d\n", 1);
    fflush(OutF);
    return 1;
  }
  if (Ri == Dj || Rj == Di) {
    fprintf(OutF, "%d\n", 0);
    fflush(OutF);
    return 0;
  }
  Si = abs(T[Ri]);
  Sj = abs(T[Rj]);
  SDi = abs(T[Di]);
  SDj = abs(T[Dj]);
  if (Si >= SDi) {
    Ui = Ri;
    Vi = Di;
  } else {
    Ui = Di;
    Vi = Ri;
    X = Si;
    Si = SDi;
    SDi = X;
  }
  if (Sj >= SDj) {
    Uj = Rj;
    Vj = Dj;
  } else {
    Uj = Dj;
    Vj = Rj;
    X = Sj;
    Sj = SDj;
    SDj = X;
  }
  if (Si + Sj >= Half) {
    Union(&Ui, Vj);
    Union(&Vi, Uj);
    D[Ui] = Vi;
    if (Vi != 0)
      D[Vi] = Ui;
    Ans = (Find(i)==Find(j));
  } else {
    if (Si + Sj <= SDi + SDj + 2) {
      Union(&Ui, Uj);
      Union(&Vi, Vj);
      D[Ui] = Vi;
      if (Vi != 0)
	D[Vi] = Ui;
      Ans = (Find(i)==Find(j));
    } else {
      if (Si + SDj == Sj + SDi) {
	X = Si + SDj + Sj + SDi;
	if ((X & M) == X) {
	  Union(&Ui, Vj);
	  Union(&Vi, Uj);
	  D[Ui] = Vi;
	  if (Vi != 0)
	    D[Vi] = Ui;
	    M &= ~X;
	  Half += -Si - SDj;
          Ans = (Find(i)==Find(j));
	} else {
	  Union(&Ui, Uj);
	  Union(&Vi, Vj);
	  D[Ui] = Vi;
	  if (Vi != 0)
	    D[Vi] = Ui;
         Ans = (Find(i)==Find(j));
	}
      } else {  /*Si+SDj<>Sj+SDi*/
	Union(&Ui, Vj);
	Union(&Vi, Uj);
	D[Ui] = Vi;
	if (Vi != 0)
	  D[Vi] = Ui;
       Ans = (Find(i)==Find(j));
      }
    }
  }

  Result = B[Ans];
  fprintf(OutF, "=%d\n", B[Ans]);
  fflush(OutF);
  return Result;
}

void Answer(int i)
{
  int Ri, Di, x, y, Nx, Sum;
  int OK;
  int G[MaxN + 1];
  int a, b, FORLIM;

  if (Init) {
    fprintf(OutF, "ERROR: Illegal dialog. Size must be called first!\n");
    EndQuery();
  }
  if (i < 1 || i > N) {
    fprintf(OutF, "Your Answer: %d\n", i);
    fprintf(OutF, "ERROR: Value out of range\n");
    EndQuery();
  }

  Ri = Find(i);
  Di = D[Ri];
  Sum = 0;

  FORLIM = N;
  for (x = 1; x <= FORLIM; x++) {
    Nx = Find(x);
    G[x] = (Nx != Ri && (T[Nx] < T[D[Nx]] ||
			 T[Nx] == T[D[Nx]] && Nx < D[Nx] || Nx == Di));
  }
  FORLIM = N;
  for (x = 1; x <= FORLIM; x++) {
    if (T[x] < 0 && x != Di && x != Ri) {
      y = D[x];
      if (T[x] < T[y])
	Sum += abs(T[x]);
      else
	Sum += abs(T[y]);
      T[x] = 0;
      T[y] = 0;
    }
  }
  /*for x=1..N*/
  Sum += abs(T[Di]);
  OK = (Sum <= N / 2);
  fprintf(OutF, "Your Answer: %d", i);
  if (OK) {
    fprintf(OutF, ", Correct\n");
    } else {
    fprintf(OutF, ", Not Correct\n");
  }

  if (OK)
    fprintf(OutF, "Majority Group:\n");
  else
    fprintf(OutF, "Non-Majority Group:\n");
  a = 0;
  b = 0;
  G[0] = true;
  G[N + 1] = true;
  FORLIM = N + 1;
  for (x = 1; x <= FORLIM; x++) {
    if (!G[x]) {
      if (!G[x - 1])
	b = x;
      else {
	a = x;
	b = a;
      }
    } else {
      if (a + 1 < b)
	fprintf(OutF, "%d..%d ", a, b);
      else if (a < b)
	fprintf(OutF, "%d %d ", a, b);
      else if (b == a && a != 0)
	fprintf(OutF, "%d ", a);
      b = 0;
    }
  }
  putc('\n', OutF);
  if (OK)
    fprintf(OutF, "Non-Majority Group:\n");
  else
    fprintf(OutF, "Majority Group:\n");
  a = 0;
  b = 0;
  G[0] = false;
  G[N + 1] = false;
  FORLIM = N + 1;
  for (x = 1; x <= FORLIM; x++) {
    if (G[x]) {
      if (G[x - 1])
	b = x;
      else {
	a = x;
	b = a;
      }
    } else {
      if (a + 1 < b)
	fprintf(OutF, "%d..%d ", a, b);
      else if (a < b)
	fprintf(OutF, "%d %d ", a, b);
      else if (b == a && a != 0)
	fprintf(OutF, "%d ", a);
      b = 0;
    }
  }
  fprintf(OutF, "\nNumber of Queries: %d \n", NQ);

  if (OK) {
    Sum = N - NQ;
    if (Sum < 0)
      Sum = 0;
    fprintf(OutF, "Full Possible Score: %d\n", FullS);
    fprintf(OutF, "Your Score: %d\n", Sum);
  } else {
    fprintf(OutF, "Full Possible Score: %d\n", FullS);
    fprintf(OutF, "Your Score: %d\n", 0);
  }
  if (OutF != NULL)
    fclose(OutF);
  OutF = NULL;
}

