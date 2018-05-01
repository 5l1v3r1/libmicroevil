#ifndef _MICROEVIL_H
#define	_MICROEVIL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct sandbox_impl {
	int (*sandbox_init)(void *);
	void (*sandbox_fini)(void);
	void *(*sandbox_cfg_new)(void);
	int (*sandbox_is_active)(void);
	int (*sandbox_open)(const char *, int, mode_t, cap_rights_t *);
	int (*sandbox_mkdir)(const char *, mode_t);
	int (*sandbox_unlink)(const char *);
	int (*sandbox_socket)(int, int, int, cap_rights_t *);
	int (*sandbox_getaddrinfo)(const char *, const char *,
	      const struct addrinfo *, struct addrinfo **);
	void (*sandbox_freeaddrinfo)(struct addrinfo *);
	int (*sandbox_connect)(int, const struct sockaddr *, socklen_t);
	int (*sandbox_stat)(const char *, struct stat *);
	int (*sandbox_chmod)(const char *, mode_t);
	int (*sandbox_chown)(const char *, uid_t, gid_t);
	int (*sandbox_rename)(const char *, const char *);
	int (*sandbox_close)(int);
	const char *(*sandbox_intern_string)(const char *);
	int (*sandbox_add_addrinfo)(const char *);
	void (*sandbox_free_getaddrinfo_cache)(void);
	void (*sandbox_disable_getaddrinfo_cache)(void);
	int (*sandbox_cfg_allow_open_filename)(void **, char *);
	int (*sandbox_cfg_allow_openat_filename)(void **, char *);
	int (*sandbox_cfg_allow_stat_filename)(void **, char *);
	int (*sandbox_cfg_allow_chown_filename)(void **, char *);
	int (*sandbox_cfg_allow_chmod_filename)(void **, char *);
	int (*sandbox_cfg_allow_rename)(void **, char *, char *);
} sandbox_impl_t;

#endif
