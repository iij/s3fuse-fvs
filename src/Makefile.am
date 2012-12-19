AM_CPPFLAGS += $(BOOST_CPPFLAGS) -DPACKAGE_NAME="\"${PACKAGE_NAME}\"" -DPACKAGE_TARNAME="\"${PACKAGE_TARNAME}\"" -DPACKAGE_VERSION="\"${PACKAGE_VERSION}\""
AM_LDFLAGS += $(BOOST_THREAD_LDFLAGS)

LDADD = $(BOOST_THREAD_LIBS)

if BUILD_TESTS
SUBDIRS = . tests
endif

bin_PROGRAMS = s3fuse-fvs s3fuse-fvs_gs_get_token

s3fuse_fvs_SOURCES = \
	fvs_service_impl.cc \
	fvs_service_impl.h \
	aws_service_impl.cc \
	aws_service_impl.h \
	config.cc \
	config.inc \
	config.h \
	file_transfer.cc \
	file_transfer.h \
	fs.cc \
	fs.h \
	gs_service_impl.cc \
	gs_service_impl.h \
	logger.cc \
	logger.h \
	main.cc \
	object_cache.cc \
	object_cache.h \
	object.cc \
	object.h \
	open_file.cc \
	open_file.h \
	request.cc \
	request.h \
	service.cc \
	service.h \
	service_impl.cc \
	service_impl.h \
	ssl_locks.cc \
	ssl_locks.h \
	thread_pool.cc \
	thread_pool.h \
	util.cc \
	util_gnu.inc \
	util_macos.inc \
	util.h \
	version.h \
	xattr.cc \
	xattr.h \
	xml.cc \
	xml.h \
	mime_types.cc \
	mime_types.h

s3fuse_fvs_gs_get_token_SOURCES = \
	fvs_service_impl.cc \
	fvs_service_impl.h \
	aws_service_impl.cc \
	aws_service_impl.h \
	config.cc \
	config.inc \
	config.h \
	gs_service_impl.cc \
	gs_service_impl.h \
	gs_get_token.cc \
	logger.cc \
	logger.h \
	object_cache.cc \
	object_cache.h \
	object.cc \
	object.h \
	request.cc \
	request.h \
	service.cc \
	service.h \
	service_impl.cc \
	service_impl.h \
	ssl_locks.cc \
	ssl_locks.h \
	xattr.cc \
	xattr.h \
	util.cc \
	util_gnu.inc \
	util_macos.inc \
	util.h \
	mime_types.cc \
	mime_types.h

dist_sysconf_DATA = \
	s3fuse-fvs.conf

s3fuse-fvs.conf: config.inc
	../build-config.sh $^ $@
