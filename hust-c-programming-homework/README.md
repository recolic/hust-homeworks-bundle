# chw [![Build Status](https://travis-ci.org/recolic/chw.svg?branch=master)](https://travis-ci.org/recolic/chw)

### [check doc](https://www.dropbox.com/s/11qrys7ewgg2las/C%E8%AF%AD%E8%A8%80%E8%AF%BE%E7%A8%8B%E8%AE%BE%E8%AE%A12017.pdf?dl=0)

### UI usage:

    cd src
    cmake -DCMAKE_BUILD_TYPE=Release . && make
    # Run chw-cli for cui edition.
    cd ../bin
    ./wserver &
    cd gui
    your_browser client.min.html

### This branch

I'm showing C++ code inside without encryption. master branch is just to make silly document happy.

### qt

cmake won't make qt autoly. qt is finished in only serveral hours, because of which codes in it must never be adapted into industry env.
