# include <stdio.h>
# include <string.h>

int  main()
{
	const char *largestring = "Foo Bar Baz";
    const char *smallstring = "Bar";
    char *ptr;

    ptr = strnstr(largestring, smallstring, 6);

	printf("%s\n", ptr);

}