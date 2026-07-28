# lcd-tools

This is a command-line tool for configuring a secondary display for watches running AsteroidOS.

As an example, the `catfish` (Mobvoi Ticwatch Pro) watch has a monochrome LCD display that is physically overlaid over the color AMOLED display.  The advantage of this is that the LCD display uses much less power and so when it is displayed and the underlying AMOLED display is off, the battery lasts much longer.

The LCD in this case is capable of displaying a stepcount and heartrate, and this utility provides the means of configuring those items.  On any watch with such a secondary display, run `lcd-tools --help` to see what settings are available.  If the watch doesn't have a secondary display, running `lcd-tools --help` will print nothing.

## Adding watches or features
See the HACKING.md file for developer details on how to add watches or features to this tool.
