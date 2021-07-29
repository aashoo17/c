## namespace, communication style, protocol:
**communication style/type of socket**  
way of sending data over internet   
SOCK_STREAM - sending stream of bytes  
SOCK_DGRAM - datagram or chunk of bytes are send  
SOCK_RAW - raw socket  
**namespace/domain**  
local namespaces - this are used local communication in same computer
AF_LOCAL, AF_UNIX, AF_FILE  
internet namespaces -  
AF_INET - ipv4  
AF_INET6 - ipv6  

**protocol**  
a combination of namespace and communication style uses some sort of protocol
there may multiple protocol possible and linux uses one as default  
internet namespace + SOCK_STREAM = default protocol is tcp  
internet namespace + SOCK_DGRAM = default protocol is udp  

## socket address:
struct sockaddr is used as address of the socket this struct is used for generic address representaion  
each namespaces may use different struct say for internet namespace uses struct sockaddr_in  
so we have to cast struct sockaddr_in => struct sockaddr  

## internet address:
create this struct sockaddr_in  
initialize its fields - family, port, address  
family is AF_INET for ipv4 and AF_INET6 for ipv6  
address field:  
this field is struct in_addr with one member s_addr  
we usually write this as "127.0.0.1" notation but can't be used directly
use some predefined constants - INADDR_LOOPBACK which is very common for "127.0.0.1"  
we can use functions in arpa/inet.h for conversion  
inet_addr()  
inet_aton()  
inet_network()  
inet_ntoa()  

## byte order:
different computers/processors uses different endianness to store data - 1. big endian 2. little endian  
we use big endianess for working over internet   
so we might need to convert bytes to big endian (network byte order) if not already in that format - as address (ip and port) will be sent over network
netinet/in.h  
provides functons to do so  
htons()  
htonl() etc  

## protocol datbases:
usually we use default protocol  
if we need any existing/possible protocol to be used  
TODO: write how we can do so 

## host names:
converting say "www.google.co.in" to ip_address form

## client vs server side code:

**for TCP:**  
server side calls:  
socket(), bind(), listen(), accept(), read()/write(), close()  
client side calls:  
TODO: since no bind call is made what address the socket will get here  
socket(),connect(),write()/read(), close()

**for UDP:**  
server side calls:  
socket(), bind(), recvfrom()/sendto(), close()  
client side calls:   
TODO: since no bind call is made what address the socket will get here  
socket(), recvfrom(), sendto(), close()  
or
socket(),connect(), read()/write(), close()  
