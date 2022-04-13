## Test task for energizeglobal

Write a program in "C" which should take as an input "XML" file (not nested, primitive) and convert it into a binary encoded "TLV" file (not nested).
The tag of each XML node shows the type of data. There are two types of data allowed: numeric or text.

It is allowed to use any "XML" parser.

Input file example:

```
<START>
<text>string1</text>
<text>string2</text>
<text>string3</text>
<numeric>205011</numeric>
<numeric>7</numeric>
</START>
```

Output: TLV File

### For build Test task use
```
    make all
```

### For clean objects-file for Test task use
```
    make clean
```

### For run Test task use
```
    ./xml_to_tlv -i [xml_filename] -o [tlv_filename]
```




For parsing I am using Mini-Xml library
(https://www.msweet.org/blog/2021-11-06-mxml-3.3.html Mini-Xml library)
### Mini-Xml install

```
    .\configure
    make
    make install
```
