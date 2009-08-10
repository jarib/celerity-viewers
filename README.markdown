what
====

Apps to help you see what's going on when you run [Celerity][cel] tests.

how
===

The applications set up a DRb server (with ACL) on port 6429. Celerity will look for anyone listening on this port whenever an instance of the browser is created, and, if found, call `render_html(html_string, current_url)` on the DRb object for every page loaded.
The RubyCocoa version has the WebKit inspector enabled - right-click and _Inspect Element_. The SWT version includes the [MouseOver DOM inspector][modi].

Note: The pure Cocoa version in the repository is not working yet, you should use the RubyCocoa version for now.

future
======

- look at [jdic](https://jdic.dev.java.net/) as possible swt alternative
- fix cocoa viewer
- other languages? Qt, Java

[cel]: http://celerity.rubyforge.org "Celerity Home Page"
[modi]: http://slayeroffice.com/tools/modi/v2.0/modi_help.html