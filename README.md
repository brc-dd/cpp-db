this branch is currently under development\
and this readme discusses about the development\
wrote three files: constants.h shade.h shade.cpp\
\_key\_ and \_iv\_ (present inside constants.h) should be uniquely generated using some CSRNG\
the length of both the strings should be 16 chars only\
wrote one new file: generator.cpp to generate \_key\_ and \_iv\_\
generator.cpp should be compiled first and then the resultant executable file shall be run before further compilation\
there is a security vulnerability that the constants.h may be retrieved by some agent which will disclose the key and iv\
some method needs to be implemented to patch this\
modified constants.h, removed the default \_key\_ and \_iv\_\
compilation process of every file needs to written\
added modified versions of loaders.h and loaders.cpp\
added modified versions of validators.h and validators.cpp
