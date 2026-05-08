#pragma once

// 1. Forçar o compilador a usar as definições de tempo e tipos do sistema primeiro
#include <sys/types.h>
#include <sys/time.h>

// 2. Trava de compatibilidade para o lwIP não tentar redeclarar funções POSIX
// Isso evita o erro de "extern" vs "static"
#ifndef LWIP_COMPAT_SOCKETS
#define LWIP_COMPAT_SOCKETS 0
#endif

#define LWIP_TIMEVAL_PRIVATE 0

// 3. Incluir os headers do lwIP ANTES do sys/socket.h do ESP-IDF
#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/inet.h"
#include "lwip/ip4_addr.h"

// 4. Agora incluímos o socket do sistema
#include <sys/socket.h>

// 5. LIMPEZA TOTAL (Para o C++ não confundir com std::ostream ou std::bind)
#undef write
#undef read
#undef close
#undef socket
#undef select
#undef accept
#undef shutdown
#undef getsockopt
#undef setsockopt
#undef getpeername
#undef getsockname
#undef connect
#undef bind
#undef inet_ntop
#undef inet_pton 

// --- AJUSTE PARA MULTICAST (Erro dos 67%) ---

// 1. Garante que as macros de Multicast existam para o FORTE
#ifndef IP_MULTICAST_IF
#define IP_MULTICAST_IF 6
#endif
#ifndef IP_ADD_MEMBERSHIP
#define IP_ADD_MEMBERSHIP 3
#endif

// 2. Define a estrutura ip_mreq se o compilador nao a encontrou
// Isso resolve o erro "incomplete type" no bsdsocketinterf.cpp
#ifndef _IP_MREQ_DEFINED
#define _IP_MREQ_DEFINED
/* struct ip_mreq {
  struct ip_addr imr_multiaddr;
  struct ip_addr imr_interface;
};
*/
#endif
