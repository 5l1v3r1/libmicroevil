SHLIB=		microevil
SHLIB_MAJOR=	0
SRCS=		microevil.c
MAN=

CFLAGS+=	-I${.CURDIR}

.include <bsd.lib.mk>
