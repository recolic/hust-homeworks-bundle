from archlinux/base

maintainer root@recolic.net

expose 8088
run pacman -Syu --noconfirm postgresql go nginx git

copy frontend/nginx.conf /etc/nginx/nginx.conf
copy . /app

workdir /app
run go get -d ./...
run go build

# run su -l postgres bash -c 'initdb --locale en_US.UTF-8 -E UTF8 -D /var/lib/postgres/data'
cmd "/app/entry.sh"

