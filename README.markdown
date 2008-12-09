what
====

Apps to help you see what's going on when you run [Celerity][cel] tests.

how
===

The applications set up a DRb server (with ACL) on port 6429. Celerity will look
for a «viewer» on this port whenever an instance of the browser is created, and if
found, calls `render_html(html_string, current_url)` on the DRb object for 
every page load.

The RubyCocoa version has the WebKit inspector enabled - right-click, then «Inspect Element».
The SWT version includes the MouseOver DOM inspector.

[cel]: http://celerity.rubyforge.org "Celerity Home Page"