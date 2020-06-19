/******************************************************************************
*
*   Copyright (c) 2020 ICT/CAS.
*
*   Licensed under the O-RAN Software License, Version 1.0 (the "Software License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       https://www.o-ran.org/software
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*******************************************************************************/

#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <ucontext.h>
#include <stdlib.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <execinfo.h>
#include <getopt.h>
#include <pthread.h>
#include <memory.h>
#include <regex.h>

#include <stdio.h>  /* for the printf() function */

/* includes required to create a fake IP packet */
#include <netinet/ip.h>  /* for the IPv4 header */
#include <string.h>      /* for the strlen() */
#include <rohc/rohc_buf.h>  /* for the rohc_buf_*() functions */

/* includes required to use the compression part of the ROHC library */
#include <time.h>             /* required by time() */
#include <rohc/rohc_comp.h>   /* for rohc_comp_*() functions */


struct rohc_comp * create_compressor();
bool compress_with_callback(struct rohc_comp *const compressor,struct rohc_buf uncomp_packet,struct rohc_buf *const packet);
