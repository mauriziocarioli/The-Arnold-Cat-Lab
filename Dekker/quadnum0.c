/* Program quadradatic rings, discriminant = 0 mod 4, T J Dekker 2003, 2011. */
/* prints character and picture of size |a| <= AMAX, |b| <= BMAX,            */
/* for each prime the last decimal digit of its norm, for each unit a +sign. */
/* main program uses subprograms from files quadchar.c and sievquad.c.       */

# include <stdlib.h>
# include <stdio.h>
	
# define MAXFACS          3     //  maximum numbers of discriminant factors 
# define MAXPERIOD      400     //  maximal period allowed by the program 
# define SIZE         12500     //  times 16 yields maximum capacity 200000 
# define AMAX            19     //  getallen  x + y � rad  voor |x| <= AMAX 
# define BMAX            19     //                     en  voor |y| <= BMAX 
# define QNORM(x, y)    abs(x * x + coef2 * (y * y)) // norm of x + y � rad 

int maxnorm, discriminant, period, coef2, nfacs, facs[MAXFACS], 
	qchar[MAXPERIOD], deltac[MAXPERIOD]; short int prinorm[SIZE];
int radicand[] =  /*  Unique Factorization Domains, discriminant = 0 mod 4  */
	{-2, -1, 2, 3, 6, 7, 11, 14, 19, 22, 23, 31}; 		  	

void norma()  /*  calculate maximum norm  */
{	
  int m, aa = AMAX * AMAX, bb = BMAX * BMAX;  
  m = discriminant * bb /4; 
  maxnorm = ((discriminant < 0) ? aa - m : (m > aa) ? m : aa) + 1;
  if (maxnorm > capacity(SIZE)) 
    maxnorm = capacity(SIZE);
}   /*  end norma  */
	
void heading(int rad)  /*  prints radicand and character  */
{	
  int i; 
  char signtoken[] = "-o+"; 
  printf("\n\n Q(V%d)  chi ", rad); 
  for (i = 0; i < period; i++) 
    printf("%c", signtoken[qchar[i] + 1]);
  printf("\n");
}   /*  end heading  */
	
void picture()  /*  prints picture of primes and units  */
{	
  int a, b, qnm; 
  extern int period, coef2; 
  coef2 = - discriminant / 4;
  for (b = - BMAX; b <= BMAX; b++) 
    {	
      printf("\n");
      for (a = - AMAX; a <= AMAX; a++)  
	// too big or prime or unit or composite number:
	if ((qnm = QNORM(a, b)) >= maxnorm) 
	  printf("  ");
	else if (inset(qnm, prinorm)) 
	  printf(" %i", qnm % 10);
	else if (qnm == 1) 
	  printf(" +");
	else printf("  ");
    }
  printf("\n");
}   /*  end picture  */

void process(int rad)  /* calculate and print for given radicand */
{	
  disfactors(rad, &discriminant, &nfacs, facs); // factorize radicand
  quadchar(discriminant, nfacs, facs, &period, qchar); // character
  norma();  // calculate maxnorm
  sievquad(nfacs, facs, qchar, SIZE, maxnorm, prinorm); // prime norms  
  heading(rad); // print heading, radicand and character  	            	            
  picture(); // print primes and units
}   /*  end process  */
	
main ()  /*  get radicand and call process  */
{	
  int rad, k, kup = sizeof radicand / sizeof(int);  	        
  for (k = 0; k < kup && (rad = radicand[k]) != 0; k++) 
    process(rad);
} 
