# Created by: Horia Racoviceanu <horia@racoviceanu.com>
# $FreeBSD: head/databases/galera/Makefile 418767 2016-07-19 11:04:13Z mat $

PORTNAME=	galera
PORTVERSION=	25.3.20
DISTVERSIONPREFIX=	3-
PORTREVISION=	1
CATEGORIES=	databases
MASTER_SITES=	http://releases.galeracluster.com/source/

MAINTAINER=	info@galeracluster.com
COMMENT=	Synchronous multi-master replication engine

LICENSE=	GPLv2

LIB_DEPENDS=	libboost_date_time.so:devel/boost-libs
BUILD_DEPENDS=	checkmk:devel/libcheck ${LOCALBASE}/include/boost/shared_ptr.hpp:devel/boost-libs

USES=		execinfo python:build scons shebangfix ssl

.include <bsd.port.options.mk>

.if ${OSVERSION} < 1000000
USE_GCC=	4.8+
GCC_LIBS=	"${LOCALBASE}/lib/${_GCC_BUILD_DEPENDS}"
.else
CXX=            clang
LDFLAGS+=       -lc++
.endif

USE_LDCONFIG=	yes

LDFLAGS+=	-lboost_program_options -lboost_system
MAKE_ARGS+=	--config=force system_asio=0 deterministic_tests=1 -j 4

PLIST_FILES=	lib/libgalera_smm.so bin/garbd

OPTIONS_DEFINE=	DEBUG

.include <bsd.port.pre.mk>

.if ${PORT_OPTIONS:MDEBUG}
MAKE_ARGS+=	debug=3
.endif

do-install:
	${INSTALL_LIB} ${WRKDIR}/${DISTNAME}/libgalera_smm.so \
		${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} ${WRKDIR}/${DISTNAME}/garb/garbd \
		${STAGEDIR}${PREFIX}/bin/

.include <bsd.port.post.mk>
