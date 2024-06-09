# TinyX

Binary executable format for linux, designed to be very economical in size<br>
A Hello, world executable can be less than 70 bytes<br>

TinyX executable format
-
This format contains only 2 segments: a tinyx header (that can contain a shebang) and just plain assembly instructions<br>
TinyX header is used to identify if an executable is in tinyx format, if there is no shebang in this segment, it should contain a text "tiny" and 1 null byte<br>
[How to make a tinyx executable](TXTUTOR.md)
