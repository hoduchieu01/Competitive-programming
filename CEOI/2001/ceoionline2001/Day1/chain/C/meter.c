#include "meter.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define MaxN            10000
#define Pr              999999001L
#define true 1
#define false 0

typedef int Map[MaxN];
static int Init = true;
static Test = false;
static int N;
static Map P, CP, Acc;
static FILE *MetinF, *OutF;
static int MaxA;
static long Sign;

static void Abort(char *M)
{
  fprintf(OutF, "%s\n", M);
  if (OutF != NULL)
    fclose(OutF);
  OutF = NULL;
  exit(0);
}

static void T1(int *P, int *Q)
{
  int x, xx, y, L, FORLIM;

  L = P[0] + 1;
  if (L > N)
    L = N;
  FORLIM = N;
  for (x = 1; x <= FORLIM; x++) {
    xx = P[x - 1];
    if (xx % L == 0) {
      y = xx - L + 1;
    } else if (xx < N)
      y = xx + 1;
    else
      y = xx / L * L + 1;
    Q[y - 1] = x;
  }
}

static void Initialise(void)
{
  long x, y, Sign0;
  Map Q;
  long FORLIM;
  int SETIO;

  OutF = fopen("chain.out", "w");  
  MetinF = NULL;
  MetinF = fopen("chain.in", "r");
  if (MetinF == NULL) 
    Abort("ERROR: Input file CHAIN.IN not found!");
  SETIO = fscanf(MetinF, "%hd", &N);

  if (SETIO == 0) {
    if (MetinF != NULL)
      fclose(MetinF);
    MetinF = NULL;
    Abort("ERROR: Non-number value in first line of CHAIN.IN");
  }
  fscanf(MetinF, "%*[^\n]");
  if (N < 3 || N > MaxN) {
    if (MetinF != NULL)
      fclose(MetinF);
    MetinF = NULL;
    Abort("ERROR: Value out of range in first line of CHAIN.IN");
  }

  FORLIM = N;
  for (x = 0; x < FORLIM; x++) {
    Q[x] = -1;
    CP[x] = 0;
    Acc[x] = 0;
  }
  FORLIM = N;
  for (x = 1; x <= FORLIM; x++) {
    SETIO = fscanf(MetinF, "%ld", &y);
    if (SETIO = 0) {
      if (MetinF != NULL)
	fclose(MetinF);
      MetinF = NULL;
      Abort("ERROR: Non-number value in second line of file CHAIN.IN");
    }
    if (y < 1 || y > N) {
      if (MetinF != NULL)
	fclose(MetinF);
      MetinF = NULL;
      Abort("ERROR: Value out of range in second line of file CHAIN.IN");
    }
    if (Q[y - 1] != -1) {
      if (MetinF != NULL)
	fclose(MetinF);
      MetinF = NULL;
      Abort("ERROR: Duplicate values in second line of file CHAIN.IN");
    }

    Q[y - 1] = x;
  }

  fscanf(MetinF, "%*[^\n]");
  Sign0 = -1;
  SETIO = fscanf(MetinF, "%ld", &Sign0);

  if (MetinF != NULL)
    fclose(MetinF);
  MetinF = NULL;

  Test = false;

  T1(Q, P);

  Sign = 0;
  FORLIM = N;
  for (x = 1; x <= FORLIM; x++) {
    y = P[x - 1];
    Sign = (Sign + (MaxN - x) * y) % Pr;
  }

  if (Sign != Sign0)
    memcpy(P, Q, sizeof(Map));
  else {
    Test = true;
    FORLIM = N;
    for (x = 1; x <= FORLIM; x++)
      Q[P[x - 1] - 1] = x;
    memcpy(P, Q, sizeof(Map));
  }

  MaxA = 0;
  Init = false;
}


int Size(void)
{
  int Result;

  if (Init)
    Initialise();

  fprintf(OutF, "Size=%d\n", N);
  fflush(OutF);
  return N;
}

void Answer(int i, int x)
{
  char Si[256], Sx[256];
  int ii;
  char STR2[256];
  int FORLIM;

  if (i < 1 || i > N || x < 1 || x > N) {
    sprintf(Si, "%d", i);
    sprintf(Sx, "%d", x);
    sprintf(STR2, "ERROR: in Answer(%s,%s)", Si, Sx);
    Abort(STR2);
  }
  CP[i - 1] = x;
  if (i != N)
    return;
  fprintf(OutF, "Your Answer:\n");
  FORLIM = N - 2;
  for (ii = 0; ii <= FORLIM; ii++)
    fprintf(OutF, "%d ", CP[ii]);
  fprintf(OutF, "%d\n", CP[N - 1]);
  fprintf(OutF, "Access/Atom:\n");
  fprintf(OutF, "%d\n", MaxA);
  if (Test) {
    fprintf(OutF, "Signature:\n");
    fprintf(OutF, "%ld\n", Sign);
  }
  if (OutF != NULL)
    fclose(OutF);
  OutF = NULL;
  exit(0);
}

int Span(int x, int y)
{
  int d;

  if (Init)
    Abort("ERROR: Illegal Dialogue! Size must be called first!");
  if (x < 1 || x > N || y < 1 || y > N) {
    fprintf(OutF, "Span(%d,%d)\n", x, y);
    fflush(OutF);
    Abort("ERROR: Parameter out of range in call Span!");
  }
  if (x == y)
    Acc[x - 1]++;
  else {
    Acc[x - 1]++;
    Acc[y - 1]++;
  }

  d = abs(P[x - 1] - P[y - 1]);
  fprintf(OutF, "Span(%d,%d)=%d\n", x, y, d);
  fflush(OutF);

  if (Acc[x - 1] > MaxA)
    MaxA = Acc[x - 1];
  if (Acc[y - 1] > MaxA)
    MaxA = Acc[y - 1];

  if (MaxA > 4) {
    OutF = fopen("chain.out", "w");
    fprintf(OutF, "%d\n\n", MaxA);
    if (Test)
      fprintf(OutF, "%ld\n", Sign);
    if (OutF != NULL)
      fclose(OutF);
    OutF = NULL;

    Abort("ERROR: Illegal Dialogue! Atom accessed more than four times.");
  }
  return d;
}

