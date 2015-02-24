/* quadprim0mod4.c for quadratic fields, d = 0 mod 4, T J Dekker, 2007-2013. */
/* Include in quadprimes.c to draw pictures of primes and units in colors.   */
/* Optionally also prime non-principal ideals (co-ideals) are drawn.         */
/* The programs use subprograms from files quadchar.c and quadsiev.c         */
/* and programming environment of Xcode system.                              */

# define SMAX           79        //  (113) maximum length character to draw	
# define CMIN           28        //  length of heading text

# define AMAX           470       //  (67) getallen x + y Ã rad, |x| <= AMAX	
# define BMAX           470       //  (49)                    en |y| <= BMAX	
# define QNORM(x, y)	abs(x*x-(discriminant/4)*y*y)  // norm of x + y Ãrad 
# define peri           period    //  to draw chi over one period

# define ideal                    //  empty if no co-ideals are drawn
# define testx                    //  empty test

/*  Select class number either 1, 2, or 3, and corresponding radicand row
    Moreover, optional include to draw prime co-ideals.
*/

//int clas = 1, radicand[] = {-2,-1,2,3,6,7,11,14,19,22,23,31,0};
//int clas = 2, radicand[] = {-58,-37,-22,-13,-10,-6,-5,10,15,26,30,0};
//# include "quadideal2.c"
int clas = 3, radicand[] = {79,142,223,254,326,0};
# include "quadideal3.c"

void printnumber(int x, int y, char c)
{
  printf("\t\t\t{{%d,%d}, \"%c\"},\n",x,y,c);
}

void picture() /* draws picture of primes, units and option prime ideals */
{	
  int a, b, norm;
  char c, prime = 'p', unit = 'u';
  for (b = -BMAX; b <= BMAX; b++) 
    for (a = -AMAX; a <= AMAX; a++)
      {	
	norm = QNORM(a, b);	
	if (norm < maxnorm)
	  {	
	    if (inset(norm, prinorm)) 
	      IsPrime;
	    else if (norm == 1) 
	      IsUnit;
	    testx  // optional extra test for co-ideals
	    else goto nodraw; 
	   // draw square at given central coordinates:
	    printnumber(a,b,c);
	  }
      nodraw: ;
      }
  printf("\t\t}\n");
  printf("\t},\n");
}   /*  end picture  */
