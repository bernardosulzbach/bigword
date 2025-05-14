# BigWord

An application to efficiently find words in a dictionary from a multiset of letters.

You might be looking at a mirror of the [original repository on GitHub](https://github.com/bernardosulzbach/bigword).

[![CI](https://github.com/bernardosulzbach/bigword/actions/workflows/ci.yml/badge.svg)](https://github.com/bernardosulzbach/bigword/actions/workflows/ci.yml)

## Building

I suggest you use Ninja.


```
$ mkdir build
$ cd build
$ cmake -G Ninja -D CMAKE_BUILD_TYPE=Release ..
$ ninja
```

## Static analysis and code formatting

From the build tree, run

```
run-clang-tidy -fix -quiet && gersemi -i ../CMakeLists.txt && clang-format -i ../sources/*
```

## Running

```
$ ./bigword --help
> Usage: ./bigword [OPTIONS] LETTERS
>     --configuration  Output the option values.
>     --copyright      Output the license.
>     --line-number    Output line numbers.
>     --source         Set the source file.
>     --time           Output computation times.
>     --version        Output the program version.

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

$ ./bigword --time anythingyousynthesize irks lock padlock
> -- Finished loading after 60 milliseconds.
> -- Query 1 matched 1 word after 2 milliseconds.
> synthesization
> -- Query 2 matched 4 words after 248 microseconds.
> irks
> kirs
> kris
> risk
> -- Query 3 matched 2 words after 294 microseconds.
> colk
> lock
> -- Query 4 matched 1 word after 1 millisecond.
> padlock
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
