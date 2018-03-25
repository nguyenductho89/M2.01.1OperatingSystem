//
//  main.c
//  Testing
//
//  Created by Nguyễn Đức Thọ on 3/25/18.
//  Copyright © 2018 Nguyễn Đức Thọ. All rights reserved.
//


#include <stdio.h>

int
main ()
{
    printf ("initial\n");
    printf ("id: %d, parent: %d\n", getpid (), getppid ());
    fork ();
    printf ("   first fork\n");
    printf ("   id: %d, parent: %d\n", getpid (), getppid ());
    
    
    fork ();
    printf ("       second fork\n");
    printf ("       id: %d, parent: %d\n", getpid (), getppid ());
    
    fork ();
    printf ("           third fork\n");
    printf ("           id: %d, parent: %d\n", getpid (), getppid ());
    
    return 0;
}

