
PsiChain
=====================================

What is PsiChain?
----------------

Psi Chain aims to be the world’s first Quantum secured decentralized digital asset ledger that is EVM compatible with high performance and scalability.
See https://psichain.org, or read the [original whitepaper](https://github.com/PsiChain/PsiChain/blob/main/Psichain-Whitepaper.pdf).

License
-------

The PsiChain is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/PsiChain/psichain/tags) are created
regularly to indicate new official, stable release versions of the PsiChain.

Install
-------

### Linux
```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install --assume-yes build-essential libtool autotools-dev autoconf automake pkg-config libssl-dev libboost-all-dev libqt5gui5 libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev libminiupnpc-dev libevent-dev libdb++-dev git cmake
```
##### Install libsodium 
If you have **Ubuntu 17.10** and higher

```bash
sudo apt-get install --assume-yes libsodium-dev
```
##### Install Botan-2.7.0 
```bash
wget https://botan.randombit.net/releases/Botan-2.7.0.tgz
tar -xzvf Botan-2.7.0.tgz
cd Botan-2.7.0/
./configure.py --disable-modules=locking_allocator
make
sudo make install && cd ..
sudo ldconfig

# check if installed
ldconfig -p | grep botan
```

### Mac OS X

#### Homebrew packages

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

```bash
brew install autoconf automake berkeley-db4 boost miniupnpc pkg-config protobuf qt libtool libevent zeromq
```

#### MacPorts packages

```bash
sudo port install wget autoconf automake libtool pkgconfig libsodium boost libevent protobuf
```

### Install PsiChain
```bash
git clone https://github.com/PsiChain/psichain
cd psichain
git submodule update --init
./autogen.sh
./configure  
make
```

### Start Mainnet
```bash
cd src
./bpqd -printtoconsole
```

### Start Testnet
```bash
cd src
./bpqd -printtoconsole -testnet
```
