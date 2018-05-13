# Reference build setup
FROM ubuntu:latest
RUN apt-get --yes --no-upgrade update
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get --yes --no-upgrade install apt-utils
RUN apt-get --yes --no-upgrade install g++-7
ENV CC gcc-7
ENV CXX g++-7
RUN apt-get --yes --no-upgrade install autoconf
RUN apt-get --yes --no-upgrade install libtool
RUN apt-get --yes --no-upgrade install autoconf-archive
RUN apt-get --yes --no-upgrade install cpputest
RUN apt-get --yes --no-upgrade install make
ADD . /home/number-reducer
WORKDIR /home/number-reducer
RUN ./autogen.sh
RUN ./configure --enable-check
RUN make check
