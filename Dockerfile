# Reference build setup
FROM ubuntu:latest
RUN apt-get --yes --no-upgrade update
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get --yes --no-upgrade --no-install-recommends install apt-utils
RUN apt-get --yes --no-upgrade --no-install-recommends install g++-7 autoconf libtool cpputest make doxygen automake graphviz autoconf-archive libgsl-dev
ADD . /home/deepnum
WORKDIR /home/deepnum
RUN ./autosetup.sh
RUN ./configure CC=gcc-7 CXX=g++-7 --enable-doc --enable-check
RUN make
RUN make check
