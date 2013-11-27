/*
  Copyright (c) 2013 Other contributors as noted in the AUTHORS file

  This file is part of ZMQ_STRELA.

  ZMQ_STRELA is free software; you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  ZMQ_STRELA is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <czmq.h>

void usage(void)
{
    printf("Usage:\n");
    printf(" -w tcp://*:<port>   : for workers\n");
    printf(" -c tcp://*:<port>   : for client\n");
    printf(" -v                  : for verbos\n");
    printf("\n");
    printf("Example:");
    printf(" zs_broker -w tpc://*:5555 -c tpc://*:5556\n");
    printf("\n");
    exit(1);
}

int main(int argc, char *argv[])
{

  char *wk_bind;
  char *cl_bind;
  int verbose;

  wk_bind = strdup("tcp://*:5555");
  cl_bind = strdup("tcp://*:5556");
  verbose = 0;

  while ((argc > 1) && (argv[1][0] == '-')) {
    switch (argv[1][1]) {
      
    case 'w':
      free(wk_bind);
      wk_bind = strdup(argv[2]);
      ++argv;
      --argc;
      break;
    case 'c':
      free(cl_bind);
      cl_bind = strdup(argv[2]);
      ++argv;
      --argc;
      break;
    case 'v':
      verbose = 1;
      break;
      
    default:
	printf("Wrong Argument: %s\n", argv[1]);
	usage();
	break;
    }
    ++argv;
    --argc;
  }


  zctx_t *ctx = zctx_new();
  void *wk_sock = zsocket_new(ctx, ZMQ_PULL);
  assert(wk_sock);
  void *cl_sock = zsocket_new(ctx, ZMQ_PUB);
  assert(cl_sock);

  printf("Broker started wk=%s cl=%s ... \n",wk_bind,cl_bind);

  int rc;
  /* binding for workers */
  rc = zsocket_bind(wk_sock, wk_bind);
  assert(rc >= 0);

  /* binding for clients */
  rc = zsocket_bind(cl_sock, cl_bind);
  assert(rc >= 0);

  int timeout = -1;
  while (!zctx_interrupted) {
    zmq_pollitem_t items[] = {{ wk_sock, 0, ZMQ_POLLIN, 0 }};
    zmq_poll(items, 1, timeout);
    if (items[0].revents & ZMQ_POLLIN) {
      
      zmsg_t *msg = zmsg_recv(wk_sock);
      if (!msg)
	break; /* Interrupted */
      
      /* we require that message contain at least 2 frames */
      /* assert(zmsg_size(msg) >= 2); */
      
      if (verbose) zmsg_dump(msg);
      
      zmsg_send(&msg, cl_sock);
    }
    
  }
    
  /* everything should be cleanly closed now */
  
  free(wk_bind);
  free(cl_bind);
  
  zctx_destroy(&ctx);
  
  return 0;
}
