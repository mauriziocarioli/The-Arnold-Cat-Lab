/* quadideal3.c for quadratic fields of class nr 2.  T J Dekker, 2012-2013. */
/* Include in quadprim0mod4.c and quadprim1mod4.c to draw prime co-ideals.  */
/* The programs use subprograms from files quadchar.c and quadsiev.c        */
/* and programming environment of Xcode system.                             */

int bynorm, natp[] = {2, 3, 5, 7, 11};

# undef   CMIN
# define  CMIN       40 

# undef  ideal
# define ideal       param();  

# undef  testx
# define testx  else if (norm % bynorm==0 && inset(norm/bynorm, prinorm)) IsIdeal;

void param()  
/*  calculates and draws bynorm == smallest prime p such that chi(p) >= 0  */
/*  bynorm is norm of non-principal ideal correctly for radicand < 34      */
{	
  int k; 
  char q[50];
  for (k = 0; qchar[natp[k]] < 0; k++) 
    ; 
  bynorm = natp[k];
  printf("\"bynorm\",%d,\n\t\t", bynorm); 
}   /*  end param  */

