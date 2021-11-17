#include "unp.h"

void
str_cli(FILE * fp, int sock)
{
    fd_set rset;
    char buf[MAXLINE];

    int stdineof = 0, n = 0;
    FD_ZERO(&rset);

    for ( ; ; ) {
        if (!stdineof) {
            FD_SET(fileno(fp), &rset);
        }

        FD_SET(sock, &rset);

        Select(max(fileno(fp), sock) + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) {
            if ( (n = Read(sock, buf, MAXLINE)) == 0) {
                if (stdineof) 
                    return;
                else
                    err_quit("str_cli: server terminated prematurely");
            } 
            Write(fileno(fp), buf, n);
        }
        if (FD_ISSET(fileno(fp), &rset)) {
            if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
                stdioeof = 1;
                Shutdown(sock, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Write(sock, buf, n);
        }
    }
}