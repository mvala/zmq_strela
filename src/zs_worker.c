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
    printf(" -b tcp://<ip>:<port>   : for workers\n");
    printf(" -m <msg>               : msg to send\n");
    printf("\n");
    printf("Example:");
    printf(" zs_client -b tcp://localhost:5555\n");
    printf("\n");
    exit(1);
}

int main(int argc, char *argv[])
{

  char *broker;
  broker = strdup("tcp://localhost:5555");
  char *msg_str;
  msg_str = strdup("empty");

  while ((argc > 1) && (argv[1][0] == '-')) {
    switch (argv[1][1]) {
      
    case 'b':
      free(broker);
      broker = strdup(argv[2]);
      ++argv;
      --argc;
      break;
    case 'm':
      free(msg_str);
      msg_str = strdup(argv[2]);
      ++argv;
      --argc;
      break;
    default:
	printf("Wrong Argument: %s\n", argv[1]);
	usage();
	break;
    }
    ++argv;
    --argc;
  }

  printf("Connecting to broker %s ...\n",broker);
  zctx_t *ctx = zctx_new();
  void *b_sock = zsocket_new(ctx, ZMQ_PUSH);
  assert(b_sock);

  int rc;
  /* connecting to master */
  rc = zsocket_connect(b_sock, broker);
  assert(!rc);

  zmsg_t *msg = zmsg_new();;
  /* send packet */
  rc = zmsg_addstr(msg, msg_str);
  assert(rc == 0);
  
  printf ("Sending msg='%s' ...\n",msg_str);
  /* zmsg_dump(msg); */
    
  /* sending message */
  rc = zmsg_send(&msg, b_sock);
  assert(rc == 0);

  /* wait for message to be sent */
  zclock_sleep(100);

  zmsg_destroy(&msg);
  
  free(broker);
  free(msg_str);
  
  /* everything should be cleanly closed now */
  zctx_destroy(&ctx);
  
  return 0;
}
