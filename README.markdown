what
====

Apps to help you see what's going on when you run [Celerity][cel] tests.
There are more READMEs further down the tree:

* [Qt][qt-readme]
* [RubyCocoa][rc-readme]
* [SWT][swt-readme]


how
===

The applications set up a TCP server on port 6429. Celerity will look for anyone listening on this port whenever an instance of the browser is created, and, if found, send HTML dumps whenever a page is changed using the protocol described on [this page][wiki-viewers] on the Celerity wiki.

The RubyCocoa and Qt apps has the WebKit inspector enabled - right-click and _Inspect Element_. The SWT version includes the [MouseOver DOM inspector][modi].

Note: The pure Cocoa version in the repository is not working yet, use Qt or RubyCocoa for now.

future
======

- look at [jdic](https://jdic.dev.java.net/) as possible swt alternative
- fix cocoa viewer? (json libs: [1](http://code.google.com/p/json-framework/), [2](http://zachwaugh.com/2009/01/how-to-use-json-in-cocoaobjective-c/))

[cel]: http://celerity.rubyforge.org "Celerity Home Page"
[modi]: http://slayeroffice.com/tools/modi/v2.0/modi_help.html
[wiki-viewers]: http://wiki.github.com/jarib/celerity/viewers
[qt-readme]: http://github.com/jarib/celerity-viewers/blob/master/qt/README.markdown
[rc-readme]: http://github.com/jarib/celerity-viewers/blob/master/rubycocoa/README.markdown
[swt-readme]: http://github.com/jarib/celerity-viewers/blob/master/jruby-swt/README.markdown
