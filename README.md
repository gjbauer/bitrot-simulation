# Bitrot Simulation
## Simulate bit rot against an AES-256 key schedule

-----

To start with, make sure that you have the OpenSSL development libraries for your distribution (assuming Linux) are installed.

For Ubuntu this can be done with the following command:

`sudo apt install libssl-dev`

After that, make sure that you initialize the 'tiny-AES-C' submodule by running the following command:

`git submodule update --init`

Finally, you should simply be able to build the project by running `make`
