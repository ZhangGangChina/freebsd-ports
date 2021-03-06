PORTNAME?=	mysql-wsrep
PORTVERSION=	5.6.35
PORTREVISION?=	0
CATEGORIES=	databases ipv6
MASTER_SITES=	http://releases.galeracluster.com/source/
DISTFILES=	mysql-wsrep-5.6.35-25.19.tar.gz
DISTNAME=	mysql-wsrep-5.6.35-25.19
PKGNAMESUFFIX?=	56-server
DATADIR=        ${PREFIX}/share/mysql

MAINTAINER=	info@galeracluster.com
COMMENT?=	A version of MySQL modified for Galera replication (server package)

BROKEN_powerpc64=	Does not build

SLAVEDIRS=	databases/mysql56-client
USES=		cmake shebangfix

BUILD_DEPENDS=	bison:devel/bison

RUN_DEPENDS=	socat:net/socat lsof:sysutils/lsof netcat:net/netcat rsync:net/rsync

.include <bsd.port.options.mk>

CXX=            clang++
CC=             clang

CMAKE_ARGS+=	-DINSTALL_DOCDIR="share/doc/mysql" \
		-DINSTALL_DOCREADMEDIR="share/doc/mysql" \
		-DINSTALL_INCLUDEDIR="include/mysql" \
		-DINSTALL_INFODIR="info" \
		-DINSTALL_LIBDIR="lib/mysql" \
		-DINSTALL_MANDIR="man" \
		-DINSTALL_MYSQLDATADIR="/var/db/mysql" \
		-DINSTALL_MYSQLSHAREDIR="share/mysql" \
		-DINSTALL_MYSQLTESTDIR="share/mysql/tests" \
		-DINSTALL_PLUGINDIR="lib/mysql/plugin" \
		-DINSTALL_SBINDIR="libexec" \
		-DINSTALL_SCRIPTDIR="bin" \
		-DINSTALL_SHAREDIR="share" \
		-DINSTALL_SQLBENCHDIR="share/mysql" \
		-DINSTALL_SUPPORTFILESDIR="share/mysql" \
		-DWITH_EDITLINE=system \
		-DWITH_LIBWRAP=1 \
		-DWITH_WSREP=1

SHEBANG_FILES=	scripts/*.pl* scripts/*.sh scripts/wsrep_sst_*

.ifdef USE_MYSQL
.error You have `USE_MYSQL' variable defined either in environment or in make(1) arguments. Please undefine and try again.
.endif

# MySQL-Server part
.if !defined(CLIENT_ONLY)
USE_MYSQL=	yes
WANT_MYSQL_VER=	56

USES+=		perl5
USE_PERL5=	run

CONFLICTS_INSTALL=	mysql5[0-57-9]-server-* \
			mariadb*-server-* \
			percona*-server-*

USE_RC_SUBR=	mysql-server

USERS=		mysql
GROUPS=		mysql

MMAN1=		my_print_defaults.1 myisam_ftdump.1 myisamchk.1 myisamlog.1 myisampack.1 \
		mysql.server.1 mysql_convert_table_format.1 mysql_fix_extensions.1 \
		mysql_install_db.1 mysql_plugin.1 mysql_secure_installation.1 mysql_setpermission.1 \
		mysql_tzinfo_to_sql.1 mysql_upgrade.1 mysql_zap.1 mysqlbug.1 \
		mysqld_multi.1 mysqld_safe.1 mysqldumpslow.1 mysqlhotcopy.1 mysqlman.1 \
		mysqltest.1 perror.1 replace.1 resolve_stack_dump.1 resolveip.1

.else
USES+=		libedit
.endif

post-patch:
	@${REINPLACE_CMD} 's/*.1/${MMAN1}/' ${WRKSRC}/man/CMakeLists.txt

.include <bsd.port.pre.mk>

.if ${ARCH} == "armv6"
EXTRA_PATCHES+=		${FILESDIR}/extra-patch-config.h.cmake
.endif

.include <bsd.port.post.mk>
