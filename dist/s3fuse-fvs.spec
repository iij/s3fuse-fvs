%define name s3fuse-fvs
%define version 0.16
%define release 1

%define debug_package %{nil}

Summary: FUSE Driver for AWS S3 and Google Storage
Name: %{name}
Version: %{version}
Release: %{release}
Source: %{name}-%{version}.tar.gz
Group: Applications/System
BuildRoot: %{_builddir}/%{name}-root
License: Apache-2.0
BuildRequires: openssl-devel >= 0.98
BuildRequires: boost-devel >= 1.41
BuildRequires: fuse-devel >= 2.8.3
BuildRequires: libxml++-devel >= 2.28.0
BuildRequires: libxml2-devel >= 2.7.6
BuildRequires: libcurl >= 7.0.0
Requires: openssl >= 0.98
Requires: boost >= 1.41
Requires: fuse-libs >= 2.8.3
Requires: libxml++ >= 2.28.0
Requires: libcurl >= 7.0.0

%description
Provides a FUSE filesystem driver for Amazon AWS S3 and Google Storage buckets.

%prep
%setup -q -n %{name}-%{version}

%build
autoreconf --force --install
./configure --enable-build-rpm=yes --prefix=/usr --sysconfdir=/etc
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post

%preun

%files
%defattr(-,root,root)
%config /etc/s3fuse-fvs.conf
%doc ChangeLog
%doc COPYING
%doc INSTALL
%doc README
/usr/bin/s3fuse-fvs
/usr/bin/s3fuse-fvs_gs_get_token