#include <netinet/in.h>
/*
socket address:
all the socket api takes generic address in form of struct sockaddr
but we can have multiple address - say for address for ipv4 is different from
ipv6 and address from same computer 
communication for internet ipv4 we use - struct sockaddr_in cast struct sockaddr_in to struct sockaddr

now at low level bytes are platform dependent - mostly two form these days
called endianess
1. big endian
2. little endian

so each computer can interpret same data differently so it was decided to
convert all data to big endian before sending so that each computer will decode
as big endian and gets same interpretation of data

so since address, port etc gets transferred around they also need to be in big
endian form

these functions are used to convert address to desired big endian form
htonl() - converts long to big endian, usually used for address
htons() - converts short to big endian, usually used for port
*/

/*
returning pointer from function - a big problem
can't be stack memory as it gets cleaned up when function returns
heap memory returned - users has to know it and they should take responsibility
of cleanup static memory - if this is returned it will persist during the whole
process (kinda unnecessary memory leak)
*/

struct sockaddr *create_internet_address() {
  // TODO: handle byte order to be big endian(network byte order)

  // i am doing static memory allocation for my internet address struct
  static struct sockaddr_in addr;
  // initialize addr
  addr.sin_family = AF_INET;   // ipv4 family
  addr.sin_port = htons(3000); // port
  // TODO: INADDR_LOOPBACK vs INADDR_ANY differences
  // ip address - loopback i.e. 127.0.0.1 here
  //todo: is htonl() required or INADDR_LOOPBACK) macro is already in big endian form
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  // cast internet address to generalized address
  return (struct sockaddr *)&addr;
}