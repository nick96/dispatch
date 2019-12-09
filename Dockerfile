FROM ubuntu:18.04 as base

RUN apt-get update && apt-get install -y libczmq-dev

FROM base as build

RUN apt-get install -y \
    gcc \
    make \
    libc6-dev

WORKDIR /build
COPY . /build
RUN make all

FROM base as dispatchctld

WORKDIR /dispatch
COPY --from=build /build/bin/dispatchctld /dispatch/dispatchctld
cMD ./dispatchctld

FROM base as dispatchd

WORKDIR /dispatch
COPY --from=build /build/bin/dispatchd /dispatch/dispatchd
CMD ./dispatchd
