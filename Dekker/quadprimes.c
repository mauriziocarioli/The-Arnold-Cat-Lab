/* Program quadprimes.c for quadratic fields programs. T J Dekker 2007-2012. */
/* To draw pictures of prime numbers (and prime ideals) in different colors. */
/* This program uses subprograms from files quadchar.c and quadsiev.c        */
/* and programming environment of Xcode system.                              */
/* main program of that system displays some pages numbered from 1,          */
/* page origin (0, height) is left upper cornor of those pages.              */

# define IsPrime c = 'p'	
# define IsUnit c = 'u'
# define IsIdeal c = 'i'
# define IsCoIdeal c = 'c'

# define MAXFACS             4   //  maximum numbers of discriminant factors 
# define MAXPERIOD        1815   //  maximal period allowed by the program	
# define SIZE            40000   //  times 16 yields maximum capacity 640000	

int rad, maxnorm, discriminant, period, nfacs, facs[MAXFACS], 
	qchar[MAXPERIOD], deltac[MAXPERIOD]; 
short int prinorm[SIZE];

// Include one for discriminant = 0 or 1 modulo 4:
//# include "quadprim0mod4.c"
# include "quadprim1mod4.c"

void norma()  /* calculates maximum norm */
{	
  int aa = AMAX * AMAX, bb = BMAX * BMAX, m; 
  m = discriminant * bb /4; 
  maxnorm = ((discriminant < 0) ? aa - m : (m > aa) ? m : aa) + 1;
  if (maxnorm > capacity(SIZE)) 
    maxnorm = capacity(SIZE);
}   /*  end norma  */

void heading(int rad) /* draws heading, radicand and character */
{	
  int imax, i; 
  char q[50], qca[SMAX], signtoken[] = "-o+"; 
  printf("\t{\n");
  printf("\t\t{\"radicand\",%d,\"class\",%d,\n\t\t ", rad, clas);
  ideal;  // optional parameter calculation and text inclusion
  printf("\"chi\",\"");
  imax = (peri > SMAX ? SMAX : peri);
  for (i = 0; i < imax; i++) 
    qca[i] = signtoken[qchar[i] + 1];
  if (CMIN + imax <= SMAX) 
    for(i = 0; i < imax; i++) printf("%c",qca[i]);
  else 
    for(i = 0; i < imax; i++) printf("%c",qca[i]);
  printf("\"},\n");
  printf("\t\t{\n");
}   /*  end heading  */

void process(int rad)  /* calculates and draws for given raicand */
{
  disfactors(rad, &discriminant, &nfacs, facs); // factorize rad
  quadchar(discriminant, nfacs, facs, &period, qchar); // character
  norma();  // defined in inclusion: calculate maxnorm
  sievquad(nfacs, facs, qchar, SIZE, maxnorm, prinorm);  
  heading(rad); // print heading, radicand and character  	            	            
  picture();  // defined in inclusion: print primes and units
}   /*  end process  */

//void mainpic(CGContextRef cgc, int height, int page)
void main()
/*  gets radicand rad depending on page number and calls process */
{	
  int inx;
  printf("QN =\n");
  printf("{\n");
  for (inx = 0; (rad = radicand[inx]) != 0; inx++)
    process(rad);
  printf("};");
}   /*  end mainopic  */
