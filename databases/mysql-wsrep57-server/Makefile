PORTNAME?=	mysql-wsrep
PORTVERSION=	5.7.17
PORTREVISION?=	0
CATEGORIES=	databases ipv6
MASTER_SITES=	http://releases.galeracluster.com/source/
DISTFILES=	mysql-wsrep-5.7.17-25.11.tar.gz
DISTNAME=	mysql-wsrep-5.7.17-25.11
PKGNAMESUFFIX?=	57-server
DATADIR=        ${PREFIX}/share/mysql
BOOST_DIR=      /var/tmp/boost
MAINTAINER=	info@galeracluster.com
COMMENT?=	A version of MySQL modified for Galera replication (server package)

BROKEN_powerpc64=	Does not build

SLAVEDIRS=	databases/mysql57-client
USES=		cmake shebangfix

BUILD_DEPENDS=	bison:devel/bison

MY_DBDIR=       /var/db/mysql
MY_SECDIR=      /var/db/mysql_secure
MY_TMPDIR=      /var/db/mysql_tmpdir

RUN_DEPENDS=	socat:net/socat lsof:sysutils/lsof netcat:net/netcat rsync:net/rsync

OPTIONS_GROUP=          STORAGE
OPTIONS_GROUP_STORAGE=  ARCHIVE BLACKHOLE EXAMPLE FEDERATED INNOBASE PARTITION PERFSCHEMA
OPTIONS_SUB=            YES
STORAGE_DESC=           Permissible "Storage Engines" (to compile statically into the server)
ARCHIVE_DESC=           Compile "Archive Storage" statically in server
BLACKHOLE_DESC=         Compile "Blackhole Storage" statically in server
EXAMPLE_DESC=           Compile "Example Storage" statically in server
FEDERATED_DESC=         Compile "Federated Storage" statically in server
INNOBASE_DESC=          Compile "InnoDB Storage" statically in server
PARTITION_DESC=         Compile "Partitioning support Storage" statically in server
PERFSCHEMA_DESC=        Compile "Performance Schema Storage" statically in server

ARCHIVE_CMAKE_ON=       -DWITH_ARCHIVE_STORAGE_ENGINE=1
BLACKHOLE_CMAKE_ON=     -DWITH_BLACKHOLE_STORAGE_ENGINE=1
EXAMPLE_CMAKE_ON=       -DWITH_EXAMPLE_STORAGE_ENGINE=1
FEDERATED_CMAKE_ON=     -DWITH_FEDERATED_STORAGE_ENGINE=1
INNOBASE_CMAKE_ON=      -DWITH_INNOBASE_STORAGE_ENGINE=1
PARTITION_CMAKE_ON=     -DWITH_PARTITION_STORAGE_ENGINE=1
PERFSCHEMA_CMAKE_ON=    -DWITH_PERFSCHEMA_STORAGE_ENGINE=1

OPTIONS_GROUP+=         FEATURES
OPTIONS_GROUP_FEATURES= PERFSCHM
FEATURES_DESC=          Default features knobs
PERFSCHM_DESC=          Enable "Performance Schema" by default (High RAM usage)
OPTIONS_DEFAULT+=       PERFSCHM

PERFSCHM_SUB_LIST+=             PERFSCHEMRC=""
PERFSCHM_SUB_LIST_OFF+=         PERFSCHEMRC="--skip-performance-schema"
FEDERATED_SUB_LIST+=            FEDER="--federated"
FEDERATED_SUB_LIST_OFF+=        FEDER=""

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
		-DWITH_WSREP=1 \
                -DDOWNLOAD_BOOST=1 -DWITH_BOOST=${BOOST_DIR}

SHEBANG_FILES=	scripts/*.pl* scripts/*.sh scripts/wsrep_sst_*

.ifdef USE_MYSQL
.error You have `USE_MYSQL' variable defined either in environment or in make(1) arguments. Please undefine and try again.
.endif

SUB_LIST+=      MY_DBDIR=${MY_DBDIR} \
                MY_SECDIR=${MY_SECDIR} \
                MY_TMPDIR=${MY_TMPDIR}

PLIST_SUB+=     MY_DBDIR=${MY_DBDIR} \
                MY_SECDIR=${MY_SECDIR} \
                MY_TMPDIR=${MY_TMPDIR}


# MySQL-Server part
.if !defined(CLIENT_ONLY)
USE_MYSQL=	yes
WANT_MYSQL_VER=	57

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
