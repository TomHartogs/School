#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    char *p;
    
    // print out the default cgi header
    printf("Content-Type: text/html\n\n");

    // print out the html header
    printf("<html>\n<head>\n<title>EL Webserver CGI example </title></head><body>");

	printf("<p>follow up link by ?*yourQuery* to show te string entered.</p>");		 
	printf("<p>Example: 192.168.0.50/cgi-bin/mycgiscript?test</p>");		 
	
    // print out some html based on the query string
    p=getenv("QUERY_STRING");
    if (p==NULL)
		 printf("<p>Query String is Empty</p>");
    else 
		printf("<p>Query String: %s</p>\n",p);

    // print out the html footer
    printf("</body></html>");
    return 0;
}
