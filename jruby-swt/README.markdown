how to use
==========

1. build a jar for your platform

  `rake jar`

2. run the app

  `jruby -r pkg/celerity-swt-{win,linux,mac}.jar -r celerity_viewer`

3. fire up a celerity script and watch the pages render

notes
=====

* On OS X, you need to use Java 5/32-bit and add -J-XstartOnFirstThread to the 
JRuby arguments (or look at the RubyCocoa version instead).
* By setting the environment variable SWT\_MOZILLA, the app will try to use 
  Mozilla/XULRunner as the rendering engine. See [this page][swtmoz] for how to 
  make it work. 
  
inspector
=========

The 'Show Inspector' button loads up MouseOver DOM Inspector, a pure-javascript
DOM inspector. Here is [more info about it][modi].

Enjoy!

[swtmoz]: http://www.eclipse.org/swt/faq.php#howusemozilla 
[modi]: http://slayeroffice.com/tools/modi/v2.0/modi_help.html