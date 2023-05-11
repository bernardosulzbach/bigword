# BigWord

An application to efficiently find words in a dictionary from a multiset of letters.

[![Build Status](https://travis-ci.com/bernardosulzbach/bigword.svg?branch=master)](https://travis-ci.com/bernardosulzbach/bigword)

## Building

I suggest you use Ninja.


```bash
$ mkdir build 
$ cd build
$ cmake -G Ninja -D CMAKE_BUILD_TYPE=Release .. 
$ ninja
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
