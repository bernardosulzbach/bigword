# BigWord

An application to efficiently find words in a dictionary from a multiset of letters.

[![Build Status](https://travis-ci.org/mafagafogigante/bigword.svg?branch=travis)](https://travis-ci.org/mafagafogigante/bigword)

## Building

```bash
$ mkdir bld 
$ cd bld
$ cmake ..
$ make
```

## Running

```bash
$ ./bigword linkedlists
> instilled
> kindliest
> niellists
> slinkiest

$ ./bigword abcdefghij
> bighead
> jibhead

$ ./bigword aeioubsdlinux
> unoxidisable
```
