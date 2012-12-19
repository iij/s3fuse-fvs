ACLOCAL_AMFLAGS = -I .

if BUILD_RPM
SUBDIRS=dist src
else
SUBDIRS=src
endif

rpm: dist
	rpmdir=`pwd`/rpm;                                                  \
	rm -rf $$rpmdir;                                                   \
	mkdir -p $$rpmdir/SOURCES;                                         \
	mkdir -p $$rpmdir/RPMS;                                            \
	mkdir -p $$rpmdir/SRPMS;                                           \
	mkdir -p $$rpmdir/BUILD;                                           \
	mkdir -p $$rpmdir/BUILDROOT;                                       \
	mkdir -p $$rpmdir/SPECS;                                           \
	cp ${PACKAGE_TARNAME}-${PACKAGE_VERSION}.tar.gz $$rpmdir/SOURCES/; \
	rpmbuild -ba --define "_topdir $$rpmdir" dist/s3fuse-fvs.spec
