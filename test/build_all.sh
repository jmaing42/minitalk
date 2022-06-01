#!/bin/sh

cd $(dirname "$0")/../src

make SANITIZER=undefined PROFILE=release TARGET=production
make SANITIZER=undefined PROFILE=release TARGET=development
make SANITIZER=undefined PROFILE=debug TARGET=production
make SANITIZER=undefined PROFILE=debug TARGET=development
make SANITIZER=address PROFILE=release TARGET=production
make SANITIZER=address PROFILE=release TARGET=development
make SANITIZER=address PROFILE=debug TARGET=production
make SANITIZER=address PROFILE=debug TARGET=development
make SANITIZER=memory PROFILE=release TARGET=production
make SANITIZER=memory PROFILE=release TARGET=development
make SANITIZER=memory PROFILE=debug TARGET=production
make SANITIZER=memory PROFILE=debug TARGET=development
make SANITIZER=leak PROFILE=release TARGET=production
make SANITIZER=leak PROFILE=release TARGET=development
make SANITIZER=leak PROFILE=debug TARGET=production
make SANITIZER=leak PROFILE=debug TARGET=development
make PROFILE=release TARGET=production
make PROFILE=release TARGET=development
make PROFILE=debug TARGET=production
make PROFILE=debug TARGET=development
make MOULINETTE_MODE=1
