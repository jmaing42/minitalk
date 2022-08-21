# minitalk

client <-> server communication via signal `SIGUSR1`, `SIGUSR2`

## Features

- the ACK timeout, connection lost timeout is customizable
- the server can receive any character, even include null (`'\0'`)
- the server is not strongly affected by malicious clients

## Prerequisite

- POSIX-compliant OS
- GNU Make

## Build

```sh
make -C src
```

to see executed commands, set environment variable `V=1`

```sh
make -C src V=1
```

## Usage

there's two executables, `server` and `client`

### server

the server will print the server's PID, and wait for the client

### client

pass the server's PID as the first argument

pass the message as the second argument

```sh
./client "${PID_OF_SERVER}" "${MESSAGE_TO_SEND}"
```

## Options

all options passed to the environment variable:

### Server options

- `TIMEOUT`: ACK timeout in microseconds
- `BUFFER_SIZE`: ACK timeout in microseconds
- `MESSAGE_FORMAT_HEADER`: message template for header
- `MESSAGE_FORMAT_LINE`: message template for each line
- `MESSAGE_FORMAT_FOOTER`: message template for footer
- `MESSAGE_FORMAT_TIMEOUT`: message template for footer

`MESSAGE_FORMAT_HEADER`, `MESSAGE_FORMAT_FOOTER`, `MESSAGE_FORMAT_TIMEOUT` is printf-like format string

- `%%`: literal character `%`
- `%P`: client's PID
- `%L`: message's length
- `%_`: space
- `%T`: tab
- `%L`: line break

for `MESSAGE_FORMAT_LINE`, only `%T` is supported. no way to express `%T`

### Client options

## Example

server

```text
user@m1jy src % ./server
Server pid is 18889. enjoy!
Message from 18895 (12 bytes)
|       Hello world!

Message from 18915 (102 bytes)
|
|       #ifndef FT_EXIT_H
|       # define FT_EXIT_H
|
|       # include <stdlib.h>
|
|       int             ft_exit(signed char status);
|
|       #endif

```

client

```text
user@m1jy src % ./client 18889 'Hello world!'
user@m1jy src % ./client 18889 \
>               "$(cat ft_exit.h | grep -v '*')"
user@m1jy src %
```

## Future plans

- separate client library
- enhance message formatter
- ... issues welcomed!
