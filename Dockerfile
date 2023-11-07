FROM debian:bullseye-slim

LABEL org.opencontainers.image.title="Unit (C)"
LABEL org.opencontainers.image.description="Unofficial build of Unit for Docker."
LABEL org.opencontainers.image.url="https://github.com/bandogora/nunit-Ceasy"
LABEL org.opencontainers.image.source="https://github.com/bandogora/nunit-Ceasy"
LABEL org.opencontainers.image.documentation="https://unit.nginx.org/installation/#docker-images"

ARG debug=false

RUN set -ex \
  && apt-get update \
  && if [ "$debug" = "true" ]; then \
    apt-get install --no-install-recommends --no-install-suggests -y ca-certificates mercurial build-essential \
    libssl-dev libpcre2-dev curl pkg-config vim libcurl4-openssl-dev \
    && echo "alias ls='ls -F --color=auto'" >> /root/.bashrc \
    && echo "alias grep='grep -nI --color=auto'" >> /root/.bashrc; \
  else \
    apt-get install --no-install-recommends --no-install-suggests -y ca-certificates mercurial build-essential \
    libssl-dev libpcre2-dev curl pkg-config libcurl4-openssl-dev; \
  fi

ARG PREFIX="/usr"
ARG EXEC_PREFIX="$PREFIX"
ARG BINDIR="$EXEC_PREFIX/bin"
ENV SBINDIR="$EXEC_PREFIX/sbin"
ARG INCLUDEDIR="$PREFIX/include"
ARG LIBDIR="$EXEC_PREFIX/lib"
ARG MODULESDIR="$LIBDIR/unit/modules"
ARG DATAROOTDIR="$PREFIX/share"
ARG MANDIR="$DATAROOTDIR/man"
ARG LOCALSTATEDIR="$PREFIX/var"
ARG LIBSTATEDIR="$LOCALSTATEDIR/run/unit"
ARG LOGDIR="$LOCALSTATEDIR/log/unit"
ARG LOGFILE="$LOGDIR/unit.log"
ENV RUNSTATEDIR="$LOCALSTATEDIR/run/unit"
ENV PIDPATH="$RUNSTATEDIR/unit.pid"
ENV SOCKET="$RUNSTATEDIR/control.unit.sock"
ARG TMPDIR="/tmp"
ARG UNIT_GROUP="unit"
ARG UNIT_USER="unit"

ARG CLONEDIR="$PREFIX/src/unit"
ARG APPDIR="$PREFIX/src/app"
ARG APPBINDIR="/srv"
ARG NCPU="getconf _NPROCESSORS_ONLN"

# Prepare dirs, group, and user
RUN set -ex \
  && mkdir -p \
    $BINDIR \
    $SBINDIR \
    $INCLUDEDIR \
    $LIBDIR \
    $MODULESDIR \
    $DATAROOTDIR \
    $MANDIR \
    $LOCALSTATEDIR \
    $LOGDIR \
    $RUNSTATEDIR \
    $TMPDIR \
    $CLONEDIR \
    $APPDIR \
    /docker-entrypoint.d \
    /usr/var/lib/unit/certs \
    /usr/var/lib/unit/scripts \
  && mkdir -p -m=700 $LIBSTATEDIR \
  && groupadd --gid 999 $UNIT_GROUP \
  && useradd \
       --uid 999 \
       --gid $UNIT_GROUP \
       --no-create-home \
       --home /nonexistent \
       --comment "unit user" \
       --shell /bin/false \
       $UNIT_USER

# Clone Unit
RUN ["hg", "clone", "-u", "1.31.1-1", "https://hg.nginx.org/unit", "$CLONEDIR"]

WORKDIR $CLONEDIR

#RUN set -ex make -j "$(eval $NCPU)" -C pkg/contrib .njs

ENV DEB_CFLAGS_MAINT_APPEND="-Wp,-D_FORTIFY_SOURCE=2 -fPIC"
ENV DEB_LDFLAGS_MAINT_APPEND="-Wl,--as-needed -pie"
ENV DEB_BUILD_MAINT_OPTIONS="hardening=+all,-pie"
#ENV PKG_CONFIG_PATH="$CLONEDIR/pkg/contrib/njs/build"

ARG CC_OPT="dpkg-buildflags --get CFLAGS"
ARG LD_OPT="dpkg-buildflags --get LDFLAGS"

ARG CONFIGURE_ARGS_MODULES=\
"--cc=gcc \
--openssl \
--user=$UNIT_USER \
--group=$UNIT_GROUP \
--prefix=$PREFIX \
--exec-prefix=$EXEC_PREFIX \
--bindir=$BINDIR \
--sbindir=$SBINDIR \
--includedir=$INCLUDEDIR \
--libdir=$LIBDIR \
--modulesdir=$MODULESDIR \
--datarootdir=$DATAROOTDIR \
--mandir=$MANDIR \
--localstatedir=$LOCALSTATEDIR \
--logdir=$LOGDIR \
--log=$LOGFILE \
--runstatedir=$RUNSTATEDIR \
--pid=$PIDPATH \
--control=unix:$SOCKET \
--tmpdir=$TMPDIR"

RUN set -ex \
  && if [ "$debug" = "true" ]; \
    then ./configure $CONFIGURE_ARGS_MODULES --debug --cc-opt="$(eval $CC_OPT)" --ld-opt="$(eval $LD_OPT)"; \
    else ./configure $CONFIGURE_ARGS_MODULES --cc-opt="$(eval $CC_OPT)" --ld-opt="$(eval $LD_OPT)"; \
  fi \
  && make -j $(eval $NCPU) unitd \
  && install -pm755 /usr/src/unit/build/sbin/unitd "$SBINDIR/unitd" \
  && ln -sf /dev/stdout "$LOGFILE" \
  && make clean \
  && if [ "$debug" = "true" ]; \
    then ./configure --openssl --debug --cc-opt="$(eval $CC_OPT)" --ld-opt="$(eval $LD_OPT)"; \
    else ./configure --openssl --cc-opt="$(eval $CC_OPT)" --ld-opt="$(eval $LD_OPT)"; \
  fi \
  && make -j $(eval $NCPU) libunit-install \
  && chmod +x ./build/lib/libunit.a \
  && mv ./build/lib/libunit.a ../app/libunit.a \
  && make clean

RUN set -ex \
  && cd \
  && savedAptMark="$(apt-mark showmanual)" \
  && for f in $SBINDIR/unitd $MODULESDIR/*.unit.so; do \
      ldd $f | awk '/=>/{print $(NF-1)}' | while read n; do dpkg-query -S $n; done | sed 's/^\([^:]\+\):.*$/\1/' | sort | uniq >> /requirements.apt; \
     done \
  && apt-mark showmanual | xargs apt-mark auto > /dev/null \
  && { [ -z "$savedAptMark" ] || apt-mark manual $savedAptMark; } \
  && /bin/true \
  && apt-get update \
  && apt-get --no-install-recommends --no-install-suggests -y install $(cat /requirements.apt)

# Copy app source files
COPY --link ./src/* "$APPDIR"

# Compile and link C app against libunit.a
Run set -x \
  && cd /usr/src/app \
  && gcc \
    -O2 \
    -fstack-protector-strong \
    -Wformat -Werror=format-security \
    -Wp,-D_FORTIFY_SOURCE=2 \
    -fPIC \
    -std=c11 \
    -I/usr/src/unit/src \
    main.c custom_http_client.c \
    -o app \
    -Wl,-z,relro \
    -Wl,-z,now \
    -Wl,--as-needed \
    -pie \
    -L. -lc -lunit -lpthread -lcurl \
  && chmod +x ./app \
  && mv ./app /srv/app

# Cleanup
RUN set -x \
  && apt-get purge -y --auto-remove build-essential \
  && rm -rf $CLONEDIR \
  && rm -rf $APPDIR \
  && rm -rf /var/lib/apt/lists/* \
  && rm -f /requirements.apt

# Copy initial config
COPY ./config.json /docker-entrypoint.d/

# Copy the default entrypoint
COPY --link ./docker-entrypoint.sh /usr/local/bin/

# Make sure the entrypoint is executable
RUN ["chmod", "+x", "/usr/local/bin/docker-entrypoint.sh"]

STOPSIGNAL SIGTERM

ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
EXPOSE 80
CMD ["unitd", "--no-daemon", "--control", "unix:$SOCKET"]
