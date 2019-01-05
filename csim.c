#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
int s,E,b;

int main(int argc, char * argv[])
{
    char c ;
    while((c=getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch(c)
        {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                break;
        }
    }
    printSummary(0, 0, 0);
    return 0;
}
