# Building Ice for C++ on Linux

This file describes the Ice source distribution, including information about
compiler requirements, third-party dependencies, and instructions for building
and testing the distribution. If you prefer, you can install [binary
packages][1] for supported platforms that contain pre-compiled libraries,
executables, and everything else necessary to build Ice applications on Linux.

## C++ Build Requirements

### Operating Systems and Compilers

Ice is expected to build and run properly on any recent Linux distribution for
x86 and x86_64, and was extensively tested using the operating systems and
compiler versions listed for our [supported platforms][2].

### Third-Party Packages

Ice has dependencies on a number of third-party packages. Install these packages 
before building Ice for C++:

 - [expat][3] 2.0
 - [OpenSSL][4] 0.9.8 or later
 - [bzip][5] 1.0
 - [LMDB][6] 0.9.16
 - [mcpp][7] 2.7.2 (with patches)

Expat, OpenSSL and bzip are included with most Linux distributions. 

ZeroC supplies binary packages for LMDB and mcpp for several Linux distributions 
that do not include them. You can install these packages as shown below:

#### Amazon Linux
    wget https://zeroc.com/download/GPG-KEY-zeroc-release
    sudo rpm --import GPG-KEY-zeroc-release
    cd /etc/yum.repos.d
    sudo wget https://dev.zeroc.com/rpm/thirdparty/zeroc-thirdparty-amzn1.repo
    sudo yum install lmdb-devel mcpp-devel

#### RHEL 7
    wget https://zeroc.com/download/GPG-KEY-zeroc-release
    sudo rpm --import GPG-KEY-zeroc-release
    cd /etc/yum.repos.d
    sudo wget https://dev.zeroc.com/rpm/thirdparty/zeroc-thirdparty-el7.repo
    sudo yum install lmdb-devel mcpp-devel

#### SLES 12
    wget https://zeroc.com/download/GPG-KEY-zeroc-release
    sudo rpm --import GPG-KEY-zeroc-release
    cd /etc/yum.repos.d
    sudo wget https://dev.zeroc.com/rpm/thirdparty/zeroc-thirdparty-sles12.repo
    sudo yum install mcpp-devel

## Building Ice

In a command window, change to the `cpp` subdirectory:

    $ cd cpp

Edit `config/Make.rules` to establish your build configuration. The comments in
the file provide more information. Pay particular attention to the variables
that define the locations of the third-party libraries.

Now you're ready to build Ice:

    $ make

This will build the Ice core libraries, services, and tests.

### 32-bit Source Builds on Linux x86_64

By default, builds on x86_64 are 64-bit. To perform a 32-bit build on an x86_64
Linux system, set the environment variable `LP64` to no, as shown below:

    $ export LP64=no

## Installing a C++ Source Build

Simply run `make install`. This will install Ice in the directory specified by
the `prefix` variable in `config/Make.rules`.

After installation, make sure that the `prefix/bin` directory is in your `PATH`.

If you choose to not embed a `runpath` into executables at build time (see your
build settings in `config/Make.rules`) or did not create a symbolic link from
the `runpath` directory to the installation directory, you also need to add the
library directory to your `LD_LIBRARY_PATH`.

On an x86 system, the library directory is:

    prefix/lib                   (RHEL, SLES, Amazon)
    prefix/lib/i386-linux-gnu    (Ubuntu)

On an x86_64 system:

    prefix/lib64                 (RHEL, SLES, Amazon)
    prefix/lib/x86_64-linux-gnu  (Ubuntu)

When compiling Ice programs, you must pass the location of the `prefix/include`
directory to the compiler with the `-I` option, and the location of the library
directory with the `-L` option. If building a C++11 program, you must add the
`/c++11` suffix to the library directory (such as `prefix/lib/c++11`).

## Running the Test Suite

Python is required to run the test suite. Additionally, the Glacier2 tests
require the Python module `passlib`, which you can install with the command:

    $ pip install passlib

After a successful source build, you can run the tests as follows:

    $ make test

This command is equivalent to:

    $ python allTests.py

If everything worked out, you should see lots of `ok` messages. In case of a
failure, the tests abort with `failed`.

[1]: https://doc.zeroc.com/display/Ice37/Using+the+Linux+Binary+Distributions
[2]: https://doc.zeroc.com/display/Ice37/Supported+Platforms+for+Ice+3.7.0
[3]: http://expat.sourceforge.net
[4]: http://openssl.org
[5]: http://bzip.org
[6]: http://symas.com/mdb/
[7]: https://github.com/zeroc-ice/mcpp
