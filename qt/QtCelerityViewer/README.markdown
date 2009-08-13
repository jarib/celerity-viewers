For now this only works on *nix.
Please help if you have a Windows machine with dev tools available! :)

Binaries
--------

If you don't want to compile the app yourself, binary downloads will be available on [GitHub](http://github.com/jarib/celerity-viewers/downloads).
In addition, you need the Qt frameworks:

  * Ubuntu/Debian:

      `sudo apt-get install libqt4-webkit`


  * Mac OS X:

      Download and install the «Framework only» version from the [Qt Downloads page](http://qt.nokia.com/downloads)

Use Rake
--------

If you have Ruby and Rake installed it will try to do the Right Thing:

on os x:

    `rake install && open /Applications/QtCelerityViewer.app`

on a Debian-based linux:

    `rake compile && ./QtCelerityViewer`


Building manually
-----------------

Dependencies:

  * cmake
  * Qt 4.5 packages:
    - QtCore
    - QtGui
    - QtNetwork
    - QtWebKit

Debian-based linux:

    $ sudo apt-get install cmake libqt4-dev
    $ qmake && make

OS X:

    $ curl -O http://get.qtsoftware.com/qtsdk/qt-sdk-mac-opensource-2009.03.1.dmg && open qt-sdk-mac-opensource-2009.03.1.dmg
    $ port install cmake
    $ qmake && make

Configuration
-------------

By default the server will start on _0.0.0.0:6429_.
Set env vars to override:

  * `QT_CELERTIY_VIEWER_HOST`
  * `QT_CELERTIY_VIEWER_PORT`

The WebKit inspector can be opened by right-clicking in the document and choosing «Inspect».
