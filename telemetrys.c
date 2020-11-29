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
#define NLISTEN 1
char *program_name;
#include "skel/skel.h"
#define TWOINTS ( sizeof( int ) * 2 )
#define THREEINTS ( sizeof( int ) * 3 )
int main( int argc, char **argv )
{
    SOCKET s;
    SOCKET s1;
    int rc;
    int i = 1;
    int pkt[ 3 ];
    INIT();
    s = tcp_server( NULL, argv[ 1 ] );
    s1 = accept( s, NULL, NULL );
    if ( !isvalidsock( s1 ) )
        error( 1, errno, "accept failure" );
    for ( ;; )
    {
        rc = recv( s1, ( char * )pkt, TWOINTS, 0 );
        if ( rc != TWOINTS )
            error( 1, 0, "recv returned %d\n", rc );
        else if ( ntohl( pkt[ 0 ] ) == 3 )
        {
            if ( sizeof( int ) != recv( s1, ( char * )pkt + TWOINTS, sizeof( int ), 0 ) )
                error( 1, 0, "recv failure");
            rc += sizeof( int );
        }
        printf( "Packet %d has %d values in %d bytes\n", i++, ntohl( pkt[ 0 ] ), rc );
    }
}