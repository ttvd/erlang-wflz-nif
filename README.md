wflz-erlang-nif
===============

An Erlang NIF wrapper for wfLZ fast compression / decompression library, distributed under WTFPL license, please see http://code.google.com/p/wflz for further information.

# License.

1. wfLZ code is distributed under the WTFPL "DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE".
2. Rest of the code, including Erlang code and nif bindings are distributed under BSD license.

# Building.

1. rake deps -- pull the wflz dependency from google code.
2. rake platform32|platform64 -- where platform is your platform (see platforms through rake -- tasks) to compile the wflz dynamic library NIF.
3. rake compile -- to compile the Erlang part.

# Running.
```
1> code:add_path("ebin").
true

2> wflz:compress(<<"01234567">>).
<<87,70,76,90,12,0,0,0,8,0,0,0,16,0,4,8,48,49,50,51,52,53,
  54,55,0,0,0,0,127,...>>

3> wflz:fastcompress(<<"01234567">>).
<<87,70,76,90,12,0,0,0,8,0,0,0,0,0,4,8,48,49,50,51,52,53,
  54,55,0,0,0,0,0,...>>

4> wflz:decompress(wflz:compress(<<"01234567">>)).
<<"01234567">>

5> wflz:decompress(wflz:fastcompress(<<"01234567">>)).     
<<"01234567">>
```
