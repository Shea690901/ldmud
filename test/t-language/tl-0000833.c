                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
#if \
 __VERSION_MAJOR
/* If this line (yes, this one) exceeds 2048 Bytes in the file,
 * then it can crash the driver (more precisely the lexer).
 * The name of the define above is wrong on purpose.
 * The first line after the #if lines doesn't need to be a comment.
 */
#endif

                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                                                                   
                                                  
#if \
 __VERSION_MAJOR__
/* If this line (yes, this one) exceeds 4096 Bytes in the file,
 * then the driver may read beyond the buffer and complain
 * about null bytes in the file. In contrast to the case above
 * here the name of the define is written correctly.
 */
#endif

int run_test() { return 1; }
