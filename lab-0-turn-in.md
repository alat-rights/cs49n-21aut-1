1. Hardware problems on the pi that results in no power delivery.
2. Any bug that causes pre-compiled programs to not be deliverable to the pi.
   We will be able to discern that the bug was not caused by a broken bootloader
   if the RPI also refuses to work with a known-good program.
3. We will know if there is a problem with the bootloader that means the pi
   cannot run any compiled programs.
4. We would know if there is a problem with the compiler (lest we suspect that
   our own program was the root of our troubles).
