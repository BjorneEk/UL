# Documentation
---
## Table of contents
1. [<UL/types.h>](#types)
2. [<UL/assert.h>](#assert.h)
    1. [```log_err```](#log_err)
    2. [```log_warn```](#log_warn)
    3. [```assertf```](#assertf)
    4. [```assertf_to```](#assertf_to)
    5. [```assert```](#assert)
    6. [```assert_to```](#assert_to)
3. [<UL/str.h>](#str)
    1. [```is_ascii```](#is_ascii)
    2. [```nbr_of_digits```](#nbr_of_digits)
    3. [```iarrtos```](#iarrtos)
    4. [```farrtos```](#farrtos)
    5. [```nvals```](#nvals)
    6. [```CSV_iarr```](#CSV_iarr)
    6. [```CSV_farr```](#CSV_farr)
4. [<UL/IO.h>](#io)
    1. [```get_filesize```](#get_filesize)
    2. [```read_sfile```](#read_sfile)
    3. [```read_file```](#read_file)
    4. [```remove_file```](#remove_file)
    5. [```create_file```](#create_file)
    6. [```rename_file```](#rename_file)
    7. [```file_exists```](#file_exists)
    8. [```file_can_read```](#file_can_read)
    9. [```file_can_write```](#file_can_write)
    10. [```file_can_exec```](#file_can_exec)
    11. [```write_file```](#write_file)
    12. [```nwrite_file```](#nwrite_file)
    13. [```append_file```](#append_file)
    14. [```nappend_file```](#nappend_file)
    15. [```hexdump```](#hexdump)
4. [<UL/math.h>](#math)
    1. [```constants```](#constants)
    2. [```low/high words```](#lhword)
    3. [```low/high bytes```](#lhbyte)
    4. [```min/max```](#minmax)
    5. [```sin2/cos2```](#cos2)
    6. [```rad/deg```](#radian)
    6. [```clamp```](#clamp)
    5. [```sign```](#sign)
    6. [```rand```](#rand)
    6. [```remap```](#remap)
4. [<UL/macro.h>](#macro)

---
# <UL/types.h> <a name="types"></a>
The ```<UL/types.h>``` header file includes useful standard typedefs.

---
```c
typedef _Bool BOOL;

typedef unsigned char      u8_t;
typedef unsigned short     u16_t;
typedef unsigned int       u32_t;
typedef unsigned long long u64_t;

typedef signed char        i8_t;
typedef signed short       i16_t;
typedef signed int         i32_t;
typedef signed long        i64_t;

typedef float              f32_t;
typedef double             f64_t;
```

---
# <UL/assert.h> <a name="assert.h"></a>
The ```<UL/assert.h>``` header contains assert macros aswell as macros for printing errors and warnings.

---
### log_err <a name="log_err"></a>
```c
#define log_err(format, ...)
```
prints ```[Error]: format``` to the ```stderr``` output buffer

### log_warn <a name="log_warn"></a>
```c
#define log_warn(format, ...)
```
prints ```[Warning]: format``` to the ```stdout``` output buffer

### assertf <a name="assertf"></a>
```c
#define assertf(assertion, format, ...)
```
if ```@assertion``` is false, print ```[Error]: format``` to ```stderr``` and call ```exit(-1):```
### assertf_to <a name="assertf_to"></a>
```c
#define assertf_to(assertion, label, format, ...)
```
if ```@assertion``` is false, print ```[Error]: format``` to ```stderr``` and ```goto label```

### assert <a name="assert"></a>
```c
#define assert(assertion)
```
if ```@assertion``` is false, print ```[Error]: assertion error``` to ```stderr``` and call ```exit(-1):```
### assert_to <a name="assert_to"></a>
```c
#define assert_to(assertion, label)
```
if ```@assertion``` is false, print ```[Error]: assertion error``` to ```stderr``` and ```goto label```

---
# <UL/str.h> <a name="str"></a>
The ```<UL/str.h>``` header contains various useful string functions.

---
### is_ascii <a name="is_ascii"></a>
```c
bool is_ascii(i32_t i);
```
if ```@i``` is a ```ascii``` character return ```true``` else return ```false```.
### nbr_of_digits <a name="nbr_of_digits"></a>
```c
u32_t nbr_of_digits(u64_t n, u32_t base);
```
returns the number of digits needed to represent ```@n``` in the base ```@base```.
### iarrtos <a name="iarrtos"></a>
```c
char * iarrtos(i32_t * data, i64_t length);
```
'int array to string', allocates and returns a comma delimited string representation of the first ```@length``` i32_t´s in ```@data```.
### iarrtos <a name="farrtos"></a>
```c
char * farrtos(f64_t * data, i64_t length);
```
'double array to string', allocates and returns a comma delimited string representation of the first ```@length``` f64_t´s in ```@data```.
### nvals <a name="nvals"></a>
```c
i64_t nvals(const char * buff, char delim);
```
returns the number of enties in ```@buff``` separated by ```@delim```,
useful for example to count number of values in a csv file eg. ```nvals("data.csv", ',');```.
### CSV_iarr <a name="CSV_iarr"></a>
```c
i64_t CSV_iarr(i32_t ** res, char * data, char del);
```
converts ```@data```: a string whith integer values separated by ```@del```, into a array of values: ```*@res``` and returns the number of values in ```@res```.
### CSV_farr <a name="CSV_farr"></a>
```c
i64_t CSV_farr(f64_t ** res, char * data, char del);
```
converts ```@data```: a string whith float values separated by ```@del```, into a array of values: ```*@res``` and returns the number of values in ```@res```.

---
# <UL/IO.h> <a name="io"></a>
The ```<UL/IO.h>``` header contains I/O functions mainly for making working whith files easier.

---
### get_filesize <a name="get_filesize"></a>
```c
i64_t get_filesize(const char *fname);
```
returns number the size of the file named ```@fname``` in bytes.
### read_file <a name="read_file"></a>
```c
u8_t * read_file(const char *fname, i64_t *len);
```
allocates and returns a ```u8_t*``` containing the contents of the file named ```@fname```. if ```@len``` is not ```NULL``` it is set to the length of the read file in bytes (allocated size is length of the read file + 1 in order to enable the addition of a ```\0``` char to convert it to a string).
### read_sfile <a name="read_sfile"></a>
```c
char * read_sfile(const char *fname, i64_t *len);
```
allocates and returns a ```\0``` terminated string containing the contents of the file named ```@fname```. if ```@len``` is not ```NULL``` it is set to the length of the read file in bytes.
### remove_file <a name="remove_file"></a>
```c
BOOL remove_file(const char *fname);
```
returns if the file named ```@fname``` was removed.
### create_file <a name="create_file"></a>
```c
void create_file(const char *fname);
```
creates the file named ```@fname```.
### rename_file <a name="rename_file"></a>
```c
BOOL rename_file(const char *src, const char *fname);
```
renames the file named ```@src``` file to ```@fname``` and returns if this was successful.
### file_exists <a name="file_exists"></a>
```c
BOOL file_exists(const char *fname);
```
returns true if the file named ```@fname``` exists.
### file_can_read <a name="file_can_read"></a>
```c
BOOL file_can_read(const char *fname);
```
returns true if the program can read the file named ```@fname```.
### file_can_write <a name="file_can_write"></a>
```c
BOOL file_can_write(const char *fname);
```
returns true if the program can write to the file named ```@fname```.
### file_can_exec <a name="file_can_exec"></a>
```c
BOOL file_can_exec(const char *fname);
```
returns true if the program can execute the file named ```@fname```.
### write_file <a name="write_file"></a>
```c
void write_file(const char *fname, const char *str);
```
write the contents of the string ```@str``` to the file named ```@fname``` if no such files exists it is created.
### nwrite_file <a name="nwrite_file"></a>
```c
void nwrite_file(const char *fname, const char *str u64_t n);
```
write the first ```@n``` bytes of the string ```@str``` to the file named ```@fname``` if no such files exists it is created.

### append_file <a name="append_file"></a>
```c
void append_file(const char *fname, const char *str);
```
appends the contents of the string ```@str``` to the file named ```@fname``` if no such files exists it is created.
### nappend_file <a name="nappend_file"></a>
```c
void nappend_file(const char *fname, const char *str u64_t n);
```
appends the first ```@n``` bytes of the string ```@str``` to the file named ```@fname``` if no such files exists it is created.

### hexdump <a name="hexdump"></a>
```c
void hexdump(const u8_t *data, u64_t len);
```
prints the first ```@len``` bytes of data in ```@data``` formated similar to [hexdump](https://en.wikipedia.org/wiki/Hex_dump)

---
# <UL/math.h> <a name="math"></a>

The ```<UL/math.h>``` header file contains various math related macros

---
### constants <a name="constants"></a>
```c
#define PI_HALF 1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TWO_PI  6.28318530717958647692528676655900576

#define RAD_IN_DEG 57.295779513082320876798154814105170408 // RAD_IN_DEG = 180 / PI
#define DEG_IN_RAD 0.017453292519943295769236907684886127  // DEG_IN_RAD = PI / 180
```
math constants
### low/high words <a name="lhword"></a>
```c
#define LOW_16(address)
#define HIGH_16(address)
```
returns the low / high u16_t values of the u32_t ```@address```
### low/high bytes <a name="lhbyte"></a>
```c
#define LOW_8(word)
#define HIGH_8(word)
```
returns the low / high u8_t bytes of the u16_t ```@word```
### min/max bytes <a name="minmax"></a>
```c
#define MAX(a, b)
#define MIN(a, b)
```
returns the largest / smallest value of ```@a``` and ```@b```
### cos2/sin2 <a name="cos2"></a>
```c
#define COS2F(_x)
#define SIN2F(_x)
```
returns quadratic sin/cos of ```@_x``` as a f32_t
### rad/deg <a name="radian"></a>
```c
#define deg_to_rad(_x)
#define rad_to_deg(_x)
```
returns ```@_x``` in radians/degrees
### clamp <a name="clamp"></a>
```c
#define clamp(v, min, max)
```
returns ```@v``` clamped between ```@min``` and ```@max```
### sign <a name="sign"></a>
```c
#define sign(v)
```
returns -1 if ```@v```is negative else 1
### rand <a name="rand"></a>
```c
#define randf(min, max)
#define randi(min, max)
```
returns a random f64_t / i32_t between ```@min``` andi ```@max```.
### remap <a name="remap"></a>
```c
#define remap(v,a1,a2,b1,b2)
```
returns ```@v``` remaped from the range ```@a1->@a2``` to the range ```@b1->@b2```.

---
# <UL/macro.h> <a name="macro"></a>
The ```<UL/macro.h``` header contains some less common specialized macros for example gcc ```__attribute__``` macros like:
```c
#define PACKED        __attribute__((__packed__))
#define WUNUSED       __attribute__((warn_unused_result))
#define ALWAYS_INLINE __attribute__((always_inline))
#define COLD          __attribute__((cold))
#define CONST         __attribute__ ((const))
#define DEPRICIATED   __attribute__ ((deprecated))
#define PURE          __attribute__ ((pure))
```
---
