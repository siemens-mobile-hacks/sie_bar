# SieBar – Icon Bar Daemon for Siemens Mobile Phones

SieBar is an ELF daemon for Siemens mobile phones that adds custom icons to the system icon bar.

## Requirements

SieBar requires a patch to be applied to the phone firmware. Without it the daemon will not work.

The patch differs depending on the phone model — find the right one here:

[Elfs can add icons to iconbar](https://patches.kibab.com/patches/search.php5?action=search&kw=Elfs+can+add+icons+to+iconbar)

## Building
The SDK must be located at `../sdk` relative to the project root.

```bash
mkdir build && cd build
cmake ..
make
```
