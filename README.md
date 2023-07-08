# BoB Decryptor

An encoding analyzer, written in C99, for linux.

## Description

BoB Decryptor is an analyzer for a text file that has all different encodings per line.

You may think what a file has that fxxking weird format... But, BoB does it!

This analyzer supports these formats:

- UTF-8
- UTF-16
- UTF-32
- CP949 HUC (EUC-KR)

## How to build it?

### Requisites

- Cygwin (If you use Windows OS)
- GCC
- GNU Binutils
- Make
- Python3

### Let's build it

1. Build CP949-compatibility pack

```shell
cd cp949
chmod +x cp949.sh
./cp949.sh
cd ..
```

2. Build with Makefile

```shell
make all
```

3. Then, result file will be in `bin/`

## How to run it?

```shell

```
