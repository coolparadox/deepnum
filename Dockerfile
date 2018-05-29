# Reference build setup
FROM ubuntu:latest
RUN apt-get --yes --no-upgrade update
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get --yes --no-upgrade --no-install-recommends install apt-utils
RUN apt-get --yes --no-upgrade --no-install-recommends install g++-7
RUN apt-get --yes --no-upgrade --no-install-recommends install autoconf
RUN apt-get --yes --no-upgrade --no-install-recommends install libtool
RUN apt-get --yes --no-upgrade --no-install-recommends install cpputest
RUN apt-get --yes --no-upgrade --no-install-recommends install make
RUN apt-get --yes --no-upgrade --no-install-recommends install doxygen
RUN apt-get --yes --no-upgrade --no-install-recommends install automake
RUN apt-get --yes --no-upgrade --no-install-recommends install graphviz
RUN apt-get --yes --no-upgrade --no-install-recommends install autoconf-archive
ENV CC gcc-7
ENV CXX g++-7
ADD . /home/number-reducer
WORKDIR /home/number-reducer
RUN ./autosetup.sh
RUN ./configure --enable-doc --enable-check
RUN make
RUN make check
