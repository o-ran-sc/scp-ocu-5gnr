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


extern int opt_debug;

#define	ASN_DEBUG(fmt, args...)	do {		\
		if(opt_debug < 2) break;	\
		fprintf(stderr, fmt, ##args);	\
		fprintf(stderr, " (%s:%d)\n",	\
			__FILE__, __LINE__);	\
	} while(0)
