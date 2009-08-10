what
====

Apps to help you see what's going on when you run [Celerity][cel] tests.

how
===

The applications set up a TCP server on port 6429. Celerity will look for anyone listening on this port whenever an instance of the browser is created, and, if found, send HTML dumps whenever a page is changed using the protocol described on [this page][wiki-viewers] on the Celerity wiki.

The RubyCocoa version has the WebKit inspector enabled - right-click and _Inspect Element_. The SWT version includes the [MouseOver DOM inspector][modi].

Note: The pure Cocoa version in the repository is not working yet, you should use the RubyCocoa version for now.

future
======

- look at [jdic](https://jdic.dev.java.net/) as possible swt alternative
- fix cocoa viewer
- other languages? Qt, Java

[cel]: http://celerity.rubyforge.org "Celerity Home Page"
[modi]: http://slayeroffice.com/tools/modi/v2.0/modi_help.html
[wiki-viewers]: http://wiki.github.com/jarib/celerity/viewers