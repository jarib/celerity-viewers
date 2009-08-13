For now this only works on *nix.

Dependencies
------------

  * cmake
  * Qt 4.5 packages:
    - QtCore
    - QtGui
    - QtNetwork
    - QtWebKit

Building
--------

    $ qmake && make

Configuration
-------------

By default the server will start on 0.0.0.0:6429.
You can override this by setting env vars:

  * `QT_CELERTIY_VIEWER_HOST`
  * `QT_CELERTIY_VIEWER_PORT`


