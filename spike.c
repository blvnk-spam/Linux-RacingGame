/* GIMP RGBA C-Source image dump (spike.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 2 + 1];
} spike = {
  32, 32, 2,
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015MkMk\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\256sY\316Y\316\256s\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\256sY\316Y\316\256s\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\256s\370\305\377"
  "\377\377\377\030\306\256s\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\010BA\010<\347\040\015"
  "\040\015\040\015\040\015\040\015\040\015mkIJ\354b\354bIJmk\040\015\040\015\040\015\040\015"
  "\040\015\040\015<\347A\010\010B\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "A\010\236\367\216s$!a\010\232\326\040\015\216s\343\030\202\020\040\000\000\000\000\000\040"
  "\000\202\020\343\030\216s\040\015\232\326a\010$!\216s\236\367A\010\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015<\347\216s\373\336~\367\226\265$!\206\061"
  "\242\020\000\000A\010\000\000\266\265\226\265\000\000A\010\000\000\242\020\206\061$!\226\265~"
  "\367\373\336\216s<\347\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015$!~\367\377\377\236\367\236\367\060\204\000\000\000\000\000\000\313Z\333\336\333\336"
  "\313Z\000\000\000\000\000\000\060\204\236\367\236\367\377\377~\367$!\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015a\010\266\265\236\367\377\377\377"
  "\377\263\234\000\000\000\000\000\000\327\275\377\377\377\377\327\275\000\000\000\000\000\000\263"
  "\234\377\377\377\377\236\367\226\265a\010\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\232\326E)\236\367\377\377\034\347\216s\000\000\000\000"
  "\000\000\263\234\236\367\236\367\263\234\000\000\000\000\000\000\216s\034\347\377\377\236"
  "\367$!\232\326\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\206\061\060\204\263\234\216se)\000\000\000\000\000\000\307\071\020\204\020\204\307"
  "\071\000\000\000\000\000\000e)\216s\263\234\060\204\206\061\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\216s\242\020\000\000\000\000\000\000\000\000\000\000\000\000"
  "\040\000\000\000\000\000\000\000\000\000\040\000\000\000\000\000\000\000\000\000\000\000\000\000\242\020\216s\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\343\030\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000A\010\000\000\000\000\000\000\000\000A\010\000\000\000\000\000\000\000\000\000\000\000\000\000\000\343\030\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\256smka\010A\010\000\000\000\000\000\000"
  "\000\000\040\000A\010\000\000\253Z\226\265\226\265\253Z\000\000A\010\040\000\000\000\000\000\000\000\000\000"
  "A\010a\010mk\256s\040\015\040\015\040\015\040\015\256s\256s\030\306IJ\000\000\000\000\313Z\327"
  "\275\263\234\307\071\000\000\000\000\253ZQ\214=\357=\357Q\214\253Z\000\000\000\000\307\071"
  "\263\234\327\275\313Z\000\000\040\000IJ\370\305\256s\256s\040\015MkY\316Y\316\377"
  "\377\354b\000\000\266\265\333\336\377\377\236\367\020\204\000\000\000\000\226\265=\357"
  "\273\336\273\336=\357\226\265\000\000\000\000\020\204\236\367\377\377\333\336\226"
  "\265\000\000\354b\377\377Y\316Y\316MkMkY\316Y\316\377\377\354b\000\000\266\265\333"
  "\336\377\377\236\367\020\204\000\000\000\000\226\265=\357\273\336\273\336=\357\226"
  "\265\000\000\000\000\020\204\236\367\377\377\333\336\226\265\000\000\354b\377\377Y\316"
  "Y\316Mk\040\015\256s\256s\370\305IJ\000\000\000\000\313Z\327\275\263\234\307\071\000\000"
  "\000\000\253ZQ\214=\357=\357Q\214\253Z\000\000\000\000\307\071\263\234\327\275\313Z\000"
  "\000\040\000IJ\370\305\256s\256s\040\015\040\015\040\015\040\015\256smka\010A\010\000\000\000"
  "\000\000\000\000\000\040\000A\010\000\000\253Z\226\265\226\265\253Z\000\000A\010\040\000\000\000\000\000\000"
  "\000\000\000A\010a\010mk\256s\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\343"
  "\030\000\000\000\000\000\000\000\000\000\000\000\000\000\000A\010\000\000\000\000\000\000\000\000A\010\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\343\030\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\216s\242\020\000\000\000\000\000\000\000\000\000\000\000\000\040\000\000\000\000\000\000\000\000\000\040\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\242\020\216s\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\206\061\060\204\263\234\216se)\000\000\000\000\000\000\307\071\020"
  "\204\020\204\307\071\000\000\000\000\000\000e)\216s\263\234\060\204\206\061\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\232\326E)\236\367\377"
  "\377\034\347\216s\000\000\000\000\000\000\263\234\236\367\236\367\263\234\000\000\000\000\000\000"
  "\216s\034\347\377\377\236\367$!\232\326\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015a\010\266\265\236\367\377\377\377\377\263\234\000\000"
  "\000\000\000\000\327\275\377\377\377\377\327\275\000\000\000\000\000\000\263\234\377\377\377"
  "\377\236\367\226\265a\010\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015$!~\367\377\377\236\367\236\367\060\204\000\000\000\000\000\000\313Z\333\336"
  "\333\336\313Z\000\000\000\000\000\000\060\204\236\367\236\367\377\377~\367$!\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015<\347\216s\373\336~\367\266"
  "\265E)\206\061\242\020\000\000A\010\000\000\266\265\266\265\000\000A\010\000\000\242\020\206\061"
  "E)\266\265~\367\373\336\216s<\347\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015A\010\236\367\216s$!a\010\232\326\040\015\216s\343\030a\010\000\000\000\000\000"
  "\000\000\000a\010\343\030\216s\040\015\232\326a\010$!\216s\236\367A\010\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\350AA\010<\347\040\015\040\015\040\015\040\015\040"
  "\015\040\015mkIJ\354b\354bIJmk\040\015\040\015\040\015\040\015\040\015\040\015<\347A\010"
  "\010B\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\256s\370\305\377\377\377\377\030\306\256"
  "s\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\256sY\316Y\316\256s\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\256sY\316Y\316"
  "\256s\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040"
  "\015\040\015\040\015\040\015\040\015\040\015MkMk\040\015\040\015\040\015\040\015\040\015\040\015"
  "\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015\040\015",
};

