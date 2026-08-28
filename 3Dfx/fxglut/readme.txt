
Here is the original disclaimer written by the author Mark Kilgard <mjk@sgi.com>

About GLUT . . .

GLUT (pronounced like the glut in gluttony) is the OpenGL Utility Toolkit, a
window system independent toolkit for writing OpenGL programs. It implements a
simple windowing application programming interface (API) for OpenGL. GLUT
makes it considerably easier to learn about and explore OpenGL programming.

GLUT is designed for constructing small to medium sized OpenGL programs.
While GLUT is well-suited to learning OpenGL and developing simple OpenGL
applications, GLUT is not a full-featured toolkit so large applications
requiring sophisticated user interfaces are better off using native window
system toolkits like Motif. GLUT is simple, easy, and small. My intent is to
keep GLUT that way.

The GLUT library supports the following functionality:

     Multiple windows for OpenGL rendering. 
     Callback driven event processing. 
     An `idle' routine and timers. 
     Utility routines to generate various solid and wire frame objects. 
     Support for bitmap and stroke fonts. 
     Miscellaneous window management functions. 

The GLUT library has both C, C++ (same as C), and FORTRAN programming
bindings. The GLUT source code distribution is portable to nearly all OpenGL
implementations for the X Window System. GLUT also works well with Brian
Paul's Mesa, a freely available implementation of the OpenGL API.

Because GLUT is window system independent (as much as possible), GLUT can be
implemented for window systems other than X. Implementations of GLUT for
OS/2, NT & Windows 95, and the Mac have ben implemented, but these
implementations are not part of the official GLUT source code distrbution.

The current version of the GLUT API is 3. The current source code
distribution is GLUT 3.3.

.....

This GLUT library is a Windows fullscreen implementation that fits with the
Mesa 3DFX driver written by David Bucciarelli. Permission to make it freely
available was kindly given by Mark Kilgard

Here goes a short description of the library

Due to various limitations imposed by the 3Dfx environment, it is a very
stripped down version compared to the original ( ie GLUT 3.3 ):
  - no support for more than one window
  - no subwindows
  - no x,y coordinates mouse support ( because no support for cursor ) but
mouse buttons are supported
  - no menu support ( because no mouse )
  - keyboard is supported
  - timers are supported
  - no color index mode nor overlay support ( the board does not feature them )
  - no font bitmaps ( it is implemented but the driver does not do bitmaps yet )
  - all calls supported even if a lot issue warnings about unimplemented
features

Timers, mouse buttons and keyboard are supported through the Windows event
loop: it means that glutCreateWindow really creates a window that is a
medium for all events. I did it this way for various reasons: it allows for
easy support for timers and mouse; it was very simple to derive the present
code from the Win32 port that I have already done; the same mechanism can be
reused for a Linux port.

BUGS: Probably numerous because it has been written very fast. I have made
some ( successful ) tests with simple examples from the Red Book but I have
not yet tried Mark Kilgard test suite. Most of them will probably fail
because of all the limitations. Please report bugs ( with code to examplify
them ) to Henri FOUSSE <arnaud@pobox.oleane.com>

TODO: 
- a Linux port. . I do not have access to a Linux box so it's up to someone
else. It would be nice to have a single source tree for both versions
- cursor and menu support. It could be done with OpenGL calls( for
portability ) reusing part of Mark Kilgard code for X or direct frame buffer
access but without some overlay mecanism, it would be rather slow because it
would interact with the frame buffer ( repainting, etc ... ).

GLUT rules !!


                                Henri FOUSSE

 ____________________________________________________________________ 
|  o o  Thomson Training & Simulation                           o o  |
|  o o  Z.A. Les Boutries; 5, rue Leonardo da Vinci; B.P. 252   o o  |
|  o o  78703 Conflans Sainte Honorine Cedex    France          o o  |
|  o o  Tel: [33] (1) 34903614      Fax: [33] (1) 34903602      o o  | 
|____________________________________________________________________| 
