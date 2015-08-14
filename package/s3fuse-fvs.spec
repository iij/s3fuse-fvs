%define name s3fuse-fvs
%define version 0.16
%define release 1

%define debug_package %{nil}

Summary: FUSE Driver for AWS S3 and Google Storage
Name: %{name}
Version: %{version}
Release: %{release}
Source: s3fuse-%{version}.tar.gz
Group: Applications/System
BuildRoot: %{_builddir}/%{name}-root
License: Apache-2.0
BuildRequires: openssl-devel >= 0.9.8
BuildRequires: boost-devel >= 1.41
BuildRequires: fuse-devel >= 2.7.3
BuildRequires: libxml2-devel >= 2.7.6
BuildRequires: libcurl >= 7.0.0
Requires: openssl >= 0.9.8
Requires: boost >= 1.41
Requires: fuse-libs >= 2.7.3
Requires: libcurl >= 7.0.0

%description
Provides a FUSE filesystem driver for Amazon AWS S3 and Google Storage buckets.

%prep
%setup -q -n s3fuse-%{version}

%build
autoreconf --force --install
./configure --enable-build-rpm=yes --prefix=/usr --sysconfdir=/etc
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install
mv $RPM_BUILD_ROOT/etc/s3fuse.conf $RPM_BUILD_ROOT/etc/s3fuse-fvs.conf
cd $RPM_BUILD_ROOT/usr/bin/
ln -s s3fuse s3fuse-fvs

%clean
rm -rf $RPM_BUILD_ROOT

%post

%preun

%files
%defattr(-,root,root)
%config /etc/s3fuse-fvs.conf
%doc README
%doc ChangeLog
%doc INSTALL
%doc COPYING
%doc /usr/share/man/man5
/usr/bin/s3fuse
/usr/bin/s3fuse-fvs
/usr/bin/s3fuse_gs_get_token
/usr/bin/s3fuse_sha256_sum
/usr/bin/s3fuse_vol_key
