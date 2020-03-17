# Cute Light Text Previewer
## What is this?

This software is open source and can open large text files in an instant. There is no file editing function. Because this software is a prototype of +Note text editor to be developed next. However, it is useful as a translator that works without a web browser.

## Building
### Requirements 

* Qt5 (and QMake)
* Qt5 PrintSupport
* Qt5 GUI
* Qt5 Dev Tools(Linguist)
* Qt5 Network
* QDDarkStyleSheet (Usually, they are cloned as submodules.)
#### Linux

Clone the source code. I also need a dark style, so add the recursive option.

:warning: Danger! Don't clone other than master branch!
```bash
git clone https://github.com/enjoysoftware/cute-light-text-previewer --recursive
```
After cloning is completed, build.   
:warning: Warning: Running the make command with the j option can cause problems. In that case, execute without the j option.   
```bash
qmake
make
```   
Executable is created to root directory.
#### Windows

After cloning the source code using Sourcetree, GitKraken, Git Bash, etc., execute it using QtCreator. For details, check the help of these software.   
Build is possible in both Visual Studio and MinGW.
### How to create an executable without dark style
By removing "WITH_DARKSTYLE" from the "DEFINES" item in the cute-light-text-previewer.pro file, you can create an executable file without dark style.