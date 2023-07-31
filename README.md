# BigWord

An application to efficiently find words in a dictionary from a multiset of letters.

[![CI](https://github.com/bernardosulzbach/bigword/actions/workflows/ci.yml/badge.svg)](https://github.com/bernardosulzbach/bigword/actions/workflows/ci.yml)

## Building

I suggest you use Ninja.


```bash
$ mkdir build 
$ cd build
$ cmake -G Ninja -D CMAKE_BUILD_TYPE=Release .. 
$ ninja
```

## Static analysis and code formatting

From the build tree, run

```bash
run-clang-tidy -fix -quiet && clang-format -i ../sources/*
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

Human-readable formats are preferred.

Most of the data is plain text, storing it as binary does not improve
performance significantly.

When a string may have spaces, it is dumped after a 32-bit unsigned integer
value which represents the string size. When it is safe to assume that the
string does not have spaces, it is dumped in a new line all by itself.
