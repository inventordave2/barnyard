#include <string.h>
#include <stdlib.h>
#include "barnyard.h"

enum status setTxtTheme(char * theme)	{
	
	struct App App_;
	
	for (int i = 0; i < App_.ThemeCount; i++)		
		if(cmp(App_.Themes[i].name, theme))	{
			
			App_._Theme = App_.Themes[i];
			return SUCCESS_;
		}
	
	return ERROR_;
};

int cmp(char *a, char *b) { // returns true (1) if the 2 c-strings match, as it should...

	return (strcmp(a, b) == 0);
}

void rotate(unsigned int * argc, char * argv[], int * _free)	{

	for(int i = 0; i < (*argc - 1); i++)	{
		
		argv[i] = argv[i+1];
	}

	argv[*argc - 1] = '\0';
	*argc -= 1;
}
// fsd.exe
// -ci 
// -c off
// -f "fs.c" +i "Kit"
void flipstr(char * in, char * out)	{
	
	unsigned int len = strlen(in);
	
	for(signed int i = len - 1; i >= 0; i--)
		*(out++) = *(in+i);
	
	*out = '\0';
}

char * itoa2(int v)	{
	
	// snprintf (buff, sizeof(buf), "%d",n); // print int 'n' into the char[] buffer
	char * s = allocs(16);
	
	snprintf (s, 16, "%d", v);
	
	return s;
}

double qdiv(double n, double d)	{
	
	double i = log10(n) - log10(d);
	
	double r = i * M_LN10;
	double x = exp(r);
	// 10 ** i also gives the answer.
	
	return x;
}

double qdiv_i(int n, int d)	{
	
	return qdiv( (double) n, (double) d );
}

/*
* function: (char *) safecat(char * str1, char *str2)
*
* definition: 	arg0 = (char *) str1
*				arg1 = (char *) str2
*
*				safely concatenates str2 to str1, both re-populating str1, and returning it's pointer.
*
* uses:			realloc()
*				strcat()
*/
#define ERR_NP_CHAR 1
char * safecat(char * s, char * rhs)	{
	
	// SAFETY
	if( (s==NULL) || (rhs==NULL) )
		return s;
	
	// check s, rhs, for nonprintable chars (0-31)
	
	unsigned int i = 0;
	char ch = '\0', chr = '\0';
	char * _s = s; char * _rhs = rhs;
	
	do	{
		
		if( ch = _s[0] )	{
			
			if( ch < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_s;

		if( chr = _rhs[0] )	{
		
			if( chr < (char)32 || ( (ch > 127) & (ch < 160) ) )
				return (char *)ERR_NP_CHAR;
		} // dangling-else!
		else
			--_rhs;
		
		++_s;
		++_rhs;

	} while (ch != '\0' || chr != '\0');
	
	char * _ = (char *)malloc( strlen(s) + strlen(rhs) +1 );
	if( _ == NULL )
		return (char *)NULL;
	
	strcpy(_, s);
	strcat(_, rhs);
	
	free(s);
	
	// Do safety check on composite string _, before returning the cstring pointer to the caller.
	// ... 1. remove any non-alphabetical control codes, though printable.

	return (s = _);
}




double expound(double base, int exp)	{	// currently int-only, at least for exponent. The base can be decimal.
	
	double lv = 1.0;
	
	for (int i = 0; i < exp; i++)
		lv *= base;
	
	char * msg = allocs(40);
	sprintf(msg, "%f exp(%f) := %f .", base, exp, lv);
	printf(msg);
	free(msg);
	
	return lv;
}

int prime(unsigned int i, unsigned int n, short unsigned int f)	{ 	// i = ith prime number, if n is set, i is ignored. n will test for a prime number. f is a flag, set to TRUE if you want reports.
	
	if(n!=0)	{
		// trial division algorithm, divide n by every integer between 2 and sqrt(n), as at n = a . b, either a
		// or b will not be bigger than sqrt(n), which means all tests have been performed
		
		if(n==1)	{
			// base case: 1, the smallest prime number is 2...
			
			if(f!=0)
				printf("1 is too small to be a prime number! The smallest prime number is 2.");
			
			return 0;
		}
		
		if(n==2)	{
			// base case 2, it interferes with the test conditional, as 2 % 2 == 0, which fails the value 2 for the test. 
			// Subsequent n % k tests don't have to check if n == k, as k will never be more than sqrt(n)
			
			if(f!=0)
				printf("2 is the 1st Prime, you know that!");
			
			return n;
		}
		
		unsigned int sqrt_ = ceil(sqrt(n)) + 1;
		for (unsigned int k = 2; k < sqrt_; k++)
			if((n % k) == 0)	{
				
				if(f!=0)
					printf("%d is NOT prime. It was divisable at %d.\n", n, k);
				
				return 0;
			}
		
		if(f!=0)
			printf("%d IS A PRIME NUMBER!\n", n);
		
		return n;
	}
	
	n = 1;
	unsigned int j = 0;
	unsigned int p = 0;
	
	while(1)	{
		
		n++;
		if(p = prime(0, n, 0))	{
			
			j++;
			if(j==i)
				break;
		}
	}
	
	printf("Prime number %d is %d.", i, p);
	return p;
}


int primedata(unsigned int min, unsigned int max, unsigned int step)	{
	// step: if set to 1, the step increment is to accumulate +1 for each prime number discovered.
	// if set to 2, the step increment is the distance to the current prime from the last prime (v. low number, usually single digits)
	// otherwise, the step increment is accumulative of each step-change between each pair of current & last prime number.
	// remember, the only even prime number is 2, so only need to check odd-numbers.
	
	char * s = allocs(1024*8*10);
	
	unsigned int p = 0;
	unsigned int p2 = 0;
	unsigned int c = 0;
	
	max += 1;
	
	if(min<=2)	{
	
		cat(5, s, "['", itoa2(2), "', ", itoa2(0), "],\n");
		
		/**
		strcat(s, itoa(2));
		strcat(s, "', ");
		strcat(s, itoa(0));
		strcat(s, "],\n");
		*/
		
		min = 3;
		
		p2 = prime(0, 2, 0);
		c++;
	}
	
	if((min%2)==0)
		min++;
	
	if(p2==0)
		p2 = prime(0, min, 0);
	
	while(min<max)	{
		
		if(p = prime(0, min, 0))	{
			
			if(step==1)
				c++;
			
			else if(step==2)
				c = p - p2;
			
			else
				c = c + (p - p2);
			
			sprintf(s, "%s%s%d", s, "['", p);
			strcat(s, "', ");
			strcat(s, itoa2(c));
			strcat(s, "],  ");
			
			p2 = p;
		}
		
		min += 2;
	}

	printf("\n%s\n", s);

	free(s);
	return 1;
	
	/**
	
		The outputted string is in the following format, but the numbers will be different:
		
		['2',  2],
		['3',  3],
		['4'   3],
		['5',  5]	
	*/
}

/*
* function: (char *) cat(argc, str1, str2, ..., strN)
*
* definition: arg0 = (int) num of subsequent variadic arguments to concatenate to str1. Returns concatenated string, as well as populating str1 with the concatenated string.
*
* uses: safecat(str1, str2)
*/
char * cat(int c, char * s, ...)	{
	
	va_list ap;
	char * _ = (char *)malloc(4096);
	_[4095] = '\0';
	
	strcpy(_, s);

	va_start(ap, c);
	for(short int i=0; i<c; i++)	{
	
		_ = safecat(_, (char *)va_arg(ap, char*));
	}
	va_end(ap);
	
	DEBUG_MSG("exiting cat()")
	return _;
}

