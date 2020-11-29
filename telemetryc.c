#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
char *program_name;
#include "skel/skel.h"
int main( int argc, char **argv )
{
    SOCKET s;
    int rc;
    int i;
    int pkt[ 3 ];
    INIT();
    s = tcp_client( argv[ 1 ], argv[ 2 ] );
    for ( i = 2;; i = 5 - i )
    {
        pkt[ 0 ] = htonl( i );
        rc = send( s, (char * )pkt, i * sizeof( int ), 0 );
        if ( rc < 0 )
            error( 1, errno, "send failure" );
        sleep( 0 );
    }
}