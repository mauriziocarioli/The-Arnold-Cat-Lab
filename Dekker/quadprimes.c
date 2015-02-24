/* Program quadprimes.c for quadratic fields programs. T J Dekker 2007-2012. */
/* To draw pictures of prime numbers (and prime ideals) in different colors. */
/* This program uses subprograms from files quadchar.c and quadsiev.c        */
/* and programming environment of Xcode system.                              */
/* main program of that system displays some pages numbered from 1,          */
/* page origin (0, height) is left upper cornor of those pages.              */

# define FillBlack CGContextSetCMYKFillColor(c, 0, 0, 0, 1, 1)     // char	
# define FillBlue  CGContextSetCMYKFillColor(c, 1, .3, 0, 0, 1)    // prime	
# define FillRed   CGContextSetCMYKFillColor(c, 0, 1, 0, 0, 1)     // unit
# define AddLineToPoint(x, y)    CGContextAddLineToPoint(c, x, y)

# define MAXFACS             4   //  maximum numbers of discriminant factors 
# define MAXPERIOD        1815   //  maximal period allowed by the program	
# define SIZE            40000   //  times 16 yields maximum capacity 640000	

# define X00                 7   //  x-coordinate of start of picture 		
# define Y00                35   //  y-coordinate of start of picture 
# define Y01                25   //  y-coordinate of start of character
# define Y11                15   //  y-coordinate of start of picture head	

CGContextRef c ; int yheight; 
int rad, maxnorm, discriminant, period, nfacs, facs[MAXFACS], 
	qchar[MAXPERIOD], deltac[MAXPERIOD]; short int prinorm[SIZE];

// Include one for discriminant = 0 or 1 modulo 4:
 # include "quadprim0mod4.c"
// # include "quadprim1mod4.c"

void norma()  /* calculates maximum norm */
{	int aa = AMAX * AMAX, bb = BMAX * BMAX, m; m = discriminant * bb /4; 
	maxnorm = ((discriminant < 0) ? aa - m : (m > aa) ? m : aa) + 1;
	if (maxnorm > capacity(SIZE)) maxnorm = capacity(SIZE);
}   /*  end norma  */

void heading(int rad) /* draws heading, radicand and character */
{	int imax, i; char q[50], qca[SMAX], signtoken[] = "-o+"; 
	CGContextSelectFont(c, "Monaco", FONTSIZE, kCGEncodingMacRoman);
	sprintf(q, "Primes  "); FillBlue;  // start page at (X00, Y11)
	CGContextShowTextAtPoint(c, X00, yheight - Y11, q, strlen(q));
	sprintf(q, "Units  "); FillRed; CGContextShowText(c, q, strlen(q));	
	ideal  // optional parameter calculation and text inclusion
	sprintf(q, "Q(V%d)  class %d  chi ", rad, clas); 
	FillBlack; CGContextShowText(c, q, strlen(q));
	imax = (peri > SMAX ? SMAX : peri);
	for (i = 0; i < imax; i++) qca[i] = signtoken[qchar[i] + 1];
	if (CMIN + imax <= SMAX) CGContextShowText(c, qca, imax);
	else CGContextShowTextAtPoint(c, X00, yheight - Y01, qca, imax);
}   /*  end heading  */

void process(int rad)  /* calculates and draws for given raicand */
{	disfactors(rad, &discriminant, &nfacs, facs); // factorize rad
	quadchar(discriminant, nfacs, facs, &period, qchar); // character
	norma();  // defined in inclusion: calculate maxnorm
	sievquad(nfacs, facs, qchar, SIZE, maxnorm, prinorm);  
	heading(rad); // print heading, radicand and character  	            	            
	picture();  // defined in inclusion: print primes and units
}   /*  end process  */

void mainpic(CGContextRef cgc, int height, int page)
/*  gets radicand rad depending on page number and calls process */
{	int inx, inxup = sizeof radicand / sizeof(int);
	c = cgc; yheight = height; inx = page - 1; 
	if (inx < inxup && (rad = radicand[inx]) != 0) process(rad); 
}   /*  end mainopic  */
