#include <netinet/in.h>

// any internet address is represented as ip and port combination
// convert ip and port to struct sockaddr_in and which in turn is casted to
// general address struct sockaddr
struct sockaddr *create_internet_address() {
  // TODO: handle byte order to be big endian(network byte order)

  // i am doing static allocation for my internet address struct
  static struct sockaddr_in addr;
  // initialize addr
  addr.sin_family = AF_INET;   // ipv4 family
  addr.sin_port = htons(3000); // port
  // TODO: INADDR_LOOPBACK vs INADDR_ANY differences
  // ip address - loopback i.e. 127.0.0.1 here

  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  // cast internet address to generalized address
  return (struct sockaddr *)&addr;
}