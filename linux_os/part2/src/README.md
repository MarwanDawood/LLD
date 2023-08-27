## Steps to solve kernel panic
1. go to `mylib` folder then run `make` then `sudo make install`
2. go to `init` folder then run `make` then `sudo make install`
3. print shared library dependency `ldd mylib.so`, all should be linked
4. now, there're two options,
    * copy the library from `/lib/libmy.so` to `/usr/lib/libmy.so`
    or
    * create the file `/mnt/myos/etc/ld.so.conf` with the content `/lib` on one line
    *  run `ldconfig -r /mnt/myos` to create cache file (`libmy.so` should be already in `/mnt/myos/lib` folder at the time)

