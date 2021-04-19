#!/bin/bash
# docker run -d --restart=always --name hustdb -p 8088:8088 -v /srv/hustdb:/var/lib/postgres/data recolic/hustdb

chown -R postgres /var/lib/postgres/data &&
[ "$(ls -A /var/lib/postgres/data)" ] || su -l postgres bash -c 'initdb --locale en_US.UTF-8 -E UTF8 -D /var/lib/postgres/data' &&

nginx &&
    mkdir -p /run/postgresql && chown -R postgres /run/postgresql && su -l postgres bash -c 'pg_ctl -D /var/lib/postgres/data start' &
# pg_ctl -D /var/lib/postgres/data -l logfile start ///// postgres -D /var/lib/postgres/data

sleep 5
/app/app -listen :8080


