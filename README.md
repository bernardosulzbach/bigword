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

## Design

Data is serialized after processing in order to speed up subsequent runs.

### Serialization

Human-readable formats are preferred. Because most of the data is plain text,
storing it as binary does not improve performance by any significant amount.

When a string may have spaces, it is dumped after dumping a 32-bit unsigned
integer value which represents the string size in base 10. When it is safe to
assume that the string does not have spaces, it is dumped in a new line all by
itself.
