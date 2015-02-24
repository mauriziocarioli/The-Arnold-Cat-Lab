/* Program chardlist.c prints quadratic characters,  T J Dekker, 2009-2013.  */
/* Prints list of characters for discriminants between  -MAXDIS and +MAXDIS. */
/* It uses subprograms disfactors and quadchar from file quadchar.c.         */

# define MAXPERIOD 		400 
# define MAXDIS    		 80
# define MAXFACS   		  3
	
# include <stdio.h>
# include <stdlib.h>

int period, facs[MAXFACS], qchars[MAXPERIOD];

	main ()
{	int rad, dis, nfacs, i; char signtoken[] = "-o+";
	printf ("\n%s\n", " discriminant      quadratic character");
	for (rad = -MAXDIS; rad <= MAXDIS; rad++)
	{	disfactors (rad, &dis, &nfacs, facs);
		if  (rad == dis)  		 
		{	quadchar (dis, nfacs, facs, &period, qchars);
			printf ("\n%4d  ", dis);      
			for (i = 0; i < abs(dis); i++) 
				printf ("%c", signtoken[qchars[i] + 1]); 
		}   
	}   /*  end for rad  */
	printf ("\n\n");
} 
	 




