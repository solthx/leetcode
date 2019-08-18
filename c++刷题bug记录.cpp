1. 关于字符串相加问题，例如: //#451 使用堆来做的时候
    while(..){
        ...
        res = res + c; // c是char类型，res是string类型 
        ...
    }
在这里，如果c的个数很多很多，可能会发生MLE
    string operator+(string&, string&)operator将参数复制到新的字符串对象中。然后将此临时返回值复制到res- 这可能还涉及复制到新的更大的缓冲区。除非启用C ++ 11，否则将使用移动分配，因此避免了后一个可能的分配+复制。

    string& operator+=(const string&)不会创建新的字符串对象。它会就地修改现有的字符串缓冲区 - 除非需要更大的缓冲区，在这种情况下无法避免重新分配。

    因此，res += c避免在动态内存中创建临时缓冲区。如果字符串足够大，则同时使用的副本数量加倍可以使程序的峰值内存使用量大约翻倍。此外，额外的临时分配可能会增加动态内存空间的碎片，这会增加动态内存管理的开销。这两个因素可能导致超出程序的内存限制。

    所以我们尽量使用 res += c 来代替 res = res + c

英文版解释:

    string operator+(string&, string&) operator copies the arguments into a new string object. You then copy this temporary return value into res - which may also involve copying into a new, larger buffer. Unless C++11 is enabled, in which case move assignment will be used, so the latter potential allocation + copy is avoided.

    string& operator+=(const string&) does not create a new string object. It modifies the existing string buffer in-place - unless a larger buffer is needed, in which case reallocation cannot be avoided.

    So, res += c avoids creation of temporary buffers in dynamic memory. If the string is large enough, doubling the number of simultaneously used copies can roughly double the peak memory use of the program. Also, the extra temporary allocations may increase the fragmentation of dynamic memory space, which increases the overhead of dynamic memory management. These two factors may cause the memory limit given for the program to be exceeded.